#include "RigidBody.h"

Matrix star(Triple v) {
    return Matrix{ {{0.0, -v.vector[2], v.vector[1]},
                           {v.vector[2], 0.0, -v.vector[0]},
                           {-v.vector[1], v.vector[0], 0.0}} };
}

RigidBody::RigidBody() {
    this->mass = 1;
    this->s = SIDE;
    this->h = HEIGHT;
    double y = s / h, theta = 0.0f;
    double Iz = ((3 * mass * h * h) / 5.0f) * (((y * y) / 16.0f) * (1.0f / 3.0f + 1.0f / (tan(PI / 3.0f) * tan(PI / 3.0f))) * (1 + cos(theta)) + sin(theta) * sin(theta));
    theta = PI / 2;
    double Iy = ((3 * mass * h * h) / 5.0f) * (((y * y) / 16.0f) * (1.0f / 3.0f + 1.0f / (tan(PI / 3.0f) * tan(PI / 3.0f))) * (1 + cos(theta)) + sin(theta) * sin(theta)) - mass * 3.0f / 4.0f * 3.0f / 4.0f * h * h;
    double Ix = ((3 * mass * h * h) / 5.0f) * (((y * y) / 16.0f) * (1.0f / 3.0f + 1.0f / (tan(PI / 3.0f) * tan(PI / 3.0f))) * (1 + cos(theta)) + sin(theta) * sin(theta)) - mass * 3.0f / 4.0f * 3.0f / 4.0f * h * h;
    Matrix Ibody = {Ix,0,0,
                    0,Iy,0,
                    0,0,Iz};//tensor inerchii
    this->Ibodyinv = Ibody.inverted();
    this->L = Triple{6, 6, 6};
    this->R = Matrix{1,0,0,0,1,0,0,0,1};
    this->P = Triple{ 0,0,0};
    this->x = {0,0,0};
}

RigidBody RigidBody::f() {
    RigidBody nr;
    nr.x = P.multipleScalar(1 / mass);
    Triple omega = ((R.multipleMatrix(Ibodyinv)).multipleMatrix(R.transposed())).multipleVector(L);
    nr.R = star(omega).multipleMatrix(R);
    nr.P = Triple{0, 0, 0};
    nr.L = Triple{0, 0, 0};
    return nr;
}

RigidBody RigidBody::addRigidBody(RigidBody rb) {
    RigidBody nr;
    nr.x = x.addVector(rb.x);
    nr.R = R.addMatrix(rb.R);
    nr.P = P.addVector(rb.P);
    nr.L = L.addVector(rb.L);
    return nr;
}
RigidBody RigidBody::multipleScalar(double y) {
    RigidBody nr;
    nr.P = P.multipleScalar(y);
    nr.x = x.multipleScalar(y);
    nr.R = R.multipleScalar(y);
    nr.L = L.multipleScalar(y);
    return nr;
}