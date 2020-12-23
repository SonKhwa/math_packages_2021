#include "RigidBody.h"

Matrix star(Triple v) {
    return Matrix{ {{0.0, v.vector[2], -v.vector[1]},
                           {-v.vector[2], 0.0, v.vector[0]},
                           {v.vector[1], -v.vector[0], 0.0}} };
}

RigidBody::RigidBody() {
    mass = -0.707107;
    s = 1;
    Matrix D = {1, 0.5, 0.5, 1, 1, 0.5, 0.5, 0.5 ,1};
    auto V =(double) (1.0/6.0*s*s*s*sqrt(D.det()));
    Ibody = {0.025, 0,0,0,0.025,0,0,0,0.025};
    Ibody.multipleScalar(V/20);
    Ibodyinv = Ibody.inverted();
    L = Triple{6, 6, 6};
    q = {cos(45), 0, 0, 1};
    R = q.toMatrix();
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