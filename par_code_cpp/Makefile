CC  := g++

fractal_par:
	$(CC) fractal_par.cc -o fractal_par -std=c++11 -pthread -Ofast

pcc_par:
	$(CC) pcc_par.cc -o pcc_par -std=c++11 -pthread -Ofast

fractal_validate:
	diff fracout_1024.tga ../resources/ref/fracout_1024.tga
	diff fracout_2048.tga ../resources/ref/fracout_2048.tga
	diff fracout_4096.tga ../resources/ref/fracout_4096.tga
	diff fracout_8192.tga ../resources/ref/fracout_8192.tga

pcc_validate:
	diff pccout_128_128.dat ../resources/ref/pccout_128_128.dat
	diff pccout_256_256.dat ../resources/ref/pccout_256_256.dat
	diff pccout_512_512.dat ../resources/ref/pccout_512_512.dat
	diff pccout_1024_1024.dat ../resources/ref/pccout_1024_1024.dat

.PHONY: all clean
all: fractal_par pcc_par
clean:
	@rm -f fractal_par fracout_*.tga pcc_par pccout_*.dat
