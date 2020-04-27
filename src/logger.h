#ifndef AUTO_MICROSERVICES_LOGGER_H_
#define AUTO_MICROSERVICES_LOGGER_H_

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <string.h>

namespace auto_microservices {
#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG(severity) \
    BOOST_LOG_TRIVIAL(severity) << "(" << __FILENAME__ << ":" \
    << __LINE__ << ":" << __FUNCTION__ << ") "

void init_logger() {
  boost::log::register_simple_formatter_factory
      <boost::log::trivial::severity_level, char>("Severity");
  boost::log::add_common_attributes();
  boost::log::add_console_log(
      std::cerr, boost::log::keywords::format =
          "[%TimeStamp%] <%Severity%>: %Message%");
  boost::log::core::get()->set_filter (
      boost::log::trivial::severity >= boost::log::trivial::warning
  );
}


} //namespace auto_microservices

#endif //#ifndef AUTO_MICROSERVICES_LOGGER_H_