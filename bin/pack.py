#!python
# due to xclip bug, please install xsel, with is prefered by pyperclip
# refer to pyperclip issue #116
import re
import sys
import os
import pyperclip
pattern = re.compile('^#include *"(.*)"')
did = set()
doglib_prefix = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
 
print(doglib_prefix)

def pack(filename):
	if filename.startswith("doglib/"):
		filename = os.path.join(doglib_prefix,  filename)
	abspath = os.path.abspath(filename)
	dirname = os.path.dirname(abspath)
	if abspath in did:
		return ""
	did.add(abspath)
	os.chdir(dirname)
	file = open(abspath, "r")
	data = ""
	for line in file.readlines():
		m = pattern.match(line)
		if not m :
			data += line
		else:
			include_filename =  m.groups()[0]
			data += '// begin of ' + include_filename + '\n'
			data += pack(include_filename)
			data += '// end of ' + include_filename + '\n'
			os.chdir(dirname)
		
	return data


root_filename = sys.argv[1]
pyperclip.copy(pack(root_filename))
# paste = pyperclip.paste()
# print(paste)
print("done")


