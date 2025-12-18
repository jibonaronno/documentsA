[linux-devkit]:~> arm-linux-gnueabihf-
arm-linux-gnueabihf-addr2line     arm-linux-gnueabihf-gcc-ar        arm-linux-gnueabihf-gprof
arm-linux-gnueabihf-ar            arm-linux-gnueabihf-gcc-ar-7      arm-linux-gnueabihf-ld
arm-linux-gnueabihf-as            arm-linux-gnueabihf-gcc-nm        arm-linux-gnueabihf-ld.bfd
arm-linux-gnueabihf-c++filt       arm-linux-gnueabihf-gcc-nm-7      arm-linux-gnueabihf-ld.gold
arm-linux-gnueabihf-cpp           arm-linux-gnueabihf-gcc-ranlib    arm-linux-gnueabihf-nm
arm-linux-gnueabihf-cpp-7         arm-linux-gnueabihf-gcc-ranlib-7  arm-linux-gnueabihf-objcopy
arm-linux-gnueabihf-dwp           arm-linux-gnueabihf-gcov          arm-linux-gnueabihf-objdump
arm-linux-gnueabihf-elfedit       arm-linux-gnueabihf-gcov-7        arm-linux-gnueabihf-ranlib
arm-linux-gnueabihf-g++           arm-linux-gnueabihf-gcov-dump     arm-linux-gnueabihf-readelf
arm-linux-gnueabihf-g++-7         arm-linux-gnueabihf-gcov-dump-7   arm-linux-gnueabihf-size
arm-linux-gnueabihf-gcc           arm-linux-gnueabihf-gcov-tool     arm-linux-gnueabihf-strings
arm-linux-gnueabihf-gcc-7         arm-linux-gnueabihf-gcov-tool-7   arm-linux-gnueabihf-strip
arm-linux-gnueabihf-gcc-7.2.1     arm-linux-gnueabihf-gdb
[linux-devkit]:~> sudo apt install libncurses5-dev
[sudo] password for jibon:
Reading package lists... Done
Building dependency tree
Reading state information... Done
The following packages were automatically installed and are no longer required:
  amd64-microcode intel-microcode iucode-tool linux-generic-hwe-18.04 linux-headers-generic-hwe-18.04
  linux-image-generic-hwe-18.04 thermald
Use 'sudo apt autoremove' to remove them.
The following additional packages will be installed:
  libtinfo-dev
Suggested packages:
  ncurses-doc
The following NEW packages will be installed:
  libncurses5-dev libtinfo-dev
0 upgraded, 2 newly installed, 0 to remove and 51 not upgraded.
Need to get 256 kB of archives.
After this operation, 1,423 kB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 http://kr.archive.ubuntu.com/ubuntu bionic-updates/main amd64 libtinfo-dev amd64 6.1-1ubuntu1.18.04.1 [81.4 kB]
Get:2 http://kr.archive.ubuntu.com/ubuntu bionic-updates/main amd64 libncurses5-dev amd64 6.1-1ubuntu1.18.04.1 [174 kB]
Fetched 256 kB in 3s (83.6 kB/s)
Selecting previously unselected package libtinfo-dev:amd64.
(Reading database ... 203394 files and directories currently installed.)
Preparing to unpack .../libtinfo-dev_6.1-1ubuntu1.18.04.1_amd64.deb ...
Unpacking libtinfo-dev:amd64 (6.1-1ubuntu1.18.04.1) ...
Selecting previously unselected package libncurses5-dev:amd64.
Preparing to unpack .../libncurses5-dev_6.1-1ubuntu1.18.04.1_amd64.deb ...
Unpacking libncurses5-dev:amd64 (6.1-1ubuntu1.18.04.1) ...
Setting up libtinfo-dev:amd64 (6.1-1ubuntu1.18.04.1) ...
Setting up libncurses5-dev:amd64 (6.1-1ubuntu1.18.04.1) ...
Processing triggers for man-db (2.8.3-2ubuntu0.1) ...
[linux-devkit]:~> sudo apt install libssl-dev
Reading package lists... Done
Building dependency tree
Reading state information... Done
The following packages were automatically installed and are no longer required:
  amd64-microcode intel-microcode iucode-tool linux-generic-hwe-18.04 linux-headers-generic-hwe-18.04
  linux-image-generic-hwe-18.04 thermald
Use 'sudo apt autoremove' to remove them.
Suggested packages:
  libssl-doc
The following NEW packages will be installed:
  libssl-dev
0 upgraded, 1 newly installed, 0 to remove and 51 not upgraded.
Need to get 1,568 kB of archives.
After this operation, 7,854 kB of additional disk space will be used.
Get:1 http://kr.archive.ubuntu.com/ubuntu bionic-updates/main amd64 libssl-dev amd64 1.1.1-1ubuntu2.1~18.04.23 [1,568 kB]
Fetched 1,568 kB in 3s (514 kB/s)
Selecting previously unselected package libssl-dev:amd64.
(Reading database ... 203443 files and directories currently installed.)
Preparing to unpack .../libssl-dev_1.1.1-1ubuntu2.1~18.04.23_amd64.deb ...
Unpacking libssl-dev:amd64 (1.1.1-1ubuntu2.1~18.04.23) ...
Setting up libssl-dev:amd64 (1.1.1-1ubuntu2.1~18.04.23) ...
[linux-devkit]:~> sudo apt install bc
Reading package lists... Done
Building dependency tree
Reading state information... Done
bc is already the newest version (1.07.1-2).
The following packages were automatically installed and are no longer required:
  amd64-microcode intel-microcode iucode-tool linux-generic-hwe-18.04 linux-headers-generic-hwe-18.04
  linux-image-generic-hwe-18.04 thermald
Use 'sudo apt autoremove' to remove them.
0 upgraded, 0 newly installed, 0 to remove and 51 not upgraded.
[linux-devkit]:~> sudo apt install parted
Reading package lists... Done
Building dependency tree
Reading state information... Done
parted is already the newest version (3.2-20ubuntu0.2).
parted set to manually installed.
The following packages were automatically installed and are no longer required:
  amd64-microcode intel-microcode iucode-tool linux-generic-hwe-18.04 linux-headers-generic-hwe-18.04
  linux-image-generic-hwe-18.04 thermald
Use 'sudo apt autoremove' to remove them.
0 upgraded, 0 newly installed, 0 to remove and 51 not upgraded.
[linux-devkit]:~> sudo apt install libusb-1.0-0-de
Reading package lists... Done
Building dependency tree
Reading state information... Done
Note, selecting 'libusb-1.0-0-dev' for regex 'libusb-1.0-0-de'
The following packages were automatically installed and are no longer required:
  amd64-microcode intel-microcode iucode-tool linux-generic-hwe-18.04 linux-headers-generic-hwe-18.04
  linux-image-generic-hwe-18.04 thermald
Use 'sudo apt autoremove' to remove them.
The following additional packages will be installed:
  libusb-1.0-doc
The following NEW packages will be installed:
  libusb-1.0-0-dev libusb-1.0-doc
0 upgraded, 2 newly installed, 0 to remove and 51 not upgraded.
Need to get 230 kB of archives.
After this operation, 1,774 kB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 http://kr.archive.ubuntu.com/ubuntu bionic/main amd64 libusb-1.0-0-dev amd64 2:1.0.21-2 [60.5 kB]
Get:2 http://kr.archive.ubuntu.com/ubuntu bionic/main amd64 libusb-1.0-doc all 2:1.0.21-2 [170 kB]
Fetched 230 kB in 3s (83.9 kB/s)
Selecting previously unselected package libusb-1.0-0-dev:amd64.
(Reading database ... 203560 files and directories currently installed.)
Preparing to unpack .../libusb-1.0-0-dev_2%3a1.0.21-2_amd64.deb ...
Unpacking libusb-1.0-0-dev:amd64 (2:1.0.21-2) ...
Selecting previously unselected package libusb-1.0-doc.
Preparing to unpack .../libusb-1.0-doc_2%3a1.0.21-2_all.deb ...
Unpacking libusb-1.0-doc (2:1.0.21-2) ...
Setting up libusb-1.0-doc (2:1.0.21-2) ...
Setting up libusb-1.0-0-dev:amd64 (2:1.0.21-2) ...
[linux-devkit]:~>
[linux-devkit]:~>
[linux-devkit]:~>
[linux-devkit]:~> ls
examples.desktop  jupyters  pdasource
[linux-devkit]:~> mkdir radxa
[linux-devkit]:~> cd radxa/
[linux-devkit]:~/radxa> ls
[linux-devkit]:~/radxa> wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.18.11.tar.xz
--2025-04-01 11:37:01--  https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.18.11.tar.xz
Resolving www.kernel.org (www.kernel.org)... 151.101.1.55, 151.101.193.55, 151.101.65.55, ...
Connecting to www.kernel.org (www.kernel.org)|151.101.1.55|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 80956324 (77M) [application/x-xz]
Saving to: ‘linux-3.18.11.tar.xz’

linux-3.18.11.tar.xz             100%[=========================================================>]  77.21M  33.1MB/s    in 2.3s

2025-04-01 11:37:10 (33.1 MB/s) - ‘linux-3.18.11.tar.xz’ saved [80956324/80956324]

[linux-devkit]:~/radxa> ls
linux-3.18.11.tar.xz
[linux-devkit]:~/radxa> tar xf linux-3.18.11.tar.xz
[linux-devkit]:~/radxa> ls
linux-3.18.11  linux-3.18.11.tar.xz
[linux-devkit]:~/radxa> cd linux-3.18.11/
[linux-devkit]:~/radxa/linux-3.18.11> wget http://rockchip.fr/radxa/linux/rockchip_defconfig -O arch/arm/configs/rockchip_defconfig
--2025-04-01 11:38:16--  http://rockchip.fr/radxa/linux/rockchip_defconfig
Resolving rockchip.fr (rockchip.fr)... 146.88.234.19
Connecting to rockchip.fr (rockchip.fr)|146.88.234.19|:80... connected.
HTTP request sent, awaiting response... 302 Found
Location: https://rockchip.fr/radxa/linux/rockchip_defconfig [following]
--2025-04-01 11:38:17--  https://rockchip.fr/radxa/linux/rockchip_defconfig
Connecting to rockchip.fr (rockchip.fr)|146.88.234.19|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 6319 (6.2K)
Saving to: ‘arch/arm/configs/rockchip_defconfig’

arch/arm/configs/rockchip_defcon 100%[=========================================================>]   6.17K  --.-KB/s    in 0s

2025-04-01 11:38:19 (3.42 GB/s) - ‘arch/arm/configs/rockchip_defconfig’ saved [6319/6319]

[linux-devkit]:~/radxa/linux-3.18.11> ls
arch     CREDITS        drivers   include  Kbuild   lib          mm      REPORTING-BUGS  security  usr
block    crypto         firmware  init     Kconfig  MAINTAINERS  net     samples         sound     virt
COPYING  Documentation  fs        ipc      kernel   Makefile     README  scripts         tools
[linux-devkit]:~/radxa/linux-3.18.11> wget http://rockchip.fr/radxa/linux/rk3188-radxarock.dts -O arch/arm/boot/dts/rk3188-radxarock.dts
--2025-04-01 11:39:18--  http://rockchip.fr/radxa/linux/rk3188-radxarock.dts
Resolving rockchip.fr (rockchip.fr)... 146.88.234.19
Connecting to rockchip.fr (rockchip.fr)|146.88.234.19|:80... connected.
HTTP request sent, awaiting response... 302 Found
Location: https://rockchip.fr/radxa/linux/rk3188-radxarock.dts [following]
--2025-04-01 11:39:19--  https://rockchip.fr/radxa/linux/rk3188-radxarock.dts
Connecting to rockchip.fr (rockchip.fr)|146.88.234.19|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 8840 (8.6K) [audio/vnd.dts]
Saving to: ‘arch/arm/boot/dts/rk3188-radxarock.dts’

arch/arm/boot/dts/rk3188-radxaro 100%[=========================================================>]   8.63K  --.-KB/s    in 0s
2025-04-01 11:39:21 (281 MB/s) - ‘arch/arm/boot/dts/rk3188-radxarock.dts’ saved [8840/8840]
## ALREADY DONE [linux-devkit]:~/radxa/linux-3.18.11> wget http://rockchip.fr/radxa/linux/rk3188-radxarock.dts -O arch/arm/boot/dts/rk3188-radxarock.dts
[linux-devkit]:~/radxa/linux-3.18.11> export ARCH=arm
[linux-devkit]:~/radxa/linux-3.18.11> export CROSS_COMPILE=arm-linux-gnueabihf-
[linux-devkit]:~/radxa/linux-3.18.11> cp arch/arm/configs/rockchip_defconfig .config
[linux-devkit]:~/radxa/linux-3.18.11> make menuconfig