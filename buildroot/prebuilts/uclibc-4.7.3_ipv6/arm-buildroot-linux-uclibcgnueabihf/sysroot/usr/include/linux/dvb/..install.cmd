cmd_/nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/dvb/.install := /bin/bash scripts/headers_install.sh /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/dvb   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/audio.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/ca.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/dmx.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/frontend.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/net.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/osd.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/version.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/dvb/video.h ; for F in ; do echo "\#include <asm-generic/$$F>" > /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/dvb/$$F; done; touch /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/dvb/.install
