BUILDING:
Unix Makefiles is for unix based systems
1. mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
                                                   or =Release
2. make -j4 # build using 4 threads

Note: if you want to build the sandbox(playground) pass -D BUILD_SANDBOX=true

PROJECT STRUCTURE:

core/
    (Core implementation)
editor/
    (Engine's Visual Editor)
include/
    resource_manager.h  (Header for engine-wide access)
libs/
    ThirdPartyLibraries/  (External libraries stay here. Glfw, glad, stb_image...)
assets/
    Textures, models, sounds, etc.
sandbox/ - Not stable
    Experiments and fun/
    TestCases/  (Engine tests and demo scenes)
