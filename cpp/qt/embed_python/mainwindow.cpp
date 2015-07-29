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

void MainWindow::importMatplotlib() {
  m_interpreter->importMatplotlib();
}

void MainWindow::executeCurrentSource() {
    m_interpreter->execute(editor->sourceCode());
}

void MainWindow::abort() {
  m_interpreter->abort();
}

void MainWindow::createActions() {
  importMPL = new QAction(tr("&Import matplotlib"), this);
  connect(importMPL, SIGNAL(triggered()), this, SLOT(importMatplotlib()));

  execScript = new QAction(tr("Execute"), this);
  connect(execScript, SIGNAL(triggered()), this, SLOT(executeCurrentSource()));

  abortScript = new QAction(tr("Abort"), this);
  connect(abortScript, SIGNAL(triggered()), this, SLOT(abort()));

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
  pythonMenu->addAction(importMPL);
  pythonMenu->addAction(execScript);
  pythonMenu->addAction(abortScript);

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
