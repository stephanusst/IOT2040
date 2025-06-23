#Ujicoba GPIO
import mraa
import time

print ("IOT2040")

# initialise gpio 7. Greed Pilot Lamp
x1 = mraa.Gpio(7)

# initialise gpio 8. Yello Pilot Lamp
x2 =mraa.Gpio(8)

while True:
        x1.write(1)
        x2.write(0)
        time.sleep(1)

        x1.write(0)
        x2.write(1)
        time.sleep(1)
