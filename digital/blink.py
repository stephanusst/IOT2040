import mraa
import time

print ("IOT2040")
x = mraa.Gpio(7)
x.dir(mraa.DIR_OUT)

while True:
        x.write(1)
        time.sleep(1)
        x.write(0)
        time.sleep(1)
