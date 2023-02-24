#include "filecompress.h"

//该函数将二进制串转为int型，即将压缩时每8个二进制位的字符串转化为ASCII码，传入压缩后的文件
int binarystringtoint(string binarystring)
{
    int sum = 0;
    int bssize = binarystring.size();
    for (int i = 0; i <  bssize ; i++)
    {
        if (binarystring[i] == '1')
        {
            int j = qPow(2, binarystring.size() - i - 1);
            sum += j;
        }
    }
    return sum;
}

//int转化为string，是上面那个函数的反操作，在解压时使用
string inttobinarystring(int value)
{
    string binarystring;
    while (value > 0)
    {
        int r = value % 2;
        if (r == 1)binarystring.insert(0, 1, '1');
        else binarystring.insert(0, 1, '0');
        value = value / 2;
    }
    if (binarystring.size() < 8)
    {
        binarystring.insert(0, 8 - binarystring.size(), '0');
    }
    return binarystring;
}
//这个函数是哈夫曼结点间比较的依据，作为sort函数的参数
bool compare(HuffmanTreeNode* node1, HuffmanTreeNode* node2)
{
    return node1->Weight.second < node2->Weight.second;
}

FileCompress::FileCompress(QWidget *parent) : QWidget(parent)
{

}
//这是删除整颗哈夫曼树的函数
void FileCompress::DEL(HuffmanTreeNode*& root)
{
    if(root==NULL) return;
    DEL(root->leftson);
    DEL(root->rightson);
    delete root;
}
//此函数功能为sourcestring按照哈夫曼编码映射初始化类中的binarystring
void FileCompress:: BinaryString_Init()
{
    int k = source_string.size();
    for (int i = 0; i < k; i++)
    {
        binary_string+= passwordmap[source_string[i]];
    }
}
//权重映射的初始化
void FileCompress::Weightmap_Init(QFile& in)
{
        QByteArray a;
        while (!in.atEnd())
        {
            a=in.read(1024);
            //一次性读取1024个字节，不足1024个字节则读取全部

            string b=a.toStdString();
            //转换为我们亲切的string
            int bsize = b.size();
            for(int i=0;i< bsize;i++)
            {
                unsigned char ch=b[i];
                source_string += ch;
                weightmap[ch]++;
            }
        }
}
//建立哈夫曼结点函数：进行初始化操作
HuffmanTreeNode* FileCompress::MakehuffmanTreeNode(int i)
{
    HuffmanTreeNode* huffman = new HuffmanTreeNode;
    huffman->Weight.first = i;
    huffman->Weight.second = weightmap[i];
    huffman->tag = 0;
    huffman->leftson = NULL;
    huffman->rightson = NULL;
    return huffman;
}
//初始化结点容器
 void FileCompress::HuffmanTreeVector_Init()
 {
     for (map<unsigned char, int>::iterator it = weightmap.begin(); it != weightmap.end(); it++)
         {
             HuffmanTreeNode* huffman = MakehuffmanTreeNode(it->first);
             container.push_back(huffman);
         }
 }
//建立哈夫曼树的函数，基本上就是原理的实现
 void FileCompress::HuffmanTree_Init()
 {
     while (container.size() != 1)
         {
             sort(container.begin(), container.end(), compare);
             int sum = container[0]->Weight.second + container[1]->Weight.second;
             HuffmanTreeNode* newhuffman = new HuffmanTreeNode;
             newhuffman->Weight.second = sum;
             newhuffman->Weight.first = 0;
             newhuffman->tag = 1;
             newhuffman->leftson = container[0];
             newhuffman->rightson = container[1];
             container.erase(container.begin());
             container.erase(container.begin());
             container.push_back(newhuffman);
         }
 }
//递归更新哈夫曼编码函数：这个函数的关键是每次递归返回时password进行一次pop操作
 void FileCompress::ZipPassword_Init(HuffmanTreeNode* &root, string& password)
 {
     if (root != NULL && !root->tag)
         {
             root->zippassword = password;
             passwordmap[root->Weight.first] = password;
         }
         if (root->leftson != NULL)
         {
             ZipPassword_Init(root->leftson, password += "0");
             password.pop_back();
         }
         if (root->rightson != NULL)
         {
             ZipPassword_Init(root->rightson, password+="1");
             password.pop_back();
         }
 }
//压缩
 void FileCompress::zip(QString path)
 {
     clock_t begin=clock();
     QFile openfile(path);
     if(!openfile.open(QIODevice::ReadOnly))
     {
         QMessageBox::information(NULL,QString("警告"),QString("文件打开失败"));
         emit error();
         return;
     }
     Weightmap_Init(openfile);
     emit mysignal(10);
     HuffmanTreeVector_Init();
     emit mysignal(20);
     HuffmanTree_Init();
     emit mysignal(30);
     string empty="";
     ZipPassword_Init(container[0],empty);
     emit mysignal(40);
     BinaryString_Init();
     emit mysignal(50);
     path+=".HuffmanZip";
     openfile.close();
     QFile savefile(path);
     savefile.open(QIODevice::WriteOnly);
     QDataStream out(&savefile);
     int size = passwordmap.size();
         if (size == 256) size = 0;
         int length = 0;
         out<<size;
         length++;
         double k=1;
         for (map<unsigned char, string>::iterator it = passwordmap.begin(); it != passwordmap.end(); it++)
         {
             emit mysignal(50+double(25*k++)/passwordmap.size());
             int first = it->first;
             out<<first;
             length++;
             string second = it->second;
             int size = second.size();
             out<<size;
             length++;
             int n = 8 - second.size() % 8;
             if (n)
             {
                 second.append(n, '0');
             }
             int sdsize = second.size();
             for (int i = 0; i < sdsize ; i += 8)
             {
                 string k = second.substr(i, 8);
                 int temp = binarystringtoint(k);
                 unsigned char ch = temp;
                 out<<ch;
                 length++;
             }
         }
         int n = 8 - binary_string.size() % 8;
         if (n)
         {
             binary_string.append(n, '0');
         }
         length++;
         int totalbitsize = binary_string.size() / 8;
         int bslength = binary_string.size() ;
         for (int i = 0; i < bslength ; i += 8)
         {
             emit mysignal(75+double(25*i)/binary_string.size());
             string k = binary_string.substr(i, 8);
             int temp = binarystringtoint(k);
             unsigned char ch = temp;
             out<<ch;
             length++;
         }
         unsigned char temp=n;
         out<<temp;
         length++;
         emit mysignal(100);
         int newlength=savefile.size();
         savefile.close();
         clock_t end=clock();
         QString tip("理论压缩比:");
         tip+=QString::number(double(totalbitsize * 100) / source_string.size());
         tip+="%,实际压缩比：";
         tip+=QString::number(double(newlength * 100) / source_string.size());
         tip+="%,压缩用时：";
         tip+=QString::number(double(end-begin)/CLOCKS_PER_SEC);
         tip+="s";
         QMessageBox::about(this,"压缩说明",tip);
         weightmap.clear();
         passwordmap.clear();
         source_string.clear();
         binary_string.clear();
         DEL(container[0]);
         container.clear();
 }
//解压
 void FileCompress::unzip(QString path)
 {
     clock_t begin=clock();
     if(path.right(11)!=".HuffmanZip")
     {
         QMessageBox::information(NULL,QString("警告"),QString("此文件非哈夫曼压缩文件，打开失败"));
         emit error();
         return;
     }
     QFile openfile(path);
     if(!openfile.open(QIODevice::ReadOnly))
     {
         QMessageBox::information(NULL,QString("警告"),QString("文件打开失败"));
         emit error();
         return;
     }
     QDataStream in(&openfile);
     int zipmapsize;
     in>>zipmapsize;
         if (zipmapsize == 0) zipmapsize = 256;
         for (int i = 1; i <= zipmapsize; i++)
         {
             int zipkey;
             in>>zipkey;
             int valuelength;
             in>>valuelength;
             string valuestring;
             for (int i = 1; i <= valuelength / 8 + 1; i++)
             {
                emit mysignal(double(20*i)/(valuelength/8 +1));
                unsigned char ch;
                in>>ch;
                int zipvalue=ch;
                 valuestring += inttobinarystring(zipvalue);
             }
             valuestring.erase(valuelength, valuestring.size() - valuelength + 1);
             zippassword[valuestring] = zipkey;
         }
         string zipstring;
         while (!in.atEnd())
         {
             unsigned char ch;
             in>>ch;
             int bit=ch;
             zipstring += inttobinarystring(bit);
         }
         emit mysignal(50);
         int zerosize = binarystringtoint(zipstring.substr(zipstring.size() - 8));
         zipstring.erase(zipstring.size() - zerosize - 8, zerosize + 8);
         openfile.close();
         path.chop(11);
         path.insert(path.lastIndexOf('.'),"(New)");
         QFile savefile(path);
         savefile.open(QIODevice::WriteOnly);
         string str;
         int zssize = zipstring.size();
         for (int i = 0; i < zssize; i++)
         {
             emit mysignal(50+double(50*i)/zipstring.size());
             str += zipstring[i];
             map<string, int>::iterator it = zippassword.find(str);
             if (it != zippassword.end())
             {
                 unsigned char temp=it->second;
                 savefile.write(reinterpret_cast<char*>(&temp),1);
                 str.clear();
             }
         }
         emit mysignal(100);
         savefile.close();
         clock_t end=clock();
         QString tip="解压用时:";
         tip+=QString::number(double(end-begin)/CLOCKS_PER_SEC);
         tip+="s";
         QMessageBox::about(this,"解压说明",tip);
         zippassword.clear();
 }
