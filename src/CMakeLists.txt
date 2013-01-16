cmake_minimum_required(VERSION 2.8)

#add_definitions("-g -O2 -Wall -Wextra")
add_definitions("-g -O2 -Wall")
add_library(useragent comm_struct.cpp setting.cpp useragent.cpp)

add_executable(example example.cpp)
target_link_libraries(example useragent gflags glog config++ re2 pthread rt)


ADD_CUSTOM_COMMAND(TARGET useragent
	PRE_BUILD
	COMMENT "[ astyle code ]"
	COMMAND [ -z `which astyle 2>/dev/null` -o ! -f ~/.astylerc ] ||
	astyle src/*.cpp src/*.h 2>/dev/null 1>&2
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	#VERBATIM
	)

ADD_CUSTOM_COMMAND(TARGET useragent
	POST_BUILD
	COMMENT "[ generate doc ]"
	COMMAND [ -z `which doxygen 2>/dev/null` ] || doxygen 2>/dev/null 1>/dev/null
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	#VERBATIM
	)
