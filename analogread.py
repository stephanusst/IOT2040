import mraa
import time
import baca

print("IOT2040")

x=mraa.Gpio(7)
x.dir(mraa.DIR_OUT)

y=mraa.Gpio(8)
y.dir(mraa.DIR_OUT)

aio2= mraa.Aio(2)
aio3= mraa.Aio(3)

#def bacau(pin):
#  aio=mraa.Aio(pin)
#  raw_value= aio.read()
#  print("A{}={}=>{:.2f} volt".format(pin, raw_value, raw_value/100))

#def bacai(pin):
#  aio=mraa.Aio(pin)
#  raw_value= aio.read()
#  print("A{}={}=>{:.2f} kgf/cm2, {:.2f} bar".format(pin, raw_value, raw_value*0.025-5,(raw_value*0.025-5)*0.980665))

while True:
  x.write(1)
  y.write(1)
  time.sleep(1)

  x.write(0)
  y.write(0)
  time.sleep(1)

  baca.bacau(2)
  baca.bacai(3)
