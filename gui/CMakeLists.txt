#===========================================================
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
ADD_EXECUTABLE(fensterkalkgui gui.cpp mainwindow.cpp )
FIND_PACKAGE(Qt5Widgets REQUIRED)

QT5_USE_MODULES(fensterkalkgui Widgets)
QT5_WRAP_UI(mainwindow.ui -o ui_mainwindow.h)

TARGET_LINK_LIBRARIES(fensterkalkgui ${Boost_LIBRARIES} fensterkalklib)
INSTALL(TARGETS fensterkalkgui DESTINATION ${CMAKE_INSTALL_BINDIR})
#===========================================================
