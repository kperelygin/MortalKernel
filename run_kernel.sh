#!/bin/sh
bochs -f bochsrc
#qemu -s -fda bootfloppy.img -boot a -hda Imgs/hdd-10M.img