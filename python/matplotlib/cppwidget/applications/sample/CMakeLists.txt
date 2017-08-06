# Define targets for sample application

function (mtd_add_qt_executable )
  set (options)
  set (oneValueArgs QT_VERSION)
  set (multiValueArgs SRC UI )
  cmake_parse_arguments (_ "${options}" "${oneValueArgs}"
                         "${multiValueArgs}")

endfunction()

set (APP_SRCS
  src/main.cpp
)

set (UI_FILES
  src/mainwindow.ui
)

set (MOC_HEADERS
  src/MainWindow.h
)

mtd_add_qt_executable (sample QT_VERSION 4 SRC ${APP_SRCS} UI ${UI_FILES} MOC ${MOC_HEADERS})
