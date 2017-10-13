from input import InputRecorder
import time

recorder = InputRecorder(60)
recorder.start()
time.sleep(5)
recorder.join()
print (len(recorder.state["path"]))

#pyautogui.MINIMUM_DURATION = 0
#pyautogui.MINIMUM_SLEEP = 0
#pyautogui.PAUSE = 0
#pyautogui.FAILSAFE = False

#for i in range(1000):
#    pyautogui.moveTo(100, 100)
#    pyautogui.moveTo(200, 100)
#    pyautogui.moveTo(200, 200)
#    pyautogui.moveTo(100, 200)
