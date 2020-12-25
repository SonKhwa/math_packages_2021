#ifndef VM_TRIPLE_H
#define VM_TRIPLE_H

class Triple {
public:
    double vector[3];
    Triple addVector (Triple nv);
    Triple multipleScalar(double x);
/*    double getSum();
    Triple makeNegative();*/
};


#endif //VM_TRIPLE_H
