from copy import deepcopy
from pynput import mouse, keyboard
from threading import Thread

def on_click(x, y, button, pressed):
    InputListener.buffer.append({"type": "click", "x": x, "y": y, "button": button, "pressed": pressed})
    if len(InputListener.buffer) > 30:
        InputListener.buffer = []

def on_scroll(x, y, dx, dy):
    InputListener.buffer.append({"type": "scroll", "x": x, "y": y, "dx": dx, "dy": dy})
    if len(InputListener.buffer) > 30:
        InputListener.buffer = []

def on_press(key):
    if InputListener.new_dialog:
        InputListener.dialog_method(key)
        InputListener.new_dialog = False
        return
    if key == InputListener.record_key:
        InputListener.record_method()
        return
    if key == InputListener.play_key:
        InputListener.play_method()
        return
    InputListener.buffer.append({"type": "keyboard", "pressed": True, "key": key})
    if len(InputListener.buffer) > 30:
        InputListener.buffer = []

def on_release(key):
    InputListener.buffer.append({"type": "keyboard", "pressed": False, "key": key})
    if len(InputListener.buffer) > 30:
        InputListener.buffer = []

class InputListener:

    buffer = []
    cont = 0
    mouse = None
    keyboard = None
    record_key = None
    record_method = None
    play_key = None
    play_method = None
    dialog_method = None
    new_dialog = False

    def __init__(self, record_method_a=None, record_key_a=None, play_method_a=None, play_key_a=None):
        if record_method_a is not None:
            InputListener.record_method = record_method_a
        if record_key_a is not None:
            InputListener.record_key = record_key_a
        if play_method_a is not None:
            InputListener.play_method = play_method_a
        if play_key_a is not None:
            InputListener.play_key = play_key_a
        if InputListener.mouse is None:
            InputListener.mouse = mouse.Listener(on_click=on_click, on_scroll=on_scroll)
            InputListener.mouse.start()
        if InputListener.keyboard is None:
            InputListener.keyboard = keyboard.Listener(on_press=on_press, on_release=on_release)
            InputListener.keyboard.start()
        InputListener.cont = InputListener.cont + 1

    def __del__(self):
        if InputListener.cont is 1:
            InputListener.mouse.stop()
            InputListener.keyboard.stop()
        InputListener.cont = InputListener.cont - 1

    def get_events(self):
        tmp = deepcopy(InputListener.buffer)
        InputListener.buffer = []
        return tmp

    def clear_buffer(self):
        InputListener.buffer = []

    def set_close_dialog(self, new_dialog_method):
        InputListener.dialog_method = new_dialog_method
        InputListener.new_dialog = True

    def set_record_key(self, key):
        InputListener.record_key = key

    def set_play_key(self, key):
        InputListener.play_key = key
