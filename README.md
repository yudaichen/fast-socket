# fastSocket

#### 介绍
最快的服务器

#### 软件架构

|  根路径 | 包名  |  注释 |
| ------------ | ------------ | ------------ |
|  examples |  designPattern |  c++设计模式案例 |
|  examples | network  |  TCP-UDP案例 |
|  examples | utils  |  常用工具包整理 |
|  include | utils-collection  |  项目通用容器封装类-头文件 |
|  include | utils-concurrent  |  项目通用多线程封装类-头文件 |
|  include | utils-include  |  项目通用魔法类-头文件 |
|  src | utils-concurrent  |  项目通用多线程封装类-实现 |
|  src | utils-magic  |  项目通用魔法操作实现-实现 |

#### 使用说明

    UNIX: -S .. -G "Unix Makefiles"
    WINODWS: -S .. -G  "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_TOOLCHAIN_FILE=${你的vcpkg路径} -DVCPKG_TARGET_TRIPLET=x64-windows-static
    运行cmake

#### 参与贡献

    姓名：余代宸
    qq: 250074249

#### 结语

“Any fool can write code that a computer can understand. Good programmers write code that humans can understand.”
― Martin Fowler

“任何傻瓜都可以编写计算机可以理解的代码。 优秀的程序员编写人类可以理解的代码。”
——马丁·福勒