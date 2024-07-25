
============================================ 
	  Upgrade Image Maker 
============================================ 
model name invlid!! >> /home/jibon/pro
TOTAL RFS PARTS=0
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=RFS, PRODUCT_NAME=SHUR, VERSION=/home/jibon/tftpboot 	TARGET_DIR=AM5718, MODEL_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver, PLATFORM=, VERSION_FILE_NAME=
Target Image Make Finish!!
[1]-  Done                    gedit bsp/target-maker/tools/binarymaker/mkbin.c
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ ls
application  bsp  BuildScript.sh  complete.sh  Makefile  ProductSW.sh  Rules.make  start.sh  TagBuildTree.sh  version
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ source ./start.sh 
chmod: cannot access 'application/61850-code/cmd/gnu/mmslite802.sh': No such file or directory
chmod: cannot access 'application/61850-code/bin/foundry_ld': No such file or directory
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cat start.sh 
#!/bin/bash

export PATH="/opt/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"

chmod -R 777 application/61850-code/cmd/gnu/mmslite802.sh
chmod -R 777 application/61850-code/bin/foundry_ld
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ ls /opt/
ti-processor-sdk-linux-rt-am57xx-evm-05.02.00.10  ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ clear

jibon@PDABUILD:~/projects/sur5000/sur5000_top$ ls
application  bsp  BuildScript.sh  complete.sh  Makefile  ProductSW.sh  Rules.make  start.sh  TagBuildTree.sh  version
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make target IMG=RFS

============================================
Building the Target Image
============================================

USEAGE:
# make target IMG=APP

IMG TYPE: ALL / BOOT / KL / APP / UP / RFS / PLATFORM / ALL-RFS
VERSION_PATH=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Nand Page Size: 2K (2048)
remove ./output_img files

Copying  Image  from ./output_img
Build Target Image...
build_ext4 RFS
Generate RFS from ./rootfs_temp
2457600+0 records in
2457600+0 records out
2516582400 bytes (2.5 GB, 2.3 GiB) copied, 7.38709 s, 341 MB/s
mke2fs 1.44.1 (24-Mar-2018)
Discarding device blocks: done                            
Creating filesystem with 614400 4k blocks and 153824 inodes
Filesystem UUID: f79b9d47-a921-4254-a74e-d6eecba97ef6
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done 

build_jffs APP
Generate APP from ./app_temp
Make Binary Image...

UPdate File Version: V 000

============================================ 
	  Upgrade Image Maker 
============================================ 
model name invlid!! >> /home/jibon/pro
TOTAL RFS PARTS=0
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=RFS, PRODUCT_NAME=SHUR, VERSION=/home/jibon/tftpboot 	TARGET_DIR=AM5718, MODEL_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver, PLATFORM=, VERSION_FILE_NAME=
Target Image Make Finish!!
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cat $TARGET
^C
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ echo $TARGET

jibon@PDABUILD:~/projects/sur5000/sur5000_top$ echo $TARGET_DIR

jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cat Rules.make 
##################################################################
############################# SANION #############################
##################################################################
#Development Name
PRODUCT_NAME=SHUR

#FPGA Name
FPGA_NAME=FPGA_HUR_MDCU_A.bin

# Process Model Name
MODEL_NAME=AM5718

#platform
PLATFORM=am57xx-evm

#UR IED Master Path
export MASTER_PATH=$(shell pwd)

# Binary File Update DIR
#SERVER_DIR=$(MASTER_PATH)/FW

#Version Path
VERSION_PATH=$(MASTER_PATH)/version/$(PRODUCT_NAME).ver

#defconfig
#DEFCONFIG=tisdk_am57xx-evm-rt_defconfig
#DEFCONFIG=UR_JOHN_AM5718_RT_defconfig
DEFCONFIG=SANION-HUR_defconfig

#Architecture
ARCH=armv7-a

#u-boot machine
UBOOT_MACHINE=am57xx_evm_config


# Binary File Target DIR
TARGET_DIR_PATH=~/tftpboot

#Points to the root of the TI SDK
export TI_SDK_PATH=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07

#root of the target file system for installing applications
DESTDIR=$(MASTER_PATH)/bsp/target-maker

#Points to the root of the Linux libraries and headers matching the
#demo file system.
export LINUX_DEVKIT_PATH=$(TI_SDK_PATH)/linux-devkit

#Cross compiler prefix
export CROSS_COMPILE=$(LINUX_DEVKIT_PATH)/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf-

#Default CC value to be used when cross compiling.  This is so that the
#GNU Make default of "cc" is not used to point to the host compiler
export CC=$(CROSS_COMPILE)gcc

#Location of environment-setup file
export ENV_SETUP=$(LINUX_DEVKIT_PATH)/environment-setup

#The directory that points to the SDK kernel source tree
LINUXKERNEL_INSTALL_DIR=$(MASTER_PATH)/bsp/linux-rt-4.14.79

CFLAGS= -march=armv7-a -marm -mfpu=neon  -mfloat-abi=hard

#Strip modules when installing to conserve disk space
INSTALL_MOD_STRIP=1

SDK_PATH_TARGET=$(TI_SDK_PATH)/linux-devkit/sysroots/armv7ahf-neon-linux-gnueabi/

# Set EXEC_DIR to install example binaries
EXEC_DIR=__EXEC_DIR__

MAKE_JOBS=4
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make target IMG=RFS

============================================
Building the Target Image
============================================

USEAGE:
# make target IMG=APP

IMG TYPE: ALL / BOOT / KL / APP / UP / RFS / PLATFORM / ALL-RFS
VERSION_PATH=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Nand Page Size: 2K (2048)
remove ./output_img files

Copying  Image  from ./output_img
Build Target Image...
build_ext4 RFS
Generate RFS from ./rootfs_temp
2457600+0 records in
2457600+0 records out
2516582400 bytes (2.5 GB, 2.3 GiB) copied, 7.59337 s, 331 MB/s
mke2fs 1.44.1 (24-Mar-2018)
Discarding device blocks: done                            
Creating filesystem with 614400 4k blocks and 153824 inodes
Filesystem UUID: 3bc86658-9f7f-4c1e-8302-7e39c9bbe961
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done 

build_jffs APP
Generate APP from ./app_temp
Make Binary Image...

UPdate File Version: V 018

============================================ 
	  Upgrade Image Maker 
============================================ 
partition[0] :  RFS, CRC(0x00000000), Data Size(0x96000000)

============== FLASH HEADER ================
Manufacturer   	ID : 0x0001
Model          	ID : 0x0041
Hardware    	ID : 0x0054
Firmware  Version  : 0.1.8
Extra Data         : 0x0020
Partition Count    : 0x1
Target Image Size  : 2400.000000 MB
============================================
TOTAL RFS PARTS=0
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=RFS, PRODUCT_NAME=SHUR, VERSION=018 	TARGET_DIR=/home/jibon/tftpboot, MODEL_NAME=AM5718, PLATFORM=018, VERSION_FILE_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Target Image Make Finish!!
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cd bsp/target-maker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls
a15_linux_code  apps  build_img.sh  fpga   logo  modules     PartitionsTablebkp  tools
AM5718          boot  dtb           linux  mnt   output_img  rootfs              UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ git branc
git: 'branc' is not a git command. See 'git --help'.
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ git branch
  master
* rfs_partition_extension
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ git status
On branch rfs_partition_extension
Your branch is up to date with 'origin/rfs_partition_extension'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   .gitignore
	modified:   AM5718
	modified:   PartitionsTablebkp
	modified:   boot/MLO
	modified:   boot/am571x-idk.dtb
	modified:   boot/u-boot.img
	modified:   dtb/am571x-idk.dtb
	modified:   linux/zImage
	modified:   logo/264.dtb
	modified:   logo/logo.bmp
	modified:   rootfs/dev/.gitkeep
	...
	....
	....
	......
	........
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/scgi-responder.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/var-include-sub.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/var-include.conf

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	a15_linux_code/

no changes added to commit (use "git add" and/or "git commit -a")
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ git ls-remote
warning: redirecting to http://git.sanion.com:8891/sur5000_code_base/a15_target_make_code.git/
From http://git.sanion.com:8891/sur5000_code_base/a15_target_make_code
37dba5dead43ed60e50f6828673c03e7528c20bc	HEAD
ca21d2bb53995d0538417ff0b075990c35fde1eb	refs/heads/IM2_develop
1a9ed797d05fa752e125daccace244e25a50abec	refs/heads/develop
83518d293bdb4fd4bdc69294de1b89ab27427aac	refs/heads/feature/IM2_HS_Log
37dba5dead43ed60e50f6828673c03e7528c20bc	refs/heads/master
05731bab8ea19e2f4a6380361719a4506ac6695c	refs/heads/product
906d380b2b6ad4c6a0342f1a4d498cade34103a5	refs/heads/release1.2
08d958b034b5330f5c045418d84fb8cc87786f79	refs/heads/rfs_partition_extension
3caacc5de907ef6ac621de19285fe344f718c205	refs/merge-requests/1/head
1272fae007190e835216c3112543a18ceac2be84	refs/merge-requests/1/merge
3a0a3a5778b7df4e313701113b18173ed1d1e318	refs/tags/IM2_20230727_R018
8fb97ed8d14ea5700232392bedd8bc479a645f2e	refs/tags/IM2_20230727_R018^{}
d1700a71fed674a74896ef3acf772c33f0ea8310	refs/tags/sur5000_20230720_T018
8fb97ed8d14ea5700232392bedd8bc479a645f2e	refs/tags/sur5000_20230720_T018^{}
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ git pull
warning: redirecting to http://git.sanion.com:8891/sur5000_code_base/a15_target_make_code.git/
remote: Enumerating objects: 8, done.
remote: Counting objects: 100% (8/8), done.
remote: Compressing objects: 100% (8/8), done.
remote: Total 8 (delta 0), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (8/8), done.
From http://git.sanion.com:8891/sur5000_code_base/a15_target_make_code
   18b17b72..ca21d2bb  IM2_develop -> origin/IM2_develop
   bf9265fe..1a9ed797  develop     -> origin/develop
Already up to date.
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ git branch
  master
* rfs_partition_extension
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ git log
commit 08d958b034b5330f5c045418d84fb8cc87786f79 (HEAD -> rfs_partition_extension, origin/rfs_partition_extension)
Author: amir-ice-1516-iu <amirkhondokar@gmail.com>
Date:   Tue Mar 5 10:20:30 2024 +0900

    (develop) updated rfs segments count variable for naming convention claim from other team

commit 7a8f2eaadb8c1a61aa661a23f424901ca464012d
Author: amir-ice-1516-iu <amirkhondokar@gmail.com>
Date:   Mon Mar 4 13:47:58 2024 +0900

    (develop) coredump crash report files gulated

commit 1545ff418999c4ce941288cc7b6c2010e99c6939
Author: amir-ice-1516-iu <amirkhondokar@gmail.com>
Date:   Thu Feb 29 14:39:48 2024 +0900

    (develop) updated to track coredump crash report files and keep last 20 files -- test reamined

commit e248d42927be25a7b20af6a39411e8c6888fe573
Author: amir-ice-1516-iu <amirkhondokar@gmail.com>
Date:   Thu Feb 29 13:25:10 2024 +0900

    (develop) RFS partition extension with splitted RFSx.bin image files tested

commit 83e0d6cd9e71c0f815afed2630a978c0ce92b35c
Author: amir-ice-1516-iu <amirkhondokar@gmail.com>
Date:   Tue Feb 27 18:08:05 2024 +0900
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls
a15_linux_code  apps  build_img.sh  fpga   logo  modules     PartitionsTablebkp  tools
AM5718          boot  dtb           linux  mnt   output_img  rootfs              UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd tools/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ ls
binarymaker     busybox-1.30.1  hmi      ksz9563_driver  libiconv-1.16.tar.gz  rs4xx   stupid-ftpd  touch         web-server
broadcast_test  gpmc_driver     KSZ9563  libiconv-1.16   mmap_exam             sqlite  timer        vsftpd-3.0.3  zlib
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls
a15_linux_code  apps  build_img.sh  fpga   logo  modules     PartitionsTablebkp  tools
AM5718          boot  dtb           linux  mnt   output_img  rootfs              UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ ls
extra-drivers  linux-rt-4.14.79  target-maker  u-boot-2018.01
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd target-maker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd u-boot-2018.01/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/u-boot-2018.01$ git branc
git: 'branc' is not a git command. See 'git --help'.
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/u-boot-2018.01$ git branch
  IM2_develop
  develop
* rfs_partition_extension
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/u-boot-2018.01$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ ls
extra-drivers  linux-rt-4.14.79  target-maker  u-boot-2018.01
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd target-maker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls
a15_linux_code  apps  build_img.sh  fpga   logo  modules     PartitionsTablebkp  tools
AM5718          boot  dtb           linux  mnt   output_img  rootfs              UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls tools/ -all
total 5124
drwxrwxrwx 19 jibon jibon    4096  7월  9 14:09 .
drwxrwxrwx 15 jibon jibon    4096  7월 18 16:19 ..
drwxrwxrwx  2 jibon jibon    4096  7월 18 15:44 binarymaker
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 broadcast_test
drwxrwxrwx 36 jibon jibon    4096  7월  9 14:09 busybox-1.30.1
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 gpmc_driver
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:08 hmi
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 KSZ9563
drwxrwxrwx  4 jibon jibon    4096  7월  9 14:09 ksz9563_driver
drwxrwxrwx 21 jibon jibon    4096  7월  9 14:09 libiconv-1.16
-rwxrwxrwx  1 jibon jibon 5166734  7월  9 14:09 libiconv-1.16.tar.gz
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 mmap_exam
drwxrwxrwx  7 jibon jibon    4096  7월  9 14:09 rs4xx
drwxrwxrwx  4 jibon jibon    4096  7월  9 14:08 sqlite
drwxrwxrwx  4 jibon jibon    4096  7월  9 14:08 stupid-ftpd
drwxrwxrwx  3 jibon jibon    4096  7월  9 14:08 timer
drwxrwxrwx  5 jibon jibon    4096  7월  9 14:08 touch
drwxrwxrwx  8 jibon jibon    4096  7월  9 14:09 vsftpd-3.0.3
drwxrwxrwx  3 jibon jibon    4096  7월  9 14:08 web-server
drwxrwxrwx  3 jibon jibon    4096  7월  9 14:08 zlib
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make target IMG=RFS

============================================
Building the Target Image
============================================

USEAGE:
# make target IMG=APP

IMG TYPE: ALL / BOOT / KL / APP / UP / RFS / PLATFORM / ALL-RFS
VERSION_PATH=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Nand Page Size: 2K (2048)
remove ./output_img files

Copying  Image  from ./output_img
Build Target Image...
build_ext4 RFS
Generate RFS from ./rootfs_temp
2457600+0 records in
2457600+0 records out
2516582400 bytes (2.5 GB, 2.3 GiB) copied, 8.31522 s, 303 MB/s
mke2fs 1.44.1 (24-Mar-2018)
Discarding device blocks: done                            
Creating filesystem with 614400 4k blocks and 153824 inodes
Filesystem UUID: 0c899a84-c062-4e4d-ae3d-2576b088200b
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done 

build_jffs APP
Generate APP from ./app_temp
Make Binary Image...

UPdate File Version: V 018

============================================ 
	  Upgrade Image Maker 
============================================ 
partition[0] :  RFS, CRC(0x00000000), Data Size(0x96000000)

============== FLASH HEADER ================
Manufacturer   	ID : 0x0001
Model          	ID : 0x0041
Hardware    	ID : 0x0054
Firmware  Version  : 0.1.8
Extra Data         : 0x0020
Partition Count    : 0x1
Target Image Size  : 2400.000000 MB
============================================
TOTAL RFS PARTS=0
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=RFS, PRODUCT_NAME=SHUR, VERSION=018 	TARGET_DIR=/home/jibon/tftpboot, MODEL_NAME=AM5718, PLATFORM=018, VERSION_FILE_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Target Image Make Finish!!
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ code bsp/target-maker/build_img.sh &
[3] 23178
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ code bsp/target-maker/
a15_linux_code/     boot/               fpga/               linux/              modules/            rootfs/             
AM5718              build_img.sh        .git/               logo/               output_img/         tools/              
apps/               dtb/                .gitignore          mnt/                PartitionsTablebkp  UpdateFlag.sh       
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ code bsp/target-maker/tools/binarymaker/ &
[4] 23528
[3]   Done                    code bsp/target-maker/build_img.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make target IMG=ALL

============================================
Building the Target Image
============================================

USEAGE:
# make target IMG=APP

IMG TYPE: ALL / BOOT / KL / APP / UP / RFS / PLATFORM / ALL-RFS
VERSION_PATH=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Nand Page Size: 2K (2048)
remove ./output_img files

Copying  Image  from ./output_img
Build Target Image...
build_ext4 RFS
Generate RFS from ./rootfs_temp
2457600+0 records in
2457600+0 records out
2516582400 bytes (2.5 GB, 2.3 GiB) copied, 8.07806 s, 312 MB/s
mke2fs 1.44.1 (24-Mar-2018)
Discarding device blocks: done                            
Creating filesystem with 614400 4k blocks and 153824 inodes
Filesystem UUID: b8ad1bc7-ada7-499b-b838-45b9e1533ea1
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done 

build_jffs APP
Generate APP from ./app_temp
Make Binary Image...

UPdate File Version: V 018

============================================ 
	  Upgrade Image Maker 
============================================ 
partition[0] :  RFS, CRC(0x00000000), Data Size(0x96000000)
partition[1] :  SPL, CRC(0x00000000), Data Size(0x00019A06)
partition[2] : BOOT, CRC(0x00000000), Data Size(0x000E14D4)
partition[3] : LOGO, CRC(0x00000000), Data Size(0x000172BD)
partition[4] :  DTB, CRC(0x00000000), Data Size(0x000177C6)
partition[5] :   KL, CRC(0x00000000), Data Size(0x003C2200)
partition[6] :  APP, CRC(0x00000000), Data Size(0x00890000)
partition[7] : FPGA, CRC(0x00000000), Data Size(0x002B501C)

============== FLASH HEADER ================
Manufacturer   	ID : 0x0001
Model          	ID : 0x0041
Hardware    	ID : 0x0054
Firmware  Version  : 0.1.8
Extra Data         : 0x017f
Partition Count    : 0x8
Target Image Size  : 2416.190430 MB
============================================
TOTAL RFS PARTS=0
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=ALL, PRODUCT_NAME=SHUR, VERSION=018 	TARGET_DIR=/home/jibon/tftpboot, MODEL_NAME=AM5718, PLATFORM=018, VERSION_FILE_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Target Image Make Finish!!
[4]+  Done                    code bsp/target-maker/tools/binarymaker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ make boot_install
=====================================
Building the Linux Kernel DTBs
=====================================
make -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- SANION-HUR_defconfig
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
#
# configuration written to .config
#
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- am571x-idk.dtb 
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
scripts/kconfig/conf  --silentoldconfig Kconfig

*** Error during update of the configuration.

scripts/kconfig/Makefile:38: recipe for target 'silentoldconfig' failed
make[3]: *** [silentoldconfig] Error 1
Makefile:518: recipe for target 'silentoldconfig' failed
make[2]: *** [silentoldconfig] Error 2
make[1]: *** No rule to make target 'include/config/auto.conf', needed by 'scripts'.  Stop.
make[1]: *** Waiting for unfinished jobs....
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
Makefile:207: recipe for target 'linux-dtbs' failed
make: *** [linux-dtbs] Error 2
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ make linux_install
=====================================
Building the Linux Kernel DTBs
=====================================
make -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- SANION-HUR_defconfig
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
#
# configuration written to .config
#
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- am571x-idk.dtb 
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
scripts/kconfig/conf  --silentoldconfig Kconfig

*** Error during update of the configuration.

scripts/kconfig/Makefile:38: recipe for target 'silentoldconfig' failed
make[3]: *** [silentoldconfig] Error 1
Makefile:518: recipe for target 'silentoldconfig' failed
make[2]: *** [silentoldconfig] Error 2
make[1]: *** No rule to make target 'include/config/auto.conf', needed by 'scripts'.  Stop.
make[1]: *** Waiting for unfinished jobs....
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
Makefile:207: recipe for target 'linux-dtbs' failed
make: *** [linux-dtbs] Error 2
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make linux_install
=====================================
Building the Linux Kernel DTBs
=====================================
make -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- SANION-HUR_defconfig
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
#
# configuration written to .config
#
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- am571x-idk.dtb 
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
scripts/kconfig/conf  --silentoldconfig Kconfig
  CHK     scripts/mod/devicetable-offsets.h
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
=======================================
Installing the Linux Kernel DTBs
=======================================
install -d /home/jibon/projects/sur5000/sur5000_top/bsp/target-maker/boot
===================================
Installing the Linux Kernel
===================================
make -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- SANION-HUR_defconfig
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
#
# configuration written to .config
#
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- zImage
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
scripts/kconfig/conf  --silentoldconfig Kconfig
  CHK     include/config/kernel.release
  CHK     include/generated/uapi/linux/version.h
  CHK     scripts/mod/devicetable-offsets.h
  CHK     include/generated/utsrelease.h
  CHK     include/generated/timeconst.h
  CHK     include/generated/bounds.h
  CHK     include/generated/asm-offsets.h
  CALL    scripts/checksyscalls.sh
  CHK     include/generated/compile.h
  GZIP    kernel/config_data.gz
  CHK     kernel/config_data.h
  Kernel: arch/arm/boot/Image is ready
  Kernel: arch/arm/boot/zImage is ready
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- modules
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
  CHK     include/config/kernel.release
  CHK     include/generated/uapi/linux/version.h
  CHK     include/generated/utsrelease.h
  CHK     scripts/mod/devicetable-offsets.h
  CHK     include/generated/timeconst.h
  CHK     include/generated/bounds.h
  CHK     include/generated/asm-offsets.h
  CALL    scripts/checksyscalls.sh
  Building modules, stage 2.
  MODPOST 67 modules
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
cp /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79/arch/arm/boot/zImage /home/jibon/projects/sur5000/sur5000_top/bsp/target-maker/linux
cp /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79/arch/arm/boot/dts/am571x-idk.dtb /home/jibon/projects/sur5000/sur5000_top/bsp/target-maker/dtb
make -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- INSTALL_MOD_PATH=/home/jibon/projects/sur5000/sur5000_top/bsp/target-maker/modules INSTALL_MOD_STRIP=1 modules_install
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
  INSTALL drivers/rpmsg/rpmsg_pru.ko
  INSTALL net/802/p8022.ko
  INSTALL net/802/psnap.ko
  INSTALL net/802/stp.ko
  INSTALL net/8021q/8021q.ko
  INSTALL net/bridge/br_netfilter.ko
  INSTALL net/bridge/bridge.ko
  INSTALL net/bridge/netfilter/ebt_802_3.ko
  INSTALL net/bridge/netfilter/ebt_among.ko
  INSTALL net/bridge/netfilter/ebt_arp.ko
  INSTALL net/bridge/netfilter/ebt_arpreply.ko
  INSTALL net/bridge/netfilter/ebt_dnat.ko
  INSTALL net/bridge/netfilter/ebt_ip.ko
  INSTALL net/bridge/netfilter/ebt_limit.ko
  INSTALL net/bridge/netfilter/ebt_log.ko
  INSTALL net/bridge/netfilter/ebt_mark.ko
  INSTALL net/bridge/netfilter/ebt_mark_m.ko
  INSTALL net/bridge/netfilter/ebt_nflog.ko
  INSTALL net/bridge/netfilter/ebt_pkttype.ko
  INSTALL net/bridge/netfilter/ebt_redirect.ko
  INSTALL net/bridge/netfilter/ebt_snat.ko
  INSTALL net/bridge/netfilter/ebt_stp.ko
  INSTALL net/bridge/netfilter/ebt_vlan.ko
  INSTALL net/bridge/netfilter/ebtable_broute.ko
  INSTALL net/bridge/netfilter/ebtable_filter.ko
  INSTALL net/bridge/netfilter/ebtable_nat.ko
  INSTALL net/bridge/netfilter/ebtables.ko
  INSTALL net/ipv4/netfilter/arp_tables.ko
  INSTALL net/ipv4/netfilter/arpt_mangle.ko
  INSTALL net/ipv4/netfilter/arptable_filter.ko
  INSTALL net/ipv4/netfilter/ip_tables.ko
  INSTALL net/ipv4/netfilter/ipt_MASQUERADE.ko
  INSTALL net/ipv4/netfilter/iptable_filter.ko
  INSTALL net/ipv4/netfilter/iptable_nat.ko
  INSTALL net/ipv4/netfilter/nf_conntrack_ipv4.ko
  INSTALL net/ipv4/netfilter/nf_defrag_ipv4.ko
  INSTALL net/ipv4/netfilter/nf_nat_ipv4.ko
  INSTALL net/ipv4/netfilter/nf_nat_masquerade_ipv4.ko
  INSTALL net/llc/llc.ko
  INSTALL net/netfilter/ipvs/ip_vs.ko
  INSTALL net/netfilter/ipvs/ip_vs_rr.ko
  INSTALL net/netfilter/nf_conntrack.ko
  INSTALL net/netfilter/nf_conntrack_ftp.ko
  INSTALL net/netfilter/nf_conntrack_tftp.ko
  INSTALL net/netfilter/nf_nat.ko
  INSTALL net/netfilter/nf_nat_ftp.ko
  INSTALL net/netfilter/nf_nat_tftp.ko
  INSTALL net/netfilter/x_tables.ko
  INSTALL net/netfilter/xt_CLASSIFY.ko
  INSTALL net/netfilter/xt_IDLETIMER.ko
  INSTALL net/netfilter/xt_addrtype.ko
  INSTALL net/netfilter/xt_comment.ko
  INSTALL net/netfilter/xt_conntrack.ko
  INSTALL net/netfilter/xt_cpu.ko
  INSTALL net/netfilter/xt_iprange.ko
  INSTALL net/netfilter/xt_ipvs.ko
  INSTALL net/netfilter/xt_length.ko
  INSTALL net/netfilter/xt_limit.ko
  INSTALL net/netfilter/xt_mac.ko
  INSTALL net/netfilter/xt_mark.ko
  INSTALL net/netfilter/xt_multiport.ko
  INSTALL net/netfilter/xt_nat.ko
  INSTALL net/netfilter/xt_pkttype.ko
  INSTALL net/netfilter/xt_policy.ko
  INSTALL net/netfilter/xt_sctp.ko
  INSTALL net/netfilter/xt_tcpudp.ko
  INSTALL net/rpmsg/rpmsg_proto.ko
  DEPMOD  4.14.79-rt47-00003-g136373f6c
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make boot_install
=====================================
Building the Linux Kernel DTBs
=====================================
make -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- SANION-HUR_defconfig
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
#
# configuration written to .config
#
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79 ARCH=arm CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- am571x-idk.dtb 
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
scripts/kconfig/conf  --silentoldconfig Kconfig
  CHK     scripts/mod/devicetable-offsets.h
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79'
===================================
Installing U-boot
===================================
Nothing to do
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-* CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- am57xx_evm_config
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-2018.01'
#
# configuration written to .config
#
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-2018.01'
make -j 4 -C /home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-* CROSS_COMPILE=/opt/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- DTC=/home/jibon/projects/sur5000/sur5000_top/bsp/linux-rt-4.14.79/scripts/dtc/dtc
make[1]: Entering directory '/home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-2018.01'
scripts/kconfig/conf  --silentoldconfig Kconfig
  CHK     include/config.h
  CFG     u-boot.cfg
  GEN     include/autoconf.mk.dep
  CFG     spl/u-boot.cfg
  GEN     spl/include/autoconf.mk
  GEN     include/autoconf.mk
  CHK     include/config/uboot.release
  CHK     include/generated/timestamp_autogenerated.h
  UPD     include/generated/timestamp_autogenerated.h
  CHK     include/generated/version_autogenerated.h
  CHK     include/generated/generic-asm-offsets.h
  CHK     include/generated/asm-offsets.h
  HOSTCC  tools/mkenvimage.o
  HOSTCC  tools/image-host.o
  HOSTCC  tools/fit_image.o
  CHK     include/config.h
  CFG     u-boot.cfg
  HOSTCC  tools/dumpimage.o
  HOSTCC  tools/mkimage.o
  HOSTLD  tools/mkenvimage
  HOSTLD  tools/dumpimage
  HOSTLD  tools/mkimage
  CC      common/main.o
  CC      cmd/version.o
  LD      cmd/built-in.o
  LD      common/built-in.o
  CC      lib/smbios.o
  CC      lib/display_options.o
  CC      lib/efi_loader/helloworld.o
  LD      lib/efi_loader/helloworld_efi.so
  OBJCOPY lib/efi_loader/helloworld.efi
rm lib/efi_loader/helloworld_efi.so lib/efi_loader/helloworld.o
  LD      lib/built-in.o
  LD      u-boot
  OBJCOPY u-boot-nodtb.bin
  OBJCOPY u-boot.srec
  SYM     u-boot.sym
make[3]: 'arch/arm/dts/am571x-idk.dtb' is up to date.
  MKIMAGE u-boot-dtb.img
  MKIMAGE u-boot.img
  CAT     u-boot-dtb.bin
  COPY    u-boot.bin
  CC      spl/common/spl/spl.o
  CC      spl/lib/display_options.o
  LD      spl/common/spl/built-in.o
  LD      spl/lib/built-in.o
  LD      spl/u-boot-spl
  OBJCOPY spl/u-boot-spl-nodtb.bin
  CAT     spl/u-boot-spl-dtb.bin
  COPY    spl/u-boot-spl.bin
  MKIMAGE MLO
===================== WARNING ======================
This board uses CONFIG_DM_I2C_COMPAT. Please remove
(possibly in a subsequent patch in your series)
before sending patches to the mailing list.
====================================================
  CFGCHK  u-boot.cfg
make[1]: Leaving directory '/home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-2018.01'
cp /home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-2018.01/u-boot.img /home/jibon/projects/sur5000/sur5000_top/bsp/target-maker/boot/ 
cp /home/jibon/projects/sur5000/sur5000_top/bsp/u-boot-2018.01/MLO /home/jibon/projects/sur5000/sur5000_top/bsp/target-maker/boot/ 
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make target IMG=RFS

============================================
Building the Target Image
============================================

USEAGE:
# make target IMG=APP

IMG TYPE: ALL / BOOT / KL / APP / UP / RFS / PLATFORM / ALL-RFS
VERSION_PATH=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Nand Page Size: 2K (2048)
remove ./output_img files

Copying  Image  from ./output_img
Build Target Image...
build_ext4 RFS
Generate RFS from ./rootfs_temp
2457600+0 records in
2457600+0 records out
2516582400 bytes (2.5 GB, 2.3 GiB) copied, 8.53545 s, 295 MB/s
mke2fs 1.44.1 (24-Mar-2018)
Discarding device blocks: done                            
Creating filesystem with 614400 4k blocks and 153824 inodes
Filesystem UUID: 913962df-10a6-4569-85bd-3f8be74ed13e
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done 

build_jffs APP
Generate APP from ./app_temp
Make Binary Image...

UPdate File Version: V 018

============================================ 
	  Upgrade Image Maker 
============================================ 
partition[0] :  RFS, CRC(0x00000000), Data Size(0x96000000)

============== FLASH HEADER ================
Manufacturer   	ID : 0x0001
Model          	ID : 0x0041
Hardware    	ID : 0x0054
Firmware  Version  : 0.1.8
Extra Data         : 0x0020
Partition Count    : 0x1
Target Image Size  : 2400.000000 MB
============================================
TOTAL RFS PARTS=0
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=RFS, PRODUCT_NAME=SHUR, VERSION=018 	TARGET_DIR=/home/jibon/tftpboot, MODEL_NAME=AM5718, PLATFORM=018, VERSION_FILE_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Target Image Make Finish!!
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cd bsp/target-maker/tools/binarymaker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin  mkbin.c  mkbin.h  mkbin.o
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ make binarymaker
make: *** No rule to make target 'binarymaker'.  Stop.
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cat Makefile | grep mkbin
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cat Makefile | grep binary
	cd ./eurasia_km/eurasiacon/binary2_omap_linux_release/target/kbuild; \
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ make binary
make: *** No rule to make target 'binary'.  Stop.
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ ls
application  bsp  BuildScript.sh  complete.sh  Makefile  ProductSW.sh  Rules.make  start.sh  TagBuildTree.sh  version
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cd bsp/target-maker/tools/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ ls
binarymaker     busybox-1.30.1  hmi      ksz9563_driver  libiconv-1.16.tar.gz  rs4xx   stupid-ftpd  touch         web-server
broadcast_test  gpmc_driver     KSZ9563  libiconv-1.16   mmap_exam             sqlite  timer        vsftpd-3.0.3  zlib
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ cd binarymaker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin  mkbin.c  mkbin.h  mkbin.o
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ make clean
rm -f mkbin
rm -rf *.o *.a
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin.c  mkbin.h
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ make all
make: Nothing to be done for 'all'.
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ make
gcc -g -c mkbin.c -I.
gcc -lm -o mkbin mkbin.o -I. -L. 
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin  mkbin.c  mkbin.h  mkbin.o
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ make clean
rm -f mkbin
rm -rf *.o *.a
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ make 
gcc -g -c mkbin.c -I.
gcc -lm -o mkbin mkbin.o -I. -L. 
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin  mkbin.c  mkbin.h  mkbin.o
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ make clean
rm -f mkbin
rm -rf *.o *.a
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin.c  mkbin.h
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ make 
gcc -g -c mkbin.c -I.
gcc -lm -o mkbin mkbin.o -I. -L. 
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin  mkbin.c  mkbin.h  mkbin.o
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ cat imagemake.sh 
#!/bin/sh

Model_Name="Omapl138"
Image_Num=$2
#
# help message
#
print_usage(){
    echo; echo;
    echo "Command:./imagemake.sh [Image Number]"
    echo
    echo "Example: ./imagemake.sh 6"
    echo
	echo "Default Image: CFG, APP"
    echo "Image Number: 0 ~ 8"
    echo "0: ALL (KL, RFS, CFG, APP, DATA)"
    echo "1: KL, RFS, APP, CFG"
    echo "2: KL, APP, CFG"
    echo "3: KL, APP"
    echo "4: KL, CFG"
    echo "5: APP, CFG"
    echo "6: KL"
    echo "7: APP"
    echo "8: CFG"
    echo;
}

#
# Check the command argument
#
if [ $# = 0 ]
then
	echo "default target name: CFG, APP"
    echo "Try [--help] for more information.";
	Image_Num=5;
elif [ $Image_Num -ge 0 ] && [ $Image_Num -le 9 ]
then
    echo "${Model_Name} Image Number: ${Image_Num}";
elif [ $Model_Name = "--help" ]
then
    print_usage
    exit;
else
    echo "Try [--help] for more information.";
	print_usage
    exit;
fi

make clean
make

#App update
./mkbin ${Model_Name} 1.0.0 0 ${Image_Num}
#All update(Recovery)
#./mkbin ${Model_Name} 1.0.0 1 0

jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cat UpdateFlag.sh 
#!/bin/bash

##################################################################################
# skaskawl - UpdateFlagFile                                                      #
##################################################################################

BIN_NAME=$1
VERSION=$2
UPDATEIMG=$3
RFS_PARTITIONS_COUNT=$4
TARGETDIR=./output_img/UpdateFlag

echo "# Update Image information (y : One Binary File / n : Each Binary File)"      > ${TARGETDIR} ;
echo "imageinfo=y"                                                                  >> ${TARGETDIR} ;
echo ""                                                                             >> ${TARGETDIR} ;
echo "# SQL DB Delete information (y : delete db files / n : don't delete db files)" >> ${TARGETDIR} ;
echo "dbDelete=n"                                                                   >> ${TARGETDIR} ;
echo ""                                                                             >> ${TARGETDIR} ;
echo "# Update Binary File Name"                                                    >> ${TARGETDIR} ;
echo "binfile=${BIN_NAME}_v${VERSION}.bin"                                          >> ${TARGETDIR} ;
echo ""                                                                             >> ${TARGETDIR} ;
echo "# Update Image"                                                               >> ${TARGETDIR} ;
echo "# ALL | ALL-RFS | BOOT | KL | RFS | APP | FPGA | PLATFORM"                    >> ${TARGETDIR} ;
echo "updateimg=${UPDATEIMG}"                                                       >> ${TARGETDIR} ;
echo ""                                                                             >> ${TARGETDIR} ;
echo "# Update Image Name"                                                          >> ${TARGETDIR} ;
echo "img_spl=SPL.img"                                                              >> ${TARGETDIR} ;
echo "img_boot=BOOT.img"                                                            >> ${TARGETDIR} ;
echo "img_logo=LOGO.img"                                                            >> ${TARGETDIR} ;
echo "img_dtb=DTB.img"                                                              >> ${TARGETDIR} ;
echo "img_kernel=KL.img"                                                            >> ${TARGETDIR} ;
echo "img_rootfs=RFS.img"                                                           >> ${TARGETDIR} ;
echo "img_app=APP.img"                                                              >> ${TARGETDIR} ;
echo "img_fpga=FPGA.img"                                                            >> ${TARGETDIR} ;
echo "rfs_parts_count=$RFS_PARTITIONS_COUNT"                                        >> ${TARGETDIR} ;

jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cat build_img.sh | grep UpgradeFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ ls
extra-drivers  linux-rt-4.14.79  target-maker  u-boot-2018.01
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ ls -all
total 24
drwxrwxr-x  6 jibon jibon 4096  7월 18 15:18 .
drwxrwxrwx  6 jibon jibon 4096  7월 18 16:19 ..
drwxrwxr-x  2 jibon jibon 4096  7월 10 17:00 extra-drivers
drwxrwxr-x 28 jibon jibon 4096  7월 18 16:36 linux-rt-4.14.79
drwxrwxrwx 15 jibon jibon 4096  7월 18 16:36 target-maker
drwxrwxrwx 26 jibon jibon 4096  7월 18 16:36 u-boot-2018.01
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd target-maker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls
a15_linux_code  apps  build_img.sh  fpga   logo  modules     PartitionsTablebkp  tools
AM5718          boot  dtb           linux  mnt   output_img  rootfs              UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd tools/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ ls -all
total 5124
drwxrwxrwx 19 jibon jibon    4096  7월  9 14:09 .
drwxrwxrwx 15 jibon jibon    4096  7월 18 16:36 ..
drwxrwxrwx  2 jibon jibon    4096  7월 18 16:42 binarymaker
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 broadcast_test
drwxrwxrwx 36 jibon jibon    4096  7월  9 14:09 busybox-1.30.1
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 gpmc_driver
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:08 hmi
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 KSZ9563
drwxrwxrwx  4 jibon jibon    4096  7월  9 14:09 ksz9563_driver
drwxrwxrwx 21 jibon jibon    4096  7월  9 14:09 libiconv-1.16
-rwxrwxrwx  1 jibon jibon 5166734  7월  9 14:09 libiconv-1.16.tar.gz
drwxrwxrwx  2 jibon jibon    4096  7월  9 14:09 mmap_exam
drwxrwxrwx  7 jibon jibon    4096  7월  9 14:09 rs4xx
drwxrwxrwx  4 jibon jibon    4096  7월  9 14:08 sqlite
drwxrwxrwx  4 jibon jibon    4096  7월  9 14:08 stupid-ftpd
drwxrwxrwx  3 jibon jibon    4096  7월  9 14:08 timer
drwxrwxrwx  5 jibon jibon    4096  7월  9 14:08 touch
drwxrwxrwx  8 jibon jibon    4096  7월  9 14:09 vsftpd-3.0.3
drwxrwxrwx  3 jibon jibon    4096  7월  9 14:08 web-server
drwxrwxrwx  3 jibon jibon    4096  7월  9 14:08 zlib
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ cd binarymaker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls
imagemake.sh  Makefile  mkbin  mkbin.c  mkbin.h  mkbin.o
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ ls -all
total 100
drwxrwxrwx  2 jibon jibon  4096  7월 18 16:42 .
drwxrwxrwx 19 jibon jibon  4096  7월  9 14:09 ..
-rwxrwxrwx  1 jibon jibon  1028  7월  9 14:08 imagemake.sh
-rwxrwxrwx  1 jibon jibon   292  7월  9 14:08 Makefile
-rwxrwxr-x  1 jibon jibon 23400  7월 18 16:42 mkbin
-rwxrwxrwx  1 jibon jibon 25511  7월  9 14:09 mkbin.c
-rwxrwxrwx  1 jibon jibon  2832  7월  9 14:09 mkbin.h
-rw-rw-r--  1 jibon jibon 25624  7월 18 16:42 mkbin.o
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools/binarymaker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker/tools$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls
a15_linux_code  apps  build_img.sh  fpga   logo  modules     PartitionsTablebkp  tools
AM5718          boot  dtb           linux  mnt   output_img  rootfs              UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ echo "4" > total_rfs_segments
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cat total_rfs_segments 
4
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make target IMG=RFS

============================================
Building the Target Image
============================================

USEAGE:
# make target IMG=APP

IMG TYPE: ALL / BOOT / KL / APP / UP / RFS / PLATFORM / ALL-RFS
VERSION_PATH=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Nand Page Size: 2K (2048)
remove ./output_img files

Copying  Image  from ./output_img
Build Target Image...
build_ext4 RFS
Generate RFS from ./rootfs_temp
2457600+0 records in
2457600+0 records out
2516582400 bytes (2.5 GB, 2.3 GiB) copied, 8.65799 s, 291 MB/s
mke2fs 1.44.1 (24-Mar-2018)
Discarding device blocks: done                            
Creating filesystem with 614400 4k blocks and 153824 inodes
Filesystem UUID: 62b11b63-6ab8-4920-86ad-81e9b8073cc9
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done 

build_jffs APP
Generate APP from ./app_temp
Make Binary Image...

UPdate File Version: V 018

============================================ 
	  Upgrade Image Maker 
============================================ 

============== FLASH HEADER ================
Manufacturer   	ID : 0x0001
Model          	ID : 0x0041
Hardware    	ID : 0x0054
Firmware  Version  : 0.1.8
Extra Data         : 0x0000
Partition Count    : 0x0
Target Image Size  : 0.000000 MB
============================================
RFS address : 0x 1000000 : 0x    8000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS0, CRC(0x00000000), Data Size(0x25800000)
RFS address : 0x26800000 : 0x  134000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS1, CRC(0x00000000), Data Size(0x25800000)
RFS address : 0x4c000000 : 0x  260000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS2, CRC(0x00000000), Data Size(0x25800000)
RFS address : 0x71800000 : 0x  38c000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS3, CRC(0x00000000), Data Size(0x25800000)
TOTAL RFS PARTS=4
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=RFS, PRODUCT_NAME=SHUR, VERSION=018 	TARGET_DIR=/home/jibon/tftpboot, MODEL_NAME=AM5718, PLATFORM=018, VERSION_FILE_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Target Image Make Finish!!
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ cd bsp/target-maker/
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls
a15_linux_code  apps  build_img.sh  fpga   logo  modules     PartitionsTablebkp  tools
AM5718          boot  dtb           linux  mnt   output_img  rootfs              UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ ls -all
total 88
drwxrwxrwx 15 jibon jibon  4096  7월 18 16:47 .
drwxrwxr-x  6 jibon jibon  4096  7월 18 15:18 ..
drwxrwxrwx 26 jibon jibon  4096  7월  9 14:11 a15_linux_code
-rwxrwxrwx  1 jibon jibon   413  7월  9 14:09 AM5718
drwxrwxrwx  2 jibon jibon  4096  7월  9 14:09 apps
drwxr-xr-x  2 jibon jibon  4096  7월  9 14:09 boot
-rwxrwxrwx  1 jibon jibon 11102  7월  9 14:09 build_img.sh
drwxrwxrwx  2 jibon jibon  4096  7월  9 14:09 dtb
drwxrwxrwx  2 jibon jibon  4096  7월  9 14:09 fpga
drwxrwxrwx  7 jibon jibon  4096  7월 18 16:21 .git
-rwxrwxrwx  1 jibon jibon   190  7월  9 14:09 .gitignore
drwxrwxrwx  2 jibon jibon  4096  7월  9 14:09 linux
drwxrwxrwx  2 jibon jibon  4096  7월  9 14:09 logo
drwxr-xr-x  2 root  root   4096  7월 17 16:21 mnt
drwxr-xr-x  3 root  root   4096  7월 18 15:41 modules
drwxr-xr-x  2 root  root   4096  7월 18 16:47 output_img
-rwxrwxrwx  1 jibon jibon   847  7월  9 14:09 PartitionsTablebkp
drwxrwxrwx 21 jibon jibon  4096  7월  9 14:09 rootfs
drwxrwxrwx 19 jibon jibon  4096  7월  9 14:09 tools
-rwxrwxrwx  1 jibon jibon  2705  7월  9 14:09 UpdateFlag.sh
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp/target-maker$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top/bsp$ cd ..
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ sudo make target IMG=ALL

============================================
Building the Target Image
============================================

USEAGE:
# make target IMG=APP

IMG TYPE: ALL / BOOT / KL / APP / UP / RFS / PLATFORM / ALL-RFS
VERSION_PATH=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Nand Page Size: 2K (2048)
remove ./output_img files

Copying  Image  from ./output_img
Build Target Image...
build_ext4 RFS
Generate RFS from ./rootfs_temp
2457600+0 records in
2457600+0 records out
2516582400 bytes (2.5 GB, 2.3 GiB) copied, 8.68576 s, 290 MB/s
mke2fs 1.44.1 (24-Mar-2018)
Discarding device blocks: done                            
Creating filesystem with 614400 4k blocks and 153824 inodes
Filesystem UUID: b9eeac43-743a-499c-ae2a-3a6aefb0f8d8
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information: done 

build_jffs APP
Generate APP from ./app_temp
Make Binary Image...

UPdate File Version: V 018

============================================ 
	  Upgrade Image Maker 
============================================ 
partition[0] :  SPL, CRC(0x00000000), Data Size(0x00019A06)
partition[1] : BOOT, CRC(0x00000000), Data Size(0x000E14D4)
partition[2] : LOGO, CRC(0x00000000), Data Size(0x000172BD)
partition[3] :  DTB, CRC(0x00000000), Data Size(0x000177C6)
partition[4] :   KL, CRC(0x00000000), Data Size(0x003C2200)
partition[5] :  APP, CRC(0x00000000), Data Size(0x00890000)
partition[6] : FPGA, CRC(0x00000000), Data Size(0x002B501C)

============== FLASH HEADER ================
Manufacturer   	ID : 0x0001
Model          	ID : 0x0041
Hardware    	ID : 0x0054
Firmware  Version  : 0.1.8
Extra Data         : 0x015f
Partition Count    : 0x7
Target Image Size  : 16.190430 MB
============================================
RFS address : 0x 1000000 : 0x    8000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS0, CRC(0x00000000), Data Size(0x25800000)
RFS address : 0x26800000 : 0x  134000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS1, CRC(0x00000000), Data Size(0x25800000)
RFS address : 0x4c000000 : 0x  260000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS2, CRC(0x00000000), Data Size(0x25800000)
RFS address : 0x71800000 : 0x  38c000 (block addr)
data file size 629145600
SIZE of HEADER 28 , SIZE of Partition 44
partition[0] :  RFS3, CRC(0x00000000), Data Size(0x25800000)
TOTAL RFS PARTS=4
OUTPUT=./output_img/APP.img, TARGET=app_temp
NAND_PAGE_SIZE=2048, IMG_NAME=ALL, PRODUCT_NAME=SHUR, VERSION=018 	TARGET_DIR=/home/jibon/tftpboot, MODEL_NAME=AM5718, PLATFORM=018, VERSION_FILE_NAME=/home/jibon/projects/sur5000/sur5000_top/version/SHUR.ver
Target Image Make Finish!!
jibon@PDABUILD:~/projects/sur5000/sur5000_top$ 

