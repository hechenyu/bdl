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
    a) lib文件在lib目录下
    b) 测试程序在build/test目录下

4) 项目工程需要依赖boost库, 确保系统安装boost
    $ sudo pacman -S boost # arch

5) python封装lib在export_py目录下, 确保先执行build.sh, 然后编译st_dataset.so
    $ cd export_py
    $ make

6) st_dataset.so依赖libpython, 确保系统安装python-dev包, 有可能需要修改export_py/Makefile, 以指定正确的python头文件和lib路径
	$ sudo apt-get install python-dev # ubuntu

7) 使用st_dataset.so, 请使用python3

8) 构建gtest, 工程顶级目录下, 执行./build_ut.sh, 需要依赖gtest, gtest安装:
	$ sudo apt-get install libgtest-dev 
	$ cd /usr/src/gtest  该目录下，有一个源码文件夹,一个cmake文件夹和一个cmake的配置文件(CMakeLists.txt)
	$ sudo mkdir build
	$ cd build
	$ sudo cmake ..
	$ sudo make
	$ sudo cp libgtest*.a /usr/local/lib
	$ cd ..
	$ sudo rm -rf ./build
