#ifndef STUD_96_MATRIX_H
#define STUD_96_MATRIX_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <vector>

struct Matrix {
public:
    int** data = nullptr;
    int rows = 0;
    int cols = 0;

    Matrix() {}

    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        data = new int*[rows];

        for (int i = 0; i < rows; i++)
            data[i] = new int[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = 0;
    }

    Matrix(const Matrix& m) {
        this->rows = m.rows;
        this->cols = m.cols;

        data = new int*[rows];

        for (int i = 0; i < rows; i++)
            data[i] = new int[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = m.data[i][j];
    }

    Matrix &operator=(const Matrix& m) {
        if (rows > 0) {
            for (int i = 0; i < cols; i++)
                delete[] data[i];
            delete[] data;
        }

        this->rows = m.rows;
        this->cols = m.cols;

        data = new int*[rows];

        for (int i = 0; i < rows; i++)
            data[i] = new int[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = m.data[i][j];

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++)
            delete[] data[i];

        delete[] data;
    }

    int scan() {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (scanf("%d", &data[i][j]) != 1) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return EXIT_FAILURE;
                }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return EXIT_SUCCESS;
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }

    void fillRand(int min, int max) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                data[i][j] = min + (rand() % static_cast<int>(max - min + 1));
        }
    }

    static void mulStand(const Matrix& m1, const Matrix& m2, Matrix& res) {
        for (int i = 0; i < m1.rows; i++) {
            for (int j = 0; j < m1.cols; j++)
                for (int k = 0; k < m2.rows; k++)
                    res.data[i][j] += m1.data[i][k] * m2.data[k][j];
        }
    }

    static void mulVinograd0(const Matrix& A, const Matrix& B, Matrix& res) {
        std::vector<int> mulH = A.preprocRows0();
        std::vector<int> mulV = B.preprocCols0();
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < B.cols; j++) {
                res.data[i][j] = -(mulH[i] + mulV[j]);
                for (int k = 0; k < A.cols/2; k++) {
                    res.data[i][j] = res.data[i][j] +
                                     (A.data[i][k*2]+B.data[k*2+1][j])*
                                     (A.data[i][k*2+1]+B.data[k*2][j]);
                }
            }
        }

        if (A.cols%2 != 0) {
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < B.cols; j++) {
                    res.data[i][j] = res.data[i][j] + A.data[i][A.cols-1]*B.data[A.cols-1][j];
                }
            }
        }
    }

    // +=
    static void mulVinograd1(const Matrix& A, const Matrix& B, Matrix& res) {
        std::vector<int> mulH = A.preprocRows1();
        std::vector<int> mulV = B.preprocCols1();
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < B.cols; j++) {
                res.data[i][j] = -(mulH[i] + mulV[j]);
                for (int k = 0; k < A.cols/2; k++) {
                    res.data[i][j] += (A.data[i][k*2]+B.data[k*2+1][j]) * (A.data[i][k*2+1]+B.data[k*2][j]);
                }
            }
        }

        if (A.cols%2 != 0) {
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < B.cols; j++) {
                    res.data[i][j] += A.data[i][A.cols-1]*B.data[A.cols-1][j];
                }
            }
        }
    }

    // >>
    static void mulVinograd2(const Matrix& A, const Matrix& B, Matrix& res) {
        std::vector<int> mulH = A.preprocRows2();
        std::vector<int> mulV = B.preprocCols2();
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < B.cols; j++) {
                res.data[i][j] = -(mulH[i] + mulV[j]);
                for (int k = 0; k < A.cols >> 1; k++) {
                    res.data[i][j] = res.data[i][j] +
                                     (A.data[i][k << 1] + B.data[(k << 1) + 1][j]) *
                                     (A.data[i][(k << 1) + 1] + B.data[k << 1][j]);
                }
            }
        }

        if ((A.cols & 1) != 0) {
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < B.cols; j++) {
                    res.data[i][j] = res.data[i][j] + A.data[i][A.cols - 1] * B.data[A.cols - 1][j];
                }
            }
        }
    }

    static void mulVinograd3(const Matrix& A, const Matrix& B, Matrix& res) {
        std::vector<int> mulH = A.preprocRows3();
        std::vector<int> mulV = B.preprocCols3();
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < B.cols; j++) {
                int tmp = mulH[i] + mulV[j];
                for (int k = 1; k < A.cols; k += 2) {
                    tmp += (A.data[i][k-1] + B.data[k][j]) *
                           (A.data[i][k] + B.data[k-1][j]);
                }
                res.data[i][j] = tmp;
            }
        }

        if ((A.cols&1) != 0) {
            int n1 = A.cols - 1;
            for (int i = 0; i < A.rows; i++) {
                for (int j = 0; j < B.cols; j++) {
                    res.data[i][j] += A.data[i][n1] * B.data[n1][j];
                }
            }
        }
    }

private:
    std::vector<int> preprocRows0() const {
        std::vector<int> res(rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols/2; j++) {
                res[i] = res[i] + data[i][j*2] * data[i][j*2+1];
            }
        }
        return res;
    }

    std::vector<int> preprocCols0() const {
        std::vector<int> res(cols);
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows/2; j++) {
                res[i] = res[i] + data[j*2][i] * data[j*2+1][i];
            }
        }
        return res;
    }

    std::vector<int> preprocRows1() const {
        std::vector<int> res(rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols/2; j++) {
                res[i] += data[i][j*2] * data[i][j*2+1];
            }
        }
        return res;
    }

    std::vector<int> preprocCols1() const {
        std::vector<int> res(cols);
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows/2; j++) {
                res[i] += data[j*2][i] * data[j*2+1][i];
            }
        }
        return res;
    }

    std::vector<int> preprocRows2() const {
        std::vector<int> res(rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols>>1; j++) {
                res[i] = res[i] + data[i][j<<1] * data[i][(j<<1)+1];
            }
        }
        return res;
    }

    std::vector<int> preprocCols2() const {
        std::vector<int> res(cols);
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows>>1; j++) {
                res[i] = res[i] + data[j<<1][i] * data[(j<<1)+1][i];
            }
        }
        return res;
    }

    std::vector<int> preprocRows3() const {
        std::vector<int> res(rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 1; j < cols; j += 2) {
                res[i] -= data[i][j-1] * data[i][j];
            }
        }
        return res;
    }

    std::vector<int> preprocCols3() const {
        std::vector<int> res(cols);
        for (int i = 0; i < cols; i++) {
            for (int j = 1; j < rows; j += 2) {
                res[i] -= data[j-1][i] * data[j][i];
            }
        }
        return res;
    }
};

#endif //STUD_96_MATRIX_H
