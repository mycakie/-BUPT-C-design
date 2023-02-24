#ifndef MANAGER_H
#define MANAGER_H
#include "user.h"

class manager : public User
{
public:
    manager(QString a, QString p, double b, int t);
    virtual int getUserType()const;
};

#endif // MANAGER_H
