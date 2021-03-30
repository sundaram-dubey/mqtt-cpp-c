import paho.mqtt.client as mqtt
import time
# Define event callbacks
##I am the publiser
def on_connect(client, userdata, rc):
    if rc == 0:
         print("Connected successfully.")
    else:
         print("Connection failed. rc= "+str(rc))

def on_publish(client, userdata, mid):
    print("Message "+str(mid)+" published.")

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribe with mid "+str(mid)+" received.")

def on_message(client, userdata, msg):
    print("Message received on topic "+ str(msg.topic)+" with QoS "+str(msg.qos)+" and payload "+ str(msg.payload))

mqttclient = mqtt.Client()

# Assign event callbacks
#mqttclient.on_connect = on_connect
mqttclient.on_publish = on_publish
mqttclient.on_subscribe = on_subscribe
mqttclient.on_message = on_message

# Connect
mqttclient.username_pw_set("ravi123sehravat@gmail.com", "0cb91e15")
mqttclient.connect("mqtt.dioty.co", 1883)

mqttclient.loop_start() #start the loop
# Start subscription
mqttclient.subscribe("/ravi123sehravat@gmail.com/narendra",1)

# Publish a message
# while True:
#     x = input("Enter your message: ")
#     mqttclient.publish("/dubesundaram99@gmail.com/sundaram", x,1)
#     if(x == "stop" or x == "quit"):
#         break

# # Loop; exit on error
# rc = 0
# while rc == 0:
#     rc = mqttclient.loop()
#     print("rc: " + str(rc))

#mqttclient.publish("/dubesundaram99@gmail.com/sundaram", "I have always been the alpha",1)
time.sleep(60) # wait
mqttclient.loop_stop() #stop the loop