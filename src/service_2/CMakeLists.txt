add_executable(
	service_2
	service_2.cpp
	${THRIFT_GEN_CPP_DIR}/service_2.cpp
	${THRIFT_GEN_CPP_DIR}/auto_microservices_types.cpp
)

target_include_directories(
	service_2 PRIVATE
	/usr/local/include/jaegertracing
)

target_link_libraries(
	service_2
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

install(TARGETS service_2 DESTINATION ./)
