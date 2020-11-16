<div style="text-align: left">
<font face="微软雅黑" size=5 color=#FF00FF>
  小关的读书笔记
</font> 
</div>


<center> Geant4 教程 </center>
===============================

>+ 安装使用 Geant4 应注意版本. 
>+ Geant4 的学习材料可能比较多, 作为新手, 我打算从 geant4 官网的入门教程 "Book For Application DevelopersLogo" 着手, 结合 geant4 安装路径下的例子进行学习！

> Geant4 学习资料
> [1.Geant4 官网入门教程](http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/)
> [2.Geant4 官方论坛](https://geant4-forum.web.cern.ch/)
> [3.Geant4 User's Guide (中文版)](https://cloud.tsinghua.edu.cn/f/592b15e0d13e4434a3c7/)
> [4.工物系杨振伟老师讲义](https://cloud.tsinghua.edu.cn/d/90b1910754ef4f44a73c/)



目录
-----
[toc]


## <font color=#DC143C> 附录: </font>
### <font color=#00BFFF> Geant4 的安装  </font>

#### <font color=#FF00FF> Step1 - 安装前的准备（在终端中分别执行下面命令）</font>

```C++
1. sudo apt-get install build-essential  ##  安装gcc等编译程序

2. //安装cmake(要注意cmake的版本要求，geant4.10.03.p01 
   // 版本要求cmake版本高于3.3) 
   sudo apt-get install cmake   
    
    //cmake 需要安装在/usr/local目录下，需要超级权限
3. //安装必须的库文件 
   sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev libxt-dev 
   libXmu-dev libXi-dev zlib1g-dev libgl2ps-dev libexpat1-dev libxerces-c-dev 

4. sudo apt-get install libqt4-dev libqt4-dbg libqt4-gui libqt4-sql 
   qt4-dev-tools qt4-doc qt4-designer qt4-qtconfig
    // 安装QT，用于可视化  （另一种安装方法：sudo apt-get install qt-sdk）
```


#### <font color=#FF00FF> Step2 - 安装xerces相关文件（在终端中分别执行下面命令）</font> 
```C++
// 这是GDML相关的库，安装geant4zh之前必须安装xerces文件
 
1. 下载源文件 xerces-c-3.1.1.tar.gz, 解压    
  //下载网址：http://xerces.apache.org/xerces-c/download.cgi #自行选择版本 
2. 进入解压后的文件夹 xerces-c-3.1.1后，打开终端，执行：
    2.1 ./configure     //如果编译通过，执行下一步命令
    2.2 make            //这一步需要等一会儿，结束之后，执行下一步
    2.3 make install   
    2.4 设置环境变量：将下列语句输入root安装过程中的env.sh文件中 //（以下几行语句是通用的）
        ##for xerces-c-3.1.1
        export XERCESC_LIBRARY=/usr/local/lib
        export XERCESC_INCLUDE_DIR=/usr/local/include/xercesc
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

```

#### <font color=#FF00FF> Step3 - 开始安装geant4 (cmake 安装方法) </font>
 ```C++
1. 在CERN官网下载geant4源文件（选择自己需要的版本，比如：geant4.10.03.p01），
    下载到指定文件夹，并解压：比如我的路径：
    /home/gfh16/Packages/GEANT4/geant4.10.03.p01

2. 在geant4.10.03.p01相同的目录下，创建新文件夹 geant4.10.03.p01-build, 
    进入其中，执行下面的命令：
    cmake -DCMAKE_INSTALL_PREFIX=/home/gfh16/Packages/GEANT4/geant4.10.03.p01 
    -install -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_QT=ON GEANT4_BUILD_MULTITHREADED=ON 
    -DGEANT4_USE_GDML=ON  -DGEANT4_INSTALL_DATA=OFF  ../geant4.10.03.p01
   // geant4.10.03.p01-install是新创建的文件夹，后续步骤中将geant4安装到此文件夹中
   //-DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_GDML=ON 几个建议选择ON 
   //-DGEANT4_INSTALL_DATA=OFF 如果选择ON, 在安装过程中会自动下载数据包，安装过程十分缓慢
   // 建议选择OFF, 之后手动下载需要的数据包，然后添加到指定位置就可以了

3. make -jn    // n 是指用上电脑的几个核， 在新终端中查看：cat /proc/cpuinfo |grep "processor"|sort -u|wc -l 

4. make install    // 将geant4安装到（2）中创建的geant4.10.03.p01-build文件夹中

5. 设置环境变量:在env.sh文件中输入
    // for Geant4.10.3.p01// for /home/gfh16/Geant4
    export Geant4_10_3_path=/home/gfh16/Packages/GEANT4/geant4.10.03.p01-install 
          // 这里的绝对路径以你实际安装的路径为准
    source $Geant4_10_3_path/bin/geant4.sh
    source $Geant4_10_3_path/share/Geant4-10.3.1/geant4make/geant4make.sh
    
6. 使配置好的环境变量生效,需要在.bashrc文件中加入一条语句：
   source /home/gfh16/Packages/env.sh  
   //在主文件夹下"Ctrl+H" 可显示.bashrc

// 环境变量配置举例
// 来源与 /data/WorkEnvironment.sh (小秦智)
{
  alias useGeant4="source /data/CEE/NEW/fairsoft_may18p1_root6/installation/bin/geant4.sh"
  alias useROOT="source /data/CEE/NEW/fairsoft_may18p1_root6/installation/bin/thisroot.sh"

  # Recommend useFROOT(not useROOT) for ROOT because of some library installed in FairSoft not ROOT
  alias useFROOT="source /data/CEE/NEW/fairroot_v18.0.6-fairsoft_may18p1_root6/bin/FairRootConfig.sh"

  export CEE_dir="/data/CEE/NEW/CeeRoot"
  export ROOTEX_dir="/data/CEE/NEW/fairsoft_may18p1_root6/installation/share/doc/root/tutorials"
  export G4EX_dir="/data/CEE/NEW/fairsoft_may18p1_root6/installation/share/Geant4-10.4.1/examples"
  export FROOT_Template_dir="/data/CEE/NEW/fairroot_src_v18.0.6-fairsoft_may18p1_root6/templates/project_template"

  export GARFIELD_HOME="/data/CEE/NEW/garfield"
  alias usegarfield=". /data/CEE/NEW/garfield/build/setup.sh"    
}
 ```
 

#### <font color=#FF00FF> Step4 - 添加必要的数据包 </font>
```C++
1. 在http://geant4.web.cern.ch/geant4/support/download.shtml上下载Date file(*)  
// 一定一定要注意，不同的版本不兼容，要找到你在安装的geant4版本下的数据包
// 建议将上面所有的数据包都下载

2. 在文件夹 /home/gfh16/Packages/GEANT4/geant4.10.03.p01-install/share/Geant4-10.3.1/ 
   下新建文件夹 data , 将下好的数据包复制到这里并解压
```
 
#### <font color=#FF00FF> Step5 - 运行一个例子 </font>
```C++
1.新建一个目录, 作为 geant4 的工作目录. 用于编译、运行 geant4 的例子. 
    gfh@enpg~$： mkdir geant4
    gfh@enpg~$： cd geant4

2.将想要运行的 geant4 例子复制到 /home/gfh/gean4/
    gfh@enpg~/geant4$ cp $EXAMPLEENVIRONMENT/B1 .
    gfh@enpg~/geant4$ cd B1

3.在 B1/ 目录下新建 build/ 目录, 将在此目录下编译
    gfh@enpg~/geant4/B1$ mkdir build
    gfh@enpg~/geant4/B1$ cd build

4.编译前, 先加载环境变量 (否则可能编译出错！)
    gfh@enpg~/geant4/B1/build$ source /data/WorkEnvironment.sh
    gfh@enpg~/geant4/B1/build$ useGeant4

5.进入 build/ 目录进行编译, 
    // cmake dir, dir 为 CMakeList.txt, 编译生成 makefile
    gfh@enpg~/geant4/B1/build$ cmake .. 
    gfh@enpg~/geant4/B1/build$ make -jN

6.运行粒子
    gfh@enpg~/geant4/B1/build$ ./exampleB1


7.举例: run 100 electrons of 1 GeV energy
    /gun/particle e-
    /gun/energy 1 GeV
    /run/beamOn 100
```




## <font color=#DC143C> 一. Geant4 基础 -- 入门介绍 </font>

## <font color=#DC143C> 二. Geant4 功能 -- 内容详解 </font>

## <font color=#DC143C> 三. Geant4 例子 -- 从零基础开始 </font>