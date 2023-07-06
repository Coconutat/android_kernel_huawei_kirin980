# Huawei Kirin980 Devices Kernel  
Huawei Kirin980 Devices Kernel.  
Source From P30.  
Based System Version is EMUI 9.1.0.  
Kernel Version 4.9.148  

***
AARCH64 GCC:[Google Android NDK](https://developer.android.com/ndk/downloads/older_releases)  
> Please choose to download **Android NDK r14b** version
***  
Modify Feature:
+ Delete Huawei SELINUX Spy
+ Delete Huawei Root Scan and Spy
+ Disable Huawei AVB Check
+ Support **Mate 20 EMUI 9.1.0**(defconfig:Mate20_kirin980_mod_defconfig)
 > Port from 970,980 open source defconfig and Mate20 config.gz
+ Support **KernelSU**(Optional, within the branch KernelSU)
***  
If you want to compile the kernel, you can only choose defconfig with the **mod** suffix.  