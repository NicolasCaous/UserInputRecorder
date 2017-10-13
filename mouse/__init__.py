import time
from threading import Thread
import pyautogui

class MouseEventListener:

    class __MouseEventListener:

        def __init__(self):
            self.run = True
            self.thread = Thread(target=self.update, args=())
            self.thread.start()

        def update(self):
            while self.run:
                self.a = 1

    instance = None

    def __init__(self):
        if not MouseEventListener.instance:
            MouseEventListener.instance = MouseEventListener.__MouseEventListener()

    def __getattr__(self, name):
        return getattr(self.instance, name)

    def __enter__(self):
        return self.instance

    def __exit__(self, exc_type, exc_value, traceback):
        self.instance.run = False
        self.instance.thread.join()

class MouseRecorder:

    def __init__(self, rate=60):
        self.recording = False
        self.state = {"rate": rate, "path": []}
        self.rate = rate

    def start(self):
        self.before = time.time()
        self.recording = True
        self.thread = Thread(target=self.update, args=())
        self.thread.start()
        return self

    def update(self):
        while self.recording:
            self.state["path"].append(MouseState())
            print("RECORDING")
            now = time.time()
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

class MouseState:
    def __init__(self):
        self.pos = pyautogui.position()
