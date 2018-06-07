1) lib源码路径在src下, 增加源码.h和.cpp文件后, 修改src/CMakeLists.txt文件,
    a) 在set(LIBBASE_DATASET_LOADER_SRC下增加.cpp列表,
    b) 如果有需要在include_directories中添加头文件路径

2) 测试代码路径在test下, 增加测试的代码步骤,
    a) cd test文件后,
    b) cp -r main your_dir_name,
    c) cd your_dir_name
    d) 修改main.cpp
    e) 修改test目录的CMakeLists.txt, 增加一行add_subdirectory(your_dir_name)

3) 构建工程, 工程顶级目录下, 执行./build.sh, 生成的lib和测试程序都在工程顶级目录的build路径下.
    a) lib文件在build/lib目录下
    b) 测试程序在build/test目录下

4) 项目生成lib(即src目录)需要依赖boost的头文件(不需要lib), 测试(即test目录)需要依赖boost库, 确保系统安装boost
    $ sudo apt-get install libboost-all-dev # ubuntu
    $ sudo pacman -S boost # arch
