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

#include "../../gen-cpp/service_1.h"
#include "../../gen-cpp/service_3.h"

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

class service_1Handler : public service_1If {
private:
  std::default_random_engine _gen;
  std::lognormal_distribution<double> _dist;
  double _scaler;
  ClientPool<ThriftClient<service_3Client>> *_service_3_client_pool;
  rpc_params *_rpc_1_params;
  std::lognormal_distribution<double> _rpc_1_proc_dist;
  rpc_params *_rpc_3_params;
  std::lognormal_distribution<double> _rpc_3_pre_dist;
  std::lognormal_distribution<double> _rpc_3_post_dist;

public:
  explicit service_1Handler(
      ClientPool<ThriftClient<service_3Client>> *service_3_client_pool,
      rpc_params *rpc_3_params, rpc_params *rpc_1_params, double scaler) {
    _service_3_client_pool = service_3_client_pool;
    _scaler = scaler;
    auto seed =
        duration_cast<microseconds>(system_clock::now().time_since_epoch())
            .count();
    _gen = std::default_random_engine(seed);
    _rpc_1_params = rpc_1_params;
    double rpc_1_proc_time_mean = _rpc_1_params->proc_time_mean;
    if (rpc_1_proc_time_mean != 0) {
      double rpc_1_proc_time_std = _rpc_1_params->proc_time_std;
      double rpc_1_proc_m = log(
          rpc_1_proc_time_mean /
          sqrt(1 + pow(rpc_1_proc_time_std, 2) / pow(rpc_1_proc_time_mean, 2)));
      double rpc_1_proc_s = sqrt(
          log(1 + pow(rpc_1_proc_time_std, 2) / pow(rpc_1_proc_time_mean, 2)));
      _rpc_1_proc_dist =
          std::lognormal_distribution<double>(rpc_1_proc_m, rpc_1_proc_s);
    }
    _rpc_3_params = rpc_3_params;
    double rpc_3_pre_time_mean = _rpc_3_params->pre_time_mean;
    if (rpc_3_pre_time_mean != 0) {
      double rpc_3_pre_time_std = _rpc_3_params->pre_time_std;
      double rpc_3_pre_m = log(
          rpc_3_pre_time_mean /
          sqrt(1 + pow(rpc_3_pre_time_std, 2) / pow(rpc_3_pre_time_mean, 2)));
      double rpc_3_pre_s = sqrt(
          log(1 + pow(rpc_3_pre_time_std, 2) / pow(rpc_3_pre_time_mean, 2)));
      _rpc_3_pre_dist =
          std::lognormal_distribution<double>(rpc_3_pre_m, rpc_3_pre_s);
    }
    double rpc_3_post_time_mean = _rpc_3_params->post_time_mean;
    if (rpc_3_post_time_mean != 0) {
      double rpc_3_post_time_std = _rpc_3_params->post_time_std;
      double rpc_3_post_m = log(
          rpc_3_post_time_mean /
          sqrt(1 + pow(rpc_3_post_time_std, 2) / pow(rpc_3_post_time_mean, 2)));
      double rpc_3_post_s = sqrt(
          log(1 + pow(rpc_3_post_time_std, 2) / pow(rpc_3_post_time_mean, 2)));
      _rpc_3_post_dist =
          std::lognormal_distribution<double>(rpc_3_post_m, rpc_3_post_s);
    }
  }

  ~service_1Handler() override = default;

  void rpc_1(const std::map<std::string, std::string> &carrier) override {
    TextMapReader reader(carrier);
    auto parent_span = opentracing::Tracer::Global()->Extract(reader);
    auto span = opentracing::Tracer::Global()->StartSpan(
        "rpc_1_server", {opentracing::ChildOf(parent_span->get())});

    double proc_time;
    double proc_time_mean = _rpc_1_params->proc_time_mean;
    if (proc_time_mean != 0) {
      DistributionType distribution_type = _rpc_1_params->distribution_type;
      switch (distribution_type) {
      case constant:
        proc_time = proc_time_mean;
        break;
      case log_normal:
        proc_time = _rpc_1_proc_dist(_gen);
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
    vector<std::shared_future<void>> fuWaitVec[1];
    std::shared_future<void> fuVec[1];

    fuVec[0] = std::async(std::launch::async, [&]() {
      std::map<std::string, std::string> writer_text_map;
      TextMapWriter writer(writer_text_map);
      if (!fuWaitVec[0].empty()) {
        for (auto &i : fuWaitVec[0]) {
          i.wait();
        }
      }
      auto self_span = opentracing::Tracer::Global()->StartSpan(
          "rpc_3_client", {opentracing::ChildOf(&(span->context()))});
      opentracing::Tracer::Global()->Inject(self_span->context(), writer);
      auto service_3_client_wrapper = _service_3_client_pool->Pop();
      if (!service_3_client_wrapper) {
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
        se.message = "Failed to connect to service_3";
        throw se;
      } else {
        auto service_3_client = service_3_client_wrapper->GetClient();
        try {
          service_3_client->rpc_3(writer_text_map);
        } catch (TException &tx) {
          cout << "ERROR: " << tx.what() << endl;
          _service_3_client_pool->Push(service_3_client_wrapper);
        }
        _service_3_client_pool->Push(service_3_client_wrapper);
      }
      self_span->Finish();
    });

    for (auto &i : fuVec) {
      i.wait();
    }
    span->Finish();
  }
};

void startServer(TServer &server) {
  cout << "Starting the service_1 server..." << endl;
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
  SetUpTracer("config/jaeger-config.yml", "service_1");
  std::string service_3_addr = services_json["service_3"]["server_addr"];
  int service_3_port = services_json["service_3"]["server_port"];
  ClientPool<ThriftClient<service_3Client>> service_3_client_pool(
      "service_3", service_3_addr, service_3_port, 0, 1024, 5000);

  string tmp_rpc_3_distribution_type = rpcs_json["rpc_3"]["distribution_type"];
  DistributionType rpc_3_distribution_type;
  if (tmp_rpc_3_distribution_type == "log_normal")
    rpc_3_distribution_type = log_normal;
  else
    rpc_3_distribution_type = constant;
  rpc_params rpc_3_params = {
      rpc_3_distribution_type,
      rpcs_json["rpc_3"]["pre_time_mean"],
      rpcs_json["rpc_3"]["pre_time_std"],
      rpcs_json["rpc_3"]["post_time_mean"],
      rpcs_json["rpc_3"]["post_time_std"],
      rpcs_json["rpc_3"]["proc_time_mean"],
      rpcs_json["rpc_3"]["proc_time_std"],
  };

  string tmp_rpc_1_distribution_type = rpcs_json["rpc_1"]["distribution_type"];
  DistributionType rpc_1_distribution_type;
  if (tmp_rpc_1_distribution_type == "log_normal")
    rpc_1_distribution_type = log_normal;
  else
    rpc_1_distribution_type = constant;
  rpc_params rpc_1_params = {
      rpc_1_distribution_type,
      rpcs_json["rpc_1"]["pre_time_mean"],
      rpcs_json["rpc_1"]["pre_time_std"],
      rpcs_json["rpc_1"]["post_time_mean"],
      rpcs_json["rpc_1"]["post_time_std"],
      rpcs_json["rpc_1"]["proc_time_mean"],
      rpcs_json["rpc_1"]["proc_time_std"],
  };

  double scaler = services_json["service_1"]["scaler"];
  int port = services_json["service_1"]["server_port"];
  int poolSize = 50;
  TThreadedServer server(
      stdcxx::make_shared<service_1Processor>(
          stdcxx::make_shared<service_1Handler>(
              &service_3_client_pool, &rpc_3_params, &rpc_1_params, scaler)),
      stdcxx::make_shared<TServerSocket>("0.0.0.0", port),
      stdcxx::make_shared<TFramedTransportFactory>(),
      stdcxx::make_shared<TBinaryProtocolFactory>());
  startServer(server);
}
