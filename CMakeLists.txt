CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(OneWeekendRT)

SET(PROJECT_HOME_DIR ${CMAKE_HOME_DIRECTORY})
SET(PROJECT_INSTALL_DIR ${CMAKE_HOME_DIRECTORY}/bin)
SET(CMAKE_INSTALL_PREFIX ${PROJECT_INSTALL_DIR})

SET(PROJECT_OUTPUT_DIR ${PROJECT_INSTALL_DIR})
IF( MSVC )
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR})
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR})
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR})
ENDIF( MSVC )

OPTION(OW_USE_DOUBLE ON)
if(OW_USE_DOUBLE)
ADD_DEFINITIONS(-DOW_USE_DOUBLE)
MESSAGE(STATUS "use double as real type.")
endif()

INCLUDE_DIRECTORIES(3rd/tbb/include)

ADD_SUBDIRECTORY(3rd/tbb)
ADD_SUBDIRECTORY(OneWeekendRT)
