#include <iostream>
#include <limits>

#include "Matrix.h"
#include "Timer.h"

void menu()
{
    printf("\nCommands:\n");
    printf("1 - Standard\n");
    printf("2 - Vinograd\n");
    printf("3 - Time\n");
    printf("0 - exit\n");
    printf("Enter the command: ");
}

enum commands
{
    EXIT,
    STANDARD,
    VINOGRAD,
    TIME,
    UNKNOWN_CMD
};

void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    setbuf(stdout, NULL);
    Timer timer;
    int command = UNKNOWN_CMD;
    int rows, cols;

    while (command != EXIT) {
        menu();
        std::cin >> command;
        if (std::cin.fail()) {
            std::cin.clear();
            command = UNKNOWN_CMD;
        }
        ignoreLine();

        switch(command) {
            case STANDARD:
            case VINOGRAD: {
                printf("Enter number of rows and columns of matrix 1: ");
                std::cin >> rows >> cols;
                if (std::cin.fail() || rows <= 0 || cols <= 0) {
                    std::cin.clear();
                    ignoreLine();
                    printf("Read columns and rows failed\n");
                    break;
                }
                Matrix m1(rows, cols);
                printf("Enter elements of matrix 1:\n");
                if (m1.scan() == EXIT_FAILURE) {
                    printf("Read matrix 1 failed\n");
                    break;
                }
                m1.print();

                rows = cols;
                printf("Enter number of columns of matrix 2: ");
                std::cin >> cols;
                if (std::cin.fail() || cols <= 0) {
                    std::cin.clear();
                    ignoreLine();
                    printf("Read columns failed\n");
                    break;
                }
                Matrix m2(rows, cols);
                printf("Enter elements of matrix 2:\n");
                if (m2.scan() == EXIT_FAILURE) {
                    printf("Read matrix 2 failed\n");
                    break;
                }
                m2.print();

                printf("Result:\n");
                Matrix res(m1.rows, m2.cols);
                switch(command) {
                    case STANDARD:
                        Matrix::mulStand(m1, m2, res);
                        break;
                    case VINOGRAD:
                        Matrix::mulVinograd0(m1, m2, res);
                        break;
                }
                res.print();

                break;
            }
            case TIME:
                printf("Measuring time...\n");
                timer.all();
                break;
            case EXIT:
                break;
            default:
                printf("Unknown command!\n");
                break;
        }
    }

    return 0;
}
