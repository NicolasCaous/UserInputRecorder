# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'dialog.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_input_capture_dialog(object):
    def setupUi(self, input_capture_dialog):
        input_capture_dialog.setObjectName(_fromUtf8("input_capture_dialog"))
        input_capture_dialog.resize(200, 100)
        input_capture_dialog.setMinimumSize(QtCore.QSize(200, 100))
        input_capture_dialog.setMaximumSize(QtCore.QSize(200, 100))
        input_capture_dialog.setWindowTitle(_fromUtf8(""))
        self.label = QtGui.QLabel(input_capture_dialog)
        self.label.setGeometry(QtCore.QRect(40, 40, 121, 20))
        self.label.setObjectName(_fromUtf8("label"))

        self.retranslateUi(input_capture_dialog)
        QtCore.QMetaObject.connectSlotsByName(input_capture_dialog)

    def retranslateUi(self, input_capture_dialog):
        self.label.setText(_translate("input_capture_dialog", "Waiting for a Key", None))

if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    input_capture_dialog = QtGui.QDialog()
    ui = Ui_input_capture_dialog()
    ui.setupUi(input_capture_dialog)
    input_capture_dialog.show()
    sys.exit(app.exec_())

