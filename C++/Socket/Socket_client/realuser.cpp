#include "realuser.h"

realUser::realUser(QString a, QString p, double b, int t):User(a,p,b,t)
{

}
int realUser::getUserType()const{
    return 0;
}
