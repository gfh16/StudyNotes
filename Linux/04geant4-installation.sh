#####$$$$  geant4安装说明  $$$########
##### 我自己装了geant4.9.6.p03不下十遍，但每次都出现各种问题，于是就决定安装了现在的
##### geant4.10.03.p01 版本，在黎明师兄的帮助下，终于成功了   ##########

&&关分海写于2017年5月12日，清华园&&  


&&& installation steps  &&

1、安装前的准备（在终端中分别执行下面命令）

 (1) sudo apt-get install build-essential  ##  安装gcc等编译程序
 (2) sudo apt-get install cmake   

     ##安装cmake(要注意cmake的版本要求，geant4.10.03.p01 版本要求cmake版本高于3.3)
     ##cmake 需要安装在/usr/local目录下，需要超级权限
 (3) sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev libxt-dev libXmu-dev libXi-dev zlib1g-dev libgl2ps-dev libexpat1-dev libxerces-c-dev        ### 安装必须的库文件
 (4) sudo apt-get install libqt4-dev libqt4-dbg libqt4-gui libqt4-sql qt4-dev-tools qt4-doc qt4-designer qt4-qtconfig
                      ### 安装QT，用于可视化  （另一种安装方法：sudo apt-get install qt-sdk）
  
2、安装xerces相关文件 （在终端中分别执行下面命令） ## 这是GDML相关的库，安装geant4zh之前必须安装xerces文件
 
 (1) 下载源文件 xerces-c-3.1.1.tar.gz, 解压 ## 下载网址：http://xerces.apache.org/xerces-c/download.cgi ###  自行选择版本 ####
 (2) 进入解压后的文件夹 xerces-c-3.1.1后，打开终端，执行：
       <1> ./configure   ###如果编译通过，执行下一步命令
       <2> make          ### 这一步需要等一会儿，结束之后，执行下一步
       <3> make install  ### 
       <4> 设置环境变量：将下列语句输入root安装过程中的env.sh文件中 //（以下几行语句是通用的）
             ##for xerces-c-3.1.1
                export XERCESC_LIBRARY=/usr/local/lib
                export XERCESC_INCLUDE_DIR=/usr/local/include/xercesc
                export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
                
 3、开始安装geant4
 
 (1) 在CERN官网下载geant4源文件（选择自己需要的版本，比如：geant4.10.03.p01），下载到指定文件夹，并解压：
            比如我的路径：/home/gfh16/Packages/GEANT4/geant4.10.03.p01
 (2) 在geant4.10.03.p01相同的目录下，创建新文件夹 geant4.10.03.p01-build, 进入其中，执行下面的命令：
 
      cmake -DCMAKE_INSTALL_PREFIX=/home/gfh16/Packages/GEANT4/geant4.10.03.p01-install -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_QT=ON GEANT4_BUILD_MULTITHREADED=ON -DGEANT4_USE_GDML=ON  -DGEANT4_INSTALL_DATA=OFF  ../geant4.10.03.p01
      
         ####geant4.10.03.p01-install是新创建的文件夹，后续步骤中将geant4安装到此文件夹中
         ####-DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_GDML=ON 几个建议选择ON 
         #### -DGEANT4_INSTALL_DATA=OFF 如果选择ON, 在安装过程中会自动下载数据包，安装过程十分缓慢
         #### 建议选择OFF, 之后手动下载需要的数据包，然后添加到指定位置就可以了
 (3) make -jn ## n 是指用上电脑的几个核， 在新终端中查看：cat /proc/cpuinfo |grep "processor"|sort -u|wc -l 
 (4) make install  ### 将geant4安装到（2）中创建的geant4.10.03.p01-build文件夹中
 (5) 设置环境变量:在env.sh文件中输入
      ##for Geant4.10.3.p01// for /home/gfh16/Geant4
        export Geant4_10_3_path=/home/gfh16/Packages/GEANT4/geant4.10.03.p01-install ### 这里的绝对路径以你实际安装的路径为准
        source $Geant4_10_3_path/bin/geant4.sh
        source $Geant4_10_3_path/share/Geant4-10.3.1/geant4make/geant4make.sh
 (6) 使配置好的环境变量生效,需要在.bashrc文件中加入一条语句：source /home/gfh16/Packages/env.sh   ###在主文件夹下"Ctrl+H" 可显示.bashrc
 
 
 4、添加必要的数据包 ###数据包是必须的
 
 (1)在http://geant4.web.cern.ch/geant4/support/download.shtml上下载Date file(*)  
            ### 一定一定要注意，不同的版本不兼容，要找到你在安装的geant4版本下的数据包。建议将上面所有的数据包都下载
 (2)在文件夹 /home/gfh16/Packages/GEANT4/geant4.10.03.p01-install/share/Geant4-10.3.1/ 下新建文件夹 data , 将下好的数据包复制到这里并解压。
 
 
 
 5、运行一个例子，试试geant4是否安装成功
 
 (1) 从 /home/gfh16/Packages/GEANT4/geant4.10.03.p01/examples/basic/ 将 B1文件夹复制出来（复制到主文件夹下）
 (2) 在B1文件夹中新建 env.sh文件， 文件内容：
             #!/bin/bash
               export G4WORKDIR=$(pwd)
               echo  $G4WORKDIR
 (3) 在 B1中打开终端： ./env.sh   ### 如果出现权限不够，执行： chmod 777 ./env.sh  接着再执行：./env.sh
 (4) make   ## make 之后，在B1中生成bin文件夹，有时候生成的bin文件夹在 主文件夹下的 geant4_workdir中
 (5) make之后，将B1中的 vis.mac, int_vis.mac, run1.mac, run2.mac 等文件复制到 bin/linux-g++中
 (6) 在 bin/linux-g++ 中打开终端， 执行：./exampleB1
 (7) 成功啦啦啦 
