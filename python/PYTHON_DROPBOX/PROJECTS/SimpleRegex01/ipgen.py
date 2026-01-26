import re

def main():
	uid_regex = re.compile(r'(\w+)*-(\w+)*-(\w+)*-(\w+)*-(\w+)*-(\w+)*')
	id_col = uid_regex.search('FF34-5DB-5431-3632-5959-4310')
	#print(id_col.groups()[0])
	print('if((encrypt[0] != 0x'+id_col.groups()[0]+') || (encrypt[1] != 0x0'+id_col.groups()[1]+') || (encrypt[2] != 0x'+id_col.groups()[2]+') || (encrypt[3] != 0x'+id_col.groups()[3]+') || (encrypt[4] != 0x'+id_col.groups()[4]+') || (encrypt[5] != 0x'+id_col.groups()[5]+'))')

if __name__ == '__main__':
	main()
