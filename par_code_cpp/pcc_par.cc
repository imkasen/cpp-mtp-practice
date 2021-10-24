#include "common.cc"
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <functional>
#include <thread>

// Read tab delimited matrix file
void read_matrix(const std::string &input_filename,
                std::vector<float> &matrix) {
    std::ifstream infile;
    infile.open(input_filename, std::ios::in);
    if (!infile) {
        std::cerr << "error: can not open " << input_filename << std::endl;
        exit(EXIT_FAILURE);
    }

    int count = 0;
    std::string line;
    std::istringstream line_stream;
    while (std::getline(infile, line)) {
        line_stream.str(line);
        std::string token;
        while (std::getline(line_stream, token, ' ')) {
            matrix[count] = std::stof(token);
            count++;
        }
        line_stream.clear();
    }

    infile.close();
}

// Calculate row mean
void calc_mean(const std::vector<float> &matrix,
              std::vector<float> &mean,
              const unsigned int rows,
              const unsigned int cols) {
    for (int i = 0; i < rows; ++i) {
        float sum = 0.0f;
        for (int j = 0; j < cols; ++j) {
            sum += matrix[i * cols + j];
        }
        mean[i] = sum / static_cast<float>(cols);
    }
}

// Calculate matrix - row mean, and standard deviation for every row
void calc_mm_std(const std::vector<float> &matrix,
                 const std::vector<float> &mean,
                 std::vector<float> &minus_mean,
                 std::vector<float> &std_dev,
                 const unsigned int rows,
                 const unsigned int cols) {
    for (int i = 0; i < rows; ++i) {
        float sum = 0.0f;
        for (int j = 0; j < cols; ++j) {
            float diff = matrix[i * cols + j] - mean[i];
            minus_mean[i * cols + j] = diff;
            sum += diff * diff;
        }
        std_dev[i] = std::sqrt(sum);
    }
}

void pearson(const std::vector<float> &minus_mean,
             const std::vector<float> &std_dev,
             std::vector<float> &output,
             const unsigned int rows,
             const unsigned int min_rows,
             const unsigned int max_rows,
             const unsigned int cols) {
    for (unsigned int sample1 = min_rows; sample1 < max_rows; ++sample1) {
        unsigned int sum1 = 0;
        sum1 = (sum1 + sample1 + 1) * (sample1 + 2) / 2;

        for (unsigned int sample2 = sample1 + 1; sample2 < rows; ++sample2) {
            float sum2 = 0.0f;
            for (int j = 0; j < cols; ++j) {
                sum2 += minus_mean[sample1 * cols + j] * minus_mean[sample2 * cols + j];
            }
            float r = sum2 / (std_dev[sample1] * std_dev[sample2]);
            output[sample1 * rows + sample2 - sum1] = r;
        }
    }
}

void concurrent_pearson(const std::vector<float> &minus_mean,
                        const std::vector<float> &std_dev,
                        std::vector<float> &output,
                        const unsigned int rows,
                        const unsigned int cols) {
    unsigned int concurrent_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    unsigned int min = 0;
    for (int i = 0; i < concurrent_count; ++i) {
        unsigned int max = rows / concurrent_count * (i + 1);
        if (i == concurrent_count - 1) {
            max = rows - 1;
        }

        threads.emplace_back(pearson, std::cref(minus_mean),
                             std::cref(std_dev), std::ref(output),
                             rows, min, max, cols);
        min = max;
    }

    for (auto &thread : threads) {
        thread.join();
    }
}

void pearson_seq(const std::vector<float> &matrix,
                 std::vector<float> &output,
                 const unsigned int rows,
                 const unsigned int cols) {
    std::vector<float> mean(rows);
    std::vector<float> std_dev(cols);
    std::vector<float> minus_mean(rows * cols);

    calc_mean(matrix, mean, rows, cols);
    calc_mm_std(matrix, mean, minus_mean, std_dev, rows, cols);
    concurrent_pearson(minus_mean, std_dev, output, rows, cols);
}

void write_output(const std::vector<float> &output,
                  const long long cor_size,
                  const std::string &output_filename) {
    FILE *f;
    f = fopen(output_filename.c_str(),"wb");
    for (int i = 0; i < cor_size; ++i) {
        fprintf(f, "%f ", output[i]);
    }
    fclose(f);
}

int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();

    if (argc < 4) {
        std::cerr << "usage: " << argv[0] << " matrix_file matrix_height matrix_width" << std::endl;
        exit(EXIT_FAILURE);
    }
    const std::string input_filename = argv[1];

    const unsigned int rows = std::stoi(argv[2]);
    if (rows < 1) {
        std::cerr << "error: height must be at least 1" << std::endl;
        exit(EXIT_FAILURE);
    }

    const unsigned int cols = std::stoi(argv[3]);
    if (cols < 1) {
        std::cerr << "error: width must be at least 1" << std::endl;
        exit(EXIT_FAILURE);
    }

    // create an array of timers for each iteration
    std::vector<double> times(ITERATIONS);

    // used to generate the correct filename
    std::string output_filename = "pccout_" + std::to_string(rows) + "_" + std::to_string(cols) + ".dat";

    // calculates the size of the output
    long long cor_size = rows - 1;
    cor_size *= rows;
    cor_size /= 2;

    std::vector<float> output(cor_size);
    std::vector<float> matrix(cols * rows);

    read_matrix(input_filename, matrix);

    for (int i = 0; i < ITERATIONS; ++i) {
        auto start_func = std::chrono::high_resolution_clock::now();

        pearson_seq(matrix, output, rows, cols);

        auto end_func = std::chrono::high_resolution_clock::now();
        times[i] = std::chrono::duration<double, std::micro>(end_func - start_func).count();
    }

    print_results(times);

    write_output(output, cor_size, output_filename);

    std::cout << std::endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_time = std::chrono::duration<double, std::micro>(end_time - start_time).count();
    std::cout << "Total time: " << total_time / 1e6 << " (s)" << std::endl;

    return EXIT_SUCCESS;
}
