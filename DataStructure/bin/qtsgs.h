#pragma once

#include "utf.h"
#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>
#include "ui_qtsgs.h"
#include "navigation.h"
#include "mainwindwo.h"
class QtSGS : public QWidget
{
    Q_OBJECT

public:
    QtSGS(QWidget *parent = Q_NULLPTR);
    void timerEvent(QTimerEvent*);
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent*);
    bool SearchJudge();//������ǰ���ж�
    void clearFinalRoad();//��յ���·��
    int CaculateDirection(int, int, int, int);//�����н�����
    bool checkBusLeaveTime(bool, bool);//��ⲻͬУ����У���͹����ķ���ʱ��
    void WriteData();//����Ϣд����־�ļ�
private:
    Ui::QtSGSClass* ui;
//    MainWindwo switchToNvg;
    QImage B_Img;//������ɳ�ӵ�ͼ
    QImage S_Img;
    QRect BRec;//������ͼ��ͼƬλ��
    QRect SRec;
    Road FinalRoad[2 * NodeCount];
    int FinalRoadCount;//�ܹ��߹��Ľ��
    int CurrentRoadNum;//��ǰ������λ��
    double StuX, StuY;//ģ���н�����������
    double StuSpeed;//ģ���н��������ٶ�
    int waitingCount;//���ڼ�������ȴ��ļ�ʱ��
    bool Simulation;//ģ���н�״̬����������ɨ�踽��������
    bool BusLeave;//��ʾ�Ƿ����ϳ����뿪
    bool NowArea;
    bool RideBike;
    int StartNodeNum;//�������
    int PassNodeNum;//;�������
    int EndNodeNum;//�յ�����
    int day,hour, minute, second;//ʱ����
    int TimerID;//��ʱ��ID
    Road ScanRoad[B_NodeNum];
    bool ShowScanRoad;
    int ScanRoadCount;
public slots:
    void TimerFaster();//�ӿ�����ʱ��
    void TimerSlower();//��������ʱ��
    void clickScanService();//ɨ�踽���ķ�����ʩ
    void clickStartSearch();//����������ť�󴥷��ĺ���
    void clickSwitchButton();//����ֹͣ���������ĺ���
    void clickStopSearchButton();
    void changeStartNodeNum();//������������κβ���������¶�Ӧ����Ϣ
    void changePassNodeNum();
    void changeEndNodeNum();
private slots:
    void on_pushButton_clicked();
    void on_changeTimeF_2_clicked();
    void on_changeTimeF_3_clicked();
};
