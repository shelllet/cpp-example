import os


try:
    filename
except NameError:
    filename = None


print("filename:", filename)

os.remove(filename)


