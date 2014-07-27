#include "constrGui.h"
#include "mainWindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
  //Q_INIT_RESOURCE(application);
  QApplication app( argc, argv );
  /*
  QGraphicsView view;
  
  QGraphicsScene* scene = new QGraphicsScene(0,0,300,300,&view);
  scene->setBackgroundBrush(Qt::white);
  
  
  SuperItem* super = new SuperItem;
  scene->addItem(super);
  
  view.setScene(scene);
  view.show();
  */
  app.setOrganizationName("FesnterKalk");
  app.setApplicationName("FesnterKalk");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
