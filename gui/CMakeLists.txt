#===========================================================
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
FIND_PACKAGE(Qt5Widgets REQUIRED)

QT5_WRAP_UI(UIS_HDRS mainwindow.ui)

ADD_EXECUTABLE(fensterkalkgui main.cpp mainwindow.cpp ${UIS_HDRS})
QT5_USE_MODULES(fensterkalkgui Widgets)

TARGET_LINK_LIBRARIES(fensterkalkgui ${Boost_LIBRARIES} fensterkalklib)
INSTALL(TARGETS fensterkalkgui DESTINATION ${CMAKE_INSTALL_BINDIR})
#===========================================================
