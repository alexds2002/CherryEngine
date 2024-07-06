# currently only Linux supported

import os
from sys import argv

build_type = "Debug"
if len(argv) == 2: # if build mode was passed
    build_type = argv[1]

def main():
    global build_type
    os.system("mkdir build")
    os.chdir("./build")
    os.system(f'cmake -DCMAKE_BUILD_TYPE={build_type} -G "Unix Makefiles" ..')
    os.system("make -j12")

if __name__ == "__main__":
    main()
