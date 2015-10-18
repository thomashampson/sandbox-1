//------------------------------------------------------------------------------
// Python exports for the widgets Qt library
//------------------------------------------------------------------------------
%Module pywidgets

%Import QtCore/QtCoremod.sip
%Import QtGui/QtGuimod.sip

class MainWindow : QMainWindow
{
%TypeHeaderCode
#include "widgets/mainwindow.h"
%End
public:
 MainWindow();
};
