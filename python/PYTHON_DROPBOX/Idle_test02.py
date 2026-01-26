Python 2.7.6 (default, Nov 10 2013, 19:24:18) [MSC v.1500 32 bit (Intel)] on win32
Type "copyright", "credits" or "license()" for more information.
>>> import re
>>> fre = re.compile(r'(\S+)\(((\S+ *)(, *\S+)*)\)')
>>> res = fre.search(r' \n\t int x = 10; \n\t 2_delay3(100, 20, YES);')
>>> fre.group()

Traceback (most recent call last):
  File "<pyshell#3>", line 1, in <module>
    fre.group()
AttributeError: '_sre.SRE_Pattern' object has no attribute 'group'
>>> res.group()
'2_delay3(100, 20, YES)'
>>> res.groups()
('2_delay3', '100, 20, YES', '100', ', YES')
>>> 
>>> res = fre.search(r' \n\t int x = 10; \n\t 2_delay3(100, 20, YES , NO);')
>>> res.group()

Traceback (most recent call last):
  File "<pyshell#8>", line 1, in <module>
    res.group()
AttributeError: 'NoneType' object has no attribute 'group'
>>> res = fre.search(r' \n\t int x = 10; \n\t 2_delay3(100, 20, YES, NO);')
>>> res.group()
'2_delay3(100, 20, YES, NO)'
>>> fre = re.compile(r'(\S+)\((( *\S+ *)( *, *\S+ *)*)\)')
>>> res = fre.search(r' \n\t int x = 10; \n\t 2_delay3(100, 20, YES , NO);')
>>> res.group()
'2_delay3(100, 20, YES , NO)'
>>> 
