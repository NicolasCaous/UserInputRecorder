from copy import deepcopy
from pynput import mouse, keyboard
from threading import Thread

def on_click(x, y, button, pressed):
    InputListener.buffer.append({"type": "click", "x": x, "y": y, "button": button, "pressed": pressed})

def on_scroll(x, y, dx, dy):
    InputListener.buffer.append({"type": "scroll", "x": x, "y": y, "dx": dx, "dy": dy})

def on_press(key):
    InputListener.buffer.append({"type": "keyboard", "pressed": True, "key": key})

def on_release(key):
    InputListener.buffer.append({"type": "keyboard", "pressed": False, "key": key})

class InputListener:

    buffer = []

    def __init__(self):
        self.__mouse = mouse.Listener(on_click=on_click, on_scroll=on_scroll)
        self.__keyboard = keyboard.Listener(on_press=on_press, on_release=on_release)

    def __enter__(self):
        self.__mouse.start()
        self.__keyboard.start()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.__mouse.stop()
        self.__keyboard.stop()

    def get_events(self):
        tmp = deepcopy(InputListener.buffer)
        InputListener.buffer = []
        return tmp
