#ifndef VM_RIGIDBODY_H
#define VM_RIGIDBODY_H
#include <iostream>
#include "..//Matrix//Matrix.h"
#include "..//Quaternion//Quaternion.h"
#include "..//Triple//Triple.h"
#define PI 3.14159265358979
#define HEIGHT 10.0f//height
#define SIDE 20.0f//side

struct RigidBody {

    double mass{}, s{}, h{};

    Triple P{};//lin mom
    Triple x{}, L{};
    Matrix Ibodyinv{}, R{};
    RigidBody();
    RigidBody f();
    RigidBody addRigidBody(RigidBody rb);
    RigidBody multipleScalar (double x);
};

#endif //VM_RIGIDBODY_H
