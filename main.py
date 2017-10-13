from input import InputRecorder, InputPlayer
import time

recorder = InputRecorder(60)
recorder.start()
time.sleep(10)
recorder.join()
print (len(recorder.state["path"]))
player = InputPlayer(recorder)
player.start()
player.join()
