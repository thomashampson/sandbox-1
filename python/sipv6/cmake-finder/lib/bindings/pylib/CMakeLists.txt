# Python bindings
include(SipQtTargetFunctions)

mtd_add_sip_module(
  MODULE_NAME _common
  TARGET_NAME _commonqt5
  SIP_SRC _common.sip
  PYQT_VERSION 5
  INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}
  LINK_LIBS widgets
)
