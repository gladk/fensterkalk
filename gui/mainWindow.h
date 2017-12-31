#pragma once
#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPolygonF>
#include <QSettings>
#include <QStatusBar>
#include <QTextStream>
#include <QToolBar>

#include "constrGui.h"
#include "order.h"

#include <boost/shared_ptr.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

protected:
  void closeEvent(QCloseEvent *event);

  const double bord_left = 50;
  const double bord_right = 50;
  const double bord_top = 50;
  const double bord_bottom = 50;
  const double bord_scale = 0.9;
  const double zoom_speed = 1.2;

private slots:
  void newFile();
  void open();
  bool save();
  bool saveAs();
  void documentWasModified();

private:
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool maybeSave();
  void loadFile(const QString &fileName);
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  void resizeEvent(QResizeEvent *event = NULL);

  void badLoadFileDialog();

  QPlainTextEdit *textEdit;
  QString curFile;

  QMenu *fileMenu;
  QToolBar *fileToolBar;
  QAction *newAct;
  QAction *openAct;
  QAction *saveAct;
  QAction *saveAsAct;
  QAction *exitAct;

  QGraphicsView *view;
  QGraphicsScene *scene;
  boost::shared_ptr<QGraphicsPolygonItem> poly1;
  boost::shared_ptr<constrGui> constr1;
  boost::shared_ptr<order> orderCur;
};
