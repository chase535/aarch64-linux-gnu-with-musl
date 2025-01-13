# aarch64-linux-musl-gcc

适用于**x64**平台**Linux**系统的gcc交叉编译器，用于交叉编译**aarch64**平台的程序，使用musl libc代替glibc

开启GitHub Actions，**协调世界时每周一的1点左右**自动clone最新的binutils、gcc、musl源码并下载最新的Release版gmp、mpfr、mpc、isl源码进行CI构建并推送

构建步骤在build.yml中写的很详细，如果想要本地使用，可以直接clone本仓库，亦可执行build.yml中的步骤自行部署
