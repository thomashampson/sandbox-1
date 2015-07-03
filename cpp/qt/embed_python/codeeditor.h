#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QWidget>
#include <code.h>


namespace Ui {
class CodeEditor;
}

class CodeEditor : public QWidget
{
  Q_OBJECT
  
public:
  explicit CodeEditor(QWidget *parent = 0);
  ~CodeEditor();

  Code sourceCode() const;

signals:
  void goClicked();
  
private:
  Ui::CodeEditor *ui;
};

#endif // CODEEDITOR_H
