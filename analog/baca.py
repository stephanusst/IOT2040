import mraa

def bacau(pin):
  aio=mraa.Aio(pin)
  raw_value= aio.read()
  print("A{}={}=>{:.2f} volt".format(pin, raw_value, raw_value/100))

def bacai(pin):
  aio=mraa.Aio(pin)
  raw_value= aio.read()
  print("A{}={}=>{:.2f} kgf/cm2= {:.2f} bar".format(pin, raw_value, raw_value*0.025-5, (raw_value*0.025-5)*0.980665))







