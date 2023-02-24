#ifndef FILECOMPRESS_H
#define FILECOMPRESS_H


#include <QMainWindow>
#include<QMessageBox>
#include<QFile>
#include<QDataStream>
#include<QString>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#include<ctime>
#include <QtCore/qmath.h>

using namespace std;

struct HuffmanTreeNode
{
    pair<unsigned char, int>Weight;  //记录字符和其权重
    string zippassword;                //等待获取的哈夫曼编码
    HuffmanTreeNode* leftson;   //左儿子指针
    HuffmanTreeNode* rightson;  //右儿子指针
    bool tag;               //是否为叶子结点的标记，true为非叶子结点
};
//哈夫曼树结点

class FileCompress : public QWidget
{
    Q_OBJECT
public:
    explicit FileCompress(QWidget *parent = nullptr);
    void zip(QString path);        //压缩函数
    void unzip(QString path);   //解压函数
protected:
    void DEL(HuffmanTreeNode*& root);
    //在每次压缩后需要delete掉申请空间的哈夫曼树指针，采用递归遍历进行delete

    void BinaryString_Init();
    //二进制字符串的初始化，即从传入文件得到的字符串按照哈夫曼编码获取二进制字符串

    void Weightmap_Init(QFile& in);
    //参数是QFile型，是Qt的文件操作，该函数打开传入文件，遍历，形成一个字符串，并且初始化WeightMap

    HuffmanTreeNode* MakehuffmanTreeNode(int i);
    //该函数的功能是创建单个哈夫曼树结点

    void HuffmanTreeVector_Init();
    //将创建的哈夫曼结点放入Vector中

    void HuffmanTree_Init();
    //建立哈夫曼树的函数

    void ZipPassword_Init(HuffmanTreeNode* &root, string& password);
    //对建成的哈夫曼树进行遍历，更新每个结点的zippassword,即哈夫曼编码

private:
    map<unsigned char, int> weightmap;  //权重映射
    map<unsigned char, string>passwordmap;  //哈夫曼编码映射
    string source_string;       //读取传入文件形成的字符串
    string binary_string;      //通过哈夫曼编码映射形成的二进制字符串
    vector<HuffmanTreeNode* > container;  //哈夫曼结点储存的容器
    map<string, int> zippassword;       //解压时建立的解码映射
signals:
    void error();                      //信号
    void mysignal(double per);  //信号
public slots:
};


#endif // FILECOMPRESS_H
