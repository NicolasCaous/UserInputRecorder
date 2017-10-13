# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
from input import InputRecorder, InputPlayer

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

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(320, 220)
        MainWindow.setMinimumSize(QtCore.QSize(320, 220))
        MainWindow.setMaximumSize(QtCore.QSize(320, 220))
        MainWindow.setBaseSize(QtCore.QSize(320, 200))
        MainWindow.setMouseTracking(False)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.record_button = QtGui.QPushButton(self.centralwidget)
        self.record_button.setGeometry(QtCore.QRect(10, 10, 141, 31))
        self.record_button.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.record_button.setAutoDefault(False)
        self.record_button.setDefault(False)
        self.record_button.setFlat(False)
        self.record_button.setObjectName(_fromUtf8("record_button"))
        self.record_button.clicked.connect(self.record)
        self.play_button = QtGui.QPushButton(self.centralwidget)
        self.play_button.setGeometry(QtCore.QRect(170, 10, 141, 31))
        self.play_button.setObjectName(_fromUtf8("play_button"))
        self.play_button.clicked.connect(self.play)
        self.text_area = QtGui.QTextBrowser(self.centralwidget)
        self.text_area.setGeometry(QtCore.QRect(10, 50, 301, 161))
        self.text_area.setObjectName(_fromUtf8("text_area"))
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.recording = False

    def record(self):
        if self.recording:
            self.recorded.join()
            self.recording = False
            print ("not recording")
        else:
            print ("recording")
            self.recorded = InputRecorder(60)
            self.recorded.start()
            self.recording = True

    def play(self):
        if self.recorded is not None and not self.recording:
            print (len(self.recorded.state["path"]))
            print ("playing")
            player = InputPlayer(self.recorded)
            player.start()

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "User Input Recorder", None))
        self.record_button.setText(_translate("MainWindow", "Set Record Button", None))
        self.play_button.setText(_translate("MainWindow", "Set Play Button", None))
        self.text_area.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:18px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MainWindow = QtGui.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

