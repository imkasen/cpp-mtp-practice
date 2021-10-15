CC	= gcc

all: fractal_seq pcc_seq pcc_generate_input

fractal_seq: 
			$(CC) fractal_seq.c -lm -std=c99 -o fractal_seq
pcc_seq: 
			$(CC) pcc_seq.c -lm -std=c99 -o pcc_seq

#fractal_par:
#			$(CC) fractal_par.c -lm -std=c99 -o fractal_par
#pcc_par:
#			$(CC) pcc_par.c -lm -std=c99 -o pcc_par

fractal_validate: 	
			diff fracout_1024.tga ref/fracout_1024.tga
			diff fracout_2048.tga ref/fracout_2048.tga
			diff fracout_4096.tga ref/fracout_4096.tga
			diff fracout_8192.tga ref/fracout_8192.tga

pcc_validate: 	
			diff pccout_128_128.dat ref/pccout_128_128.dat
			diff pccout_256_256.dat ref/pccout_256_256.dat
			diff pccout_512_512.dat ref/pccout_512_512.dat
			diff pccout_1024_1024.dat ref/pccout_1024_1024.dat

pcc_generate_input:
	$(CC) generate.c -o pcc_generate

clean: 
			rm -f fractal_seq fractal_par pcc_seq pcc_par pcc_generate

