import paho.mqtt.client as mqtt
import time
# Define event callbacks
##I am the publiser and the subscriber as well 
def on_connect(client, userdata, rc):
    if rc == 0:
         print("Connected successfully.")
    else:
         print("Connection failed. rc= "+str(rc))

def on_publish(client, userdata, mid):
    print()

def on_subscribe(client, userdata, mid, granted_qos):
    print()

def on_message(client, userdata, msg):
    print("narendra sent:"+ str(msg.payload))#.replace("b", "")

#object creation
mc1 = mqtt.Client()
mc2 = mqtt.Client()


#callbacks assigning
mc1.on_publish = on_publish
mc1.on_subscribe = on_subscribe
mc1.on_message = on_message

mc2.on_publish = on_publish
mc2.on_subscribe = on_subscribe
mc2.on_message = on_message


#password
mc1.username_pw_set("dubesundaram99@gmail.com", "5d263fb2") # client1 ka password kaju
mc2.username_pw_set("ravi123sehravat@gmail.com", "0cb91e15") # client2 ka password ravi
mc1.connect("mqtt.dioty.co", 1883)  # c1 ka connection
mc2.connect("mqtt.dioty.co", 1883)  # c2 ka connection


# looping mc1
mc1.loop_start()
mc2.loop_start() #start the loop
# Start subscription
#mc2.subscribe("/ravi123sehravat@gmail.com/narendra",1)
mc1.subscribe("/dubesundaram99@gmail.com/sundaram",1)


msg1=input("enter your msg: ")
while msg1 != "quit":
	mc2.publish("/ravi123sehravat@gmail.com/narendra", msg1 ,1)
	time.sleep(5) # wait
	msg1=input()

mc2.loop_stop()
mc1.loop_stop() #stop the loop


