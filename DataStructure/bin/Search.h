#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <string.h>
#include <vector>
#include "eventsql.h"
#include "malloc.h"
#include <QTextCodec>
//#include "mainwindwo.h"
using namespace std;
#define Number 256 //数组大小宏
typedef struct point
{
    struct point *pNext;
    int nValue;
    char Name[20];
}Point;
void CreateHashTable(Point *arr[],const char *src, QList<EventInfo> lEvents);
void HashSearch(Point *arr[],const char ch,int position[], string to_search);
int* Search(QList<EventInfo>, QString scan_string);
int KMP(string, string);
int* getNext(string p);
void DestroyHashTable(Point *arr[]);
QString getChineseSpell(QString& src);
char convert(wchar_t n);
bool In(wchar_t start, wchar_t end, wchar_t code);
#endif // SEARCH_H

