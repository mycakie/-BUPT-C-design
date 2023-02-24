#include "qtsgs.h"

QtSGS::QtSGS(QWidget* parent)
    : QWidget(parent), ui(new Ui::QtSGSClass)
{
    ui->setupUi(this);
    B_Img = QImage(":/img/B_Map.png");
    S_Img = QImage(":/img/S_Map.png");
    BRec = QRect(0, 0, 466, 700);
    SRec = QRect(0, 0, 583, 339);
    NowArea = true;
    Simulation = false;
    ShowScanRoad = false;
    BusLeave = false;
    RideBike = false;
    StartNodeNum = -1;
    PassNodeNum = -1;
    EndNodeNum = -1;
    CurrentRoadNum = 0;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
    StuX = -50;
    StuY = -50;
    StuSpeed = 1.2;
    FinalRoadCount = 0;
    ScanRoadCount = 0;
    ui->changeTimeF->setEnabled(true);
    ui->StopSearch->setEnabled(false);
    ui->SwitchMap->setEnabled(true);
    connect(ui->changeTimeF, SIGNAL(clicked()), this, SLOT(TimerFaster()));
    connect(ui->StartSearch, SIGNAL(clicked()), this, SLOT(clickStartSearch()));
    connect(ui->SwitchMap, SIGNAL(clicked()), this, SLOT(clickSwitchButton()));
    connect(ui->StartBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeStartNodeNum()));
    connect(ui->PassBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changePassNodeNum()));
    connect(ui->EndBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeEndNodeNum()));
    connect(ui->StopSearch, SIGNAL(clicked()), this, SLOT(clickStopSearchButton()));
    TimerID = startTimer(1000/360);
}

void QtSGS::timerEvent(QTimerEvent* e)
{
    if (e->timerId() == TimerID)
    {
        second++;
        if (second == 60)
        {
            second = 0;
            minute++;
            if (minute == 60)
            {
                minute = 0;
                hour++;
                if (hour == 24)
                {
                    hour = 0;
                    day++;
                    if (day == 8)
                        day = 1;
                }
            }
        }
        if (Simulation)//如果开始模拟行进
        {

            if (FinalRoad[CurrentRoadNum].NodeNum < B_NodeNum)
                NowArea = true;
            else
                NowArea = false;
            if ((FinalRoad[CurrentRoadNum].NodeNum == 114 || FinalRoad[CurrentRoadNum].NodeNum == 131 ||
                FinalRoad[CurrentRoadNum].NodeNum == 165 || FinalRoad[CurrentRoadNum].NodeNum == 180) &&
                FinalRoad[CurrentRoadNum].WaitCount > 0)
            {
                if (BusLeave || checkBusLeaveTime(FinalRoad[CurrentRoadNum].NodeNum < B_NodeNum, FinalRoad[CurrentRoadNum].NodeNum == 114 || FinalRoad[CurrentRoadNum].NodeNum == 165))
                {
                    FinalRoad[CurrentRoadNum].WaitCount--;
                    if (FinalRoad[CurrentRoadNum].WaitCount == 0)
                        BusLeave = false;
                }
            }
            else if (CurrentRoadNum >= FinalRoadCount)
            {
                Simulation = false;
                ui->StartSearch->setEnabled(true);
                ui->StopSearch->setEnabled(false);
                ui->SwitchMap->setEnabled(true);
                BusLeave = false;
                clearFinalRoad();
                StuX = -50;
                StuY = -50;
                CurrentRoadNum = 0;
                FinalRoadCount = 0;
            }
            else
            {
                double Speed = StuSpeed / FinalRoad[CurrentRoadNum].Crowed;
                switch (FinalRoad[CurrentRoadNum].MoveDirection)
                {
                case 8:
                    StuX = FinalRoad[CurrentRoadNum].LX;
                    StuY = StuY - Speed;
                    if (StuY <= FinalRoad[CurrentRoadNum + 1].LY)
                    {
                        CurrentRoadNum++;
                        StuY = FinalRoad[CurrentRoadNum].LY;
                    }
                    break;
                case 2:
                    StuX = FinalRoad[CurrentRoadNum].LX;
                    StuY = StuY + Speed;
                    if (StuY >= FinalRoad[CurrentRoadNum + 1].LY)
                    {
                        CurrentRoadNum++;
                        StuY = FinalRoad[CurrentRoadNum].LY;
                    }
                    break;
                case 4:
                    StuX = StuX - Speed;
                    StuY = FinalRoad[CurrentRoadNum].LY;
                    if (StuX <= FinalRoad[CurrentRoadNum + 1].LX)
                    {
                        CurrentRoadNum++;
                        StuX = FinalRoad[CurrentRoadNum].LX;
                    }
                    break;
                case 6:
                    StuX = StuX + Speed;
                    StuY = FinalRoad[CurrentRoadNum].LY;
                    if (StuX >= FinalRoad[CurrentRoadNum + 1].LX)
                    {
                        CurrentRoadNum++;
                        StuX = FinalRoad[CurrentRoadNum].LX;
                    }
                    break;
                default:
                    CurrentRoadNum++;
                    StuX = FinalRoad[CurrentRoadNum].LX;
                    StuY = FinalRoad[CurrentRoadNum].LY;
                    break;
                }
            }
        }
    }
    repaint();
}

void QtSGS::paintEvent(QPaintEvent*)
{
    QPainter pt(this);
    QString str = QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second);
    QString week_day;
    switch (day)
    {
    case 1:
        week_day = "Monday";
        break;
    case 2:
        week_day = "Tuesday";
        break;
    case 3:
        week_day = "Wednesday";
        break;
    case 4:
        week_day = "Thursday";
        break;
    case 5:
        week_day = "Friday";
        break;
    case 6:
        week_day = "Saturday";
        break;
    case 7:
        week_day = "Sunday";
        break;
    }
    ui->Weekday->setText(week_day);
    ui->VirtualTime->setText(str);
    if (NowArea)
        pt.drawImage(BRec, B_Img);
    else
        pt.drawImage(SRec, S_Img);
    QFont fo("新宋体", 12, QFont::Bold, true);
    pt.setFont(fo);
    pt.setPen(Qt::black);
    if (!BusLeave && FinalRoad[CurrentRoadNum].WaitCount == 0)
        pt.drawText(585, 40, tr("Not Moving"));
    else if(!BusLeave && FinalRoad[CurrentRoadNum].WaitCount != 0)
        pt.drawText(585, 40, tr("Waiting"));
    else if(BusLeave)
    {
        pt.setPen(Qt::red);
        pt.drawText(580, 40, tr("Riding"));
    }
    QBrush br;
    br.setStyle(Qt::SolidPattern);
    br.setColor(Qt::GlobalColor::yellow);
    pt.setBrush(br);
    if (Simulation)
    {
        if (!RideBike)
            pt.drawEllipse(StuX - 5, StuY - 5, 10, 10);
        else
            pt.drawRect(StuX - 5, StuY - 5, 10, 10);
        if (NowArea && FinalRoad[CurrentRoadNum + 1].NodeNum < B_NodeNum && FinalRoad[CurrentRoadNum + 1].NodeNum != -1)
            pt.drawLine(StuX, StuY, FinalRoad[CurrentRoadNum + 1].LX, FinalRoad[CurrentRoadNum + 1].LY);
        else if (!NowArea && FinalRoad[CurrentRoadNum + 1].NodeNum >= B_NodeNum && FinalRoad[CurrentRoadNum + 1].NodeNum != -1)
            pt.drawLine(StuX, StuY, FinalRoad[CurrentRoadNum + 1].LX, FinalRoad[CurrentRoadNum + 1].LY);
        for (int i = CurrentRoadNum + 1; i < FinalRoadCount; i++)
        {
            if (NowArea && ((FinalRoad[i].NodeNum >= B_NodeNum || FinalRoad[i].NodeNum == -1) || (FinalRoad[i + 1].NodeNum >= B_NodeNum || FinalRoad[i + 1].NodeNum == -1)))
                break;
            else if (!NowArea && ((FinalRoad[i].NodeNum < B_NodeNum || FinalRoad[i].NodeNum == -1) || (FinalRoad[i + 1].NodeNum < B_NodeNum || FinalRoad[i + 1].NodeNum == -1)))
                break;
            pt.drawLine(FinalRoad[i].LX, FinalRoad[i].LY, FinalRoad[i + 1].LX, FinalRoad[i + 1].LY);
        }
    }
    if (ShowScanRoad)
    {
        for (int i = 0; i < B_NodeNum; i++)
            if (ScanRoad[i].NodeNum == -1)
                break;
            else
            {
                pt.drawEllipse(ScanRoad[i].LX - 5, ScanRoad[i].LY - 5, 10, 10);

            }
    }
}

void QtSGS::closeEvent(QCloseEvent*)
{
}

bool QtSGS::SearchJudge()//搜索的前置判断
{
    if (ui->NavigationBox->currentIndex() == 0)
    {
        QMessageBox::information(this, "警告", QString("请选择导航策略"));
        return false;
    }
    else if (ui->NavigationBox->currentIndex() == 1 || ui->NavigationBox->currentIndex() == 2)
    {
        if (ui->StartBox->currentIndex() == 0 || ui->EndBox->currentIndex() == 0)
        {
            QMessageBox::information(this, "警告", QString("请选择当前位置和终点位置"));
            return false;
        }
        if (ui->StartBox->currentIndex() == ui->EndBox->currentIndex())
        {
            QMessageBox::information(this, "警告", QString("当前位置和终点位置不能相同"));
            return false;
        }
    }
    else if (ui->NavigationBox->currentIndex() == 3)
    {
        if (ui->StartBox->currentIndex() == 0 || ui->PassBox->currentIndex() == 0 || ui->EndBox->currentIndex() == 0)
        {
            QMessageBox::information(this, "警告", QString("请选择当前位置、途径位置和终点位置"));
            return false;
        }
        if ((ui->StartBox->currentIndex() == ui->PassBox->currentIndex()) || (ui->PassBox->currentIndex() == ui->EndBox->currentIndex()))
        {
            QMessageBox::information(this, "警告", QString("当前位置和途径位置、途径位置和终点位置不能相同"));
            return false;
        }
    }
    else if (ui->NavigationBox->currentIndex() == 4)
    {
        if (ui->StartBox->currentIndex() == 0 || ui->EndBox->currentIndex() == 0)
        {
            QMessageBox::information(this, "警告", QString("请选择当前位置和终点位置"));
            return false;
        }
        if (ui->StartBox->currentIndex() == ui->EndBox->currentIndex())
        {
            QMessageBox::information(this, "警告", QString("当前位置和终点位置不能相同"));
            return false;
        }
        if (ui->StartBox->currentIndex() <= 84 && ui->EndBox->currentIndex() > 84)
        {
            QMessageBox::information(this, "警告", QString("当前策略禁止跨校区"));
            return false;
        }
        if (ui->StartBox->currentIndex() > 84 && ui->EndBox->currentIndex() <= 84)
        {
            QMessageBox::information(this, "警告", QString("当前策略禁止跨校区"));
            return false;
        }
    }
    return true;
}

void QtSGS::clearFinalRoad()//清空导航路线
{
    for (int i = 0; i < 2 * NodeCount; i++)
        FinalRoad[i].NodeNum = -1;//根据NodeNum值判断导航是否结束
    FinalRoadCount = 0;
    ScanRoadCount = 0;
    ShowScanRoad = false;
    RideBike = false;
    for (int j = 0; j < B_NodeNum; j++)
        ScanRoad[j].NodeNum = -1;
}

int QtSGS::CaculateDirection(int x1, int y1, int x2, int y2)//计算行进方向
{
    if (x1 == x2 && y1 < y2)
        return 2;
    else if (x1 == x2 && y1 > y2)
        return 8;
    else if (x1 < x2 && y1 == y2)
        return 6;
    else if (x1 > x2 && y1 == y2)
        return 4;
    return 0;
}

bool QtSGS::checkBusLeaveTime(bool schoolType, bool busType)//检测不同校区内校车和公交的发车时间
{
    BusLeave = true;
    if (schoolType && day >= 1 && day <= 5)//本部
    {
        if (busType)//如果是校车
        {
            if (hour == 6 && minute == 50)
                return true;
            else if (hour == 7 && minute == 0)
                return true;
            else if (hour == 8 && minute == 40)
                return true;
            else if (hour == 12 && minute == 30)
                return true;
        }
        else if (!busType)//如果是公交车
        {
            if (hour >= 7 && hour <= 19 && minute % 10 == 0)
                return true;
        }
    }
    else if (!schoolType && day >= 1 && day <= 5)
    {
        if (busType)//如果是校车
        {
            if (hour == 10 && minute == 10)
                return true;
            else if (hour == 12 && minute == 30)
                return true;
            else if (hour == 16 && minute == 40)
                return true;
            else if (hour == 17 && minute == 40)
                return true;
        }
        else if (!busType)//如果是公交车
        {
            if (hour >= 7 && hour <= 19 && minute % 10 == 0)
                return true;
        }
    }
    BusLeave = false;
    return false;
}

void QtSGS::WriteData()//将信息写入日志文件
{
    std::ofstream OF("./Data.db", std::ios::app);
    //OF.open("./Data.db");
    if (!OF)
    {
        OF.close();
        return;
    }
    Navigation* N = new Navigation();
    OF << "导航开始---->";
    for (int i = 0; i < FinalRoadCount; i++)
    {
        OF << N->BestAnt.MapNodes[FinalRoad[i].NodeNum].Name << "--->";
    }
    OF << "导航结束";
    OF << std::endl << std::endl;
    OF.close();
    delete N;
}

void QtSGS::TimerFaster()//加快虚拟时间
{
    killTimer(TimerID);
    TimerID = startTimer(5);
    ui->changeTimeF->setEnabled(false);
}



void QtSGS::clickStartSearch()//单击搜索按钮后触发的函数
{
    if (!SearchJudge())
        return;
    srand((unsigned)time(NULL));
    if (ui->NavigationBox->currentIndex() == 1)//如果是最短路径策略
    {
        clearFinalRoad();
        Navigation* n = new Navigation();
        n->Search1(StartNodeNum, EndNodeNum, false, (day - 1) * 86400 + hour * 3600 + minute * 60 + second);
        FinalRoad[FinalRoadCount].NodeNum = n->BestAnt.TravelCityNum[0];
        if (StartNodeNum <= 131)
        {
            FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PX;
            FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PY;
        }
        else
        {
            FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PX;
            FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PY;
        }
        FinalRoad[FinalRoadCount].Crowed = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].Crowed;
        FinalRoad[FinalRoadCount].WaitCount = 0;
        FinalRoadCount++;
        for (int i = 0; i < n->BestAnt.TravelCityCount; i++)
        {
            FinalRoad[FinalRoadCount].NodeNum = n->BestAnt.TravelCityNum[i];
            if (FinalRoad[FinalRoadCount].NodeNum <= 131)
            {
                FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LY;
            }
            else
            {
                FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LY;
            }
            FinalRoad[FinalRoadCount].Crowed = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].Crowed;
            FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
                FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
            if (FinalRoad[FinalRoadCount].NodeNum == 114 && n->BestAnt.TravelCityNum[i + 1] == 165)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 131 && n->BestAnt.TravelCityNum[i + 1] == 180)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 165 && n->BestAnt.TravelCityNum[i + 1] == 114)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 180 && n->BestAnt.TravelCityNum[i + 1] == 131)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else
                FinalRoad[FinalRoadCount].WaitCount = 0;
            FinalRoadCount++;
        }
        FinalRoad[FinalRoadCount].NodeNum = FinalRoad[FinalRoadCount - 1].NodeNum;
        if (FinalRoad[FinalRoadCount].NodeNum <= 131)
        {
            FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        else
        {
            FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        FinalRoad[FinalRoadCount].Crowed = FinalRoad[FinalRoadCount - 1].Crowed;
        FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
            FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
        FinalRoad[FinalRoadCount].WaitCount = 0;
        Simulation = true;
        CurrentRoadNum = 0;
        StuX = FinalRoad[0].LX;
        StuY = FinalRoad[0].LY;
        StuSpeed = 1.2;
        BusLeave = false;
        delete n;
        ui->StartSearch->setEnabled(false);
        ui->StopSearch->setEnabled(true);
        ui->SwitchMap->setEnabled(false);
        WriteData();
        repaint();
        return;
    }
    else if (ui->NavigationBox->currentIndex() == 2)//如果是时间最短策略
    {
        clearFinalRoad();
        Navigation* n = new Navigation();
        n->SearchTime(StartNodeNum, EndNodeNum, false, (day - 1) * 86400 + hour * 3600 + minute * 60 + second);
        FinalRoad[FinalRoadCount].NodeNum = n->BestAnt.TravelCityNum[0];
        if (StartNodeNum <= 131)
        {
            FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PX;
            FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PY;
        }
        else
        {
            FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PX;
            FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PY;
        }
        FinalRoad[FinalRoadCount].Crowed = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].Crowed;
        FinalRoad[FinalRoadCount].WaitCount = 0;
        FinalRoadCount++;
        for (int i = 0; i < n->BestAnt.TravelCityCount; i++)
        {
            FinalRoad[FinalRoadCount].NodeNum = n->BestAnt.TravelCityNum[i];
            if (FinalRoad[FinalRoadCount].NodeNum <= 131)
            {
                FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LY;
            }
            else
            {
                FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LY;
            }
            FinalRoad[FinalRoadCount].Crowed = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].Crowed;
            FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
                FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
            if (FinalRoad[FinalRoadCount].NodeNum == 114 && n->BestAnt.TravelCityNum[i + 1] == 165)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 131 && n->BestAnt.TravelCityNum[i + 1] == 180)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 165 && n->BestAnt.TravelCityNum[i + 1] == 114)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 180 && n->BestAnt.TravelCityNum[i + 1] == 131)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else
                FinalRoad[FinalRoadCount].WaitCount = 0;
            FinalRoadCount++;
        }
        FinalRoad[FinalRoadCount].NodeNum = FinalRoad[FinalRoadCount - 1].NodeNum;
        if (FinalRoad[FinalRoadCount].NodeNum <= 131)
        {
            FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        else
        {
            FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        FinalRoad[FinalRoadCount].Crowed = FinalRoad[FinalRoadCount - 1].Crowed;
        FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
            FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
        FinalRoad[FinalRoadCount].WaitCount = 0;
        Simulation = true;
        CurrentRoadNum = 0;
        StuX = FinalRoad[0].LX;
        StuY = FinalRoad[0].LY;
        StuSpeed = 1.2;
        BusLeave = false;
        delete n;
        ui->StartSearch->setEnabled(false);
        ui->StopSearch->setEnabled(true);
        ui->SwitchMap->setEnabled(false);
        WriteData();
        repaint();
        return;
    }
    else if (ui->NavigationBox->currentIndex() == 3)//如果是途径距离最短策略
    {
        clearFinalRoad();
        Navigation* n = new Navigation();
        n->Search1(StartNodeNum, PassNodeNum, false, (day - 1) * 86400 + hour * 3600 + minute * 60 + second);
        FinalRoad[FinalRoadCount].NodeNum = n->BestAnt.TravelCityNum[0];
        if (StartNodeNum <= 131)
        {
            FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PX;
            FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PY;
        }
        else
        {
            FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PX;
            FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].PY;
        }
        FinalRoad[FinalRoadCount].Crowed = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[0]].Crowed;
        FinalRoad[FinalRoadCount].WaitCount = 0;
        FinalRoadCount++;
        for (int i = 0; i < n->BestAnt.TravelCityCount; i++)
        {
            FinalRoad[FinalRoadCount].NodeNum = n->BestAnt.TravelCityNum[i];
            if (FinalRoad[FinalRoadCount].NodeNum <= 131)
            {
                FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LY;
            }
            else
            {
                FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].LY;
            }
            FinalRoad[FinalRoadCount].Crowed = n->BestAnt.MapNodes[n->BestAnt.TravelCityNum[i]].Crowed;
            FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
                FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
            if (FinalRoad[FinalRoadCount].NodeNum == 114 && n->BestAnt.TravelCityNum[i + 1] == 165)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 131 && n->BestAnt.TravelCityNum[i + 1] == 180)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 165 && n->BestAnt.TravelCityNum[i + 1] == 114)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 180 && n->BestAnt.TravelCityNum[i + 1] == 131)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else
                FinalRoad[FinalRoadCount].WaitCount = 0;
            FinalRoadCount++;
        }
        FinalRoad[FinalRoadCount].NodeNum = FinalRoad[FinalRoadCount - 1].NodeNum;
        if (FinalRoad[FinalRoadCount].NodeNum <= 131)
        {
            FinalRoad[FinalRoadCount].LX = 20 + n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 675 - n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        else
        {
            FinalRoad[FinalRoadCount].LX = n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 339 - n->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        FinalRoad[FinalRoadCount].Crowed = FinalRoad[FinalRoadCount - 1].Crowed;
        FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
            FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
        FinalRoad[FinalRoadCount].WaitCount = 0;
        FinalRoadCount++;
        Navigation* na = new Navigation();
        na->Search1(PassNodeNum, EndNodeNum, false, (day - 1) * 86400 + hour * 3600 + minute * 60 + second + n->BestAnt.MoveTime);
        for (int i = 0; i < na->BestAnt.TravelCityCount; i++)
        {
            FinalRoad[FinalRoadCount].NodeNum = na->BestAnt.TravelCityNum[i];
            if (FinalRoad[FinalRoadCount].NodeNum <= 131)
            {
                FinalRoad[FinalRoadCount].LX = 20 + na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 675 - na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LY;
            }
            else
            {
                FinalRoad[FinalRoadCount].LX = na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LX;
                FinalRoad[FinalRoadCount].LY = 339 - na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LY;
            }
            FinalRoad[FinalRoadCount].Crowed = na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].Crowed;
            FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
                FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
            if (FinalRoad[FinalRoadCount].NodeNum == 114 && na->BestAnt.TravelCityNum[i + 1] == 165)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 131 && na->BestAnt.TravelCityNum[i + 1] == 180)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 165 && na->BestAnt.TravelCityNum[i + 1] == 114)
                FinalRoad[FinalRoadCount].WaitCount = 2400;
            else if (FinalRoad[FinalRoadCount].NodeNum == 180 && na->BestAnt.TravelCityNum[i + 1] == 131)
                FinalRoad[FinalRoadCount].WaitCount = 5400;
            else
                FinalRoad[FinalRoadCount].WaitCount = 0;
            FinalRoadCount++;
        }
        FinalRoad[FinalRoadCount].NodeNum = FinalRoad[FinalRoadCount - 1].NodeNum;
        if (FinalRoad[FinalRoadCount].NodeNum <= 131)
        {
            FinalRoad[FinalRoadCount].LX = 20 + na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 675 - na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        else
        {
            FinalRoad[FinalRoadCount].LX = na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
            FinalRoad[FinalRoadCount].LY = 339 - na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
        }
        FinalRoad[FinalRoadCount].Crowed = FinalRoad[FinalRoadCount - 1].Crowed;
        FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
            FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
        FinalRoad[FinalRoadCount].WaitCount = 0;
        Simulation = true;
        CurrentRoadNum = 0;
        StuX = FinalRoad[0].LX;
        StuY = FinalRoad[0].LY;
        StuSpeed = 1.2;
        BusLeave = false;
        delete n;
        ui->StartSearch->setEnabled(false);
        ui->StopSearch->setEnabled(true);
        ui->SwitchMap->setEnabled(false);
        WriteData();
        repaint();
        return;
    }
    else if (ui->NavigationBox->currentIndex() == 4)//如果是最短骑行时间策略
    {
            clearFinalRoad();
            Navigation* na = new Navigation();
            if (!na->BestAnt.MapNodes[StartNodeNum].RideAllow || !na->BestAnt.MapNodes[EndNodeNum].RideAllow)
            {
                QMessageBox::information(this, "警告", QString("当前位置或终点位置不允许骑行"));
                return;
            }
            na->Search2(StartNodeNum, EndNodeNum, true, day * 86400 + hour * 3600 + minute * 60 + second);
            bool FindSuccess = false;
            for (int m = 0; m < na->BestAnt.TravelCityCount; m++)
                if (na->BestAnt.TravelCityNum[m] == EndNodeNum)
                {
                    FindSuccess = true;
                    break;
                }
            if (!FindSuccess)
            {
                QMessageBox::information(this, "错误", QString("没有搜索到可以到达目的地的路线"));
                return;
            }
            FinalRoad[FinalRoadCount].NodeNum = na->BestAnt.TravelCityNum[0];
            if (FinalRoad[FinalRoadCount].NodeNum <= 131)
            {
                FinalRoad[FinalRoadCount].LX = 20 + na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[0]].PX;
                FinalRoad[FinalRoadCount].LY = 675 - na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[0]].PY;
            }
            else
            {
                FinalRoad[FinalRoadCount].LX = na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[0]].PX;
                FinalRoad[FinalRoadCount].LY = 339 - na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[0]].PY;
            }
            FinalRoad[FinalRoadCount].Crowed = na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[0]].Crowed;
            FinalRoad[FinalRoadCount].WaitCount = 0;
            FinalRoadCount++;
            for (int i = 0; i < na->BestAnt.TravelCityCount; i++)
            {
                FinalRoad[FinalRoadCount].NodeNum = na->BestAnt.TravelCityNum[i];
                if (FinalRoad[FinalRoadCount].NodeNum <= 131)
                {
                    FinalRoad[FinalRoadCount].LX = 20 + na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LX;
                    FinalRoad[FinalRoadCount].LY = 675 - na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LY;
                }
                else
                {
                    FinalRoad[FinalRoadCount].LX = na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LX;
                    FinalRoad[FinalRoadCount].LY = 339 - na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].LY;
                }
                FinalRoad[FinalRoadCount].Crowed = na->BestAnt.MapNodes[na->BestAnt.TravelCityNum[i]].Crowed;
                FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
                    FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
                FinalRoad[FinalRoadCount].WaitCount = 0;
                FinalRoadCount++;
            }
            FinalRoad[FinalRoadCount].NodeNum = FinalRoad[FinalRoadCount - 1].NodeNum;
            if (FinalRoad[FinalRoadCount].NodeNum <= 131)
            {
                FinalRoad[FinalRoadCount].LX = 20 + na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
                FinalRoad[FinalRoadCount].LY = 675 - na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
            }
            else
            {
                FinalRoad[FinalRoadCount].LX = na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PX;
                FinalRoad[FinalRoadCount].LY = 339 - na->BestAnt.MapNodes[FinalRoad[FinalRoadCount].NodeNum].PY;
            }
            FinalRoad[FinalRoadCount].Crowed = FinalRoad[FinalRoadCount - 1].Crowed;
            FinalRoad[FinalRoadCount - 1].MoveDirection = CaculateDirection(FinalRoad[FinalRoadCount - 1].LX,
                FinalRoad[FinalRoadCount - 1].LY, FinalRoad[FinalRoadCount].LX, FinalRoad[FinalRoadCount].LY);
            FinalRoad[FinalRoadCount].WaitCount = 0;
            Simulation = true;
            CurrentRoadNum = 0;
            StuX = FinalRoad[0].LX;
            StuY = FinalRoad[0].LY;
            StuSpeed = 2.4;
            BusLeave = false;
            RideBike = true;
            delete na;
            ui->StartSearch->setEnabled(false);
            ui->StopSearch->setEnabled(true);
            ui->SwitchMap->setEnabled(false);
            WriteData();repaint();
            return;
    }
}

void QtSGS::clickSwitchButton()
{
    if (NowArea)
        NowArea = false;
    else
        NowArea = true;
    repaint();
}
 
void QtSGS::clickStopSearchButton()
{
    BusLeave = false;
    this->Simulation = false;
    ui->StartSearch->setEnabled(true);
    ui->StopSearch->setEnabled(false);
    ui->SwitchMap->setEnabled(true);
}

void QtSGS::changeStartNodeNum()//如果下拉框有任何操作。则更新对应的信息
{
    if (ui->StartBox->currentIndex() == 0) StartNodeNum = -1;
    else if (ui->StartBox->currentIndex() == 1) StartNodeNum = 0;
    else if (ui->StartBox->currentIndex() == 2) StartNodeNum = 3;
    else if (ui->StartBox->currentIndex() == 3) StartNodeNum = 4;
    else if (ui->StartBox->currentIndex() == 4) StartNodeNum = 5;
    else if (ui->StartBox->currentIndex() == 5) StartNodeNum = 6;
    else if (ui->StartBox->currentIndex() == 6) StartNodeNum = 7;
    else if (ui->StartBox->currentIndex() == 7) StartNodeNum = 8;
    else if (ui->StartBox->currentIndex() == 8) StartNodeNum = 10;
    else if (ui->StartBox->currentIndex() == 9) StartNodeNum = 12;
    else if (ui->StartBox->currentIndex() == 10) StartNodeNum = 13;
    else if (ui->StartBox->currentIndex() == 11) StartNodeNum = 15;
    else if (ui->StartBox->currentIndex() == 12) StartNodeNum = 16;
    else if (ui->StartBox->currentIndex() == 13) StartNodeNum = 17;
    else if (ui->StartBox->currentIndex() == 14) StartNodeNum = 18;
    else if (ui->StartBox->currentIndex() == 15) StartNodeNum = 20;
    else if (ui->StartBox->currentIndex() == 16) StartNodeNum = 22;
    else if (ui->StartBox->currentIndex() == 17) StartNodeNum = 23;
    else if (ui->StartBox->currentIndex() == 18) StartNodeNum = 24;
    else if (ui->StartBox->currentIndex() == 19) StartNodeNum = 25;
    else if (ui->StartBox->currentIndex() == 20) StartNodeNum = 30;
    else if (ui->StartBox->currentIndex() == 21) StartNodeNum = 31;
    else if (ui->StartBox->currentIndex() == 22) StartNodeNum = 32;
    else if (ui->StartBox->currentIndex() == 23) StartNodeNum = 33;
    else if (ui->StartBox->currentIndex() == 24) StartNodeNum = 34;
    else if (ui->StartBox->currentIndex() == 25) StartNodeNum = 35;
    else if (ui->StartBox->currentIndex() == 26) StartNodeNum = 36;
    else if (ui->StartBox->currentIndex() == 27) StartNodeNum = 37;
    else if (ui->StartBox->currentIndex() == 28) StartNodeNum = 39;
    else if (ui->StartBox->currentIndex() == 29) StartNodeNum = 40;
    else if (ui->StartBox->currentIndex() == 30) StartNodeNum = 42;
    else if (ui->StartBox->currentIndex() == 31) StartNodeNum = 44;
    else if (ui->StartBox->currentIndex() == 32) StartNodeNum = 45;
    else if (ui->StartBox->currentIndex() == 33) StartNodeNum = 46;
    else if (ui->StartBox->currentIndex() == 34) StartNodeNum = 47;
    else if (ui->StartBox->currentIndex() == 35) StartNodeNum = 48;
    else if (ui->StartBox->currentIndex() == 36) StartNodeNum = 51;
    else if (ui->StartBox->currentIndex() == 37) StartNodeNum = 53;
    else if (ui->StartBox->currentIndex() == 38) StartNodeNum = 55;
    else if (ui->StartBox->currentIndex() == 39) StartNodeNum = 57;
    else if (ui->StartBox->currentIndex() == 40) StartNodeNum = 60;
    else if (ui->StartBox->currentIndex() == 41) StartNodeNum = 62;
    else if (ui->StartBox->currentIndex() == 42) StartNodeNum = 64;
    else if (ui->StartBox->currentIndex() == 43) StartNodeNum = 65;
    else if (ui->StartBox->currentIndex() == 44) StartNodeNum = 66;
    else if (ui->StartBox->currentIndex() == 45) StartNodeNum = 67;
    else if (ui->StartBox->currentIndex() == 46) StartNodeNum = 69;
    else if (ui->StartBox->currentIndex() == 47) StartNodeNum = 71;
    else if (ui->StartBox->currentIndex() == 48) StartNodeNum = 73;
    else if (ui->StartBox->currentIndex() == 49) StartNodeNum = 76;
    else if (ui->StartBox->currentIndex() == 50) StartNodeNum = 78;
    else if (ui->StartBox->currentIndex() == 51) StartNodeNum = 79;
    else if (ui->StartBox->currentIndex() == 52) StartNodeNum = 80;
    else if (ui->StartBox->currentIndex() == 53) StartNodeNum = 81;
    else if (ui->StartBox->currentIndex() == 54) StartNodeNum = 82;
    else if (ui->StartBox->currentIndex() == 55) StartNodeNum = 83;
    else if (ui->StartBox->currentIndex() == 56) StartNodeNum = 84;
    else if (ui->StartBox->currentIndex() == 57) StartNodeNum = 85;
    else if (ui->StartBox->currentIndex() == 58) StartNodeNum = 86;
    else if (ui->StartBox->currentIndex() == 59) StartNodeNum = 87;
    else if (ui->StartBox->currentIndex() == 60) StartNodeNum = 88;
    else if (ui->StartBox->currentIndex() == 61) StartNodeNum = 90;
    else if (ui->StartBox->currentIndex() == 62) StartNodeNum = 92;
    else if (ui->StartBox->currentIndex() == 63) StartNodeNum = 94;
    else if (ui->StartBox->currentIndex() == 64) StartNodeNum = 96;
    else if (ui->StartBox->currentIndex() == 65) StartNodeNum = 97;
    else if (ui->StartBox->currentIndex() == 66) StartNodeNum = 98;
    else if (ui->StartBox->currentIndex() == 67) StartNodeNum = 100;
    else if (ui->StartBox->currentIndex() == 68) StartNodeNum = 101;
    else if (ui->StartBox->currentIndex() == 69) StartNodeNum = 103;
    else if (ui->StartBox->currentIndex() == 70) StartNodeNum = 105;
    else if (ui->StartBox->currentIndex() == 71) StartNodeNum = 109;
    else if (ui->StartBox->currentIndex() == 72) StartNodeNum = 110;
    else if (ui->StartBox->currentIndex() == 73) StartNodeNum = 111;
    else if (ui->StartBox->currentIndex() == 74) StartNodeNum = 112;
    else if (ui->StartBox->currentIndex() == 75) StartNodeNum = 113;
    else if (ui->StartBox->currentIndex() == 76) StartNodeNum = 114;
    else if (ui->StartBox->currentIndex() == 77) StartNodeNum = 118;
    else if (ui->StartBox->currentIndex() == 78) StartNodeNum = 120;
    else if (ui->StartBox->currentIndex() == 79) StartNodeNum = 121;
    else if (ui->StartBox->currentIndex() == 80) StartNodeNum = 122;
    else if (ui->StartBox->currentIndex() == 81) StartNodeNum = 123;
    else if (ui->StartBox->currentIndex() == 82) StartNodeNum = 126;
    else if (ui->StartBox->currentIndex() == 83) StartNodeNum = 128;
    else if (ui->StartBox->currentIndex() == 84) StartNodeNum = 131;
    else if (ui->StartBox->currentIndex() == 85) StartNodeNum = 133;
    else if (ui->StartBox->currentIndex() == 86) StartNodeNum = 137;
    else if (ui->StartBox->currentIndex() == 87) StartNodeNum = 140;
    else if (ui->StartBox->currentIndex() == 88) StartNodeNum = 141;
    else if (ui->StartBox->currentIndex() == 89) StartNodeNum = 143;
    else if (ui->StartBox->currentIndex() == 90) StartNodeNum = 144;
    else if (ui->StartBox->currentIndex() == 91) StartNodeNum = 146;
    else if (ui->StartBox->currentIndex() == 92) StartNodeNum = 147;
    else if (ui->StartBox->currentIndex() == 93) StartNodeNum = 148;
    else if (ui->StartBox->currentIndex() == 94) StartNodeNum = 149;
    else if (ui->StartBox->currentIndex() == 95) StartNodeNum = 150;
    else if (ui->StartBox->currentIndex() == 96) StartNodeNum = 151;
    else if (ui->StartBox->currentIndex() == 97) StartNodeNum = 153;
    else if (ui->StartBox->currentIndex() == 98) StartNodeNum = 155;
    else if (ui->StartBox->currentIndex() == 99) StartNodeNum = 158;
    else if (ui->StartBox->currentIndex() == 100) StartNodeNum = 159;
    else if (ui->StartBox->currentIndex() == 101) StartNodeNum = 160;
    else if (ui->StartBox->currentIndex() == 102) StartNodeNum = 162;
    else if (ui->StartBox->currentIndex() == 103) StartNodeNum = 163;
    else if (ui->StartBox->currentIndex() == 104) StartNodeNum = 164;
    else if (ui->StartBox->currentIndex() == 105) StartNodeNum = 165;
    else if (ui->StartBox->currentIndex() == 106) StartNodeNum = 169;
    else if (ui->StartBox->currentIndex() == 107) StartNodeNum = 171;
    else if (ui->StartBox->currentIndex() == 108) StartNodeNum = 175;
    else if (ui->StartBox->currentIndex() == 109) StartNodeNum = 176;
    else if (ui->StartBox->currentIndex() == 110) StartNodeNum = 180;
}

void QtSGS::changePassNodeNum()
{
    if (ui->PassBox->currentIndex() == 0) PassNodeNum = -1;
    else if (ui->PassBox->currentIndex() == 1) PassNodeNum = 0;
    else if (ui->PassBox->currentIndex() == 2) PassNodeNum = 3;
    else if (ui->PassBox->currentIndex() == 3) PassNodeNum = 4;
    else if (ui->PassBox->currentIndex() == 4) PassNodeNum = 5;
    else if (ui->PassBox->currentIndex() == 5) PassNodeNum = 6;
    else if (ui->PassBox->currentIndex() == 6) PassNodeNum = 7;
    else if (ui->PassBox->currentIndex() == 7) PassNodeNum = 8;
    else if (ui->PassBox->currentIndex() == 8) PassNodeNum = 10;
    else if (ui->PassBox->currentIndex() == 9) PassNodeNum = 12;
    else if (ui->PassBox->currentIndex() == 10) PassNodeNum = 13;
    else if (ui->PassBox->currentIndex() == 11) PassNodeNum = 15;
    else if (ui->PassBox->currentIndex() == 12) PassNodeNum = 16;
    else if (ui->PassBox->currentIndex() == 13) PassNodeNum = 17;
    else if (ui->PassBox->currentIndex() == 14) PassNodeNum = 18;
    else if (ui->PassBox->currentIndex() == 15) PassNodeNum = 20;
    else if (ui->PassBox->currentIndex() == 16) PassNodeNum = 22;
    else if (ui->PassBox->currentIndex() == 17) PassNodeNum = 23;
    else if (ui->PassBox->currentIndex() == 18) PassNodeNum = 24;
    else if (ui->PassBox->currentIndex() == 19) PassNodeNum = 25;
    else if (ui->PassBox->currentIndex() == 20) PassNodeNum = 30;
    else if (ui->PassBox->currentIndex() == 21) PassNodeNum = 31;
    else if (ui->PassBox->currentIndex() == 22) PassNodeNum = 32;
    else if (ui->PassBox->currentIndex() == 23) PassNodeNum = 33;
    else if (ui->PassBox->currentIndex() == 24) PassNodeNum = 34;
    else if (ui->PassBox->currentIndex() == 25) PassNodeNum = 35;
    else if (ui->PassBox->currentIndex() == 26) PassNodeNum = 36;
    else if (ui->PassBox->currentIndex() == 27) PassNodeNum = 37;
    else if (ui->PassBox->currentIndex() == 28) PassNodeNum = 39;
    else if (ui->PassBox->currentIndex() == 29) PassNodeNum = 40;
    else if (ui->PassBox->currentIndex() == 30) PassNodeNum = 42;
    else if (ui->PassBox->currentIndex() == 31) PassNodeNum = 44;
    else if (ui->PassBox->currentIndex() == 32) PassNodeNum = 45;
    else if (ui->PassBox->currentIndex() == 33) PassNodeNum = 46;
    else if (ui->PassBox->currentIndex() == 34) PassNodeNum = 47;
    else if (ui->PassBox->currentIndex() == 35) PassNodeNum = 48;
    else if (ui->PassBox->currentIndex() == 36) PassNodeNum = 51;
    else if (ui->PassBox->currentIndex() == 37) PassNodeNum = 53;
    else if (ui->PassBox->currentIndex() == 38) PassNodeNum = 55;
    else if (ui->PassBox->currentIndex() == 39) PassNodeNum = 57;
    else if (ui->PassBox->currentIndex() == 40) PassNodeNum = 60;
    else if (ui->PassBox->currentIndex() == 41) PassNodeNum = 62;
    else if (ui->PassBox->currentIndex() == 42) PassNodeNum = 64;
    else if (ui->PassBox->currentIndex() == 43) PassNodeNum = 65;
    else if (ui->PassBox->currentIndex() == 44) PassNodeNum = 66;
    else if (ui->PassBox->currentIndex() == 45) PassNodeNum = 67;
    else if (ui->PassBox->currentIndex() == 46) PassNodeNum = 69;
    else if (ui->PassBox->currentIndex() == 47) PassNodeNum = 71;
    else if (ui->PassBox->currentIndex() == 48) PassNodeNum = 73;
    else if (ui->PassBox->currentIndex() == 49) PassNodeNum = 76;
    else if (ui->PassBox->currentIndex() == 50) PassNodeNum = 78;
    else if (ui->PassBox->currentIndex() == 51) PassNodeNum = 79;
    else if (ui->PassBox->currentIndex() == 52) PassNodeNum = 80;
    else if (ui->PassBox->currentIndex() == 53) PassNodeNum = 81;
    else if (ui->PassBox->currentIndex() == 54) PassNodeNum = 82;
    else if (ui->PassBox->currentIndex() == 55) PassNodeNum = 83;
    else if (ui->PassBox->currentIndex() == 56) PassNodeNum = 84;
    else if (ui->PassBox->currentIndex() == 57) PassNodeNum = 85;
    else if (ui->PassBox->currentIndex() == 58) PassNodeNum = 86;
    else if (ui->PassBox->currentIndex() == 59) PassNodeNum = 87;
    else if (ui->PassBox->currentIndex() == 60) PassNodeNum = 88;
    else if (ui->PassBox->currentIndex() == 61) PassNodeNum = 90;
    else if (ui->PassBox->currentIndex() == 62) PassNodeNum = 92;
    else if (ui->PassBox->currentIndex() == 63) PassNodeNum = 94;
    else if (ui->PassBox->currentIndex() == 64) PassNodeNum = 96;
    else if (ui->PassBox->currentIndex() == 65) PassNodeNum = 97;
    else if (ui->PassBox->currentIndex() == 66) PassNodeNum = 98;
    else if (ui->PassBox->currentIndex() == 67) PassNodeNum = 100;
    else if (ui->PassBox->currentIndex() == 68) PassNodeNum = 101;
    else if (ui->PassBox->currentIndex() == 69) PassNodeNum = 103;
    else if (ui->PassBox->currentIndex() == 70) PassNodeNum = 105;
    else if (ui->PassBox->currentIndex() == 71) PassNodeNum = 109;
    else if (ui->PassBox->currentIndex() == 72) PassNodeNum = 110;
    else if (ui->PassBox->currentIndex() == 73) PassNodeNum = 111;
    else if (ui->PassBox->currentIndex() == 74) PassNodeNum = 112;
    else if (ui->PassBox->currentIndex() == 75) PassNodeNum = 113;
    else if (ui->PassBox->currentIndex() == 76) PassNodeNum = 114;
    else if (ui->PassBox->currentIndex() == 77) PassNodeNum = 118;
    else if (ui->PassBox->currentIndex() == 78) PassNodeNum = 120;
    else if (ui->PassBox->currentIndex() == 79) PassNodeNum = 121;
    else if (ui->PassBox->currentIndex() == 80) PassNodeNum = 122;
    else if (ui->PassBox->currentIndex() == 81) PassNodeNum = 123;
    else if (ui->PassBox->currentIndex() == 82) PassNodeNum = 126;
    else if (ui->PassBox->currentIndex() == 83) PassNodeNum = 128;
    else if (ui->PassBox->currentIndex() == 84) PassNodeNum = 131;
    else if (ui->PassBox->currentIndex() == 85) PassNodeNum = 133;
    else if (ui->PassBox->currentIndex() == 86) PassNodeNum = 137;
    else if (ui->PassBox->currentIndex() == 87) PassNodeNum = 140;
    else if (ui->PassBox->currentIndex() == 88) PassNodeNum = 141;
    else if (ui->PassBox->currentIndex() == 89) PassNodeNum = 143;
    else if (ui->PassBox->currentIndex() == 90) PassNodeNum = 144;
    else if (ui->PassBox->currentIndex() == 91) PassNodeNum = 146;
    else if (ui->PassBox->currentIndex() == 92) PassNodeNum = 147;
    else if (ui->PassBox->currentIndex() == 93) PassNodeNum = 148;
    else if (ui->PassBox->currentIndex() == 94) PassNodeNum = 149;
    else if (ui->PassBox->currentIndex() == 95) PassNodeNum = 150;
    else if (ui->PassBox->currentIndex() == 96) PassNodeNum = 151;
    else if (ui->PassBox->currentIndex() == 97) PassNodeNum = 153;
    else if (ui->PassBox->currentIndex() == 98) PassNodeNum = 155;
    else if (ui->PassBox->currentIndex() == 99) PassNodeNum = 158;
    else if (ui->PassBox->currentIndex() == 100) PassNodeNum = 159;
    else if (ui->PassBox->currentIndex() == 101) PassNodeNum = 160;
    else if (ui->PassBox->currentIndex() == 102) PassNodeNum = 162;
    else if (ui->PassBox->currentIndex() == 103) PassNodeNum = 163;
    else if (ui->PassBox->currentIndex() == 104) PassNodeNum = 164;
    else if (ui->PassBox->currentIndex() == 105) PassNodeNum = 165;
    else if (ui->PassBox->currentIndex() == 106) PassNodeNum = 169;
    else if (ui->PassBox->currentIndex() == 107) PassNodeNum = 171;
    else if (ui->PassBox->currentIndex() == 108) PassNodeNum = 175;
    else if (ui->PassBox->currentIndex() == 109) PassNodeNum = 176;
    else if (ui->PassBox->currentIndex() == 110) PassNodeNum = 180;
}

void QtSGS::changeEndNodeNum()
{
    if (ui->EndBox->currentIndex() == 0) EndNodeNum = -1;
    else if (ui->EndBox->currentIndex() == 1) EndNodeNum = 0;
    else if (ui->EndBox->currentIndex() == 2) EndNodeNum = 3;
    else if (ui->EndBox->currentIndex() == 3) EndNodeNum = 4;
    else if (ui->EndBox->currentIndex() == 4) EndNodeNum = 5;
    else if (ui->EndBox->currentIndex() == 5) EndNodeNum = 6;
    else if (ui->EndBox->currentIndex() == 6) EndNodeNum = 7;
    else if (ui->EndBox->currentIndex() == 7) EndNodeNum = 8;
    else if (ui->EndBox->currentIndex() == 8) EndNodeNum = 10;
    else if (ui->EndBox->currentIndex() == 9) EndNodeNum = 12;
    else if (ui->EndBox->currentIndex() == 10) EndNodeNum = 13;
    else if (ui->EndBox->currentIndex() == 11) EndNodeNum = 15;
    else if (ui->EndBox->currentIndex() == 12) EndNodeNum = 16;
    else if (ui->EndBox->currentIndex() == 13) EndNodeNum = 17;
    else if (ui->EndBox->currentIndex() == 14) EndNodeNum = 18;
    else if (ui->EndBox->currentIndex() == 15) EndNodeNum = 20;
    else if (ui->EndBox->currentIndex() == 16) EndNodeNum = 22;
    else if (ui->EndBox->currentIndex() == 17) EndNodeNum = 23;
    else if (ui->EndBox->currentIndex() == 18) EndNodeNum = 24;
    else if (ui->EndBox->currentIndex() == 19) EndNodeNum = 25;
    else if (ui->EndBox->currentIndex() == 20) EndNodeNum = 30;
    else if (ui->EndBox->currentIndex() == 21) EndNodeNum = 31;
    else if (ui->EndBox->currentIndex() == 22) EndNodeNum = 32;
    else if (ui->EndBox->currentIndex() == 23) EndNodeNum = 33;
    else if (ui->EndBox->currentIndex() == 24) EndNodeNum = 34;
    else if (ui->EndBox->currentIndex() == 25) EndNodeNum = 35;
    else if (ui->EndBox->currentIndex() == 26) EndNodeNum = 36;
    else if (ui->EndBox->currentIndex() == 27) EndNodeNum = 37;
    else if (ui->EndBox->currentIndex() == 28) EndNodeNum = 39;
    else if (ui->EndBox->currentIndex() == 29) EndNodeNum = 40;
    else if (ui->EndBox->currentIndex() == 30) EndNodeNum = 42;
    else if (ui->EndBox->currentIndex() == 31) EndNodeNum = 44;
    else if (ui->EndBox->currentIndex() == 32) EndNodeNum = 45;
    else if (ui->EndBox->currentIndex() == 33) EndNodeNum = 46;
    else if (ui->EndBox->currentIndex() == 34) EndNodeNum = 47;
    else if (ui->EndBox->currentIndex() == 35) EndNodeNum = 48;
    else if (ui->EndBox->currentIndex() == 36) EndNodeNum = 51;
    else if (ui->EndBox->currentIndex() == 37) EndNodeNum = 53;
    else if (ui->EndBox->currentIndex() == 38) EndNodeNum = 55;
    else if (ui->EndBox->currentIndex() == 39) EndNodeNum = 57;
    else if (ui->EndBox->currentIndex() == 40) EndNodeNum = 60;
    else if (ui->EndBox->currentIndex() == 41) EndNodeNum = 62;
    else if (ui->EndBox->currentIndex() == 42) EndNodeNum = 64;
    else if (ui->EndBox->currentIndex() == 43) EndNodeNum = 65;
    else if (ui->EndBox->currentIndex() == 44) EndNodeNum = 66;
    else if (ui->EndBox->currentIndex() == 45) EndNodeNum = 67;
    else if (ui->EndBox->currentIndex() == 46) EndNodeNum = 69;
    else if (ui->EndBox->currentIndex() == 47) EndNodeNum = 71;
    else if (ui->EndBox->currentIndex() == 48) EndNodeNum = 73;
    else if (ui->EndBox->currentIndex() == 49) EndNodeNum = 76;
    else if (ui->EndBox->currentIndex() == 50) EndNodeNum = 78;
    else if (ui->EndBox->currentIndex() == 51) EndNodeNum = 79;
    else if (ui->EndBox->currentIndex() == 52) EndNodeNum = 80;
    else if (ui->EndBox->currentIndex() == 53) EndNodeNum = 81;
    else if (ui->EndBox->currentIndex() == 54) EndNodeNum = 82;
    else if (ui->EndBox->currentIndex() == 55) EndNodeNum = 83;
    else if (ui->EndBox->currentIndex() == 56) EndNodeNum = 84;
    else if (ui->EndBox->currentIndex() == 57) EndNodeNum = 85;
    else if (ui->EndBox->currentIndex() == 58) EndNodeNum = 86;
    else if (ui->EndBox->currentIndex() == 59) EndNodeNum = 87;
    else if (ui->EndBox->currentIndex() == 60) EndNodeNum = 88;
    else if (ui->EndBox->currentIndex() == 61) EndNodeNum = 90;
    else if (ui->EndBox->currentIndex() == 62) EndNodeNum = 92;
    else if (ui->EndBox->currentIndex() == 63) EndNodeNum = 94;
    else if (ui->EndBox->currentIndex() == 64) EndNodeNum = 96;
    else if (ui->EndBox->currentIndex() == 65) EndNodeNum = 97;
    else if (ui->EndBox->currentIndex() == 66) EndNodeNum = 98;
    else if (ui->EndBox->currentIndex() == 67) EndNodeNum = 100;
    else if (ui->EndBox->currentIndex() == 68) EndNodeNum = 101;
    else if (ui->EndBox->currentIndex() == 69) EndNodeNum = 103;
    else if (ui->EndBox->currentIndex() == 70) EndNodeNum = 105;
    else if (ui->EndBox->currentIndex() == 71) EndNodeNum = 109;
    else if (ui->EndBox->currentIndex() == 72) EndNodeNum = 110;
    else if (ui->EndBox->currentIndex() == 73) EndNodeNum = 111;
    else if (ui->EndBox->currentIndex() == 74) EndNodeNum = 112;
    else if (ui->EndBox->currentIndex() == 75) EndNodeNum = 113;
    else if (ui->EndBox->currentIndex() == 76) EndNodeNum = 114;
    else if (ui->EndBox->currentIndex() == 77) EndNodeNum = 118;
    else if (ui->EndBox->currentIndex() == 78) EndNodeNum = 120;
    else if (ui->EndBox->currentIndex() == 79) EndNodeNum = 121;
    else if (ui->EndBox->currentIndex() == 80) EndNodeNum = 122;
    else if (ui->EndBox->currentIndex() == 81) EndNodeNum = 123;
    else if (ui->EndBox->currentIndex() == 82) EndNodeNum = 126;
    else if (ui->EndBox->currentIndex() == 83) EndNodeNum = 128;
    else if (ui->EndBox->currentIndex() == 84) EndNodeNum = 131;
    else if (ui->EndBox->currentIndex() == 85) EndNodeNum = 133;
    else if (ui->EndBox->currentIndex() == 86) EndNodeNum = 137;
    else if (ui->EndBox->currentIndex() == 87) EndNodeNum = 140;
    else if (ui->EndBox->currentIndex() == 88) EndNodeNum = 141;
    else if (ui->EndBox->currentIndex() == 89) EndNodeNum = 143;
    else if (ui->EndBox->currentIndex() == 90) EndNodeNum = 144;
    else if (ui->EndBox->currentIndex() == 91) EndNodeNum = 146;
    else if (ui->EndBox->currentIndex() == 92) EndNodeNum = 147;
    else if (ui->EndBox->currentIndex() == 93) EndNodeNum = 148;
    else if (ui->EndBox->currentIndex() == 94) EndNodeNum = 149;
    else if (ui->EndBox->currentIndex() == 95) EndNodeNum = 150;
    else if (ui->EndBox->currentIndex() == 96) EndNodeNum = 151;
    else if (ui->EndBox->currentIndex() == 97) EndNodeNum = 153;
    else if (ui->EndBox->currentIndex() == 98) EndNodeNum = 155;
    else if (ui->EndBox->currentIndex() == 99) EndNodeNum = 158;
    else if (ui->EndBox->currentIndex() == 100) EndNodeNum = 159;
    else if (ui->EndBox->currentIndex() == 101) EndNodeNum = 160;
    else if (ui->EndBox->currentIndex() == 102) EndNodeNum = 162;
    else if (ui->EndBox->currentIndex() == 103) EndNodeNum = 163;
    else if (ui->EndBox->currentIndex() == 104) EndNodeNum = 164;
    else if (ui->EndBox->currentIndex() == 105) EndNodeNum = 165;
    else if (ui->EndBox->currentIndex() == 106) EndNodeNum = 169;
    else if (ui->EndBox->currentIndex() == 107) EndNodeNum = 171;
    else if (ui->EndBox->currentIndex() == 108) EndNodeNum = 175;
    else if (ui->EndBox->currentIndex() == 109) EndNodeNum = 176;
    else if (ui->EndBox->currentIndex() == 110) EndNodeNum = 180;
}

void QtSGS::on_pushButton_clicked()
{
    //点击进入主界面
     MainWindwo *event_table=new MainWindwo;  //给窗口3创建一个对象
     this ->close();                //this是当前窗体（窗口2）的指针，关闭
     event_table ->show();              //窗口2显示出来
}

void QtSGS::on_changeTimeF_2_clicked()
{
    killTimer(TimerID);
}

void QtSGS::on_changeTimeF_3_clicked()
{
    TimerID = startTimer(1000/360);
}
