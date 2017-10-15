from input import InputRecorder, InputPlayer
from PyQt4 import QtGui, QtCore
import sys
import time

class Window(QtGui.QMainWindow):

    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry(50, 50, 500, 300)
        self.setFixedSize(self.size())
        self.setWindowTitle("Input Recorder And Player")
        self.setWindowIcon(QtGui.QIcon("input.png"))
        self.home()

    def home(self):
        self.show()

def run():
    app = QtGui.QApplication(sys.argv)
    GUI = Window()
    sys.exit(app.exec_())

run()

#recorder = InputRecorder(60)
#recorder.start()
#time.sleep(10)
#recorder.join()
#print (len(recorder.state["path"]))
#player = InputPlayer(recorder)
#player.start()
#player.join()
