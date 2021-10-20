CC  := g++

fractal_seq:
	$(CC) fractal_seq.cc -o fractal_seq -std=c++11

pcc_seq:
	$(CC) pcc_seq.cc -o pcc_seq -std=c++11

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
all: fractal_seq pcc_seq
clean:
	@rm -f fractal_seq fracout_*.tga pcc_seq pccout_*.dat
