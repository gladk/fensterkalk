project(fensterkalk CXX)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cMake")
INCLUDE(GNUInstallDirs)

#C+11 support
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
#===========================================================
# Add possibility to use local boost installation (e.g. -DLocalBoost=1.46.1)
FIND_PACKAGE(Boost ${LocalBoost} COMPONENTS program_options filesystem system regex iostreams log log_setup thread REQUIRED)
INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS( "-DBOOST_LOG_DYN_LINK" )

FIND_PACKAGE(Eigen3 REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

FIND_PACKAGE(CGAL REQUIRED)
ADD_DEFINITIONS( "${CGAL_DEFINITIONS}")

FIND_PACKAGE(GMP REQUIRED)

#===========================================================
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#===========================================================
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/lib")
#===========================================================

#===========================================================
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/bin)
ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/bin")
#===========================================================

#===========================================================
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/gui)
ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/gui")
#===========================================================


