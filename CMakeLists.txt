CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(useragent)

#FIND_PACKAGE(dataparse-extlib REQUIRED)
FIND_PACKAGE(utils-extlib REQUIRED)
FIND_PACKAGE(regex-extlib REQUIRED)

ADD_SUBDIRECTORY(src)
INSTALL(PROGRAMS tools/restart.sh DESTINATION useragent/tools)
INSTALL(FILES useragent.conf DESTINATION useragent/conf)
