CC  := g++

fractal_seq:
	$(CC) fractal_seq.cc -o fractal_seq -std=c++11

pcc_seq:
	$(CC) pcc_seq.cc -o pcc_seq -std=c++11

.PHONY: all clean
all: fractal_seq pcc_seq
clean:
	@rm -f fractal_seq fracout_*.tga pcc_seq pccout_*.dat
