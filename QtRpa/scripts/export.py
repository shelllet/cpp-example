import vcpkgs
import subprocess

sep = " "

print(f'vcpkg export {sep.join(vcpkgs.pkgs)} --zip')

stream = subprocess.Popen(
    f'vcpkg export {sep.join(vcpkgs.pkgs)} --zip', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
out, err = stream.communicate()
if err:
    print(err.decode("utf-8"))
else:
    print(out.decode("utf-8"))
