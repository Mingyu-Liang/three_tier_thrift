/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef service_2_H
#define service_2_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "auto_microservices_types.h"

namespace auto_microservices {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class service_2If {
 public:
  virtual ~service_2If() {}
  virtual void rpc_2(const std::map<std::string, std::string> & carrier) = 0;
};

class service_2IfFactory {
 public:
  typedef service_2If Handler;

  virtual ~service_2IfFactory() {}

  virtual service_2If* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(service_2If* /* handler */) = 0;
};

class service_2IfSingletonFactory : virtual public service_2IfFactory {
 public:
  service_2IfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<service_2If>& iface) : iface_(iface) {}
  virtual ~service_2IfSingletonFactory() {}

  virtual service_2If* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(service_2If* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<service_2If> iface_;
};

class service_2Null : virtual public service_2If {
 public:
  virtual ~service_2Null() {}
  void rpc_2(const std::map<std::string, std::string> & /* carrier */) {
    return;
  }
};

typedef struct _service_2_rpc_2_args__isset {
  _service_2_rpc_2_args__isset() : carrier(false) {}
  bool carrier :1;
} _service_2_rpc_2_args__isset;

class service_2_rpc_2_args {
 public:

  service_2_rpc_2_args(const service_2_rpc_2_args&);
  service_2_rpc_2_args& operator=(const service_2_rpc_2_args&);
  service_2_rpc_2_args() {
  }

  virtual ~service_2_rpc_2_args() throw();
  std::map<std::string, std::string>  carrier;

  _service_2_rpc_2_args__isset __isset;

  void __set_carrier(const std::map<std::string, std::string> & val);

  bool operator == (const service_2_rpc_2_args & rhs) const
  {
    if (!(carrier == rhs.carrier))
      return false;
    return true;
  }
  bool operator != (const service_2_rpc_2_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const service_2_rpc_2_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class service_2_rpc_2_pargs {
 public:


  virtual ~service_2_rpc_2_pargs() throw();
  const std::map<std::string, std::string> * carrier;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _service_2_rpc_2_result__isset {
  _service_2_rpc_2_result__isset() : se(false) {}
  bool se :1;
} _service_2_rpc_2_result__isset;

class service_2_rpc_2_result {
 public:

  service_2_rpc_2_result(const service_2_rpc_2_result&);
  service_2_rpc_2_result& operator=(const service_2_rpc_2_result&);
  service_2_rpc_2_result() {
  }

  virtual ~service_2_rpc_2_result() throw();
  ServiceException se;

  _service_2_rpc_2_result__isset __isset;

  void __set_se(const ServiceException& val);

  bool operator == (const service_2_rpc_2_result & rhs) const
  {
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const service_2_rpc_2_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const service_2_rpc_2_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _service_2_rpc_2_presult__isset {
  _service_2_rpc_2_presult__isset() : se(false) {}
  bool se :1;
} _service_2_rpc_2_presult__isset;

class service_2_rpc_2_presult {
 public:


  virtual ~service_2_rpc_2_presult() throw();
  ServiceException se;

  _service_2_rpc_2_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class service_2Client : virtual public service_2If {
 public:
  service_2Client(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  service_2Client(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void rpc_2(const std::map<std::string, std::string> & carrier);
  void send_rpc_2(const std::map<std::string, std::string> & carrier);
  void recv_rpc_2();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class service_2Processor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<service_2If> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (service_2Processor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_rpc_2(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  service_2Processor(::apache::thrift::stdcxx::shared_ptr<service_2If> iface) :
    iface_(iface) {
    processMap_["rpc_2"] = &service_2Processor::process_rpc_2;
  }

  virtual ~service_2Processor() {}
};

class service_2ProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  service_2ProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< service_2IfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< service_2IfFactory > handlerFactory_;
};

class service_2Multiface : virtual public service_2If {
 public:
  service_2Multiface(std::vector<apache::thrift::stdcxx::shared_ptr<service_2If> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~service_2Multiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<service_2If> > ifaces_;
  service_2Multiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<service_2If> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void rpc_2(const std::map<std::string, std::string> & carrier) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->rpc_2(carrier);
    }
    ifaces_[i]->rpc_2(carrier);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class service_2ConcurrentClient : virtual public service_2If {
 public:
  service_2ConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  service_2ConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void rpc_2(const std::map<std::string, std::string> & carrier);
  int32_t send_rpc_2(const std::map<std::string, std::string> & carrier);
  void recv_rpc_2(const int32_t seqid);
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
