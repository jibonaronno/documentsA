
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
	modified:   rootfs/etc/ca-certificates/update.d/.gitkeep
	modified:   rootfs/etc/cron.d/.gitkeep
	modified:   rootfs/etc/cron.hourly/.gitkeep
	modified:   rootfs/etc/cron.monthly/.gitkeep
	modified:   rootfs/etc/cron.weekly/.gitkeep
	modified:   rootfs/etc/depmod.d/.gitkeep
	modified:   rootfs/etc/dropbear/.gitkeep
	modified:   rootfs/etc/issue
	modified:   rootfs/etc/systemd/coredump.conf
	modified:   rootfs/etc/systemd/journald.conf
	modified:   rootfs/etc/systemd/logind.conf
	modified:   rootfs/etc/systemd/resolved.conf
	modified:   rootfs/etc/systemd/system.conf
	modified:   rootfs/etc/systemd/timesyncd.conf
	modified:   rootfs/etc/systemd/user.conf
	modified:   rootfs/etc/ver_history
	modified:   rootfs/home/sootoo23/.gitkeep
	modified:   rootfs/include/iconv.h
	modified:   rootfs/include/libcharset.h
	modified:   rootfs/include/localcharset.h
	modified:   rootfs/lib/libcharset.a
	modified:   rootfs/lib/libiconv.a
	modified:   rootfs/lib/systemd/system/alsa-restore.service
	modified:   rootfs/lib/systemd/system/alsa-state.service
	modified:   rootfs/lib/systemd/system/atd.service
	modified:   rootfs/lib/systemd/system/avahi-daemon.service
	modified:   rootfs/lib/systemd/system/avahi-daemon.socket
	modified:   rootfs/lib/systemd/system/basic.target
	modified:   rootfs/lib/systemd/system/bt-enable.service
	modified:   rootfs/lib/systemd/system/busnames.target
	modified:   rootfs/lib/systemd/system/busybox-klogd.service
	modified:   rootfs/lib/systemd/system/busybox-syslog.service
	modified:   rootfs/lib/systemd/system/console-getty.service
	modified:   rootfs/lib/systemd/system/container-getty@.service
	modified:   rootfs/lib/systemd/system/crond.service
	modified:   rootfs/lib/systemd/system/dbus.service
	modified:   rootfs/lib/systemd/system/dbus.socket
	modified:   rootfs/lib/systemd/system/debug-shell.service
	modified:   rootfs/lib/systemd/system/dev-hugepages.mount
	modified:   rootfs/lib/systemd/system/dev-mqueue.mount
	modified:   rootfs/lib/systemd/system/dropbear.socket
	modified:   rootfs/lib/systemd/system/dropbear@.service
	modified:   rootfs/lib/systemd/system/dropbearkey.service
	modified:   rootfs/lib/systemd/system/emergency.service
	modified:   rootfs/lib/systemd/system/emergency.target
	modified:   rootfs/lib/systemd/system/exit.target
	modified:   rootfs/lib/systemd/system/final.target
	modified:   rootfs/lib/systemd/system/getty.target
	modified:   rootfs/lib/systemd/system/getty@.service
	modified:   rootfs/lib/systemd/system/gplv3-notice.service
	modified:   rootfs/lib/systemd/system/graphical.target
	modified:   rootfs/lib/systemd/system/halt-local.service
	modified:   rootfs/lib/systemd/system/halt.target
	modified:   rootfs/lib/systemd/system/hibernate.target
	modified:   rootfs/lib/systemd/system/hybrid-sleep.target
	modified:   rootfs/lib/systemd/system/initrd-cleanup.service
	modified:   rootfs/lib/systemd/system/initrd-fs.target
	modified:   rootfs/lib/systemd/system/initrd-parse-etc.service
	modified:   rootfs/lib/systemd/system/initrd-root-device.target
	modified:   rootfs/lib/systemd/system/initrd-root-fs.target
	modified:   rootfs/lib/systemd/system/initrd-switch-root.service
	modified:   rootfs/lib/systemd/system/initrd-switch-root.target
	modified:   rootfs/lib/systemd/system/initrd-udevadm-cleanup-db.service
	modified:   rootfs/lib/systemd/system/initrd.target
	modified:   rootfs/lib/systemd/system/kexec.target
	modified:   rootfs/lib/systemd/system/kmod-static-nodes.service
	modified:   rootfs/lib/systemd/system/ldconfig.service
	modified:   rootfs/lib/systemd/system/lighttpd.service
	modified:   rootfs/lib/systemd/system/local-fs-pre.target
	modified:   rootfs/lib/systemd/system/local-fs.target
	modified:   rootfs/lib/systemd/system/logrotate.service
	modified:   rootfs/lib/systemd/system/logrotate.timer
	modified:   rootfs/lib/systemd/system/machine.slice
	modified:   rootfs/lib/systemd/system/machines.target
	modified:   rootfs/lib/systemd/system/multi-user.target
	modified:   rootfs/lib/systemd/system/network-online.target
	modified:   rootfs/lib/systemd/system/network-pre.target
	modified:   rootfs/lib/systemd/system/network.target
	modified:   rootfs/lib/systemd/system/nfs-statd.service
	modified:   rootfs/lib/systemd/system/nss-lookup.target
	modified:   rootfs/lib/systemd/system/nss-user-lookup.target
	modified:   rootfs/lib/systemd/system/opkg-configure.service
	modified:   rootfs/lib/systemd/system/org.freedesktop.hostname1.busname
	modified:   rootfs/lib/systemd/system/org.freedesktop.locale1.busname
	modified:   rootfs/lib/systemd/system/org.freedesktop.login1.busname
	modified:   rootfs/lib/systemd/system/org.freedesktop.machine1.busname
	modified:   rootfs/lib/systemd/system/org.freedesktop.network1.busname
	modified:   rootfs/lib/systemd/system/org.freedesktop.resolve1.busname
	modified:   rootfs/lib/systemd/system/org.freedesktop.systemd1.busname
	modified:   rootfs/lib/systemd/system/org.freedesktop.timedate1.busname
	modified:   rootfs/lib/systemd/system/paths.target
	modified:   rootfs/lib/systemd/system/poweroff.target
	modified:   rootfs/lib/systemd/system/printer.target
	modified:   rootfs/lib/systemd/system/ptpd.service
	modified:   rootfs/lib/systemd/system/quotaon.service
	modified:   rootfs/lib/systemd/system/rc-local.service
	modified:   rootfs/lib/systemd/system/reboot.target
	modified:   rootfs/lib/systemd/system/remote-fs-pre.target
	modified:   rootfs/lib/systemd/system/remote-fs.target
	modified:   rootfs/lib/systemd/system/rescue.service
	modified:   rootfs/lib/systemd/system/rescue.target
	modified:   rootfs/lib/systemd/system/rngd.service
	modified:   rootfs/lib/systemd/system/rpcbind.service
	modified:   rootfs/lib/systemd/system/rpcbind.socket
	modified:   rootfs/lib/systemd/system/rpcbind.target
	modified:   rootfs/lib/systemd/system/run-postinsts.service
	modified:   rootfs/lib/systemd/system/serial-getty@.service
	modified:   rootfs/lib/systemd/system/shutdown.target
	modified:   rootfs/lib/systemd/system/sigpwr.target
	modified:   rootfs/lib/systemd/system/sleep.target
	modified:   rootfs/lib/systemd/system/slices.target
	modified:   rootfs/lib/systemd/system/smartcard.target
	modified:   rootfs/lib/systemd/system/snmpd.service
	modified:   rootfs/lib/systemd/system/sockets.target
	modified:   rootfs/lib/systemd/system/sound.target
	modified:   rootfs/lib/systemd/system/strongswan.service
	modified:   rootfs/lib/systemd/system/suspend.target
	modified:   rootfs/lib/systemd/system/swap.target
	modified:   rootfs/lib/systemd/system/sys-fs-fuse-connections.mount
	modified:   rootfs/lib/systemd/system/sys-kernel-config.mount
	modified:   rootfs/lib/systemd/system/sys-kernel-debug.mount
	modified:   rootfs/lib/systemd/system/sysinit.target
	modified:   rootfs/lib/systemd/system/syslog.socket
	modified:   rootfs/lib/systemd/system/system-update-cleanup.service
	modified:   rootfs/lib/systemd/system/system-update.target
	modified:   rootfs/lib/systemd/system/system.slice
	modified:   rootfs/lib/systemd/system/systemd-ask-password-console.path
	modified:   rootfs/lib/systemd/system/systemd-ask-password-console.service
	modified:   rootfs/lib/systemd/system/systemd-ask-password-wall.path
	modified:   rootfs/lib/systemd/system/systemd-ask-password-wall.service
	modified:   rootfs/lib/systemd/system/systemd-backlight@.service
	modified:   rootfs/lib/systemd/system/systemd-coredump.socket
	modified:   rootfs/lib/systemd/system/systemd-coredump@.service
	modified:   rootfs/lib/systemd/system/systemd-exit.service
	modified:   rootfs/lib/systemd/system/systemd-firstboot.service
	modified:   rootfs/lib/systemd/system/systemd-fsck-root.service
	modified:   rootfs/lib/systemd/system/systemd-fsck@.service
	modified:   rootfs/lib/systemd/system/systemd-halt.service
	modified:   rootfs/lib/systemd/system/systemd-hibernate-resume@.service
	modified:   rootfs/lib/systemd/system/systemd-hibernate.service
	modified:   rootfs/lib/systemd/system/systemd-hostnamed.service
	modified:   rootfs/lib/systemd/system/systemd-hwdb-update.service
	modified:   rootfs/lib/systemd/system/systemd-hybrid-sleep.service
	modified:   rootfs/lib/systemd/system/systemd-initctl.service
	modified:   rootfs/lib/systemd/system/systemd-initctl.socket
	modified:   rootfs/lib/systemd/system/systemd-journal-catalog-update.service
	modified:   rootfs/lib/systemd/system/systemd-journal-flush.service
	modified:   rootfs/lib/systemd/system/systemd-journald-audit.socket
	modified:   rootfs/lib/systemd/system/systemd-journald-dev-log.socket
	modified:   rootfs/lib/systemd/system/systemd-journald.service
	modified:   rootfs/lib/systemd/system/systemd-journald.socket
	modified:   rootfs/lib/systemd/system/systemd-kexec.service
	modified:   rootfs/lib/systemd/system/systemd-localed.service
	modified:   rootfs/lib/systemd/system/systemd-logind.service
	modified:   rootfs/lib/systemd/system/systemd-machine-id-commit.service
	modified:   rootfs/lib/systemd/system/systemd-machined.service
	modified:   rootfs/lib/systemd/system/systemd-modules-load.service
	modified:   rootfs/lib/systemd/system/systemd-networkd-wait-online.service
	modified:   rootfs/lib/systemd/system/systemd-networkd.service
	modified:   rootfs/lib/systemd/system/systemd-networkd.socket
	modified:   rootfs/lib/systemd/system/systemd-nspawn@.service
	modified:   rootfs/lib/systemd/system/systemd-poweroff.service
	modified:   rootfs/lib/systemd/system/systemd-quotacheck.service
	modified:   rootfs/lib/systemd/system/systemd-random-seed.service
	modified:   rootfs/lib/systemd/system/systemd-reboot.service
	modified:   rootfs/lib/systemd/system/systemd-remount-fs.service
	modified:   rootfs/lib/systemd/system/systemd-resolved.service
	modified:   rootfs/lib/systemd/system/systemd-rfkill.service
	modified:   rootfs/lib/systemd/system/systemd-rfkill.socket
	modified:   rootfs/lib/systemd/system/systemd-suspend.service
	modified:   rootfs/lib/systemd/system/systemd-sysctl.service
	modified:   rootfs/lib/systemd/system/systemd-sysusers.service
	modified:   rootfs/lib/systemd/system/systemd-timedated.service
	modified:   rootfs/lib/systemd/system/systemd-timesyncd.service
	modified:   rootfs/lib/systemd/system/systemd-tmpfiles-clean.service
	modified:   rootfs/lib/systemd/system/systemd-tmpfiles-clean.timer
	modified:   rootfs/lib/systemd/system/systemd-tmpfiles-setup-dev.service
	modified:   rootfs/lib/systemd/system/systemd-tmpfiles-setup.service
	modified:   rootfs/lib/systemd/system/systemd-udev-settle.service
	modified:   rootfs/lib/systemd/system/systemd-udev-trigger.service
	modified:   rootfs/lib/systemd/system/systemd-udevd-control.socket
	modified:   rootfs/lib/systemd/system/systemd-udevd-kernel.socket
	modified:   rootfs/lib/systemd/system/systemd-udevd.service
	modified:   rootfs/lib/systemd/system/systemd-update-done.service
	modified:   rootfs/lib/systemd/system/systemd-update-utmp-runlevel.service
	modified:   rootfs/lib/systemd/system/systemd-update-utmp.service
	modified:   rootfs/lib/systemd/system/systemd-user-sessions.service
	modified:   rootfs/lib/systemd/system/systemd-vconsole-setup.service
	modified:   rootfs/lib/systemd/system/systemd-volatile-root.service
	modified:   rootfs/lib/systemd/system/ti-mct-daemon.service
	modified:   rootfs/lib/systemd/system/tiipclad-daemon.service
	modified:   rootfs/lib/systemd/system/time-sync.target
	modified:   rootfs/lib/systemd/system/timers.target
	modified:   rootfs/lib/systemd/system/tmp.mount
	modified:   rootfs/lib/systemd/system/umount.target
	modified:   rootfs/lib/systemd/system/user.slice
	modified:   rootfs/lib/systemd/system/user@.service
	modified:   rootfs/lib/systemd/system/var-lib-machines.mount
	modified:   rootfs/lib/systemd/system/var-volatile-cache.service
	modified:   rootfs/lib/systemd/system/var-volatile-lib.service
	modified:   rootfs/lib/systemd/system/var-volatile-spool.service
	modified:   rootfs/lib/systemd/system/var-volatile-srv.service
	modified:   rootfs/media/.gitkeep
	modified:   rootfs/mnt/.gitkeep
	modified:   rootfs/proc/.gitkeep
	modified:   rootfs/run/.gitkeep
	modified:   rootfs/share/doc/iconv.1.html
	modified:   rootfs/share/doc/iconv.3.html
	modified:   rootfs/share/doc/iconv_close.3.html
	modified:   rootfs/share/doc/iconv_open.3.html
	modified:   rootfs/share/doc/iconv_open_into.3.html
	modified:   rootfs/share/doc/iconvctl.3.html
	modified:   rootfs/share/locale/af/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/bg/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/ca/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/cs/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/da/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/de/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/el/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/eo/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/es/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/et/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/fi/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/fr/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/ga/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/gl/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/hr/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/hu/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/id/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/it/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/ja/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/lt/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/nl/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/pl/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/pt_BR/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/rm/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/ro/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/ru/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/sk/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/sl/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/sq/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/sr/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/sv/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/tr/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/uk/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/vi/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/wa/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/zh_CN/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/locale/zh_TW/LC_MESSAGES/libiconv.mo
	modified:   rootfs/share/man/man1/iconv.1
	modified:   rootfs/share/man/man3/iconv.3
	modified:   rootfs/share/man/man3/iconv_close.3
	modified:   rootfs/share/man/man3/iconv_open.3
	modified:   rootfs/share/man/man3/iconv_open_into.3
	modified:   rootfs/share/man/man3/iconvctl.3
	modified:   rootfs/sys/.gitkeep
	modified:   rootfs/tmp/.gitkeep
	modified:   rootfs/usr/lib/libmodbus.a
	modified:   rootfs/usr/share/terminfo/N/ncrvt100wpp
	modified:   rootfs/usr/share/terminfo/P/p12
	modified:   rootfs/usr/share/terminfo/P/p14-w
	modified:   rootfs/usr/share/terminfo/P/p4
	modified:   rootfs/usr/share/terminfo/P/p5
	modified:   rootfs/usr/share/terminfo/P/p7
	modified:   rootfs/usr/share/terminfo/P/p8
	modified:   rootfs/usr/share/terminfo/P/p9
	modified:   rootfs/usr/share/terminfo/P/p9-8
	modified:   rootfs/usr/share/terminfo/P/p9-8-w
	modified:   rootfs/usr/share/terminfo/P/p9-w
	modified:   rootfs/usr/share/terminfo/e/Eterm
	modified:   rootfs/usr/share/terminfo/e/Eterm-color
	modified:   rootfs/usr/share/terminfo/p/P12-M-W
	modified:   rootfs/usr/share/terminfo/p/P12-W
	modified:   rootfs/usr/share/terminfo/p/P14
	modified:   rootfs/usr/share/terminfo/p/P14-M
	modified:   rootfs/usr/share/terminfo/p/P14-M-W
	modified:   rootfs/usr/share/terminfo/p/P8-W
	modified:   rootfs/usr/share/terminfo/p/P9-8
	modified:   rootfs/usr/share/terminfo/p/P9-8-W
	modified:   rootfs/usr/share/terminfo/p/P9-W
	modified:   tools/binarymaker/mkbin
	modified:   tools/binarymaker/mkbin.o
	modified:   tools/broadcast_test/Makefile
	modified:   tools/broadcast_test/broadcast.c
	modified:   tools/busybox-1.30.1/.busybox_unstripped.cmd
	modified:   tools/busybox-1.30.1/.config
	modified:   tools/busybox-1.30.1/.config.old
	modified:   tools/busybox-1.30.1/.indent.pro
	modified:   tools/busybox-1.30.1/.kconfig.d
	modified:   tools/busybox-1.30.1/.kernelrelease
	modified:   tools/busybox-1.30.1/0004-bc-fold-xc_lex_more_input-into-peek_inbuf.patch
	modified:   tools/busybox-1.30.1/0005-bc-support-ibase-up-to-36-GNU-compat.patch
	modified:   tools/busybox-1.30.1/0006-bc-remove-superfluous-assigment.patch
	modified:   tools/busybox-1.30.1/0007-bc-in-xc_read_line-check-C-on-NUL-input-bytes-too.patch
	modified:   tools/busybox-1.30.1/0010-bc-upstream-fixes.patch
	modified:   tools/busybox-1.30.1/0011-bc-speed-up-string-printing-fix-print.patch
	modified:   tools/busybox-1.30.1/0012-bc-generate-large-bc-tests-on-the-fly-5-mbytes-in-th.patch
	modified:   tools/busybox-1.30.1/0013-bc-make-error-line-number-also-size_t-like-everythin.patch
	modified:   tools/busybox-1.30.1/0014-bc-fix-.-return-to-work-disallow-return.patch
	modified:   tools/busybox-1.30.1/0015-bc-remove-extra-div-0-test-remove-test-for-string-fu.patch
	modified:   tools/busybox-1.30.1/0016-bc-add-a-palceholder-comment-for-void-return.patch
	modified:   tools/busybox-1.30.1/0017-bc-eliminate-struct-BcInstPtr-results_len_before_cal.patch
	modified:   tools/busybox-1.30.1/0018-dc-fix.patch
	modified:   tools/busybox-1.30.1/0019-dc-fit-returning-of-string.patch
	modified:   tools/busybox-1.30.1/0020-bc-support-void-functions-GNU-compat.patch
	modified:   tools/busybox-1.30.1/0021-bc-formatting-changes-added-a-FIXME-comment-no-logic.patch
	modified:   tools/busybox-1.30.1/0022-bc-shorten-limits-output.patch
	modified:   tools/busybox-1.30.1/0025-ls-make-i-compatible-with-coreutils-don-t-follow-sym.patch
	modified:   tools/busybox-1.30.1/0038-bc-disallow-invalid-syntax-like-print-1-print-2.patch
	modified:   tools/busybox-1.30.1/0039-bc-zbc_parse_expr_empty_ok-is-unused-except-by-zbc_p.patch
	modified:   tools/busybox-1.30.1/0040-bc-remove-empty-expression-check-message-parsing-fai.patch
	modified:   tools/busybox-1.30.1/0041-bc-code-shrink.patch
	modified:   tools/busybox-1.30.1/0056-capability-fix-string-comparison-in-cap_name_to_numb.patch
	modified:   tools/busybox-1.30.1/0060-sed-Fix-backslash-parsing-for-w-command-arg.patch
	modified:   tools/busybox-1.30.1/0063-ip-link-fix-mismatched-enums-in-vlan_parse_opt-close.patch
	modified:   tools/busybox-1.30.1/0064-ip-link-Fix-vlan-proto-closes-8261-and-11638.patch
	modified:   tools/busybox-1.30.1/0066-bc-implement-pass-by-reference-code-from-upstream.patch
	modified:   tools/busybox-1.30.1/0067-grep-fix-x-v-with-certain-pattern-orders.patch
	modified:   tools/busybox-1.30.1/0070-lineedit-fix-SEGV-in-isk-hexedit-ed-closes-11661.patch
	modified:   tools/busybox-1.30.1/0073-chcon-Fix-typo-in-ACTION_RECURSE.patch
	modified:   tools/busybox-1.30.1/AUTHORS
	modified:   tools/busybox-1.30.1/Config.in
	modified:   tools/busybox-1.30.1/INSTALL
	modified:   tools/busybox-1.30.1/LICENSE
	modified:   tools/busybox-1.30.1/Makefile
	modified:   tools/busybox-1.30.1/Makefile.custom
	modified:   tools/busybox-1.30.1/Makefile.flags
	modified:   tools/busybox-1.30.1/Makefile.help
	modified:   tools/busybox-1.30.1/NOFORK_NOEXEC.lst
	modified:   tools/busybox-1.30.1/README
	modified:   tools/busybox-1.30.1/TODO
	modified:   tools/busybox-1.30.1/TODO_unicode
	modified:   tools/busybox-1.30.1/applets/.applet_tables.cmd
	modified:   tools/busybox-1.30.1/applets/.applets.o.cmd
	modified:   tools/busybox-1.30.1/applets/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/applets/.usage.cmd
	modified:   tools/busybox-1.30.1/applets/.usage_pod.cmd
	modified:   tools/busybox-1.30.1/applets/Kbuild
	modified:   tools/busybox-1.30.1/applets/Kbuild.src
	modified:   tools/busybox-1.30.1/applets/applet_tables.c
	modified:   tools/busybox-1.30.1/applets/applets.c
	modified:   tools/busybox-1.30.1/applets/applets.o
	modified:   tools/busybox-1.30.1/applets/built-in.o
	modified:   tools/busybox-1.30.1/applets/individual.c
	modified:   tools/busybox-1.30.1/applets/usage.c
	modified:   tools/busybox-1.30.1/applets/usage_pod.c
	modified:   tools/busybox-1.30.1/arch/i386/Makefile
	modified:   tools/busybox-1.30.1/arch/sparc/Makefile
	modified:   tools/busybox-1.30.1/arch/sparc64/Makefile
	modified:   tools/busybox-1.30.1/archival/.bbunzip.o.cmd
	modified:   tools/busybox-1.30.1/archival/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/archival/.bzip2.o.cmd
	modified:   tools/busybox-1.30.1/archival/.cpio.o.cmd
	modified:   tools/busybox-1.30.1/archival/.dpkg.o.cmd
	modified:   tools/busybox-1.30.1/archival/.dpkg_deb.o.cmd
	modified:   tools/busybox-1.30.1/archival/.gzip.o.cmd
	modified:   tools/busybox-1.30.1/archival/.lib.a.cmd
	modified:   tools/busybox-1.30.1/archival/.lzop.o.cmd
	modified:   tools/busybox-1.30.1/archival/.rpm.o.cmd
	modified:   tools/busybox-1.30.1/archival/.tar.o.cmd
	modified:   tools/busybox-1.30.1/archival/.unzip.o.cmd
	modified:   tools/busybox-1.30.1/archival/Config.in
	modified:   tools/busybox-1.30.1/archival/Config.src
	modified:   tools/busybox-1.30.1/archival/Kbuild
	modified:   tools/busybox-1.30.1/archival/Kbuild.src
	modified:   tools/busybox-1.30.1/archival/ar.c
	modified:   tools/busybox-1.30.1/archival/bbunzip.c
	modified:   tools/busybox-1.30.1/archival/bbunzip.o
	modified:   tools/busybox-1.30.1/archival/bbunzip_test.sh
	modified:   tools/busybox-1.30.1/archival/bbunzip_test2.sh
	modified:   tools/busybox-1.30.1/archival/bbunzip_test3.sh
	modified:   tools/busybox-1.30.1/archival/built-in.o
	modified:   tools/busybox-1.30.1/archival/bzip2.c
	modified:   tools/busybox-1.30.1/archival/bzip2.o
	modified:   tools/busybox-1.30.1/archival/cpio.c
	modified:   tools/busybox-1.30.1/archival/cpio.o
	modified:   tools/busybox-1.30.1/archival/dpkg.c
	modified:   tools/busybox-1.30.1/archival/dpkg.o
	modified:   tools/busybox-1.30.1/archival/dpkg_deb.c
	modified:   tools/busybox-1.30.1/archival/dpkg_deb.o
	modified:   tools/busybox-1.30.1/archival/gzip.c
	modified:   tools/busybox-1.30.1/archival/gzip.o
	modified:   tools/busybox-1.30.1/archival/lib.a
	modified:   tools/busybox-1.30.1/archival/libarchive/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.common.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.data_align.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.data_extract_all.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.data_extract_to_command.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.data_extract_to_stdout.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.data_skip.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.decompress_bunzip2.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.decompress_gunzip.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.decompress_unlzma.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.decompress_unxz.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.filter_accept_all.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.filter_accept_list.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.filter_accept_list_reassign.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.filter_accept_reject_list.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.find_list_entry.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.get_header_ar.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.get_header_cpio.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.get_header_tar.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.get_header_tar_bz2.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.get_header_tar_gz.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.get_header_tar_lzma.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.get_header_tar_xz.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.header_list.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.header_skip.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.header_verbose_list.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.init_handle.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.lib.a.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.lzo1x_1.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.lzo1x_1o.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.lzo1x_d.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.open_transformer.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.seek_by_jump.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.seek_by_read.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.unpack_ar_archive.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.unsafe_prefix.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/.unsafe_symlink_target.o.cmd
	modified:   tools/busybox-1.30.1/archival/libarchive/Kbuild
	modified:   tools/busybox-1.30.1/archival/libarchive/Kbuild.src
	modified:   tools/busybox-1.30.1/archival/libarchive/built-in.o
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/LICENSE
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/README
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/blocksort.c
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/bzlib.c
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/bzlib.h
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/bzlib_private.h
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/compress.c
	modified:   tools/busybox-1.30.1/archival/libarchive/bz/huffman.c
	modified:   tools/busybox-1.30.1/archival/libarchive/common.c
	modified:   tools/busybox-1.30.1/archival/libarchive/common.o
	modified:   tools/busybox-1.30.1/archival/libarchive/data_align.c
	modified:   tools/busybox-1.30.1/archival/libarchive/data_align.o
	modified:   tools/busybox-1.30.1/archival/libarchive/data_extract_all.c
	modified:   tools/busybox-1.30.1/archival/libarchive/data_extract_all.o
	modified:   tools/busybox-1.30.1/archival/libarchive/data_extract_to_command.c
	modified:   tools/busybox-1.30.1/archival/libarchive/data_extract_to_command.o
	modified:   tools/busybox-1.30.1/archival/libarchive/data_extract_to_stdout.c
	modified:   tools/busybox-1.30.1/archival/libarchive/data_extract_to_stdout.o
	modified:   tools/busybox-1.30.1/archival/libarchive/data_skip.c
	modified:   tools/busybox-1.30.1/archival/libarchive/data_skip.o
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_bunzip2.c
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_bunzip2.o
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_gunzip.c
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_gunzip.o
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_uncompress.c
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_unlzma.c
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_unlzma.o
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_unxz.c
	modified:   tools/busybox-1.30.1/archival/libarchive/decompress_unxz.o
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_all.c
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_all.o
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_list.c
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_list.o
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_list_reassign.c
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_list_reassign.o
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_reject_list.c
	modified:   tools/busybox-1.30.1/archival/libarchive/filter_accept_reject_list.o
	modified:   tools/busybox-1.30.1/archival/libarchive/find_list_entry.c
	modified:   tools/busybox-1.30.1/archival/libarchive/find_list_entry.o
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_ar.c
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_ar.o
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_cpio.c
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_cpio.o
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar.c
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar.o
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_bz2.c
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_bz2.o
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_gz.c
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_gz.o
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_lzma.c
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_lzma.o
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_xz.c
	modified:   tools/busybox-1.30.1/archival/libarchive/get_header_tar_xz.o
	modified:   tools/busybox-1.30.1/archival/libarchive/header_list.c
	modified:   tools/busybox-1.30.1/archival/libarchive/header_list.o
	modified:   tools/busybox-1.30.1/archival/libarchive/header_skip.c
	modified:   tools/busybox-1.30.1/archival/libarchive/header_skip.o
	modified:   tools/busybox-1.30.1/archival/libarchive/header_verbose_list.c
	modified:   tools/busybox-1.30.1/archival/libarchive/header_verbose_list.o
	modified:   tools/busybox-1.30.1/archival/libarchive/init_handle.c
	modified:   tools/busybox-1.30.1/archival/libarchive/init_handle.o
	modified:   tools/busybox-1.30.1/archival/libarchive/lib.a
	modified:   tools/busybox-1.30.1/archival/libarchive/liblzo.h
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_1.c
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_1.o
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_1o.c
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_1o.o
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_9x.c
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_c.c
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_d.c
	modified:   tools/busybox-1.30.1/archival/libarchive/lzo1x_d.o
	modified:   tools/busybox-1.30.1/archival/libarchive/open_transformer.c
	modified:   tools/busybox-1.30.1/archival/libarchive/open_transformer.o
	modified:   tools/busybox-1.30.1/archival/libarchive/seek_by_jump.c
	modified:   tools/busybox-1.30.1/archival/libarchive/seek_by_jump.o
	modified:   tools/busybox-1.30.1/archival/libarchive/seek_by_read.c
	modified:   tools/busybox-1.30.1/archival/libarchive/seek_by_read.o
	modified:   tools/busybox-1.30.1/archival/libarchive/unpack_ar_archive.c
	modified:   tools/busybox-1.30.1/archival/libarchive/unpack_ar_archive.o
	modified:   tools/busybox-1.30.1/archival/libarchive/unsafe_prefix.c
	modified:   tools/busybox-1.30.1/archival/libarchive/unsafe_prefix.o
	modified:   tools/busybox-1.30.1/archival/libarchive/unsafe_symlink_target.c
	modified:   tools/busybox-1.30.1/archival/libarchive/unsafe_symlink_target.o
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/README
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz.h
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz_config.h
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz_dec_bcj.c
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz_dec_lzma2.c
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz_dec_stream.c
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz_lzma2.h
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz_private.h
	modified:   tools/busybox-1.30.1/archival/libarchive/unxz/xz_stream.h
	modified:   tools/busybox-1.30.1/archival/lzop.c
	modified:   tools/busybox-1.30.1/archival/lzop.o
	modified:   tools/busybox-1.30.1/archival/rpm.c
	modified:   tools/busybox-1.30.1/archival/rpm.h
	modified:   tools/busybox-1.30.1/archival/rpm.o
	modified:   tools/busybox-1.30.1/archival/tar.c
	modified:   tools/busybox-1.30.1/archival/tar.o
	modified:   tools/busybox-1.30.1/archival/unzip.c
	modified:   tools/busybox-1.30.1/archival/unzip.o
	modified:   tools/busybox-1.30.1/busybox.links
	modified:   tools/busybox-1.30.1/busybox_unstripped.map
	modified:   tools/busybox-1.30.1/busybox_unstripped.out
	modified:   tools/busybox-1.30.1/configs/TEST_nommu_defconfig
	modified:   tools/busybox-1.30.1/configs/TEST_noprintf_defconfig
	modified:   tools/busybox-1.30.1/configs/TEST_rh9_defconfig
	modified:   tools/busybox-1.30.1/configs/android2_defconfig
	modified:   tools/busybox-1.30.1/configs/android_502_defconfig
	modified:   tools/busybox-1.30.1/configs/android_defconfig
	modified:   tools/busybox-1.30.1/configs/android_ndk_defconfig
	modified:   tools/busybox-1.30.1/configs/cygwin_defconfig
	modified:   tools/busybox-1.30.1/configs/freebsd_defconfig
	modified:   tools/busybox-1.30.1/console-tools/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.chvt.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.clear.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.deallocvt.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.dumpkmap.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.fgconsole.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.kbd_mode.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.lib.a.cmd
	modified:   tools/busybox-1.30.1/console-tools/.loadfont.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.loadkmap.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.openvt.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.reset.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.resize.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.setconsole.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.setkeycodes.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.setlogcons.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/.showkey.o.cmd
	modified:   tools/busybox-1.30.1/console-tools/Config.in
	modified:   tools/busybox-1.30.1/console-tools/Config.src
	modified:   tools/busybox-1.30.1/console-tools/Kbuild
	modified:   tools/busybox-1.30.1/console-tools/Kbuild.src
	modified:   tools/busybox-1.30.1/console-tools/built-in.o
	modified:   tools/busybox-1.30.1/console-tools/chvt.c
	modified:   tools/busybox-1.30.1/console-tools/chvt.o
	modified:   tools/busybox-1.30.1/console-tools/clear.c
	modified:   tools/busybox-1.30.1/console-tools/clear.o
	modified:   tools/busybox-1.30.1/console-tools/deallocvt.c
	modified:   tools/busybox-1.30.1/console-tools/deallocvt.o
	modified:   tools/busybox-1.30.1/console-tools/dumpkmap.c
	modified:   tools/busybox-1.30.1/console-tools/dumpkmap.o
	modified:   tools/busybox-1.30.1/console-tools/fgconsole.c
	modified:   tools/busybox-1.30.1/console-tools/fgconsole.o
	modified:   tools/busybox-1.30.1/console-tools/kbd_mode.c
	modified:   tools/busybox-1.30.1/console-tools/kbd_mode.o
	modified:   tools/busybox-1.30.1/console-tools/lib.a
	modified:   tools/busybox-1.30.1/console-tools/loadfont.c
	modified:   tools/busybox-1.30.1/console-tools/loadfont.o
	modified:   tools/busybox-1.30.1/console-tools/loadkmap.c
	modified:   tools/busybox-1.30.1/console-tools/loadkmap.o
	modified:   tools/busybox-1.30.1/console-tools/openvt.c
	modified:   tools/busybox-1.30.1/console-tools/openvt.o
	modified:   tools/busybox-1.30.1/console-tools/reset.c
	modified:   tools/busybox-1.30.1/console-tools/reset.o
	modified:   tools/busybox-1.30.1/console-tools/resize.c
	modified:   tools/busybox-1.30.1/console-tools/resize.o
	modified:   tools/busybox-1.30.1/console-tools/setconsole.c
	modified:   tools/busybox-1.30.1/console-tools/setconsole.o
	modified:   tools/busybox-1.30.1/console-tools/setkeycodes.c
	modified:   tools/busybox-1.30.1/console-tools/setkeycodes.o
	modified:   tools/busybox-1.30.1/console-tools/setlogcons.c
	modified:   tools/busybox-1.30.1/console-tools/setlogcons.o
	modified:   tools/busybox-1.30.1/console-tools/showkey.c
	modified:   tools/busybox-1.30.1/console-tools/showkey.o
	modified:   tools/busybox-1.30.1/coreutils/.basename.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.cat.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.chgrp.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.chmod.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.chown.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.chroot.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.cksum.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.comm.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.cp.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.cut.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.date.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.dd.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.df.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.dirname.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.dos2unix.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.du.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.echo.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.env.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.expand.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.expr.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.factor.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.false.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.fold.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.fsync.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.head.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.hostid.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.id.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.install.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/coreutils/.link.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.ln.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.logname.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.ls.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.md5_sha1_sum.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.mkdir.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.mkfifo.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.mknod.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.mktemp.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.mv.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.nice.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.nl.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.nohup.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.nproc.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.od.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.paste.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.printenv.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.printf.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.pwd.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.readlink.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.realpath.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.rm.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.rmdir.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.seq.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.shred.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.shuf.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.sleep.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.sort.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.split.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.stat.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.stty.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.sum.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.sync.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.tac.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.tail.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.tee.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.test.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.test_ptr_hack.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.timeout.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.touch.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.tr.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.true.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.truncate.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.tty.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.uname.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.uniq.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.unlink.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.usleep.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.uudecode.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.uuencode.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.wc.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.who.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.whoami.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/.yes.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/Config.in
	modified:   tools/busybox-1.30.1/coreutils/Config.src
	modified:   tools/busybox-1.30.1/coreutils/Kbuild
	modified:   tools/busybox-1.30.1/coreutils/Kbuild.src
	modified:   tools/busybox-1.30.1/coreutils/basename.c
	modified:   tools/busybox-1.30.1/coreutils/basename.o
	modified:   tools/busybox-1.30.1/coreutils/built-in.o
	modified:   tools/busybox-1.30.1/coreutils/cat.c
	modified:   tools/busybox-1.30.1/coreutils/cat.o
	modified:   tools/busybox-1.30.1/coreutils/chgrp.c
	modified:   tools/busybox-1.30.1/coreutils/chgrp.o
	modified:   tools/busybox-1.30.1/coreutils/chmod.c
	modified:   tools/busybox-1.30.1/coreutils/chmod.o
	modified:   tools/busybox-1.30.1/coreutils/chown.c
	modified:   tools/busybox-1.30.1/coreutils/chown.o
	modified:   tools/busybox-1.30.1/coreutils/chroot.c
	modified:   tools/busybox-1.30.1/coreutils/chroot.o
	modified:   tools/busybox-1.30.1/coreutils/cksum.c
	modified:   tools/busybox-1.30.1/coreutils/cksum.o
	modified:   tools/busybox-1.30.1/coreutils/comm.c
	modified:   tools/busybox-1.30.1/coreutils/comm.o
	modified:   tools/busybox-1.30.1/coreutils/cp.c
	modified:   tools/busybox-1.30.1/coreutils/cp.o
	modified:   tools/busybox-1.30.1/coreutils/cut.c
	modified:   tools/busybox-1.30.1/coreutils/cut.o
	modified:   tools/busybox-1.30.1/coreutils/date.c
	modified:   tools/busybox-1.30.1/coreutils/date.o
	modified:   tools/busybox-1.30.1/coreutils/dd.c
	modified:   tools/busybox-1.30.1/coreutils/dd.o
	modified:   tools/busybox-1.30.1/coreutils/df.c
	modified:   tools/busybox-1.30.1/coreutils/df.o
	modified:   tools/busybox-1.30.1/coreutils/dirname.c
	modified:   tools/busybox-1.30.1/coreutils/dirname.o
	modified:   tools/busybox-1.30.1/coreutils/dos2unix.c
	modified:   tools/busybox-1.30.1/coreutils/dos2unix.o
	modified:   tools/busybox-1.30.1/coreutils/du.c
	modified:   tools/busybox-1.30.1/coreutils/du.o
	modified:   tools/busybox-1.30.1/coreutils/echo.c
	modified:   tools/busybox-1.30.1/coreutils/echo.o
	modified:   tools/busybox-1.30.1/coreutils/env.c
	modified:   tools/busybox-1.30.1/coreutils/env.o
	modified:   tools/busybox-1.30.1/coreutils/expand.c
	modified:   tools/busybox-1.30.1/coreutils/expand.o
	modified:   tools/busybox-1.30.1/coreutils/expr.c
	modified:   tools/busybox-1.30.1/coreutils/expr.o
	modified:   tools/busybox-1.30.1/coreutils/factor.c
	modified:   tools/busybox-1.30.1/coreutils/factor.o
	modified:   tools/busybox-1.30.1/coreutils/false.c
	modified:   tools/busybox-1.30.1/coreutils/false.o
	modified:   tools/busybox-1.30.1/coreutils/fold.c
	modified:   tools/busybox-1.30.1/coreutils/fold.o
	modified:   tools/busybox-1.30.1/coreutils/fsync.c
	modified:   tools/busybox-1.30.1/coreutils/fsync.o
	modified:   tools/busybox-1.30.1/coreutils/head.c
	modified:   tools/busybox-1.30.1/coreutils/head.o
	modified:   tools/busybox-1.30.1/coreutils/hostid.c
	modified:   tools/busybox-1.30.1/coreutils/hostid.o
	modified:   tools/busybox-1.30.1/coreutils/id.c
	modified:   tools/busybox-1.30.1/coreutils/id.o
	modified:   tools/busybox-1.30.1/coreutils/install.c
	modified:   tools/busybox-1.30.1/coreutils/install.o
	modified:   tools/busybox-1.30.1/coreutils/lib.a
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/.cp_mv_stat.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/.getopt_mk_fifo_nod.o.cmd
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/Kbuild
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/Kbuild.src
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/built-in.o
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/coreutils.h
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/cp_mv_stat.c
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/cp_mv_stat.o
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/getopt_mk_fifo_nod.c
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/getopt_mk_fifo_nod.o
	modified:   tools/busybox-1.30.1/coreutils/libcoreutils/lib.a
	modified:   tools/busybox-1.30.1/coreutils/link.c
	modified:   tools/busybox-1.30.1/coreutils/link.o
	modified:   tools/busybox-1.30.1/coreutils/ln.c
	modified:   tools/busybox-1.30.1/coreutils/ln.o
	modified:   tools/busybox-1.30.1/coreutils/logname.c
	modified:   tools/busybox-1.30.1/coreutils/logname.o
	modified:   tools/busybox-1.30.1/coreutils/ls.c
	modified:   tools/busybox-1.30.1/coreutils/ls.o
	modified:   tools/busybox-1.30.1/coreutils/md5_sha1_sum.c
	modified:   tools/busybox-1.30.1/coreutils/md5_sha1_sum.o
	modified:   tools/busybox-1.30.1/coreutils/mkdir.c
	modified:   tools/busybox-1.30.1/coreutils/mkdir.o
	modified:   tools/busybox-1.30.1/coreutils/mkfifo.c
	modified:   tools/busybox-1.30.1/coreutils/mkfifo.o
	modified:   tools/busybox-1.30.1/coreutils/mknod.c
	modified:   tools/busybox-1.30.1/coreutils/mknod.o
	modified:   tools/busybox-1.30.1/coreutils/mktemp.c
	modified:   tools/busybox-1.30.1/coreutils/mktemp.o
	modified:   tools/busybox-1.30.1/coreutils/mv.c
	modified:   tools/busybox-1.30.1/coreutils/mv.o
	modified:   tools/busybox-1.30.1/coreutils/nice.c
	modified:   tools/busybox-1.30.1/coreutils/nice.o
	modified:   tools/busybox-1.30.1/coreutils/nl.c
	modified:   tools/busybox-1.30.1/coreutils/nl.o
	modified:   tools/busybox-1.30.1/coreutils/nohup.c
	modified:   tools/busybox-1.30.1/coreutils/nohup.o
	modified:   tools/busybox-1.30.1/coreutils/nproc.c
	modified:   tools/busybox-1.30.1/coreutils/nproc.o
	modified:   tools/busybox-1.30.1/coreutils/od.c
	modified:   tools/busybox-1.30.1/coreutils/od.o
	modified:   tools/busybox-1.30.1/coreutils/od_bloaty.c
	modified:   tools/busybox-1.30.1/coreutils/paste.c
	modified:   tools/busybox-1.30.1/coreutils/paste.o
	modified:   tools/busybox-1.30.1/coreutils/printenv.c
	modified:   tools/busybox-1.30.1/coreutils/printenv.o
	modified:   tools/busybox-1.30.1/coreutils/printf.c
	modified:   tools/busybox-1.30.1/coreutils/printf.o
	modified:   tools/busybox-1.30.1/coreutils/pwd.c
	modified:   tools/busybox-1.30.1/coreutils/pwd.o
	modified:   tools/busybox-1.30.1/coreutils/readlink.c
	modified:   tools/busybox-1.30.1/coreutils/readlink.o
	modified:   tools/busybox-1.30.1/coreutils/realpath.c
	modified:   tools/busybox-1.30.1/coreutils/realpath.o
	modified:   tools/busybox-1.30.1/coreutils/rm.c
	modified:   tools/busybox-1.30.1/coreutils/rm.o
	modified:   tools/busybox-1.30.1/coreutils/rmdir.c
	modified:   tools/busybox-1.30.1/coreutils/rmdir.o
	modified:   tools/busybox-1.30.1/coreutils/seq.c
	modified:   tools/busybox-1.30.1/coreutils/seq.o
	modified:   tools/busybox-1.30.1/coreutils/shred.c
	modified:   tools/busybox-1.30.1/coreutils/shred.o
	modified:   tools/busybox-1.30.1/coreutils/shuf.c
	modified:   tools/busybox-1.30.1/coreutils/shuf.o
	modified:   tools/busybox-1.30.1/coreutils/sleep.c
	modified:   tools/busybox-1.30.1/coreutils/sleep.o
	modified:   tools/busybox-1.30.1/coreutils/sort.c
	modified:   tools/busybox-1.30.1/coreutils/sort.o
	modified:   tools/busybox-1.30.1/coreutils/split.c
	modified:   tools/busybox-1.30.1/coreutils/split.o
	modified:   tools/busybox-1.30.1/coreutils/stat.c
	modified:   tools/busybox-1.30.1/coreutils/stat.o
	modified:   tools/busybox-1.30.1/coreutils/stty.c
	modified:   tools/busybox-1.30.1/coreutils/stty.o
	modified:   tools/busybox-1.30.1/coreutils/sum.c
	modified:   tools/busybox-1.30.1/coreutils/sum.o
	modified:   tools/busybox-1.30.1/coreutils/sync.c
	modified:   tools/busybox-1.30.1/coreutils/sync.o
	modified:   tools/busybox-1.30.1/coreutils/tac.c
	modified:   tools/busybox-1.30.1/coreutils/tac.o
	modified:   tools/busybox-1.30.1/coreutils/tail.c
	modified:   tools/busybox-1.30.1/coreutils/tail.o
	modified:   tools/busybox-1.30.1/coreutils/tee.c
	modified:   tools/busybox-1.30.1/coreutils/tee.o
	modified:   tools/busybox-1.30.1/coreutils/test.c
	modified:   tools/busybox-1.30.1/coreutils/test.o
	modified:   tools/busybox-1.30.1/coreutils/test_ptr_hack.c
	modified:   tools/busybox-1.30.1/coreutils/test_ptr_hack.o
	modified:   tools/busybox-1.30.1/coreutils/timeout.c
	modified:   tools/busybox-1.30.1/coreutils/timeout.o
	modified:   tools/busybox-1.30.1/coreutils/touch.c
	modified:   tools/busybox-1.30.1/coreutils/touch.o
	modified:   tools/busybox-1.30.1/coreutils/tr.c
	modified:   tools/busybox-1.30.1/coreutils/tr.o
	modified:   tools/busybox-1.30.1/coreutils/true.c
	modified:   tools/busybox-1.30.1/coreutils/true.o
	modified:   tools/busybox-1.30.1/coreutils/truncate.c
	modified:   tools/busybox-1.30.1/coreutils/truncate.o
	modified:   tools/busybox-1.30.1/coreutils/tty.c
	modified:   tools/busybox-1.30.1/coreutils/tty.o
	modified:   tools/busybox-1.30.1/coreutils/uname.c
	modified:   tools/busybox-1.30.1/coreutils/uname.o
	modified:   tools/busybox-1.30.1/coreutils/uniq.c
	modified:   tools/busybox-1.30.1/coreutils/uniq.o
	modified:   tools/busybox-1.30.1/coreutils/unlink.c
	modified:   tools/busybox-1.30.1/coreutils/unlink.o
	modified:   tools/busybox-1.30.1/coreutils/usleep.c
	modified:   tools/busybox-1.30.1/coreutils/usleep.o
	modified:   tools/busybox-1.30.1/coreutils/uudecode.c
	modified:   tools/busybox-1.30.1/coreutils/uudecode.o
	modified:   tools/busybox-1.30.1/coreutils/uuencode.c
	modified:   tools/busybox-1.30.1/coreutils/uuencode.o
	modified:   tools/busybox-1.30.1/coreutils/wc.c
	modified:   tools/busybox-1.30.1/coreutils/wc.o
	modified:   tools/busybox-1.30.1/coreutils/who.c
	modified:   tools/busybox-1.30.1/coreutils/who.o
	modified:   tools/busybox-1.30.1/coreutils/whoami.c
	modified:   tools/busybox-1.30.1/coreutils/whoami.o
	modified:   tools/busybox-1.30.1/coreutils/yes.c
	modified:   tools/busybox-1.30.1/coreutils/yes.o
	modified:   tools/busybox-1.30.1/debianutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/debianutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/debianutils/.pipe_progress.o.cmd
	modified:   tools/busybox-1.30.1/debianutils/.run_parts.o.cmd
	modified:   tools/busybox-1.30.1/debianutils/.start_stop_daemon.o.cmd
	modified:   tools/busybox-1.30.1/debianutils/.which.o.cmd
	modified:   tools/busybox-1.30.1/debianutils/Config.in
	modified:   tools/busybox-1.30.1/debianutils/Config.src
	modified:   tools/busybox-1.30.1/debianutils/Kbuild
	modified:   tools/busybox-1.30.1/debianutils/Kbuild.src
	modified:   tools/busybox-1.30.1/debianutils/built-in.o
	modified:   tools/busybox-1.30.1/debianutils/lib.a
	modified:   tools/busybox-1.30.1/debianutils/pipe_progress.c
	modified:   tools/busybox-1.30.1/debianutils/pipe_progress.o
	modified:   tools/busybox-1.30.1/debianutils/run_parts.c
	modified:   tools/busybox-1.30.1/debianutils/run_parts.o
	modified:   tools/busybox-1.30.1/debianutils/start_stop_daemon.c
	modified:   tools/busybox-1.30.1/debianutils/start_stop_daemon.o
	modified:   tools/busybox-1.30.1/debianutils/which.c
	modified:   tools/busybox-1.30.1/debianutils/which.o
	modified:   tools/busybox-1.30.1/docs/BusyBox.html
	modified:   tools/busybox-1.30.1/docs/busybox.1
	modified:   tools/busybox-1.30.1/docs/busybox.net/BusyBox.html
	modified:   tools/busybox-1.30.1/docs/busybox.pod
	modified:   tools/busybox-1.30.1/docs/busybox_footer.pod
	modified:   tools/busybox-1.30.1/docs/busybox_header.pod
	modified:   tools/busybox-1.30.1/docs/cgi/cl.html
	modified:   tools/busybox-1.30.1/docs/cgi/env.html
	modified:   tools/busybox-1.30.1/docs/cgi/in.html
	modified:   tools/busybox-1.30.1/docs/cgi/interface.html
	modified:   tools/busybox-1.30.1/docs/cgi/out.html
	modified:   tools/busybox-1.30.1/docs/ctty.htm
	modified:   tools/busybox-1.30.1/docs/draft-coar-cgi-v11-03-clean.html
	modified:   tools/busybox-1.30.1/docs/sigint.htm
	modified:   tools/busybox-1.30.1/e2fsprogs/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/e2fsprogs/.chattr.o.cmd
	modified:   tools/busybox-1.30.1/e2fsprogs/.e2fs_lib.o.cmd
	modified:   tools/busybox-1.30.1/e2fsprogs/.fsck.o.cmd
	modified:   tools/busybox-1.30.1/e2fsprogs/.lib.a.cmd
	modified:   tools/busybox-1.30.1/e2fsprogs/.lsattr.o.cmd
	modified:   tools/busybox-1.30.1/e2fsprogs/Config.in
	modified:   tools/busybox-1.30.1/e2fsprogs/Config.src
	modified:   tools/busybox-1.30.1/e2fsprogs/Kbuild
	modified:   tools/busybox-1.30.1/e2fsprogs/Kbuild.src
	modified:   tools/busybox-1.30.1/e2fsprogs/README
	modified:   tools/busybox-1.30.1/e2fsprogs/built-in.o
	modified:   tools/busybox-1.30.1/e2fsprogs/chattr.c
	modified:   tools/busybox-1.30.1/e2fsprogs/chattr.o
	modified:   tools/busybox-1.30.1/e2fsprogs/e2fs_lib.c
	modified:   tools/busybox-1.30.1/e2fsprogs/e2fs_lib.h
	modified:   tools/busybox-1.30.1/e2fsprogs/e2fs_lib.o
	modified:   tools/busybox-1.30.1/e2fsprogs/fsck.c
	modified:   tools/busybox-1.30.1/e2fsprogs/fsck.o
	modified:   tools/busybox-1.30.1/e2fsprogs/lib.a
	modified:   tools/busybox-1.30.1/e2fsprogs/lsattr.c
	modified:   tools/busybox-1.30.1/e2fsprogs/lsattr.o
	modified:   tools/busybox-1.30.1/e2fsprogs/tune2fs.c
	modified:   tools/busybox-1.30.1/editors/.awk.o.cmd
	modified:   tools/busybox-1.30.1/editors/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/editors/.cmp.o.cmd
	modified:   tools/busybox-1.30.1/editors/.diff.o.cmd
	modified:   tools/busybox-1.30.1/editors/.ed.o.cmd
	modified:   tools/busybox-1.30.1/editors/.lib.a.cmd
	modified:   tools/busybox-1.30.1/editors/.patch.o.cmd
	modified:   tools/busybox-1.30.1/editors/.sed.o.cmd
	modified:   tools/busybox-1.30.1/editors/.vi.o.cmd
	modified:   tools/busybox-1.30.1/editors/Config.in
	modified:   tools/busybox-1.30.1/editors/Config.src
	modified:   tools/busybox-1.30.1/editors/Kbuild
	modified:   tools/busybox-1.30.1/editors/Kbuild.src
	modified:   tools/busybox-1.30.1/editors/awk.c
	modified:   tools/busybox-1.30.1/editors/awk.o
	modified:   tools/busybox-1.30.1/editors/built-in.o
	modified:   tools/busybox-1.30.1/editors/cmp.c
	modified:   tools/busybox-1.30.1/editors/cmp.o
	modified:   tools/busybox-1.30.1/editors/diff.c
	modified:   tools/busybox-1.30.1/editors/diff.o
	modified:   tools/busybox-1.30.1/editors/ed.c
	modified:   tools/busybox-1.30.1/editors/ed.o
	modified:   tools/busybox-1.30.1/editors/lib.a
	modified:   tools/busybox-1.30.1/editors/patch.c
	modified:   tools/busybox-1.30.1/editors/patch.o
	modified:   tools/busybox-1.30.1/editors/patch_bbox.c
	modified:   tools/busybox-1.30.1/editors/patch_toybox.c
	modified:   tools/busybox-1.30.1/editors/sed.c
	modified:   tools/busybox-1.30.1/editors/sed.o
	modified:   tools/busybox-1.30.1/editors/sed_summary.htm
	modified:   tools/busybox-1.30.1/editors/vi.c
	modified:   tools/busybox-1.30.1/editors/vi.o
	modified:   tools/busybox-1.30.1/examples/bootfloppy/etc/fstab
	modified:   tools/busybox-1.30.1/examples/bootfloppy/etc/inittab
	modified:   tools/busybox-1.30.1/examples/bootfloppy/etc/profile
	modified:   tools/busybox-1.30.1/examples/bootfloppy/syslinux.cfg
	modified:   tools/busybox-1.30.1/examples/busybox.spec
	modified:   tools/busybox-1.30.1/examples/devfsd.conf
	modified:   tools/busybox-1.30.1/examples/dnsd.conf
	modified:   tools/busybox-1.30.1/examples/inetd.conf
	modified:   tools/busybox-1.30.1/examples/inittab
	modified:   tools/busybox-1.30.1/examples/linux-2.6.30_proc_self_exe.patch
	modified:   tools/busybox-1.30.1/examples/mdev.conf
	modified:   tools/busybox-1.30.1/examples/mdev_fat.conf
	modified:   tools/busybox-1.30.1/examples/shutdown-1.0/README
	modified:   tools/busybox-1.30.1/examples/shutdown-1.0/script/hardshutdown.c
	modified:   tools/busybox-1.30.1/examples/udhcp/udhcpd.conf
	modified:   tools/busybox-1.30.1/examples/var_service/README
	modified:   tools/busybox-1.30.1/examples/var_service/dhcpd_if/udhcpd.conf
	modified:   tools/busybox-1.30.1/examples/var_service/dnsmasq/README
	modified:   tools/busybox-1.30.1/examples/var_service/dnsmasq/dnsmasq.conf
	modified:   tools/busybox-1.30.1/examples/var_service/fw/conf/11.22.33.44.ipconf--
	modified:   tools/busybox-1.30.1/examples/var_service/fw/conf/192.168.0.1.ipconf
	modified:   tools/busybox-1.30.1/examples/var_service/fw/conf/lo.ipconf
	modified:   tools/busybox-1.30.1/examples/var_service/fw/etc/dnsmasq_servers.conf
	modified:   tools/busybox-1.30.1/examples/var_service/fw/etc/hosts
	modified:   tools/busybox-1.30.1/examples/var_service/fw/etc/resolv.conf
	modified:   tools/busybox-1.30.1/examples/var_service/getty_tty1/alt08x16+unimap.fnt
	modified:   tools/busybox-1.30.1/examples/var_service/getty_tty1/koi8r_to_uni.trans
	modified:   tools/busybox-1.30.1/examples/var_service/getty_tty1/unicode_cyrillic.keymap
	modified:   tools/busybox-1.30.1/examples/var_service/inetd/inetd.conf
	modified:   tools/busybox-1.30.1/examples/var_service/supplicant_if/wpa_supplicant.conf
	modified:   tools/busybox-1.30.1/findutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/findutils/.find.o.cmd
	modified:   tools/busybox-1.30.1/findutils/.grep.o.cmd
	modified:   tools/busybox-1.30.1/findutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/findutils/.xargs.o.cmd
	modified:   tools/busybox-1.30.1/findutils/Config.in
	modified:   tools/busybox-1.30.1/findutils/Config.src
	modified:   tools/busybox-1.30.1/findutils/Kbuild
	modified:   tools/busybox-1.30.1/findutils/Kbuild.src
	modified:   tools/busybox-1.30.1/findutils/built-in.o
	modified:   tools/busybox-1.30.1/findutils/find.c
	modified:   tools/busybox-1.30.1/findutils/find.o
	modified:   tools/busybox-1.30.1/findutils/grep.c
	modified:   tools/busybox-1.30.1/findutils/grep.o
	modified:   tools/busybox-1.30.1/findutils/lib.a
	modified:   tools/busybox-1.30.1/findutils/xargs.c
	modified:   tools/busybox-1.30.1/findutils/xargs.o
	modified:   tools/busybox-1.30.1/include/NUM_APPLETS.h
	modified:   tools/busybox-1.30.1/include/applet_metadata.h
	modified:   tools/busybox-1.30.1/include/applet_tables.h
	modified:   tools/busybox-1.30.1/include/applets.h
	modified:   tools/busybox-1.30.1/include/applets.src.h
	modified:   tools/busybox-1.30.1/include/ar.h
	modified:   tools/busybox-1.30.1/include/autoconf.h
	modified:   tools/busybox-1.30.1/include/bb_archive.h
	modified:   tools/busybox-1.30.1/include/bb_e2fs_defs.h
	modified:   tools/busybox-1.30.1/include/bbconfigopts.h
	modified:   tools/busybox-1.30.1/include/bbconfigopts_bz2.h
	modified:   tools/busybox-1.30.1/include/busybox.h
	modified:   tools/busybox-1.30.1/include/common_bufsiz.h
	modified:   tools/busybox-1.30.1/include/common_bufsiz.h.method
	modified:   tools/busybox-1.30.1/include/config/MARKER
	modified:   tools/busybox-1.30.1/include/config/acpid.h
	modified:   tools/busybox-1.30.1/include/config/add/shell.h
	modified:   tools/busybox-1.30.1/include/config/addgroup.h
	modified:   tools/busybox-1.30.1/include/config/adduser.h
	modified:   tools/busybox-1.30.1/include/config/adjtimex.h
	modified:   tools/busybox-1.30.1/include/config/ar.h
	modified:   tools/busybox-1.30.1/include/config/arp.h
	modified:   tools/busybox-1.30.1/include/config/arping.h
	modified:   tools/busybox-1.30.1/include/config/ash.h
	modified:   tools/busybox-1.30.1/include/config/ash/alias.h
	modified:   tools/busybox-1.30.1/include/config/ash/bash/compat.h
	modified:   tools/busybox-1.30.1/include/config/ash/bash/not/found/hook.h
	modified:   tools/busybox-1.30.1/include/config/ash/bash/source/curdir.h
	modified:   tools/busybox-1.30.1/include/config/ash/cmdcmd.h
	modified:   tools/busybox-1.30.1/include/config/ash/echo.h
	modified:   tools/busybox-1.30.1/include/config/ash/expand/prmt.h
	modified:   tools/busybox-1.30.1/include/config/ash/getopts.h
	modified:   tools/busybox-1.30.1/include/config/ash/help.h
	modified:   tools/busybox-1.30.1/include/config/ash/idle/timeout.h
	modified:   tools/busybox-1.30.1/include/config/ash/internal/glob.h
	modified:   tools/busybox-1.30.1/include/config/ash/job/control.h
	modified:   tools/busybox-1.30.1/include/config/ash/mail.h
	modified:   tools/busybox-1.30.1/include/config/ash/optimize/for/size.h
	modified:   tools/busybox-1.30.1/include/config/ash/printf.h
	modified:   tools/busybox-1.30.1/include/config/ash/random/support.h
	modified:   tools/busybox-1.30.1/include/config/ash/test.h
	modified:   tools/busybox-1.30.1/include/config/awk.h
	modified:   tools/busybox-1.30.1/include/config/base64.h
	modified:   tools/busybox-1.30.1/include/config/basename.h
	modified:   tools/busybox-1.30.1/include/config/bash/is/ash.h
	modified:   tools/busybox-1.30.1/include/config/bash/is/hush.h
	modified:   tools/busybox-1.30.1/include/config/bash/is/none.h
	modified:   tools/busybox-1.30.1/include/config/bb/arch.h
	modified:   tools/busybox-1.30.1/include/config/bb/sysctl.h
	modified:   tools/busybox-1.30.1/include/config/bbconfig.h
	modified:   tools/busybox-1.30.1/include/config/bc.h
	modified:   tools/busybox-1.30.1/include/config/beep.h
	modified:   tools/busybox-1.30.1/include/config/blkdiscard.h
	modified:   tools/busybox-1.30.1/include/config/blkid.h
	modified:   tools/busybox-1.30.1/include/config/blockdev.h
	modified:   tools/busybox-1.30.1/include/config/bootchartd.h
	modified:   tools/busybox-1.30.1/include/config/brctl.h
	modified:   tools/busybox-1.30.1/include/config/build/libbusybox.h
	modified:   tools/busybox-1.30.1/include/config/bunzip2.h
	modified:   tools/busybox-1.30.1/include/config/busybox.h
	modified:   tools/busybox-1.30.1/include/config/busybox/exec/path.h
	modified:   tools/busybox-1.30.1/include/config/bzcat.h
	modified:   tools/busybox-1.30.1/include/config/bzip2.h
	modified:   tools/busybox-1.30.1/include/config/bzip2/small.h
	modified:   tools/busybox-1.30.1/include/config/cal.h
	modified:   tools/busybox-1.30.1/include/config/cat.h
	modified:   tools/busybox-1.30.1/include/config/chat.h
	modified:   tools/busybox-1.30.1/include/config/chattr.h
	modified:   tools/busybox-1.30.1/include/config/chcon.h
	modified:   tools/busybox-1.30.1/include/config/chgrp.h
	modified:   tools/busybox-1.30.1/include/config/chmod.h
	modified:   tools/busybox-1.30.1/include/config/chown.h
	modified:   tools/busybox-1.30.1/include/config/chpasswd.h
	modified:   tools/busybox-1.30.1/include/config/chpst.h
	modified:   tools/busybox-1.30.1/include/config/chroot.h
	modified:   tools/busybox-1.30.1/include/config/chrt.h
	modified:   tools/busybox-1.30.1/include/config/chvt.h
	modified:   tools/busybox-1.30.1/include/config/cksum.h
	modified:   tools/busybox-1.30.1/include/config/clear.h
	modified:   tools/busybox-1.30.1/include/config/cmp.h
	modified:   tools/busybox-1.30.1/include/config/comm.h
	modified:   tools/busybox-1.30.1/include/config/conspy.h
	modified:   tools/busybox-1.30.1/include/config/cp.h
	modified:   tools/busybox-1.30.1/include/config/cpio.h
	modified:   tools/busybox-1.30.1/include/config/crond.h
	modified:   tools/busybox-1.30.1/include/config/crontab.h
	modified:   tools/busybox-1.30.1/include/config/cross/compiler/prefix.h
	modified:   tools/busybox-1.30.1/include/config/cryptpw.h
	modified:   tools/busybox-1.30.1/include/config/cttyhack.h
	modified:   tools/busybox-1.30.1/include/config/cut.h
	modified:   tools/busybox-1.30.1/include/config/date.h
	modified:   tools/busybox-1.30.1/include/config/dc.h
	modified:   tools/busybox-1.30.1/include/config/dd.h
	modified:   tools/busybox-1.30.1/include/config/deallocvt.h
	modified:   tools/busybox-1.30.1/include/config/debug.h
	modified:   tools/busybox-1.30.1/include/config/debug/pessimize.h
	modified:   tools/busybox-1.30.1/include/config/debug/sanitize.h
	modified:   tools/busybox-1.30.1/include/config/default/depmod/file.h
	modified:   tools/busybox-1.30.1/include/config/default/modules/dir.h
	modified:   tools/busybox-1.30.1/include/config/default/setfont/dir.h
	modified:   tools/busybox-1.30.1/include/config/delgroup.h
	modified:   tools/busybox-1.30.1/include/config/deluser.h
	modified:   tools/busybox-1.30.1/include/config/depmod.h
	modified:   tools/busybox-1.30.1/include/config/desktop.h
	modified:   tools/busybox-1.30.1/include/config/devfsd.h
	modified:   tools/busybox-1.30.1/include/config/devfsd/fg/np.h
	modified:   tools/busybox-1.30.1/include/config/devfsd/modload.h
	modified:   tools/busybox-1.30.1/include/config/devfsd/verbose.h
	modified:   tools/busybox-1.30.1/include/config/devmem.h
	modified:   tools/busybox-1.30.1/include/config/df.h
	modified:   tools/busybox-1.30.1/include/config/dhcpd/leases/file.h
	modified:   tools/busybox-1.30.1/include/config/dhcprelay.h
	modified:   tools/busybox-1.30.1/include/config/diff.h
	modified:   tools/busybox-1.30.1/include/config/dirname.h
	modified:   tools/busybox-1.30.1/include/config/dmalloc.h
	modified:   tools/busybox-1.30.1/include/config/dmesg.h
	modified:   tools/busybox-1.30.1/include/config/dnsd.h
	modified:   tools/busybox-1.30.1/include/config/dnsdomainname.h
	modified:   tools/busybox-1.30.1/include/config/dos2unix.h
	modified:   tools/busybox-1.30.1/include/config/dpkg.h
	modified:   tools/busybox-1.30.1/include/config/dpkg/deb.h
	modified:   tools/busybox-1.30.1/include/config/du.h
	modified:   tools/busybox-1.30.1/include/config/dumpkmap.h
	modified:   tools/busybox-1.30.1/include/config/dumpleases.h
	modified:   tools/busybox-1.30.1/include/config/echo.h
	modified:   tools/busybox-1.30.1/include/config/ed.h
	modified:   tools/busybox-1.30.1/include/config/efence.h
	modified:   tools/busybox-1.30.1/include/config/egrep.h
	modified:   tools/busybox-1.30.1/include/config/eject.h
	modified:   tools/busybox-1.30.1/include/config/env.h
	modified:   tools/busybox-1.30.1/include/config/envdir.h
	modified:   tools/busybox-1.30.1/include/config/envuidgid.h
	modified:   tools/busybox-1.30.1/include/config/ether/wake.h
	modified:   tools/busybox-1.30.1/include/config/expand.h
	modified:   tools/busybox-1.30.1/include/config/expr.h
	modified:   tools/busybox-1.30.1/include/config/expr/math/support/64.h
	modified:   tools/busybox-1.30.1/include/config/extra/cflags.h
	modified:   tools/busybox-1.30.1/include/config/extra/compat.h
	modified:   tools/busybox-1.30.1/include/config/extra/ldflags.h
	modified:   tools/busybox-1.30.1/include/config/extra/ldlibs.h
	modified:   tools/busybox-1.30.1/include/config/factor.h
	modified:   tools/busybox-1.30.1/include/config/fakeidentd.h
	modified:   tools/busybox-1.30.1/include/config/fallocate.h
	modified:   tools/busybox-1.30.1/include/config/false.h
	modified:   tools/busybox-1.30.1/include/config/fatattr.h
	modified:   tools/busybox-1.30.1/include/config/fbset.h
	modified:   tools/busybox-1.30.1/include/config/fbsplash.h
	modified:   tools/busybox-1.30.1/include/config/fdflush.h
	modified:   tools/busybox-1.30.1/include/config/fdformat.h
	modified:   tools/busybox-1.30.1/include/config/fdisk.h
	modified:   tools/busybox-1.30.1/include/config/fdisk/support/large/disks.h
	modified:   tools/busybox-1.30.1/include/config/feature/2/4/modules.h
	modified:   tools/busybox-1.30.1/include/config/feature/acpid/compat.h
	modified:   tools/busybox-1.30.1/include/config/feature/adduser/to/group.h
	modified:   tools/busybox-1.30.1/include/config/feature/aix/label.h
	modified:   tools/busybox-1.30.1/include/config/feature/allow/exec.h
	modified:   tools/busybox-1.30.1/include/config/feature/ar/create.h
	modified:   tools/busybox-1.30.1/include/config/feature/ar/long/filenames.h
	modified:   tools/busybox-1.30.1/include/config/feature/awk/gnu/extensions.h
	modified:   tools/busybox-1.30.1/include/config/feature/awk/libm.h
	modified:   tools/busybox-1.30.1/include/config/feature/bc/interactive.h
	modified:   tools/busybox-1.30.1/include/config/feature/bc/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/beep/freq.h
	modified:   tools/busybox-1.30.1/include/config/feature/beep/length/ms.h
	modified:   tools/busybox-1.30.1/include/config/feature/blkid/type.h
	modified:   tools/busybox-1.30.1/include/config/feature/bootchartd/bloated/header.h
	modified:   tools/busybox-1.30.1/include/config/feature/bootchartd/config/file.h
	modified:   tools/busybox-1.30.1/include/config/feature/brctl/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/brctl/show.h
	modified:   tools/busybox-1.30.1/include/config/feature/buffers/go/in/bss.h
	modified:   tools/busybox-1.30.1/include/config/feature/buffers/go/on/stack.h
	modified:   tools/busybox-1.30.1/include/config/feature/buffers/use/malloc.h
	modified:   tools/busybox-1.30.1/include/config/feature/bzip2/decompress.h
	modified:   tools/busybox-1.30.1/include/config/feature/call/telinit.h
	modified:   tools/busybox-1.30.1/include/config/feature/catn.h
	modified:   tools/busybox-1.30.1/include/config/feature/catv.h
	modified:   tools/busybox-1.30.1/include/config/feature/chat/clr/abort.h
	modified:   tools/busybox-1.30.1/include/config/feature/chat/implicit/cr.h
	modified:   tools/busybox-1.30.1/include/config/feature/chat/nofail.h
	modified:   tools/busybox-1.30.1/include/config/feature/chat/send/escapes.h
	modified:   tools/busybox-1.30.1/include/config/feature/chat/swallow/opts.h
	modified:   tools/busybox-1.30.1/include/config/feature/chat/tty/hifi.h
	modified:   tools/busybox-1.30.1/include/config/feature/chat/var/abort/len.h
	modified:   tools/busybox-1.30.1/include/config/feature/check/names.h
	modified:   tools/busybox-1.30.1/include/config/feature/check/tainted/module.h
	modified:   tools/busybox-1.30.1/include/config/feature/check/unicode/in/env.h
	modified:   tools/busybox-1.30.1/include/config/feature/chown/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/clean/up.h
	modified:   tools/busybox-1.30.1/include/config/feature/cmdline/module/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/compress/bbconfig.h
	modified:   tools/busybox-1.30.1/include/config/feature/compress/usage.h
	modified:   tools/busybox-1.30.1/include/config/feature/copybuf/kb.h
	modified:   tools/busybox-1.30.1/include/config/feature/cp/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/cp/reflink.h
	modified:   tools/busybox-1.30.1/include/config/feature/cpio/o.h
	modified:   tools/busybox-1.30.1/include/config/feature/cpio/p.h
	modified:   tools/busybox-1.30.1/include/config/feature/crond/call/sendmail.h
	modified:   tools/busybox-1.30.1/include/config/feature/crond/d.h
	modified:   tools/busybox-1.30.1/include/config/feature/crond/dir.h
	modified:   tools/busybox-1.30.1/include/config/feature/crond/special/times.h
	modified:   tools/busybox-1.30.1/include/config/feature/date/compat.h
	modified:   tools/busybox-1.30.1/include/config/feature/date/isofmt.h
	modified:   tools/busybox-1.30.1/include/config/feature/date/nano.h
	modified:   tools/busybox-1.30.1/include/config/feature/dc/big.h
	modified:   tools/busybox-1.30.1/include/config/feature/dc/libm.h
	modified:   tools/busybox-1.30.1/include/config/feature/dd/ibs/obs.h
	modified:   tools/busybox-1.30.1/include/config/feature/dd/signal/handling.h
	modified:   tools/busybox-1.30.1/include/config/feature/dd/status.h
	modified:   tools/busybox-1.30.1/include/config/feature/dd/third/status/line.h
	modified:   tools/busybox-1.30.1/include/config/feature/default/passwd/algo.h
	modified:   tools/busybox-1.30.1/include/config/feature/del/user/from/group.h
	modified:   tools/busybox-1.30.1/include/config/feature/devfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/devpts.h
	modified:   tools/busybox-1.30.1/include/config/feature/df/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/diff/dir.h
	modified:   tools/busybox-1.30.1/include/config/feature/diff/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/dmesg/pretty.h
	modified:   tools/busybox-1.30.1/include/config/feature/du/default/blocksize/1k.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/ask/terminal.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/fancy/prompt.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/history.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/max/len.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/save/on/exit.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/savehistory.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/vi.h
	modified:   tools/busybox-1.30.1/include/config/feature/editing/winch.h
	modified:   tools/busybox-1.30.1/include/config/feature/eject/scsi.h
	modified:   tools/busybox-1.30.1/include/config/feature/etc/networks.h
	modified:   tools/busybox-1.30.1/include/config/feature/etc/services.h
	modified:   tools/busybox-1.30.1/include/config/feature/fancy/echo.h
	modified:   tools/busybox-1.30.1/include/config/feature/fancy/head.h
	modified:   tools/busybox-1.30.1/include/config/feature/fancy/ping.h
	modified:   tools/busybox-1.30.1/include/config/feature/fancy/sleep.h
	modified:   tools/busybox-1.30.1/include/config/feature/fancy/tail.h
	modified:   tools/busybox-1.30.1/include/config/feature/fast/top.h
	modified:   tools/busybox-1.30.1/include/config/feature/fbset/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/fbset/readmode.h
	modified:   tools/busybox-1.30.1/include/config/feature/fdisk/advanced.h
	modified:   tools/busybox-1.30.1/include/config/feature/fdisk/writable.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/context.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/delete.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/depth.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/exec.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/exec/plus.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/executable.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/group.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/inum.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/links.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/maxdepth.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/mmin.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/mtime.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/newer.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/not.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/paren.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/path.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/perm.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/print0.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/prune.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/quit.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/regex.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/size.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/type.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/user.h
	modified:   tools/busybox-1.30.1/include/config/feature/find/xdev.h
	modified:   tools/busybox-1.30.1/include/config/feature/ftpd/accept/broken/list.h
	modified:   tools/busybox-1.30.1/include/config/feature/ftpd/authentication.h
	modified:   tools/busybox-1.30.1/include/config/feature/ftpd/write.h
	modified:   tools/busybox-1.30.1/include/config/feature/ftpgetput/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/getopt/long.h
	modified:   tools/busybox-1.30.1/include/config/feature/gpt/label.h
	modified:   tools/busybox-1.30.1/include/config/feature/grep/context.h
	modified:   tools/busybox-1.30.1/include/config/feature/gunzip/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/gzip/decompress.h
	modified:   tools/busybox-1.30.1/include/config/feature/gzip/levels.h
	modified:   tools/busybox-1.30.1/include/config/feature/gzip/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/hdparm/get/identity.h
	modified:   tools/busybox-1.30.1/include/config/feature/hdparm/hdio/drive/reset.h
	modified:   tools/busybox-1.30.1/include/config/feature/hdparm/hdio/getset/dma.h
	modified:   tools/busybox-1.30.1/include/config/feature/hdparm/hdio/scan/hwif.h
	modified:   tools/busybox-1.30.1/include/config/feature/hdparm/hdio/tristate/hwif.h
	modified:   tools/busybox-1.30.1/include/config/feature/hdparm/hdio/unregister/hwif.h
	modified:   tools/busybox-1.30.1/include/config/feature/hexdump/reverse.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/auth/md5.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/basic/auth.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/cgi.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/config/with/script/interpr.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/encode/url/str.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/error/pages.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/gzip.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/proxy.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/ranges.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/set/remote/port/to/env.h
	modified:   tools/busybox-1.30.1/include/config/feature/httpd/setuid.h
	modified:   tools/busybox-1.30.1/include/config/feature/human/readable.h
	modified:   tools/busybox-1.30.1/include/config/feature/hwclock/adjtime/fhs.h
	modified:   tools/busybox-1.30.1/include/config/feature/hwib.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifconfig/broadcast/plus.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifconfig/hw.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifconfig/memstart/ioaddr/irq.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifconfig/slip.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifconfig/status.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifupdown/external/dhcp.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifupdown/ip.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifupdown/ipv4.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifupdown/ipv6.h
	modified:   tools/busybox-1.30.1/include/config/feature/ifupdown/mapping.h
	modified:   tools/busybox-1.30.1/include/config/feature/individual.h
	modified:   tools/busybox-1.30.1/include/config/feature/inetd/rpc.h
	modified:   tools/busybox-1.30.1/include/config/feature/inetd/support/builtin/chargen.h
	modified:   tools/busybox-1.30.1/include/config/feature/inetd/support/builtin/daytime.h
	modified:   tools/busybox-1.30.1/include/config/feature/inetd/support/builtin/discard.h
	modified:   tools/busybox-1.30.1/include/config/feature/inetd/support/builtin/echo.h
	modified:   tools/busybox-1.30.1/include/config/feature/inetd/support/builtin/time.h
	modified:   tools/busybox-1.30.1/include/config/feature/init/coredumps.h
	modified:   tools/busybox-1.30.1/include/config/feature/init/modify/cmdline.h
	modified:   tools/busybox-1.30.1/include/config/feature/init/quiet.h
	modified:   tools/busybox-1.30.1/include/config/feature/init/sctty.h
	modified:   tools/busybox-1.30.1/include/config/feature/init/syslog.h
	modified:   tools/busybox-1.30.1/include/config/feature/insmod/ksymoops/symbols.h
	modified:   tools/busybox-1.30.1/include/config/feature/insmod/load/map.h
	modified:   tools/busybox-1.30.1/include/config/feature/insmod/load/map/full.h
	modified:   tools/busybox-1.30.1/include/config/feature/insmod/loadinkmem.h
	modified:   tools/busybox-1.30.1/include/config/feature/insmod/try/mmap.h
	modified:   tools/busybox-1.30.1/include/config/feature/insmod/version/checking.h
	modified:   tools/busybox-1.30.1/include/config/feature/install/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/installer.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/address.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/link.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/neigh.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/rare/protocols.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/route.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/route/dir.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/rule.h
	modified:   tools/busybox-1.30.1/include/config/feature/ip/tunnel.h
	modified:   tools/busybox-1.30.1/include/config/feature/ipc/syslog.h
	modified:   tools/busybox-1.30.1/include/config/feature/ipc/syslog/buffer/size.h
	modified:   tools/busybox-1.30.1/include/config/feature/ipcalc/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/ipcalc/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/ipv6.h
	modified:   tools/busybox-1.30.1/include/config/feature/kill/delay.h
	modified:   tools/busybox-1.30.1/include/config/feature/kill/removed.h
	modified:   tools/busybox-1.30.1/include/config/feature/klogd/klogctl.h
	modified:   tools/busybox-1.30.1/include/config/feature/kmsg/syslog.h
	modified:   tools/busybox-1.30.1/include/config/feature/last/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/ask/terminal.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/brackets.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/dashcmd.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/env.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/flags.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/linenums.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/marks.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/maxlines.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/raw.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/regexp.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/truncate.h
	modified:   tools/busybox-1.30.1/include/config/feature/less/winch.h
	modified:   tools/busybox-1.30.1/include/config/feature/libbusybox/static.h
	modified:   tools/busybox-1.30.1/include/config/feature/loadfont/psf2.h
	modified:   tools/busybox-1.30.1/include/config/feature/loadfont/raw.h
	modified:   tools/busybox-1.30.1/include/config/feature/logread/reduced/locking.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/color.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/color/is/default.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/filetypes.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/followlinks.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/recursive.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/sortfiles.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/timestamps.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/username.h
	modified:   tools/busybox-1.30.1/include/config/feature/ls/width.h
	modified:   tools/busybox-1.30.1/include/config/feature/lsmod/pretty/2/6/output.h
	modified:   tools/busybox-1.30.1/include/config/feature/lzma/fast.h
	modified:   tools/busybox-1.30.1/include/config/feature/makedevs/leaf.h
	modified:   tools/busybox-1.30.1/include/config/feature/makedevs/table.h
	modified:   tools/busybox-1.30.1/include/config/feature/md5/sha1/sum/check.h
	modified:   tools/busybox-1.30.1/include/config/feature/mdev/conf.h
	modified:   tools/busybox-1.30.1/include/config/feature/mdev/exec.h
	modified:   tools/busybox-1.30.1/include/config/feature/mdev/load/firmware.h
	modified:   tools/busybox-1.30.1/include/config/feature/mdev/rename.h
	modified:   tools/busybox-1.30.1/include/config/feature/mdev/rename/regexp.h
	modified:   tools/busybox-1.30.1/include/config/feature/mesg/enable/only/group.h
	modified:   tools/busybox-1.30.1/include/config/feature/mime/charset.h
	modified:   tools/busybox-1.30.1/include/config/feature/minix2.h
	modified:   tools/busybox-1.30.1/include/config/feature/mkswap/uuid.h
	modified:   tools/busybox-1.30.1/include/config/feature/modprobe/blacklist.h
	modified:   tools/busybox-1.30.1/include/config/feature/modprobe/small/check/already/loaded.h
	modified:   tools/busybox-1.30.1/include/config/feature/modutils/alias.h
	modified:   tools/busybox-1.30.1/include/config/feature/modutils/symbols.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/cifs.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/fake.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/flags.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/fstab.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/helpers.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/label.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/loop.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/loop/create.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/nfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/othertab.h
	modified:   tools/busybox-1.30.1/include/config/feature/mount/verbose.h
	modified:   tools/busybox-1.30.1/include/config/feature/mtab/support.h
	modified:   tools/busybox-1.30.1/include/config/feature/nameif/extended.h
	modified:   tools/busybox-1.30.1/include/config/feature/netstat/prg.h
	modified:   tools/busybox-1.30.1/include/config/feature/netstat/wide.h
	modified:   tools/busybox-1.30.1/include/config/feature/nologin.h
	modified:   tools/busybox-1.30.1/include/config/feature/non/posix/cp.h
	modified:   tools/busybox-1.30.1/include/config/feature/nslookup/big.h
	modified:   tools/busybox-1.30.1/include/config/feature/nslookup/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/ntp/auth.h
	modified:   tools/busybox-1.30.1/include/config/feature/ntpd/conf.h
	modified:   tools/busybox-1.30.1/include/config/feature/ntpd/server.h
	modified:   tools/busybox-1.30.1/include/config/feature/osf/label.h
	modified:   tools/busybox-1.30.1/include/config/feature/passwd/weak/check.h
	modified:   tools/busybox-1.30.1/include/config/feature/pidfile.h
	modified:   tools/busybox-1.30.1/include/config/feature/pidof/omit.h
	modified:   tools/busybox-1.30.1/include/config/feature/pidof/single.h
	modified:   tools/busybox-1.30.1/include/config/feature/popmaildir/delivery.h
	modified:   tools/busybox-1.30.1/include/config/feature/powertop/interactive.h
	modified:   tools/busybox-1.30.1/include/config/feature/prefer/applets.h
	modified:   tools/busybox-1.30.1/include/config/feature/prefer/ipv4/address.h
	modified:   tools/busybox-1.30.1/include/config/feature/preserve/hardlinks.h
	modified:   tools/busybox-1.30.1/include/config/feature/ps/additional/columns.h
	modified:   tools/busybox-1.30.1/include/config/feature/ps/long.h
	modified:   tools/busybox-1.30.1/include/config/feature/ps/time.h
	modified:   tools/busybox-1.30.1/include/config/feature/ps/unusual/systems.h
	modified:   tools/busybox-1.30.1/include/config/feature/ps/wide.h
	modified:   tools/busybox-1.30.1/include/config/feature/readlink/follow.h
	modified:   tools/busybox-1.30.1/include/config/feature/reformime/compat.h
	modified:   tools/busybox-1.30.1/include/config/feature/remote/log.h
	modified:   tools/busybox-1.30.1/include/config/feature/resize/print.h
	modified:   tools/busybox-1.30.1/include/config/feature/reverse/search.h
	modified:   tools/busybox-1.30.1/include/config/feature/rotate/logfile.h
	modified:   tools/busybox-1.30.1/include/config/feature/rtminmax.h
	modified:   tools/busybox-1.30.1/include/config/feature/rtminmax/use/libc/definitions.h
	modified:   tools/busybox-1.30.1/include/config/feature/run/parts/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/run/parts/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/runsvdir/log.h
	modified:   tools/busybox-1.30.1/include/config/feature/seamless/bz2.h
	modified:   tools/busybox-1.30.1/include/config/feature/seamless/gz.h
	modified:   tools/busybox-1.30.1/include/config/feature/seamless/lzma.h
	modified:   tools/busybox-1.30.1/include/config/feature/seamless/xz.h
	modified:   tools/busybox-1.30.1/include/config/feature/seamless/z.h
	modified:   tools/busybox-1.30.1/include/config/feature/securetty.h
	modified:   tools/busybox-1.30.1/include/config/feature/setconsole/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/setfiles/check/option.h
	modified:   tools/busybox-1.30.1/include/config/feature/setfont/textual/map.h
	modified:   tools/busybox-1.30.1/include/config/feature/setpriv/capabilities.h
	modified:   tools/busybox-1.30.1/include/config/feature/setpriv/capability/names.h
	modified:   tools/busybox-1.30.1/include/config/feature/setpriv/dump.h
	modified:   tools/busybox-1.30.1/include/config/feature/sgi/label.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/embedded/scripts.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/extra/quiet.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/histfilesize.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/math.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/math/64.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/nofork.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/read/frac.h
	modified:   tools/busybox-1.30.1/include/config/feature/sh/standalone.h
	modified:   tools/busybox-1.30.1/include/config/feature/shadowpasswds.h
	modified:   tools/busybox-1.30.1/include/config/feature/shared/busybox.h
	modified:   tools/busybox-1.30.1/include/config/feature/show/script.h
	modified:   tools/busybox-1.30.1/include/config/feature/show/threads.h
	modified:   tools/busybox-1.30.1/include/config/feature/skip/rootfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/sort/big.h
	modified:   tools/busybox-1.30.1/include/config/feature/sort/optimize/memory.h
	modified:   tools/busybox-1.30.1/include/config/feature/split/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/start/stop/daemon/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/start/stop/daemon/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/stat/filesystem.h
	modified:   tools/busybox-1.30.1/include/config/feature/stat/format.h
	modified:   tools/busybox-1.30.1/include/config/feature/su/blank/pw/needs/secure/tty.h
	modified:   tools/busybox-1.30.1/include/config/feature/su/checks/shells.h
	modified:   tools/busybox-1.30.1/include/config/feature/su/syslog.h
	modified:   tools/busybox-1.30.1/include/config/feature/suid.h
	modified:   tools/busybox-1.30.1/include/config/feature/suid/config.h
	modified:   tools/busybox-1.30.1/include/config/feature/suid/config/quiet.h
	modified:   tools/busybox-1.30.1/include/config/feature/sun/label.h
	modified:   tools/busybox-1.30.1/include/config/feature/swapon/discard.h
	modified:   tools/busybox-1.30.1/include/config/feature/swapon/pri.h
	modified:   tools/busybox-1.30.1/include/config/feature/swaponoff/label.h
	modified:   tools/busybox-1.30.1/include/config/feature/sync/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/syslog.h
	modified:   tools/busybox-1.30.1/include/config/feature/syslogd/cfg.h
	modified:   tools/busybox-1.30.1/include/config/feature/syslogd/dup.h
	modified:   tools/busybox-1.30.1/include/config/feature/syslogd/read/buffer/size.h
	modified:   tools/busybox-1.30.1/include/config/feature/tab/completion.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/autodetect.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/create.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/from.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/gnu/extensions.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/nopreserve/time.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/oldgnu/compatibility.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/oldsun/compatibility.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/selinux.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/to/command.h
	modified:   tools/busybox-1.30.1/include/config/feature/tar/uname/gname.h
	modified:   tools/busybox-1.30.1/include/config/feature/taskset/fancy.h
	modified:   tools/busybox-1.30.1/include/config/feature/tc/ingress.h
	modified:   tools/busybox-1.30.1/include/config/feature/tee/use/block/io.h
	modified:   tools/busybox-1.30.1/include/config/feature/telnet/autologin.h
	modified:   tools/busybox-1.30.1/include/config/feature/telnet/ttype.h
	modified:   tools/busybox-1.30.1/include/config/feature/telnet/width.h
	modified:   tools/busybox-1.30.1/include/config/feature/telnetd/inetd/wait.h
	modified:   tools/busybox-1.30.1/include/config/feature/telnetd/standalone.h
	modified:   tools/busybox-1.30.1/include/config/feature/test/64.h
	modified:   tools/busybox-1.30.1/include/config/feature/tftp/blocksize.h
	modified:   tools/busybox-1.30.1/include/config/feature/tftp/get.h
	modified:   tools/busybox-1.30.1/include/config/feature/tftp/progress/bar.h
	modified:   tools/busybox-1.30.1/include/config/feature/tftp/put.h
	modified:   tools/busybox-1.30.1/include/config/feature/tls/sha1.h
	modified:   tools/busybox-1.30.1/include/config/feature/top/cpu/global/percents.h
	modified:   tools/busybox-1.30.1/include/config/feature/top/cpu/usage/percentage.h
	modified:   tools/busybox-1.30.1/include/config/feature/top/decimals.h
	modified:   tools/busybox-1.30.1/include/config/feature/top/interactive.h
	modified:   tools/busybox-1.30.1/include/config/feature/top/smp/cpu.h
	modified:   tools/busybox-1.30.1/include/config/feature/top/smp/process.h
	modified:   tools/busybox-1.30.1/include/config/feature/topmem.h
	modified:   tools/busybox-1.30.1/include/config/feature/touch/noderef.h
	modified:   tools/busybox-1.30.1/include/config/feature/touch/susv3.h
	modified:   tools/busybox-1.30.1/include/config/feature/tr/classes.h
	modified:   tools/busybox-1.30.1/include/config/feature/tr/equiv.h
	modified:   tools/busybox-1.30.1/include/config/feature/traceroute/use/icmp.h
	modified:   tools/busybox-1.30.1/include/config/feature/traceroute/verbose.h
	modified:   tools/busybox-1.30.1/include/config/feature/tunctl/ug.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcp/8021q.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcp/port.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcp/rfc3397.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpc/arping.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpc/sanitizeopt.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpc6/rfc3646.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpc6/rfc4704.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpc6/rfc4833.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpc6/rfc5970.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpd/base/ip/on/mac.h
	modified:   tools/busybox-1.30.1/include/config/feature/udhcpd/write/leases/early.h
	modified:   tools/busybox-1.30.1/include/config/feature/umount/all.h
	modified:   tools/busybox-1.30.1/include/config/feature/unix/local.h
	modified:   tools/busybox-1.30.1/include/config/feature/unzip/bzip2.h
	modified:   tools/busybox-1.30.1/include/config/feature/unzip/cdf.h
	modified:   tools/busybox-1.30.1/include/config/feature/unzip/lzma.h
	modified:   tools/busybox-1.30.1/include/config/feature/unzip/xz.h
	modified:   tools/busybox-1.30.1/include/config/feature/uptime/utmp/support.h
	modified:   tools/busybox-1.30.1/include/config/feature/use/bss/tail.h
	modified:   tools/busybox-1.30.1/include/config/feature/use/inittab.h
	modified:   tools/busybox-1.30.1/include/config/feature/use/sendfile.h
	modified:   tools/busybox-1.30.1/include/config/feature/username/completion.h
	modified:   tools/busybox-1.30.1/include/config/feature/utmp.h
	modified:   tools/busybox-1.30.1/include/config/feature/verbose.h
	modified:   tools/busybox-1.30.1/include/config/feature/verbose/cp/message.h
	modified:   tools/busybox-1.30.1/include/config/feature/verbose/usage.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/8bit.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/ask/terminal.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/colon.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/dot/cmd.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/max/len.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/readonly.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/regex/search.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/search.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/set.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/setopts.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/undo.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/undo/queue.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/undo/queue/max.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/use/signals.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/win/resize.h
	modified:   tools/busybox-1.30.1/include/config/feature/vi/yankmark.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/bcache.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/btrfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/cramfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/exfat.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/ext.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/f2fs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/fat.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/hfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/iso9660.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/jfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/lfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/linuxraid.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/linuxswap.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/luks.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/minix.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/nilfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/ntfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/ocfs2.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/reiserfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/romfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/squashfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/sysv.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/ubifs.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/udf.h
	modified:   tools/busybox-1.30.1/include/config/feature/volumeid/xfs.h
	modified:   tools/busybox-1.30.1/include/config/feature/wait/for/init.h
	modified:   tools/busybox-1.30.1/include/config/feature/wc/large.h
	modified:   tools/busybox-1.30.1/include/config/feature/wget/authentication.h
	modified:   tools/busybox-1.30.1/include/config/feature/wget/https.h
	modified:   tools/busybox-1.30.1/include/config/feature/wget/long/options.h
	modified:   tools/busybox-1.30.1/include/config/feature/wget/openssl.h
	modified:   tools/busybox-1.30.1/include/config/feature/wget/statusbar.h
	modified:   tools/busybox-1.30.1/include/config/feature/wget/timeout.h
	modified:   tools/busybox-1.30.1/include/config/feature/wtmp.h
	modified:   tools/busybox-1.30.1/include/config/feature/xargs/support/args/file.h
	modified:   tools/busybox-1.30.1/include/config/feature/xargs/support/confirmation.h
	modified:   tools/busybox-1.30.1/include/config/feature/xargs/support/parallel.h
	modified:   tools/busybox-1.30.1/include/config/feature/xargs/support/quotes.h
	modified:   tools/busybox-1.30.1/include/config/feature/xargs/support/repl/str.h
	modified:   tools/busybox-1.30.1/include/config/feature/xargs/support/termopt.h
	modified:   tools/busybox-1.30.1/include/config/feature/xargs/support/zero/term.h
	modified:   tools/busybox-1.30.1/include/config/fedora/compat.h
	modified:   tools/busybox-1.30.1/include/config/fgconsole.h
	modified:   tools/busybox-1.30.1/include/config/fgrep.h
	modified:   tools/busybox-1.30.1/include/config/find.h
	modified:   tools/busybox-1.30.1/include/config/findfs.h
	modified:   tools/busybox-1.30.1/include/config/first/system/id.h
	modified:   tools/busybox-1.30.1/include/config/flash/eraseall.h
	modified:   tools/busybox-1.30.1/include/config/flash/lock.h
	modified:   tools/busybox-1.30.1/include/config/flash/unlock.h
	modified:   tools/busybox-1.30.1/include/config/flashcp.h
	modified:   tools/busybox-1.30.1/include/config/float/duration.h
	modified:   tools/busybox-1.30.1/include/config/flock.h
	modified:   tools/busybox-1.30.1/include/config/fold.h
	modified:   tools/busybox-1.30.1/include/config/free.h
	modified:   tools/busybox-1.30.1/include/config/freeramdisk.h
	modified:   tools/busybox-1.30.1/include/config/fsck.h
	modified:   tools/busybox-1.30.1/include/config/fsck/minix.h
	modified:   tools/busybox-1.30.1/include/config/fsfreeze.h
	modified:   tools/busybox-1.30.1/include/config/fstrim.h
	modified:   tools/busybox-1.30.1/include/config/fsync.h
	modified:   tools/busybox-1.30.1/include/config/ftpd.h
	modified:   tools/busybox-1.30.1/include/config/ftpget.h
	modified:   tools/busybox-1.30.1/include/config/ftpput.h
	modified:   tools/busybox-1.30.1/include/config/fuser.h
	modified:   tools/busybox-1.30.1/include/config/getenforce.h
	modified:   tools/busybox-1.30.1/include/config/getopt.h
	modified:   tools/busybox-1.30.1/include/config/getsebool.h
	modified:   tools/busybox-1.30.1/include/config/getty.h
	modified:   tools/busybox-1.30.1/include/config/grep.h
	modified:   tools/busybox-1.30.1/include/config/groups.h
	modified:   tools/busybox-1.30.1/include/config/gunzip.h
	modified:   tools/busybox-1.30.1/include/config/gzip.h
	modified:   tools/busybox-1.30.1/include/config/gzip/fast.h
	modified:   tools/busybox-1.30.1/include/config/halt.h
	modified:   tools/busybox-1.30.1/include/config/have/dot/config.h
	modified:   tools/busybox-1.30.1/include/config/hd.h
	modified:   tools/busybox-1.30.1/include/config/hdparm.h
	modified:   tools/busybox-1.30.1/include/config/head.h
	modified:   tools/busybox-1.30.1/include/config/hexdump.h
	modified:   tools/busybox-1.30.1/include/config/hexedit.h
	modified:   tools/busybox-1.30.1/include/config/hostid.h
	modified:   tools/busybox-1.30.1/include/config/hostname.h
	modified:   tools/busybox-1.30.1/include/config/httpd.h
	modified:   tools/busybox-1.30.1/include/config/hush.h
	modified:   tools/busybox-1.30.1/include/config/hush/bash/compat.h
	modified:   tools/busybox-1.30.1/include/config/hush/bash/source/curdir.h
	modified:   tools/busybox-1.30.1/include/config/hush/brace/expansion.h
	modified:   tools/busybox-1.30.1/include/config/hush/case.h
	modified:   tools/busybox-1.30.1/include/config/hush/command.h
	modified:   tools/busybox-1.30.1/include/config/hush/echo.h
	modified:   tools/busybox-1.30.1/include/config/hush/export.h
	modified:   tools/busybox-1.30.1/include/config/hush/export/n.h
	modified:   tools/busybox-1.30.1/include/config/hush/functions.h
	modified:   tools/busybox-1.30.1/include/config/hush/getopts.h
	modified:   tools/busybox-1.30.1/include/config/hush/help.h
	modified:   tools/busybox-1.30.1/include/config/hush/if.h
	modified:   tools/busybox-1.30.1/include/config/hush/interactive.h
	modified:   tools/busybox-1.30.1/include/config/hush/job.h
	modified:   tools/busybox-1.30.1/include/config/hush/kill.h
	modified:   tools/busybox-1.30.1/include/config/hush/lineno/var.h
	modified:   tools/busybox-1.30.1/include/config/hush/local.h
	modified:   tools/busybox-1.30.1/include/config/hush/loops.h
	modified:   tools/busybox-1.30.1/include/config/hush/memleak.h
	modified:   tools/busybox-1.30.1/include/config/hush/mode/x.h
	modified:   tools/busybox-1.30.1/include/config/hush/printf.h
	modified:   tools/busybox-1.30.1/include/config/hush/random/support.h
	modified:   tools/busybox-1.30.1/include/config/hush/read.h
	modified:   tools/busybox-1.30.1/include/config/hush/readonly.h
	modified:   tools/busybox-1.30.1/include/config/hush/savehistory.h
	modified:   tools/busybox-1.30.1/include/config/hush/set.h
	modified:   tools/busybox-1.30.1/include/config/hush/test.h
	modified:   tools/busybox-1.30.1/include/config/hush/tick.h
	modified:   tools/busybox-1.30.1/include/config/hush/times.h
	modified:   tools/busybox-1.30.1/include/config/hush/trap.h
	modified:   tools/busybox-1.30.1/include/config/hush/type.h
	modified:   tools/busybox-1.30.1/include/config/hush/ulimit.h
	modified:   tools/busybox-1.30.1/include/config/hush/umask.h
	modified:   tools/busybox-1.30.1/include/config/hush/unset.h
	modified:   tools/busybox-1.30.1/include/config/hush/wait.h
	modified:   tools/busybox-1.30.1/include/config/hwclock.h
	modified:   tools/busybox-1.30.1/include/config/i2cdetect.h
	modified:   tools/busybox-1.30.1/include/config/i2cdump.h
	modified:   tools/busybox-1.30.1/include/config/i2cget.h
	modified:   tools/busybox-1.30.1/include/config/i2cset.h
	modified:   tools/busybox-1.30.1/include/config/id.h
	modified:   tools/busybox-1.30.1/include/config/ifconfig.h
	modified:   tools/busybox-1.30.1/include/config/ifdown.h
	modified:   tools/busybox-1.30.1/include/config/ifenslave.h
	modified:   tools/busybox-1.30.1/include/config/ifplugd.h
	modified:   tools/busybox-1.30.1/include/config/ifup.h
	modified:   tools/busybox-1.30.1/include/config/ifupdown/ifstate/path.h
	modified:   tools/busybox-1.30.1/include/config/ifupdown/udhcpc/cmd/options.h
	modified:   tools/busybox-1.30.1/include/config/include/susv2.h
	modified:   tools/busybox-1.30.1/include/config/inetd.h
	modified:   tools/busybox-1.30.1/include/config/init.h
	modified:   tools/busybox-1.30.1/include/config/init/terminal/type.h
	modified:   tools/busybox-1.30.1/include/config/inotifyd.h
	modified:   tools/busybox-1.30.1/include/config/insmod.h
	modified:   tools/busybox-1.30.1/include/config/install.h
	modified:   tools/busybox-1.30.1/include/config/install/applet/dont.h
	modified:   tools/busybox-1.30.1/include/config/install/applet/hardlinks.h
	modified:   tools/busybox-1.30.1/include/config/install/applet/script/wrappers.h
	modified:   tools/busybox-1.30.1/include/config/install/applet/symlinks.h
	modified:   tools/busybox-1.30.1/include/config/install/no/usr.h
	modified:   tools/busybox-1.30.1/include/config/install/sh/applet/hardlink.h
	modified:   tools/busybox-1.30.1/include/config/install/sh/applet/script/wrapper.h
	modified:   tools/busybox-1.30.1/include/config/install/sh/applet/symlink.h
	modified:   tools/busybox-1.30.1/include/config/ioctl/hex2str/error.h
	modified:   tools/busybox-1.30.1/include/config/ionice.h
	modified:   tools/busybox-1.30.1/include/config/iostat.h
	modified:   tools/busybox-1.30.1/include/config/ip.h
	modified:   tools/busybox-1.30.1/include/config/ipaddr.h
	modified:   tools/busybox-1.30.1/include/config/ipcalc.h
	modified:   tools/busybox-1.30.1/include/config/ipcrm.h
	modified:   tools/busybox-1.30.1/include/config/ipcs.h
	modified:   tools/busybox-1.30.1/include/config/iplink.h
	modified:   tools/busybox-1.30.1/include/config/ipneigh.h
	modified:   tools/busybox-1.30.1/include/config/iproute.h
	modified:   tools/busybox-1.30.1/include/config/iprule.h
	modified:   tools/busybox-1.30.1/include/config/iptunnel.h
	modified:   tools/busybox-1.30.1/include/config/kbd/mode.h
	modified:   tools/busybox-1.30.1/include/config/kill.h
	modified:   tools/busybox-1.30.1/include/config/killall.h
	modified:   tools/busybox-1.30.1/include/config/killall5.h
	modified:   tools/busybox-1.30.1/include/config/klogd.h
	modified:   tools/busybox-1.30.1/include/config/last.h
	modified:   tools/busybox-1.30.1/include/config/last/id.h
	modified:   tools/busybox-1.30.1/include/config/last/supported/wchar.h
	modified:   tools/busybox-1.30.1/include/config/last/system/id.h
	modified:   tools/busybox-1.30.1/include/config/less.h
	modified:   tools/busybox-1.30.1/include/config/lfs.h
	modified:   tools/busybox-1.30.1/include/config/link.h
	modified:   tools/busybox-1.30.1/include/config/linux32.h
	modified:   tools/busybox-1.30.1/include/config/linux64.h
	modified:   tools/busybox-1.30.1/include/config/linuxrc.h
	modified:   tools/busybox-1.30.1/include/config/ln.h
	modified:   tools/busybox-1.30.1/include/config/load/policy.h
	modified:   tools/busybox-1.30.1/include/config/loadfont.h
	modified:   tools/busybox-1.30.1/include/config/loadkmap.h
	modified:   tools/busybox-1.30.1/include/config/locale/support.h
	modified:   tools/busybox-1.30.1/include/config/logger.h
	modified:   tools/busybox-1.30.1/include/config/login.h
	modified:   tools/busybox-1.30.1/include/config/login/scripts.h
	modified:   tools/busybox-1.30.1/include/config/login/session/as/child.h
	modified:   tools/busybox-1.30.1/include/config/logname.h
	modified:   tools/busybox-1.30.1/include/config/logread.h
	modified:   tools/busybox-1.30.1/include/config/long/opts.h
	modified:   tools/busybox-1.30.1/include/config/losetup.h
	modified:   tools/busybox-1.30.1/include/config/lpd.h
	modified:   tools/busybox-1.30.1/include/config/lpq.h
	modified:   tools/busybox-1.30.1/include/config/lpr.h
	modified:   tools/busybox-1.30.1/include/config/ls.h
	modified:   tools/busybox-1.30.1/include/config/lsattr.h
	modified:   tools/busybox-1.30.1/include/config/lsmod.h
	modified:   tools/busybox-1.30.1/include/config/lsof.h
	modified:   tools/busybox-1.30.1/include/config/lspci.h
	modified:   tools/busybox-1.30.1/include/config/lsscsi.h
	modified:   tools/busybox-1.30.1/include/config/lsusb.h
	modified:   tools/busybox-1.30.1/include/config/lzcat.h
	modified:   tools/busybox-1.30.1/include/config/lzma.h
	modified:   tools/busybox-1.30.1/include/config/lzop.h
	modified:   tools/busybox-1.30.1/include/config/lzop/compr/high.h
	modified:   tools/busybox-1.30.1/include/config/lzopcat.h
	modified:   tools/busybox-1.30.1/include/config/makedevs.h
	modified:   tools/busybox-1.30.1/include/config/makemime.h
	modified:   tools/busybox-1.30.1/include/config/man.h
	modified:   tools/busybox-1.30.1/include/config/matchpathcon.h
	modified:   tools/busybox-1.30.1/include/config/md5/small.h
	modified:   tools/busybox-1.30.1/include/config/md5sum.h
	modified:   tools/busybox-1.30.1/include/config/mdev.h
	modified:   tools/busybox-1.30.1/include/config/mesg.h
	modified:   tools/busybox-1.30.1/include/config/microcom.h
	modified:   tools/busybox-1.30.1/include/config/minips.h
	modified:   tools/busybox-1.30.1/include/config/mkdir.h
	modified:   tools/busybox-1.30.1/include/config/mkdosfs.h
	modified:   tools/busybox-1.30.1/include/config/mke2fs.h
	modified:   tools/busybox-1.30.1/include/config/mkfifo.h
	modified:   tools/busybox-1.30.1/include/config/mkfs/ext2.h
	modified:   tools/busybox-1.30.1/include/config/mkfs/minix.h
	modified:   tools/busybox-1.30.1/include/config/mkfs/reiser.h
	modified:   tools/busybox-1.30.1/include/config/mkfs/vfat.h
	modified:   tools/busybox-1.30.1/include/config/mknod.h
	modified:   tools/busybox-1.30.1/include/config/mkpasswd.h
	modified:   tools/busybox-1.30.1/include/config/mkswap.h
	modified:   tools/busybox-1.30.1/include/config/mktemp.h
	modified:   tools/busybox-1.30.1/include/config/modinfo.h
	modified:   tools/busybox-1.30.1/include/config/modprobe.h
	modified:   tools/busybox-1.30.1/include/config/modprobe/small.h
	modified:   tools/busybox-1.30.1/include/config/monotonic/syscall.h
	modified:   tools/busybox-1.30.1/include/config/more.h
	modified:   tools/busybox-1.30.1/include/config/mount.h
	modified:   tools/busybox-1.30.1/include/config/mountpoint.h
	modified:   tools/busybox-1.30.1/include/config/mpstat.h
	modified:   tools/busybox-1.30.1/include/config/mt.h
	modified:   tools/busybox-1.30.1/include/config/mv.h
	modified:   tools/busybox-1.30.1/include/config/nameif.h
	modified:   tools/busybox-1.30.1/include/config/nanddump.h
	modified:   tools/busybox-1.30.1/include/config/nandwrite.h
	modified:   tools/busybox-1.30.1/include/config/nbdclient.h
	modified:   tools/busybox-1.30.1/include/config/nc.h
	modified:   tools/busybox-1.30.1/include/config/nc/110/compat.h
	modified:   tools/busybox-1.30.1/include/config/nc/extra.h
	modified:   tools/busybox-1.30.1/include/config/nc/server.h
	modified:   tools/busybox-1.30.1/include/config/netcat.h
	modified:   tools/busybox-1.30.1/include/config/netstat.h
	modified:   tools/busybox-1.30.1/include/config/nice.h
	modified:   tools/busybox-1.30.1/include/config/nl.h
	modified:   tools/busybox-1.30.1/include/config/nmeter.h
	modified:   tools/busybox-1.30.1/include/config/no/debug/lib.h
	modified:   tools/busybox-1.30.1/include/config/nohup.h
	modified:   tools/busybox-1.30.1/include/config/nologin.h
	modified:   tools/busybox-1.30.1/include/config/nologin/dependencies.h
	modified:   tools/busybox-1.30.1/include/config/nommu.h
	modified:   tools/busybox-1.30.1/include/config/nproc.h
	modified:   tools/busybox-1.30.1/include/config/nsenter.h
	modified:   tools/busybox-1.30.1/include/config/nslookup.h
	modified:   tools/busybox-1.30.1/include/config/ntpd.h
	modified:   tools/busybox-1.30.1/include/config/nuke.h
	modified:   tools/busybox-1.30.1/include/config/od.h
	modified:   tools/busybox-1.30.1/include/config/openvt.h
	modified:   tools/busybox-1.30.1/include/config/pam.h
	modified:   tools/busybox-1.30.1/include/config/partprobe.h
	modified:   tools/busybox-1.30.1/include/config/passwd.h
	modified:   tools/busybox-1.30.1/include/config/password/minlen.h
	modified:   tools/busybox-1.30.1/include/config/paste.h
	modified:   tools/busybox-1.30.1/include/config/patch.h
	modified:   tools/busybox-1.30.1/include/config/pgrep.h
	modified:   tools/busybox-1.30.1/include/config/pid/file/path.h
	modified:   tools/busybox-1.30.1/include/config/pidof.h
	modified:   tools/busybox-1.30.1/include/config/pie.h
	modified:   tools/busybox-1.30.1/include/config/ping.h
	modified:   tools/busybox-1.30.1/include/config/ping6.h
	modified:   tools/busybox-1.30.1/include/config/pipe/progress.h
	modified:   tools/busybox-1.30.1/include/config/pivot/root.h
	modified:   tools/busybox-1.30.1/include/config/pkill.h
	modified:   tools/busybox-1.30.1/include/config/platform/linux.h
	modified:   tools/busybox-1.30.1/include/config/pmap.h
	modified:   tools/busybox-1.30.1/include/config/popmaildir.h
	modified:   tools/busybox-1.30.1/include/config/poweroff.h
	modified:   tools/busybox-1.30.1/include/config/powertop.h
	modified:   tools/busybox-1.30.1/include/config/prefix.h
	modified:   tools/busybox-1.30.1/include/config/printenv.h
	modified:   tools/busybox-1.30.1/include/config/printf.h
	modified:   tools/busybox-1.30.1/include/config/ps.h
	modified:   tools/busybox-1.30.1/include/config/pscan.h
	modified:   tools/busybox-1.30.1/include/config/pstree.h
	modified:   tools/busybox-1.30.1/include/config/pwd.h
	modified:   tools/busybox-1.30.1/include/config/pwdx.h
	modified:   tools/busybox-1.30.1/include/config/raidautorun.h
	modified:   tools/busybox-1.30.1/include/config/rdate.h
	modified:   tools/busybox-1.30.1/include/config/rdev.h
	modified:   tools/busybox-1.30.1/include/config/readahead.h
	modified:   tools/busybox-1.30.1/include/config/readlink.h
	modified:   tools/busybox-1.30.1/include/config/readprofile.h
	modified:   tools/busybox-1.30.1/include/config/realpath.h
	modified:   tools/busybox-1.30.1/include/config/reboot.h
	modified:   tools/busybox-1.30.1/include/config/reformime.h
	modified:   tools/busybox-1.30.1/include/config/remove/shell.h
	modified:   tools/busybox-1.30.1/include/config/renice.h
	modified:   tools/busybox-1.30.1/include/config/reset.h
	modified:   tools/busybox-1.30.1/include/config/resize.h
	modified:   tools/busybox-1.30.1/include/config/restorecon.h
	modified:   tools/busybox-1.30.1/include/config/resume.h
	modified:   tools/busybox-1.30.1/include/config/rev.h
	modified:   tools/busybox-1.30.1/include/config/rfkill.h
	modified:   tools/busybox-1.30.1/include/config/rm.h
	modified:   tools/busybox-1.30.1/include/config/rmdir.h
	modified:   tools/busybox-1.30.1/include/config/rmmod.h
	modified:   tools/busybox-1.30.1/include/config/route.h
	modified:   tools/busybox-1.30.1/include/config/rpm.h
	modified:   tools/busybox-1.30.1/include/config/rpm2cpio.h
	modified:   tools/busybox-1.30.1/include/config/rtcwake.h
	modified:   tools/busybox-1.30.1/include/config/run/init.h
	modified:   tools/busybox-1.30.1/include/config/run/parts.h
	modified:   tools/busybox-1.30.1/include/config/runcon.h
	modified:   tools/busybox-1.30.1/include/config/runlevel.h
	modified:   tools/busybox-1.30.1/include/config/runsv.h
	modified:   tools/busybox-1.30.1/include/config/runsvdir.h
	modified:   tools/busybox-1.30.1/include/config/rx.h
	modified:   tools/busybox-1.30.1/include/config/script.h
	modified:   tools/busybox-1.30.1/include/config/scriptreplay.h
	modified:   tools/busybox-1.30.1/include/config/sed.h
	modified:   tools/busybox-1.30.1/include/config/selinux.h
	modified:   tools/busybox-1.30.1/include/config/selinuxenabled.h
	modified:   tools/busybox-1.30.1/include/config/sendmail.h
	modified:   tools/busybox-1.30.1/include/config/seq.h
	modified:   tools/busybox-1.30.1/include/config/sestatus.h
	modified:   tools/busybox-1.30.1/include/config/setarch.h
	modified:   tools/busybox-1.30.1/include/config/setconsole.h
	modified:   tools/busybox-1.30.1/include/config/setenforce.h
	modified:   tools/busybox-1.30.1/include/config/setfattr.h
	modified:   tools/busybox-1.30.1/include/config/setfiles.h
	modified:   tools/busybox-1.30.1/include/config/setfont.h
	modified:   tools/busybox-1.30.1/include/config/setkeycodes.h
	modified:   tools/busybox-1.30.1/include/config/setlogcons.h
	modified:   tools/busybox-1.30.1/include/config/setpriv.h
	modified:   tools/busybox-1.30.1/include/config/setsebool.h
	modified:   tools/busybox-1.30.1/include/config/setserial.h
	modified:   tools/busybox-1.30.1/include/config/setsid.h
	modified:   tools/busybox-1.30.1/include/config/setuidgid.h
	modified:   tools/busybox-1.30.1/include/config/sh/is/ash.h
	modified:   tools/busybox-1.30.1/include/config/sh/is/hush.h
	modified:   tools/busybox-1.30.1/include/config/sh/is/none.h
	modified:   tools/busybox-1.30.1/include/config/sha1sum.h
	modified:   tools/busybox-1.30.1/include/config/sha256sum.h
	modified:   tools/busybox-1.30.1/include/config/sha3/small.h
	modified:   tools/busybox-1.30.1/include/config/sha3sum.h
	modified:   tools/busybox-1.30.1/include/config/sha512sum.h
	modified:   tools/busybox-1.30.1/include/config/show/usage.h
	modified:   tools/busybox-1.30.1/include/config/showkey.h
	modified:   tools/busybox-1.30.1/include/config/shred.h
	modified:   tools/busybox-1.30.1/include/config/shuf.h
	modified:   tools/busybox-1.30.1/include/config/slattach.h
	modified:   tools/busybox-1.30.1/include/config/sleep.h
	modified:   tools/busybox-1.30.1/include/config/smemcap.h
	modified:   tools/busybox-1.30.1/include/config/softlimit.h
	modified:   tools/busybox-1.30.1/include/config/sort.h
	modified:   tools/busybox-1.30.1/include/config/split.h
	modified:   tools/busybox-1.30.1/include/config/ssl/client.h
	modified:   tools/busybox-1.30.1/include/config/stack/optimization/386.h
	modified:   tools/busybox-1.30.1/include/config/start/stop/daemon.h
	modified:   tools/busybox-1.30.1/include/config/stat.h
	modified:   tools/busybox-1.30.1/include/config/static.h
	modified:   tools/busybox-1.30.1/include/config/strings.h
	modified:   tools/busybox-1.30.1/include/config/stty.h
	modified:   tools/busybox-1.30.1/include/config/su.h
	modified:   tools/busybox-1.30.1/include/config/subst/wchar.h
	modified:   tools/busybox-1.30.1/include/config/sulogin.h
	modified:   tools/busybox-1.30.1/include/config/sum.h
	modified:   tools/busybox-1.30.1/include/config/sv.h
	modified:   tools/busybox-1.30.1/include/config/sv/default/service/dir.h
	modified:   tools/busybox-1.30.1/include/config/svc.h
	modified:   tools/busybox-1.30.1/include/config/svlogd.h
	modified:   tools/busybox-1.30.1/include/config/svok.h
	modified:   tools/busybox-1.30.1/include/config/swapoff.h
	modified:   tools/busybox-1.30.1/include/config/swapon.h
	modified:   tools/busybox-1.30.1/include/config/switch/root.h
	modified:   tools/busybox-1.30.1/include/config/sync.h
	modified:   tools/busybox-1.30.1/include/config/syslogd.h
	modified:   tools/busybox-1.30.1/include/config/sysroot.h
	modified:   tools/busybox-1.30.1/include/config/tac.h
	modified:   tools/busybox-1.30.1/include/config/tail.h
	modified:   tools/busybox-1.30.1/include/config/tar.h
	modified:   tools/busybox-1.30.1/include/config/taskset.h
	modified:   tools/busybox-1.30.1/include/config/tc.h
	modified:   tools/busybox-1.30.1/include/config/tcpsvd.h
	modified:   tools/busybox-1.30.1/include/config/tee.h
	modified:   tools/busybox-1.30.1/include/config/telinit/path.h
	modified:   tools/busybox-1.30.1/include/config/telnet.h
	modified:   tools/busybox-1.30.1/include/config/telnetd.h
	modified:   tools/busybox-1.30.1/include/config/test.h
	modified:   tools/busybox-1.30.1/include/config/test1.h
	modified:   tools/busybox-1.30.1/include/config/test2.h
	modified:   tools/busybox-1.30.1/include/config/tftp.h
	modified:   tools/busybox-1.30.1/include/config/tftp/debug.h
	modified:   tools/busybox-1.30.1/include/config/tftpd.h
	modified:   tools/busybox-1.30.1/include/config/time.h
	modified:   tools/busybox-1.30.1/include/config/timeout.h
	modified:   tools/busybox-1.30.1/include/config/tls.h
	modified:   tools/busybox-1.30.1/include/config/top.h
	modified:   tools/busybox-1.30.1/include/config/touch.h
	modified:   tools/busybox-1.30.1/include/config/tr.h
	modified:   tools/busybox-1.30.1/include/config/traceroute.h
	modified:   tools/busybox-1.30.1/include/config/traceroute6.h
	modified:   tools/busybox-1.30.1/include/config/true.h
	modified:   tools/busybox-1.30.1/include/config/truncate.h
	modified:   tools/busybox-1.30.1/include/config/tty.h
	modified:   tools/busybox-1.30.1/include/config/ttysize.h
	modified:   tools/busybox-1.30.1/include/config/tunctl.h
	modified:   tools/busybox-1.30.1/include/config/tune2fs.h
	modified:   tools/busybox-1.30.1/include/config/ubiattach.h
	modified:   tools/busybox-1.30.1/include/config/ubidetach.h
	modified:   tools/busybox-1.30.1/include/config/ubimkvol.h
	modified:   tools/busybox-1.30.1/include/config/ubirename.h
	modified:   tools/busybox-1.30.1/include/config/ubirmvol.h
	modified:   tools/busybox-1.30.1/include/config/ubirsvol.h
	modified:   tools/busybox-1.30.1/include/config/ubiupdatevol.h
	modified:   tools/busybox-1.30.1/include/config/udhcp/debug.h
	modified:   tools/busybox-1.30.1/include/config/udhcpc.h
	modified:   tools/busybox-1.30.1/include/config/udhcpc/default/script.h
	modified:   tools/busybox-1.30.1/include/config/udhcpc/slack/for/buggy/servers.h
	modified:   tools/busybox-1.30.1/include/config/udhcpc6.h
	modified:   tools/busybox-1.30.1/include/config/udhcpd.h
	modified:   tools/busybox-1.30.1/include/config/udpsvd.h
	modified:   tools/busybox-1.30.1/include/config/uevent.h
	modified:   tools/busybox-1.30.1/include/config/umount.h
	modified:   tools/busybox-1.30.1/include/config/uname.h
	modified:   tools/busybox-1.30.1/include/config/uname/osname.h
	modified:   tools/busybox-1.30.1/include/config/uncompress.h
	modified:   tools/busybox-1.30.1/include/config/unexpand.h
	modified:   tools/busybox-1.30.1/include/config/unicode/bidi/support.h
	modified:   tools/busybox-1.30.1/include/config/unicode/combining/wchars.h
	modified:   tools/busybox-1.30.1/include/config/unicode/neutral/table.h
	modified:   tools/busybox-1.30.1/include/config/unicode/preserve/broken.h
	modified:   tools/busybox-1.30.1/include/config/unicode/support.h
	modified:   tools/busybox-1.30.1/include/config/unicode/using/locale.h
	modified:   tools/busybox-1.30.1/include/config/unicode/wide/wchars.h
	modified:   tools/busybox-1.30.1/include/config/uniq.h
	modified:   tools/busybox-1.30.1/include/config/unit/test.h
	modified:   tools/busybox-1.30.1/include/config/unix2dos.h
	modified:   tools/busybox-1.30.1/include/config/unlink.h
	modified:   tools/busybox-1.30.1/include/config/unlzma.h
	modified:   tools/busybox-1.30.1/include/config/unlzop.h
	modified:   tools/busybox-1.30.1/include/config/unshare.h
	modified:   tools/busybox-1.30.1/include/config/unxz.h
	modified:   tools/busybox-1.30.1/include/config/unzip.h
	modified:   tools/busybox-1.30.1/include/config/uptime.h
	modified:   tools/busybox-1.30.1/include/config/use/bb/crypt.h
	modified:   tools/busybox-1.30.1/include/config/use/bb/crypt/sha.h
	modified:   tools/busybox-1.30.1/include/config/use/bb/pwd/grp.h
	modified:   tools/busybox-1.30.1/include/config/use/bb/shadow.h
	modified:   tools/busybox-1.30.1/include/config/use/portable/code.h
	modified:   tools/busybox-1.30.1/include/config/users.h
	modified:   tools/busybox-1.30.1/include/config/usleep.h
	modified:   tools/busybox-1.30.1/include/config/uudecode.h
	modified:   tools/busybox-1.30.1/include/config/uuencode.h
	modified:   tools/busybox-1.30.1/include/config/vconfig.h
	modified:   tools/busybox-1.30.1/include/config/verbose/resolution/errors.h
	modified:   tools/busybox-1.30.1/include/config/vi.h
	modified:   tools/busybox-1.30.1/include/config/vlock.h
	modified:   tools/busybox-1.30.1/include/config/volname.h
	modified:   tools/busybox-1.30.1/include/config/volumeid.h
	modified:   tools/busybox-1.30.1/include/config/w.h
	modified:   tools/busybox-1.30.1/include/config/wall.h
	modified:   tools/busybox-1.30.1/include/config/watch.h
	modified:   tools/busybox-1.30.1/include/config/watchdog.h
	modified:   tools/busybox-1.30.1/include/config/wc.h
	modified:   tools/busybox-1.30.1/include/config/werror.h
	modified:   tools/busybox-1.30.1/include/config/wget.h
	modified:   tools/busybox-1.30.1/include/config/which.h
	modified:   tools/busybox-1.30.1/include/config/who.h
	modified:   tools/busybox-1.30.1/include/config/whoami.h
	modified:   tools/busybox-1.30.1/include/config/whois.h
	modified:   tools/busybox-1.30.1/include/config/xargs.h
	modified:   tools/busybox-1.30.1/include/config/xxd.h
	modified:   tools/busybox-1.30.1/include/config/xz.h
	modified:   tools/busybox-1.30.1/include/config/xzcat.h
	modified:   tools/busybox-1.30.1/include/config/yes.h
	modified:   tools/busybox-1.30.1/include/config/zcat.h
	modified:   tools/busybox-1.30.1/include/config/zcip.h
	modified:   tools/busybox-1.30.1/include/dump.h
	modified:   tools/busybox-1.30.1/include/embedded_scripts.h
	modified:   tools/busybox-1.30.1/include/fix_u32.h
	modified:   tools/busybox-1.30.1/include/grp_.h
	modified:   tools/busybox-1.30.1/include/inet_common.h
	modified:   tools/busybox-1.30.1/include/libbb.h
	modified:   tools/busybox-1.30.1/include/liblzo_interface.h
	modified:   tools/busybox-1.30.1/include/platform.h
	modified:   tools/busybox-1.30.1/include/pwd_.h
	modified:   tools/busybox-1.30.1/include/rtc_.h
	modified:   tools/busybox-1.30.1/include/shadow_.h
	modified:   tools/busybox-1.30.1/include/unicode.h
	modified:   tools/busybox-1.30.1/include/usage.h
	modified:   tools/busybox-1.30.1/include/usage.src.h
	modified:   tools/busybox-1.30.1/include/usage_compressed.h
	modified:   tools/busybox-1.30.1/include/volume_id.h
	modified:   tools/busybox-1.30.1/include/xatonum.h
	modified:   tools/busybox-1.30.1/include/xregex.h
	modified:   tools/busybox-1.30.1/init/.bootchartd.o.cmd
	modified:   tools/busybox-1.30.1/init/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/init/.halt.o.cmd
	modified:   tools/busybox-1.30.1/init/.init.o.cmd
	modified:   tools/busybox-1.30.1/init/.lib.a.cmd
	modified:   tools/busybox-1.30.1/init/Config.in
	modified:   tools/busybox-1.30.1/init/Config.src
	modified:   tools/busybox-1.30.1/init/Kbuild
	modified:   tools/busybox-1.30.1/init/Kbuild.src
	modified:   tools/busybox-1.30.1/init/bootchartd.c
	modified:   tools/busybox-1.30.1/init/bootchartd.o
	modified:   tools/busybox-1.30.1/init/built-in.o
	modified:   tools/busybox-1.30.1/init/halt.c
	modified:   tools/busybox-1.30.1/init/halt.o
	modified:   tools/busybox-1.30.1/init/init.c
	modified:   tools/busybox-1.30.1/init/init.o
	modified:   tools/busybox-1.30.1/init/lib.a
	modified:   tools/busybox-1.30.1/init/reboot.h
	modified:   tools/busybox-1.30.1/klibc-utils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/klibc-utils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/klibc-utils/.nuke.o.cmd
	modified:   tools/busybox-1.30.1/klibc-utils/.resume.o.cmd
	modified:   tools/busybox-1.30.1/klibc-utils/Config.in
	modified:   tools/busybox-1.30.1/klibc-utils/Config.src
	modified:   tools/busybox-1.30.1/klibc-utils/Kbuild
	modified:   tools/busybox-1.30.1/klibc-utils/Kbuild.src
	modified:   tools/busybox-1.30.1/klibc-utils/built-in.o
	modified:   tools/busybox-1.30.1/klibc-utils/lib.a
	modified:   tools/busybox-1.30.1/klibc-utils/minips.c
	modified:   tools/busybox-1.30.1/klibc-utils/nuke.c
	modified:   tools/busybox-1.30.1/klibc-utils/nuke.o
	modified:   tools/busybox-1.30.1/klibc-utils/resume.c
	modified:   tools/busybox-1.30.1/klibc-utils/resume.o
	modified:   tools/busybox-1.30.1/klibc-utils/run-init.c
	modified:   tools/busybox-1.30.1/libbb/.appletlib.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.ask_confirmation.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.auto_string.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_askpass.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_bswap_64.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_cat.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_do_delay.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_getgroups.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_getsockname.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_pwd.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_qsort.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.bb_strtonum.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.capability.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.change_identity.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.chomp.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.common_bufsiz.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.compare_string_array.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.concat_path_file.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.concat_subpath_file.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.copy_file.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.copyfd.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.correct_password.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.crc32.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.default_error_retval.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.device_open.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.dump.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.duration.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.endofname.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.executable.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.fclose_nonstdin.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.fflush_stdout_and_exit.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.fgets_str.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.find_mount_point.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.find_pid_by_name.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.find_root_device.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.full_write.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.get_console.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.get_cpu_count.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.get_last_path_component.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.get_line_from_file.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.get_shell_name.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.get_volsize.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.getopt32.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.getopt_allopts.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.getpty.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.hash_md5_sha.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.herror_msg.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.human_readable.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.in_ether.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.inet_cksum.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.inet_common.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.inode_hash.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.isdirectory.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.isqrt.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.kernel_version.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.last_char_is.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.lib.a.cmd
	modified:   tools/busybox-1.30.1/libbb/.lineedit.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.lineedit_ptr_hack.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.llist.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.logenv.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.login.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.loop.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.make_directory.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.makedev.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.match_fstype.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.messages.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.missing_syscalls.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.mode_string.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.nuke_str.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.obscure.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.parse_config.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.parse_mode.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.percent_decode.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.perror_msg.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.perror_nomsg.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.perror_nomsg_and_die.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.pidfile.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.platform.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.print_flags.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.print_numbered_lines.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.printable.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.printable_string.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.process_escape_sequence.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.procps.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.progress.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.ptr_to_globals.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.pw_encrypt.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.read.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.read_key.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.read_printf.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.recursive_action.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.remove_file.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.replace.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.rtc.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.run_shell.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.safe_gethostname.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.safe_poll.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.safe_strncpy.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.safe_write.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.securetty.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.setup_environment.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.signals.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.simplify_path.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.single_argv.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.skip_whitespace.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.speed_table.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.str_tolower.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.strrstr.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.sysconf.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.time.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.trim.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.u_signal_names.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.ubi.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.udp_io.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.unicode.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.update_passwd.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.utmp.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.uuencode.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.verror_msg.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.vfork_daemon_rexec.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.warn_ignoring_args.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.wfopen.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.wfopen_input.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.write.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xatonum.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xconnect.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xfunc_die.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xfuncs.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xfuncs_printf.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xgetcwd.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xgethostbyname.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xreadlink.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xrealloc_vector.o.cmd
	modified:   tools/busybox-1.30.1/libbb/.xregcomp.o.cmd
	modified:   tools/busybox-1.30.1/libbb/Config.in
	modified:   tools/busybox-1.30.1/libbb/Config.src
	modified:   tools/busybox-1.30.1/libbb/Kbuild
	modified:   tools/busybox-1.30.1/libbb/Kbuild.src
	modified:   tools/busybox-1.30.1/libbb/README
	modified:   tools/busybox-1.30.1/libbb/appletlib.c
	modified:   tools/busybox-1.30.1/libbb/appletlib.o
	modified:   tools/busybox-1.30.1/libbb/ask_confirmation.c
	modified:   tools/busybox-1.30.1/libbb/ask_confirmation.o
	modified:   tools/busybox-1.30.1/libbb/auto_string.c
	modified:   tools/busybox-1.30.1/libbb/auto_string.o
	modified:   tools/busybox-1.30.1/libbb/bb_askpass.c
	modified:   tools/busybox-1.30.1/libbb/bb_askpass.o
	modified:   tools/busybox-1.30.1/libbb/bb_bswap_64.c
	modified:   tools/busybox-1.30.1/libbb/bb_bswap_64.o
	modified:   tools/busybox-1.30.1/libbb/bb_cat.c
	modified:   tools/busybox-1.30.1/libbb/bb_cat.o
	modified:   tools/busybox-1.30.1/libbb/bb_do_delay.c
	modified:   tools/busybox-1.30.1/libbb/bb_do_delay.o
	modified:   tools/busybox-1.30.1/libbb/bb_getgroups.c
	modified:   tools/busybox-1.30.1/libbb/bb_getgroups.o
	modified:   tools/busybox-1.30.1/libbb/bb_getsockname.c
	modified:   tools/busybox-1.30.1/libbb/bb_getsockname.o
	modified:   tools/busybox-1.30.1/libbb/bb_pwd.c
	modified:   tools/busybox-1.30.1/libbb/bb_pwd.o
	modified:   tools/busybox-1.30.1/libbb/bb_qsort.c
	modified:   tools/busybox-1.30.1/libbb/bb_qsort.o
	modified:   tools/busybox-1.30.1/libbb/bb_strtod.c
	modified:   tools/busybox-1.30.1/libbb/bb_strtonum.c
	modified:   tools/busybox-1.30.1/libbb/bb_strtonum.o
	modified:   tools/busybox-1.30.1/libbb/bbunit.c
	modified:   tools/busybox-1.30.1/libbb/built-in.o
	modified:   tools/busybox-1.30.1/libbb/capability.c
	modified:   tools/busybox-1.30.1/libbb/capability.o
	modified:   tools/busybox-1.30.1/libbb/change_identity.c
	modified:   tools/busybox-1.30.1/libbb/change_identity.o
	modified:   tools/busybox-1.30.1/libbb/chomp.c
	modified:   tools/busybox-1.30.1/libbb/chomp.o
	modified:   tools/busybox-1.30.1/libbb/common_bufsiz.c
	modified:   tools/busybox-1.30.1/libbb/common_bufsiz.o
	modified:   tools/busybox-1.30.1/libbb/compare_string_array.c
	modified:   tools/busybox-1.30.1/libbb/compare_string_array.o
	modified:   tools/busybox-1.30.1/libbb/concat_path_file.c
	modified:   tools/busybox-1.30.1/libbb/concat_path_file.o
	modified:   tools/busybox-1.30.1/libbb/concat_subpath_file.c
	modified:   tools/busybox-1.30.1/libbb/concat_subpath_file.o
	modified:   tools/busybox-1.30.1/libbb/copy_file.c
	modified:   tools/busybox-1.30.1/libbb/copy_file.o
	modified:   tools/busybox-1.30.1/libbb/copyfd.c
	modified:   tools/busybox-1.30.1/libbb/copyfd.o
	modified:   tools/busybox-1.30.1/libbb/correct_password.c
	modified:   tools/busybox-1.30.1/libbb/correct_password.o
	modified:   tools/busybox-1.30.1/libbb/crc32.c
	modified:   tools/busybox-1.30.1/libbb/crc32.o
	modified:   tools/busybox-1.30.1/libbb/default_error_retval.c
	modified:   tools/busybox-1.30.1/libbb/default_error_retval.o
	modified:   tools/busybox-1.30.1/libbb/device_open.c
	modified:   tools/busybox-1.30.1/libbb/device_open.o
	modified:   tools/busybox-1.30.1/libbb/die_if_bad_username.c
	modified:   tools/busybox-1.30.1/libbb/dump.c
	modified:   tools/busybox-1.30.1/libbb/dump.o
	modified:   tools/busybox-1.30.1/libbb/duration.c
	modified:   tools/busybox-1.30.1/libbb/duration.o
	modified:   tools/busybox-1.30.1/libbb/endofname.c
	modified:   tools/busybox-1.30.1/libbb/endofname.o
	modified:   tools/busybox-1.30.1/libbb/executable.c
	modified:   tools/busybox-1.30.1/libbb/executable.o
	modified:   tools/busybox-1.30.1/libbb/fclose_nonstdin.c
	modified:   tools/busybox-1.30.1/libbb/fclose_nonstdin.o
	modified:   tools/busybox-1.30.1/libbb/fflush_stdout_and_exit.c
	modified:   tools/busybox-1.30.1/libbb/fflush_stdout_and_exit.o
	modified:   tools/busybox-1.30.1/libbb/fgets_str.c
	modified:   tools/busybox-1.30.1/libbb/fgets_str.o
	modified:   tools/busybox-1.30.1/libbb/find_mount_point.c
	modified:   tools/busybox-1.30.1/libbb/find_mount_point.o
	modified:   tools/busybox-1.30.1/libbb/find_pid_by_name.c
	modified:   tools/busybox-1.30.1/libbb/find_pid_by_name.o
	modified:   tools/busybox-1.30.1/libbb/find_root_device.c
	modified:   tools/busybox-1.30.1/libbb/find_root_device.o
	modified:   tools/busybox-1.30.1/libbb/full_write.c
	modified:   tools/busybox-1.30.1/libbb/full_write.o
	modified:   tools/busybox-1.30.1/libbb/get_console.c
	modified:   tools/busybox-1.30.1/libbb/get_console.o
	modified:   tools/busybox-1.30.1/libbb/get_cpu_count.c
	modified:   tools/busybox-1.30.1/libbb/get_cpu_count.o
	modified:   tools/busybox-1.30.1/libbb/get_last_path_component.c
	modified:   tools/busybox-1.30.1/libbb/get_last_path_component.o
	modified:   tools/busybox-1.30.1/libbb/get_line_from_file.c
	modified:   tools/busybox-1.30.1/libbb/get_line_from_file.o
	modified:   tools/busybox-1.30.1/libbb/get_shell_name.c
	modified:   tools/busybox-1.30.1/libbb/get_shell_name.o
	modified:   tools/busybox-1.30.1/libbb/get_volsize.c
	modified:   tools/busybox-1.30.1/libbb/get_volsize.o
	modified:   tools/busybox-1.30.1/libbb/getopt32.c
	modified:   tools/busybox-1.30.1/libbb/getopt32.o
	modified:   tools/busybox-1.30.1/libbb/getopt_allopts.c
	modified:   tools/busybox-1.30.1/libbb/getopt_allopts.o
	modified:   tools/busybox-1.30.1/libbb/getpty.c
	modified:   tools/busybox-1.30.1/libbb/getpty.o
	modified:   tools/busybox-1.30.1/libbb/hash_md5_sha.c
	modified:   tools/busybox-1.30.1/libbb/hash_md5_sha.o
	modified:   tools/busybox-1.30.1/libbb/hash_md5prime.c
	modified:   tools/busybox-1.30.1/libbb/herror_msg.c
	modified:   tools/busybox-1.30.1/libbb/herror_msg.o
	modified:   tools/busybox-1.30.1/libbb/human_readable.c
	modified:   tools/busybox-1.30.1/libbb/human_readable.o
	modified:   tools/busybox-1.30.1/libbb/in_ether.c
	modified:   tools/busybox-1.30.1/libbb/in_ether.o
	modified:   tools/busybox-1.30.1/libbb/inet_cksum.c
	modified:   tools/busybox-1.30.1/libbb/inet_cksum.o
	modified:   tools/busybox-1.30.1/libbb/inet_common.c
	modified:   tools/busybox-1.30.1/libbb/inet_common.o
	modified:   tools/busybox-1.30.1/libbb/inode_hash.c
	modified:   tools/busybox-1.30.1/libbb/inode_hash.o
	modified:   tools/busybox-1.30.1/libbb/isdirectory.c
	modified:   tools/busybox-1.30.1/libbb/isdirectory.o
	modified:   tools/busybox-1.30.1/libbb/isqrt.c
	modified:   tools/busybox-1.30.1/libbb/isqrt.o
	modified:   tools/busybox-1.30.1/libbb/kernel_version.c
	modified:   tools/busybox-1.30.1/libbb/kernel_version.o
	modified:   tools/busybox-1.30.1/libbb/last_char_is.c
	modified:   tools/busybox-1.30.1/libbb/last_char_is.o
	modified:   tools/busybox-1.30.1/libbb/lib.a
	modified:   tools/busybox-1.30.1/libbb/lineedit.c
	modified:   tools/busybox-1.30.1/libbb/lineedit.o
	modified:   tools/busybox-1.30.1/libbb/lineedit_ptr_hack.c
	modified:   tools/busybox-1.30.1/libbb/lineedit_ptr_hack.o
	modified:   tools/busybox-1.30.1/libbb/llist.c
	modified:   tools/busybox-1.30.1/libbb/llist.o
	modified:   tools/busybox-1.30.1/libbb/logenv.c
	modified:   tools/busybox-1.30.1/libbb/logenv.o
	modified:   tools/busybox-1.30.1/libbb/login.c
	modified:   tools/busybox-1.30.1/libbb/login.o
	modified:   tools/busybox-1.30.1/libbb/loop.c
	modified:   tools/busybox-1.30.1/libbb/loop.o
	modified:   tools/busybox-1.30.1/libbb/make_directory.c
	modified:   tools/busybox-1.30.1/libbb/make_directory.o
	modified:   tools/busybox-1.30.1/libbb/makedev.c
	modified:   tools/busybox-1.30.1/libbb/makedev.o
	modified:   tools/busybox-1.30.1/libbb/match_fstype.c
	modified:   tools/busybox-1.30.1/libbb/match_fstype.o
	modified:   tools/busybox-1.30.1/libbb/messages.c
	modified:   tools/busybox-1.30.1/libbb/messages.o
	modified:   tools/busybox-1.30.1/libbb/missing_syscalls.c
	modified:   tools/busybox-1.30.1/libbb/missing_syscalls.o
	modified:   tools/busybox-1.30.1/libbb/mode_string.c
	modified:   tools/busybox-1.30.1/libbb/mode_string.o
	modified:   tools/busybox-1.30.1/libbb/mtab.c
	modified:   tools/busybox-1.30.1/libbb/nuke_str.c
	modified:   tools/busybox-1.30.1/libbb/nuke_str.o
	modified:   tools/busybox-1.30.1/libbb/obscure.c
	modified:   tools/busybox-1.30.1/libbb/obscure.o
	modified:   tools/busybox-1.30.1/libbb/parse_config.c
	modified:   tools/busybox-1.30.1/libbb/parse_config.o
	modified:   tools/busybox-1.30.1/libbb/parse_mode.c
	modified:   tools/busybox-1.30.1/libbb/parse_mode.o
	modified:   tools/busybox-1.30.1/libbb/percent_decode.c
	modified:   tools/busybox-1.30.1/libbb/percent_decode.o
	modified:   tools/busybox-1.30.1/libbb/perror_msg.c
	modified:   tools/busybox-1.30.1/libbb/perror_msg.o
	modified:   tools/busybox-1.30.1/libbb/perror_nomsg.c
	modified:   tools/busybox-1.30.1/libbb/perror_nomsg.o
	modified:   tools/busybox-1.30.1/libbb/perror_nomsg_and_die.c
	modified:   tools/busybox-1.30.1/libbb/perror_nomsg_and_die.o
	modified:   tools/busybox-1.30.1/libbb/pidfile.c
	modified:   tools/busybox-1.30.1/libbb/pidfile.o
	modified:   tools/busybox-1.30.1/libbb/platform.c
	modified:   tools/busybox-1.30.1/libbb/platform.o
	modified:   tools/busybox-1.30.1/libbb/print_flags.c
	modified:   tools/busybox-1.30.1/libbb/print_flags.o
	modified:   tools/busybox-1.30.1/libbb/print_numbered_lines.c
	modified:   tools/busybox-1.30.1/libbb/print_numbered_lines.o
	modified:   tools/busybox-1.30.1/libbb/printable.c
	modified:   tools/busybox-1.30.1/libbb/printable.o
	modified:   tools/busybox-1.30.1/libbb/printable_string.c
	modified:   tools/busybox-1.30.1/libbb/printable_string.o
	modified:   tools/busybox-1.30.1/libbb/process_escape_sequence.c
	modified:   tools/busybox-1.30.1/libbb/process_escape_sequence.o
	modified:   tools/busybox-1.30.1/libbb/procps.c
	modified:   tools/busybox-1.30.1/libbb/procps.o
	modified:   tools/busybox-1.30.1/libbb/progress.c
	modified:   tools/busybox-1.30.1/libbb/progress.o
	modified:   tools/busybox-1.30.1/libbb/ptr_to_globals.c
	modified:   tools/busybox-1.30.1/libbb/ptr_to_globals.o
	modified:   tools/busybox-1.30.1/libbb/pw_encrypt.c
	modified:   tools/busybox-1.30.1/libbb/pw_encrypt.o
	modified:   tools/busybox-1.30.1/libbb/pw_encrypt_des.c
	modified:   tools/busybox-1.30.1/libbb/pw_encrypt_md5.c
	modified:   tools/busybox-1.30.1/libbb/pw_encrypt_sha.c
	modified:   tools/busybox-1.30.1/libbb/read.c
	modified:   tools/busybox-1.30.1/libbb/read.o
	modified:   tools/busybox-1.30.1/libbb/read_key.c
	modified:   tools/busybox-1.30.1/libbb/read_key.o
	modified:   tools/busybox-1.30.1/libbb/read_printf.c
	modified:   tools/busybox-1.30.1/libbb/read_printf.o
	modified:   tools/busybox-1.30.1/libbb/recursive_action.c
	modified:   tools/busybox-1.30.1/libbb/recursive_action.o
	modified:   tools/busybox-1.30.1/libbb/remove_file.c
	modified:   tools/busybox-1.30.1/libbb/remove_file.o
	modified:   tools/busybox-1.30.1/libbb/replace.c
	modified:   tools/busybox-1.30.1/libbb/replace.o
	modified:   tools/busybox-1.30.1/libbb/rtc.c
	modified:   tools/busybox-1.30.1/libbb/rtc.o
	modified:   tools/busybox-1.30.1/libbb/run_shell.c
	modified:   tools/busybox-1.30.1/libbb/run_shell.o
	modified:   tools/busybox-1.30.1/libbb/safe_gethostname.c
	modified:   tools/busybox-1.30.1/libbb/safe_gethostname.o
	modified:   tools/busybox-1.30.1/libbb/safe_poll.c
	modified:   tools/busybox-1.30.1/libbb/safe_poll.o
	modified:   tools/busybox-1.30.1/libbb/safe_strncpy.c
	modified:   tools/busybox-1.30.1/libbb/safe_strncpy.o
	modified:   tools/busybox-1.30.1/libbb/safe_write.c
	modified:   tools/busybox-1.30.1/libbb/safe_write.o
	modified:   tools/busybox-1.30.1/libbb/securetty.c
	modified:   tools/busybox-1.30.1/libbb/securetty.o
	modified:   tools/busybox-1.30.1/libbb/selinux_common.c
	modified:   tools/busybox-1.30.1/libbb/setup_environment.c
	modified:   tools/busybox-1.30.1/libbb/setup_environment.o
	modified:   tools/busybox-1.30.1/libbb/signals.c
	modified:   tools/busybox-1.30.1/libbb/signals.o
	modified:   tools/busybox-1.30.1/libbb/simplify_path.c
	modified:   tools/busybox-1.30.1/libbb/simplify_path.o
	modified:   tools/busybox-1.30.1/libbb/single_argv.c
	modified:   tools/busybox-1.30.1/libbb/single_argv.o
	modified:   tools/busybox-1.30.1/libbb/skip_whitespace.c
	modified:   tools/busybox-1.30.1/libbb/skip_whitespace.o
	modified:   tools/busybox-1.30.1/libbb/speed_table.c
	modified:   tools/busybox-1.30.1/libbb/speed_table.o
	modified:   tools/busybox-1.30.1/libbb/str_tolower.c
	modified:   tools/busybox-1.30.1/libbb/str_tolower.o
	modified:   tools/busybox-1.30.1/libbb/strrstr.c
	modified:   tools/busybox-1.30.1/libbb/strrstr.o
	modified:   tools/busybox-1.30.1/libbb/sysconf.c
	modified:   tools/busybox-1.30.1/libbb/sysconf.o
	modified:   tools/busybox-1.30.1/libbb/time.c
	modified:   tools/busybox-1.30.1/libbb/time.o
	modified:   tools/busybox-1.30.1/libbb/trim.c
	modified:   tools/busybox-1.30.1/libbb/trim.o
	modified:   tools/busybox-1.30.1/libbb/u_signal_names.c
	modified:   tools/busybox-1.30.1/libbb/u_signal_names.o
	modified:   tools/busybox-1.30.1/libbb/ubi.c
	modified:   tools/busybox-1.30.1/libbb/ubi.o
	modified:   tools/busybox-1.30.1/libbb/udp_io.c
	modified:   tools/busybox-1.30.1/libbb/udp_io.o
	modified:   tools/busybox-1.30.1/libbb/unicode.c
	modified:   tools/busybox-1.30.1/libbb/unicode.o
	modified:   tools/busybox-1.30.1/libbb/update_passwd.c
	modified:   tools/busybox-1.30.1/libbb/update_passwd.o
	modified:   tools/busybox-1.30.1/libbb/utmp.c
	modified:   tools/busybox-1.30.1/libbb/utmp.o
	modified:   tools/busybox-1.30.1/libbb/uuencode.c
	modified:   tools/busybox-1.30.1/libbb/uuencode.o
	modified:   tools/busybox-1.30.1/libbb/verror_msg.c
	modified:   tools/busybox-1.30.1/libbb/verror_msg.o
	modified:   tools/busybox-1.30.1/libbb/vfork_daemon_rexec.c
	modified:   tools/busybox-1.30.1/libbb/vfork_daemon_rexec.o
	modified:   tools/busybox-1.30.1/libbb/warn_ignoring_args.c
	modified:   tools/busybox-1.30.1/libbb/warn_ignoring_args.o
	modified:   tools/busybox-1.30.1/libbb/wfopen.c
	modified:   tools/busybox-1.30.1/libbb/wfopen.o
	modified:   tools/busybox-1.30.1/libbb/wfopen_input.c
	modified:   tools/busybox-1.30.1/libbb/wfopen_input.o
	modified:   tools/busybox-1.30.1/libbb/write.c
	modified:   tools/busybox-1.30.1/libbb/write.o
	modified:   tools/busybox-1.30.1/libbb/xatonum.c
	modified:   tools/busybox-1.30.1/libbb/xatonum.o
	modified:   tools/busybox-1.30.1/libbb/xatonum_template.c
	modified:   tools/busybox-1.30.1/libbb/xconnect.c
	modified:   tools/busybox-1.30.1/libbb/xconnect.o
	modified:   tools/busybox-1.30.1/libbb/xfunc_die.c
	modified:   tools/busybox-1.30.1/libbb/xfunc_die.o
	modified:   tools/busybox-1.30.1/libbb/xfuncs.c
	modified:   tools/busybox-1.30.1/libbb/xfuncs.o
	modified:   tools/busybox-1.30.1/libbb/xfuncs_printf.c
	modified:   tools/busybox-1.30.1/libbb/xfuncs_printf.o
	modified:   tools/busybox-1.30.1/libbb/xgetcwd.c
	modified:   tools/busybox-1.30.1/libbb/xgetcwd.o
	modified:   tools/busybox-1.30.1/libbb/xgethostbyname.c
	modified:   tools/busybox-1.30.1/libbb/xgethostbyname.o
	modified:   tools/busybox-1.30.1/libbb/xreadlink.c
	modified:   tools/busybox-1.30.1/libbb/xreadlink.o
	modified:   tools/busybox-1.30.1/libbb/xrealloc_vector.c
	modified:   tools/busybox-1.30.1/libbb/xrealloc_vector.o
	modified:   tools/busybox-1.30.1/libbb/xregcomp.c
	modified:   tools/busybox-1.30.1/libbb/xregcomp.o
	modified:   tools/busybox-1.30.1/libpwdgrp/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/libpwdgrp/.lib.a.cmd
	modified:   tools/busybox-1.30.1/libpwdgrp/.pwd_grp.o.cmd
	modified:   tools/busybox-1.30.1/libpwdgrp/.uidgid_get.o.cmd
	modified:   tools/busybox-1.30.1/libpwdgrp/Kbuild
	modified:   tools/busybox-1.30.1/libpwdgrp/Kbuild.src
	modified:   tools/busybox-1.30.1/libpwdgrp/built-in.o
	modified:   tools/busybox-1.30.1/libpwdgrp/lib.a
	modified:   tools/busybox-1.30.1/libpwdgrp/pwd_grp.c
	modified:   tools/busybox-1.30.1/libpwdgrp/pwd_grp.o
	modified:   tools/busybox-1.30.1/libpwdgrp/uidgid_get.c
	modified:   tools/busybox-1.30.1/libpwdgrp/uidgid_get.o
	modified:   tools/busybox-1.30.1/loginutils/.add-remove-shell.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.addgroup.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.adduser.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.chpasswd.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.cryptpw.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.deluser.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.getty.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/loginutils/.login.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.passwd.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.su.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.sulogin.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/.vlock.o.cmd
	modified:   tools/busybox-1.30.1/loginutils/Config.in
	modified:   tools/busybox-1.30.1/loginutils/Config.src
	modified:   tools/busybox-1.30.1/loginutils/Kbuild
	modified:   tools/busybox-1.30.1/loginutils/Kbuild.src
	modified:   tools/busybox-1.30.1/loginutils/README
	modified:   tools/busybox-1.30.1/loginutils/add-remove-shell.c
	modified:   tools/busybox-1.30.1/loginutils/add-remove-shell.o
	modified:   tools/busybox-1.30.1/loginutils/addgroup.c
	modified:   tools/busybox-1.30.1/loginutils/addgroup.o
	modified:   tools/busybox-1.30.1/loginutils/adduser.c
	modified:   tools/busybox-1.30.1/loginutils/adduser.o
	modified:   tools/busybox-1.30.1/loginutils/built-in.o
	modified:   tools/busybox-1.30.1/loginutils/chpasswd.c
	modified:   tools/busybox-1.30.1/loginutils/chpasswd.o
	modified:   tools/busybox-1.30.1/loginutils/cryptpw.c
	modified:   tools/busybox-1.30.1/loginutils/cryptpw.o
	modified:   tools/busybox-1.30.1/loginutils/deluser.c
	modified:   tools/busybox-1.30.1/loginutils/deluser.o
	modified:   tools/busybox-1.30.1/loginutils/getty.c
	modified:   tools/busybox-1.30.1/loginutils/getty.o
	modified:   tools/busybox-1.30.1/loginutils/lib.a
	modified:   tools/busybox-1.30.1/loginutils/login.c
	modified:   tools/busybox-1.30.1/loginutils/login.o
	modified:   tools/busybox-1.30.1/loginutils/passwd.c
	modified:   tools/busybox-1.30.1/loginutils/passwd.o
	modified:   tools/busybox-1.30.1/loginutils/su.c
	modified:   tools/busybox-1.30.1/loginutils/su.o
	modified:   tools/busybox-1.30.1/loginutils/sulogin.c
	modified:   tools/busybox-1.30.1/loginutils/sulogin.o
	modified:   tools/busybox-1.30.1/loginutils/vlock.c
	modified:   tools/busybox-1.30.1/loginutils/vlock.o
	modified:   tools/busybox-1.30.1/mailutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/mailutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/mailutils/.mail.o.cmd
	modified:   tools/busybox-1.30.1/mailutils/.makemime.o.cmd
	modified:   tools/busybox-1.30.1/mailutils/.popmaildir.o.cmd
	modified:   tools/busybox-1.30.1/mailutils/.reformime.o.cmd
	modified:   tools/busybox-1.30.1/mailutils/.sendmail.o.cmd
	modified:   tools/busybox-1.30.1/mailutils/Config.in
	modified:   tools/busybox-1.30.1/mailutils/Config.src
	modified:   tools/busybox-1.30.1/mailutils/Kbuild
	modified:   tools/busybox-1.30.1/mailutils/Kbuild.src
	modified:   tools/busybox-1.30.1/mailutils/built-in.o
	modified:   tools/busybox-1.30.1/mailutils/lib.a
	modified:   tools/busybox-1.30.1/mailutils/mail.c
	modified:   tools/busybox-1.30.1/mailutils/mail.h
	modified:   tools/busybox-1.30.1/mailutils/mail.o
	modified:   tools/busybox-1.30.1/mailutils/makemime.c
	modified:   tools/busybox-1.30.1/mailutils/makemime.o
	modified:   tools/busybox-1.30.1/mailutils/popmaildir.c
	modified:   tools/busybox-1.30.1/mailutils/popmaildir.o
	modified:   tools/busybox-1.30.1/mailutils/reformime.c
	modified:   tools/busybox-1.30.1/mailutils/reformime.o
	modified:   tools/busybox-1.30.1/mailutils/sendmail.c
	modified:   tools/busybox-1.30.1/mailutils/sendmail.o
	modified:   tools/busybox-1.30.1/miscutils/.adjtimex.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.bc.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.beep.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.chat.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.conspy.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.crond.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.crontab.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.devmem.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.fbsplash.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.hdparm.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.hexedit.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.i2c_tools.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.less.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/miscutils/.lsscsi.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.makedevs.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.man.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.microcom.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.mt.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.nandwrite.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.partprobe.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.raidautorun.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.readahead.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.runlevel.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.rx.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.setfattr.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.setserial.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.strings.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.time.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.ttysize.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.ubi_tools.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.ubirename.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.volname.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/.watchdog.o.cmd
	modified:   tools/busybox-1.30.1/miscutils/Config.in
	modified:   tools/busybox-1.30.1/miscutils/Config.src
	modified:   tools/busybox-1.30.1/miscutils/Kbuild
	modified:   tools/busybox-1.30.1/miscutils/Kbuild.src
	modified:   tools/busybox-1.30.1/miscutils/adjtimex.c
	modified:   tools/busybox-1.30.1/miscutils/adjtimex.o
	modified:   tools/busybox-1.30.1/miscutils/bbconfig.c
	modified:   tools/busybox-1.30.1/miscutils/bc.c
	modified:   tools/busybox-1.30.1/miscutils/bc.o
	modified:   tools/busybox-1.30.1/miscutils/beep.c
	modified:   tools/busybox-1.30.1/miscutils/beep.o
	modified:   tools/busybox-1.30.1/miscutils/built-in.o
	modified:   tools/busybox-1.30.1/miscutils/chat.c
	modified:   tools/busybox-1.30.1/miscutils/chat.o
	modified:   tools/busybox-1.30.1/miscutils/conspy.c
	modified:   tools/busybox-1.30.1/miscutils/conspy.o
	modified:   tools/busybox-1.30.1/miscutils/crond.c
	modified:   tools/busybox-1.30.1/miscutils/crond.o
	modified:   tools/busybox-1.30.1/miscutils/crontab.c
	modified:   tools/busybox-1.30.1/miscutils/crontab.o
	modified:   tools/busybox-1.30.1/miscutils/dc.c
	modified:   tools/busybox-1.30.1/miscutils/devfsd.c
	modified:   tools/busybox-1.30.1/miscutils/devmem.c
	modified:   tools/busybox-1.30.1/miscutils/devmem.o
	modified:   tools/busybox-1.30.1/miscutils/fbsplash.c
	modified:   tools/busybox-1.30.1/miscutils/fbsplash.cfg
	modified:   tools/busybox-1.30.1/miscutils/fbsplash.o
	modified:   tools/busybox-1.30.1/miscutils/flash_eraseall.c
	modified:   tools/busybox-1.30.1/miscutils/flash_lock_unlock.c
	modified:   tools/busybox-1.30.1/miscutils/flashcp.c
	modified:   tools/busybox-1.30.1/miscutils/hdparm.c
	modified:   tools/busybox-1.30.1/miscutils/hdparm.o
	modified:   tools/busybox-1.30.1/miscutils/hexedit.c
	modified:   tools/busybox-1.30.1/miscutils/hexedit.o
	modified:   tools/busybox-1.30.1/miscutils/i2c_tools.c
	modified:   tools/busybox-1.30.1/miscutils/i2c_tools.o
	modified:   tools/busybox-1.30.1/miscutils/inotifyd.c
	modified:   tools/busybox-1.30.1/miscutils/less.c
	modified:   tools/busybox-1.30.1/miscutils/less.o
	modified:   tools/busybox-1.30.1/miscutils/lib.a
	modified:   tools/busybox-1.30.1/miscutils/lsscsi.c
	modified:   tools/busybox-1.30.1/miscutils/lsscsi.o
	modified:   tools/busybox-1.30.1/miscutils/makedevs.c
	modified:   tools/busybox-1.30.1/miscutils/makedevs.o
	modified:   tools/busybox-1.30.1/miscutils/man.c
	modified:   tools/busybox-1.30.1/miscutils/man.o
	modified:   tools/busybox-1.30.1/miscutils/microcom.c
	modified:   tools/busybox-1.30.1/miscutils/microcom.o
	modified:   tools/busybox-1.30.1/miscutils/mt.c
	modified:   tools/busybox-1.30.1/miscutils/mt.o
	modified:   tools/busybox-1.30.1/miscutils/nandwrite.c
	modified:   tools/busybox-1.30.1/miscutils/nandwrite.o
	modified:   tools/busybox-1.30.1/miscutils/partprobe.c
	modified:   tools/busybox-1.30.1/miscutils/partprobe.o
	modified:   tools/busybox-1.30.1/miscutils/raidautorun.c
	modified:   tools/busybox-1.30.1/miscutils/raidautorun.o
	modified:   tools/busybox-1.30.1/miscutils/readahead.c
	modified:   tools/busybox-1.30.1/miscutils/readahead.o
	modified:   tools/busybox-1.30.1/miscutils/rfkill.c
	modified:   tools/busybox-1.30.1/miscutils/runlevel.c
	modified:   tools/busybox-1.30.1/miscutils/runlevel.o
	modified:   tools/busybox-1.30.1/miscutils/rx.c
	modified:   tools/busybox-1.30.1/miscutils/rx.o
	modified:   tools/busybox-1.30.1/miscutils/setfattr.c
	modified:   tools/busybox-1.30.1/miscutils/setfattr.o
	modified:   tools/busybox-1.30.1/miscutils/setserial.c
	modified:   tools/busybox-1.30.1/miscutils/setserial.o
	modified:   tools/busybox-1.30.1/miscutils/strings.c
	modified:   tools/busybox-1.30.1/miscutils/strings.o
	modified:   tools/busybox-1.30.1/miscutils/time.c
	modified:   tools/busybox-1.30.1/miscutils/time.o
	modified:   tools/busybox-1.30.1/miscutils/ttysize.c
	modified:   tools/busybox-1.30.1/miscutils/ttysize.o
	modified:   tools/busybox-1.30.1/miscutils/ubi_tools.c
	modified:   tools/busybox-1.30.1/miscutils/ubi_tools.o
	modified:   tools/busybox-1.30.1/miscutils/ubirename.c
	modified:   tools/busybox-1.30.1/miscutils/ubirename.o
	modified:   tools/busybox-1.30.1/miscutils/volname.c
	modified:   tools/busybox-1.30.1/miscutils/volname.o
	modified:   tools/busybox-1.30.1/miscutils/watchdog.c
	modified:   tools/busybox-1.30.1/miscutils/watchdog.o
	modified:   tools/busybox-1.30.1/modutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/modutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/modutils/.modinfo.o.cmd
	modified:   tools/busybox-1.30.1/modutils/.modprobe-small.o.cmd
	modified:   tools/busybox-1.30.1/modutils/.modutils.o.cmd
	modified:   tools/busybox-1.30.1/modutils/Config.in
	modified:   tools/busybox-1.30.1/modutils/Config.src
	modified:   tools/busybox-1.30.1/modutils/Kbuild
	modified:   tools/busybox-1.30.1/modutils/Kbuild.src
	modified:   tools/busybox-1.30.1/modutils/built-in.o
	modified:   tools/busybox-1.30.1/modutils/depmod.c
	modified:   tools/busybox-1.30.1/modutils/insmod.c
	modified:   tools/busybox-1.30.1/modutils/lib.a
	modified:   tools/busybox-1.30.1/modutils/lsmod.c
	modified:   tools/busybox-1.30.1/modutils/modinfo.c
	modified:   tools/busybox-1.30.1/modutils/modinfo.o
	modified:   tools/busybox-1.30.1/modutils/modprobe-small.c
	modified:   tools/busybox-1.30.1/modutils/modprobe-small.o
	modified:   tools/busybox-1.30.1/modutils/modprobe.c
	modified:   tools/busybox-1.30.1/modutils/modutils-24.c
	modified:   tools/busybox-1.30.1/modutils/modutils.c
	modified:   tools/busybox-1.30.1/modutils/modutils.h
	modified:   tools/busybox-1.30.1/modutils/modutils.o
	modified:   tools/busybox-1.30.1/modutils/rmmod.c
	modified:   tools/busybox-1.30.1/networking/.arp.o.cmd
	modified:   tools/busybox-1.30.1/networking/.arping.o.cmd
	modified:   tools/busybox-1.30.1/networking/.brctl.o.cmd
	modified:   tools/busybox-1.30.1/networking/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/networking/.dnsd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ether-wake.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ftpd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ftpgetput.o.cmd
	modified:   tools/busybox-1.30.1/networking/.hostname.o.cmd
	modified:   tools/busybox-1.30.1/networking/.httpd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ifconfig.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ifenslave.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ifplugd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ifupdown.o.cmd
	modified:   tools/busybox-1.30.1/networking/.inetd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.interface.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ip.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ipcalc.o.cmd
	modified:   tools/busybox-1.30.1/networking/.isrv.o.cmd
	modified:   tools/busybox-1.30.1/networking/.isrv_identd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.lib.a.cmd
	modified:   tools/busybox-1.30.1/networking/.nameif.o.cmd
	modified:   tools/busybox-1.30.1/networking/.nbd-client.o.cmd
	modified:   tools/busybox-1.30.1/networking/.nc.o.cmd
	modified:   tools/busybox-1.30.1/networking/.netstat.o.cmd
	modified:   tools/busybox-1.30.1/networking/.nslookup.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ntpd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.parse_pasv_epsv.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ping.o.cmd
	modified:   tools/busybox-1.30.1/networking/.pscan.o.cmd
	modified:   tools/busybox-1.30.1/networking/.route.o.cmd
	modified:   tools/busybox-1.30.1/networking/.slattach.o.cmd
	modified:   tools/busybox-1.30.1/networking/.ssl_client.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tc.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tcpudp.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tcpudp_perhost.o.cmd
	modified:   tools/busybox-1.30.1/networking/.telnet.o.cmd
	modified:   tools/busybox-1.30.1/networking/.telnetd.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tftp.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_aes.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_aesgcm.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_fe.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_pstm.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_pstm_montgomery_reduce.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_pstm_mul_comba.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_pstm_sqr_comba.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tls_rsa.o.cmd
	modified:   tools/busybox-1.30.1/networking/.traceroute.o.cmd
	modified:   tools/busybox-1.30.1/networking/.tunctl.o.cmd
	modified:   tools/busybox-1.30.1/networking/.vconfig.o.cmd
	modified:   tools/busybox-1.30.1/networking/.wget.o.cmd
	modified:   tools/busybox-1.30.1/networking/.whois.o.cmd
	modified:   tools/busybox-1.30.1/networking/.zcip.o.cmd
	modified:   tools/busybox-1.30.1/networking/Config.in
	modified:   tools/busybox-1.30.1/networking/Config.src
	modified:   tools/busybox-1.30.1/networking/Kbuild
	modified:   tools/busybox-1.30.1/networking/Kbuild.src
	modified:   tools/busybox-1.30.1/networking/arp.c
	modified:   tools/busybox-1.30.1/networking/arp.o
	modified:   tools/busybox-1.30.1/networking/arping.c
	modified:   tools/busybox-1.30.1/networking/arping.o
	modified:   tools/busybox-1.30.1/networking/brctl.c
	modified:   tools/busybox-1.30.1/networking/brctl.o
	modified:   tools/busybox-1.30.1/networking/built-in.o
	modified:   tools/busybox-1.30.1/networking/dnsd.c
	modified:   tools/busybox-1.30.1/networking/dnsd.o
	modified:   tools/busybox-1.30.1/networking/ether-wake.c
	modified:   tools/busybox-1.30.1/networking/ether-wake.o
	modified:   tools/busybox-1.30.1/networking/ftpd.c
	modified:   tools/busybox-1.30.1/networking/ftpd.o
	modified:   tools/busybox-1.30.1/networking/ftpgetput.c
	modified:   tools/busybox-1.30.1/networking/ftpgetput.o
	modified:   tools/busybox-1.30.1/networking/hostname.c
	modified:   tools/busybox-1.30.1/networking/hostname.o
	modified:   tools/busybox-1.30.1/networking/httpd.c
	modified:   tools/busybox-1.30.1/networking/httpd.o
	modified:   tools/busybox-1.30.1/networking/httpd_indexcgi.c
	modified:   tools/busybox-1.30.1/networking/httpd_ssi.c
	modified:   tools/busybox-1.30.1/networking/ifconfig.c
	modified:   tools/busybox-1.30.1/networking/ifconfig.o
	modified:   tools/busybox-1.30.1/networking/ifenslave.c
	modified:   tools/busybox-1.30.1/networking/ifenslave.o
	modified:   tools/busybox-1.30.1/networking/ifplugd.c
	modified:   tools/busybox-1.30.1/networking/ifplugd.o
	modified:   tools/busybox-1.30.1/networking/ifupdown.c
	modified:   tools/busybox-1.30.1/networking/ifupdown.o
	modified:   tools/busybox-1.30.1/networking/inetd.c
	modified:   tools/busybox-1.30.1/networking/inetd.o
	modified:   tools/busybox-1.30.1/networking/interface.c
	modified:   tools/busybox-1.30.1/networking/interface.o
	modified:   tools/busybox-1.30.1/networking/ip.c
	modified:   tools/busybox-1.30.1/networking/ip.o
	modified:   tools/busybox-1.30.1/networking/ipcalc.c
	modified:   tools/busybox-1.30.1/networking/ipcalc.o
	modified:   tools/busybox-1.30.1/networking/isrv.c
	modified:   tools/busybox-1.30.1/networking/isrv.h
	modified:   tools/busybox-1.30.1/networking/isrv.o
	modified:   tools/busybox-1.30.1/networking/isrv_identd.c
	modified:   tools/busybox-1.30.1/networking/isrv_identd.o
	modified:   tools/busybox-1.30.1/networking/lib.a
	modified:   tools/busybox-1.30.1/networking/libiproute/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.ip_parse_common_args.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.ipaddress.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.iplink.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.ipneigh.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.iproute.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.iprule.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.iptunnel.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.lib.a.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.libnetlink.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.ll_addr.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.ll_map.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.ll_proto.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.ll_types.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.rt_names.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.rtm_map.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/.utils.o.cmd
	modified:   tools/busybox-1.30.1/networking/libiproute/Kbuild
	modified:   tools/busybox-1.30.1/networking/libiproute/Kbuild.src
	modified:   tools/busybox-1.30.1/networking/libiproute/built-in.o
	modified:   tools/busybox-1.30.1/networking/libiproute/ip_common.h
	modified:   tools/busybox-1.30.1/networking/libiproute/ip_parse_common_args.c
	modified:   tools/busybox-1.30.1/networking/libiproute/ip_parse_common_args.o
	modified:   tools/busybox-1.30.1/networking/libiproute/ipaddress.c
	modified:   tools/busybox-1.30.1/networking/libiproute/ipaddress.o
	modified:   tools/busybox-1.30.1/networking/libiproute/iplink.c
	modified:   tools/busybox-1.30.1/networking/libiproute/iplink.o
	modified:   tools/busybox-1.30.1/networking/libiproute/ipneigh.c
	modified:   tools/busybox-1.30.1/networking/libiproute/ipneigh.o
	modified:   tools/busybox-1.30.1/networking/libiproute/iproute.c
	modified:   tools/busybox-1.30.1/networking/libiproute/iproute.o
	modified:   tools/busybox-1.30.1/networking/libiproute/iprule.c
	modified:   tools/busybox-1.30.1/networking/libiproute/iprule.o
	modified:   tools/busybox-1.30.1/networking/libiproute/iptunnel.c
	modified:   tools/busybox-1.30.1/networking/libiproute/iptunnel.o
	modified:   tools/busybox-1.30.1/networking/libiproute/lib.a
	modified:   tools/busybox-1.30.1/networking/libiproute/libnetlink.c
	modified:   tools/busybox-1.30.1/networking/libiproute/libnetlink.h
	modified:   tools/busybox-1.30.1/networking/libiproute/libnetlink.o
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_addr.c
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_addr.o
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_map.c
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_map.h
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_map.o
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_proto.c
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_proto.o
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_types.c
	modified:   tools/busybox-1.30.1/networking/libiproute/ll_types.o
	modified:   tools/busybox-1.30.1/networking/libiproute/rt_names.c
	modified:   tools/busybox-1.30.1/networking/libiproute/rt_names.h
	modified:   tools/busybox-1.30.1/networking/libiproute/rt_names.o
	modified:   tools/busybox-1.30.1/networking/libiproute/rtm_map.c
	modified:   tools/busybox-1.30.1/networking/libiproute/rtm_map.h
	modified:   tools/busybox-1.30.1/networking/libiproute/rtm_map.o
	modified:   tools/busybox-1.30.1/networking/libiproute/utils.c
	modified:   tools/busybox-1.30.1/networking/libiproute/utils.h
	modified:   tools/busybox-1.30.1/networking/libiproute/utils.o
	modified:   tools/busybox-1.30.1/networking/nameif.c
	modified:   tools/busybox-1.30.1/networking/nameif.o
	modified:   tools/busybox-1.30.1/networking/nbd-client.c
	modified:   tools/busybox-1.30.1/networking/nbd-client.o
	modified:   tools/busybox-1.30.1/networking/nc.c
	modified:   tools/busybox-1.30.1/networking/nc.o
	modified:   tools/busybox-1.30.1/networking/nc_bloaty.c
	modified:   tools/busybox-1.30.1/networking/netstat.c
	modified:   tools/busybox-1.30.1/networking/netstat.o
	modified:   tools/busybox-1.30.1/networking/nslookup.c
	modified:   tools/busybox-1.30.1/networking/nslookup.o
	modified:   tools/busybox-1.30.1/networking/ntpd.c
	modified:   tools/busybox-1.30.1/networking/ntpd.diff
	modified:   tools/busybox-1.30.1/networking/ntpd.o
	modified:   tools/busybox-1.30.1/networking/parse_pasv_epsv.c
	modified:   tools/busybox-1.30.1/networking/parse_pasv_epsv.o
	modified:   tools/busybox-1.30.1/networking/ping.c
	modified:   tools/busybox-1.30.1/networking/ping.o
	modified:   tools/busybox-1.30.1/networking/pscan.c
	modified:   tools/busybox-1.30.1/networking/pscan.o
	modified:   tools/busybox-1.30.1/networking/route.c
	modified:   tools/busybox-1.30.1/networking/route.o
	modified:   tools/busybox-1.30.1/networking/slattach.c
	modified:   tools/busybox-1.30.1/networking/slattach.o
	modified:   tools/busybox-1.30.1/networking/ssl_client.c
	modified:   tools/busybox-1.30.1/networking/ssl_client.o
	modified:   tools/busybox-1.30.1/networking/ssl_helper-wolfssl/README
	modified:   tools/busybox-1.30.1/networking/ssl_helper-wolfssl/ssl_helper.c
	modified:   tools/busybox-1.30.1/networking/ssl_helper/README
	modified:   tools/busybox-1.30.1/networking/ssl_helper/ssl_helper.c
	modified:   tools/busybox-1.30.1/networking/tc.c
	modified:   tools/busybox-1.30.1/networking/tc.o
	modified:   tools/busybox-1.30.1/networking/tcpudp.c
	modified:   tools/busybox-1.30.1/networking/tcpudp.o
	modified:   tools/busybox-1.30.1/networking/tcpudp_perhost.c
	modified:   tools/busybox-1.30.1/networking/tcpudp_perhost.h
	modified:   tools/busybox-1.30.1/networking/tcpudp_perhost.o
	modified:   tools/busybox-1.30.1/networking/telnet.c
	modified:   tools/busybox-1.30.1/networking/telnet.o
	modified:   tools/busybox-1.30.1/networking/telnetd.IAC_test.sh
	modified:   tools/busybox-1.30.1/networking/telnetd.c
	modified:   tools/busybox-1.30.1/networking/telnetd.ctrlSQ.patch
	modified:   tools/busybox-1.30.1/networking/telnetd.o
	modified:   tools/busybox-1.30.1/networking/tftp.c
	modified:   tools/busybox-1.30.1/networking/tftp.o
	modified:   tools/busybox-1.30.1/networking/tls.c
	modified:   tools/busybox-1.30.1/networking/tls.h
	modified:   tools/busybox-1.30.1/networking/tls.o
	modified:   tools/busybox-1.30.1/networking/tls_aes.c
	modified:   tools/busybox-1.30.1/networking/tls_aes.h
	modified:   tools/busybox-1.30.1/networking/tls_aes.o
	modified:   tools/busybox-1.30.1/networking/tls_aesgcm.c
	modified:   tools/busybox-1.30.1/networking/tls_aesgcm.h
	modified:   tools/busybox-1.30.1/networking/tls_aesgcm.o
	modified:   tools/busybox-1.30.1/networking/tls_fe.c
	modified:   tools/busybox-1.30.1/networking/tls_fe.h
	modified:   tools/busybox-1.30.1/networking/tls_fe.o
	modified:   tools/busybox-1.30.1/networking/tls_pstm.c
	modified:   tools/busybox-1.30.1/networking/tls_pstm.h
	modified:   tools/busybox-1.30.1/networking/tls_pstm.o
	modified:   tools/busybox-1.30.1/networking/tls_pstm_montgomery_reduce.c
	modified:   tools/busybox-1.30.1/networking/tls_pstm_montgomery_reduce.o
	modified:   tools/busybox-1.30.1/networking/tls_pstm_mul_comba.c
	modified:   tools/busybox-1.30.1/networking/tls_pstm_mul_comba.o
	modified:   tools/busybox-1.30.1/networking/tls_pstm_sqr_comba.c
	modified:   tools/busybox-1.30.1/networking/tls_pstm_sqr_comba.o
	modified:   tools/busybox-1.30.1/networking/tls_rsa.c
	modified:   tools/busybox-1.30.1/networking/tls_rsa.h
	modified:   tools/busybox-1.30.1/networking/tls_rsa.o
	modified:   tools/busybox-1.30.1/networking/tls_symmetric.h
	modified:   tools/busybox-1.30.1/networking/traceroute.c
	modified:   tools/busybox-1.30.1/networking/traceroute.o
	modified:   tools/busybox-1.30.1/networking/tunctl.c
	modified:   tools/busybox-1.30.1/networking/tunctl.o
	modified:   tools/busybox-1.30.1/networking/udhcp/.arpping.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.common.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.dhcpc.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.dhcpd.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.dhcprelay.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.domain_codec.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.dumpleases.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.lib.a.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.packet.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.signalpipe.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/.socket.o.cmd
	modified:   tools/busybox-1.30.1/networking/udhcp/Config.in
	modified:   tools/busybox-1.30.1/networking/udhcp/Config.src
	modified:   tools/busybox-1.30.1/networking/udhcp/Kbuild
	modified:   tools/busybox-1.30.1/networking/udhcp/Kbuild.src
	modified:   tools/busybox-1.30.1/networking/udhcp/arpping.c
	modified:   tools/busybox-1.30.1/networking/udhcp/arpping.o
	modified:   tools/busybox-1.30.1/networking/udhcp/built-in.o
	modified:   tools/busybox-1.30.1/networking/udhcp/common.c
	modified:   tools/busybox-1.30.1/networking/udhcp/common.h
	modified:   tools/busybox-1.30.1/networking/udhcp/common.o
	modified:   tools/busybox-1.30.1/networking/udhcp/d6_common.h
	modified:   tools/busybox-1.30.1/networking/udhcp/d6_dhcpc.c
	modified:   tools/busybox-1.30.1/networking/udhcp/d6_packet.c
	modified:   tools/busybox-1.30.1/networking/udhcp/d6_socket.c
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcpc.c
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcpc.h
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcpc.o
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcpd.c
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcpd.h
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcpd.o
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcprelay.c
	modified:   tools/busybox-1.30.1/networking/udhcp/dhcprelay.o
	modified:   tools/busybox-1.30.1/networking/udhcp/domain_codec.c
	modified:   tools/busybox-1.30.1/networking/udhcp/domain_codec.o
	modified:   tools/busybox-1.30.1/networking/udhcp/dumpleases.c
	modified:   tools/busybox-1.30.1/networking/udhcp/dumpleases.o
	modified:   tools/busybox-1.30.1/networking/udhcp/lib.a
	modified:   tools/busybox-1.30.1/networking/udhcp/packet.c
	modified:   tools/busybox-1.30.1/networking/udhcp/packet.o
	modified:   tools/busybox-1.30.1/networking/udhcp/signalpipe.c
	modified:   tools/busybox-1.30.1/networking/udhcp/signalpipe.o
	modified:   tools/busybox-1.30.1/networking/udhcp/socket.c
	modified:   tools/busybox-1.30.1/networking/udhcp/socket.o
	modified:   tools/busybox-1.30.1/networking/vconfig.c
	modified:   tools/busybox-1.30.1/networking/vconfig.o
	modified:   tools/busybox-1.30.1/networking/wget.c
	modified:   tools/busybox-1.30.1/networking/wget.o
	modified:   tools/busybox-1.30.1/networking/whois.c
	modified:   tools/busybox-1.30.1/networking/whois.o
	modified:   tools/busybox-1.30.1/networking/zcip.c
	modified:   tools/busybox-1.30.1/networking/zcip.o
	modified:   tools/busybox-1.30.1/printutils/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/printutils/.lib.a.cmd
	modified:   tools/busybox-1.30.1/printutils/.lpd.o.cmd
	modified:   tools/busybox-1.30.1/printutils/.lpr.o.cmd
	modified:   tools/busybox-1.30.1/printutils/Config.in
	modified:   tools/busybox-1.30.1/printutils/Config.src
	modified:   tools/busybox-1.30.1/printutils/Kbuild
	modified:   tools/busybox-1.30.1/printutils/Kbuild.src
	modified:   tools/busybox-1.30.1/printutils/built-in.o
	modified:   tools/busybox-1.30.1/printutils/lib.a
	modified:   tools/busybox-1.30.1/printutils/lpd.c
	modified:   tools/busybox-1.30.1/printutils/lpd.o
	modified:   tools/busybox-1.30.1/printutils/lpr.c
	modified:   tools/busybox-1.30.1/printutils/lpr.o
	modified:   tools/busybox-1.30.1/procps/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/procps/.free.o.cmd
	modified:   tools/busybox-1.30.1/procps/.fuser.o.cmd
	modified:   tools/busybox-1.30.1/procps/.iostat.o.cmd
	modified:   tools/busybox-1.30.1/procps/.kill.o.cmd
	modified:   tools/busybox-1.30.1/procps/.lib.a.cmd
	modified:   tools/busybox-1.30.1/procps/.lsof.o.cmd
	modified:   tools/busybox-1.30.1/procps/.mpstat.o.cmd
	modified:   tools/busybox-1.30.1/procps/.nmeter.o.cmd
	modified:   tools/busybox-1.30.1/procps/.pgrep.o.cmd
	modified:   tools/busybox-1.30.1/procps/.pidof.o.cmd
	modified:   tools/busybox-1.30.1/procps/.pmap.o.cmd
	modified:   tools/busybox-1.30.1/procps/.powertop.o.cmd
	modified:   tools/busybox-1.30.1/procps/.ps.o.cmd
	modified:   tools/busybox-1.30.1/procps/.pstree.o.cmd
	modified:   tools/busybox-1.30.1/procps/.pwdx.o.cmd
	modified:   tools/busybox-1.30.1/procps/.smemcap.o.cmd
	modified:   tools/busybox-1.30.1/procps/.sysctl.o.cmd
	modified:   tools/busybox-1.30.1/procps/.top.o.cmd
	modified:   tools/busybox-1.30.1/procps/.uptime.o.cmd
	modified:   tools/busybox-1.30.1/procps/.watch.o.cmd
	modified:   tools/busybox-1.30.1/procps/Config.in
	modified:   tools/busybox-1.30.1/procps/Config.src
	modified:   tools/busybox-1.30.1/procps/Kbuild
	modified:   tools/busybox-1.30.1/procps/Kbuild.src
	modified:   tools/busybox-1.30.1/procps/built-in.o
	modified:   tools/busybox-1.30.1/procps/free.c
	modified:   tools/busybox-1.30.1/procps/free.o
	modified:   tools/busybox-1.30.1/procps/fuser.c
	modified:   tools/busybox-1.30.1/procps/fuser.o
	modified:   tools/busybox-1.30.1/procps/iostat.c
	modified:   tools/busybox-1.30.1/procps/iostat.o
	modified:   tools/busybox-1.30.1/procps/kill.c
	modified:   tools/busybox-1.30.1/procps/kill.o
	modified:   tools/busybox-1.30.1/procps/lib.a
	modified:   tools/busybox-1.30.1/procps/lsof.c
	modified:   tools/busybox-1.30.1/procps/lsof.o
	modified:   tools/busybox-1.30.1/procps/mpstat.c
	modified:   tools/busybox-1.30.1/procps/mpstat.o
	modified:   tools/busybox-1.30.1/procps/nmeter.c
	modified:   tools/busybox-1.30.1/procps/nmeter.o
	modified:   tools/busybox-1.30.1/procps/pgrep.c
	modified:   tools/busybox-1.30.1/procps/pgrep.o
	modified:   tools/busybox-1.30.1/procps/pidof.c
	modified:   tools/busybox-1.30.1/procps/pidof.o
	modified:   tools/busybox-1.30.1/procps/pmap.c
	modified:   tools/busybox-1.30.1/procps/pmap.o
	modified:   tools/busybox-1.30.1/procps/powertop.c
	modified:   tools/busybox-1.30.1/procps/powertop.o
	modified:   tools/busybox-1.30.1/procps/ps.c
	modified:   tools/busybox-1.30.1/procps/ps.o
	modified:   tools/busybox-1.30.1/procps/ps.posix
	modified:   tools/busybox-1.30.1/procps/pstree.c
	modified:   tools/busybox-1.30.1/procps/pstree.o
	modified:   tools/busybox-1.30.1/procps/pwdx.c
	modified:   tools/busybox-1.30.1/procps/pwdx.o
	modified:   tools/busybox-1.30.1/procps/smemcap.c
	modified:   tools/busybox-1.30.1/procps/smemcap.o
	modified:   tools/busybox-1.30.1/procps/sysctl.c
	modified:   tools/busybox-1.30.1/procps/sysctl.o
	modified:   tools/busybox-1.30.1/procps/top.c
	modified:   tools/busybox-1.30.1/procps/top.o
	modified:   tools/busybox-1.30.1/procps/uptime.c
	modified:   tools/busybox-1.30.1/procps/uptime.o
	modified:   tools/busybox-1.30.1/procps/watch.c
	modified:   tools/busybox-1.30.1/procps/watch.o
	modified:   tools/busybox-1.30.1/qemu_multiarch_testing/README
	modified:   tools/busybox-1.30.1/runit/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/runit/.chpst.o.cmd
	modified:   tools/busybox-1.30.1/runit/.lib.a.cmd
	modified:   tools/busybox-1.30.1/runit/.runsv.o.cmd
	modified:   tools/busybox-1.30.1/runit/.runsvdir.o.cmd
	modified:   tools/busybox-1.30.1/runit/.sv.o.cmd
	modified:   tools/busybox-1.30.1/runit/.svlogd.o.cmd
	modified:   tools/busybox-1.30.1/runit/Config.in
	modified:   tools/busybox-1.30.1/runit/Config.src
	modified:   tools/busybox-1.30.1/runit/Kbuild
	modified:   tools/busybox-1.30.1/runit/Kbuild.src
	modified:   tools/busybox-1.30.1/runit/built-in.o
	modified:   tools/busybox-1.30.1/runit/chpst.c
	modified:   tools/busybox-1.30.1/runit/chpst.o
	modified:   tools/busybox-1.30.1/runit/lib.a
	modified:   tools/busybox-1.30.1/runit/runit_lib.h
	modified:   tools/busybox-1.30.1/runit/runsv.c
	modified:   tools/busybox-1.30.1/runit/runsv.o
	modified:   tools/busybox-1.30.1/runit/runsvdir.c
	modified:   tools/busybox-1.30.1/runit/runsvdir.o
	modified:   tools/busybox-1.30.1/runit/sv.c
	modified:   tools/busybox-1.30.1/runit/sv.o
	modified:   tools/busybox-1.30.1/runit/svlogd.c
	modified:   tools/busybox-1.30.1/runit/svlogd.o
	modified:   tools/busybox-1.30.1/scripts/Kbuild
	modified:   tools/busybox-1.30.1/scripts/Kbuild.include
	modified:   tools/busybox-1.30.1/scripts/Kbuild.src
	modified:   tools/busybox-1.30.1/scripts/Makefile.IMA
	modified:   tools/busybox-1.30.1/scripts/Makefile.build
	modified:   tools/busybox-1.30.1/scripts/Makefile.clean
	modified:   tools/busybox-1.30.1/scripts/Makefile.host
	modified:   tools/busybox-1.30.1/scripts/Makefile.lib
	modified:   tools/busybox-1.30.1/scripts/basic/.docproc.cmd
	modified:   tools/busybox-1.30.1/scripts/basic/.fixdep.cmd
	modified:   tools/busybox-1.30.1/scripts/basic/.split-include.cmd
	modified:   tools/busybox-1.30.1/scripts/basic/Makefile
	modified:   tools/busybox-1.30.1/scripts/basic/docproc.c
	modified:   tools/busybox-1.30.1/scripts/basic/fixdep.c
	modified:   tools/busybox-1.30.1/scripts/basic/split-include.c
	modified:   tools/busybox-1.30.1/scripts/echo.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/.conf.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/.kxgettext.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/.mconf.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/.mconf.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/.zconf.tab.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/Makefile
	modified:   tools/busybox-1.30.1/scripts/kconfig/POTFILES.in
	modified:   tools/busybox-1.30.1/scripts/kconfig/conf.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/conf.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/confdata.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/expr.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/expr.h
	modified:   tools/busybox-1.30.1/scripts/kconfig/gconf.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/gconf.glade
	modified:   tools/busybox-1.30.1/scripts/kconfig/images.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/kconfig_load.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/kxgettext.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/kxgettext.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lex.zconf.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lex.zconf.c_shipped
	modified:   tools/busybox-1.30.1/scripts/kconfig/lkc.h
	modified:   tools/busybox-1.30.1/scripts/kconfig/lkc_proto.h
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.checklist.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.inputbox.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.lxdialog.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.lxdialog.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.menubox.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.msgbox.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.textbox.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.util.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/.yesno.o.cmd
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/BIG.FAT.WARNING
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/Makefile
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/checklist.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/checklist.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/colors.h
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/dialog.h
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/inputbox.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/inputbox.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/lxdialog.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/lxdialog.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/menubox.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/menubox.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/msgbox.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/msgbox.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/textbox.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/textbox.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/util.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/util.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/yesno.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/lxdialog/yesno.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/mconf.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/mconf.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/menu.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/qconf.cc
	modified:   tools/busybox-1.30.1/scripts/kconfig/qconf.h
	modified:   tools/busybox-1.30.1/scripts/kconfig/symbol.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/util.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.gperf
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.hash.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.hash.c_shipped
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.l
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.tab.c
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.tab.c_shipped
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.tab.o
	modified:   tools/busybox-1.30.1/scripts/kconfig/zconf.y
	modified:   tools/busybox-1.30.1/scripts/test_setenv_leak.c
	modified:   tools/busybox-1.30.1/selinux/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/selinux/.lib.a.cmd
	modified:   tools/busybox-1.30.1/selinux/Config.in
	modified:   tools/busybox-1.30.1/selinux/Config.src
	modified:   tools/busybox-1.30.1/selinux/Kbuild
	modified:   tools/busybox-1.30.1/selinux/Kbuild.src
	modified:   tools/busybox-1.30.1/selinux/built-in.o
	modified:   tools/busybox-1.30.1/selinux/chcon.c
	modified:   tools/busybox-1.30.1/selinux/getenforce.c
	modified:   tools/busybox-1.30.1/selinux/getsebool.c
	modified:   tools/busybox-1.30.1/selinux/lib.a
	modified:   tools/busybox-1.30.1/selinux/load_policy.c
	modified:   tools/busybox-1.30.1/selinux/matchpathcon.c
	modified:   tools/busybox-1.30.1/selinux/runcon.c
	modified:   tools/busybox-1.30.1/selinux/selinuxenabled.c
	modified:   tools/busybox-1.30.1/selinux/sestatus.c
	modified:   tools/busybox-1.30.1/selinux/setenforce.c
	modified:   tools/busybox-1.30.1/selinux/setfiles.c
	modified:   tools/busybox-1.30.1/selinux/setsebool.c
	modified:   tools/busybox-1.30.1/shell/.ash.o.cmd
	modified:   tools/busybox-1.30.1/shell/.ash_ptr_hack.o.cmd
	modified:   tools/busybox-1.30.1/shell/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/shell/.cttyhack.o.cmd
	modified:   tools/busybox-1.30.1/shell/.hush.o.cmd
	modified:   tools/busybox-1.30.1/shell/.lib.a.cmd
	modified:   tools/busybox-1.30.1/shell/.match.o.cmd
	modified:   tools/busybox-1.30.1/shell/.math.o.cmd
	modified:   tools/busybox-1.30.1/shell/.random.o.cmd
	modified:   tools/busybox-1.30.1/shell/.shell_common.o.cmd
	modified:   tools/busybox-1.30.1/shell/Config.in
	modified:   tools/busybox-1.30.1/shell/Config.src
	modified:   tools/busybox-1.30.1/shell/Kbuild
	modified:   tools/busybox-1.30.1/shell/Kbuild.src
	modified:   tools/busybox-1.30.1/shell/README
	modified:   tools/busybox-1.30.1/shell/README.job
	modified:   tools/busybox-1.30.1/shell/ash.c
	modified:   tools/busybox-1.30.1/shell/ash.o
	modified:   tools/busybox-1.30.1/shell/ash_ptr_hack.c
	modified:   tools/busybox-1.30.1/shell/ash_ptr_hack.o
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-alias/alias.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-arith/README.ash
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-arith/arith-bash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-arith/arith-for.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-arith/arith-postinc.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-arith/arith.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-arith/arith_nested1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-getopts/getopt_nested.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-getopts/getopt_optarg.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-getopts/getopt_positional.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-getopts/getopt_silent.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-getopts/getopt_simple.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-getopts/getopt_test_libc_bug.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob_altvalue1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob_and_assign.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob_bkslash_in_var.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob_dir.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-glob/glob_redir.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc6.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc7.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc8.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc9.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredocA.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredocB.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_after_compound1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_backquote1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_backslash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_bkslash_newline1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_bkslash_newline2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_empty.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_empty2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_empty3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_huge.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-heredoc/heredoc_var_expand1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-invert/invert.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/and-or.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/assignment1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/assignment2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/assignment3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/assignment4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/assignment5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/break1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/break2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/break3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/break4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/break5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/builtin1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/case1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/colon.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/command.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/command2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/compound.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/continue1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/continue2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/continue3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/control_char1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/control_char2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/echo_write_error.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/empty_args.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/empty_for.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/empty_for1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/empty_for2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/env_and_func.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/errexit1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/eval1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/eval2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/exec.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/exit1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/exitcode1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/exitcode2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/exitcode_EACCES.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/exitcode_ENOENT.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/for.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/for_with_bslashes.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/for_with_keywords.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_args1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_bash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_compound1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_local1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_local2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_prio_over_builtins.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_return1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/func_return2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/group_in_braces.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/if_false_exitcode.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/last_amp.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/local1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/local2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/nommu1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/nommu2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/nommu3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/nulltick1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/opts1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/pid.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/pipefail.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/read.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/return1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/shift.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/shift1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/source1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/source2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/source3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/source5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/source_argv_and_shift.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/tickquote1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/unicode1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/until1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/wait4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/wait5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/wait6.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/while1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/while2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/while4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-misc/while_in_subshell.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/and_or_and_backgrounding.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/argv0.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/bkslash_eof1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/bkslash_newline1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/bkslash_newline2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/bkslash_newline3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/brace1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/brace2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/comment1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/comment2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/eol1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/escape1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/escape2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/escape3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/escape4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/escape5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/group1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/group2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/groups_and_keywords1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/groups_and_keywords2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/negate.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/noeol.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/noeol2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/noeol3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/process_subst.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/quote1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/quote2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/quote3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/quote4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/starquoted.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/starquoted2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-parsing/starquoted3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-psubst/emptytick.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-psubst/tick.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-psubst/tick2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-psubst/tick3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-psubst/tick4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-psubst/tick_huge.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/bkslash_case1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/bkslash_case2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/bkslash_in_varexp.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/bkslash_in_varexp1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/case_glob1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_altvalue1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_altvalue2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_altvalue9.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_repl_bash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_repl_slash_bash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_repl_slash_bash2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_squote_bash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/dollar_squote_bash2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/mode_x.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/quote_in_varexp1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/quoted_punct.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/squote_in_varexp.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/squote_in_varexp1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/squote_in_varexp2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/squote_in_varexp3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-quoting/unicode_8x_chars.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-read/read_REPLY.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-read/read_SIGCHLD.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-read/read_ifs.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-read/read_n.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-read/read_r.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-read/read_t.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-read/read_t0.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir6.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir7.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir8.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir9.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redirA.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_children_should_not_see_saved_fd_1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_children_should_not_see_saved_fd_2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_children_should_not_see_saved_fd_3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_escapednum.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_exec1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_expand.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_leak.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_multi.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_script.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_space.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_to_bad_fd.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_to_bad_fd255.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-redir/redir_to_bad_fd3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/catch.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/continue_and_trap1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/reap1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/return_in_trap1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/save-ret.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/savetrap.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/sigint1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal6.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal7.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal8.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal9.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/signal_read2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/sigquit_exec.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-signals/subshell.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-standalone/noexec_gets_no_env.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-standalone/nofork_env.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-standalone/nofork_trashes_getopt.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-standalone/var_standalone1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/empty.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/glob_and_vars.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_alt.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_alt2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_assign.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_bash_substring.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_default.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_indicate_error.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_len.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_expand_len1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_glob.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/param_subshell.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/readonly0.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/readonly1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/star.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/unset.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-do-not-collapse-arithmetic-expansion-at-parse-time.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-do-not-expand-tilde-in-parameter-expansion-in-quotes.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-do-not-quote-backslashes-in-parameter-expansions-outside-quotes.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-expand-tilde-in-parameter-expansion.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-pattern-replacement-in-parameter-expansion-1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-pattern-replacement-in-parameter-expansion-2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-pattern-replacement-in-parameter-expansion-3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-pattern-replacement-in-parameter-expansion-4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-pattern-replacement-in-parameter-expansion-5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-runtime-quote-detection.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var-utf8-length.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_LINENO1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash1a.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash1b.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash6.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash7.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash_pattern_starting_with_slash.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash_repl_empty_pattern.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_bash_repl_empty_var.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_expand_in_assign.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_expand_in_redir.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_expand_on_ifs.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_in_pipes.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_leak.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_leaks.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_posix1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_serial.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_subst_in_for.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_unbackslash.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_unbackslash1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_wordsplit_ifs1.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_wordsplit_ifs2.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_wordsplit_ifs3.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_wordsplit_ifs4.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-vars/var_wordsplit_ifs5.right
	modified:   tools/busybox-1.30.1/shell/ash_test/ash-z_slow/many_ifs.right
	modified:   tools/busybox-1.30.1/shell/ash_test/printenv.c
	modified:   tools/busybox-1.30.1/shell/ash_test/recho.c
	modified:   tools/busybox-1.30.1/shell/ash_test/zecho.c
	modified:   tools/busybox-1.30.1/shell/built-in.o
	modified:   tools/busybox-1.30.1/shell/cttyhack.c
	modified:   tools/busybox-1.30.1/shell/cttyhack.o
	modified:   tools/busybox-1.30.1/shell/hush.c
	modified:   tools/busybox-1.30.1/shell/hush.o
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-arith/arith-postinc.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-arith/arith.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-arith/arith_nested1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-bugs/export_exp.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-bugs/export_exp.tests.disabled
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-getopts/getopt_nested.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-getopts/getopt_optarg.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-getopts/getopt_positional.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-getopts/getopt_silent.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-getopts/getopt_simple.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-getopts/getopt_test_libc_bug.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/bash_brace1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob_altvalue1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob_and_assign.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob_bkslash_in_var.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob_dir.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-glob/glob_redir.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc6.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc7.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc8.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc9.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredocA.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredocB.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_after_compound1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_backslash1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_bkslash_newline1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_bkslash_newline2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_empty2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_empty3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_huge.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-heredoc/heredoc_var_expand1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-invert/invert.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-leak/leak_argv1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/and-or.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/assignment1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/assignment2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/assignment3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/assignment4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/assignment5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/break1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/break2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/break3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/break4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/break5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/builtin1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/case1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/colon.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/command2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/compound.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/continue1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/continue2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/continue3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/control_char1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/control_char2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/echo_write_error.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/empty_args.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/empty_for.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/empty_for1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/empty_for2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/env_and_func.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/errexit1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/eval1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/eval2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/exec.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/exit1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/exitcode1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/exitcode2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/exitcode_EACCES.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/exitcode_ENOENT.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/export-n.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/export.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/for.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/for_with_bslashes.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/for_with_keywords.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func_args1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func_local1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func_local2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func_prio_over_builtins.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func_return1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/func_return2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/group_in_braces.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/if_false_exitcode.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/last_amp.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/local1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/nommu1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/nommu2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/nommu3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/nulltick1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/opts1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/pid.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/pipefail.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/read.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/return1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/shift.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/shift1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/sig_exitcode.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/source1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/source2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/source3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/source4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/source5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/source_argv_and_shift.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/syntax_err.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/syntax_err_negate.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/tickquote1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/unicode1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/until1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/wait1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/wait2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/wait3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/wait4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/wait5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/wait6.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/while1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/while2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/while3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/while4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-misc/while_in_subshell.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/and_or_and_backgrounding.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/argv0.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/bkslash_eof1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/bkslash_eof2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/bkslash_newline1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/bkslash_newline2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/bkslash_newline3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/brace1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/brace2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/comment1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/comment2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/eol1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/escape1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/escape2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/escape3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/escape4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/escape5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/group1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/group2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/groups_and_keywords1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/groups_and_keywords2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/negate.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/noeol.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/noeol2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/noeol3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/process_subst.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/quote1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/quote2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/quote3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/quote4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/starquoted.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/starquoted2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-parsing/starquoted3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/emptytick.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/falsetick.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/falsetick2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/tick.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/tick2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/tick3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/tick4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/tick5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-psubst/tick_huge.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/bkslash_case1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/bkslash_case2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/bkslash_in_varexp.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/bkslash_in_varexp1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/case_glob1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/dollar_altvalue1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/dollar_altvalue2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/dollar_altvalue9.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/dollar_repl_bash1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/dollar_repl_slash_bash1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/dollar_repl_slash_bash2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/quote_in_varexp1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/quoted_punct.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/squote_in_varexp.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/squote_in_varexp1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/squote_in_varexp2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/squote_in_varexp3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-quoting/unicode_8x_chars.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_REPLY.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_SIGCHLD.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_ifs.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_ifs2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_n.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_r.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_t.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-read/read_t0.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir6.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir7.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir8.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir9.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redirA.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_backquote1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_children_should_not_see_saved_fd_1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_children_should_not_see_saved_fd_2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_children_should_not_see_saved_fd_3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_errors.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_escapednum.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_exec1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_expand.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_leak.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_multi.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_script.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_space.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_to_bad_fd.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_to_bad_fd255.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-redir/redir_to_bad_fd3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/catch.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/continue_and_trap1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/exit.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/reap1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/return_in_trap1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/save-ret.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/savetrap.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/sigint1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal6.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal7.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal8.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal9.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal_read1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/signal_read2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/sigquit_exec.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/subshell.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-signals/usage.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-standalone/noexec_gets_no_env.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-standalone/nofork_env.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-standalone/nofork_trashes_getopt.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-standalone/var_standalone1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/empty.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/glob_and_vars.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_alt.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_alt2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_assign.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_bash_substring.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_default.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_indicate_error.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_len.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_expand_len1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_glob.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/param_subshell.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/readonly0.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/readonly2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/readonly3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/star.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/unset.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-do-not-collapse-arithmetic-expansion-at-parse-time.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-do-not-expand-tilde-in-parameter-expansion-in-quotes.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-do-not-quote-backslashes-in-parameter-expansions-outside-quotes.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-pattern-replacement-in-parameter-expansion-1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-pattern-replacement-in-parameter-expansion-2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-pattern-replacement-in-parameter-expansion-3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-pattern-replacement-in-parameter-expansion-4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-pattern-replacement-in-parameter-expansion-5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-runtime-quote-detection.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var-utf8-length.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var6.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_LINENO1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash1a.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash1b.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash6.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash_pattern_starting_with_slash.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash_repl_empty_pattern.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_bash_repl_empty_var.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_expand_in_assign.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_expand_in_redir.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_expand_on_ifs.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_in_pipes.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_leaks.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_nested1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_nested2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_posix1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_preserved.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_serial.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_subst_in_for.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_unbackslash.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_unbackslash1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_wordsplit_ifs1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_wordsplit_ifs2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_wordsplit_ifs3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_wordsplit_ifs4.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-vars/var_wordsplit_ifs5.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/leak_all1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/leak_all2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/leak_empty_tick.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/leak_heredoc1.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/leak_var.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/leak_var2.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/leak_var3.right
	modified:   tools/busybox-1.30.1/shell/hush_test/hush-z_slow/many_ifs.right
	modified:   tools/busybox-1.30.1/shell/lib.a
	modified:   tools/busybox-1.30.1/shell/match.c
	modified:   tools/busybox-1.30.1/shell/match.h
	modified:   tools/busybox-1.30.1/shell/match.o
	modified:   tools/busybox-1.30.1/shell/math.c
	modified:   tools/busybox-1.30.1/shell/math.h
	modified:   tools/busybox-1.30.1/shell/math.o
	modified:   tools/busybox-1.30.1/shell/random.c
	modified:   tools/busybox-1.30.1/shell/random.h
	modified:   tools/busybox-1.30.1/shell/random.o
	modified:   tools/busybox-1.30.1/shell/shell_common.c
	modified:   tools/busybox-1.30.1/shell/shell_common.h
	modified:   tools/busybox-1.30.1/shell/shell_common.o
	modified:   tools/busybox-1.30.1/sysklogd/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/sysklogd/.klogd.o.cmd
	modified:   tools/busybox-1.30.1/sysklogd/.lib.a.cmd
	modified:   tools/busybox-1.30.1/sysklogd/.logread.o.cmd
	modified:   tools/busybox-1.30.1/sysklogd/.syslogd_and_logger.o.cmd
	modified:   tools/busybox-1.30.1/sysklogd/Config.in
	modified:   tools/busybox-1.30.1/sysklogd/Config.src
	modified:   tools/busybox-1.30.1/sysklogd/Kbuild
	modified:   tools/busybox-1.30.1/sysklogd/Kbuild.src
	modified:   tools/busybox-1.30.1/sysklogd/built-in.o
	modified:   tools/busybox-1.30.1/sysklogd/klogd.c
	modified:   tools/busybox-1.30.1/sysklogd/klogd.o
	modified:   tools/busybox-1.30.1/sysklogd/lib.a
	modified:   tools/busybox-1.30.1/sysklogd/logger.c
	modified:   tools/busybox-1.30.1/sysklogd/logread.c
	modified:   tools/busybox-1.30.1/sysklogd/logread.o
	modified:   tools/busybox-1.30.1/sysklogd/syslogd.c
	modified:   tools/busybox-1.30.1/sysklogd/syslogd_and_logger.c
	modified:   tools/busybox-1.30.1/sysklogd/syslogd_and_logger.o
	modified:   tools/busybox-1.30.1/testsuite/README
	modified:   tools/busybox-1.30.1/testsuite/TODO
	modified:   tools/busybox-1.30.1/testsuite/awk_t1.tar.bz2
	modified:   tools/busybox-1.30.1/testsuite/basename/basename-does-not-remove-identical-extension
	modified:   tools/busybox-1.30.1/testsuite/basename/basename-works
	modified:   tools/busybox-1.30.1/testsuite/bc_add.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_arctangent.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_array.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_arrays.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_bessel.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_boolean.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_cosine.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_decimal.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_divide.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_exponent.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_log.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_misc.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_misc1.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_misc2.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_modulus.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_multiply.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_numbers1.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_numbers2.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_pi.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_power.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_references.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_sine.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_sqrt.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_strings.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_subtract.bc
	modified:   tools/busybox-1.30.1/testsuite/bc_vars.bc
	modified:   tools/busybox-1.30.1/testsuite/bunzip2/bunzip2-reads-from-standard-input
	modified:   tools/busybox-1.30.1/testsuite/bunzip2/bunzip2-removes-compressed-file
	modified:   tools/busybox-1.30.1/testsuite/bz2_issue_11.bz2
	modified:   tools/busybox-1.30.1/testsuite/bz2_issue_12.bz2
	modified:   tools/busybox-1.30.1/testsuite/bzcat/bzcat-does-not-remove-compressed-file
	modified:   tools/busybox-1.30.1/testsuite/cat/cat-prints-a-file
	modified:   tools/busybox-1.30.1/testsuite/cat/cat-prints-a-file-and-standard-input
	modified:   tools/busybox-1.30.1/testsuite/cmp/cmp-detects-difference
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-RHL-does_not_preserve-links
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-a-files-to-dir
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-a-preserves-links
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-copies-empty-file
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-copies-large-file
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-copies-small-file
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-d-files-to-dir
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-dev-file
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-dir-create-dir
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-dir-existing-dir
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-does-not-copy-unreadable-file
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-files-to-dir
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-follows-links
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-parents
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-preserves-hard-links
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-preserves-links
	modified:   tools/busybox-1.30.1/testsuite/cp/cp-preserves-source-file
	modified:   tools/busybox-1.30.1/testsuite/cut/cut-cuts-a-character
	modified:   tools/busybox-1.30.1/testsuite/cut/cut-cuts-a-closed-range
	modified:   tools/busybox-1.30.1/testsuite/cut/cut-cuts-a-field
	modified:   tools/busybox-1.30.1/testsuite/cut/cut-cuts-an-open-range
	modified:   tools/busybox-1.30.1/testsuite/cut/cut-cuts-an-unclosed-range
	modified:   tools/busybox-1.30.1/testsuite/date/date-@-works
	modified:   tools/busybox-1.30.1/testsuite/date/date-R-works
	modified:   tools/busybox-1.30.1/testsuite/date/date-format-works
	modified:   tools/busybox-1.30.1/testsuite/date/date-u-works
	modified:   tools/busybox-1.30.1/testsuite/date/date-works
	modified:   tools/busybox-1.30.1/testsuite/date/date-works-1
	modified:   tools/busybox-1.30.1/testsuite/dc_add.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_boolean.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_decimal.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_divide.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_divmod.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_misc.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_modexp.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_modulus.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_multiply.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_power.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_sqrt.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_strings.dc
	modified:   tools/busybox-1.30.1/testsuite/dc_subtract.dc
	modified:   tools/busybox-1.30.1/testsuite/dcx_vars.dc
	modified:   tools/busybox-1.30.1/testsuite/dd/dd-accepts-if
	modified:   tools/busybox-1.30.1/testsuite/dd/dd-accepts-of
	modified:   tools/busybox-1.30.1/testsuite/dd/dd-copies-from-standard-input-to-standard-output
	modified:   tools/busybox-1.30.1/testsuite/dd/dd-prints-count-to-standard-error
	modified:   tools/busybox-1.30.1/testsuite/dd/dd-reports-write-errors
	modified:   tools/busybox-1.30.1/testsuite/dirname/dirname-handles-absolute-path
	modified:   tools/busybox-1.30.1/testsuite/dirname/dirname-handles-empty-path
	modified:   tools/busybox-1.30.1/testsuite/dirname/dirname-handles-multiple-slashes
	modified:   tools/busybox-1.30.1/testsuite/dirname/dirname-handles-relative-path
	modified:   tools/busybox-1.30.1/testsuite/dirname/dirname-handles-root
	modified:   tools/busybox-1.30.1/testsuite/dirname/dirname-handles-single-component
	modified:   tools/busybox-1.30.1/testsuite/dirname/dirname-works
	modified:   tools/busybox-1.30.1/testsuite/du/du-h-works
	modified:   tools/busybox-1.30.1/testsuite/du/du-k-works
	modified:   tools/busybox-1.30.1/testsuite/du/du-l-works
	modified:   tools/busybox-1.30.1/testsuite/du/du-m-works
	modified:   tools/busybox-1.30.1/testsuite/du/du-s-works
	modified:   tools/busybox-1.30.1/testsuite/du/du-works
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-does-not-print-newline
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-argument
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-arguments
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-dash
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-newline
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-non-opts
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-slash-zero
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-slash_00041
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-slash_0041
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-slash_041
	modified:   tools/busybox-1.30.1/testsuite/echo/echo-prints-slash_41
	modified:   tools/busybox-1.30.1/testsuite/expand/expand-works-like-GNU
	modified:   tools/busybox-1.30.1/testsuite/expr/expr-big
	modified:   tools/busybox-1.30.1/testsuite/expr/expr-works
	modified:   tools/busybox-1.30.1/testsuite/false/false-is-silent
	modified:   tools/busybox-1.30.1/testsuite/false/false-returns-failure
	modified:   tools/busybox-1.30.1/testsuite/find/find-supports-minus-xdev
	modified:   tools/busybox-1.30.1/testsuite/gunzip/gunzip-reads-from-standard-input
	modified:   tools/busybox-1.30.1/testsuite/gzip/gzip-accepts-multiple-files
	modified:   tools/busybox-1.30.1/testsuite/gzip/gzip-accepts-single-minus
	modified:   tools/busybox-1.30.1/testsuite/gzip/gzip-compression-levels
	modified:   tools/busybox-1.30.1/testsuite/gzip/gzip-removes-original-file
	modified:   tools/busybox-1.30.1/testsuite/hostid/hostid-works
	modified:   tools/busybox-1.30.1/testsuite/hostname/hostname-d-works
	modified:   tools/busybox-1.30.1/testsuite/hostname/hostname-i-works
	modified:   tools/busybox-1.30.1/testsuite/hostname/hostname-s-works
	modified:   tools/busybox-1.30.1/testsuite/hostname/hostname-works
	modified:   tools/busybox-1.30.1/testsuite/id/id-g-works
	modified:   tools/busybox-1.30.1/testsuite/id/id-u-works
	modified:   tools/busybox-1.30.1/testsuite/id/id-un-works
	modified:   tools/busybox-1.30.1/testsuite/id/id-ur-works
	modified:   tools/busybox-1.30.1/testsuite/ln/ln-creates-hard-links
	modified:   tools/busybox-1.30.1/testsuite/ln/ln-creates-soft-links
	modified:   tools/busybox-1.30.1/testsuite/ln/ln-force-creates-hard-links
	modified:   tools/busybox-1.30.1/testsuite/ln/ln-force-creates-soft-links
	modified:   tools/busybox-1.30.1/testsuite/ln/ln-preserves-hard-links
	modified:   tools/busybox-1.30.1/testsuite/ln/ln-preserves-soft-links
	modified:   tools/busybox-1.30.1/testsuite/ls.mk_uni_tests
	modified:   tools/busybox-1.30.1/testsuite/ls/ls-1-works
	modified:   tools/busybox-1.30.1/testsuite/ls/ls-h-works
	modified:   tools/busybox-1.30.1/testsuite/ls/ls-l-works
	modified:   tools/busybox-1.30.1/testsuite/ls/ls-s-works
	modified:   tools/busybox-1.30.1/testsuite/md5sum/md5sum-verifies-non-binary-file
	modified:   tools/busybox-1.30.1/testsuite/mkdir/mkdir-makes-a-directory
	modified:   tools/busybox-1.30.1/testsuite/mkdir/mkdir-makes-parent-directories
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-files-to-dir
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-follows-links
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-moves-empty-file
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-moves-file
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-moves-hardlinks
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-moves-large-file
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-moves-small-file
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-moves-symlinks
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-moves-unreadable-files
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-preserves-hard-links
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-preserves-links
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-refuses-mv-dir-to-subdir
	modified:   tools/busybox-1.30.1/testsuite/mv/mv-removes-source-file
	modified:   tools/busybox-1.30.1/testsuite/paste/paste
	modified:   tools/busybox-1.30.1/testsuite/paste/paste-back-cuted-lines
	modified:   tools/busybox-1.30.1/testsuite/paste/paste-multi-stdin
	modified:   tools/busybox-1.30.1/testsuite/paste/paste-pairs
	modified:   tools/busybox-1.30.1/testsuite/paste/paste-separate
	modified:   tools/busybox-1.30.1/testsuite/pwd/pwd-prints-working-directory
	modified:   tools/busybox-1.30.1/testsuite/rm/rm-removes-file
	modified:   tools/busybox-1.30.1/testsuite/rmdir/rmdir-removes-parent-directories
	modified:   tools/busybox-1.30.1/testsuite/strings/strings-works-like-GNU
	modified:   tools/busybox-1.30.1/testsuite/tail/tail-n-works
	modified:   tools/busybox-1.30.1/testsuite/tail/tail-works
	modified:   tools/busybox-1.30.1/testsuite/tar.utf8.tar.bz2
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-archives-multiple-files
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-complains-about-missing-file
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-demands-at-least-one-ctx
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-demands-at-most-one-ctx
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-extracts-all-subdirs
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-extracts-file
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-extracts-from-standard-input
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-extracts-multiple-files
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-extracts-to-standard-output
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-handles-cz-options
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-handles-empty-include-and-non-empty-exclude-list
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-handles-exclude-and-extract-lists
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-handles-multiple-X-options
	modified:   tools/busybox-1.30.1/testsuite/tar/tar-handles-nested-exclude
	modified:   tools/busybox-1.30.1/testsuite/tar/tar_with_link_with_size
	modified:   tools/busybox-1.30.1/testsuite/tar/tar_with_prefix_fields
	modified:   tools/busybox-1.30.1/testsuite/tee/tee-appends-input
	modified:   tools/busybox-1.30.1/testsuite/tee/tee-tees-input
	modified:   tools/busybox-1.30.1/testsuite/testing.sh
	modified:   tools/busybox-1.30.1/testsuite/touch/touch-creates-file
	modified:   tools/busybox-1.30.1/testsuite/touch/touch-does-not-create-file
	modified:   tools/busybox-1.30.1/testsuite/touch/touch-touches-files-after-non-existent-file
	modified:   tools/busybox-1.30.1/testsuite/tr/tr-d-alnum-works
	modified:   tools/busybox-1.30.1/testsuite/tr/tr-d-works
	modified:   tools/busybox-1.30.1/testsuite/tr/tr-non-gnu
	modified:   tools/busybox-1.30.1/testsuite/tr/tr-rejects-wrong-class
	modified:   tools/busybox-1.30.1/testsuite/tr/tr-works
	modified:   tools/busybox-1.30.1/testsuite/true/true-is-silent
	modified:   tools/busybox-1.30.1/testsuite/true/true-returns-success
	modified:   tools/busybox-1.30.1/testsuite/unexpand/unexpand-works-like-GNU
	modified:   tools/busybox-1.30.1/testsuite/unlzma_issue_1.lzma
	modified:   tools/busybox-1.30.1/testsuite/unlzma_issue_2.lzma
	modified:   tools/busybox-1.30.1/testsuite/unzip_bad_lzma_1.zip
	modified:   tools/busybox-1.30.1/testsuite/unzip_bad_lzma_2.zip
	modified:   tools/busybox-1.30.1/testsuite/uptime/uptime-works
	modified:   tools/busybox-1.30.1/testsuite/wc/wc-counts-all
	modified:   tools/busybox-1.30.1/testsuite/wc/wc-counts-characters
	modified:   tools/busybox-1.30.1/testsuite/wc/wc-counts-lines
	modified:   tools/busybox-1.30.1/testsuite/wc/wc-counts-words
	modified:   tools/busybox-1.30.1/testsuite/wc/wc-prints-longest-line-length
	modified:   tools/busybox-1.30.1/testsuite/wget/wget--O-overrides--P
	modified:   tools/busybox-1.30.1/testsuite/wget/wget-handles-empty-path
	modified:   tools/busybox-1.30.1/testsuite/wget/wget-retrieves-google-index
	modified:   tools/busybox-1.30.1/testsuite/wget/wget-supports--P
	modified:   tools/busybox-1.30.1/testsuite/which/which-uses-default-path
	modified:   tools/busybox-1.30.1/testsuite/xargs/xargs-works
	modified:   tools/busybox-1.30.1/util-linux/.acpid.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.blkdiscard.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.blkid.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.blockdev.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.cal.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.chrt.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.dmesg.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.eject.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fallocate.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fatattr.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fbset.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fdformat.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fdisk.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.findfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.flock.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.freeramdisk.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fsck_minix.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fsfreeze.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.fstrim.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.getopt.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.hexdump.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.hexdump_xxd.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.hwclock.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.ionice.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.ipcrm.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.ipcs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.last_fancy.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.lib.a.cmd
	modified:   tools/busybox-1.30.1/util-linux/.losetup.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.lspci.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.lsusb.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mdev.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mesg.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mkfs_ext2.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mkfs_minix.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mkfs_vfat.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mkswap.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.more.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mount.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.mountpoint.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.nsenter.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.pivot_root.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.rdate.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.rdev.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.readprofile.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.renice.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.rev.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.rtcwake.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.script.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.scriptreplay.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.setarch.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.setpriv.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.setsid.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.swaponoff.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.switch_root.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.taskset.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.uevent.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.umount.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.unshare.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/.wall.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/Config.in
	modified:   tools/busybox-1.30.1/util-linux/Config.src
	modified:   tools/busybox-1.30.1/util-linux/Kbuild
	modified:   tools/busybox-1.30.1/util-linux/Kbuild.src
	modified:   tools/busybox-1.30.1/util-linux/acpid.c
	modified:   tools/busybox-1.30.1/util-linux/acpid.o
	modified:   tools/busybox-1.30.1/util-linux/blkdiscard.c
	modified:   tools/busybox-1.30.1/util-linux/blkdiscard.o
	modified:   tools/busybox-1.30.1/util-linux/blkid.c
	modified:   tools/busybox-1.30.1/util-linux/blkid.o
	modified:   tools/busybox-1.30.1/util-linux/blockdev.c
	modified:   tools/busybox-1.30.1/util-linux/blockdev.o
	modified:   tools/busybox-1.30.1/util-linux/built-in.o
	modified:   tools/busybox-1.30.1/util-linux/cal.c
	modified:   tools/busybox-1.30.1/util-linux/cal.o
	modified:   tools/busybox-1.30.1/util-linux/chrt.c
	modified:   tools/busybox-1.30.1/util-linux/chrt.o
	modified:   tools/busybox-1.30.1/util-linux/dmesg.c
	modified:   tools/busybox-1.30.1/util-linux/dmesg.o
	modified:   tools/busybox-1.30.1/util-linux/eject.c
	modified:   tools/busybox-1.30.1/util-linux/eject.o
	modified:   tools/busybox-1.30.1/util-linux/fallocate.c
	modified:   tools/busybox-1.30.1/util-linux/fallocate.o
	modified:   tools/busybox-1.30.1/util-linux/fatattr.c
	modified:   tools/busybox-1.30.1/util-linux/fatattr.o
	modified:   tools/busybox-1.30.1/util-linux/fbset.c
	modified:   tools/busybox-1.30.1/util-linux/fbset.o
	modified:   tools/busybox-1.30.1/util-linux/fdformat.c
	modified:   tools/busybox-1.30.1/util-linux/fdformat.o
	modified:   tools/busybox-1.30.1/util-linux/fdisk.c
	modified:   tools/busybox-1.30.1/util-linux/fdisk.o
	modified:   tools/busybox-1.30.1/util-linux/fdisk_aix.c
	modified:   tools/busybox-1.30.1/util-linux/fdisk_gpt.c
	modified:   tools/busybox-1.30.1/util-linux/fdisk_osf.c
	modified:   tools/busybox-1.30.1/util-linux/fdisk_sgi.c
	modified:   tools/busybox-1.30.1/util-linux/fdisk_sun.c
	modified:   tools/busybox-1.30.1/util-linux/findfs.c
	modified:   tools/busybox-1.30.1/util-linux/findfs.o
	modified:   tools/busybox-1.30.1/util-linux/flock.c
	modified:   tools/busybox-1.30.1/util-linux/flock.o
	modified:   tools/busybox-1.30.1/util-linux/freeramdisk.c
	modified:   tools/busybox-1.30.1/util-linux/freeramdisk.o
	modified:   tools/busybox-1.30.1/util-linux/fsck_minix.c
	modified:   tools/busybox-1.30.1/util-linux/fsck_minix.o
	modified:   tools/busybox-1.30.1/util-linux/fsfreeze.c
	modified:   tools/busybox-1.30.1/util-linux/fsfreeze.o
	modified:   tools/busybox-1.30.1/util-linux/fstrim.c
	modified:   tools/busybox-1.30.1/util-linux/fstrim.o
	modified:   tools/busybox-1.30.1/util-linux/getopt.c
	modified:   tools/busybox-1.30.1/util-linux/getopt.o
	modified:   tools/busybox-1.30.1/util-linux/hexdump.c
	modified:   tools/busybox-1.30.1/util-linux/hexdump.o
	modified:   tools/busybox-1.30.1/util-linux/hexdump_xxd.c
	modified:   tools/busybox-1.30.1/util-linux/hexdump_xxd.o
	modified:   tools/busybox-1.30.1/util-linux/hwclock.c
	modified:   tools/busybox-1.30.1/util-linux/hwclock.o
	modified:   tools/busybox-1.30.1/util-linux/ionice.c
	modified:   tools/busybox-1.30.1/util-linux/ionice.o
	modified:   tools/busybox-1.30.1/util-linux/ipcrm.c
	modified:   tools/busybox-1.30.1/util-linux/ipcrm.o
	modified:   tools/busybox-1.30.1/util-linux/ipcs.c
	modified:   tools/busybox-1.30.1/util-linux/ipcs.o
	modified:   tools/busybox-1.30.1/util-linux/last.c
	modified:   tools/busybox-1.30.1/util-linux/last_fancy.c
	modified:   tools/busybox-1.30.1/util-linux/last_fancy.o
	modified:   tools/busybox-1.30.1/util-linux/lib.a
	modified:   tools/busybox-1.30.1/util-linux/losetup.c
	modified:   tools/busybox-1.30.1/util-linux/losetup.o
	modified:   tools/busybox-1.30.1/util-linux/lspci.c
	modified:   tools/busybox-1.30.1/util-linux/lspci.o
	modified:   tools/busybox-1.30.1/util-linux/lsusb.c
	modified:   tools/busybox-1.30.1/util-linux/lsusb.o
	modified:   tools/busybox-1.30.1/util-linux/mdev.c
	modified:   tools/busybox-1.30.1/util-linux/mdev.o
	modified:   tools/busybox-1.30.1/util-linux/mesg.c
	modified:   tools/busybox-1.30.1/util-linux/mesg.o
	modified:   tools/busybox-1.30.1/util-linux/minix.h
	modified:   tools/busybox-1.30.1/util-linux/mkfs_ext2.c
	modified:   tools/busybox-1.30.1/util-linux/mkfs_ext2.o
	modified:   tools/busybox-1.30.1/util-linux/mkfs_minix.c
	modified:   tools/busybox-1.30.1/util-linux/mkfs_minix.o
	modified:   tools/busybox-1.30.1/util-linux/mkfs_reiser.c
	modified:   tools/busybox-1.30.1/util-linux/mkfs_vfat.c
	modified:   tools/busybox-1.30.1/util-linux/mkfs_vfat.o
	modified:   tools/busybox-1.30.1/util-linux/mkswap.c
	modified:   tools/busybox-1.30.1/util-linux/mkswap.o
	modified:   tools/busybox-1.30.1/util-linux/more.c
	modified:   tools/busybox-1.30.1/util-linux/more.o
	modified:   tools/busybox-1.30.1/util-linux/mount.c
	modified:   tools/busybox-1.30.1/util-linux/mount.o
	modified:   tools/busybox-1.30.1/util-linux/mountpoint.c
	modified:   tools/busybox-1.30.1/util-linux/mountpoint.o
	modified:   tools/busybox-1.30.1/util-linux/nologin.c
	modified:   tools/busybox-1.30.1/util-linux/nsenter.c
	modified:   tools/busybox-1.30.1/util-linux/nsenter.o
	modified:   tools/busybox-1.30.1/util-linux/pivot_root.c
	modified:   tools/busybox-1.30.1/util-linux/pivot_root.o
	modified:   tools/busybox-1.30.1/util-linux/rdate.c
	modified:   tools/busybox-1.30.1/util-linux/rdate.o
	modified:   tools/busybox-1.30.1/util-linux/rdev.c
	modified:   tools/busybox-1.30.1/util-linux/rdev.o
	modified:   tools/busybox-1.30.1/util-linux/readprofile.c
	modified:   tools/busybox-1.30.1/util-linux/readprofile.o
	modified:   tools/busybox-1.30.1/util-linux/renice.c
	modified:   tools/busybox-1.30.1/util-linux/renice.o
	modified:   tools/busybox-1.30.1/util-linux/rev.c
	modified:   tools/busybox-1.30.1/util-linux/rev.o
	modified:   tools/busybox-1.30.1/util-linux/rtcwake.c
	modified:   tools/busybox-1.30.1/util-linux/rtcwake.o
	modified:   tools/busybox-1.30.1/util-linux/script.c
	modified:   tools/busybox-1.30.1/util-linux/script.o
	modified:   tools/busybox-1.30.1/util-linux/scriptreplay.c
	modified:   tools/busybox-1.30.1/util-linux/scriptreplay.o
	modified:   tools/busybox-1.30.1/util-linux/setarch.c
	modified:   tools/busybox-1.30.1/util-linux/setarch.o
	modified:   tools/busybox-1.30.1/util-linux/setpriv.c
	modified:   tools/busybox-1.30.1/util-linux/setpriv.o
	modified:   tools/busybox-1.30.1/util-linux/setsid.c
	modified:   tools/busybox-1.30.1/util-linux/setsid.o
	modified:   tools/busybox-1.30.1/util-linux/swaponoff.c
	modified:   tools/busybox-1.30.1/util-linux/swaponoff.o
	modified:   tools/busybox-1.30.1/util-linux/switch_root.c
	modified:   tools/busybox-1.30.1/util-linux/switch_root.o
	modified:   tools/busybox-1.30.1/util-linux/taskset.c
	modified:   tools/busybox-1.30.1/util-linux/taskset.o
	modified:   tools/busybox-1.30.1/util-linux/uevent.c
	modified:   tools/busybox-1.30.1/util-linux/uevent.o
	modified:   tools/busybox-1.30.1/util-linux/umount.c
	modified:   tools/busybox-1.30.1/util-linux/umount.o
	modified:   tools/busybox-1.30.1/util-linux/unshare.c
	modified:   tools/busybox-1.30.1/util-linux/unshare.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.bcache.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.btrfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.built-in.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.cramfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.exfat.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.ext.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.f2fs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.fat.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.get_devname.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.hfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.iso9660.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.jfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.lfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.lib.a.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.linux_raid.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.linux_swap.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.luks.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.minix.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.nilfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.ntfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.ocfs2.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.reiserfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.romfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.squashfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.sysv.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.ubifs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.udf.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.util.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.volume_id.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/.xfs.o.cmd
	modified:   tools/busybox-1.30.1/util-linux/volume_id/Config.in
	modified:   tools/busybox-1.30.1/util-linux/volume_id/Config.src
	modified:   tools/busybox-1.30.1/util-linux/volume_id/Kbuild
	modified:   tools/busybox-1.30.1/util-linux/volume_id/Kbuild.src
	modified:   tools/busybox-1.30.1/util-linux/volume_id/bcache.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/bcache.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/btrfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/btrfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/built-in.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/cramfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/cramfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/exfat.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/exfat.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ext.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ext.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/f2fs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/f2fs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/fat.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/fat.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/get_devname.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/get_devname.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/hfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/hfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/iso9660.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/iso9660.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/jfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/jfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/lfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/lfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/lib.a
	modified:   tools/busybox-1.30.1/util-linux/volume_id/linux_raid.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/linux_raid.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/linux_swap.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/linux_swap.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/luks.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/luks.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/minix.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/minix.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/nilfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/nilfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ntfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ntfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ocfs2.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ocfs2.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/reiserfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/reiserfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/romfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/romfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/squashfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/squashfs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/sysv.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/sysv.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ubifs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/ubifs.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/udf.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/udf.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_highpoint.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_hpfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_isw_raid.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_lsi_raid.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_lvm.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_mac.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_msdos.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_nvidia_raid.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_promise_raid.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_silicon_raid.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_ufs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/unused_via_raid.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/util.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/util.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/volume_id.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/volume_id.o
	modified:   tools/busybox-1.30.1/util-linux/volume_id/volume_id_internal.h
	modified:   tools/busybox-1.30.1/util-linux/volume_id/xfs.c
	modified:   tools/busybox-1.30.1/util-linux/volume_id/xfs.o
	modified:   tools/busybox-1.30.1/util-linux/wall.c
	modified:   tools/busybox-1.30.1/util-linux/wall.o
	modified:   tools/ksz9563_driver/.ksz9563.ko.cmd
	modified:   tools/ksz9563_driver/.ksz9563.mod.o.cmd
	modified:   tools/ksz9563_driver/.ksz9563.o.cmd
	modified:   tools/ksz9563_driver/.tmp_versions/ksz9563.mod
	modified:   tools/ksz9563_driver/Module.symvers
	modified:   tools/ksz9563_driver/ksz9563.ko
	modified:   tools/ksz9563_driver/ksz9563.mod.c
	modified:   tools/ksz9563_driver/ksz9563_test/Makefile
	modified:   tools/ksz9563_driver/ksz9563_test/ksz9563_i2c.c
	modified:   tools/ksz9563_driver/ksz9563_test/ksz9563_i2c.h
	modified:   tools/ksz9563_driver/modules.order
	modified:   tools/libiconv-1.16/ABOUT-NLS
	modified:   tools/libiconv-1.16/AUTHORS
	modified:   tools/libiconv-1.16/COPYING
	modified:   tools/libiconv-1.16/COPYING.LIB
	modified:   tools/libiconv-1.16/ChangeLog
	modified:   tools/libiconv-1.16/DEPENDENCIES
	modified:   tools/libiconv-1.16/DESIGN
	modified:   tools/libiconv-1.16/HACKING
	modified:   tools/libiconv-1.16/INSTALL.generic
	modified:   tools/libiconv-1.16/INSTALL.windows
	modified:   tools/libiconv-1.16/Makefile
	modified:   tools/libiconv-1.16/Makefile.devel
	modified:   tools/libiconv-1.16/Makefile.in
	modified:   tools/libiconv-1.16/NEWS
	modified:   tools/libiconv-1.16/NOTES
	modified:   tools/libiconv-1.16/README
	modified:   tools/libiconv-1.16/THANKS
	modified:   tools/libiconv-1.16/aclocal.m4
	modified:   tools/libiconv-1.16/build-aux/ltmain.sh
	modified:   tools/libiconv-1.16/build.tar.xz
	modified:   tools/libiconv-1.16/build/include/iconv.h
	modified:   tools/libiconv-1.16/build/include/libcharset.h
	modified:   tools/libiconv-1.16/build/include/localcharset.h
	modified:   tools/libiconv-1.16/build/share/doc/iconv.1.html
	modified:   tools/libiconv-1.16/build/share/doc/iconv.3.html
	modified:   tools/libiconv-1.16/build/share/doc/iconv_close.3.html
	modified:   tools/libiconv-1.16/build/share/doc/iconv_open.3.html
	modified:   tools/libiconv-1.16/build/share/doc/iconv_open_into.3.html
	modified:   tools/libiconv-1.16/build/share/doc/iconvctl.3.html
	modified:   tools/libiconv-1.16/build/share/locale/af/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/bg/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/ca/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/cs/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/da/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/de/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/el/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/eo/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/es/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/et/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/fi/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/fr/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/ga/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/gl/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/hr/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/hu/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/id/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/it/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/ja/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/lt/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/nl/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/pl/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/pt_BR/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/rm/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/ro/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/ru/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/sk/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/sl/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/sq/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/sr/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/sv/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/tr/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/uk/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/vi/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/wa/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/zh_CN/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/locale/zh_TW/LC_MESSAGES/libiconv.mo
	modified:   tools/libiconv-1.16/build/share/man/man1/iconv.1
	modified:   tools/libiconv-1.16/build/share/man/man3/iconv.3
	modified:   tools/libiconv-1.16/build/share/man/man3/iconv_close.3
	modified:   tools/libiconv-1.16/build/share/man/man3/iconv_open.3
	modified:   tools/libiconv-1.16/build/share/man/man3/iconv_open_into.3
	modified:   tools/libiconv-1.16/build/share/man/man3/iconvctl.3
	modified:   tools/libiconv-1.16/config.h
	modified:   tools/libiconv-1.16/config.h.in
	modified:   tools/libiconv-1.16/config.log
	modified:   tools/libiconv-1.16/configure.ac
	modified:   tools/libiconv-1.16/doc/relocatable.texi
	modified:   tools/libiconv-1.16/extras/ChangeLog
	modified:   tools/libiconv-1.16/extras/iconv_string.c
	modified:   tools/libiconv-1.16/extras/iconv_string.h
	modified:   tools/libiconv-1.16/gnulib-local/lib/alloca.in.h
	modified:   tools/libiconv-1.16/gnulib-local/lib/error.h.diff
	modified:   tools/libiconv-1.16/gnulib-local/lib/progname.h.diff
	modified:   tools/libiconv-1.16/gnulib-local/lib/xalloc.h
	modified:   tools/libiconv-1.16/gnulib-local/lib/xmalloc.c
	modified:   tools/libiconv-1.16/gnulib-local/lib/xstrdup.c
	modified:   tools/libiconv-1.16/gnulib-local/m4/alloca.m4
	modified:   tools/libiconv-1.16/gnulib-local/modules/libiconv-misc
	modified:   tools/libiconv-1.16/gnulib-local/modules/mbstate
	modified:   tools/libiconv-1.16/gnulib-local/modules/xalloc
	modified:   tools/libiconv-1.16/include/export.h
	modified:   tools/libiconv-1.16/include/iconv.h
	modified:   tools/libiconv-1.16/include/iconv.h.build.in
	modified:   tools/libiconv-1.16/include/iconv.h.in
	modified:   tools/libiconv-1.16/include/iconv.h.inst
	modified:   tools/libiconv-1.16/lib/.libs/libiconv.lai
	modified:   tools/libiconv-1.16/lib/Makefile
	modified:   tools/libiconv-1.16/lib/Makefile.in
	modified:   tools/libiconv-1.16/lib/aliases.gperf
	modified:   tools/libiconv-1.16/lib/aliases.h
	modified:   tools/libiconv-1.16/lib/aliases2.h
	modified:   tools/libiconv-1.16/lib/aliases_aix.h
	modified:   tools/libiconv-1.16/lib/aliases_aix_sysaix.h
	modified:   tools/libiconv-1.16/lib/aliases_dos.h
	modified:   tools/libiconv-1.16/lib/aliases_extra.h
	modified:   tools/libiconv-1.16/lib/aliases_osf1.h
	modified:   tools/libiconv-1.16/lib/aliases_osf1_sysosf1.h
	modified:   tools/libiconv-1.16/lib/aliases_sysaix.gperf
	modified:   tools/libiconv-1.16/lib/aliases_sysaix.h
	modified:   tools/libiconv-1.16/lib/aliases_syshpux.gperf
	modified:   tools/libiconv-1.16/lib/aliases_syshpux.h
	modified:   tools/libiconv-1.16/lib/aliases_sysosf1.gperf
	modified:   tools/libiconv-1.16/lib/aliases_sysosf1.h
	modified:   tools/libiconv-1.16/lib/aliases_syssolaris.gperf
	modified:   tools/libiconv-1.16/lib/aliases_syssolaris.h
	modified:   tools/libiconv-1.16/lib/armscii_8.h
	modified:   tools/libiconv-1.16/lib/ascii.h
	modified:   tools/libiconv-1.16/lib/atarist.h
	modified:   tools/libiconv-1.16/lib/big5.h
	modified:   tools/libiconv-1.16/lib/big5_2003.h
	modified:   tools/libiconv-1.16/lib/big5hkscs1999.h
	modified:   tools/libiconv-1.16/lib/big5hkscs2001.h
	modified:   tools/libiconv-1.16/lib/big5hkscs2004.h
	modified:   tools/libiconv-1.16/lib/big5hkscs2008.h
	modified:   tools/libiconv-1.16/lib/c99.h
	modified:   tools/libiconv-1.16/lib/canonical.h
	modified:   tools/libiconv-1.16/lib/canonical_aix.h
	modified:   tools/libiconv-1.16/lib/canonical_aix_sysaix.h
	modified:   tools/libiconv-1.16/lib/canonical_dos.h
	modified:   tools/libiconv-1.16/lib/canonical_extra.h
	modified:   tools/libiconv-1.16/lib/canonical_local.h
	modified:   tools/libiconv-1.16/lib/canonical_local_sysaix.h
	modified:   tools/libiconv-1.16/lib/canonical_local_syshpux.h
	modified:   tools/libiconv-1.16/lib/canonical_local_sysosf1.h
	modified:   tools/libiconv-1.16/lib/canonical_local_syssolaris.h
	modified:   tools/libiconv-1.16/lib/canonical_osf1.h
	modified:   tools/libiconv-1.16/lib/canonical_osf1_sysosf1.h
	modified:   tools/libiconv-1.16/lib/canonical_sysaix.h
	modified:   tools/libiconv-1.16/lib/canonical_syshpux.h
	modified:   tools/libiconv-1.16/lib/canonical_sysosf1.h
	modified:   tools/libiconv-1.16/lib/canonical_syssolaris.h
	modified:   tools/libiconv-1.16/lib/ces_big5.h
	modified:   tools/libiconv-1.16/lib/ces_gbk.h
	modified:   tools/libiconv-1.16/lib/cjk_variants.h
	modified:   tools/libiconv-1.16/lib/cns11643.h
	modified:   tools/libiconv-1.16/lib/cns11643_1.h
	modified:   tools/libiconv-1.16/lib/cns11643_15.h
	modified:   tools/libiconv-1.16/lib/cns11643_2.h
	modified:   tools/libiconv-1.16/lib/cns11643_3.h
	modified:   tools/libiconv-1.16/lib/cns11643_4.h
	modified:   tools/libiconv-1.16/lib/cns11643_4a.h
	modified:   tools/libiconv-1.16/lib/cns11643_4b.h
	modified:   tools/libiconv-1.16/lib/cns11643_5.h
	modified:   tools/libiconv-1.16/lib/cns11643_6.h
	modified:   tools/libiconv-1.16/lib/cns11643_7.h
	modified:   tools/libiconv-1.16/lib/cns11643_inv.h
	modified:   tools/libiconv-1.16/lib/config.h
	modified:   tools/libiconv-1.16/lib/config.h.in
	modified:   tools/libiconv-1.16/lib/converters.h
	modified:   tools/libiconv-1.16/lib/cp1046.h
	modified:   tools/libiconv-1.16/lib/cp1124.h
	modified:   tools/libiconv-1.16/lib/cp1125.h
	modified:   tools/libiconv-1.16/lib/cp1129.h
	modified:   tools/libiconv-1.16/lib/cp1131.h
	modified:   tools/libiconv-1.16/lib/cp1133.h
	modified:   tools/libiconv-1.16/lib/cp1161.h
	modified:   tools/libiconv-1.16/lib/cp1162.h
	modified:   tools/libiconv-1.16/lib/cp1163.h
	modified:   tools/libiconv-1.16/lib/cp1250.h
	modified:   tools/libiconv-1.16/lib/cp1251.h
	modified:   tools/libiconv-1.16/lib/cp1252.h
	modified:   tools/libiconv-1.16/lib/cp1253.h
	modified:   tools/libiconv-1.16/lib/cp1254.h
	modified:   tools/libiconv-1.16/lib/cp1255.h
	modified:   tools/libiconv-1.16/lib/cp1256.h
	modified:   tools/libiconv-1.16/lib/cp1257.h
	modified:   tools/libiconv-1.16/lib/cp1258.h
	modified:   tools/libiconv-1.16/lib/cp437.h
	modified:   tools/libiconv-1.16/lib/cp50221_0208_ext.h
	modified:   tools/libiconv-1.16/lib/cp50221_0212_ext.h
	modified:   tools/libiconv-1.16/lib/cp737.h
	modified:   tools/libiconv-1.16/lib/cp775.h
	modified:   tools/libiconv-1.16/lib/cp850.h
	modified:   tools/libiconv-1.16/lib/cp852.h
	modified:   tools/libiconv-1.16/lib/cp853.h
	modified:   tools/libiconv-1.16/lib/cp855.h
	modified:   tools/libiconv-1.16/lib/cp856.h
	modified:   tools/libiconv-1.16/lib/cp857.h
	modified:   tools/libiconv-1.16/lib/cp858.h
	modified:   tools/libiconv-1.16/lib/cp860.h
	modified:   tools/libiconv-1.16/lib/cp861.h
	modified:   tools/libiconv-1.16/lib/cp862.h
	modified:   tools/libiconv-1.16/lib/cp863.h
	modified:   tools/libiconv-1.16/lib/cp864.h
	modified:   tools/libiconv-1.16/lib/cp865.h
	modified:   tools/libiconv-1.16/lib/cp866.h
	modified:   tools/libiconv-1.16/lib/cp869.h
	modified:   tools/libiconv-1.16/lib/cp874.h
	modified:   tools/libiconv-1.16/lib/cp922.h
	modified:   tools/libiconv-1.16/lib/cp932.h
	modified:   tools/libiconv-1.16/lib/cp932ext.h
	modified:   tools/libiconv-1.16/lib/cp936.h
	modified:   tools/libiconv-1.16/lib/cp936ext.h
	modified:   tools/libiconv-1.16/lib/cp943.h
	modified:   tools/libiconv-1.16/lib/cp949.h
	modified:   tools/libiconv-1.16/lib/cp950.h
	modified:   tools/libiconv-1.16/lib/cp950ext.h
	modified:   tools/libiconv-1.16/lib/dec_hanyu.h
	modified:   tools/libiconv-1.16/lib/dec_kanji.h
	modified:   tools/libiconv-1.16/lib/encodings.def
	modified:   tools/libiconv-1.16/lib/encodings_aix.def
	modified:   tools/libiconv-1.16/lib/encodings_dos.def
	modified:   tools/libiconv-1.16/lib/encodings_extra.def
	modified:   tools/libiconv-1.16/lib/encodings_local.def
	modified:   tools/libiconv-1.16/lib/encodings_osf1.def
	modified:   tools/libiconv-1.16/lib/euc_cn.h
	modified:   tools/libiconv-1.16/lib/euc_jisx0213.h
	modified:   tools/libiconv-1.16/lib/euc_jp.h
	modified:   tools/libiconv-1.16/lib/euc_kr.h
	modified:   tools/libiconv-1.16/lib/euc_tw.h
	modified:   tools/libiconv-1.16/lib/flags.h
	modified:   tools/libiconv-1.16/lib/flushwc.h
	modified:   tools/libiconv-1.16/lib/gb12345.h
	modified:   tools/libiconv-1.16/lib/gb12345ext.h
	modified:   tools/libiconv-1.16/lib/gb18030.h
	modified:   tools/libiconv-1.16/lib/gb18030ext.h
	modified:   tools/libiconv-1.16/lib/gb18030uni.h
	modified:   tools/libiconv-1.16/lib/gb2312.h
	modified:   tools/libiconv-1.16/lib/gbk.h
	modified:   tools/libiconv-1.16/lib/gbkext1.h
	modified:   tools/libiconv-1.16/lib/gbkext2.h
	modified:   tools/libiconv-1.16/lib/gbkext_inv.h
	modified:   tools/libiconv-1.16/lib/genaliases.c
	modified:   tools/libiconv-1.16/lib/genaliases2.c
	modified:   tools/libiconv-1.16/lib/genflags.c
	modified:   tools/libiconv-1.16/lib/gentranslit.c
	modified:   tools/libiconv-1.16/lib/georgian_academy.h
	modified:   tools/libiconv-1.16/lib/georgian_ps.h
	modified:   tools/libiconv-1.16/lib/hkscs1999.h
	modified:   tools/libiconv-1.16/lib/hkscs2001.h
	modified:   tools/libiconv-1.16/lib/hkscs2004.h
	modified:   tools/libiconv-1.16/lib/hkscs2008.h
	modified:   tools/libiconv-1.16/lib/hp_roman8.h
	modified:   tools/libiconv-1.16/lib/hz.h
	modified:   tools/libiconv-1.16/lib/iconv.c
	modified:   tools/libiconv-1.16/lib/iconv.lo
	modified:   tools/libiconv-1.16/lib/iconv_open1.h
	modified:   tools/libiconv-1.16/lib/iconv_open2.h
	modified:   tools/libiconv-1.16/lib/iso2022_cn.h
	modified:   tools/libiconv-1.16/lib/iso2022_cnext.h
	modified:   tools/libiconv-1.16/lib/iso2022_jp.h
	modified:   tools/libiconv-1.16/lib/iso2022_jp1.h
	modified:   tools/libiconv-1.16/lib/iso2022_jp2.h
	modified:   tools/libiconv-1.16/lib/iso2022_jp3.h
	modified:   tools/libiconv-1.16/lib/iso2022_jpms.h
	modified:   tools/libiconv-1.16/lib/iso2022_kr.h
	modified:   tools/libiconv-1.16/lib/iso646_cn.h
	modified:   tools/libiconv-1.16/lib/iso646_jp.h
	modified:   tools/libiconv-1.16/lib/iso8859_1.h
	modified:   tools/libiconv-1.16/lib/iso8859_10.h
	modified:   tools/libiconv-1.16/lib/iso8859_11.h
	modified:   tools/libiconv-1.16/lib/iso8859_13.h
	modified:   tools/libiconv-1.16/lib/iso8859_14.h
	modified:   tools/libiconv-1.16/lib/iso8859_15.h
	modified:   tools/libiconv-1.16/lib/iso8859_16.h
	modified:   tools/libiconv-1.16/lib/iso8859_2.h
	modified:   tools/libiconv-1.16/lib/iso8859_3.h
	modified:   tools/libiconv-1.16/lib/iso8859_4.h
	modified:   tools/libiconv-1.16/lib/iso8859_5.h
	modified:   tools/libiconv-1.16/lib/iso8859_6.h
	modified:   tools/libiconv-1.16/lib/iso8859_7.h
	modified:   tools/libiconv-1.16/lib/iso8859_8.h
	modified:   tools/libiconv-1.16/lib/iso8859_9.h
	modified:   tools/libiconv-1.16/lib/isoir165.h
	modified:   tools/libiconv-1.16/lib/isoir165ext.h
	modified:   tools/libiconv-1.16/lib/java.h
	modified:   tools/libiconv-1.16/lib/jisx0201.h
	modified:   tools/libiconv-1.16/lib/jisx0208.h
	modified:   tools/libiconv-1.16/lib/jisx0212.h
	modified:   tools/libiconv-1.16/lib/jisx0213.h
	modified:   tools/libiconv-1.16/lib/johab.h
	modified:   tools/libiconv-1.16/lib/johab_hangul.h
	modified:   tools/libiconv-1.16/lib/koi8_r.h
	modified:   tools/libiconv-1.16/lib/koi8_ru.h
	modified:   tools/libiconv-1.16/lib/koi8_t.h
	modified:   tools/libiconv-1.16/lib/koi8_u.h
	modified:   tools/libiconv-1.16/lib/ksc5601.h
	modified:   tools/libiconv-1.16/lib/libcharset.h
	modified:   tools/libiconv-1.16/lib/libiconv.la
	modified:   tools/libiconv-1.16/lib/localcharset.h
	modified:   tools/libiconv-1.16/lib/localcharset.lo
	modified:   tools/libiconv-1.16/lib/loop_unicode.h
	modified:   tools/libiconv-1.16/lib/loop_wchar.h
	modified:   tools/libiconv-1.16/lib/loops.h
	modified:   tools/libiconv-1.16/lib/mac_arabic.h
	modified:   tools/libiconv-1.16/lib/mac_centraleurope.h
	modified:   tools/libiconv-1.16/lib/mac_croatian.h
	modified:   tools/libiconv-1.16/lib/mac_cyrillic.h
	modified:   tools/libiconv-1.16/lib/mac_greek.h
	modified:   tools/libiconv-1.16/lib/mac_hebrew.h
	modified:   tools/libiconv-1.16/lib/mac_iceland.h
	modified:   tools/libiconv-1.16/lib/mac_roman.h
	modified:   tools/libiconv-1.16/lib/mac_romania.h
	modified:   tools/libiconv-1.16/lib/mac_thai.h
	modified:   tools/libiconv-1.16/lib/mac_turkish.h
	modified:   tools/libiconv-1.16/lib/mac_ukraine.h
	modified:   tools/libiconv-1.16/lib/mulelao.h
	modified:   tools/libiconv-1.16/lib/nextstep.h
	modified:   tools/libiconv-1.16/lib/pt154.h
	modified:   tools/libiconv-1.16/lib/relocatable.c
	modified:   tools/libiconv-1.16/lib/relocatable.h
	modified:   tools/libiconv-1.16/lib/relocatable.lo
	modified:   tools/libiconv-1.16/lib/riscos1.h
	modified:   tools/libiconv-1.16/lib/rk1048.h
	modified:   tools/libiconv-1.16/lib/shift_jisx0213.h
	modified:   tools/libiconv-1.16/lib/sjis.h
	modified:   tools/libiconv-1.16/lib/stamp-h2
	modified:   tools/libiconv-1.16/lib/tcvn.h
	modified:   tools/libiconv-1.16/lib/tds565.h
	modified:   tools/libiconv-1.16/lib/tis620.h
	modified:   tools/libiconv-1.16/lib/translit.def
	modified:   tools/libiconv-1.16/lib/translit.h
	modified:   tools/libiconv-1.16/lib/ucs2.h
	modified:   tools/libiconv-1.16/lib/ucs2be.h
	modified:   tools/libiconv-1.16/lib/ucs2internal.h
	modified:   tools/libiconv-1.16/lib/ucs2le.h
	modified:   tools/libiconv-1.16/lib/ucs2swapped.h
	modified:   tools/libiconv-1.16/lib/ucs4.h
	modified:   tools/libiconv-1.16/lib/ucs4be.h
	modified:   tools/libiconv-1.16/lib/ucs4internal.h
	modified:   tools/libiconv-1.16/lib/ucs4le.h
	modified:   tools/libiconv-1.16/lib/ucs4swapped.h
	modified:   tools/libiconv-1.16/lib/uhc_1.h
	modified:   tools/libiconv-1.16/lib/uhc_2.h
	modified:   tools/libiconv-1.16/lib/utf16.h
	modified:   tools/libiconv-1.16/lib/utf16be.h
	modified:   tools/libiconv-1.16/lib/utf16le.h
	modified:   tools/libiconv-1.16/lib/utf32.h
	modified:   tools/libiconv-1.16/lib/utf32be.h
	modified:   tools/libiconv-1.16/lib/utf32le.h
	modified:   tools/libiconv-1.16/lib/utf7.h
	modified:   tools/libiconv-1.16/lib/utf8.h
	modified:   tools/libiconv-1.16/lib/vietcomb.h
	modified:   tools/libiconv-1.16/lib/viscii.h
	modified:   tools/libiconv-1.16/libcharset/AUTHORS
	modified:   tools/libiconv-1.16/libcharset/COPYING.LIB
	modified:   tools/libiconv-1.16/libcharset/ChangeLog
	modified:   tools/libiconv-1.16/libcharset/DEPENDENCIES
	modified:   tools/libiconv-1.16/libcharset/HACKING
	modified:   tools/libiconv-1.16/libcharset/INSTALL.generic
	modified:   tools/libiconv-1.16/libcharset/INSTALL.windows
	modified:   tools/libiconv-1.16/libcharset/INTEGRATE
	modified:   tools/libiconv-1.16/libcharset/Makefile
	modified:   tools/libiconv-1.16/libcharset/Makefile.devel
	modified:   tools/libiconv-1.16/libcharset/Makefile.in
	modified:   tools/libiconv-1.16/libcharset/NEWS
	modified:   tools/libiconv-1.16/libcharset/README
	modified:   tools/libiconv-1.16/libcharset/autoconf/aclocal.m4
	modified:   tools/libiconv-1.16/libcharset/build-aux/ltmain.sh
	modified:   tools/libiconv-1.16/libcharset/config.h
	modified:   tools/libiconv-1.16/libcharset/config.h.in
	modified:   tools/libiconv-1.16/libcharset/config.log
	modified:   tools/libiconv-1.16/libcharset/configure.ac
	modified:   tools/libiconv-1.16/libcharset/include/export.h
	modified:   tools/libiconv-1.16/libcharset/include/libcharset.h
	modified:   tools/libiconv-1.16/libcharset/include/libcharset.h.in
	modified:   tools/libiconv-1.16/libcharset/include/localcharset.h
	modified:   tools/libiconv-1.16/libcharset/include/localcharset.h.build.in
	modified:   tools/libiconv-1.16/libcharset/include/localcharset.h.in
	modified:   tools/libiconv-1.16/libcharset/include/localcharset.h.inst
	modified:   tools/libiconv-1.16/libcharset/lib/.libs/libcharset.lai
	modified:   tools/libiconv-1.16/libcharset/lib/ChangeLog
	modified:   tools/libiconv-1.16/libcharset/lib/Makefile
	modified:   tools/libiconv-1.16/libcharset/lib/Makefile.in
	modified:   tools/libiconv-1.16/libcharset/lib/libcharset.la
	modified:   tools/libiconv-1.16/libcharset/lib/localcharset.c
	modified:   tools/libiconv-1.16/libcharset/lib/localcharset.lo
	modified:   tools/libiconv-1.16/libcharset/lib/relocatable-stub.c
	modified:   tools/libiconv-1.16/libcharset/lib/relocatable-stub.lo
	modified:   tools/libiconv-1.16/libcharset/m4/codeset.m4
	modified:   tools/libiconv-1.16/libcharset/m4/fcntl-o.m4
	modified:   tools/libiconv-1.16/libcharset/m4/glibc21.m4
	modified:   tools/libiconv-1.16/libcharset/m4/libtool.m4
	modified:   tools/libiconv-1.16/libcharset/m4/ltoptions.m4
	modified:   tools/libiconv-1.16/libcharset/m4/ltsugar.m4
	modified:   tools/libiconv-1.16/libcharset/m4/ltversion.m4
	modified:   tools/libiconv-1.16/libcharset/m4/lt~obsolete.m4
	modified:   tools/libiconv-1.16/libcharset/m4/visibility.m4
	modified:   tools/libiconv-1.16/libcharset/tools/README
	modified:   tools/libiconv-1.16/libcharset/tools/aix-3.2.5
	modified:   tools/libiconv-1.16/libcharset/tools/aix-4.1.5
	modified:   tools/libiconv-1.16/libcharset/tools/aix-4.2.0
	modified:   tools/libiconv-1.16/libcharset/tools/aix-4.3.2
	modified:   tools/libiconv-1.16/libcharset/tools/beos-5
	modified:   tools/libiconv-1.16/libcharset/tools/cygwin-1.7.2
	modified:   tools/libiconv-1.16/libcharset/tools/darwin-6.8
	modified:   tools/libiconv-1.16/libcharset/tools/darwin-7.5
	modified:   tools/libiconv-1.16/libcharset/tools/darwin-9.5
	modified:   tools/libiconv-1.16/libcharset/tools/freebsd-3.3
	modified:   tools/libiconv-1.16/libcharset/tools/glibc-2.1.3
	modified:   tools/libiconv-1.16/libcharset/tools/glibc-2.1.90
	modified:   tools/libiconv-1.16/libcharset/tools/glibc-2.2
	modified:   tools/libiconv-1.16/libcharset/tools/glibc-2.2-XF86-3.3.6
	modified:   tools/libiconv-1.16/libcharset/tools/glibc-2.2-XF86-4.0.1f
	modified:   tools/libiconv-1.16/libcharset/tools/hpux-10.01
	modified:   tools/libiconv-1.16/libcharset/tools/hpux-10.20
	modified:   tools/libiconv-1.16/libcharset/tools/hpux-11.00
	modified:   tools/libiconv-1.16/libcharset/tools/irix-6.5
	modified:   tools/libiconv-1.16/libcharset/tools/locale_charset.c
	modified:   tools/libiconv-1.16/libcharset/tools/locale_codeset.c
	modified:   tools/libiconv-1.16/libcharset/tools/locale_monthnames.c
	modified:   tools/libiconv-1.16/libcharset/tools/locale_x11encoding.c
	modified:   tools/libiconv-1.16/libcharset/tools/netbsd-3.0
	modified:   tools/libiconv-1.16/libcharset/tools/openbsd-4.1
	modified:   tools/libiconv-1.16/libcharset/tools/osf1-4.0a
	modified:   tools/libiconv-1.16/libcharset/tools/osf1-4.0d
	modified:   tools/libiconv-1.16/libcharset/tools/osf1-5.1
	modified:   tools/libiconv-1.16/libcharset/tools/solaris-2.4
	modified:   tools/libiconv-1.16/libcharset/tools/solaris-2.5.1
	modified:   tools/libiconv-1.16/libcharset/tools/solaris-2.6
	modified:   tools/libiconv-1.16/libcharset/tools/solaris-2.6-cjk
	modified:   tools/libiconv-1.16/libcharset/tools/solaris-2.7
	modified:   tools/libiconv-1.16/libcharset/tools/sunos-4.1.4
	modified:   tools/libiconv-1.16/libcharset/tools/win32
	modified:   tools/libiconv-1.16/m4/cp.m4
	modified:   tools/libiconv-1.16/m4/eilseq.m4
	modified:   tools/libiconv-1.16/m4/endian.m4
	modified:   tools/libiconv-1.16/m4/general.m4
	modified:   tools/libiconv-1.16/m4/libtool.m4
	modified:   tools/libiconv-1.16/m4/ln.m4
	modified:   tools/libiconv-1.16/m4/ltoptions.m4
	modified:   tools/libiconv-1.16/m4/ltsugar.m4
	modified:   tools/libiconv-1.16/m4/ltversion.m4
	modified:   tools/libiconv-1.16/m4/lt~obsolete.m4
	modified:   tools/libiconv-1.16/m4/proto.m4
	modified:   tools/libiconv-1.16/man/Makefile
	modified:   tools/libiconv-1.16/man/Makefile.in
	modified:   tools/libiconv-1.16/man/iconv.1
	modified:   tools/libiconv-1.16/man/iconv.1.html
	modified:   tools/libiconv-1.16/man/iconv.3
	modified:   tools/libiconv-1.16/man/iconv.3.html
	modified:   tools/libiconv-1.16/man/iconv_close.3
	modified:   tools/libiconv-1.16/man/iconv_close.3.html
	modified:   tools/libiconv-1.16/man/iconv_open.3
	modified:   tools/libiconv-1.16/man/iconv_open.3.html
	modified:   tools/libiconv-1.16/man/iconv_open_into.3
	modified:   tools/libiconv-1.16/man/iconv_open_into.3.html
	modified:   tools/libiconv-1.16/man/iconvctl.3
	modified:   tools/libiconv-1.16/man/iconvctl.3.html
	modified:   tools/libiconv-1.16/os2/iconv.def
	modified:   tools/libiconv-1.16/po/ChangeLog
	modified:   tools/libiconv-1.16/po/LINGUAS
	modified:   tools/libiconv-1.16/po/Makefile
	modified:   tools/libiconv-1.16/po/Makefile.in
	modified:   tools/libiconv-1.16/po/Makefile.in.in
	modified:   tools/libiconv-1.16/po/Makevars
	modified:   tools/libiconv-1.16/po/POTFILES
	modified:   tools/libiconv-1.16/po/POTFILES.in
	modified:   tools/libiconv-1.16/po/Rules-quot
	modified:   tools/libiconv-1.16/po/af.gmo
	modified:   tools/libiconv-1.16/po/af.po
	modified:   tools/libiconv-1.16/po/bg.gmo
	modified:   tools/libiconv-1.16/po/bg.po
	modified:   tools/libiconv-1.16/po/boldquot.sed
	modified:   tools/libiconv-1.16/po/ca.gmo
	modified:   tools/libiconv-1.16/po/ca.po
	modified:   tools/libiconv-1.16/po/cs.gmo
	modified:   tools/libiconv-1.16/po/cs.po
	modified:   tools/libiconv-1.16/po/da.gmo
	modified:   tools/libiconv-1.16/po/da.po
	modified:   tools/libiconv-1.16/po/de.gmo
	modified:   tools/libiconv-1.16/po/de.po
	modified:   tools/libiconv-1.16/po/el.gmo
	modified:   tools/libiconv-1.16/po/el.po
	modified:   tools/libiconv-1.16/po/en@boldquot.header
	modified:   tools/libiconv-1.16/po/en@quot.header
	modified:   tools/libiconv-1.16/po/eo.gmo
	modified:   tools/libiconv-1.16/po/eo.po
	modified:   tools/libiconv-1.16/po/es.gmo
	modified:   tools/libiconv-1.16/po/es.po
	modified:   tools/libiconv-1.16/po/et.gmo
	modified:   tools/libiconv-1.16/po/et.po
	modified:   tools/libiconv-1.16/po/fi.gmo
	modified:   tools/libiconv-1.16/po/fi.po
	modified:   tools/libiconv-1.16/po/fr.gmo
	modified:   tools/libiconv-1.16/po/fr.po
	modified:   tools/libiconv-1.16/po/ga.gmo
	modified:   tools/libiconv-1.16/po/ga.po
	modified:   tools/libiconv-1.16/po/gl.gmo
	modified:   tools/libiconv-1.16/po/gl.po
	modified:   tools/libiconv-1.16/po/hr.gmo
	modified:   tools/libiconv-1.16/po/hr.po
	modified:   tools/libiconv-1.16/po/hu.gmo
	modified:   tools/libiconv-1.16/po/hu.po
	modified:   tools/libiconv-1.16/po/id.gmo
	modified:   tools/libiconv-1.16/po/id.po
	modified:   tools/libiconv-1.16/po/insert-header.sin
	modified:   tools/libiconv-1.16/po/it.gmo
	modified:   tools/libiconv-1.16/po/it.po
	modified:   tools/libiconv-1.16/po/ja.gmo
	modified:   tools/libiconv-1.16/po/ja.po
	modified:   tools/libiconv-1.16/po/libiconv.pot
	modified:   tools/libiconv-1.16/po/lt.gmo
	modified:   tools/libiconv-1.16/po/lt.po
	modified:   tools/libiconv-1.16/po/nl.gmo
	modified:   tools/libiconv-1.16/po/nl.po
	modified:   tools/libiconv-1.16/po/pl.gmo
	modified:   tools/libiconv-1.16/po/pl.po
	modified:   tools/libiconv-1.16/po/pt_BR.gmo
	modified:   tools/libiconv-1.16/po/pt_BR.po
	modified:   tools/libiconv-1.16/po/quot.sed
	modified:   tools/libiconv-1.16/po/remove-potcdate.sin
	modified:   tools/libiconv-1.16/po/rm.gmo
	modified:   tools/libiconv-1.16/po/rm.po
	modified:   tools/libiconv-1.16/po/ro.gmo
	modified:   tools/libiconv-1.16/po/ro.po
	modified:   tools/libiconv-1.16/po/ru.gmo
	modified:   tools/libiconv-1.16/po/ru.po
	modified:   tools/libiconv-1.16/po/sk.gmo
	modified:   tools/libiconv-1.16/po/sk.po
	modified:   tools/libiconv-1.16/po/sl.gmo
	modified:   tools/libiconv-1.16/po/sl.po
	modified:   tools/libiconv-1.16/po/sq.gmo
	modified:   tools/libiconv-1.16/po/sq.po
	modified:   tools/libiconv-1.16/po/sr.gmo
	modified:   tools/libiconv-1.16/po/sr.po
	modified:   tools/libiconv-1.16/po/stamp-po
	modified:   tools/libiconv-1.16/po/sv.gmo
	modified:   tools/libiconv-1.16/po/sv.po
	modified:   tools/libiconv-1.16/po/tr.gmo
	modified:   tools/libiconv-1.16/po/tr.po
	modified:   tools/libiconv-1.16/po/uk.gmo
	modified:   tools/libiconv-1.16/po/uk.po
	modified:   tools/libiconv-1.16/po/vi.gmo
	modified:   tools/libiconv-1.16/po/vi.po
	modified:   tools/libiconv-1.16/po/wa.gmo
	modified:   tools/libiconv-1.16/po/wa.po
	modified:   tools/libiconv-1.16/po/zh_CN.gmo
	modified:   tools/libiconv-1.16/po/zh_CN.po
	modified:   tools/libiconv-1.16/po/zh_TW.gmo
	modified:   tools/libiconv-1.16/po/zh_TW.po
	modified:   tools/libiconv-1.16/src/Makefile
	modified:   tools/libiconv-1.16/src/Makefile.in
	modified:   tools/libiconv-1.16/src/iconv.c
	modified:   tools/libiconv-1.16/src/iconv_no_i18n.c
	modified:   tools/libiconv-1.16/srclib/Makefile
	modified:   tools/libiconv-1.16/srclib/Makefile.am
	modified:   tools/libiconv-1.16/srclib/Makefile.gnulib
	modified:   tools/libiconv-1.16/srclib/Makefile.in
	modified:   tools/libiconv-1.16/srclib/_Noreturn.h
	modified:   tools/libiconv-1.16/srclib/alloca.h
	modified:   tools/libiconv-1.16/srclib/alloca.in.h
	modified:   tools/libiconv-1.16/srclib/allocator.c
	modified:   tools/libiconv-1.16/srclib/allocator.h
	modified:   tools/libiconv-1.16/srclib/areadlink.c
	modified:   tools/libiconv-1.16/srclib/areadlink.h
	modified:   tools/libiconv-1.16/srclib/arg-nonnull.h
	modified:   tools/libiconv-1.16/srclib/basename-lgpl.c
	modified:   tools/libiconv-1.16/srclib/binary-io.c
	modified:   tools/libiconv-1.16/srclib/binary-io.h
	modified:   tools/libiconv-1.16/srclib/c++defs.h
	modified:   tools/libiconv-1.16/srclib/c-ctype.c
	modified:   tools/libiconv-1.16/srclib/c-ctype.h
	modified:   tools/libiconv-1.16/srclib/canonicalize-lgpl.c
	modified:   tools/libiconv-1.16/srclib/careadlinkat.c
	modified:   tools/libiconv-1.16/srclib/careadlinkat.h
	modified:   tools/libiconv-1.16/srclib/dirname-lgpl.c
	modified:   tools/libiconv-1.16/srclib/dirname.h
	modified:   tools/libiconv-1.16/srclib/dosname.h
	modified:   tools/libiconv-1.16/srclib/errno.in.h
	modified:   tools/libiconv-1.16/srclib/error.c
	modified:   tools/libiconv-1.16/srclib/error.h
	modified:   tools/libiconv-1.16/srclib/fcntl.h
	modified:   tools/libiconv-1.16/srclib/fcntl.in.h
	modified:   tools/libiconv-1.16/srclib/filename.h
	modified:   tools/libiconv-1.16/srclib/getprogname.c
	modified:   tools/libiconv-1.16/srclib/getprogname.h
	modified:   tools/libiconv-1.16/srclib/gettext.h
	modified:   tools/libiconv-1.16/srclib/intprops.h
	modified:   tools/libiconv-1.16/srclib/limits.h
	modified:   tools/libiconv-1.16/srclib/limits.in.h
	modified:   tools/libiconv-1.16/srclib/localcharset.h
	modified:   tools/libiconv-1.16/srclib/lstat.c
	modified:   tools/libiconv-1.16/srclib/malloc.c
	modified:   tools/libiconv-1.16/srclib/malloca.c
	modified:   tools/libiconv-1.16/srclib/malloca.h
	modified:   tools/libiconv-1.16/srclib/msvc-inval.c
	modified:   tools/libiconv-1.16/srclib/msvc-inval.h
	modified:   tools/libiconv-1.16/srclib/msvc-nothrow.c
	modified:   tools/libiconv-1.16/srclib/msvc-nothrow.h
	modified:   tools/libiconv-1.16/srclib/pathmax.h
	modified:   tools/libiconv-1.16/srclib/progname.c
	modified:   tools/libiconv-1.16/srclib/progname.h
	modified:   tools/libiconv-1.16/srclib/progreloc.c
	modified:   tools/libiconv-1.16/srclib/raise.c
	modified:   tools/libiconv-1.16/srclib/read.c
	modified:   tools/libiconv-1.16/srclib/readlink.c
	modified:   tools/libiconv-1.16/srclib/relocatable.c
	modified:   tools/libiconv-1.16/srclib/relocatable.h
	modified:   tools/libiconv-1.16/srclib/relocwrapper.c
	modified:   tools/libiconv-1.16/srclib/safe-read.c
	modified:   tools/libiconv-1.16/srclib/safe-read.h
	modified:   tools/libiconv-1.16/srclib/setenv.c
	modified:   tools/libiconv-1.16/srclib/signal.h
	modified:   tools/libiconv-1.16/srclib/signal.in.h
	modified:   tools/libiconv-1.16/srclib/sigprocmask.c
	modified:   tools/libiconv-1.16/srclib/stat-time.c
	modified:   tools/libiconv-1.16/srclib/stat-time.h
	modified:   tools/libiconv-1.16/srclib/stat-w32.c
	modified:   tools/libiconv-1.16/srclib/stat-w32.h
	modified:   tools/libiconv-1.16/srclib/stat.c
	modified:   tools/libiconv-1.16/srclib/stdbool.in.h
	modified:   tools/libiconv-1.16/srclib/stddef.in.h
	modified:   tools/libiconv-1.16/srclib/stdint.in.h
	modified:   tools/libiconv-1.16/srclib/stdio-write.c
	modified:   tools/libiconv-1.16/srclib/stdio.h
	modified:   tools/libiconv-1.16/srclib/stdio.in.h
	modified:   tools/libiconv-1.16/srclib/stdlib.h
	modified:   tools/libiconv-1.16/srclib/stdlib.in.h
	modified:   tools/libiconv-1.16/srclib/streq.h
	modified:   tools/libiconv-1.16/srclib/strerror-override.c
	modified:   tools/libiconv-1.16/srclib/strerror-override.h
	modified:   tools/libiconv-1.16/srclib/strerror.c
	modified:   tools/libiconv-1.16/srclib/string.h
	modified:   tools/libiconv-1.16/srclib/string.in.h
	modified:   tools/libiconv-1.16/srclib/stripslash.c
	modified:   tools/libiconv-1.16/srclib/sys-limits.h
	modified:   tools/libiconv-1.16/srclib/sys/stat.h
	modified:   tools/libiconv-1.16/srclib/sys/types.h
	modified:   tools/libiconv-1.16/srclib/sys_stat.in.h
	modified:   tools/libiconv-1.16/srclib/sys_types.in.h
	modified:   tools/libiconv-1.16/srclib/time.h
	modified:   tools/libiconv-1.16/srclib/time.in.h
	modified:   tools/libiconv-1.16/srclib/unistd.c
	modified:   tools/libiconv-1.16/srclib/unistd.h
	modified:   tools/libiconv-1.16/srclib/unistd.in.h
	modified:   tools/libiconv-1.16/srclib/unitypes.h
	modified:   tools/libiconv-1.16/srclib/unitypes.in.h
	modified:   tools/libiconv-1.16/srclib/uniwidth.h
	modified:   tools/libiconv-1.16/srclib/uniwidth.in.h
	modified:   tools/libiconv-1.16/srclib/uniwidth/.dirstamp
	modified:   tools/libiconv-1.16/srclib/uniwidth/cjk.h
	modified:   tools/libiconv-1.16/srclib/uniwidth/width.c
	modified:   tools/libiconv-1.16/srclib/unlocked-io.h
	modified:   tools/libiconv-1.16/srclib/verify.h
	modified:   tools/libiconv-1.16/srclib/warn-on-use.h
	modified:   tools/libiconv-1.16/srclib/xalloc-oversized.h
	modified:   tools/libiconv-1.16/srclib/xalloc.h
	modified:   tools/libiconv-1.16/srclib/xmalloc.c
	modified:   tools/libiconv-1.16/srclib/xreadlink.c
	modified:   tools/libiconv-1.16/srclib/xreadlink.h
	modified:   tools/libiconv-1.16/srclib/xstrdup.c
	modified:   tools/libiconv-1.16/srcm4/00gnulib.m4
	modified:   tools/libiconv-1.16/srcm4/absolute-header.m4
	modified:   tools/libiconv-1.16/srcm4/alloca.m4
	modified:   tools/libiconv-1.16/srcm4/asm-underscore.m4
	modified:   tools/libiconv-1.16/srcm4/canonicalize.m4
	modified:   tools/libiconv-1.16/srcm4/codeset.m4
	modified:   tools/libiconv-1.16/srcm4/dirname.m4
	modified:   tools/libiconv-1.16/srcm4/double-slash-root.m4
	modified:   tools/libiconv-1.16/srcm4/eealloc.m4
	modified:   tools/libiconv-1.16/srcm4/environ.m4
	modified:   tools/libiconv-1.16/srcm4/errno_h.m4
	modified:   tools/libiconv-1.16/srcm4/error.m4
	modified:   tools/libiconv-1.16/srcm4/extensions.m4
	modified:   tools/libiconv-1.16/srcm4/extern-inline.m4
	modified:   tools/libiconv-1.16/srcm4/fcntl-o.m4
	modified:   tools/libiconv-1.16/srcm4/fcntl_h.m4
	modified:   tools/libiconv-1.16/srcm4/getprogname.m4
	modified:   tools/libiconv-1.16/srcm4/gettext.m4
	modified:   tools/libiconv-1.16/srcm4/glibc2.m4
	modified:   tools/libiconv-1.16/srcm4/glibc21.m4
	modified:   tools/libiconv-1.16/srcm4/gnulib-cache.m4
	modified:   tools/libiconv-1.16/srcm4/gnulib-common.m4
	modified:   tools/libiconv-1.16/srcm4/gnulib-comp.m4
	modified:   tools/libiconv-1.16/srcm4/gnulib-tool.m4
	modified:   tools/libiconv-1.16/srcm4/host-cpu-c-abi.m4
	modified:   tools/libiconv-1.16/srcm4/iconv.m4
	modified:   tools/libiconv-1.16/srcm4/include_next.m4
	modified:   tools/libiconv-1.16/srcm4/intdiv0.m4
	modified:   tools/libiconv-1.16/srcm4/intl-thread-locale.m4
	modified:   tools/libiconv-1.16/srcm4/intl.m4
	modified:   tools/libiconv-1.16/srcm4/intldir.m4
	modified:   tools/libiconv-1.16/srcm4/intlmacosx.m4
	modified:   tools/libiconv-1.16/srcm4/intmax.m4
	modified:   tools/libiconv-1.16/srcm4/inttypes-pri.m4
	modified:   tools/libiconv-1.16/srcm4/inttypes_h.m4
	modified:   tools/libiconv-1.16/srcm4/largefile.m4
	modified:   tools/libiconv-1.16/srcm4/lcmessage.m4
	modified:   tools/libiconv-1.16/srcm4/lib-ld.m4
	modified:   tools/libiconv-1.16/srcm4/lib-link.m4
	modified:   tools/libiconv-1.16/srcm4/lib-prefix.m4
	modified:   tools/libiconv-1.16/srcm4/libunistring-base.m4
	modified:   tools/libiconv-1.16/srcm4/limits-h.m4
	modified:   tools/libiconv-1.16/srcm4/lock.m4
	modified:   tools/libiconv-1.16/srcm4/longlong.m4
	modified:   tools/libiconv-1.16/srcm4/lstat.m4
	modified:   tools/libiconv-1.16/srcm4/malloc.m4
	modified:   tools/libiconv-1.16/srcm4/malloca.m4
	modified:   tools/libiconv-1.16/srcm4/mbstate_t.m4
	modified:   tools/libiconv-1.16/srcm4/msvc-inval.m4
	modified:   tools/libiconv-1.16/srcm4/msvc-nothrow.m4
	modified:   tools/libiconv-1.16/srcm4/multiarch.m4
	modified:   tools/libiconv-1.16/srcm4/nls.m4
	modified:   tools/libiconv-1.16/srcm4/nocrash.m4
	modified:   tools/libiconv-1.16/srcm4/off_t.m4
	modified:   tools/libiconv-1.16/srcm4/pathmax.m4
	modified:   tools/libiconv-1.16/srcm4/po.m4
	modified:   tools/libiconv-1.16/srcm4/printf-posix.m4
	modified:   tools/libiconv-1.16/srcm4/progtest.m4
	modified:   tools/libiconv-1.16/srcm4/raise.m4
	modified:   tools/libiconv-1.16/srcm4/read.m4
	modified:   tools/libiconv-1.16/srcm4/readlink.m4
	modified:   tools/libiconv-1.16/srcm4/relocatable-lib.m4
	modified:   tools/libiconv-1.16/srcm4/relocatable.m4
	modified:   tools/libiconv-1.16/srcm4/safe-read.m4
	modified:   tools/libiconv-1.16/srcm4/setenv.m4
	modified:   tools/libiconv-1.16/srcm4/signal_h.m4
	modified:   tools/libiconv-1.16/srcm4/signalblocking.m4
	modified:   tools/libiconv-1.16/srcm4/sigpipe.m4
	modified:   tools/libiconv-1.16/srcm4/size_max.m4
	modified:   tools/libiconv-1.16/srcm4/ssize_t.m4
	modified:   tools/libiconv-1.16/srcm4/stat-time.m4
	modified:   tools/libiconv-1.16/srcm4/stat.m4
	modified:   tools/libiconv-1.16/srcm4/stdbool.m4
	modified:   tools/libiconv-1.16/srcm4/stddef_h.m4
	modified:   tools/libiconv-1.16/srcm4/stdint.m4
	modified:   tools/libiconv-1.16/srcm4/stdint_h.m4
	modified:   tools/libiconv-1.16/srcm4/stdio_h.m4
	modified:   tools/libiconv-1.16/srcm4/stdlib_h.m4
	modified:   tools/libiconv-1.16/srcm4/strerror.m4
	modified:   tools/libiconv-1.16/srcm4/string_h.m4
	modified:   tools/libiconv-1.16/srcm4/sys_socket_h.m4
	modified:   tools/libiconv-1.16/srcm4/sys_stat_h.m4
	modified:   tools/libiconv-1.16/srcm4/sys_types_h.m4
	modified:   tools/libiconv-1.16/srcm4/threadlib.m4
	modified:   tools/libiconv-1.16/srcm4/time_h.m4
	modified:   tools/libiconv-1.16/srcm4/uintmax_t.m4
	modified:   tools/libiconv-1.16/srcm4/unistd_h.m4
	modified:   tools/libiconv-1.16/srcm4/unlocked-io.m4
	modified:   tools/libiconv-1.16/srcm4/visibility.m4
	modified:   tools/libiconv-1.16/srcm4/warn-on-use.m4
	modified:   tools/libiconv-1.16/srcm4/wchar_t.m4
	modified:   tools/libiconv-1.16/srcm4/wint_t.m4
	modified:   tools/libiconv-1.16/srcm4/xsize.m4
	modified:   tools/libiconv-1.16/stamp-h1
	modified:   tools/libiconv-1.16/tests/ARMSCII-8.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/ARMSCII-8.TXT
	modified:   tools/libiconv-1.16/tests/ASCII.TXT
	modified:   tools/libiconv-1.16/tests/ATARIST.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-2003.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-2003.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-1999-snippet
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-1999-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-1999.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-1999.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2001-snippet
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2001-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2001.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2001.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2004-snippet
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2004-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2004.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2004.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2008-snippet
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2008-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2008.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/BIG5-HKSCS-2008.TXT
	modified:   tools/libiconv-1.16/tests/BIG5.TXT
	modified:   tools/libiconv-1.16/tests/CP1046.TXT
	modified:   tools/libiconv-1.16/tests/CP1124.TXT
	modified:   tools/libiconv-1.16/tests/CP1125.TXT
	modified:   tools/libiconv-1.16/tests/CP1129.TXT
	modified:   tools/libiconv-1.16/tests/CP1131.TXT
	modified:   tools/libiconv-1.16/tests/CP1133.TXT
	modified:   tools/libiconv-1.16/tests/CP1161.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/CP1161.TXT
	modified:   tools/libiconv-1.16/tests/CP1162.TXT
	modified:   tools/libiconv-1.16/tests/CP1163.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/CP1163.TXT
	modified:   tools/libiconv-1.16/tests/CP1250.TXT
	modified:   tools/libiconv-1.16/tests/CP1251.TXT
	modified:   tools/libiconv-1.16/tests/CP1252.TXT
	modified:   tools/libiconv-1.16/tests/CP1253.TXT
	modified:   tools/libiconv-1.16/tests/CP1254.TXT
	modified:   tools/libiconv-1.16/tests/CP1255-snippet
	modified:   tools/libiconv-1.16/tests/CP1255-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/CP1255.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/CP1255.TXT
	modified:   tools/libiconv-1.16/tests/CP1256.TXT
	modified:   tools/libiconv-1.16/tests/CP1257.TXT
	modified:   tools/libiconv-1.16/tests/CP1258-snippet
	modified:   tools/libiconv-1.16/tests/CP1258-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/CP1258.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/CP1258.TXT
	modified:   tools/libiconv-1.16/tests/CP437.TXT
	modified:   tools/libiconv-1.16/tests/CP737.TXT
	modified:   tools/libiconv-1.16/tests/CP775.TXT
	modified:   tools/libiconv-1.16/tests/CP850.TXT
	modified:   tools/libiconv-1.16/tests/CP852.TXT
	modified:   tools/libiconv-1.16/tests/CP853.TXT
	modified:   tools/libiconv-1.16/tests/CP855.TXT
	modified:   tools/libiconv-1.16/tests/CP856.TXT
	modified:   tools/libiconv-1.16/tests/CP857.TXT
	modified:   tools/libiconv-1.16/tests/CP858.TXT
	modified:   tools/libiconv-1.16/tests/CP860.TXT
	modified:   tools/libiconv-1.16/tests/CP861.TXT
	modified:   tools/libiconv-1.16/tests/CP862.TXT
	modified:   tools/libiconv-1.16/tests/CP863.TXT
	modified:   tools/libiconv-1.16/tests/CP864.TXT
	modified:   tools/libiconv-1.16/tests/CP865.TXT
	modified:   tools/libiconv-1.16/tests/CP866.TXT
	modified:   tools/libiconv-1.16/tests/CP869.TXT
	modified:   tools/libiconv-1.16/tests/CP874.TXT
	modified:   tools/libiconv-1.16/tests/CP922.TXT
	modified:   tools/libiconv-1.16/tests/CP932.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/CP932.TXT
	modified:   tools/libiconv-1.16/tests/CP936.TXT
	modified:   tools/libiconv-1.16/tests/CP949.TXT
	modified:   tools/libiconv-1.16/tests/CP950.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/CP950.TXT
	modified:   tools/libiconv-1.16/tests/DEC-HANYU.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/DEC-HANYU.TXT
	modified:   tools/libiconv-1.16/tests/DEC-KANJI.TXT
	modified:   tools/libiconv-1.16/tests/EUC-CN.TXT
	modified:   tools/libiconv-1.16/tests/EUC-JISX0213.TXT
	modified:   tools/libiconv-1.16/tests/EUC-JP.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/EUC-JP.TXT
	modified:   tools/libiconv-1.16/tests/EUC-KR.TXT
	modified:   tools/libiconv-1.16/tests/EUC-TW.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/EUC-TW.TXT
	modified:   tools/libiconv-1.16/tests/GB18030-BMP.TXT
	modified:   tools/libiconv-1.16/tests/GB18030.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/GBK.TXT
	modified:   tools/libiconv-1.16/tests/Georgian-Academy.TXT
	modified:   tools/libiconv-1.16/tests/Georgian-PS.TXT
	modified:   tools/libiconv-1.16/tests/HP-ROMAN8.TXT
	modified:   tools/libiconv-1.16/tests/HZ-snippet
	modified:   tools/libiconv-1.16/tests/HZ-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-CN-EXT-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-CN-EXT-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-CN-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-CN-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-1-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-1-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-2-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-2-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-3-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-3-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-MS-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-MS-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-MS-snippet.alt
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-JP-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-2022-KR-snippet
	modified:   tools/libiconv-1.16/tests/ISO-2022-KR-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/ISO-8859-1.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-10.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-11.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-13.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-14.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-15.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-16.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-2.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-3.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-4.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-5.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-6.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-7.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-8.TXT
	modified:   tools/libiconv-1.16/tests/ISO-8859-9.TXT
	modified:   tools/libiconv-1.16/tests/ISO-IR-165.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/ISO-IR-165.TXT
	modified:   tools/libiconv-1.16/tests/ISO646-CN.TXT
	modified:   tools/libiconv-1.16/tests/ISO646-JP.TXT
	modified:   tools/libiconv-1.16/tests/JIS_X0201.TXT
	modified:   tools/libiconv-1.16/tests/JOHAB.TXT
	modified:   tools/libiconv-1.16/tests/KOI8-R.TXT
	modified:   tools/libiconv-1.16/tests/KOI8-RU.TXT
	modified:   tools/libiconv-1.16/tests/KOI8-T.TXT
	modified:   tools/libiconv-1.16/tests/KOI8-U.TXT
	modified:   tools/libiconv-1.16/tests/MacArabic.TXT
	modified:   tools/libiconv-1.16/tests/MacCentralEurope.TXT
	modified:   tools/libiconv-1.16/tests/MacCroatian.TXT
	modified:   tools/libiconv-1.16/tests/MacCyrillic.TXT
	modified:   tools/libiconv-1.16/tests/MacGreek.TXT
	modified:   tools/libiconv-1.16/tests/MacHebrew.TXT
	modified:   tools/libiconv-1.16/tests/MacIceland.TXT
	modified:   tools/libiconv-1.16/tests/MacRoman.TXT
	modified:   tools/libiconv-1.16/tests/MacRomania.TXT
	modified:   tools/libiconv-1.16/tests/MacThai.TXT
	modified:   tools/libiconv-1.16/tests/MacTurkish.TXT
	modified:   tools/libiconv-1.16/tests/MacUkraine.TXT
	modified:   tools/libiconv-1.16/tests/Makefile
	modified:   tools/libiconv-1.16/tests/Makefile.in
	modified:   tools/libiconv-1.16/tests/MuleLao-1.TXT
	modified:   tools/libiconv-1.16/tests/NEXTSTEP.TXT
	modified:   tools/libiconv-1.16/tests/PT154.TXT
	modified:   tools/libiconv-1.16/tests/Quotes.ASCII
	modified:   tools/libiconv-1.16/tests/Quotes.ISO-8859-1
	modified:   tools/libiconv-1.16/tests/Quotes.UTF-8
	modified:   tools/libiconv-1.16/tests/RISCOS-LATIN1.TXT
	modified:   tools/libiconv-1.16/tests/RK1048.TXT
	modified:   tools/libiconv-1.16/tests/SHIFT_JIS.TXT
	modified:   tools/libiconv-1.16/tests/SHIFT_JISX0213.TXT
	modified:   tools/libiconv-1.16/tests/TCVN-snippet
	modified:   tools/libiconv-1.16/tests/TCVN-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/TCVN.IRREVERSIBLE.TXT
	modified:   tools/libiconv-1.16/tests/TCVN.TXT
	modified:   tools/libiconv-1.16/tests/TDS565.TXT
	modified:   tools/libiconv-1.16/tests/TIS-620.TXT
	modified:   tools/libiconv-1.16/tests/Translit1.ASCII
	modified:   tools/libiconv-1.16/tests/Translit1.ISO-8859-1
	modified:   tools/libiconv-1.16/tests/TranslitFail1.ISO-8859-1
	modified:   tools/libiconv-1.16/tests/UCS-2BE-snippet
	modified:   tools/libiconv-1.16/tests/UCS-2BE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UCS-2LE-snippet
	modified:   tools/libiconv-1.16/tests/UCS-2LE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UCS-4BE-snippet
	modified:   tools/libiconv-1.16/tests/UCS-4BE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UCS-4LE-snippet
	modified:   tools/libiconv-1.16/tests/UCS-4LE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UTF-16-snippet
	modified:   tools/libiconv-1.16/tests/UTF-16-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UTF-16BE-snippet
	modified:   tools/libiconv-1.16/tests/UTF-16BE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UTF-16LE-snippet
	modified:   tools/libiconv-1.16/tests/UTF-16LE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UTF-32-snippet
	modified:   tools/libiconv-1.16/tests/UTF-32-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UTF-32BE-snippet
	modified:   tools/libiconv-1.16/tests/UTF-32BE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UTF-32LE-snippet
	modified:   tools/libiconv-1.16/tests/UTF-32LE-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/UTF-7-snippet
	modified:   tools/libiconv-1.16/tests/UTF-7-snippet.UTF-8
	modified:   tools/libiconv-1.16/tests/VISCII.TXT
	modified:   tools/libiconv-1.16/tests/check-stateful.bat
	modified:   tools/libiconv-1.16/tests/check-stateless.bat
	modified:   tools/libiconv-1.16/tests/check-translit.bat
	modified:   tools/libiconv-1.16/tests/gengb18030z.c
	modified:   tools/libiconv-1.16/tests/genutf8.c
	modified:   tools/libiconv-1.16/tests/table-from.c
	modified:   tools/libiconv-1.16/tests/table-to.c
	modified:   tools/libiconv-1.16/tests/test-shiftseq.c
	modified:   tools/libiconv-1.16/tests/test-to-wchar.c
	modified:   tools/libiconv-1.16/tests/uniq-u.c
	modified:   tools/libiconv-1.16/tools/8bit_tab_to_h.c
	modified:   tools/libiconv-1.16/tools/CP50221-0208-EXT.TXT
	modified:   tools/libiconv-1.16/tools/CP50221-0212-EXT.TXT
	modified:   tools/libiconv-1.16/tools/JISX0213.TXT
	modified:   tools/libiconv-1.16/tools/Makefile
	modified:   tools/libiconv-1.16/tools/cjk_tab_to_h.c
	modified:   tools/libiconv-1.16/tools/cjk_variants.c
	modified:   tools/libiconv-1.16/windows/iconv.rc
	modified:   tools/libiconv-1.16/windows/libiconv.rc
	modified:   tools/libiconv-1.16/woe32dll/export.h
	modified:   tools/libiconv-1.16/woe32dll/iconv-exports.c
	modified:   tools/mmap_exam/mmap_ext.c
	modified:   tools/rs4xx/.cproject
	modified:   tools/rs4xx/.project
	modified:   tools/rs4xx/.settings/language.settings.xml
	modified:   tools/rs4xx/.settings/org.eclipse.cdt.core.prefs
	modified:   tools/rs4xx/Debug/makefile
	modified:   tools/rs4xx/Debug/objects.mk
	modified:   tools/rs4xx/Debug/src/CfgManager.d
	modified:   tools/rs4xx/Debug/src/CfgManager.o
	modified:   tools/rs4xx/Debug/src/Common.d
	modified:   tools/rs4xx/Debug/src/ConsoleManager.d
	modified:   tools/rs4xx/Debug/src/ConsoleManager.o
	modified:   tools/rs4xx/Debug/src/DBManager.d
	modified:   tools/rs4xx/Debug/src/DBManager.o
	modified:   tools/rs4xx/Debug/src/Device/HMI/_2X68P~X.D
	modified:   tools/rs4xx/Debug/src/Device/ModbusRTU/_2X68P~X.D
	modified:   tools/rs4xx/Debug/src/PCInterface/_2X68P~X.D
	modified:   tools/rs4xx/Debug/src/SVTransmit.d
	modified:   tools/rs4xx/Debug/src/SVTransmit.o
	modified:   tools/rs4xx/Debug/src/VT100.d
	modified:   tools/rs4xx/Debug/src/VT100.o
	modified:   tools/rs4xx/Debug/src/_2X68P~X.D
	modified:   tools/rs4xx/Debug/src/main.d
	modified:   tools/rs4xx/Debug/src/main.o
	modified:   tools/rs4xx/Debug/src/subdir.mk
	modified:   tools/rs4xx/Makefile
	modified:   tools/rs4xx/include/sqlite.h
	modified:   tools/rs4xx/include/sqlite3.h
	modified:   tools/rs4xx/include/sqlite3ext.h
	modified:   tools/rs4xx/libs/libsqlite3.so
	modified:   tools/rs4xx/libs/libsqlite3.so.0
	modified:   tools/rs4xx/libs/libsqlite3.so.0.8.6
	modified:   tools/rs4xx/libs/libticmem.a
	modified:   tools/rs4xx/libs/libtiipc.a
	modified:   tools/rs4xx/libs/libtiipcutils.a
	modified:   tools/rs4xx/libs/libtitransportrpmsg.a
	modified:   tools/rs4xx/src/CfgManager.c
	modified:   tools/rs4xx/src/CfgManager.h
	modified:   tools/rs4xx/src/Common.c
	modified:   tools/rs4xx/src/Common.h
	modified:   tools/rs4xx/src/Common.o
	modified:   tools/rs4xx/src/ConsoleManager.c
	modified:   tools/rs4xx/src/ConsoleManager.h
	modified:   tools/rs4xx/src/DBManager.c
	modified:   tools/rs4xx/src/DBManager.h
	modified:   tools/rs4xx/src/SVTransmit.c
	modified:   tools/rs4xx/src/SVTransmit.h
	modified:   tools/rs4xx/src/VT100.c
	modified:   tools/rs4xx/src/VT100.h
	modified:   tools/rs4xx/src/build_defs.h
	modified:   tools/rs4xx/src/global.h
	modified:   tools/vsftpd-3.0.3/.ftpcmdio.h.swp
	modified:   tools/vsftpd-3.0.3/AUDIT
	modified:   tools/vsftpd-3.0.3/BENCHMARKS
	modified:   tools/vsftpd-3.0.3/BUGS
	modified:   tools/vsftpd-3.0.3/COPYING
	modified:   tools/vsftpd-3.0.3/COPYRIGHT
	modified:   tools/vsftpd-3.0.3/Changelog
	modified:   tools/vsftpd-3.0.3/EXAMPLE/INTERNET_SITE/README
	modified:   tools/vsftpd-3.0.3/EXAMPLE/INTERNET_SITE/vsftpd.conf
	modified:   tools/vsftpd-3.0.3/EXAMPLE/INTERNET_SITE/vsftpd.xinetd
	modified:   tools/vsftpd-3.0.3/EXAMPLE/INTERNET_SITE_NOINETD/README
	modified:   tools/vsftpd-3.0.3/EXAMPLE/INTERNET_SITE_NOINETD/vsftpd.conf
	modified:   tools/vsftpd-3.0.3/EXAMPLE/PER_IP_CONFIG/README
	modified:   tools/vsftpd-3.0.3/EXAMPLE/PER_IP_CONFIG/hosts.allow
	modified:   tools/vsftpd-3.0.3/EXAMPLE/README
	modified:   tools/vsftpd-3.0.3/EXAMPLE/VIRTUAL_HOSTS/README
	modified:   tools/vsftpd-3.0.3/EXAMPLE/VIRTUAL_USERS/README
	modified:   tools/vsftpd-3.0.3/EXAMPLE/VIRTUAL_USERS/vsftpd.conf
	modified:   tools/vsftpd-3.0.3/EXAMPLE/VIRTUAL_USERS/vsftpd.pam
	modified:   tools/vsftpd-3.0.3/EXAMPLE/VIRTUAL_USERS_2/README
	modified:   tools/vsftpd-3.0.3/FAQ
	modified:   tools/vsftpd-3.0.3/INSTALL
	modified:   tools/vsftpd-3.0.3/LICENSE
	modified:   tools/vsftpd-3.0.3/Makefile
	modified:   tools/vsftpd-3.0.3/README
	modified:   tools/vsftpd-3.0.3/README.security
	modified:   tools/vsftpd-3.0.3/README.ssl
	modified:   tools/vsftpd-3.0.3/REFS
	modified:   tools/vsftpd-3.0.3/REWARD
	modified:   tools/vsftpd-3.0.3/RedHat/README.spec
	modified:   tools/vsftpd-3.0.3/RedHat/vsftpd.log
	modified:   tools/vsftpd-3.0.3/RedHat/vsftpd.pam
	modified:   tools/vsftpd-3.0.3/SECURITY/DESIGN
	modified:   tools/vsftpd-3.0.3/SECURITY/IMPLEMENTATION
	modified:   tools/vsftpd-3.0.3/SECURITY/OVERVIEW
	modified:   tools/vsftpd-3.0.3/SECURITY/TRUST
	modified:   tools/vsftpd-3.0.3/SIZE
	modified:   tools/vsftpd-3.0.3/SPEED
	modified:   tools/vsftpd-3.0.3/TODO
	modified:   tools/vsftpd-3.0.3/TUNING
	modified:   tools/vsftpd-3.0.3/access.c
	modified:   tools/vsftpd-3.0.3/access.h
	modified:   tools/vsftpd-3.0.3/access.o
	modified:   tools/vsftpd-3.0.3/ascii.c
	modified:   tools/vsftpd-3.0.3/ascii.h
	modified:   tools/vsftpd-3.0.3/ascii.o
	modified:   tools/vsftpd-3.0.3/banner.c
	modified:   tools/vsftpd-3.0.3/banner.h
	modified:   tools/vsftpd-3.0.3/banner.o
	modified:   tools/vsftpd-3.0.3/builddefs.h
	modified:   tools/vsftpd-3.0.3/defs.h
	modified:   tools/vsftpd-3.0.3/dummyinc/crypt.h
	modified:   tools/vsftpd-3.0.3/dummyinc/openssl/ssl.h
	modified:   tools/vsftpd-3.0.3/dummyinc/security/pam_appl.h
	modified:   tools/vsftpd-3.0.3/dummyinc/shadow.h
	modified:   tools/vsftpd-3.0.3/dummyinc/sys/capability.h
	modified:   tools/vsftpd-3.0.3/dummyinc/sys/prctl.h
	modified:   tools/vsftpd-3.0.3/dummyinc/sys/sendfile.h
	modified:   tools/vsftpd-3.0.3/dummyinc/utmpx.h
	modified:   tools/vsftpd-3.0.3/features.c
	modified:   tools/vsftpd-3.0.3/features.h
	modified:   tools/vsftpd-3.0.3/features.o
	modified:   tools/vsftpd-3.0.3/filesize.h
	modified:   tools/vsftpd-3.0.3/filestr.c
	modified:   tools/vsftpd-3.0.3/filestr.h
	modified:   tools/vsftpd-3.0.3/filestr.o
	modified:   tools/vsftpd-3.0.3/ftpcmdio.c
	modified:   tools/vsftpd-3.0.3/ftpcmdio.h
	modified:   tools/vsftpd-3.0.3/ftpcmdio.o
	modified:   tools/vsftpd-3.0.3/ftpcodes.h
	modified:   tools/vsftpd-3.0.3/ftpdataio.c
	modified:   tools/vsftpd-3.0.3/ftpdataio.h
	modified:   tools/vsftpd-3.0.3/ftpdataio.o
	modified:   tools/vsftpd-3.0.3/ftppolicy.c
	modified:   tools/vsftpd-3.0.3/ftppolicy.h
	modified:   tools/vsftpd-3.0.3/ftppolicy.o
	modified:   tools/vsftpd-3.0.3/hash.c
	modified:   tools/vsftpd-3.0.3/hash.h
	modified:   tools/vsftpd-3.0.3/hash.o
	modified:   tools/vsftpd-3.0.3/ipaddrparse.c
	modified:   tools/vsftpd-3.0.3/ipaddrparse.h
	modified:   tools/vsftpd-3.0.3/ipaddrparse.o
	modified:   tools/vsftpd-3.0.3/logging.c
	modified:   tools/vsftpd-3.0.3/logging.h
	modified:   tools/vsftpd-3.0.3/logging.o
	modified:   tools/vsftpd-3.0.3/ls.c
	modified:   tools/vsftpd-3.0.3/ls.h
	modified:   tools/vsftpd-3.0.3/ls.o
	modified:   tools/vsftpd-3.0.3/main.c
	modified:   tools/vsftpd-3.0.3/main.o
	modified:   tools/vsftpd-3.0.3/netstr.c
	modified:   tools/vsftpd-3.0.3/netstr.h
	modified:   tools/vsftpd-3.0.3/netstr.o
	modified:   tools/vsftpd-3.0.3/oneprocess.c
	modified:   tools/vsftpd-3.0.3/oneprocess.h
	modified:   tools/vsftpd-3.0.3/oneprocess.o
	modified:   tools/vsftpd-3.0.3/opts.c
	modified:   tools/vsftpd-3.0.3/opts.h
	modified:   tools/vsftpd-3.0.3/opts.o
	modified:   tools/vsftpd-3.0.3/parseconf.c
	modified:   tools/vsftpd-3.0.3/parseconf.h
	modified:   tools/vsftpd-3.0.3/parseconf.o
	modified:   tools/vsftpd-3.0.3/port/aix_bogons.h
	modified:   tools/vsftpd-3.0.3/port/cmsg_extras.h
	modified:   tools/vsftpd-3.0.3/port/dirfd_extras.h
	modified:   tools/vsftpd-3.0.3/port/hpux_bogons.h
	modified:   tools/vsftpd-3.0.3/port/irix_bogons.h
	modified:   tools/vsftpd-3.0.3/port/porting_junk.h
	modified:   tools/vsftpd-3.0.3/port/solaris_bogons.h
	modified:   tools/vsftpd-3.0.3/port/tru64_bogons.h
	modified:   tools/vsftpd-3.0.3/postlogin.c
	modified:   tools/vsftpd-3.0.3/postlogin.h
	modified:   tools/vsftpd-3.0.3/postlogin.o
	modified:   tools/vsftpd-3.0.3/postprivparent.c
	modified:   tools/vsftpd-3.0.3/postprivparent.h
	modified:   tools/vsftpd-3.0.3/postprivparent.o
	modified:   tools/vsftpd-3.0.3/prelogin.c
	modified:   tools/vsftpd-3.0.3/prelogin.h
	modified:   tools/vsftpd-3.0.3/prelogin.o
	modified:   tools/vsftpd-3.0.3/privops.c
	modified:   tools/vsftpd-3.0.3/privops.h
	modified:   tools/vsftpd-3.0.3/privops.o
	modified:   tools/vsftpd-3.0.3/privsock.c
	modified:   tools/vsftpd-3.0.3/privsock.h
	modified:   tools/vsftpd-3.0.3/privsock.o
	modified:   tools/vsftpd-3.0.3/ptracesandbox.c
	modified:   tools/vsftpd-3.0.3/ptracesandbox.h
	modified:   tools/vsftpd-3.0.3/ptracesandbox.o
	modified:   tools/vsftpd-3.0.3/readwrite.c
	modified:   tools/vsftpd-3.0.3/readwrite.h
	modified:   tools/vsftpd-3.0.3/readwrite.o
	modified:   tools/vsftpd-3.0.3/secbuf.c
	modified:   tools/vsftpd-3.0.3/secbuf.h
	modified:   tools/vsftpd-3.0.3/secbuf.o
	modified:   tools/vsftpd-3.0.3/seccompsandbox.c
	modified:   tools/vsftpd-3.0.3/seccompsandbox.h
	modified:   tools/vsftpd-3.0.3/seccompsandbox.o
	modified:   tools/vsftpd-3.0.3/secutil.c
	modified:   tools/vsftpd-3.0.3/secutil.h
	modified:   tools/vsftpd-3.0.3/secutil.o
	modified:   tools/vsftpd-3.0.3/session.h
	modified:   tools/vsftpd-3.0.3/ssl.c
	modified:   tools/vsftpd-3.0.3/ssl.h
	modified:   tools/vsftpd-3.0.3/ssl.o
	modified:   tools/vsftpd-3.0.3/sslslave.c
	modified:   tools/vsftpd-3.0.3/sslslave.h
	modified:   tools/vsftpd-3.0.3/sslslave.o
	modified:   tools/vsftpd-3.0.3/standalone.c
	modified:   tools/vsftpd-3.0.3/standalone.h
	modified:   tools/vsftpd-3.0.3/standalone.o
	modified:   tools/vsftpd-3.0.3/str.c
	modified:   tools/vsftpd-3.0.3/str.h
	modified:   tools/vsftpd-3.0.3/str.o
	modified:   tools/vsftpd-3.0.3/strlist.c
	modified:   tools/vsftpd-3.0.3/strlist.h
	modified:   tools/vsftpd-3.0.3/strlist.o
	modified:   tools/vsftpd-3.0.3/sysdeputil.c
	modified:   tools/vsftpd-3.0.3/sysdeputil.h
	modified:   tools/vsftpd-3.0.3/sysdeputil.o
	modified:   tools/vsftpd-3.0.3/sysstr.c
	modified:   tools/vsftpd-3.0.3/sysstr.h
	modified:   tools/vsftpd-3.0.3/sysstr.o
	modified:   tools/vsftpd-3.0.3/sysutil.c
	modified:   tools/vsftpd-3.0.3/sysutil.h
	modified:   tools/vsftpd-3.0.3/sysutil.o
	modified:   tools/vsftpd-3.0.3/tcpwrap.c
	modified:   tools/vsftpd-3.0.3/tcpwrap.h
	modified:   tools/vsftpd-3.0.3/tcpwrap.o
	modified:   tools/vsftpd-3.0.3/tunables.c
	modified:   tools/vsftpd-3.0.3/tunables.h
	modified:   tools/vsftpd-3.0.3/tunables.o
	modified:   tools/vsftpd-3.0.3/twoprocess.c
	modified:   tools/vsftpd-3.0.3/twoprocess.h
	modified:   tools/vsftpd-3.0.3/twoprocess.o
	modified:   tools/vsftpd-3.0.3/utility.c
	modified:   tools/vsftpd-3.0.3/utility.h
	modified:   tools/vsftpd-3.0.3/utility.o
	modified:   tools/vsftpd-3.0.3/vsftpd.8
	modified:   tools/vsftpd-3.0.3/vsftpd.conf
	modified:   tools/vsftpd-3.0.3/vsftpd.conf.5
	modified:   tools/vsftpd-3.0.3/vsftpver.h
	modified:   tools/vsftpd-3.0.3/xinetd.d/vsftpd
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52.tar.gz
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/AUTHORS
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/COPYING
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/INSTALL
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/cgi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/access_log.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/auth.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/cgi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/cml.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/compress.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/debug.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/dirlisting.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/evhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/expire.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/fastcgi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/geoip.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/magnet.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/mime.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/mod.template
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/mysql_vhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/proxy.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/rrdtool.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/scgi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/secdownload.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/simple_vhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/ssi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/status.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/trigger_b4_dl.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/userdir.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/conf.d/webdav.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/lighttpd.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/modules.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/vhosts.d/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/vhosts.d/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/vhosts.d/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/JohnCfg/vhosts.d/vhosts.template
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/NEWS
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/README
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/README.FreeBSD
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/SConstruct
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/aclocal.m4
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/config.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/config.h.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/config.log
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/configure.ac
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/distribute.sh
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/distribute.sh.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/access_log.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/auth.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/cgi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/cml.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/compress.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/debug.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/dirlisting.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/evhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/expire.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/fastcgi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/geoip.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/magnet.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/mime.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/mod.template
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/mysql_vhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/proxy.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/rrdtool.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/scgi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/secdownload.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/simple_vhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/ssi.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/status.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/trigger_b4_dl.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/userdir.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/conf.d/webdav.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/lighttpd.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/modules.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/vhosts.d/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/vhosts.d/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/vhosts.d/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/config/vhosts.d/vhosts.template
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/lighttpd-angel.8
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/lighttpd.8
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/newstyle.css
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/oldstyle.css
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/outdated/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/outdated/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/outdated/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/outdated/fastcgi-state.dot
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/outdated/state.dot
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/scripts/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/scripts/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/scripts/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/systemd/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/systemd/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/systemd/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/doc/systemd/lighttpd.service
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/ltmain.sh
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/m4/libtool.m4
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/m4/ltoptions.m4
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/m4/ltsugar.m4
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/m4/ltversion.m4
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/m4/lt~obsolete.m4
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/meson.build
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/scripts/cmake/FindLibEV.cmake
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/scripts/cmake/LighttpdMacros.cmake
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/scripts/m4/ax_prog_cc_for_build.m4
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/array.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/base64.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/buffer.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/burl.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/data_array.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/data_config.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/data_integer.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/data_string.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/http_header.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/http_kv.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-algo_sha1.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-array.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-base64.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-buffer.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-burl.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-chunk.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-configfile-glue.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-connections-glue.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-crc32.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-data_array.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-data_config.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-data_integer.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-data_string.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-etag.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent_freebsd_kqueue.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent_libev.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent_linux_sysepoll.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent_poll.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent_select.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent_solaris_devpoll.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-fdevent_solaris_port.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-gw_backend.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-http-header-glue.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-http_auth.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-http_chunk.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-http_header.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-http_kv.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-http_vhostdb.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-joblist.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-keyvalue.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-log.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-md5.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-plugin.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-rand.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-request.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-safe_memclear.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-sock_addr.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-splaytree.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-stat_cache.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-stream.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/liblightcomp_la-vector.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-algo_sha1.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-angel.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-array.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-base64.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-buffer.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-burl.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-chunk.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-configfile-glue.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-configfile.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-configparser.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-connections-glue.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-connections.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-crc32.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-data_array.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-data_config.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-data_integer.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-data_string.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-etag.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent_freebsd_kqueue.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent_libev.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent_linux_sysepoll.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent_poll.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent_select.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent_solaris_devpoll.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-fdevent_solaris_port.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-gw_backend.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-http-header-glue.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-http_auth.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-http_chunk.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-http_header.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-http_kv.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-http_vhostdb.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-inet_ntop_cache.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-joblist.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-keyvalue.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-log.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-md5.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_access.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_accesslog.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_alias.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_auth.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_authn_file.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_authn_gssapi.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_authn_ldap.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_authn_mysql.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_authn_pam.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_cgi.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_cml.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_cml_funcs.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_cml_lua.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_compress.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_deflate.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_dirlisting.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_evasive.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_expire.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_extforward.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_fastcgi.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_flv_streaming.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_geoip.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_indexfile.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_magnet.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_magnet_cache.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_mysql_vhost.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_openssl.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_proxy.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_redirect.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_rewrite.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_rrdtool.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_scgi.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_secdownload.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_setenv.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_simple_vhost.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_ssi.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_ssi_expr.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_ssi_exprparser.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_staticfile.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_status.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_trigger_b4_dl.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_uploadprogress.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_userdir.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_usertrack.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_vhostdb.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_vhostdb_dbi.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_vhostdb_ldap.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_vhostdb_mysql.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_vhostdb_pgsql.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-mod_webdav.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-network.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-network_write.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-plugin.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-rand.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-request.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-response.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-safe_memclear.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-server.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-sock_addr.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-splaytree.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-stat_cache.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-stream.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/lighttpd-vector.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/log.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_access.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_accesslog.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_alias.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_auth.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_authn_file.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_authn_gssapi.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_authn_ldap.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_authn_mysql_la-mod_authn_mysql.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_authn_pam.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_authn_sasl_la-mod_authn_sasl.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_cgi.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_cml_la-mod_cml.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_cml_la-mod_cml_funcs.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_cml_la-mod_cml_lua.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_compress.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_deflate.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_dirlisting.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_evasive.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_evhost.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_expire.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_extforward.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_fastcgi.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_flv_streaming.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_geoip.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_indexfile.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_magnet_la-mod_magnet.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_magnet_la-mod_magnet_cache.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_mysql_vhost_la-mod_mysql_vhost.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_openssl.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_proxy.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_redirect.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_rewrite.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_rrdtool.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_scgi.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_secdownload.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_setenv.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_simple_vhost.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_sockproxy.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_ssi.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_ssi_expr.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_ssi_exprparser.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_staticfile.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_status.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_trigger_b4_dl.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_uploadprogress.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_userdir.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_usertrack.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_vhostdb.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_vhostdb_dbi_la-mod_vhostdb_dbi.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_vhostdb_ldap.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_vhostdb_mysql_la-mod_vhostdb_mysql.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_vhostdb_pgsql_la-mod_vhostdb_pgsql.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_webdav_la-mod_webdav.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/mod_wstunnel.Plo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/request.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/sock_addr.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.deps/vector.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_access.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_access.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_accesslog.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_accesslog.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_alias.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_alias.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_auth.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_auth.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_authn_file.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_authn_file.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_cgi.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_cgi.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_compress.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_compress.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_deflate.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_deflate.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_dirlisting.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_dirlisting.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_evasive.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_evasive.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_evhost.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_evhost.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_expire.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_expire.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_extforward.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_extforward.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_fastcgi.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_fastcgi.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_flv_streaming.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_flv_streaming.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_indexfile.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_indexfile.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_proxy.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_proxy.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_redirect.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_redirect.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_rewrite.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_rewrite.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_rrdtool.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_rrdtool.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_scgi.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_scgi.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_secdownload.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_secdownload.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_setenv.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_setenv.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_simple_vhost.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_simple_vhost.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_sockproxy.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_sockproxy.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_ssi.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_ssi.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_ssi_expr.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_ssi_exprparser.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_staticfile.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_staticfile.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_status.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_status.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_uploadprogress.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_uploadprogress.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_userdir.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_userdir.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_usertrack.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_usertrack.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_vhostdb.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_vhostdb.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_webdav.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_webdav_la-mod_webdav.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_wstunnel.lai
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/.libs/mod_wstunnel.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/SConscript
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/algo_sha1.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/algo_sha1.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/array.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/array.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/array.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/base.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/base64.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/base64.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/base64.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/base_decls.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/buffer.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/buffer.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/buffer.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/burl.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/burl.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/burl.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/chunk.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/chunk.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/config.h.cmake
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/configfile-glue.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/configfile.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/configfile.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/configparser.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/configparser.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/configparser.y
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/connections-glue.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/connections.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/connections.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/crc32.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/crc32.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_array.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_array.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_config.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_config.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_integer.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_integer.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_string.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/data_string.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/etag.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/etag.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fastcgi.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_freebsd_kqueue.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_impl.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_libev.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_linux_sysepoll.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_poll.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_select.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_solaris_devpoll.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/fdevent_solaris_port.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/first.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/gw_backend.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/gw_backend.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http-header-glue.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_auth.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_auth.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_chunk.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_chunk.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_header.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_header.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_header.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_kv.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_kv.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_kv.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_vhostdb.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/http_vhostdb.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/inet_ntop_cache.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/inet_ntop_cache.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/joblist.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/joblist.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/keyvalue.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/keyvalue.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lemon.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lempar.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-algo_sha1.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-angel.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-angel.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-array.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-base64.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-buffer.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-burl.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-chunk.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-configfile-glue.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-configfile.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-configparser.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-connections-glue.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-connections.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-crc32.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-data_array.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-data_config.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-data_integer.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-data_string.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-etag.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent_freebsd_kqueue.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent_libev.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent_linux_sysepoll.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent_poll.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent_select.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent_solaris_devpoll.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-fdevent_solaris_port.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-gw_backend.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-http-header-glue.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-http_auth.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-http_chunk.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-http_header.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-http_kv.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-http_vhostdb.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-inet_ntop_cache.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-joblist.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-keyvalue.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-log.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-md5.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-network.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-network_write.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-plugin.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-rand.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-request.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-response.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-safe_memclear.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-server.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-sock_addr.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-splaytree.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-stat_cache.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-stream.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/lighttpd-vector.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/log.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/log.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/log.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/md5.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/md5.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/meson.build
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_access.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_access.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_access.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_accesslog.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_accesslog.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_accesslog.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_alias.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_alias.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_alias.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_auth.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_auth.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_auth.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_file.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_file.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_file.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_gssapi.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_ldap.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_mysql.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_pam.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_authn_sasl.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cgi.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cgi.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cgi.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cml.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cml.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cml_funcs.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cml_funcs.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_cml_lua.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_compress.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_compress.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_compress.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_deflate.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_deflate.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_deflate.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_dirlisting.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_dirlisting.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_dirlisting.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_evasive.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_evasive.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_evasive.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_evhost.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_evhost.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_evhost.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_expire.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_expire.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_expire.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_extforward.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_extforward.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_extforward.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_fastcgi.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_fastcgi.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_fastcgi.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_flv_streaming.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_flv_streaming.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_flv_streaming.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_geoip.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_indexfile.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_indexfile.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_indexfile.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_magnet.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_magnet_cache.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_magnet_cache.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_mysql_vhost.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_openssl.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_proxy.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_proxy.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_proxy.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_redirect.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_redirect.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_redirect.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_rewrite.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_rewrite.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_rewrite.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_rrdtool.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_rrdtool.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_rrdtool.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_scgi.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_scgi.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_scgi.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_secdownload.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_secdownload.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_secdownload.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_setenv.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_setenv.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_setenv.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_simple_vhost.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_simple_vhost.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_simple_vhost.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_skeleton.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_sockproxy.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_sockproxy.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_sockproxy.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi_expr.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi_expr.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi_expr.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi_exprparser.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi_exprparser.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi_exprparser.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_ssi_exprparser.y
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_staticfile.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_staticfile.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_staticfile.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_status.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_status.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_status.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_trigger_b4_dl.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_uploadprogress.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_uploadprogress.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_uploadprogress.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_userdir.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_userdir.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_userdir.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_usertrack.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_usertrack.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_usertrack.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_vhostdb.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_vhostdb.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_vhostdb.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_vhostdb_dbi.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_vhostdb_ldap.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_vhostdb_mysql.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_vhostdb_pgsql.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_webdav.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_webdav.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_webdav_la-mod_webdav.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_wstunnel.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_wstunnel.la
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/mod_wstunnel.lo
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/network.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/network.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/network_write.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/network_write.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/plugin.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/plugin.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/rand.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/rand.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/request.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/request.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/request.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/response.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/response.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/safe_memclear.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/safe_memclear.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/server.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/server.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/settings.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sock_addr.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sock_addr.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sock_addr.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/splaytree.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/splaytree.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/stat_cache.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/stat_cache.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/status_counter.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/stream.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/stream.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sys-crypto.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sys-endian.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sys-mmap.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sys-socket.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/sys-strings.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.deps/.dirstamp
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.deps/test_array.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.deps/test_base64.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.deps/test_buffer.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.deps/test_burl.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.deps/test_configfile.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.deps/test_request.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/.dirstamp
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_array.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_array.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_base64.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_base64.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_buffer.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_buffer.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_burl.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_burl.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_configfile.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_configfile.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_request.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/t/test_request.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/vector.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/vector.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/vector.o
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/src/versionstamp.h
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/stamp-h1
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/.deps/fcgi-auth.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/.deps/fcgi-responder.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/.deps/scgi-responder.Po
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/404-handler.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/LightyTest.pm
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/SConscript
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/bug-06.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/bug-12.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/condition.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/123/12345.html
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/123/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/123/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/123/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/123/dummyfile.bla
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/123/phpinfo.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/404.html
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/exec-date.shtml
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/expire/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/expire/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/expire/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/get-env.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/get-server-env.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/go/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/go/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/go/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/index.html
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/indexfile/Makefile
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/indexfile/Makefile.am
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/indexfile/Makefile.in
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/indexfile/index.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/indexfile/return-404.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/indexfile/rewrite.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/phpinfo.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/prefix.fcgi
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/redirect.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/sendfile.php
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/ssi-include.shtml
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/docroot/www/ssi.shtml
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/fastcgi-10.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/fastcgi-13.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/fastcgi-auth.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/fastcgi-responder.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/fcgi-auth.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/fcgi-responder.c
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/lighttpd.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/lighttpd.htpasswd
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/lighttpd.user
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/lowercase.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/meson.build
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/mod-compress.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/mod-evhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/mod-extforward.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/mod-simplevhost.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/proxy.conf
	modified:   tools/web-server/lighttpd/lighttpd-1.4.52/tests/scgi-responder.c
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

