add_executable(
	service_0
	service_0.cpp
	${THRIFT_GEN_CPP_DIR}/service_0.cpp
	${THRIFT_GEN_CPP_DIR}/service_1.cpp
	${THRIFT_GEN_CPP_DIR}/service_2.cpp
	${THRIFT_GEN_CPP_DIR}/auto_microservices_types.cpp
)

target_include_directories(
	service_0 PRIVATE
	/usr/local/include/jaegertracing
)

target_link_libraries(
	service_0
	${THRIFT_LIB}
	jaegertracing
	${CMAKE_THREAD_LIBS_INIT}
	${Boost_LIBRARIES}
	nlohmann_json::nlohmann_json
	Boost::log
	Boost::log_setup
	OpenSSL::SSL
	/usr/local/lib/libjaegertracing.so
	/usr/local/lib/libthriftnb.so
)

install(TARGETS service_0 DESTINATION ./)
