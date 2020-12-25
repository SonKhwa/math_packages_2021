#include "Triple.h"

Triple Triple::addVector(Triple nv) {
    return Triple{vector[0] + nv.vector[0],vector[1] + nv.vector[1],vector[2] + nv.vector[2]};
}

Triple Triple::multipleScalar(double x){
    return Triple{vector[0] * x, vector[1] * x, vector[2] * x };
}
/*double Triple::getSum() {
    return (vector[0] + vector[1] + vector[2]);
}
Triple Triple::makeNegative() {
    return Triple{-vector[0], -vector[1], -vector[2]};
}*/