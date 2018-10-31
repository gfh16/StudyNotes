$$$$$$ How to install ROOT $$$$$$


 
 #####安装前需要的软件包####
 #####打开官网 https://root.cern.ch/build-prerequisites#ubuntu 
     
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

