from ._input_listener import InputListener
from copy import deepcopy
from pynput.mouse import Controller
from threading import Thread
import time

class InputRecorder:

    def __init__(self, rate=60):
        self.mouse = Controller()
        self.rate = rate
        self.recording = False
        self.state = {"rate": rate, "path": []}

    def start(self):
        self.before = time.time()
        self.recording = True
        self.thread = Thread(target=self.update, args=())
        self.thread.start()
        return self

    def update(self):
        with InputListener() as il:
            while self.recording:
                self.state["path"].append(self.getInputState(il))
                now = time.time()
                if not ((1/self.rate) - (now - self.before) < 0):
                    time.sleep((1/self.rate) - (now - self.before))
                self.before = time.time()

    def stop(self):
        self.recording = False
        return self

    def join(self):
        if self.recording:
            self.recording = False
            if self.thread is not None:
                self.thread.join()
        return self

    def getInputState(self, input_listener):
        return {"pos": self.mouse.position, "events": deepcopy(input_listener.get_events())}
