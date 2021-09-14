import subprocess


try:
    filename
    args
except NameError:
    filename = None
    args = None

filename = "notepad.exe"
#args = "file.txt"

if args is None:
    subprocess.Popen(filename)
else:
    subprocess.Popen([filename, args])
