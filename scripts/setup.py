import os
import subprocess
import platform

from setup_python import PythonConfiguration as PythonRequirements
from setup_premake import PremakeConfiguration as PremakeRequirements

os.chdir('./../')
PythonRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

premakeInstalled = PremakeRequirements.Validate()
if (premakeInstalled):
    print("\nRunning premake...")
    if platform.system() == "Windows":
        subprocess.call([os.path.abspath("./scripts/win_gen.bat"), "NOPAUSE"])
    else:
        print(f"{os.platform()} is not supported !")
        exit()
    print("\033[32mSetup completed!\033[0m")
else:
    print("\033[31mSimConnector requires Premake to generate project files.\033[0m")
