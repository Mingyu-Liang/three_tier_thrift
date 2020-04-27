/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef service_9_H
#define service_9_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "auto_microservices_types.h"

namespace auto_microservices {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class service_9If {
 public:
  virtual ~service_9If() {}
  virtual void rpc_9(const std::map<std::string, std::string> & carrier) = 0;
};

class service_9IfFactory {
 public:
  typedef service_9If Handler;

  virtual ~service_9IfFactory() {}

  virtual service_9If* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(service_9If* /* handler */) = 0;
};

class service_9IfSingletonFactory : virtual public service_9IfFactory {
 public:
  service_9IfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<service_9If>& iface) : iface_(iface) {}
  virtual ~service_9IfSingletonFactory() {}

  virtual service_9If* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(service_9If* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<service_9If> iface_;
};

class service_9Null : virtual public service_9If {
 public:
  virtual ~service_9Null() {}
  void rpc_9(const std::map<std::string, std::string> & /* carrier */) {
    return;
  }
};

typedef struct _service_9_rpc_9_args__isset {
  _service_9_rpc_9_args__isset() : carrier(false) {}
  bool carrier :1;
} _service_9_rpc_9_args__isset;

class service_9_rpc_9_args {
 public:

  service_9_rpc_9_args(const service_9_rpc_9_args&);
  service_9_rpc_9_args& operator=(const service_9_rpc_9_args&);
  service_9_rpc_9_args() {
  }

  virtual ~service_9_rpc_9_args() throw();
  std::map<std::string, std::string>  carrier;

  _service_9_rpc_9_args__isset __isset;

  void __set_carrier(const std::map<std::string, std::string> & val);

  bool operator == (const service_9_rpc_9_args & rhs) const
  {
    if (!(carrier == rhs.carrier))
      return false;
    return true;
  }
  bool operator != (const service_9_rpc_9_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const service_9_rpc_9_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class service_9_rpc_9_pargs {
 public:


  virtual ~service_9_rpc_9_pargs() throw();
  const std::map<std::string, std::string> * carrier;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _service_9_rpc_9_result__isset {
  _service_9_rpc_9_result__isset() : se(false) {}
  bool se :1;
} _service_9_rpc_9_result__isset;

class service_9_rpc_9_result {
 public:

  service_9_rpc_9_result(const service_9_rpc_9_result&);
  service_9_rpc_9_result& operator=(const service_9_rpc_9_result&);
  service_9_rpc_9_result() {
  }

  virtual ~service_9_rpc_9_result() throw();
  ServiceException se;

  _service_9_rpc_9_result__isset __isset;

  void __set_se(const ServiceException& val);

  bool operator == (const service_9_rpc_9_result & rhs) const
  {
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const service_9_rpc_9_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const service_9_rpc_9_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _service_9_rpc_9_presult__isset {
  _service_9_rpc_9_presult__isset() : se(false) {}
  bool se :1;
} _service_9_rpc_9_presult__isset;

class service_9_rpc_9_presult {
 public:


  virtual ~service_9_rpc_9_presult() throw();
  ServiceException se;

  _service_9_rpc_9_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class service_9Client : virtual public service_9If {
 public:
  service_9Client(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  service_9Client(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void rpc_9(const std::map<std::string, std::string> & carrier);
  void send_rpc_9(const std::map<std::string, std::string> & carrier);
  void recv_rpc_9();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class service_9Processor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<service_9If> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (service_9Processor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_rpc_9(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  service_9Processor(::apache::thrift::stdcxx::shared_ptr<service_9If> iface) :
    iface_(iface) {
    processMap_["rpc_9"] = &service_9Processor::process_rpc_9;
  }

  virtual ~service_9Processor() {}
};

class service_9ProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  service_9ProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< service_9IfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< service_9IfFactory > handlerFactory_;
};

class service_9Multiface : virtual public service_9If {
 public:
  service_9Multiface(std::vector<apache::thrift::stdcxx::shared_ptr<service_9If> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~service_9Multiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<service_9If> > ifaces_;
  service_9Multiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<service_9If> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void rpc_9(const std::map<std::string, std::string> & carrier) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->rpc_9(carrier);
    }
    ifaces_[i]->rpc_9(carrier);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class service_9ConcurrentClient : virtual public service_9If {
 public:
  service_9ConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  service_9ConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void rpc_9(const std::map<std::string, std::string> & carrier);
  int32_t send_rpc_9(const std::map<std::string, std::string> & carrier);
  void recv_rpc_9(const int32_t seqid);
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
