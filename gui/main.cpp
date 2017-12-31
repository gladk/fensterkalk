#include "constrGui.h"
#include "mainWindow.h"
#include <QApplication>

int main(int argc, char **argv) {
  // Q_INIT_RESOURCE(application);
  QApplication app(argc, argv);
  app.setOrganizationName("FesnterKalk");
  app.setApplicationName("FesnterKalk");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
