#include "Search.h"

//创建哈希表
void CreateHashTable(Point *arr[],const char *src, QList<EventInfo> lEvents)
{
    if(src == NULL) return;
    //初始化数组
    int i;
    for(i = 0;i < Number;i++)
    arr[i] = NULL;
    i = 0;
    Point *pTemp = NULL;//记录新添加的节点
    Point *pMark = NULL;//标记添加位置
    while(src[i] != '\0')
    {

        //向Hash_Table添加元素
        pTemp = (Point*)malloc(sizeof(Point));
        pTemp->pNext = NULL;
        pTemp->nValue = i;
        string s = lEvents[i].name.toStdString();
        char * strs = new char[s.length() + 1];
        strcpy(strs, s.c_str());
        strcpy(pTemp->Name, strs);
        if(arr[(int)src[i]] == NULL)
        {
            arr[(int)src[i]] = pTemp;
        }
        else
        {
            pMark = arr[(int)src[i]];
            //找到要插入链表位置的尾，尾添加
            while(pMark->pNext != NULL)
                pMark = pMark->pNext;
            pMark->pNext = pTemp;
        }
        ++i;
    }
}

void HashSearch(Point *arr[],const char ch,int position[], string to_search)
{
    Point *pMark = arr[(int)ch];
    int i = 0;
    while(pMark != NULL)
    {
        string s = pMark->Name;
        if(KMP(to_search, s) != -1){
            position[i] = pMark->nValue;
            ++i;
        }
        pMark = pMark->pNext;
    }
}

int* Search(QList<EventInfo> lEvents, QString scan_string){
    //定义数组
    int *out_id = (int*)malloc(20);
    Point *arr[Number];
    char src[lEvents.size()+1];
    for(int i = 0; i < lEvents.size(); i++){
        QString p = getChineseSpell(lEvents[i].name);
        string temp = p.toStdString();
        src[i] = temp[0];
    }
    src[lEvents.size()] = '\0';
    int position[Number];
    QString s = getChineseSpell(scan_string);
    string to_search = scan_string.toStdString();
    string tmp = s.toStdString();
    char ch = tmp[0];
    //将position数组里的值初始化为-1
    for(int i = 0;i < Number;i++)
        position[i] = -1;
    int k = 0;
    for(int i = 0; i < lEvents.size(); i++){
        string p = lEvents[i].name.toStdString();
        if(KMP(p, to_search) != -1)
            out_id[k++] = i;
    }
    out_id[k] = -1;
    return out_id;
    CreateHashTable(arr, src, lEvents);
    HashSearch(arr, ch, position, tmp);
    int i = 0;
    while(position[i] != -1 && i < Number)
    {
        out_id[i] = position[i];
        ++i;
    }
    out_id[i] = -1;
    DestroyHashTable(arr);
    return out_id;
}

void DestroyHashTable(Point *arr[])
{
    Point *pMark = NULL;
    Point *pDel = NULL;
    for(int i = 0;i < Number;i++)
    {
        pMark = arr[i];
        while(pMark != NULL)
        {
            pDel = pMark;
            pMark = pMark->pNext;
            free(pDel);
            pDel = NULL;
        }

    }
}

QString getChineseSpell(QString& src)
{
    QTextCodec *codec4gbk = QTextCodec::codecForName("GBK"); //获取qt提供的gbk的解码器
    QByteArray buf = codec4gbk->fromUnicode(src); //qt用的unicode，转成gbk
    int size = buf.size();
    quint16 *array = new quint16[size+1];
    QString alphbats;

    for( int i = 0, j = 0; i < buf.size(); i++, j++ )
    {
        if( (quint8)buf[i] < 0x80 ) //gbk的第一个字节都大于0x81，所以小于0x80的都是符号，字母，数字etc
            continue;
        array[j] = (((quint8)buf[i]) << 8) + (quint8)buf[i+1]; //计算gbk编码
        i++;
        alphbats.append( convert( array[j] ) ); //相当于查表，用gbk编码得到首拼音字母
    }
    delete [] array;
    return alphbats;
}

char convert(wchar_t n)
{
    if   (In(0xB0A1,0xB0C4,n))   return   'a';
    if   (In(0XB0C5,0XB2C0,n))   return   'b';
    if   (In(0xB2C1,0xB4ED,n))   return   'c';
    if   (In(0xB4EE,0xB6E9,n))   return   'd';
    if   (In(0xB6EA,0xB7A1,n))   return   'e';
    if   (In(0xB7A2,0xB8c0,n))   return   'f';
    if   (In(0xB8C1,0xB9FD,n))   return   'g';
    if   (In(0xB9FE,0xBBF6,n))   return   'h';
    if   (In(0xBBF7,0xBFA5,n))   return   'j';
    if   (In(0xBFA6,0xC0AB,n))   return   'k';
    if   (In(0xC0AC,0xC2E7,n))   return   'l';
    if   (In(0xC2E8,0xC4C2,n))   return   'm';
    if   (In(0xC4C3,0xC5B5,n))   return   'n';
    if   (In(0xC5B6,0xC5BD,n))   return   'o';
    if   (In(0xC5BE,0xC6D9,n))   return   'p';
    if   (In(0xC6DA,0xC8BA,n))   return   'q';
    if   (In(0xC8BB,0xC8F5,n))   return   'r';
    if   (In(0xC8F6,0xCBF0,n))   return   's';
    if   (In(0xCBFA,0xCDD9,n))   return   't';
    if   (In(0xCDDA,0xCEF3,n))   return   'w';
    if   (In(0xCEF4,0xD188,n))   return   'x';
    if   (In(0xD1B9,0xD4D0,n))   return   'y';
    if   (In(0xD4D1,0xD7F9,n))   return   'z';
    return   '\0';
}

bool In(wchar_t start, wchar_t end, wchar_t code)
{
    if(code >= start && code <= end)
    {
        return true;
    }
    return false;
}

int* getNext(string p)
{
    int* next = new int[p.length()];
    next[0] = -1;
    int j = 0;
    int k = -1;
    while (j < (int)p.length() - 1)
    {
        if (k == -1 || p[j] == p[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
    return next;
}



int KMP(string T,string p)
{
    int i=0;
    int j=0;
    int* next=getNext(T);
    while (i < (int)T.length() && j < (int)p.length())
    {
        if (j == -1 || T[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if (j == (int)p.length())
    {
        return i-j;
    }
    return -1;
}
