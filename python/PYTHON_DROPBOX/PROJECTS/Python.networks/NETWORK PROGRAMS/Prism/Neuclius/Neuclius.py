__author__ = 'Aronno'

import os
import asyncore
import asyncio
import socket
from asyncore import dispatcher



if __name__ == '__main__':
    print('Starting Network Client....')
    dispatchers = []
    dispatchers.append(dispatcher(socket.socket(socket.AF_INET, socket.SOCK_STREAM)))

    addresses = []

    addresses.append(('', 13000))

    