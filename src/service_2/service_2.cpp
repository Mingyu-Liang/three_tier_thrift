#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"
#include "../tracing.h"
#include <jaegertracing/Tracer.h>
#include <opentracing/propagation.h>
#include <thrift/TToString.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TServer.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/stdcxx.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <yaml-cpp/yaml.h>

#include <execinfo.h>
#include <fstream>
#include <future>
#include <getopt.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <time.h>

#include "../../gen-cpp/service_2.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using json = nlohmann::json;
using std::chrono::microseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

using namespace auto_microservices;

enum DistributionType { constant, log_normal };

struct rpc_params {
  DistributionType distribution_type;
  double pre_time_mean;
  double pre_time_std;
  double post_time_mean;
  double post_time_std;
  double proc_time_mean;
  double proc_time_std;
};

class service_2Handler : public service_2If {
private:
  std::default_random_engine _gen;
  std::lognormal_distribution<double> _dist;
  double _scaler;
  rpc_params *_rpc_2_params;
  std::lognormal_distribution<double> _rpc_2_proc_dist;

public:
  explicit service_2Handler(rpc_params *rpc_2_params, double scaler) {
    _scaler = scaler;
    auto seed =
        duration_cast<microseconds>(system_clock::now().time_since_epoch())
            .count();
    _gen = std::default_random_engine(seed);
    _rpc_2_params = rpc_2_params;
    double rpc_2_proc_time_mean = _rpc_2_params->proc_time_mean;
    if (rpc_2_proc_time_mean != 0) {
      double rpc_2_proc_time_std = _rpc_2_params->proc_time_std;
      double rpc_2_proc_m = log(
          rpc_2_proc_time_mean /
          sqrt(1 + pow(rpc_2_proc_time_std, 2) / pow(rpc_2_proc_time_mean, 2)));
      double rpc_2_proc_s = sqrt(
          log(1 + pow(rpc_2_proc_time_std, 2) / pow(rpc_2_proc_time_mean, 2)));
      _rpc_2_proc_dist =
          std::lognormal_distribution<double>(rpc_2_proc_m, rpc_2_proc_s);
    }
  }

  ~service_2Handler() override = default;

  void rpc_2(const std::map<std::string, std::string> &carrier) override {
    TextMapReader reader(carrier);
    auto parent_span = opentracing::Tracer::Global()->Extract(reader);
    auto span = opentracing::Tracer::Global()->StartSpan(
        "rpc_2_server", {opentracing::ChildOf(parent_span->get())});

    double proc_time;
    double proc_time_mean = _rpc_2_params->proc_time_mean;
    if (proc_time_mean != 0) {
      DistributionType distribution_type = _rpc_2_params->distribution_type;
      switch (distribution_type) {
      case constant:
        proc_time = proc_time_mean;
        break;
      case log_normal:
        proc_time = _rpc_2_proc_dist(_gen);
        break;
      default:
        proc_time = proc_time_mean;
      }
    } else
      proc_time = proc_time_mean;
    proc_time *= _scaler;
    auto proc_t0 =
        duration_cast<microseconds>(system_clock::now().time_since_epoch())
            .count();
    while (true) {
      auto proc_t1 =
          duration_cast<microseconds>(system_clock::now().time_since_epoch())
              .count();
      if (proc_t1 - proc_t0 >= (int)(proc_time))
        break;
    }
    span->Finish();
  }
};

void startServer(TServer &server) {
  cout << "Starting the service_2 server..." << endl;
  server.serve();
  cout << "Done." << endl;
}

int main(int argc, char *argv[]) {
  json rpcs_json;
  json services_json;
  std::ifstream json_file;
  json_file.open("config/rpcs.json");
  if (json_file.is_open()) {
    json_file >> rpcs_json;
    json_file.close();
  } else {
    cout << "Cannot open rpcs-config.json" << endl;
    return -1;
  }
  json_file.open("config/services.json");
  if (json_file.is_open()) {
    json_file >> services_json;
    json_file.close();
  } else {
    cout << "Cannot open services-config.json" << endl;
    return -1;
  }

  srand((unsigned)time(NULL));
  SetUpTracer("config/jaeger-config.yml", "service_2");
  string tmp_rpc_2_distribution_type = rpcs_json["rpc_2"]["distribution_type"];
  DistributionType rpc_2_distribution_type;
  if (tmp_rpc_2_distribution_type == "log_normal")
    rpc_2_distribution_type = log_normal;
  else
    rpc_2_distribution_type = constant;
  rpc_params rpc_2_params = {
      rpc_2_distribution_type,
      rpcs_json["rpc_2"]["pre_time_mean"],
      rpcs_json["rpc_2"]["pre_time_std"],
      rpcs_json["rpc_2"]["post_time_mean"],
      rpcs_json["rpc_2"]["post_time_std"],
      rpcs_json["rpc_2"]["proc_time_mean"],
      rpcs_json["rpc_2"]["proc_time_std"],
  };

  double scaler = services_json["service_2"]["scaler"];
  int port = services_json["service_2"]["server_port"];
  int poolSize = 50;
  TThreadedServer server(
      stdcxx::make_shared<service_2Processor>(
          stdcxx::make_shared<service_2Handler>(&rpc_2_params, scaler)),
      stdcxx::make_shared<TServerSocket>("0.0.0.0", port),
      stdcxx::make_shared<TFramedTransportFactory>(),
      stdcxx::make_shared<TBinaryProtocolFactory>());
  startServer(server);
}
