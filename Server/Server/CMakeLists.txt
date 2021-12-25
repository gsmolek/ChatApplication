cmake_minimum_required (VERSION 3.8)

project(main)

if(WIN32)

	set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "C:/Program Files/MySQL/Connector C++ 8.0")
	set(FULL_PATH_TO_BOOST_DIR "C:/Program Files/Boost/boost_1_77_0")
	set(INCLUDE /include/)
	FILE(GLOB SRC */*.cpp)
	#FIND_PACKAGE( Boost 1.77 COMPONENTS program_options REQUIRED )
	#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
	INCLUDE_DIRECTORIES( ${FULL_PATH_TO_BOOST_DIR} )
	include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
	include_directories(${INCLUDE})
	link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14)
	set(CMAKE_CXX_STANDARD 17)

	add_subdirectory(lib/sha256)
	add_subdirectory(lib/rsa)

	#add_executable(main ${SRC} "src/sha256.cpp" "include/sha256.h" "src/rsa.cpp" "include/rsa.h")
	add_executable(main ${SRC} "src/rsa.cpp")

	TARGET_LINK_LIBRARIES(main LINK_PUBLIC ${Boost_LIBRARIES} wsock32 ws2_32 mysqlcppconn.lib mysqlcppconn-static.lib sha256 rsa)
	#target_link_libraries(main wsock32 ws2_32)
	target_include_directories(${PROJECT_NAME} PUBLIC include/)
	#target_link_libraries(main mysqlcppconn.lib)
	#target_link_libraries(main mysqlcppconn-static.lib)
	include_directories(${FULL_PATH_TO_BOOST_DIR})
elseif(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
elseif(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
endif()