###oooooooo0000ooooooooo 此文档用于Ubuntu配置软件更新源和更新镜像  ooooooo0000oooooooo

0、联网
1、首先备份Ubuntu源列表
    sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup
    
    或者   cd /etc/apt/  
           sudo cp sources.list sources.list.bak 
2、打开更新源列表
    sudo gedit /etc/apt/sources.list  

3、选择更新源地址
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
    
    把上面的地址“全部“”复制到sources.list中。可根据个人情况选择更新源，个人觉得重庆大学更新源速度比较快，而且有各个版本ubuntu的更新源，比较推荐
    
4、 更新源列表信息：    sudo apt-get update  
    必须执行这一步骤，在执行这一步时如有提示错误，则找到相关内容将其注释掉（可能会出现网站无法连接的情况，将相关网站注释掉即可），想省事儿可以在第三步把 sources.list中内容全部删除，然后将需要的更新源的地址复制进去即可。若在软件更新界面为刷新，可以尝试重启
