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

#include "../../gen-cpp/service_0.h"
#include "../../gen-cpp/service_1.h"
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

class service_0Handler : public service_0If {
private:
  std::default_random_engine _gen;
  std::lognormal_distribution<double> _dist;
  double _scaler;
  ClientPool<ThriftClient<service_1Client>> *_service_1_client_pool;
  ClientPool<ThriftClient<service_2Client>> *_service_2_client_pool;
  rpc_params *_rpc_0_params;
  std::lognormal_distribution<double> _rpc_0_proc_dist;
  rpc_params *_rpc_1_params;
  std::lognormal_distribution<double> _rpc_1_pre_dist;
  std::lognormal_distribution<double> _rpc_1_post_dist;
  rpc_params *_rpc_2_params;
  std::lognormal_distribution<double> _rpc_2_pre_dist;
  std::lognormal_distribution<double> _rpc_2_post_dist;

public:
  explicit service_0Handler(
      ClientPool<ThriftClient<service_1Client>> *service_1_client_pool,
      ClientPool<ThriftClient<service_2Client>> *service_2_client_pool,
      rpc_params *rpc_1_params, rpc_params *rpc_2_params,
      rpc_params *rpc_0_params, double scaler) {
    _service_1_client_pool = service_1_client_pool;
    _service_2_client_pool = service_2_client_pool;
    _scaler = scaler;
    auto seed =
        duration_cast<microseconds>(system_clock::now().time_since_epoch())
            .count();
    _gen = std::default_random_engine(seed);
    _rpc_0_params = rpc_0_params;
    double rpc_0_proc_time_mean = _rpc_0_params->proc_time_mean;
    if (rpc_0_proc_time_mean != 0) {
      double rpc_0_proc_time_std = _rpc_0_params->proc_time_std;
      double rpc_0_proc_m = log(
          rpc_0_proc_time_mean /
          sqrt(1 + pow(rpc_0_proc_time_std, 2) / pow(rpc_0_proc_time_mean, 2)));
      double rpc_0_proc_s = sqrt(
          log(1 + pow(rpc_0_proc_time_std, 2) / pow(rpc_0_proc_time_mean, 2)));
      _rpc_0_proc_dist =
          std::lognormal_distribution<double>(rpc_0_proc_m, rpc_0_proc_s);
    }
    _rpc_1_params = rpc_1_params;
    double rpc_1_pre_time_mean = _rpc_1_params->pre_time_mean;
    if (rpc_1_pre_time_mean != 0) {
      double rpc_1_pre_time_std = _rpc_1_params->pre_time_std;
      double rpc_1_pre_m = log(
          rpc_1_pre_time_mean /
          sqrt(1 + pow(rpc_1_pre_time_std, 2) / pow(rpc_1_pre_time_mean, 2)));
      double rpc_1_pre_s = sqrt(
          log(1 + pow(rpc_1_pre_time_std, 2) / pow(rpc_1_pre_time_mean, 2)));
      _rpc_1_pre_dist =
          std::lognormal_distribution<double>(rpc_1_pre_m, rpc_1_pre_s);
    }
    double rpc_1_post_time_mean = _rpc_1_params->post_time_mean;
    if (rpc_1_post_time_mean != 0) {
      double rpc_1_post_time_std = _rpc_1_params->post_time_std;
      double rpc_1_post_m = log(
          rpc_1_post_time_mean /
          sqrt(1 + pow(rpc_1_post_time_std, 2) / pow(rpc_1_post_time_mean, 2)));
      double rpc_1_post_s = sqrt(
          log(1 + pow(rpc_1_post_time_std, 2) / pow(rpc_1_post_time_mean, 2)));
      _rpc_1_post_dist =
          std::lognormal_distribution<double>(rpc_1_post_m, rpc_1_post_s);
    }
    _rpc_2_params = rpc_2_params;
    double rpc_2_pre_time_mean = _rpc_2_params->pre_time_mean;
    if (rpc_2_pre_time_mean != 0) {
      double rpc_2_pre_time_std = _rpc_2_params->pre_time_std;
      double rpc_2_pre_m = log(
          rpc_2_pre_time_mean /
          sqrt(1 + pow(rpc_2_pre_time_std, 2) / pow(rpc_2_pre_time_mean, 2)));
      double rpc_2_pre_s = sqrt(
          log(1 + pow(rpc_2_pre_time_std, 2) / pow(rpc_2_pre_time_mean, 2)));
      _rpc_2_pre_dist =
          std::lognormal_distribution<double>(rpc_2_pre_m, rpc_2_pre_s);
    }
    double rpc_2_post_time_mean = _rpc_2_params->post_time_mean;
    if (rpc_2_post_time_mean != 0) {
      double rpc_2_post_time_std = _rpc_2_params->post_time_std;
      double rpc_2_post_m = log(
          rpc_2_post_time_mean /
          sqrt(1 + pow(rpc_2_post_time_std, 2) / pow(rpc_2_post_time_mean, 2)));
      double rpc_2_post_s = sqrt(
          log(1 + pow(rpc_2_post_time_std, 2) / pow(rpc_2_post_time_mean, 2)));
      _rpc_2_post_dist =
          std::lognormal_distribution<double>(rpc_2_post_m, rpc_2_post_s);
    }
  }

  ~service_0Handler() override = default;

  void rpc_0(const std::map<std::string, std::string> &carrier) override {
    TextMapReader reader(carrier);
    auto parent_span = opentracing::Tracer::Global()->Extract(reader);
    auto span = opentracing::Tracer::Global()->StartSpan(
        "rpc_0_server", {opentracing::ChildOf(parent_span->get())});

    double proc_time;
    double proc_time_mean = _rpc_0_params->proc_time_mean;
    if (proc_time_mean != 0) {
      DistributionType distribution_type = _rpc_0_params->distribution_type;
      switch (distribution_type) {
      case constant:
        proc_time = proc_time_mean;
        break;
      case log_normal:
        proc_time = _rpc_0_proc_dist(_gen);
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
    vector<std::shared_future<void>> fuWaitVec[2];
    std::shared_future<void> fuVec[2];

    fuVec[0] = std::async(std::launch::async, [&]() {
      std::map<std::string, std::string> writer_text_map;
      TextMapWriter writer(writer_text_map);
      if (!fuWaitVec[0].empty()) {
        for (auto &i : fuWaitVec[0]) {
          i.wait();
        }
      }
      auto self_span = opentracing::Tracer::Global()->StartSpan(
          "rpc_2_client", {opentracing::ChildOf(&(span->context()))});
      opentracing::Tracer::Global()->Inject(self_span->context(), writer);
      auto service_2_client_wrapper = _service_2_client_pool->Pop();
      if (!service_2_client_wrapper) {
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
        se.message = "Failed to connect to service_2";
        throw se;
      } else {
        auto service_2_client = service_2_client_wrapper->GetClient();
        try {
          service_2_client->rpc_2(writer_text_map);
        } catch (TException &tx) {
          cout << "ERROR: " << tx.what() << endl;
          _service_2_client_pool->Push(service_2_client_wrapper);
        }
        _service_2_client_pool->Push(service_2_client_wrapper);
      }
      self_span->Finish();
    });

    fuVec[1] = std::async(std::launch::async, [&]() {
      std::map<std::string, std::string> writer_text_map;
      TextMapWriter writer(writer_text_map);
      if (!fuWaitVec[1].empty()) {
        for (auto &i : fuWaitVec[1]) {
          i.wait();
        }
      }
      auto self_span = opentracing::Tracer::Global()->StartSpan(
          "rpc_1_client", {opentracing::ChildOf(&(span->context()))});
      opentracing::Tracer::Global()->Inject(self_span->context(), writer);
      auto service_1_client_wrapper = _service_1_client_pool->Pop();
      if (!service_1_client_wrapper) {
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
        se.message = "Failed to connect to service_1";
        throw se;
      } else {
        auto service_1_client = service_1_client_wrapper->GetClient();
        try {
          service_1_client->rpc_1(writer_text_map);
        } catch (TException &tx) {
          cout << "ERROR: " << tx.what() << endl;
          _service_1_client_pool->Push(service_1_client_wrapper);
        }
        _service_1_client_pool->Push(service_1_client_wrapper);
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
  cout << "Starting the service_0 server..." << endl;
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
  SetUpTracer("config/jaeger-config.yml", "service_0");
  std::string service_1_addr = services_json["service_1"]["server_addr"];
  int service_1_port = services_json["service_1"]["server_port"];
  ClientPool<ThriftClient<service_1Client>> service_1_client_pool(
      "service_1", service_1_addr, service_1_port, 0, 1024, 5000);

  std::string service_2_addr = services_json["service_2"]["server_addr"];
  int service_2_port = services_json["service_2"]["server_port"];
  ClientPool<ThriftClient<service_2Client>> service_2_client_pool(
      "service_2", service_2_addr, service_2_port, 0, 1024, 5000);

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

  string tmp_rpc_0_distribution_type = rpcs_json["rpc_0"]["distribution_type"];
  DistributionType rpc_0_distribution_type;
  if (tmp_rpc_0_distribution_type == "log_normal")
    rpc_0_distribution_type = log_normal;
  else
    rpc_0_distribution_type = constant;
  rpc_params rpc_0_params = {
      rpc_0_distribution_type,
      rpcs_json["rpc_0"]["pre_time_mean"],
      rpcs_json["rpc_0"]["pre_time_std"],
      rpcs_json["rpc_0"]["post_time_mean"],
      rpcs_json["rpc_0"]["post_time_std"],
      rpcs_json["rpc_0"]["proc_time_mean"],
      rpcs_json["rpc_0"]["proc_time_std"],
  };

  double scaler = services_json["service_0"]["scaler"];
  int port = services_json["service_0"]["server_port"];
  int poolSize = 50;
  TThreadedServer server(
      stdcxx::make_shared<service_0Processor>(
          stdcxx::make_shared<service_0Handler>(
              &service_1_client_pool, &service_2_client_pool, &rpc_1_params,
              &rpc_2_params, &rpc_0_params, scaler)),
      stdcxx::make_shared<TServerSocket>("0.0.0.0", port),
      stdcxx::make_shared<TFramedTransportFactory>(),
      stdcxx::make_shared<TBinaryProtocolFactory>());
  startServer(server);
}
