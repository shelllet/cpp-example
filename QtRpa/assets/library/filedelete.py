import dataset
from system import file_remove

hash = 0x01

file_remove.invoke(filename= dataset.attribute[hash].filename)