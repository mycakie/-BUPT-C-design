#include "update.h"
#include "ui_update.h"
#include <QDir>
#include <QtDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
update::update(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update)
{

    ui->setupUi(this);
    com=new FileCompress();
    //获取当前应用程序所在目录
    m_strDataPath = QApplication::applicationDirPath()+"/file/";
    m_strunPath = QApplication::applicationDirPath()+"/uncompressfile/";
    QDir d(m_strDataPath);
    QDir t(m_strunPath);
    if(!d.exists())
    {
        d.mkdir(m_strDataPath);
    }
    if(!t.exists())
    {
        t.mkdir(m_strunPath);
    }
    connect(&m_timer,&QTimer::timeout,this,&update::updateFile);
    m_timer.start(1000);
    updateFile();
}

update::~update()
{
    delete ui;
    delete com;
}

void update::updateFile()
{
    QDir d(m_strDataPath);
    QStringList lFilter;
    lFilter<<"*.txt"<<"*.jpg"<<"*.docx"<<"*.HuffmanZip"<<"*.bmp";
    QFileInfoList lFileInfo = d.entryInfoList(lFilter,QDir::Files);
    QString strFilter = ui->lineEdit->text();

    m_model.clear();
    QList<QStandardItem*> lRow;
    for(int i = 0;i<lFileInfo.size();i++)
    {
        lRow.clear();
        QFileInfo &info = lFileInfo[i];
        if(!info.completeBaseName().contains(strFilter))
            continue;
        QStandardItem *p1 = new QStandardItem(info.baseName());
        QStandardItem *p2 = new QStandardItem(info.absoluteFilePath());
        QStandardItem *p3 = new QStandardItem(info.birthTime().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p4 = new QStandardItem(QString::number(info.size()/1024)+"KB");
        QStandardItem *p5 = new QStandardItem(info.lastModified().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p6 = new QStandardItem(info.completeSuffix());
        lRow<<p1<<p2<<p3<<p4<<p5<<p6;
        m_model.appendRow(lRow);
    }
    QStringList lHeaders{"文件名","绝对路径","创建日期","文件大小","最后一次修改","文件类型"};
    m_model.setHorizontalHeaderLabels(lHeaders);
    ui->tableView->setModel(&m_model);
}

void update::on_btn_update_clicked()
{
    auto strPath = QFileDialog::getOpenFileName(nullptr,"文件上传",QDir::homePath(),"All files(*.*)");
    QString afterPath = strPath+".HuffmanZip";
    if(strPath.isEmpty())
        return;
    com->zip(strPath);
    auto uploadPath = m_strDataPath + strPath.section("/",-1)+".HuffmanZip";

    //判断缓存目录中是否有相同文件名的文件
    if(QFile::exists(uploadPath))
    {
        QMessageBox::warning(nullptr,"文件已存在","请重新命名");
        return;
    }
    bool ret =  QFile::copy(afterPath,uploadPath);
    QMessageBox::warning(nullptr,"信息",ret?"成功":"上传失败");
    qDebug()<<"用户上传了学习资料";
}

void update::on_pushButton_clicked()
{
    auto strPath = QFileDialog::getOpenFileName(nullptr,"文件解压",m_strDataPath,"All files(*.*)");
    if(strPath.isEmpty())
        return;
    auto uploadPath = m_strunPath + strPath.section("/",-1);
    com->unzip(strPath);
    strPath.chop(11);
    strPath.insert(strPath.lastIndexOf('.'),"(New)");
    uploadPath.chop(11);
    uploadPath.insert(uploadPath.lastIndexOf('.'),"(New)");
    bool ret = QFile::copy(strPath,uploadPath);
    QMessageBox::warning(nullptr,"信息",ret?"成功":"解压失败");
}

void update::on_search_clicked()
{
    QDir d(m_strDataPath);
    QStringList lFilter;
    lFilter<<"*.txt"<<"*.jpg"<<"*.docx"<<"*.HuffmanZip"<<"*.bmp";
    QFileInfoList lFileInfo = d.entryInfoList(lFilter,QDir::Files);
    QString strFilter = ui->lineEdit->text();

    m_model.clear();
    QList<QStandardItem*> lRow;
    for(int i = 0;i<lFileInfo.size();i++)
    {
        lRow.clear();
        QFileInfo &info = lFileInfo[i];
        if(!info.completeBaseName().contains(strFilter))
            continue;
        QStandardItem *p1 = new QStandardItem(info.baseName());
        QStandardItem *p2 = new QStandardItem(info.absoluteFilePath());
        QStandardItem *p3 = new QStandardItem(info.birthTime().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p4 = new QStandardItem(QString::number(info.size()/1024)+"KB");
        QStandardItem *p5 = new QStandardItem(info.lastModified().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p6 = new QStandardItem(info.completeSuffix());
        lRow<<p1<<p2<<p3<<p4<<p5<<p6;
        m_model.appendRow(lRow);
    }
    QStringList lHeaders{"文件名","绝对路径","创建日期","文件大小","最后一次修改","文件类型"};
    m_model.setHorizontalHeaderLabels(lHeaders);
    ui->tableView->setModel(&m_model);
}
