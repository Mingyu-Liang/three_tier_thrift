add_executable(
	service_3
	service_3.cpp
	${THRIFT_GEN_CPP_DIR}/service_3.cpp
	${THRIFT_GEN_CPP_DIR}/auto_microservices_types.cpp
)

target_include_directories(
	service_3 PRIVATE
	/usr/local/include/jaegertracing
)

target_link_libraries(
	service_3
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

install(TARGETS service_3 DESTINATION ./)
