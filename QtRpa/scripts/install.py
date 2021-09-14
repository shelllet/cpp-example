import vcpkgs
import subprocess


for pkg in vcpkgs.pkgs:
    print(f"prepare to install {pkg} ......")
    stream = subprocess.Popen(
        f'vcpkg install {pkg}', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = stream.communicate()
    if err:
        print(err.decode("utf-8"))
    else:
        print(out.decode("utf-8"))
