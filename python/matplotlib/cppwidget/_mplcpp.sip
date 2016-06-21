%Module _mplcpp

%Import QtGui/QtGuimod.sip

class MplPlot : QWidget {
%TypeHeaderCode
#include "MplPlot.h"
%End
};
