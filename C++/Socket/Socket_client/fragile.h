#ifndef FRAGILE_H
#define FRAGILE_H
#include "package.h"

class fragile : public package
{
public:
    fragile(double p);
    double getPrice();
};

#endif // FRAGILE_H
