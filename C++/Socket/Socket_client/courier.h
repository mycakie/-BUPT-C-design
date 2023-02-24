#ifndef COURIER_H
#define COURIER_H

#include "user.h"

class courier : public User
{
public:
    courier(QString a, QString p, double b, int t);
    virtual int getUserType()const;
};

#endif // COURIER_H
