<div style="text-align: left">
<font face="微软雅黑" size=5 color=#FF00FF>
  小关的读书笔记
</font> 
</div>



<center>Linux 基础</center>
=================================



目录
--------
[toc]

-------------------------------------
# <font color=#DC143C> Linux 基础功能 </font>

## <font color=#00BFFF> vim 的使用 </font>
[如何配置.vimrc文件](https://www.cnblogs.com/vitasyuan/p/9650637.html)




--------------------------------------------------------------
# <font color=#DC143C>  Linux 下一些有用的使用技巧 </font>

### <font color=#00BFFF> 在Ubuntu下右键打开当前目录下的终端 </font>
```C++
sudo apt-get install nautilus-open-terminal 
sudo apt-get install nautilus - gksu
nautilus -q

```

### <font color=#00BFFF> 解决Ubuntu14.04中wifi不工作 </font>
```C++
1. 打开网址：<https://askubuntu.com/questions/858546/wifi-not-working-intel-on-hp-spectre-x360-13>
2. 将里面的4个链接包安装上
   2.1 下载到自定义的位置，如 /home/Softwares
   2.2 解压即可安装
        cd /home/Softwares
        sudo dpkg -i filename
// 如连接中第四个安装包链接失效，自行下载linux-firmware_1.169.2_all.deb 即可
3. 重启电脑
```


### <font color=#00BFFF> Ubuntu 看不了视频的问题 </font>
[链接：解决方法](https://askubuntu.com/questions/502207/ubuntu-14-04-problem-when-install-gstreamer1-0-libav-unmet-dependencies)
```C++
1. sudo apt-get install libopus0
2. 然后双击视频，然后就可以直接安装相关的软件包
```

### <font color=#00BFFF> 更改镜像源 </font>
```C++
1. 联网
2. 首先备份Ubuntu源列表
   sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup
   或者 
   cd /etc/apt/  
   sudo cp sources.list sources.list.bak 

3. 打开更新源列
   sudo gedit /etc/apt/sources.list 

4. 选择更新源地址
   可将更新源地址复制到 sources.list中去（注意文件权限），例如重庆大学源地址（代码）如下：
   deb http://mirrors.cqu.edu.cn/ubuntu/ trusty main restricted universe multiverse  
   deb http://mirrors.cqu.edu.cn/ubuntu/ trusty-security main restricted universe multiverse  
   deb http://mirrors.cqu.edu.cn/ubuntu/ trusty-updates main restricted universe multiverse  
   deb http://mirrors.cqu.edu.cn/ubuntu/ trusty-proposed main restricted universe multiverse  
   deb http://mirrors.cqu.edu.cn/ubuntu/ trusty-backports main restricted universe multiverse  
   deb-src http://mirrors.cqu.edu.cn/ubuntu/ trusty main restricted universe multiverse  
   deb-src http://mirrors.cqu.edu.cn/ubuntu/ trusty-security main restricted universe multiverse  
   deb-src http://mirrors.cqu.edu.cn/ubuntu/ trusty-updates main restricted universe multiverse  
   deb-src http://mirrors.cqu.edu.cn/ubuntu/ trusty-proposed main restricted universe multiverse  
   deb-src http://mirrors.cqu.edu.cn/ubuntu/ trusty-backports main restricted universe multiverse  
    
把上面的地址“全部“”复制到sources.list中。可根据个人情况选择更新源，个人觉得重庆大学
更新源速度比较快，而且有各个版本ubuntu的更新源，比较推荐
    
5. 更新源列表信息：  sudo apt-get update  
   //必须执行这一步骤，在执行这一步时如有提示错误，则找到相关内容将其注释掉
   //（可能会出现网站无法连接的情况，将相关网站注释掉即可），想省事儿可以在第三步把
   //sources.list中内容全部删除，然后将需要的更新源的地址复制进去即可。若在软件更新界面为刷新，可以尝试重启
```


### <font color=#00BFFF> Linux 下连接校内服务器 </font>
```C++
1.安装 openconnect
$ sudo apt install openconnect

2.下载http://www.infradead.org/openconnect/vpnc-script.html提供
   的vpnc-script,并复制到/etc/vpnc/vpnc-script
$ wget http://git.infradead.org/users/dwmw2/vpnc-scripts.git/blob_plain/HEAD:/vpnc-script
$ sudo cp vpnc-script /etc/vpnc/vpnc-script

3.连接校园网
$ sudo openconnect --juniper -u [学号] [sslvpn url]
# 如 sudo openconnect --juniper -u 20xxxxxxxx https://sslvpn.tsinghua.edu.cn/

4.之后会要求输入密码，没有报错并最终显示类似ESP session established with serve,
  表明校园网连接成功.

5.打开新的窗口, 登录服务器 (ENPG的服务器)
$ ssh -X username@166.111.26.233


// 外网访问 ENPG 服务器
ssh -X -p 4869 username@166.111.26.233
```