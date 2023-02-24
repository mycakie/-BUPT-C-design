#include "courier.h"

courier::courier(QString a, QString p, double b, int t):User(a,p,b,t)
{

}

int courier::getUserType()const{
    return 2;
}

