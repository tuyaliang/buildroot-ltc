cmd_/home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/nfsd/.install := /bin/bash scripts/headers_install.sh /home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/nfsd   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/nfsd/cld.h   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/nfsd/debug.h   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/nfsd/export.h   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/nfsd/nfsfh.h   /home/devin/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/nfsd/stats.h ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/nfsd/$$F; done; touch /home/devin/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/nfsd/.install
