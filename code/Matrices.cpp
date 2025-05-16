#include "Matrices.h"

Matrices::Matrix::Matrix(int _rows, int _cols) {
    a.resize(_rows);

    for (int i = 0; i < _rows; i++) {
        a.at(i).resize(_cols, 0);
    }

    rows = _rows;
    cols = _cols;
}

Matrices::Matrix Matrices::operator+(const Matrix& a, const Matrix& b) {
    if ((a.getCols() != b.getCols()) || (a.getRows() != b.getRows())) {
        throw runtime_error("Error: dimensions must agree");
    }
    else {
        int matrixRow = a.getRows();
        int matrixCol = a.getCols();

        Matrices::Matrix c(matrixRow, matrixCol);
        for (int i = 0; i < matrixRow; i++) {
            for (int j = 0; j < matrixCol; j++) {
                c(i, j) = a(i, j) + b(i, j);
            }
        }
        return c;
    }
}

Matrices::Matrix Matrices::operator*(const Matrix& a, const Matrix& b) {
    if (!(a.getCols() == b.getRows())) {
        throw runtime_error("Error: dimensions must agree");
    }
    else {
        int aRow = a.getRows();
        int aCol = a.getCols();
        int bCol = b.getCols();


        Matrices::Matrix c(aRow, bCol);
        double sum;

        for (int i = 0; i < aRow; i++) {
            for (int j = 0; j < bCol; j++) {
                sum = 0;
                for (int k = 0; k < aCol; k++) {
                    sum += a(i, k) * b(k, j);
                };
                c(i, j) = sum;
            }
        }

        return c;
    }
}

bool Matrices::operator==(const Matrix& a, const Matrix& b) {
    bool matching = true;
    if ((a.getCols() != b.getCols()) || (a.getRows() != b.getRows())) {
        matching = false;
    }
    else {
        for (int i = 0; i < a.getRows(); i++) {
            for (int j = 0; j < a.getCols(); j++) {
                if (abs(a(i, j) - b(i, j)) > 0.001) {
                    matching = false;
                }
            }
        }
    }

    return matching;

}

bool Matrices::operator!=(const Matrix& a, const Matrix& b) {
    return (!(a == b));
}

ostream& Matrices::operator<<(ostream& os, const Matrix& a) {
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            os << setw(10) << a(i, j) << " ";
        }
        cout << endl;

    }

    return os;
}

Matrices::RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
    a.at(0).at(0) = cos(theta);
    a.at(0).at(1) = -sin(theta);
    a.at(1).at(0) = sin(theta);
    a.at(1).at(1) = cos(theta);

}

Matrices::ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
    a.at(0).at(0) = scale;
    a.at(0).at(1) = 0;
    a.at(1).at(0) = 0;
    a.at(1).at(1) = scale;
}

Matrices::TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < nCols; j++) {
            if (i == 0) {
                a.at(i).at(j) = xShift;
            }
            else {
                a.at(i).at(j) = yShift;
            }
        }
    }
}