"""Attempts to import and create an InfoTestWidget
"""
from PyQt5.QtWidgets import QApplication

from _commonqt5 import InfoWidget

qapp = QApplication(['test_infowidget'])
window = InfoWidget()
assert window is not None
