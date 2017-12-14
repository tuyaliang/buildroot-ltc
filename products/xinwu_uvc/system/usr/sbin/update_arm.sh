 #!/bin/sh

ps -o pid,rss,comm | sed '/PID/d' | while read p o c; do
 echo "treating $p $o $c"
 if test "$c" != "sh" && ! [ $o -eq 0 ] && test "$c" != "exe"; then
	 echo "killing: $c($p)"
	 kill -9 $p > /dev/null 2>&1
 fi
done

echo "pgm is $0"

#umount -a
umount /sys
umount /mnt
umount /tmp
umount /dev/pts
umount /proc
umount /dev
umount /

mount none /tmp -t tmpfs
mkdir -p /tmp
mkdir /tmp/old
mkdir /tmp/proc
mkdir /tmp/sys
mkdir /tmp/tmp
mv /dev/shm/burn.ius /tmp/tmp
mkdir /tmp/dev
cd /dev
for i in `ls`; do if [ "$i" != "usb-ffs" ]; then cp -pdrvf $i /tmp/dev; fi; done
cd /
cp -pdrf *bin lib*  usr /tmp
mount none /tmp/proc -t proc
mount none /tmp/sys -t sysfs
pivot_root /tmp /tmp/old

clear
ota_upgrade /tmp/burn.ius
