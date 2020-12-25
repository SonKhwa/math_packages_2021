#include <iostream>
#include "Matrix.h"

double Matrix::det() {
    double det = 0.0;

    for (int i = 0; i < 3; i++) {
        int i1, i2, j1, j2;
        if (i == 0) {
            i1 = 1;  i2 = 2;
        }
        else if (i == 1) {
            i1 = 0;  i2 = 2;
        }
        else {
            i1 = 0;  i2 = 1;
        }
        j1 = 1; j2 = 2;
        if (i % 2) {
            det += -(matrix[i1][j1] * matrix[i2][j2] - matrix[i1][j2] * matrix[i2][j1]) * matrix[i][0];
        }
        else {
            det += (matrix[i1][j1] * matrix[i2][j2] - matrix[i1][j2] * matrix[i2][j1]) * matrix[i][0];
        }
    }
    return det;
}

Matrix Matrix::multipleScalar(double x) {
    return Matrix{ {{matrix[0][0] * x, matrix[0][1] * x, matrix[0][2] * x},
                           {matrix[1][0] * x, matrix[1][1] * x, matrix[1][2] * x},
                           {matrix[2][0] * x, matrix[2][1] * x, matrix[2][2] * x}} };
}


Matrix Matrix::multipleMatrix(Matrix m) {
    Matrix nm = { {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}} };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                //nm.matrix[j][i] += matrix[k][i] * m.matrix[j][k];
                nm.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
            }
        }
    }
    return nm;
}

Triple Matrix::multipleVector(Triple v) {
    Triple nv = { {0.0, 0.0, 0.0} };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nv.vector[i] += matrix[i][j] * v.vector[j];
        }
    }
    return nv;
}

Matrix Matrix::inverted() {
    Matrix nm = { {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int i1, i2, j1, j2;
            if (i == 0) {
                i1 = 1;  i2 = 2;
            }
            else if (i == 1) {
                i1 = 0;  i2 = 2;
            }
            else {
                i1 = 0;  i2 = 1;
            }
            if (j == 0) {
                j1 = 1;  j2 = 2;
            }
            else if (j == 1) {
                j1 = 0;  j2 = 2;
            }
            else {
                j1 = 0;  j2 = 1;
            }
            if ((i + j)%2) {
                nm.matrix[j][i] = -(matrix[i1][j1] * matrix[i2][j2] - matrix[i1][j2] * matrix[i2][j1]);
            }
            else {
                nm.matrix[j][i] = (matrix[i1][j1] * matrix[i2][j2] - matrix[i1][j2] * matrix[i2][j1]);
            }
        }
    }

    return (nm.multipleScalar(1/det()));
   /* float nm[3][6] = {0,0,0, 0, 0,0,
                      0,0,0,0, 0,0,
                       0,0, 0,0, 0,0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nm[i][j] = matrix[i][j];
        }
    }
    float temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2 * 3; j++) {
            if (j == (i + 3))
                nm[i][j] = 1;
        }
    }
    float tmp[6];
    for (int i = 3 - 1; i > 0; i--) {
        if (nm[i - 1][0] < nm[i][0]) {
            for (int k = 0; k < 6;k++)
                tmp[k] = nm[i][k];
            for (int k = 0; k < 6;k++) {
                nm[i][k] = nm[i - 1][k];
                nm[i - 1][k] = tmp[k];
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j != i) {
                temp = nm[j][i] / nm[i][i];
                for (int k = 0; k < 2 * 3; k++) {
                    nm[j][k] -= nm[i][k] * temp;
                }
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        temp = nm[i][i];
        for (int j = 0; j < 2 * 3; j++) {
            nm[i][j] = nm[i][j] / temp;
        }
    }
    Matrix rm;
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 6; j++) {
            rm.matrix[i][j - 3] = nm[i][j];
        }
    }
    return rm;*/

}

Matrix Matrix::transposed() {
    Matrix nm = { {{matrix[0][0], matrix[0][1], matrix[0][2]},
                          {matrix[1][0], matrix[1][1], matrix[1][2]},
                          {matrix[2][0], matrix[2][1], matrix[2][2]}} };

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            nm.matrix[i][j] = matrix[j][i];
            nm.matrix[j][i] = matrix[i][j];
        }
    }
    return nm;
}

Matrix Matrix::addMatrix(Matrix nm) {
    Matrix m;
    for (int i = 0; i < 3;i++)
        for (int j = 0; j < 3;j++)
            m.matrix[i][j] = matrix[i][j] + nm.matrix[i][j];
    return m;
}


/*Quaternion Matrix::toQuaternion() {
    float tr = matrix[0][0] + matrix[1][1] + matrix[2][2]; // trace of martix
    if (tr > 0.0f){ // if trace positive than "w" is biggest component
        return Quaternion{ matrix[1][2] - matrix[2][1], matrix[2][0] - matrix[0][2], matrix[0][1] - matrix[1][0], tr + 1.0f};
    }else // Some of vector components is bigger
    if( (matrix[0][0] > matrix[1][1] ) && ( matrix[0][0] > matrix[2][2]) ) {
        return Quaternion{  1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2], matrix[1][0] + matrix[0][1],
             matrix[2][0] + matrix[0][2], matrix[1][2] - matrix[2][1] };
    }else
    if ( matrix[1][1] > matrix[2][2] ){
        return Quaternion{  matrix[1][0] + matrix[0][1], 1.0f + matrix[1][1] - matrix[0][0] - matrix[2][2],
             matrix[2][1] + matrix[1][2], matrix[2][0] - matrix[0][2] };
    }else{
        return Quaternion {  matrix[2][0] + matrix[0][2], matrix[2][1] + matrix[1][2],
             1.0f + matrix[2][2] - matrix[0][0] - matrix[1][1], matrix[0][1] - matrix[1][0] };
    }
}*/
/*Quaternion Matrix::toQuaternion() {
// Преобразование матрицы в кватернион
    Quaternion quat;
    double tr, SIDE, q[4];
    int i, j, k;
    int nxt[3] = {1, 2, 0};
    tr = matrix[0][0] + matrix[1][1] + matrix[2][2];

    if (tr > 0.0) {
        SIDE = sqrt(tr + 1.0);
        quat.r = SIDE / 2.0;
        SIDE = 0.5 / SIDE;
        quat.i = (matrix[1][2] - matrix[2][1]) * SIDE;
        quat.j = (matrix[2][0] - matrix[0][2]) * SIDE;
        quat.k = (matrix[0][1] - matrix[1][0]) * SIDE;
    } else {
        i = 0;
        if (matrix[1][1] > matrix[0][0]) i = 1;
        if (matrix[2][2] > matrix[i][i]) i = 2;
        j = nxt[i];
        k = nxt[j];
        SIDE = sqrt((matrix[i][i] - (matrix[j][j] + matrix[k][k])) + 1.0);
        q[i] = SIDE * 0.5;
        if (SIDE != 0.0) SIDE = 0.5 / SIDE;

        q[3] = (matrix[j][k] - matrix[k][j]) * SIDE;
        q[j] = (matrix[i][j] + matrix[j][i]) * SIDE;
        q[k] = (matrix[i][k] + matrix[k][i]) * SIDE;

        quat.i = q[0];
        quat.j = q[1];
        quat.k = q[2];
        quat.r = q[3];
    }
    return quat;
}*/

/*Matrix Matrix::orthogonalityMatrix() {
    Matrix nm;
    Triple a[3], b[3];
    for (int i = 0;i < 3;i++)
        a[i] = Triple{matrix[0][i], matrix[1][i], matrix[2][i]};
    b[0] = a[0];
    b[1] = a[1].addVector(b[0].multipleScalar(a[1].addVector(b[0]).getSum()/b[0].addVector(b[0]).getSum()).makeNegative());
    b[2] = a[2].addVector(b[0].multipleScalar(a[2].addVector(b[0]).getSum()/b[0].addVector(b[1]).getSum()).makeNegative()).addVector(b[1].multipleScalar(a[2].addVector(b[1]).getSum()/b[1].addVector(b[1]).getSum()).makeNegative());
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            nm.matrix[j][i] = b[i].vector[j];
        }
    }
    return nm;
}*/