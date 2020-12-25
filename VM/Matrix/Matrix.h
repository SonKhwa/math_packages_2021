#ifndef VM_MATRIX_H
#define VM_MATRIX_H
#include "..//Triple//Triple.h"
#include "../Quaternion/Quaternion.h"
class Matrix {
public:
    double matrix[3][3];
    double det();
    Matrix multipleScalar(double x);
    Matrix multipleMatrix(Matrix m);
    Triple multipleVector(Triple v);
    Matrix addMatrix(Matrix nm);
    Matrix inverted();
    Matrix transposed();
//    Matrix orthogonalityMatrix();
};
#endif //VM_MATRIX_H
