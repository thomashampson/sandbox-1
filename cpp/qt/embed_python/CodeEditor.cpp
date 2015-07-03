#include "CodeEditor.h"
#include <QVBoxLayout>

CodeEditor::CodeEditor(QWidget *parent) : QWidget(parent), m_editor(new QTabWidget(this)) {
  this->setLayout(new QVBoxLayout);
  layout()->addWidget(m_editor);
  this->setFocusProxy(m_editor);
}
