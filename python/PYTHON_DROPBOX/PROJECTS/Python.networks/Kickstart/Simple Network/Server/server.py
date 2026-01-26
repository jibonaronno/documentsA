import os
from socket import *
from asyncore import dispatcher
import logging
import asyncore
import string


host = ""
port = 13000
buf = 1024
address = (host, port)
UDPSocket = socket(AF_INET, SOCK_DGRAM)