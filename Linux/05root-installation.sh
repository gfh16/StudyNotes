$$$$$$ How to install ROOT $$$$$$



 #####安装前需要的软件包####
 #####打开官网 https://root.cern.ch/build-prerequisites#ubuntu

===========================
Method 1: 使用 make 方法安装
===========================

(1) sudo apt-get install git dpkg-dev cmake g++ gcc binutils libx11-dev libxpm-dev  libxft-dev libxext-dev
         ###安装 Required packages
(2) sudo apt-get install gfortran libssl-dev libpcre3-dev xlibmesa-glu-dev libglew1.5-dev libftgl-dev
              libmysqlclient-dev libfftw3-dev libcfitsio-dev  graphviz-dev libavahi-compat-libdnssd-dev
              libldap2-dev python-dev libxml2-dev libkrb5-dev libgsl0-dev libqt4-dev
         #### 安装Optional packages  ###  libcfitsio-dev可能出错，则改为libcfitsio3-dev
(3) 下载需要的ROOT版本，https://root.cern.ch/releases
    解压到指定文件夹，比如：/home/gfh16/Packages/root/

(4)  ./configure   ##在/home/gfh16/Packages/root/ 下打开终端
     （或者 ./configure --all  ### 安装更多的功能）
(5) make -j4   ### jn 根据自己的电脑情况而定  ### 这一步可能需要等很长时间
(6) 配置环境变量： source /home/gfh16/Packages/root/bin/thisroot.sh 添加到 .bashrc文件中
(7) 安装成功




============================
Method 2: 使用 cmake 方法安装
============================

(1) 与上同
(2) 与上同
(3) 下载需要的ROOT版本：https://root.cern.ch/releases
    需要注意几个问题：
    <1> root 版本有source版本(源代码)、binary版本。一定要下载source版
    <2> ubuntu18.04, ubuntu16.04, ubuntu14.04 对root版本要求不一样，要
        选择配套的root版本
(4) 如下载：root_v6.18.00.source.tar.gz
    解压： tar zxvf root_v6.18.00.source.tar.gz
    解压后自动生成文件：root_v6.18.00.source

(5) 在root_v6.18.00.source所在的路径新建文件夹，用来安装root;进入新建文件夹：
    mkdir root_install
    cd root_install

(6) cmake ../root_v6.18.00.source/

(7) cmake --build . -- -jN      // N is the number of available cores

(8) 设置环境变量：source /home/sea/Packages/root6.18/root_install/bin/thisroot.sh
