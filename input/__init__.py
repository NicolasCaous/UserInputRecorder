from ._input_listener import InputListener
from copy import deepcopy
from pynput import mouse, keyboard
import math
import time
import threading

class InputRecorder:

    def __init__(self, rate=60):
        self.mouse = mouse.Controller()
        self.rate = rate
        self.recording = False
        self.state = {"rate": rate, "path": []}

    def start(self):
        self.before = time.time()
        self.recording = True
        self.thread = threading.Thread(target=self.update, args=())
        self.thread.start()
        return self

    def update(self):
        listener = InputListener()
        while self.recording:
            self.state["path"].append(self.getInputState(listener))
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

class InputPlayer:

    def __init__(self, recorder, interpolate=False):
        self.rate = recorder.state["rate"]
        self.path = recorder.state["path"][math.ceil(self.rate/6):-math.ceil(self.rate/6)]
        self.playing = False
        self.mouse = mouse.Controller()
        self.keyboard = keyboard.Controller()

    def start(self, stop_method):
        self.stop_method = stop_method
        self.before = time.time()
        self.playing = True
        self.thread = threading.Thread(target=self.update, args=())
        self.thread.start()
        return self

    def update(self):
        for state in self.path:
            if not self.playing:
                break
            self.mouse.position = state["pos"]
            for event in state["events"]:
                if event["type"] is "click":
                    self.mouse.position = (event["x"], event["y"])
                    if event["pressed"]:
                        self.mouse.press(event["button"])
                    else:
                        self.mouse.release(event["button"])
                elif event["type"] is "scroll":
                    self.mouse.position = (event["x"], event["y"])
                    self.mouse.scroll(event["dx"], event["dy"])
                else:
                    if event["pressed"]:
                        self.keyboard.press(event["key"])
                    else:
                        self.keyboard.release(event["key"])
            now = time.time()
            if not ((1/self.rate) - (now - self.before) < 0):
                time.sleep((1/self.rate) - (now - self.before))
            self.before = time.time()
        self.stop_method()

    def stop(self):
        self.playing = False
        return self

    def join(self):
        try:
            self.thread.join()
        except:
            return self
        return self
