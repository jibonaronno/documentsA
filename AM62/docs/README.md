# Trismed Yocto Repository

This repository contains Yocto configurations and changes specific to the Trismed project. 


## Cloning and Building

To clone and build the repository, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone http://192.168.10.251/Bonobo.Git.Server/yocto-trismed.git
   ```

2. **Navigate to the Project Directory:**
   ```bash
   cd yocto-trismed
   ```

3. **Fetch Layers from Yocto, TI, Variscite and Trismed (192.168.10.251) Servers:**
It receives the username and password as argument to acces the git repository
   ```bash
   ./FetchAll.sh ronny superStrongPassword
   ```
**Note:** 'FetchAll.sh' must only be run one time!

Latest updated from varigit: ba01aeb688ffab6e38d6b02d1c30d8bea1c8a1aa

This will create 'meta-trismed' and 'var-ti-yocto'.
- var-ti-yocto: contains Yocto relesed by Variscite (no changes made)
- meta-trismed: contains Trismed's modifications

It will also:
- Configure the 'conf/bblayers.conf' adding 'meta-trismed' layer.
- Add the MACHINE to 'am62x-var-som' in 'conf/local.conf' so that it is no longer required when building images or sdk.

### Environment Setup

Before building, you need to prepare the environment. After every reboot or in a new terminal session, run:

```bash
. conf/setenv
```

#### Note for Ubuntu 24.04 Users:
After each reboot, execute the following command to avoid AppArmor restrictions:

```bash
echo 0 | sudo tee /proc/sys/kernel/apparmor_restrict_unprivileged_userns
```

**Note:** After any bitbake build or failure, use the following command to kill all remaining process before trying to build again:
```bash
pkill -f bitbake
```

### Building the default Trismed image:

```bash
cd ~/am62/yocto/yocto-trismed/var-ti-yocto/build
# image for the development kit
bitbake var-default-image
# build image for cardipia-12ch
bitbake cardipia-12ch-image
# build image for cardipia-18ch
bitbake cardipia-18ch-image
```

### Dealing with build errors

When building big packages, Yocto buildsystem may fail due to system running our of memory.
There are big packages like *opengl-es-cts*, *vulkan-cts*, and other that are likelly to cause this issue.

This can be fixed by limiting the amount of simultenous package being built to 1 (BB_NUMBER_THREADS).
Also you may need to decrase the pararel makes (PARALLEL_MAKE).

To do this, follow the following steps:

```bash
. conf/setenv
export BB_NUMBER_THREADS=1
export PARALLEL_MAKE="-j 2"
# build slower bu uses less RAM
MACHINE=am62x-var-som bitbake var-default-image
# after the big recipes are built press CTRL+C and then ->
unset BB_NUMBER_THREADS
unset PARALLEL_MAKE
# continue to build at full speed
MACHINE=am62x-var-som bitbake var-default-image
```

### Burning the Micro SD card
- Connect the Micro SD to the virtual machine using an USB ready and find the device node associated.
Asuming that the Micro SD card node is */dev/sde* the following command should be used to burn the file on the Micro SD card
```bash
zstdcat deploy-ti/images/am62x-var-som/var-default-image-am62x-var-som.wic.zst | sudo dd of=/dev/sde bs=1M && sync

zstdcat deploy-ti/images/am62x-var-som/cardipia-12ch-image-am62x-var-som.wic.zst | sudo dd of=/dev/sde bs=1M && sync
```

### Building the SDK

To build the Software Development Kit (SDK), run:

```bash
MACHINE=am62x-var-som bitbake -c populate_sdk var-default-image
```

### Installing the SDK

Once the build is complete, install the SDK using the following script:

```bash
./deploy-ti/sdk/arago-2023.10-toolchain-2023.10.sh
```

### Modifying the Kernel
```bash
cd ~/am62/yocto/yocto-trismed/var-ti-yocto/build/arago-tmp-default-glibc/work/am62x_var_som-oe-linux/linux-variscite/6.1.83+gitAUTOINC+055ead3d53-r0b/git/
# make the changes
git diff > 0001-new-lcd.patch
#sha256sum 0001-new-lcd.patch
#bf84fd2052ec19b76798f0c247e1c1a9270a21726d2c951bc22dbc30c73372e0  0001-new-lcd.patch

# build what is needed for the image (will take about 30 minutes)
MACHINE=am62x-var-som bitbake var-default-image
# a faster way to update using 'opkg'
MACHINE=am62x-var-som bitbake linux-variscite

# rebuild ipks index
MACHINE=am62x-var-som bitbake package-index

# serve the updates if not done yet:
cd ~/am62/yocto/yocto-trismed/var-ti-yocto/build/arago-tmp-default-glibc/deploy/ipk
python3 -m http.server 8080

# update on the target:
opkg update
opkg upgrade kernel-image
opkg upgrade kernel-devicetree
opkg install spi-kbd-module
opkg install hw-control-module
```

### Serving the software packages
Make sure to build the packages index with:
```bash
MACHINE=am62x-var-som bitbake package-index
```

#### Serve the packages with:
```bash
cd ~/am62/yocto/yocto-trismed/var-ti-yocto/build/arago-tmp-default-glibc/deploy/ipk
python3 -m http.server 8080
```

On the targer update the packages sources:
```bash
vi /etc/opkg/base-feeds.conf
```
And add the paths using the actual IP that is serving them as follows:

```
src/gz all http://192.168.10.10:8080/all
#src/gz any http://192.168.10.10:8080/any
#src/gz noarch http://192.168.10.10:8080/noarch
src/gz aarch64 http://192.168.10.10:8080/aarch64
src/gz am62x_var_som http://192.168.10.10:8080/am62x_var_som
```
#### Update the packages with:
```bash
opkg update
```

Update stuff:
```bash
opkg install kernel
opkg install kernel-modules
opkg install kernel-devicetree
```

## Using the SDK with Qt Creator

To configure Qt Creator with the built SDK, use the following paths:

- **QMake:**
  ```
  /opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/qmake
  ```

- **Compilers:**
  ```
  /opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/aarch64-oe-linux/aarch64-oe-linux-gcc
  /opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/aarch64-oe-linux/aarch64-oe-linux-g++
  ```

- **Debugger:**
  ```
  /opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/aarch64-oe-linux/aarch64-oe-linux-gdb
  ```

- **Sysroot:**
  ```
  /opt/arago-2023.10/sysroots/aarch64-oe-linux
  ```

- **Kit Environment**
 Open a terminal and type
```
  source /opt/arago-2023.10/environment-setup-aarch64-oe-linux
  env
```
 Copy the entire environment to the AM62 kit envoronment in qt Creator:
 Projects -> Manage Kits -> Select AM62 kit -> "Environent:" -> Change
 ```
 OE_QMAKE_CXX=aarch64-oe-linux-g++  -mbranch-protection=standard --sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
SHELL=/bin/bash
SESSION_MANAGER=local/trismed-vmwarevirtualplatform:@/tmp/.ICE-unix/2323,unix/trismed-vmwarevirtualplatform:/tmp/.ICE-unix/2323
WINDOWID=62914571
QT_ACCESSIBILITY=1
OPENSSL_ENGINES=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/lib/engines-3
COLORTERM=truecolor
OE_CMAKE_TOOLCHAIN_FILE=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/share/cmake/OEToolchainConfig.cmake
XDG_CONFIG_DIRS=/home/trismed/.config/kdedefaults:/etc/xdg/xdg-plasma:/etc/xdg:/usr/share/kubuntu-default-settings/kf5-settings
OE_QMAKE_RCC=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/rcc
M4=m4
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session1
OECORE_TUNE_CCARGS= -mbranch-protection=standard
QT_CONF_PATH=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/qt.conf
GTK_IM_MODULE=fcitx
OECORE_SDK_VERSION=2023.10
PKG_CONFIG_PATH=/opt/arago-2023.10/sysroots/aarch64-oe-linux/usr/lib/pkgconfig:/opt/arago-2023.10/sysroots/aarch64-oe-linux/usr/share/pkgconfig
ICEAUTHORITY=/run/user/1000/iceauth_jVtkFS
LANGUAGE=
GDB=aarch64-oe-linux-gdb
SDKTARGETSYSROOT=/opt/arago-2023.10/sysroots/aarch64-oe-linux
LC_ADDRESS=en_US.UTF-8
LC_NAME=en_US.UTF-8
SSH_AUTH_SOCK=/tmp/ssh-nWzggIcSrcAy/agent.2142
OECORE_BASELIB=lib
CPP=aarch64-oe-linux-gcc -E  -mbranch-protection=standard --sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
SHELL_SESSION_ID=47f1eca4617449a593bedf4b5d411d0e
OE_QMAKE_INCDIR_QT=/opt/arago-2023.10/sysroots/aarch64-oe-linux/usr/include
MEMORY_PRESSURE_WRITE=c29tZSAyMDAwMDAgMjAwMDAwMAA=
OE_QMAKE_OBJCOPY=aarch64-oe-linux-objcopy
OE_QMAKE_AR=aarch64-oe-linux-ar
TARGET_PREFIX=aarch64-oe-linux-
OE_CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX=
XMODIFIERS=@im=fcitx
OE_QMAKE_LINK=aarch64-oe-linux-g++  -mbranch-protection=standard --sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
DESKTOP_SESSION=plasma
LC_MONETARY=en_US.UTF-8
SSH_AGENT_PID=2213
GTK_RC_FILES=/etc/gtk/gtkrc:/home/trismed/.gtkrc:/home/trismed/.config/gtkrc
XCURSOR_SIZE=24
XDG_SEAT=seat0
PWD=/home/trismed/am62/yocto/yocto-trismed/var-ti-yocto/build
XDG_SESSION_DESKTOP=KDE
LOGNAME=trismed
XDG_SESSION_TYPE=x11
GPG_AGENT_INFO=/run/user/1000/gnupg/S.gpg-agent:0:1
SYSTEMD_EXEC_PID=2393
OECORE_TARGET_OS=linux
CXX=aarch64-oe-linux-g++  -mbranch-protection=standard --sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
CXXFLAGS= -O2 -pipe -g -feliminate-unused-debug-types
OE_QMAKE_PATH_HOST_BINS=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin
XAUTHORITY=/tmp/xauth_jAWQEL
OECORE_NATIVE_SYSROOT=/opt/arago-2023.10/sysroots/x86_64-arago-linux
OE_QMAKE_MOC=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/moc
GTK2_RC_FILES=/etc/gtk-2.0/gtkrc:/home/trismed/.gtkrc-2.0:/home/trismed/.config/gtkrc-2.0
LDFLAGS=-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed
HOME=/home/trismed
IM_CONFIG_PHASE=1
SSH_ASKPASS=/usr/bin/ksshaskpass
LC_PAPER=en_US.UTF-8
LANG=en_US.UTF-8
OE_QMAKE_LIBDIR_QT=/opt/arago-2023.10/sysroots/aarch64-oe-linux/usr/lib
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=00:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.avif=01;35:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:*~=00;90:*#=00;90:*.bak=00;90:*.crdownload=00;90:*.dpkg-dist=00;90:*.dpkg-new=00;90:*.dpkg-old=00;90:*.dpkg-tmp=00;90:*.old=00;90:*.orig=00;90:*.part=00;90:*.rej=00;90:*.rpmnew=00;90:*.rpmorig=00;90:*.rpmsave=00;90:*.swp=00;90:*.tmp=00;90:*.ucf-dist=00;90:*.ucf-new=00;90:*.ucf-old=00;90:
OPENSSL_CONF=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/lib/ssl-3/openssl.cnf
XDG_CURRENT_DESKTOP=KDE
KONSOLE_DBUS_SERVICE=:1.106
MEMORY_PRESSURE_WATCH=/sys/fs/cgroup/user.slice/user-1000.slice/user@1000.service/session.slice/plasma-plasmashell.service/memory.pressure
OE_QMAKE_CXXFLAGS= -O2 -pipe -g -feliminate-unused-debug-types
SSL_CERT_DIR=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/lib/ssl-3/certs
KCFLAGS=--sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
KONSOLE_DBUS_SESSION=/Sessions/3
PROFILEHOME=
OECORE_TARGET_SYSROOT=/opt/arago-2023.10/sysroots/aarch64-oe-linux
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
CPPFLAGS=
OPENSSL_MODULES=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/lib/ossl-modules/
LD=aarch64-oe-linux-ld  --sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
QTWEBENGINE_DICTIONARIES_PATH=/usr/share/hunspell-bdic/
INVOCATION_ID=79dc7c977bb24fd0a49f8d9c22bcfa11
OE_QMAKE_CC=aarch64-oe-linux-gcc  -mbranch-protection=standard --sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
KONSOLE_VERSION=230805
MANAGERPID=2102
OE_QMAKE_CFLAGS= -O2 -pipe -g -feliminate-unused-debug-types
READELF=aarch64-oe-linux-readelf
OE_QMAKE_UIC=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/uic
CLUTTER_IM_MODULE=xim
KDE_SESSION_UID=1000
OE_QMAKE_LDFLAGS=-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed
SDL_IM_MODULE=fcitx
QMAKESPEC=/opt/arago-2023.10/sysroots/aarch64-oe-linux/usr/lib/mkspecs/linux-oe-g++
LESSCLOSE=/usr/bin/lesspipe %s %s
XDG_SESSION_CLASS=user
TERM=xterm-256color
LC_IDENTIFICATION=en_US.UTF-8
LESSOPEN=| /usr/bin/lesspipe %s
USER=trismed
COLORFGBG=15;0
AR=aarch64-oe-linux-ar
ARCH=arm64
AS=aarch64-oe-linux-as
KDE_SESSION_VERSION=5
PAM_KWALLET5_LOGIN=/run/user/1000/kwallet5.socket
DISPLAY=:0
SHLVL=1
NM=aarch64-oe-linux-nm
GSM_SKIP_SSH_AGENT_WORKAROUND=true
LC_TELEPHONE=en_US.UTF-8
OE_QMAKE_STRIP=aarch64-oe-linux-strip
QT_IM_MODULE=fcitx
OECORE_TARGET_ARCH=aarch64
LC_MEASUREMENT=en_US.UTF-8
XDG_VTNR=2
XDG_SESSION_ID=4
XDG_RUNTIME_DIR=/run/user/1000
SSL_CERT_FILE=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/lib/ssl-3/certs/ca-certificates.crt
OECORE_DISTRO_VERSION=2023.10
PKG_CONFIG_SYSROOT_DIR=/opt/arago-2023.10/sysroots/aarch64-oe-linux
OECORE_ACLOCAL_OPTS=-I /opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/share/aclocal
OE_QMAKE_QDBUSXML2CPP=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/qdbusxml2cpp
OBJCOPY=aarch64-oe-linux-objcopy
DEBUGINFOD_URLS=https://debuginfod.ubuntu.com
LC_TIME=en_US.UTF-8
STRIP=aarch64-oe-linux-strip
QT_AUTO_SCREEN_SCALE_FACTOR=0
JOURNAL_STREAM=8:30085
XCURSOR_THEME=breeze_cursors
XDG_DATA_DIRS=/usr/share/plasma:/usr/local/share:/usr/share:/var/lib/snapd/desktop
KDE_FULL_SESSION=true
OBJDUMP=aarch64-oe-linux-objdump
CONFIG_SITE=/opt/arago-2023.10/site-config-aarch64-oe-linux
PATH=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin:/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin:/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/sbin:/opt/arago-2023.10/sysroots/x86_64-arago-linux/bin:/opt/arago-2023.10/sysroots/x86_64-arago-linux/sbin:/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/../x86_64-arago-linux/bin:/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/aarch64-oe-linux:/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/aarch64-oe-linux-musl:/home/trismed/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
CC=aarch64-oe-linux-gcc  -mbranch-protection=standard --sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
CFLAGS= -O2 -pipe -g -feliminate-unused-debug-types
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
CROSS_COMPILE=aarch64-oe-linux-
KDE_APPLICATIONS_AS_SCOPE=1
CONFIGURE_FLAGS=--target=aarch64-oe-linux --host=aarch64-oe-linux --build=x86_64-linux --with-libtool-sysroot=/opt/arago-2023.10/sysroots/aarch64-oe-linux
OE_QMAKE_QDBUSCPP2XML=/opt/arago-2023.10/sysroots/x86_64-arago-linux/usr/bin/qdbuscpp2xml
RANLIB=aarch64-oe-linux-ranlib
LC_NUMERIC=en_US.UTF-8
OE_QMAKE_QT_CONFIG=/opt/arago-2023.10/sysroots/aarch64-oe-linux/usr/lib/mkspecs/qconfig.pri
KONSOLE_DBUS_WINDOW=/Windows/1
_=/usr/bin/env
 ```

## Debugging on the target using QtCreator
Use the default environment on *Qt Creator* to run the aplpication on the target.
To know the default environment run:
```bash
env
```
- Copy and paste the output into *Build & Run*/*Environment*.

**Note:** The *Fetch Device Environment* button should do this, but it didn't work.

- **Set the run Environment to:**
```
XDG_RUNTIME_DIR=/
SHELL=/bin/sh
QT_QPA_EGLFS_INTEGRATION=eglfs_kms
QT_WAYLAND_SHELL_INTEGRATION=xdg-shell
EDITOR=vi
QTWEBENGINE_DISABLE_SANDBOX=1
PWD=/
LOGNAME=root
XDG_SESSION_TYPE=tty
SYSTEMD_EXEC_PID=785
MOTD_SHOWN=pam
HOME=/home/root
LANG=C
QT_QPA_EGLFS_ALWAYS_SET_MODE=1
WAYLAND_DISPLAY=/run/wayland-0
QT_QPA_EGLFS_KMS_CONFIG=/etc/qt5/eglfs_kms_cfg.json
INVOCATION_ID=9bf5d126fbc4480c953611d5394f5a6e
XDG_SESSION_CLASS=user
TERM=vt220
USER=root
SHLVL=1
XDG_SESSION_ID=c2
XDG_RUNTIME_DIR=/run/user/0
SSL_CERT_FILE=/etc/ssl/certs/ca-certificates.crt
PS1=\u@\h:\w\$
HUSHLOGIN=FALSE
PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin
QTWEBENGINE_CHROMIUM_FLAGS=--disable-seccomp-filter-sandbox
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/0/bus
MAIL=/var/spool/mail/root
OLDPWD=/home/root
_=/usr/bin/env
```

## Additional Information

Yocto is a powerful but complex tool for building custom Linux distributions. In the Trismed project, we maintain only the necessary repositories that we need to modify for our image and SDK customization.

### Internally hosted and maintained repositories

The following repositories are customized for the Trismed project:
- **yocto-trismed** *(this repository)*
  - [Repository Link](http://192.168.10.251/Bonobo.Git.Server/yocto-trismed.git)
  - *Contains the 'FetchAll.sh' script to gather an configure everything for building Yocto.*

- **meta-trismed**
  - [Repository Link](http://192.168.10.251/Bonobo.Git.Server/meta-trismed.git)
  - *Layer containing all the modifications that will be applied to Variscite's Yocto*

### Directly referenced repositories

- **varigit/oe-layersetup**
  - [Repository Link](https://github.com/varigit/oe-layersetup)
  - *This is Variscite's Yocto repository*

## How to rebuild a specific module

Clear the entire 'qtbase' module (including cache):
```bash
MACHINE=am62x-var-som  bitbake -c cleanall qtbase
```
Build it again:
```bash
MACHINE=am62x-var-som  bitbake qtbase
```
Then rebuild the image and SDK if needed.

### Building QCardipia with Yocto
```
  . conf/setenv
  echo 0 | sudo tee /proc/sys/kernel/apparmor_restrict_unprivileged_userns
  # clean up any previous build of QCardipia
  bitbake -c cleansstate qcardipia
  # build 'qcardipia' recipe
  bitbake qcardipia
  # rebuild packages indexes
  MACHINE=am62x-var-som bitbake package-index
```
on another terminal tab (keep this running):
```
cd ~/am62/yocto/yocto-trismed/var-ti-yocto/build/arago-tmp-default-glibc/deploy/ipk
python3 -m http.server 8080
```
on the target:
```
opkg update
opkp upgrade qcardipia
```

### Update uboot after changes (only when booting from micro SD card)

```bash
# set cardipia's IP address
export CARDIPIA_IP="192.168.10.122"

# make sure the device is ON and accesible
ping $CARDIPIA_IP

# go to am62-var-som output folder
cd /home/trismed/am62/yocto/yocto-trismed/var-ti-yocto/build/deploy-ti/images/am62x-var-som/

# execute the following commands
scp tispl.bin-am62x-var-som-2023.04+gitAUTOINC+e8b424ab77-r0 root@$CARDIPIA_IP:/run/media/boot-mmcblk1p1/tispl.bin
scp tiboot3-am62x-hs-fs-am62x-var-som-am62x-var-som-k3r5-2023.04+gitAUTOINC+e8b424ab77-r0.bin root@$CARDIPIA_IP:/run/media/boot-mmcblk1p1/tiboot3.bin
scp u-boot-am62x-var-som-2023.04+gitAUTOINC+e8b424ab77-r0.img root@$CARDIPIA_IP:/run/media/boot-mmcblk1p1/u-boot.img
scp tiboot3-am62x-hs-fs-am62x-var-som-am62x-var-som-k3r5-2023.04+gitAUTOINC+e8b424ab77-r0.bin root@$CARDIPIA_IP:/run/media/boot-mmcblk1p1/tiboot3.bin
scp tiboot3-am62x-hs-fs-am62x-var-som.bin root@$CARDIPIA_IP:/run/media/boot-mmcblk1p1/tiboot3-am62x-hs-fs-am62x-var-som.bin
scp tiboot3-am62x-hs-am62x-var-som.bin root@$CARDIPIA_IP:/run/media/boot-mmcblk1p1/tiboot3-am62x-hs-am62x-var-som.bin
scp tiboot3-am62x-gp-am62x-var-som.bin root@$CARDIPIA_IP:/run/media/boot-mmcblk1p1/tiboot3-am62x-gp-am62x-var-som.bin

# connect to the target and reboot it to make the changes efective
```

# Other useful Yocto commands

```bash
bitbake -c clean linux-variscite
bitbake linux-variscite -f -c compile
bitbake virtual/kernel -c modules_install

bitbake -c clean spi-kbd-module
bitbake -c clean hw-control-module
```

# Uboot commands to change devicetree (to be automated in image recipe)
 ```bash
printenv default_device_tree
default_device_tree="k3-am625-var-som-symphony".dtb

setenv default_device_tree "k3-am625-var-som-cardipia12ch".dtb
saveenv
reset

setenv default_device_tree "k3-am625-var-som-cardipia18ch".dtb

setenv name_overlays ""
saveenv
setenv name_overlays spi_keypad-overlay.dtbo
```

opkg update
opkg upgrade kernel-image
opkg upgrade kernel-devicetree
opkg upgrade kernel-module-spi-kbd
opkg upgrade kernel-module-hw-control

see:
/home/trismed/am62/yocto/yocto-trismed/var-ti-yocto/sources/meta-variscite-sdk-ti/dynamic-layers/meta-arago-distro/recipes-tisdk/tisdk-uenv/tisdk-uenv/

# Other Resources:
Tool to find out devide-tree pinctrl definitions
https://dev.ti.com/sysconfig

