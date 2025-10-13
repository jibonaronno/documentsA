import subprocess
from os.path import join, dirname, abspath
import os
import pprint
from ftplib import FTP
from time import sleep
from datetime import datetime
import requests

def getExistingFileList():
    lines = []
    with open(join(dirname(abspath(__file__)), 'files.csv'), 'r') as rdr:
        lines = rdr.readlines()
        return lines

def main():
    flist = []
    files = []
    ftp_ip = "ftp.toiconnect.net"
    ftp_usr = "jibon@toiconnect.net"
    ftp_pwd = "jibon@2021"
    ftp_client = FTP(ftp_ip)
    ftp_client.login(user=ftp_usr, passwd = ftp_pwd)
    ftp_client.dir(flist.append)
    newFiles = ""
    oldFiles = getExistingFileList()
    print("Files Count : " + str(len(oldFiles)))


    #splt = flist[0].split(" ")
    #print(len(splt))
    #print(type(flist[0]))
    #print(flist[0])
    for fl in flist:
        splt = fl.split(" ")
        files.append(splt[-1])
        #print(splt[-1])

    for fl in files:
        if fl+"\n" not in oldFiles:
            newFiles += fl + "\n"
            URL = "https://camera.toiconnect.net/api/sync_data?devid=0x00001&image_name=" + fl
            r = requests.get(url = URL)
            pprint.pprint(r)

    with open(join(dirname(abspath(__file__)), 'files.csv'), 'a') as rdr:
        rdr.write(newFiles)

while True:
    main()
    sleep(10)
