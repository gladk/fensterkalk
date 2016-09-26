#===========================================================
ADD_LIBRARY(fensterkalklib SHARED node.cpp beam.cpp frame.cpp constr.cpp order.cpp loadjson.cpp)

TARGET_LINK_LIBRARIES(fensterkalklib ${Boost_LIBRARIES} ${CGAL_LIBRARIES} ${GMP_LIBRARIES})
INSTALL(TARGETS fensterkalklib DESTINATION ${CMAKE_INSTALL_LIBDIR})
#===========================================================
INSTALL (FILES node.h beam.h frame.h constr.h order.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fensterkalk)
