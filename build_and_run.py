import os

def main():
    os.system('mkdir build')
    os.chdir('./build')
    # Generates unix make files instead of the Windows equivelent
    os.system('cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release .. && make -j4 && ./CherrY')

if name == "__main__":
    main()
