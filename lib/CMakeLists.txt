#===========================================================
SET(LIB_SRC src/node.cpp
            src/beam.cpp
            src/frame.cpp
            src/constr.cpp
            src/order.cpp
            src/loadjson.cpp
)

SET(LIB_HDR public/node.h
            public/beam.h
            public/frame.h
            public/constr.h
            public/order.h
            public/loadjson.h
)

ADD_LIBRARY(fensterkalklib SHARED ${LIB_SRC})
TARGET_LINK_LIBRARIES(fensterkalklib ${Boost_LIBRARIES} ${CGAL_LIBRARIES} ${GMP_LIBRARIES})

#===========================================================

INSTALL(TARGETS fensterkalklib DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL (FILES ${LIB_HDR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fensterkalk)
