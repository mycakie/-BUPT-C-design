#ifndef BOOK_H
#define BOOK_H
#include "package.h"

class book :public package
{
public:
    book(double p);
    double getPrice();
};

#endif // BOOK_H
