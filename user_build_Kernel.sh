#!/bin/bash
#设置环境

# Special Clean For Huawei Kernel.
if [ -d include/config ];
then
    echo "Find config,will remove it"
	rm -rf include/config
else
	echo "No Config,good."
fi


echo " "
echo "***Setting environment...***"
# 交叉编译器路径
# 
export PATH=$PATH:"/home/coconutat/下载/P30/android-ndk-r14b/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin"
export CROSS_COMPILE=aarch64-linux-android-

export GCC_COLORS=auto
export ARCH=arm64
if [ ! -d "out" ];
then
	mkdir out
fi

date="$(date +%Y.%m.%d-%I:%M)"

echo "***Building kernel..***"
make ARCH=arm64 O=out merge_kirin980_mod_defconfig
# 定义编译线程数
make ARCH=arm64 O=out -j256 2>&1 | tee kernel_log-${date}.txt

#打包Ravel版内核

if [ -f out/arch/arm64/boot/Image.gz ];
then
	echo "***Packing kernel...***"

	tools/mkbootimg --kernel out/arch/arm64/boot/Image.gz --base 0x0 --cmdline "loglevel=4 initcall_debug=n page_tracker=on ssbd=kernel printktimer=0xfff0a000,0x534,0x538 androidboot.selinux=permissive unmovable_isolate1=2:192M,3:224M,4:256M buildvariant=user" --tags_offset 0x07A00000 --kernel_offset 0x00080000 --ramdisk_offset 0x07c00000 --header_version 1 --os_version 9 --os_patch_level 2019-03-01  --output Kirin980_PM-${date}.img

	cp out/arch/arm64/boot/Image.gz Image.gz 
	echo " "
	echo "***Sucessfully built kernel...***"
	echo " "
	exit 0
else
	echo " "
	echo "***Failed!***"
	exit 0
fi