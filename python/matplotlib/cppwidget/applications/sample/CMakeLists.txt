# Define targets for sample application
set (APP_SRCS
  src/main.cpp
  src/MainWindow.cpp
)

set (UI_FILES
  src/mainwindow.ui
)

set (MOC_HEADERS
  src/MainWindow.h
)

mtd_add_qt4_and_qt5_executable (TARGET_NAME sample SRC ${APP_SRCS} UI ${UI_FILES}
                                MOC ${MOC_HEADERS} INCLUDE_DIRS
                                LINK_LIBRARIES ${PYTHON_LIBRARIES}
                                MTD_QT_LINK_LIBRARIES mplcpp)
