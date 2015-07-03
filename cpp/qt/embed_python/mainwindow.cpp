#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow() {

  // In reality these would be far more encapulsated in further classes...
  editor = new CodeEditor;
  setCentralWidget(editor);
  m_interpreter = new PythonInterpreter;
  connect(editor, SIGNAL(goClicked()), this, SLOT(executeCurrentSource()));

  createActions();
  createMenus();
  createStatusBar();



  setCurrentFile("");
  setUnifiedTitleAndToolBarOnMac(true);
}
void MainWindow::closeEvent(QCloseEvent *) { delete m_interpreter; }

void MainWindow::about() {
  QMessageBox::about(this, tr("About Application"),
                     tr("The <b>Application</b> example demonstrates how to "
                        "use an embedded python interpreter"));
}

void MainWindow::appendToPythonPath() {
  QString path = "/mnt/data1/Scripts";
  m_interpreter->sysPathAppend(path);
}

void MainWindow::executeCurrentSource() {
  m_interpreter->execute(editor->sourceCode());
}

void MainWindow::createActions() {
  pathAppend = new QAction(tr("&Append To Path"), this);
  connect(pathAppend, SIGNAL(triggered()), this, SLOT(appendToPythonPath()));

  execScript = new QAction(tr("Execute"), this);
  connect(execScript, SIGNAL(triggered()), this, SLOT(executeCurrentSource()));

  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  aboutAct = new QAction(tr("&About"), this);
  aboutAct->setStatusTip(tr("Show the application's About box"));
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAct = new QAction(tr("About &Qt"), this);
  aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
  connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  pythonMenu = menuBar()->addMenu(tr("&Python"));
  pythonMenu->addAction(pathAppend);
  pythonMenu->addAction(execScript);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);
}
void MainWindow::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::setCurrentFile(const QString &fileName)
{
  curFile = fileName;
  setWindowFilePath(fileName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
  return QFileInfo(fullFileName).fileName();
}
