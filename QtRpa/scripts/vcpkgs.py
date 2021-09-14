import re
import sys
import os

readme = open("./README.md", "r", encoding='UTF-8')

data = readme.read()
readme.close()

pkgs = []
p = re.compile("vcpkg install (.+:.+)$", re.MULTILINE)

for m in re.finditer(p, data):
    pkgs.append(m.group(1))


