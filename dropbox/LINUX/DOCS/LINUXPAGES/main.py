
import network
import socket

sta = network.WLAN(network.STA_IF)
sta.active(True)
sta.connect('TEST2', 'febr2022')
while not sta.isconnected():
	pass
print('net config:', sta.ifconfig())

