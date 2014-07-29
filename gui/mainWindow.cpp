#include "mainWindow.h"
#include "loadjson.h"


MainWindow::MainWindow()
{ 
    view = new QGraphicsView(this);
    view->setObjectName(QString::fromUtf8("graphicsView"));
    
    scene = new QGraphicsScene();
    view->setScene(scene);
    
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();
    resizeEvent();
    
    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);
    orderCur = boost::shared_ptr<order> (new order());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        //textEdit->clear();
        setCurrentFile("");
    }
}

void MainWindow::open() {
  QString fileName = QFileDialog::getOpenFileName(this);
  
  if (!fileName.isEmpty()) {
    if (not(loadJson(fileName.toUtf8().constData(), orderCur))) {
      badLoadFileDialog();
      return;
    }
  }
  
  if (not(orderCur->calculate())) {
      badLoadFileDialog();
      return;
  } else {
      if (constr1.get()) scene->removeItem(constr1.get());
      constr1 = boost::shared_ptr<constrGui> (new constrGui (orderCur->constrGet(0)));
      scene->addItem(constr1.get());
      resizeEvent();
  }
}

void MainWindow::badLoadFileDialog() {
  QMessageBox::StandardButton ret;
  ret = QMessageBox::warning(this, tr("Application"),
               tr("Loaded construction is wrong!"),
               QMessageBox::Ok);
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.exec();
    QStringList files = dialog.selectedFiles();

    if (files.isEmpty())
        return false;

    return saveFile(files.at(0));
}

void MainWindow::documentWasModified()
{
    //setWindowModified(textEdit->document()->isModified());
}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon("./images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon("./images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon("./images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addSeparator();
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings("QtProject", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool MainWindow::maybeSave()
{
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    //out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::resizeEvent ( QResizeEvent * event)
{   
    view->setGeometry(QRect(QPoint(bord_left, bord_top), 
                            QPoint(width()-bord_right, height()-bord_bottom)));
    view->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    view->scale(bord_scale,bord_scale);
    
}
