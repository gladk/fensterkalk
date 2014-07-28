#pragma once
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QSettings>
#include <QTextStream>
#include <QApplication>
#include <QStatusBar>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QPolygonF>

#include <boost/shared_ptr.hpp>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    
    const double bord_left=50;
    const double bord_right=50;
    const double bord_top=50;
    const double bord_bottom=50;
    const double bord_scale=0.9;
    const double zoom_speed=1.2;

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
    
    void resizeEvent ( QResizeEvent * event=NULL);
    void wheelEvent  (QWheelEvent* event);

    QPlainTextEdit *textEdit;
    QString curFile;

    QMenu *fileMenu;
    QToolBar *fileToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsRectItem* rect1;
    boost::shared_ptr<QGraphicsPolygonItem> poly1;
};
