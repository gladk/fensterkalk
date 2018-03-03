#===========================================================
SET(LIB_SRC node.cpp
            beam.cpp
            frame.cpp
            constr.cpp
            order.cpp
            loadjson.cpp
)

SET(LIB_HDR node.h
            beam.h
            frame.h
            constr.h
            order.h
            loadjson.h
)

ADD_LIBRARY(fensterkalklib SHARED ${LIB_SRC})
TARGET_LINK_LIBRARIES(fensterkalklib
  PUBLIC
    ${Boost_LIBRARIES}
    ${CGAL_LIBRARIES}
  PRIVATE
    ${GMP_LIBRARIES}
)
TARGET_INCLUDE_DIRECTORIES(fensterkalklib
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/fensterkalk>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
#===========================================================

INSTALL(TARGETS fensterkalklib
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

INSTALL (FILES ${LIB_HDR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fensterkalk)

#===========================================================

IF (ENABLE_TESTING)
    ADD_EXECUTABLE(testlib
            /usr/src/gtest/src/gtest-all.cc
            /usr/src/googletest/googletest/src/gtest_main.cc
            test.cpp)
    TARGET_LINK_LIBRARIES(testlib
      fensterkalklib
      ${Boost_LIBRARIES}
      ${CGAL_LIBRARIES}
      ${GMP_LIBRARIES}
    )
    ADD_TEST(testlib testlib)
ENDIF (ENABLE_TESTING)
