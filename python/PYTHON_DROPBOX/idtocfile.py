import re
import sys
import shutil

def ReadWrite(newline):
	idx = 0

	with open('main.c', 'r') as f:
		txt = f.readlines()
		f.close()
		with open('main.c', 'w') as f:
			txt[495] = '\t' + newline + '\n' #Change the contents of line 496
			f.writelines(txt)
			f.close()

def copyfile(uid):
	shutil.copy('C:/Study/ARM/STM32/STM32F107RC/Ethertest/Gptest.05/MDK-ARM/Gptest/Gptest.hex', 'C:/Study/ARM/STM32/STM32F107RC/Ethertest/Gptest.05/MDK-ARM/Gptest/'+uid+'.hex')

def main():
	srctxt = 'FF37-5D5-5232-3538-5855-4320'
	uid_regex = re.compile(r'(\w+)*-(\w+)*-(\w+)*-(\w+)*-(\w+)*-(\w+)*')
	id_col = uid_regex.search(srctxt)
	#print(id_col.groups()[0])
	#print('if((encrypt[0] != 0x'+id_col.groups()[0]+') || (encrypt[1] != 0x0'+id_col.groups()[1]+') || (encrypt[2] != 0x'+id_col.groups()[2]+') || (encrypt[3] != 0x'+id_col.groups()[3]+') || (encrypt[4] != 0x'+id_col.groups()[4]+') || (encrypt[5] != 0x'+id_col.groups()[5]+'))')

	newline = 'if((encrypt[0] != 0x'+id_col.groups()[0]+') || (encrypt[1] != 0x0'+id_col.groups()[1]+') || (encrypt[2] != 0x'+id_col.groups()[2]+') || (encrypt[3] != 0x'+id_col.groups()[3]+') || (encrypt[4] != 0x'+id_col.groups()[4]+') || (encrypt[5] != 0x'+id_col.groups()[5]+'))'
	ReadWrite(newline)
	raw_input("Press Enter to continue...")
	print('Copying')
	copyfile(srctxt)

if __name__ == '__main__':
	main()
