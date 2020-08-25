import os
import subprocess
# Create a software version from Git tag
try:
    with open(os.devnull, "w") as DEVNULL:
        label=subprocess.check_output(["git", "describe", "--tags", "--dirty"],stderr=DEVNULL).strip().decode()
except subprocess.CalledProcessError as e:
    #label='v0.0-0-'+ subprocess.check_output(["git", "rev-parse", "--short", "HEAD"]).strip().decode()
    #git rev-parse --short HEAD
    label='v0.0-0-'+ subprocess.check_output(["git", "describe", "--always", "--dirty"]).strip().decode()
    
print(label)
