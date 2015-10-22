#include "codeeditor.h"
#include "ui_codeeditor.h"

#include <QPlainTextEdit>

/**
 *
 * @param parent
 */
CodeEditor::CodeEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeEditor)
{
  ui->setupUi(this);

  ui->tabWidget->addTab(new QPlainTextEdit, "Tab 1");
  ui->tabWidget->addTab(new QPlainTextEdit, "Tab 2");
  
  ui->tabWidget->setCurrentIndex(0);
  
  connect(ui->execButton, SIGNAL(clicked()), this, SIGNAL(goClicked()));
}

/**
 *
 */
CodeEditor::~CodeEditor()
{
  delete ui;
}

/**
 *
 * @return A Code object with the text from the active tab
 */
Code CodeEditor::sourceCode() const
{
  QWidget* widget = ui->tabWidget->currentWidget();
  return Code(QString(qobject_cast<QPlainTextEdit*>(widget)->toPlainText()));
}
