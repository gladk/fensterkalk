#===========================================================
ADD_EXECUTABLE(fensterkalkbin main.cpp log.cpp config.cpp loadjson.cpp)
TARGET_LINK_LIBRARIES(fensterkalkbin ${Boost_LIBRARIES} ${CGAL_LIBRARIES} fensterkalklib)
INSTALL(TARGETS fensterkalkbin DESTINATION ${CMAKE_INSTALL_BINDIR})
#===========================================================
#===========================================================
ADD_EXECUTABLE(writejsjon writejson.cpp)
TARGET_LINK_LIBRARIES(writejsjon ${Boost_LIBRARIES} ${CGAL_LIBRARIES} fensterkalklib)
INSTALL(TARGETS writejsjon DESTINATION ${CMAKE_INSTALL_BINDIR})
#===========================================================
