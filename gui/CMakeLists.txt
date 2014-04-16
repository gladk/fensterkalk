#===========================================================
SET(CMAKE_AUTOMOC ON)
#SET(CMAKE_INCLUDE_CURRENT_DIR ON)
ADD_EXECUTABLE(fensterkalkgui gui.cpp)
FIND_PACKAGE(Qt5Widgets REQUIRED)

QT5_USE_MODULES(fensterkalkgui Widgets)


TARGET_LINK_LIBRARIES(fensterkalkgui ${Boost_LIBRARIES} fensterkalklib)
INSTALL(TARGETS fensterkalkgui DESTINATION ${CMAKE_INSTALL_BINDIR})
#===========================================================
