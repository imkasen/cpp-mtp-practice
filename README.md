# C++ Multi-threaded Programming of MFC and PCC

Use C++ to practice multi-threaded programming of Mandelbrot Fractal Calculation (MFC) algorithm and Pearson Correlation Coefficient (PCC) algorithm.

# Environments

* Ubuntu 20.04 LTS
* GCC 9.3.0
* C99 / C++17

# Mandelbrot fractal calculation

> The Mandelbrot set is an example of a fractal in mathematics. It is named after Benoît Mandelbrot, a Polish-French-American mathematician. The Mandelbrot set is important for chaos theory. The edging of the set shows a self-similarity, which is not perfect because it has deformations.

## Sequential Version in C

1. compile the Mandelbrot fractal application
   
   ``` bash
   $ cd seq_code_c
   $ make fractal_seq
   ```

2. executes the code

   ``` bash
   $ ./fractal_seq <fractal_size> # 1024, 2048, ...
   ```

3. validate for correctness

   ``` bash
   $ make fractal_validate
   # or
   $ diff fracout_<size>.tga ../resources/ref/fracout_<size>.tga
   ```

# Pearson Correlation Coefficient (PCC)

> In statistics, the Pearson correlation coefficient (PCC) ― also known as Pearson's r, the Pearson product-moment correlation coefficient (PPMCC), the bivariate correlation, or colloquially simply as the correlation coefficient ― is a measure of linear correlation between two sets of data.

## Sequential Version in C

1. *generate the matrix input for the PCC application (optional, provided in `resources/pcc_input` folder)*
   
   ``` bash
   $ cd ./seq_code_c
   $ make pcc_generate_input
   $ ./pcc_generate <matrix_height> <matrix_width> > xxx.dat
   ```

2. compiles the PCC application

   ``` bash
   $ make pcc_seq
   ```

3. executes the code

   ``` bash
   $ ./pcc_seq ../resources/pcc_input/matrix_<height>_<weight>.dat <matrix_height> <matrix_width>
   ```

4. validate for correctness

   ``` bash
   $ make fractal_validate
   # or
   $ diff pccout_<size>_<size>.dat ../resources/ref/pccout_<size>_<size>.dat
   ```

# LICENSE

GNU GPLv3
