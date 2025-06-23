import sys

import paho.mqtt.client as paho

client = paho.Client()

if client.connect("emjsl.ddns.net", 1883, 60) != 0:
    print("Couldn't connect to the mqtt broker")
    sys.exit(1)

client.publish("test", "Home", 0)
client.disconnect()
