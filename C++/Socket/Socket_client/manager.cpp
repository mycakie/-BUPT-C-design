#include "manager.h"

manager::manager(QString a, QString p, double b, int t):User(a,p,b,t)
{

}

int manager::getUserType()const{
    return 1;
}
