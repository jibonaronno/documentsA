Python 2.7.12 (v2.7.12:d33e0cf91556, Jun 27 2016, 15:19:22) [MSC v.1500 32 bit (Intel)] on win32
Type "copyright", "credits" or "license()" for more information.
>>> import re
>>> funcRegex = re.compile(r"(\D)+(\w)*\((\w+,|\w+)|*\)")

Traceback (most recent call last):
  File "<pyshell#1>", line 1, in <module>
    funcRegex = re.compile(r"(\D)+(\w)*\((\w+,|\w+)|*\)")
  File "C:\Python27\lib\re.py", line 194, in compile
    return _compile(pattern, flags)
  File "C:\Python27\lib\re.py", line 251, in _compile
    raise error, v # invalid expression
error: nothing to repeat
>>> funcRegex = re.compile(r"(\D)+(\w)*\((\w+,|\w+)*\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200);\n\n\t')
>>> funcResult.gr

Traceback (most recent call last):
  File "<pyshell#4>", line 1, in <module>
    funcResult.gr
AttributeError: '_sre.SRE_Match' object has no attribute 'gr'
>>> funcResult.group()
'; \n\t delay(200)'
>>> funcRegex = re.compile(r"(\S)+(\w)*\((\w+,|\w+)*\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200);\n\n\t')
>>> funcResult.group()
'delay(200)'
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200, 100);\n\n\t')
>>> funcResult.group()

Traceback (most recent call last):
  File "<pyshell#10>", line 1, in <module>
    funcResult.group()
AttributeError: 'NoneType' object has no attribute 'group'
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200,100);\n\n\t')
>>> funcResult.group()
'delay(200,100)'
>>> funcRegex = re.compile(r"(\S)+(\w)*\((\w+ *, *| *\w+ *)*\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200, 100);\n\n\t')
>>> funcResult.group()
'delay(200, 100)'
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200,100);\n\n\t')
>>> funcResult.group()
'delay(200,100)'
>>> funcResult.groups().len

Traceback (most recent call last):
  File "<pyshell#18>", line 1, in <module>
    funcResult.groups().len
AttributeError: 'tuple' object has no attribute 'len'
>>> funcResult.groups().len()

Traceback (most recent call last):
  File "<pyshell#19>", line 1, in <module>
    funcResult.groups().len()
AttributeError: 'tuple' object has no attribute 'len'
>>> funcResult.groups()
('y', None, '100')
>>> funcResult.groups(1)
('y', 1, '100')
>>> funcResult.groups(2)
('y', 2, '100')
>>> funcResult.groups(3)
('y', 3, '100')
>>> funcResult.groups(4)
('y', 4, '100')
>>> funcResult.groups(5)
('y', 5, '100')
>>> funcResult.group(1)
'y'
>>> funcResult.group()
'delay(200,100)'
>>> funcResult.group(2)
>>> funcResult.group(3)
'100'
>>> funcResult.group(4)

Traceback (most recent call last):
  File "<pyshell#30>", line 1, in <module>
    funcResult.group(4)
IndexError: no such group
>>> funcRegex = re.compile(r"((\S)+)(\w)*\((\w+ *, *| *\w+ *)*\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200, 100);\n\n\t')
>>> funcResult.group()
'delay(200, 100)'
>>> funcResult.group(1)
'delay'
>>> funcResult.group(2)
'y'
>>> funcResult.group(3)
>>> funcResult.group(4)
'100'
>>> funcRegex = re.compile(r"((\S)+)((\w)*)\(((\w+ *, *| *\w+ *)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200, 100);\n\n\t')
>>> funcResult.group(2)
'y'
>>> funcResult.group(1)
'delay'
>>> funcResult.group(3)
''
>>> funcResult.group(4)
>>> funcResult.group(5)
'200, 100'
>>> funcResult.groups()
('delay', 'y', '', None, '200, 100', '100')
>>> funcRegex = re.compile(r"(\S+)(\w*)\(((\w+ *, *| *\w+ *)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200, 100);\n\n\t')
>>> funcResult.groups()
('delay', '', '200, 100', '100')
>>> funcResult = funcRegex.search('int x = 0; \n\t delay (200, 100);\n\n\t')
>>> funcResult.groups()

Traceback (most recent call last):
  File "<pyshell#50>", line 1, in <module>
    funcResult.groups()
AttributeError: 'NoneType' object has no attribute 'groups'
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200, 100);\n\n\t')
>>> funcResult.groups()
('delay', '', '200, 100', '100')
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200  ,  100);\n\n\t')
>>> funcResult.groups()
('delay', '', '200  ,  100', '100')
>>> funcRegex = re.compile(r"(\S+)(\w*)\(((\w+ *,? *)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200  ,  100);\n\n\t')
>>> funcResult.groups()
('delay', '', '200  ,  100', '100')
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200  ,  100, 432);\n\n\t')
>>> funcResult.groups()
('delay', '', '200  ,  100, 432', '432')
>>> funcRegex = re.compile(r"(\S+)(\w*)\(((\S+ *,? *)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200  ,  100, 432);\n\n\t')
>>> funcResult.groups()
('delay', '', '200  ,  100, 432', '432')
>>> funcRegex = re.compile(r"(\S+)\(((\S+ *,? *)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200  ,  100, 432);\n\n\t')
>>> funcResult.groups()
('delay', '200  ,  100, 432', '432')
>>> funcResult = funcRegex.search('int x = 0; \n\t delay(200  ,  100,a_432);\n\n\t')
>>> funcResult.groups()
('delay', '200  ,  100,a_432', '100,a_432')
>>> funcResult = funcRegex.search('int x = 0; \n\t 2_delay3(200  ,  100,a_432);\n\n\t')
>>> funcResult.groups()
('2_delay3', '200  ,  100,a_432', '100,a_432')
>>> funcResult = funcRegex.search('int x = 0; \n\t 2_delay3(200  ,  100, a_432);\n\n\t')
>>> funcResult.groups()
('2_delay3', '200  ,  100, a_432', 'a_432')
>>> funcResult = funcRegex.search('int x = 0; \n\t 2_delay3();\n\n\t')
>>> funcResult.groups()
('2_delay3', '', None)
>>> funcResult = funcRegex.search('int x = 0; \n\t 2_delay3(,);\n\n\t')
>>> funcResult.groups()
('2_delay3', ',', ',')
>>> funcRegex = re.compile(r"(\S+)(\w*)\((((\w+ *)(,\w)*)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t 2_delay3(200  ,  100, a_432);\n\n\t')
>>> funcResult.groups()

Traceback (most recent call last):
  File "<pyshell#78>", line 1, in <module>
    funcResult.groups()
AttributeError: 'NoneType' object has no attribute 'groups'
>>> funcRegex = re.compile(r"(\S+)(\w*)\((((\w+ *)( *, *\w+)*)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t 2_delay3(200  ,  100, a_432);\n\n\t')
>>> funcResult.groups()
('2_delay3', '', '200  ,  100, a_432', '200  ,  100, a_432', '200  ', ', a_432')
>>> funcRegex = re.compile(r"(\S+)\((((\w+ *)( *, *\w+)*)*)\)")
>>> funcResult = funcRegex.search('int x = 0; \n\t 2_delay3(200  ,  100, a_432);\n\n\t')
>>> funcResult.groups()
('2_delay3', '200  ,  100, a_432', '200  ,  100, a_432', '200  ', ', a_432')
>>> 
