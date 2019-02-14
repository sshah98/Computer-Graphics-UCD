#include "matrix.h"

Matrix::Matrix() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            coeff[i][j] = 0.0f;
        }
    }
}

Matrix::Matrix(float m_coeff[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            coeff[i][j] = m_coeff[i][j];
        }
    }
}

Matrix::~Matrix() {}

const Matrix Matrix::Identity() const {

    float ident[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

    return Matrix(ident);
}

std::ostream &operator<<(std::ostream &ostr, Matrix m) {
    ostr << "[";
    for (int i = 0; i < 3; i++) {
        ostr << m[i];
    }
    ostr << "]";

    return ostr;
}

const Vector Matrix::operator[](int i) const {
    /**
      implemented
    */
    return Vector(coeff[i][0], coeff[i][1], coeff[i][2]);
}

const Vector Matrix::column(int j) const {
    /**
      implemented
    */
    return Vector(coeff[j][0], coeff[j][1], coeff[j][2]);
}

const Point operator*(const Matrix &m, const Point &p) {
    /**
      implemented
    */
    float q[3];
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            q[i] += m[i][j] * p[j];
        }
    }

    return Point(q[0], q[1], q[2]);

}

const Vector operator*(const Matrix &m, const Vector &v) {
    /**
      implemented
    */

    float u[3];
    for(int i=0; i<3;i++) {
        u[i] = m[i].dot(v);
    }
    return Vector(u[0], u[1], u[2]);
}

const Matrix operator*(const Matrix &m, const Matrix &n) {
    Matrix a;
    /**
      implemented
    */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a.coeff[i][j]=0;
            for (int k = 0; k < 3; k++) {
                a.coeff[i][j] += m.coeff[i][k] * n.coeff[k][j];
            }
        }
    }
    return a;
}

const Matrix operator+(const Matrix &m, const Matrix &n) {
    Matrix a;
    /**
       implemented
    */
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            a.coeff[i][j] = (m.coeff[i][j] + n.coeff[i][j]);
        }
    }
    return a;
}

const Matrix operator-(const Matrix &m, const Matrix &n) {
    Matrix a;
    /**
        implemented
    */
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            a.coeff[i][j] = (m.coeff[i][j] - n.coeff[i][j]);
        }
    }
    return a;
}
