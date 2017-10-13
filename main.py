from mouse import MouseRecorder, MouseEventListener
import time

with MouseEventListener() as mel:
    recorder = MouseRecorder(1)
    recorder.start()
    time.sleep(5)
    recorder.join()
    mel.printA()

#pyautogui.MINIMUM_DURATION = 0
#pyautogui.MINIMUM_SLEEP = 0
#pyautogui.PAUSE = 0
#pyautogui.FAILSAFE = False

#for i in range(1000):
#    pyautogui.moveTo(100, 100)
#    pyautogui.moveTo(200, 100)
#    pyautogui.moveTo(200, 200)
#    pyautogui.moveTo(100, 200)
