# C++ Multi-threaded Programming of MFC and PCC

Use C++ to practice multi-threaded programming of Mandelbrot Fractal Calculation (MFC) algorithm and Pearson Correlation Coefficient (PCC) algorithm.

# Environments

* Ubuntu 20.04 LTS
* GCC 9.3.0 / CMake 3.16.3
* C99 / C++11

# Mandelbrot fractal calculation

> The Mandelbrot set is an example of a fractal in mathematics. It is named after Benoît Mandelbrot, a Polish-French-American mathematician. The Mandelbrot set is important for chaos theory. The edging of the set shows a self-similarity, which is not perfect because it has deformations.

## Execution

1. compile the program
   
   ``` bash
   $ cd seq_code_cpp / par_code_cpp
   $ make fractal_seq / fractal_par
   ```

2. execute the code

   ``` bash
   $ ./fractal_seq <fractal_size> # 1024, 2048, ...
   # or
   $ ./fractal_par <fractal_size> # 1024, 2048, ...
   ```

3. validate the generated file for correctness

   ``` bash
   $ make fractal_validate
   # or
   $ diff fracout_<size>.tga ../resources/ref/fracout_<size>.tga
   ```

# Pearson Correlation Coefficient (PCC)

> In statistics, the Pearson correlation coefficient (PCC) ― also known as Pearson's r, the Pearson product-moment correlation coefficient (PPMCC), the bivariate correlation, or colloquially simply as the correlation coefficient ― is a measure of linear correlation between two sets of data.

## Execution

1. compile the program

   ``` bash
   $ cd seq_code_cpp / par_code_cpp
   $ make pcc_seq / pcc_par
   ```

2. execute the code

   ``` bash
   $ ./pcc_seq ../resources/pcc_input/matrix_<height>_<weight>.dat <matrix_height> <matrix_width>
   # or
   $ ./pcc_par ../resources/pcc_input/matrix_<height>_<weight>.dat <matrix_height> <matrix_width>
   ```

3. validate the generated file for correctness

   ``` bash
   $ make fractal_validate
   # or
   $ diff pccout_<size>_<size>.dat ../resources/ref/pccout_<size>_<size>.dat
   ```

# LICENSE

GNU GPLv3
