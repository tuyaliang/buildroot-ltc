cmd_/nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video/.install := /bin/bash scripts/headers_install.sh /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/video/edid.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/video/sisfb.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/video/uvesafb.h ; for F in ; do echo "\#include <asm-generic/$$F>" > /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video/$$F; done; touch /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/video/.install
