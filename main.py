# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui
from dialog import Ui_input_capture_dialog
from input._input_listener import InputListener
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

    dialog = False
    dialog_type = None
    dialog_window = None
    dialog_window_ui = None
    listener = None
    recording = False
    recorder = None
    playing = False
    player = None
    slider = None
    messages = []

    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(320, 220)
        MainWindow.setMinimumSize(QtCore.QSize(320, 220))
        MainWindow.setMaximumSize(QtCore.QSize(320, 220))
        MainWindow.setBaseSize(QtCore.QSize(320, 200))
        MainWindow.setMouseTracking(False)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.set_record_button = QtGui.QPushButton(self.centralwidget)
        self.set_record_button.setGeometry(QtCore.QRect(10, 10, 141, 31))
        self.set_record_button.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.set_record_button.setAutoDefault(False)
        self.set_record_button.setDefault(False)
        self.set_record_button.setFlat(False)
        self.set_record_button.setObjectName(_fromUtf8("set_record_button"))
        self.set_record_button.clicked.connect(self.show_dialog_record)
        self.set_play_button = QtGui.QPushButton(self.centralwidget)
        self.set_play_button.setGeometry(QtCore.QRect(10, 50, 141, 31))
        self.set_play_button.setObjectName(_fromUtf8("set_play_button"))
        self.set_play_button.clicked.connect(self.show_dialog_play)
        self.text_area = QtGui.QTextBrowser(self.centralwidget)
        self.text_area.setGeometry(QtCore.QRect(170, 10, 141, 201))
        self.text_area.setObjectName(_fromUtf8("text_area"))
        Ui_MainWindow.text_area = self.text_area
        self.slider_frequency = QtGui.QSlider(self.centralwidget)
        self.slider_frequency.setGeometry(QtCore.QRect(10, 110, 141, 29))
        self.slider_frequency.setMinimum(10)
        self.slider_frequency.setMaximum(200)
        self.slider_frequency.setSliderPosition(60)
        self.slider_frequency.setOrientation(QtCore.Qt.Horizontal)
        self.slider_frequency.setTickPosition(QtGui.QSlider.TicksAbove)
        self.slider_frequency.setTickInterval(10)
        self.slider_frequency.setObjectName(_fromUtf8("slider_frequency"))
        Ui_MainWindow.slider = self.slider_frequency
        self.label_frequency = QtGui.QLabel(self.centralwidget)
        self.label_frequency.setGeometry(QtCore.QRect(10, 90, 101, 17))
        self.label_frequency.setObjectName(_fromUtf8("label_frequency"))
        self.recording_button = QtGui.QPushButton(self.centralwidget)
        self.recording_button.setEnabled(False)
        self.recording_button.setGeometry(QtCore.QRect(0, 140, 81, 71))
        self.recording_button.setObjectName(_fromUtf8("recording_button"))
        self.playing_button = QtGui.QPushButton(self.centralwidget)
        self.playing_button.setEnabled(False)
        self.playing_button.setGeometry(QtCore.QRect(80, 140, 81, 71))
        self.playing_button.setObjectName(_fromUtf8("playing_button"))
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        Ui_MainWindow.listener = InputListener(record_method_a=Ui_MainWindow.record_method, record_key_a="r", play_method_a=Ui_MainWindow.play_method, play_key_a="p")

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "User Input Recorder", None))
        self.set_record_button.setText(_translate("MainWindow", "Set Record Button", None))
        self.set_play_button.setText(_translate("MainWindow", "Set Play Button", None))
        self.label_frequency.setText(_translate("MainWindow", "Frequency", None))
        self.recording_button.setText(_translate("MainWindow", "recording", None))
        self.playing_button.setText(_translate("MainWindow", "playing", None))
        self.text_area.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:18px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", None))

    def show_dialog_record(self):
        if not Ui_MainWindow.recording and not Ui_MainWindow.playing and not Ui_MainWindow.dialog:
            Ui_MainWindow.dialog_window = QtGui.QWidget()
            Ui_MainWindow.dialog_window_ui  = Ui_input_capture_dialog()
            Ui_MainWindow.dialog_window_ui.setupUi(Ui_MainWindow.dialog_window)
            Ui_MainWindow.dialog_window.show()
            Ui_MainWindow.listener.set_close_dialog(Ui_MainWindow.close_dialog)
            Ui_MainWindow.dialog = True
            Ui_MainWindow.dialog_type = "record"

    def show_dialog_play(self):
        if not Ui_MainWindow.recording and not Ui_MainWindow.playing and not Ui_MainWindow.dialog:
            Ui_MainWindow.dialog_window = QtGui.QWidget()
            Ui_MainWindow.dialog_window_ui  = Ui_input_capture_dialog()
            Ui_MainWindow.dialog_window_ui.setupUi(Ui_MainWindow.dialog_window)
            Ui_MainWindow.dialog_window.show()
            Ui_MainWindow.listener.set_close_dialog(Ui_MainWindow.close_dialog)
            Ui_MainWindow.dialog = True
            Ui_MainWindow.dialog_type = "play"

    def close_dialog(key):
        if Ui_MainWindow.dialog_type is "play":
            a =1
            Ui_MainWindow.listener.set_play_key(key)
        elif Ui_MainWindow.dialog_type is "record":
            Ui_MainWindow.listener.set_record_key(key)
        #Ui_MainWindow.dialog_window.hide()
        Ui_MainWindow.dialog = False

    def record_method():
        if not Ui_MainWindow.dialog:
            if Ui_MainWindow.recording:
                Ui_MainWindow.recorder.join()
                Ui_MainWindow.recording = False
                print("stoped recording")
            else:
                if not Ui_MainWindow.playing:
                    Ui_MainWindow.recorder = InputRecorder(Ui_MainWindow.slider.value())
                    Ui_MainWindow.recorder.start()
                    Ui_MainWindow.recording = True
                    print("recording")

    def play_method():
        if not Ui_MainWindow.dialog:
            if Ui_MainWindow.playing:
                Ui_MainWindow.player.stop()
                Ui_MainWindow.player.join()
                Ui_MainWindow.playing = False
                print("stoped playing")
            else:
                if Ui_MainWindow.recorder is not None and not Ui_MainWindow.recording:
                    Ui_MainWindow.player = InputPlayer(Ui_MainWindow.recorder)
                    Ui_MainWindow.player.start(Ui_MainWindow.play_method)
                    Ui_MainWindow.playing = True
                    print("playing")

if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MainWindow = QtGui.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

