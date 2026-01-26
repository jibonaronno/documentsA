import re
import sys
import os.path
from os import path

def main(arg):
	#uid_regex = re.compile(r'(\w+)*-(\w+)*-(\w+)*-(\w+)*-(\w+)*-(\w+)*')
	#id_col = uid_regex.search('FF34-5DB-5431-3636-5922-4310')
	#print(id_col.groups()[0])
	#print('if((encrypt[0] != 0x'+id_col.groups()[0]+') || (encrypt[1] != 0x0'+id_col.groups()[1]+') || (encrypt[2] != 0x'+id_col.groups()[2]+') || (encrypt[3] != 0x'+id_col.groups()[3]+') || (encrypt[4] != 0x'+id_col.groups()[4]+') || (encrypt[5] != 0x'+id_col.groups()[5]+'))')

	#newline = 'if((encrypt[0] != 0x'+id_col.groups()[0]+') || (encrypt[1] != 0x0'+id_col.groups()[1]+') || (encrypt[2] != 0x'+id_col.groups()[2]+') || (encrypt[3] != 0x'+id_col.groups()[3]+') || (encrypt[4] != 0x'+id_col.groups()[4]+') || (encrypt[5] != 0x'+id_col.groups()[5]+'))'

	idx = 0

	with open('main1.c', 'r') as f:
		txt = f.readlines()
		f.close()
		with open('main1.c', 'w') as f:
			txt[495] = '\t' + newline + '\n' #Change the contents of line 496
			f.writelines(txt)
			f.close()

if __name__ == '__main__':
	if len(sys.argv) > 0:
        main(sys.argv[0])
    else:
        exit()
