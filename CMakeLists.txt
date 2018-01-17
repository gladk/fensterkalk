project(fensterkalk CXX)
cmake_minimum_required(VERSION 3.0)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cMake")
INCLUDE(GNUInstallDirs)


#===========================================================
# Options
OPTION(BUILD_DOC "Build documentation" OFF)
OPTION(ENABLE_TESTING "Enable testing" OFF)
#===========================================================

#C++14 support
set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
#===========================================================
FIND_PACKAGE(Boost COMPONENTS program_options filesystem system log log_setup REQUIRED)
INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS( "-DBOOST_LOG_DYN_LINK" )

FIND_PACKAGE(Eigen3 REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

FIND_PACKAGE(CGAL REQUIRED)
ADD_DEFINITIONS( "${CGAL_DEFINITIONS}")

FIND_PACKAGE(GMP REQUIRED)

IF (ENABLE_TESTING)
  INCLUDE_DIRECTORIES (/usr/src/gtest)
  ENABLE_TESTING()
ENDIF (ENABLE_TESTING)

#===========================================================
IF (BUILD_DOC)
  FIND_PACKAGE(Doxygen)
  IF (DOXYGEN_FOUND)
      # set input and output files
      SET(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
      SET(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

      # request to configure the file
      CONFIGURE_FILE(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
      MESSAGE("Doxygen build started")

      # note the option ALL which allows to build the docs together with the application
      ADD_CUSTOM_TARGET( doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen"
          VERBATIM )
  ELSE (DOXYGEN_FOUND)
    MESSAGE("Doxygen need to be installed to generate the doxygen documentation")
  ENDIF (DOXYGEN_FOUND)
ENDIF (BUILD_DOC)
#===========================================================
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#===========================================================
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/lib")
#===========================================================
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/bin)
ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/bin")
#===========================================================
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/gui)
ADD_SUBDIRECTORY("${CMAKE_SOURCE_DIR}/gui")
#===========================================================