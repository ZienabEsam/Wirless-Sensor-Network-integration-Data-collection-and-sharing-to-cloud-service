![IMG_20170602_120447](https://user-images.githubusercontent.com/24304903/130311500-fd20bc07-87bb-46d6-a095-829d5c3ceead.jpg)
# Wirless-Sensor-Network-integration-Data-collection-and-sharing-to-cloud-service
Integration of Wireless sensor Network for data collection and sharing (IoT)
The basic idea of the prototype is to implement the basic
concept of Internet of Thing with a basic application specified as
an example.In the prototype implemented, I adopted the concept
of a smart home to be basic building block to impalement the
idea.In general a smart home can include some kind of various
types of sensors,which collects any type of data and connected
to a coordinator as a gateway to be in turn connected to the
Internet.In the implementation I used the temperature ,and
humidity sensing as an example of the data collected,these data
according to the previous sections taking about the Wireless
sensor networks (WSN), are goatherd via a coordinator unit to
share it somewhere on the Internet, either a private hosting or a
Cloud service.

![layers of Iot](https://user-images.githubusercontent.com/24304903/130311616-dd22370c-f9d4-4ba8-b209-37ae927fbbcd.png)

Inte block diagram the layers of the project, only using Wifi instead of Xbee

To complete the project you will need :
+Wi-Fi module ESP8266-01 (Or any type of wifi modules you prefere)
+ 1* DHT11 Temperature humidity sensor
+ 1* PDU (Power Distribution Unit)
+ Different sizes of pin headers wires
+ USB-to-TTL

Thingspeak Application is acctulay very user-friendly , and the results can be something like this

![Screenshot_2017-06-02-12-05-56](https://user-images.githubusercontent.com/24304903/130311704-59f7e649-cb2e-4b48-8b1b-9d505b5d253f.png)

Using web thingspeak will show results also like this

![tem hum](https://user-images.githubusercontent.com/24304903/130311747-564127ac-c0a8-47f7-b4c0-2300dc1349ce.PNG)

