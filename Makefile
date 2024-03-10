all: build flash clear

build: main.c
	sdcc main.c --std-sdcc99 -DSTM8S103 -lstm8 -mstm8 --Werror

flash: main.ihx
	sudo stm8flash -c stlinkv2 -p stm8s103f3 -w main.ihx

clear:
	rm main.asm main.ihx main.lk main.lst main.map main.rel main.rst main.sym