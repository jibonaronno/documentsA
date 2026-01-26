Python 2.7.12 (v2.7.12:d33e0cf91556, Jun 27 2016, 15:19:22) [MSC v.1500 32 bit (Intel)] on win32
Type "copyright", "credits" or "license()" for more information.
>>> import serial
>>> import random
>>> def CRCcal(msg):
    #CRC (Cyclical Redundancy Check) Calculation
    CRC = 0xFFFF
    CRCHi = 0xFF
    CRCLo = 0xFF
    CRCLSB = 0x00
    for i in range(0, len(msg)-2,+1):
        CRC = (CRC ^ msg[i])
        for j in range(0, 8):
            CRCLSB = (CRC & 0x0001);
            CRC = ((CRC >> 1) & 0x7FFF)

            if (CRCLSB == 1):
                CRC = (CRC ^ 0xA001)
    CRCHi = ((CRC >> 8) & 0xFF)
    CRCLo = (CRC & 0xFF)
    return (CRCLo,CRCHi)

>>> CRCcal([0x11, 0x02, 0x00, 0xc4, 0x00, 0x16])
(165, 75)
>>> CRCcal([0x16, 0x00, 0xc4, 0x00, 0x02, 0x11])
(86, 172)
>>> def CRCcal2(msg):
    #CRC (Cyclical Redundancy Check) Calculation
    CRC = 0xFFFF
    CRCHi = 0xFF
    CRCLo = 0xFF
    CRCLSB = 0x00
    for i in range(0, len(msg)-2,+1):
        CRC = (CRC ^ msg[i])
        for j in range(0, 8):
            CRCLSB = (CRC & 0x0001);
            CRC = ((CRC >> 1) & 0x7FFF)

            if (CRCLSB == 1):
                CRC = (CRC ^ 0xA001)
    CRCHi = ((CRC >> 8) & 0xFF)
    CRCLo = (CRC & 0xFF)
    print("{0:X} , {1:X}".format(CRCLo, CRCHi))
    return (CRCLo,CRCHi)

>>> CRCcal2([0x11, 0x02, 0x03, 0xAC, 0xDB, 0x35])
A4 , 55
(164, 85)
>>> def CRCcal3(msg):
    #CRC (Cyclical Redundancy Check) Calculation
    CRC = 0xFFFF
    CRCHi = 0xFF
    CRCLo = 0xFF
    CRCLSB = 0x00
    for i in range(0, len(msg)):
        CRC = (CRC ^ msg[i])
        for j in range(0, 8):
            CRCLSB = (CRC & 0x0001);
            CRC = ((CRC >> 1) & 0x7FFF)

            if (CRCLSB == 1):
                CRC = (CRC ^ 0xA001)
    CRCHi = ((CRC >> 8) & 0xFF)
    CRCLo = (CRC & 0xFF)
    print("{0:X} , {1:X}".format(CRCLo, CRCHi))
    return (CRCLo,CRCHi)

>>> CRCcalc3([0x11, 0x02, 0x00, 0xc4, 0x00, 0x16])

Traceback (most recent call last):
  File "<pyshell#11>", line 1, in <module>
    CRCcalc3([0x11, 0x02, 0x00, 0xc4, 0x00, 0x16])
NameError: name 'CRCcalc3' is not defined
>>> CRCcal3([0x11, 0x02, 0x00, 0xc4, 0x00, 0x16])
BA , A9
(186, 169)
>>> 
