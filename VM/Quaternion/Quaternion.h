#ifndef VM_QUATERNION_H
#define VM_QUATERNION_H
#include <cmath>
//#include "..//Matrix/Matrix.h"
 class Matrix;
class Quaternion {
public:
    double r;
    double i, j, k;

    Matrix toMatrix();
    Quaternion normalized();
    Quaternion multipleScalar(double x);
    Quaternion multipleQuaternion (Quaternion q);
    Quaternion addQuaternion(Quaternion q);
};

#endif //VM_QUATERNION_H
