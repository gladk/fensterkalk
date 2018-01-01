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
TARGET_LINK_LIBRARIES(fensterkalklib ${Boost_LIBRARIES} ${CGAL_LIBRARIES} ${GMP_LIBRARIES})

#===========================================================

INSTALL(TARGETS fensterkalklib DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL (FILES ${LIB_HDR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fensterkalk)
