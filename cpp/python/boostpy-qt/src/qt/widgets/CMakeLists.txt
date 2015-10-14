################################################################################
# Widgets library
################################################################################
set( MOC_HDRS
  mainwindow.h
)
set( SRCS
  mainwindow.cpp
)

# Generate moc files
qt4_wrap_cpp ( MOCCED_CPP ${MOC_HDRS} )
# Add resources
qt4_add_resources ( RES_FILE_CPP widgets.qrc )

################################################################################
# Targets
################################################################################
add_library( widgets ${SRCS} ${MOCCED_CPP} ${RES_FILE_CPP} )
target_link_libraries( widgets LINK_PRIVATE ${QT_LIBRARIES} )
