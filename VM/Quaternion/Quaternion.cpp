#include "Quaternion.h"
#include "../Matrix/Matrix.h"

Quaternion Quaternion::normalized() {
    Quaternion nq = Quaternion{0.0, 0.0, 0.0, 0.0};
    double norm = sqrt(pow(r, 2) + pow(i, 2) + pow(j, 2) + pow(k, 2));
    if (norm != 0) {
        nq.r = r / norm;
        nq.i = i / norm;
        nq.j = j / norm;
        nq.k = k / norm;
    }
    return nq;
}

Quaternion Quaternion::multipleScalar(double x) {
    return Quaternion{ r * x, i * x, j * x, k * x };
}

Quaternion Quaternion::multipleQuaternion (Quaternion q) {
    return Quaternion{r * q.r - i * q.i - j * q.j - k * q.k,r * q.i + i * q.r + j * q.k - k * q.j, r * q.j - i * q.k + j * q.r + k * q.i, r * q.k + i * q.j - j * q.i + k * q.r };
}

Quaternion Quaternion::addQuaternion(Quaternion q) {
    return Quaternion {r + q.r, i + q.i, j + q.j, k + q.k};
}

Matrix Quaternion::toMatrix() {
        Matrix nm;
        nm.matrix[0][0] = 1 - 2 * j * j - 2 * k * k;
        nm.matrix[0][1] = 2 * i * j - 2 * r * k;
        nm.matrix[0][2] = 2 * i * k + 2 * r * j;
        nm.matrix[1][0] = 2 * i * j + 2 * r * k;
        nm.matrix[1][1] = 1 - 2 * i * i - 2 * k * k;
        nm.matrix[1][2] = 2 * j * k - 2 * r * i;
        nm.matrix[2][0] = 2 * i * k - 2 * r * j;
        nm.matrix[2][1] = 2 * j * k + 2 * r * i;
        nm.matrix[2][2] = 1 - 2 * i * i - 2 * j * j;
        return nm;

}