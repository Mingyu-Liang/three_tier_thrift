/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef service_0_H
#define service_0_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "auto_microservices_types.h"

namespace auto_microservices {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class service_0If {
 public:
  virtual ~service_0If() {}
  virtual void rpc_0(const std::map<std::string, std::string> & carrier) = 0;
};

class service_0IfFactory {
 public:
  typedef service_0If Handler;

  virtual ~service_0IfFactory() {}

  virtual service_0If* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(service_0If* /* handler */) = 0;
};

class service_0IfSingletonFactory : virtual public service_0IfFactory {
 public:
  service_0IfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<service_0If>& iface) : iface_(iface) {}
  virtual ~service_0IfSingletonFactory() {}

  virtual service_0If* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(service_0If* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<service_0If> iface_;
};

class service_0Null : virtual public service_0If {
 public:
  virtual ~service_0Null() {}
  void rpc_0(const std::map<std::string, std::string> & /* carrier */) {
    return;
  }
};

typedef struct _service_0_rpc_0_args__isset {
  _service_0_rpc_0_args__isset() : carrier(false) {}
  bool carrier :1;
} _service_0_rpc_0_args__isset;

class service_0_rpc_0_args {
 public:

  service_0_rpc_0_args(const service_0_rpc_0_args&);
  service_0_rpc_0_args& operator=(const service_0_rpc_0_args&);
  service_0_rpc_0_args() {
  }

  virtual ~service_0_rpc_0_args() throw();
  std::map<std::string, std::string>  carrier;

  _service_0_rpc_0_args__isset __isset;

  void __set_carrier(const std::map<std::string, std::string> & val);

  bool operator == (const service_0_rpc_0_args & rhs) const
  {
    if (!(carrier == rhs.carrier))
      return false;
    return true;
  }
  bool operator != (const service_0_rpc_0_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const service_0_rpc_0_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class service_0_rpc_0_pargs {
 public:


  virtual ~service_0_rpc_0_pargs() throw();
  const std::map<std::string, std::string> * carrier;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _service_0_rpc_0_result__isset {
  _service_0_rpc_0_result__isset() : se(false) {}
  bool se :1;
} _service_0_rpc_0_result__isset;

class service_0_rpc_0_result {
 public:

  service_0_rpc_0_result(const service_0_rpc_0_result&);
  service_0_rpc_0_result& operator=(const service_0_rpc_0_result&);
  service_0_rpc_0_result() {
  }

  virtual ~service_0_rpc_0_result() throw();
  ServiceException se;

  _service_0_rpc_0_result__isset __isset;

  void __set_se(const ServiceException& val);

  bool operator == (const service_0_rpc_0_result & rhs) const
  {
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const service_0_rpc_0_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const service_0_rpc_0_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _service_0_rpc_0_presult__isset {
  _service_0_rpc_0_presult__isset() : se(false) {}
  bool se :1;
} _service_0_rpc_0_presult__isset;

class service_0_rpc_0_presult {
 public:


  virtual ~service_0_rpc_0_presult() throw();
  ServiceException se;

  _service_0_rpc_0_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class service_0Client : virtual public service_0If {
 public:
  service_0Client(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  service_0Client(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void rpc_0(const std::map<std::string, std::string> & carrier);
  void send_rpc_0(const std::map<std::string, std::string> & carrier);
  void recv_rpc_0();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class service_0Processor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<service_0If> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (service_0Processor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_rpc_0(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  service_0Processor(::apache::thrift::stdcxx::shared_ptr<service_0If> iface) :
    iface_(iface) {
    processMap_["rpc_0"] = &service_0Processor::process_rpc_0;
  }

  virtual ~service_0Processor() {}
};

class service_0ProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  service_0ProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< service_0IfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< service_0IfFactory > handlerFactory_;
};

class service_0Multiface : virtual public service_0If {
 public:
  service_0Multiface(std::vector<apache::thrift::stdcxx::shared_ptr<service_0If> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~service_0Multiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<service_0If> > ifaces_;
  service_0Multiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<service_0If> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void rpc_0(const std::map<std::string, std::string> & carrier) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->rpc_0(carrier);
    }
    ifaces_[i]->rpc_0(carrier);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class service_0ConcurrentClient : virtual public service_0If {
 public:
  service_0ConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  service_0ConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void rpc_0(const std::map<std::string, std::string> & carrier);
  int32_t send_rpc_0(const std::map<std::string, std::string> & carrier);
  void recv_rpc_0(const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

} // namespace

#endif
