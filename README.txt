BUILDING:
Unix Makefiles is for unix based systems
1. mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
                                                      =Release
2. make -j4 # build using 4 threads
