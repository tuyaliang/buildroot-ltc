cmd_/home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video/.install := /bin/bash scripts/headers_install.sh /home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/video/edid.h   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/video/sisfb.h   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/video/uvesafb.h ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video/$$F; done; touch /home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video/.install
