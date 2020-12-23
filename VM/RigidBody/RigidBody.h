#ifndef VM_RIGIDBODY_H
#define VM_RIGIDBODY_H
#include <iostream>
#include "..//Matrix//Matrix.h"
#include "..//Quaternion//Quaternion.h"
#include "..//Triple//Triple.h"

struct RigidBody {

    double mass, s;

    Triple P;//lin mom
    Triple x, L;
    Quaternion q;
    Matrix Ibody, Ibodyinv, R;

    RigidBody();
    RigidBody f();
    RigidBody addRigidBody(RigidBody rb);
    RigidBody multipleScalar (double x);
};

#endif //VM_RIGIDBODY_H
