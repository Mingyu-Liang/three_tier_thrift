#ifndef AUTO_MICROSERVICES_SRC_GENERICCLIENT_H_
#define AUTO_MICROSERVICES_SRC_GENERICCLIENT_H_

#include <string>

namespace auto_microservices {

class GenericClient{
 public:
  virtual ~GenericClient() = default;
  virtual void Connect() = 0;
  virtual void KeepAlive() = 0;
  virtual void KeepAlive(int) = 0;
  virtual void Disconnect() = 0;
  virtual bool IsConnected() = 0;

 protected:
  std::string _addr;
  int _port;
};

} // namespace auto_microservices

#endif //AUTO_MICROSERVICES_SRC_GENERICCLIENT_H_
