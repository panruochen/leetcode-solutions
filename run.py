#!/usr/bin/python3 -f

import os, sys, platform, subprocess

print("OS %s" % os.name)
print("System %s" % platform.system())
if len(sys.argv) < 2 :
	print("Usage: run QUESTION")
	sys.exit(1)

new_env = os.environ.copy()
system_name = platform.system()

compilerLists = [ 'g++', 'clang++' ]
cl = None
exeFile = 'solution'

if system_name.find("MSYS_NT") >= 0 or system_name == "Windows" :
	exeFile += '.exe'
	try :
		sp = subprocess.Popen('cl -nologo -help'.split(), stdout=subprocess.PIPE)
		sp.communicate()
		if sp.returncode == 0 :
			cl = 'cl -nologo -O2 -EHsc -Fe:' + exeFile
	except :
		pass

if cl is None :
	for i in compilerLists :
		try :
			sp = subprocess.Popen((i + ' --version').split(), stdout=subprocess.PIPE)
			sp.communicate()
			if sp.returncode == 0 :
				cl = i + ' -O2 -std=c++11 -o ' + exeFile
				break
		except:
			pass

if cl is None :
	print("No compiler found")
	sys.exit(1)

print("CL : " + cl)
sourceFile = sys.argv[1]
if not sourceFile.endswith('.cpp') :
	sourceFile += ".cpp"
if not os.path.exists(sourceFile) :
	print("%s not exists" % sourceFile)
	sys.exit(1)

subprocess.check_call((cl + ' ' + sourceFile).split())
subprocess.check_call('./' + exeFile)


