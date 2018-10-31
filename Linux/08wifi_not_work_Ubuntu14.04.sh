
####  Ubuntu14.04 链接不了wifi，是因为内核版本太低   #########

解决方法如下：

1、打开 
   https://askubuntu.com/questions/858546/wifi-not-working-intel-on-hp-spectre-x360-13
   
2、将里面的4个链接包安装上
    （1） 下载到自定义的位置，如 /home/Softwares
    （2） 安装： 
         cd /home/Softwares
         sudo dpkg -i filename
         
   #######说明，连接中第四个安装包链接失效，自行下载linux-firmware_1.169.2_all.deb 即可
         
3、重启电脑即可
