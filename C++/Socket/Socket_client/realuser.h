#ifndef REALUSER_H
#define REALUSER_H


#include "user.h"

class realUser : public User
{
public:
    realUser(QString a, QString p, double b, int t);
    virtual int getUserType()const;
};

#endif // REALUSER_H
