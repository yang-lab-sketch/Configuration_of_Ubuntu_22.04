# Ubuntu22.04双系统安装及开发环境配置详细教程

***——yang-lab-sketch***

## 前言

在完成Ubuntu所有的系统安装和环境配置之后，我只总结出了一句话：Ubuntu不是乌托邦，这一整个过程和理想可以说是一点搭不上边！为了以后具有和我相同情况，即电脑很新，但为了适配队友或者协同开发者的开发环境而不得不安装Ubuntu22.04的人群，能够顺利完成，或者说只花个半天时间就能完成整个Ubuntu22.04的安装和环境配置，特地将我所有遇到的问题以及解决方案整理出来，帮助大家避雷

**接下来，让我们正式走进一位22.04 24.04 26.04全部尝试安装过的，被Ubuntu连续折腾三天的可怜人的经验之谈**

## 为什么选择Ubuntu22.04

经过各种版本的安装尝试，我不得不说现在是一个很尴尬的时间段，Ubuntu26.04刚刚出版，导致很多诸如TensorRT，DNN推理模块尚未发行适配于Ubuntu26.04的版本，我查阅了Ubuntu社区发现普遍对于用TensorRT等的22或24版本去适配Ubuntu26.04的效果都不佳；另一方面，Ubuntu24.04对于内核显卡适配度的审核更加严格，导致我的电脑连烧录好的Ubuntu24.04装都装不了了，好在，官方对于Ubuntu22.04仍然在进维护和升级，所以或许对于新电脑来说Ubuntu22.04才是最好的选择

## Ubuntu22.04的安装

基本的安装思路仿照<https://www.bilibili.com/video/BV1hL411r7p2>即可，各种细节相当详细了，但是需要注意的是，这个视频发布于2023年，与现如今相比，无论是显卡还是内核，都会出现部分不适配的情况，所以，**请认真阅读以下备注：**

- 视频中为Ubuntu22.04分配的内存是30G，但是根据我安装的经验而言，30G似乎不是很够用，这里建议有条件的话分配100G左右（如果你以后经常需要在Ubuntu中开发的话），没有特别充裕条件的话也尽可能分配40～50G

- 关于Ubuntu22.04的下载，由于Ubuntu官方已经出了26.04了，所以现在访问Ubuntu官网打开的界面，自然与视频中完全不同，需要去找到历史版本，以下链接提供了路径
<https://releases.ubuntu.com/22.04/?_gl=1*19ip6hm*_gcl_au*MTE4NTIyOTI0MS4xNzA3MTMxMDQx&_ga=2.149898549.2084151835.1707729318-1126754318.1683186906>
选择64-bit PC (AMD64) desktop image完成安装即可，当然为了防止后续网址进一步变动，核心的宗旨是要去找到**22.04.5**的版本而不是22.04，因为前者是6.80的内核，与新电脑内核更加匹配

- 关于视频中重启出现的limpus lite，我的几次尝试一般很少有第一遍重启就出现的，如果没有出现的话**不要乱点**，长按电源关机之后重启进入Windows再按照视频中的重启操作来一遍应该就会有了

- 点进limpus lite出现视频中的黑色界面的时候，不要急着enter，如果你的电脑和我一样是Nvidia的显卡的话，**直接enter包给你卡住的**，因为Ubuntu22.04默认的内核携带驱动是nouveau，对nviadia显卡支持不佳，图形化界面没法打开，后续安装nvidia闭源驱动会解决这个问题，但这个时候为了先进入Ubuntu，**请按以下步骤操作：**
  
  - 先点击e键，进入另一个黑色界面
  - 找到quiet splash字样，在后面加上nomodeset，形如：quiet splash nomodeset，告诉系统不要尝试用自带开源驱动去驱动nviadia显卡，能显示即可
  - 按F10，等个几秒就可以进入Ubuntu系统
  - 继续按照视频操作安装完成后系统会提示你重启，重启又会遇到一个黑色界面，重复点击e键及后续步骤进入（始终记得：**只要你还没有安装nvidia驱动，一定要加nomodeset**）

## Nviadia驱动安装

1. 请务必先对当前的系统版本和内核版本有一个掌握，执行以下命令
```bash
lsb_release -a #示例：可以看到自己的Ubuntu版本是22.04.5
uname -r       #示例：可以看到自己的内核是6.8.0--40--generic
```

2. 预先完成对软件安装包的升级和对驱动依赖的补全（当初我就在这个上面吃了亏，**如果不预先做一些更新和补全，有可能在安装驱动的时候会顺手帮你把内核也更新了，然后就会导致部分驱动没有被携带，比如我的网卡驱动就被落下了，升完级之后直接没网了**，但是不要紧，因为那个时候的我已经安详了，删掉系统重装一遍就好了）
```bash
sudo apt update
sudo apt update -y
sudo apt dist-upgrade -y
sudo reboot #注意，这个时候还没装驱动，重启依旧要nomodeset
```

3. 安装驱动并重启检验
```bash
sudo ubuntu-drivers autoinstall
sudo reboot
nvidia-smi #出现表状输出即成功
```

## VScode安装与基本的Markdown配置

1. 访问 <https://code.visualstudio.com/download>下载Linux版本的.deb文件，文件会默认下载在/下载文件夹

2. 打开终端，输入以下命令以进入下载文件夹：
```bash
cd ~/下载
```

3. 执行以下命令以完成vscode的安装：
```bash
sudo apt install ./code_*.deb
```
4. 为了完成一些记录，可以先完成最简单的MD插件配置：在插件商城下载Markdown All in One，Markdown Preview Enhanced，Markdown PDF，即可实现编辑，预览，导出一条龙

**备注一句：内存不够用但是要传文件的话不用下载微信，手机数据线就可以了**

## Ubuntu22.04 Clash配置——帮助你在小电脑里科学上网

1. 安装git，执行以下命令：
```bash
sudo apt update
sudo apt install git -y

# 安装完成之后检验git版本
git --version

# 信息初始化
git config --global user.name "yang-lab-sketch"
git config --global user.email "251880286@smail.nju.edu.cn"

# 信息检查
git config --global --list
```

2. 安装curl
```bash
sudo apt install curl
```

3. 安装clash
在一台已经具备clash代理能力的电脑，访问以下网址严格按照教程完成配置即可
<https://github.com/SaladDay/clash-for-lab>

4. firefox浏览器设置，打开浏览器，找到设置，找到网络设置，选择手动配置代理，在socks主机一栏填入27.0.0.1，端口7890，重启浏览器即可科学上网
   
## C/C++编译环境配置

### G++配置

1. 在VScode插件商店中搜索C/C++插件安装

2. 执行以下命令安装g++编译器
```bash
sudo apt install -y build-essential gdb
```

3. VScode中写一个测试cpp文件（注意crtl+s保存），crtl+`快捷键调出内置终端，执行cd命令进入当前工作目录，执行以下编译命令：
   
```bash
g++ test.cpp -o test #生成可执行文件
./test #运行输出结果
```

### CMake配置
只需执行以下命令即可完成安装：
```bash
sudo apt update
sudo apt install cmake
cmake --version #检查是否安装完成
```

**附：测试cmake——利用cmake完成对刚刚test.cpp文件的编译：**

1. 写CMakeLists.txt：
``` cmake
# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 工程名
project(test_project)

# 生成可执行文件
add_executable(test_app test.cpp)
``` 

2. 执行以下命令：
```bash
mkdir build
cd build
cmake ..
make
./test_app
```
 
## CUDA toolkit安装——实现GPU跑程序

1. 添加NVIDIA官方仓库
```bash
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-ubuntu2204.pin
sudo mv cuda-ubuntu2204.pin /etc/apt/preferences.d/cuda-repository-pin-600

wget https://developer.download.nvidia.com/compute/cuda/12.1.0/local_installers/cuda-repo-ubuntu2204-12-1-local_12.1.0-530.30.02-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu2204-12-1-local_12.1.0-530.30.02-1_amd64.deb
sudo cp /var/cuda-repo-ubuntu2204-12-1-local/cuda-*-keyring.gpg /usr/share/keyrings/

sudo apt update
```

2. 安装CUDA toolkit（不重装驱动）
```bash
sudo apt install -y cuda-toolkit-12-1
```

3. 配置环境变量
```bash
export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
```

4. 生效
```bash
source ~/.bashrc
```

5. 检验
```bash
nvcc --version
```

## cuDNN安装
1. 执行以下命令：
```bash
# 1. 下载官方 cuda-keyring（network repo 凭证）
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.1-1_all.deb
sudo dpkg -i cuda-keyring_1.1-1_all.deb

# 2. （可选但推荐）保留 pin 保证优先级
echo "Package: *
Pin: origin \"developer.download.nvidia.com\"
Pin-Priority: 600" \
| sudo tee /etc/apt/preferences.d/cuda-repository-pin-600

# 3. 更新索引
sudo apt update
```

2. 安装：
```bash
sudo apt install -y libcudnn8 libcudnn8-dev
```

3. 检验：
```bash
dpkg -l | grep cudnn
apt-cache show libcudnn8 | grep Version #看到版本号即为成功
```

## TensorRT安装
```bash
sudo apt install -y \
  libnvinfer8=8.6.1.6-1+cuda12.0 \
  libnvinfer-dev=8.6.1.6-1+cuda12.0 \
  libnvinfer-headers-dev=8.6.1.6-1+cuda12.0 \
  libnvinfer-plugin8=8.6.1.6-1+cuda12.0 \
  libnvinfer-plugin-dev=8.6.1.6-1+cuda12.0 \
  libnvinfer-headers-plugin-dev=8.6.1.6-1+cuda12.0 \
  libnvonnxparsers8=8.6.1.6-1+cuda12.0 \
  libnvonnxparsers-dev=8.6.1.6-1+cuda12.0 \
  libnvparsers8=8.6.1.6-1+cuda12.0 \
  libnvparsers-dev=8.6.1.6-1+cuda12.0 \
  python3-libnvinfer=8.6.1.6-1+cuda12.0
```
检验：
```bash
ls /usr/include/NvInfer.h
dpkg -l | grep nvinfer | grep 8.6
```

## OpenCV环境配置
先记得安装python的必要依赖
```bash
sudo apt update
sudo apt install -y \
  python3-dev \
  python3-pip \
  python3-numpy
```
接下来执行的命令，虽然如果你严格按照我上面的步骤做下来的话应该问题不是很大，但考虑到安装OpenCV需要再安装需要检查哪些内容，依次检查好之后一定时间成本，**依旧强烈建议先把以下命令给ai看，让它告诉你安装前需要检查哪些内容**
```bash
# 下载 OpenCV 4.12 源码
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.12.0.zip
wget -O opencv_contrib.zip
https://github.com/opencv/opencv_contrib/archive/4.12.0.zip
unzip opencv.zip && unzip opencv_contrib.zip

# 编译安装
cd opencv-4.12.0
mkdir -p build && cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-4.12.0/modules \
-D WITH_CUDA=ON \
-D WITH_CUDNN=ON \
-D WITH_TENSORRT=ON \
-D OPENCV_DNN_CUDA=ON \
-D CUDA_ARCH_BIN=8.7 \
-D WITH_TBB=ON \
-D WITH_V4L=ON \
-D WITH_GSTREAMER=ON \
-D WITH_OPENGL=ON \
-D BUILD_SHARED_LIBS=ON \
-D BUILD_opencv_python3=ON \
-D BUILD_TESTS=OFF \
-D BUILD_PERF_TESTS=OFF \
-D BUILD_EXAMPLES=OFF \
-D BUILD_DOCS=OFF \
-D BUILD_JAVA=OFF \
-D BUILD_opencv_java=OFF \
-D BUILD_opencv_js=OFF \
-D BUILD_opencv_apps=OFF \
..

make -j$(nproc)
sudo make install

# 验证安装
python3 -c "import cv2; print(cv2.__version__)"
```
## ROS环境配置
```bash
# 使用鱼香 ROS 一键安装脚本（推荐 Humble，适配 Ubuntu 22.04）
wget http://fishros.com/install -O fishros && bash fishros
```

## 补充（针对OpenCV）：其他开发相关依赖配置
```bash
sudo apt install -y python3.10 python3.10-dev python3-pip
sudo apt install -y libeigen3-dev
sudo apt install -y build-essential cmake git pkg-config \
libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev \
libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev \
libtiff-dev gfortran openexr libatlas-base-dev \libtbb2 libtbb-dev libopenexr-dev libgstreamer-plugins-base1.0-dev \
libgstreamer1.0-dev
```