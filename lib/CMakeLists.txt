#===========================================================
ADD_LIBRARY(fensterkalklib SHARED node.cpp frame.cpp constr.cpp order.cpp)
TARGET_LINK_LIBRARIES(fensterkalklib ${Boost_LIBRARIES} ${CGAL_LIBRARIES} ${GMP_LIBRARIES})
INSTALL(TARGETS fensterkalklib DESTINATION ${CMAKE_INSTALL_LIBDIR})
#===========================================================
