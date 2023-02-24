#include "navigation.h"
#include <QDebug>

Ant::Ant()
{
	std::ifstream INF;
    INF.open("D:\\Application\\QtSGS\\QtSGS\\Map.txt", std::ios::in);
    if(!INF.is_open())
    {
        qDebug() << "Open Error";
        return;
    }
	for (int i = 0; i < NodeCount; i++)
	{
		INF >> MapNodes[i].Name;
		INF >> MapNodes[i].LX >> MapNodes[i].LY;
		INF >> MapNodes[i].PX >> MapNodes[i].PY;
		for (int j = 0; j < 4; j++)
		{
			INF >> MapNodes[i].ConnectionNodeNum[j];
			MapNodes[i].Crowed = 1.0;
			MapNodes[i].RideAllow = true;
		}
		INF >> MapNodes[i].Crowed;
		INF >> MapNodes[i].RideAllow;
		INF >> MapNodes[i].ServiceNode;
		CityVisited[i] = false;
	}
	INF.close();
	for (int m = 0; m < NodeCount; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			if (MapNodes[m].ConnectionNodeNum[n] != -1 && MapNodes[m].LX == MapNodes[MapNodes[m].ConnectionNodeNum[n]].LX && MapNodes[m].LY != MapNodes[MapNodes[m].ConnectionNodeNum[n]].LY)
				MapNodes[m].ConnectionNodeDistance[n] = fabs(MapNodes[m].LY - MapNodes[MapNodes[m].ConnectionNodeNum[n]].LY);
			else if (MapNodes[m].ConnectionNodeNum[n] != -1 && MapNodes[m].LX != MapNodes[MapNodes[m].ConnectionNodeNum[n]].LX && MapNodes[m].LY == MapNodes[MapNodes[m].ConnectionNodeNum[n]].LY)
				MapNodes[m].ConnectionNodeDistance[n] = fabs(MapNodes[m].LX - MapNodes[MapNodes[m].ConnectionNodeNum[n]].LX);
			else
				MapNodes[m].ConnectionNodeDistance[n] = MaxValue;
		}
	}
	MapNodes[114].ConnectionNodeNum[2] = 165;
	MapNodes[114].ConnectionNodeDistance[2] = 30000;
	MapNodes[114].ConnectionNodeNum[3] = 165;
	MapNodes[114].ConnectionNodeDistance[3] = 30000;
	MapNodes[131].ConnectionNodeNum[1] = 180;
	MapNodes[131].ConnectionNodeDistance[1] = 40000;
	MapNodes[131].ConnectionNodeNum[2] = 180;
	MapNodes[131].ConnectionNodeDistance[2] = 40000;
	MapNodes[131].ConnectionNodeNum[3] = 180;
	MapNodes[131].ConnectionNodeDistance[3] = 40000;
	MapNodes[165].ConnectionNodeNum[2] = 114;
	MapNodes[165].ConnectionNodeDistance[2] = 30000;
	MapNodes[165].ConnectionNodeNum[3] = 114;
	MapNodes[165].ConnectionNodeDistance[3] = 30000;
	MapNodes[180].ConnectionNodeNum[1] = 131;
	MapNodes[180].ConnectionNodeDistance[1] = 40000;
	MapNodes[180].ConnectionNodeNum[2] = 131;
	MapNodes[180].ConnectionNodeDistance[2] = 40000;
	MapNodes[180].ConnectionNodeNum[3] = 131;
	MapNodes[180].ConnectionNodeDistance[3] = 40000;
	for (int p = 0; p < 2 * NodeCount; p++)
		TravelCityNum[p] = -1;
	TravelCityCount = 0;
	CurrentCity = -1;
	MoveSpeed = 1.2;
	MoveDistance = 0.0;
	MoveTime = 0.0;
}

Ant::~Ant()
{

}

void Ant::ResetAnt()//重置蚂蚁信息---除了地图结点信息，全部重置
{
	for (int i = 0; i < NodeCount; i++)
		CityVisited[i] = false;
	for (int p = 0; p < 2 * NodeCount; p++)
		TravelCityNum[p] = -1;
	TravelCityCount = 0;
	CurrentCity = -1;
	MoveSpeed = 1.2;
	MoveDistance = 0.0;
	MoveTime = 0.0;
	//srand((unsigned)time(NULL));
}

int Ant::FindMinTime(int startTime, int startLocation)
{//一天是86400秒;
	if (startLocation == 114)
	{
		int nowDay = startTime / 86400;//先计算当天是周几
		int todayTime = startTime % 86400;//然后计算当天的具体时间
		if (todayTime > 12 * 3600 + 30 * 60 && nowDay < 4)
			return (86400 + 6 * 3600 + 50 * 60) - startTime;
		else if (todayTime > 12 * 3600 + 30 * 60 && nowDay >= 4)
			return ((7 - nowDay) * 86400 + 6 * 3600 + 50 * 60) - startTime;
		else if (todayTime <= 12 * 3600 + 30 * 60)
		{
			int SchoolBus[4]; //当天的四班车
			SchoolBus[0] = 6 * 3600 + 50 * 60;
			SchoolBus[1] = 7 * 3600;
			SchoolBus[2] = 8 * 3600 + 40 * 60;
			SchoolBus[3] = 12 * 3600 + 30 * 60;
			for (int i = 0; i < 4; i++)
				if (todayTime <= SchoolBus[i])
					return (SchoolBus[i] - todayTime);
			return (86400 + 6 * 3600 + 50 * 60) - startTime;
		}
		return (86400 + 6 * 3600 + 50 * 60) - startTime;
	}
	else if (startLocation == 131)
	{
		int todayTime = startTime % 86400;//计算当天的具体时间
		for (int i = 0; i < 12 * 6; i++)
			if (todayTime <= 7 * 3600 + 10 * 60 * i)
				return (7 * 3600 + 10 * 60 * i - todayTime);
		return (86400 + 7 * 3600) - todayTime;
	}
	else if (startLocation == 165)
	{
		int nowDay = startTime / 86400;//先计算当天是周几
		int todayTime = startTime % 86400;//然后计算当天的具体时间
		if (todayTime > 17 * 3600 + 40 * 60 && nowDay < 4)
			return (86400 + 10 * 3600 + 10 * 60) - startTime;
		else if (todayTime > 17 * 3600 + 40 * 60 && nowDay >= 4)
			return ((7 - nowDay) * 86400 + 10 * 3600 + 10 * 60) - startTime;
		else if (todayTime <= 17 * 3600 + 40 * 60)
		{
			int SchoolBus[4]; //当天的四班车
			SchoolBus[0] = 10 * 3600 + 10 * 60;
			SchoolBus[1] = 12 * 3600 + 30 * 60;
			SchoolBus[2] = 16 * 3600 + 40 * 60;
			SchoolBus[3] = 17 * 3600 + 40 * 60;
			for (int i = 0; i < 4; i++)
				if (todayTime <= SchoolBus[i])
					return (SchoolBus[i] - todayTime);
			return (86400 + 10 * 3600 + 10 * 60) - startTime;
		}
		return (86400 + 10 * 3600 + 10 * 60) - startTime;
	}
	else if (startLocation == 180)
	{
		int todayTime = startTime % 86400;//计算当天的具体时间
		for (int i = 0; i < 12 * 6 + 1; i++)
			if (todayTime <= 7 * 3600 + 10 * 60 * i)
				return (7 * 3600 + 10 * 60 * i - todayTime);
		return (86400 + 7 * 3600) - todayTime;
	}
	else
		return MaxValue;
}

int Ant::SelectNextCityNum(bool ride)//选择下一个前进的结点----先寻找到一条路径到达终点，然后再计算距离和时间的优先程度
{
	int NextNodeNum = -1, Buffer[4] = { -1, -1, -1, -1 }, Count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (MapNodes[CurrentCity].ConnectionNodeNum[i] != -1 && CityVisited[MapNodes[CurrentCity].ConnectionNodeNum[i]] == false)
		{
			if(ride && MapNodes[CurrentCity].RideAllow)
				Buffer[Count++] = MapNodes[CurrentCity].ConnectionNodeNum[i];
			else if(!ride)
				Buffer[Count++] = MapNodes[CurrentCity].ConnectionNodeNum[i];
		}
	}
	if(Count == 0)
		return NextNodeNum;
	NextNodeNum = rand() % Count;
	return Buffer[NextNodeNum];
}

void Ant::MoveAnt(bool ride, int nowTime)//移动蚂蚁位置，并计算移动距离和花费时间
{
	int NextNodeNum = SelectNextCityNum(ride);
	if (NextNodeNum == -1)
	{
		CurrentCity = NextNodeNum;
		return;
	}
	for(int i = 0; i < 4; i++)
		if (NextNodeNum == MapNodes[CurrentCity].ConnectionNodeNum[i])
		{
			double Speed = MoveSpeed / MapNodes[MapNodes[CurrentCity].ConnectionNodeNum[i]].Crowed;
			MoveDistance += MapNodes[CurrentCity].ConnectionNodeDistance[i];
			if (CurrentCity == 114 && NextNodeNum == 165)
			{
				MoveTime += FindMinTime(nowTime + MoveTime, CurrentCity);
				MoveTime += 2400;
			}
			else if (CurrentCity == 131 && NextNodeNum == 180)
			{
				MoveTime += FindMinTime(nowTime + MoveTime, CurrentCity);
				MoveTime += 5400;
			}
			else if (CurrentCity == 165 && NextNodeNum == 114)
			{
				MoveTime += FindMinTime(nowTime + MoveTime, CurrentCity);
				MoveTime += 2400;
			}
			else if (CurrentCity == 180 && NextNodeNum == 131)
			{
				MoveTime += FindMinTime(nowTime + MoveTime, CurrentCity);
				MoveTime += 5400;
			}
			else
				MoveTime += MapNodes[CurrentCity].ConnectionNodeDistance[i] / Speed;
			break;
		}
	TravelCityNum[TravelCityCount] = NextNodeNum;
	CurrentCity = NextNodeNum;
	CityVisited[CurrentCity] = true;
	TravelCityCount++;
}

void Ant::Search(int start, int finish, bool ride, int nowTime)//根据布尔变量判断是否更改默认移动速度。
{
	CurrentCity = start;
	TravelCityNum[TravelCityCount] = CurrentCity;
	TravelCityCount++;
	CityVisited[CurrentCity] = true;
	if (ride)
		MoveSpeed = 2.4;
	while (CurrentCity != finish && CurrentCity != -1 && TravelCityCount < NodeCount)
		MoveAnt(ride, nowTime);
}

Navigation::Navigation()
{

}

Navigation::~Navigation()
{

}

bool Navigation::returnCross(int start, int end)
{
	if (start <= 131 && end > 131)
		return true;
	else if (start > 131 && end <= 131)
		return true;
	else if (start <= 131 && end <= 131)
		return false;
	else if (start > 131 && end > 131)
		return false;
	else
		return false;
	return false;
}

void Navigation::ResetResult()//如果有更短的路径出现。则更新一定区域内的结点信息
{

}

void Navigation::Search1(int start, int finish, bool bike, int nowTime)//同一校区间两点的最短路径
{
		BestAnt.MoveDistance = MaxValue;//先将最佳路径设置为最大值。
		for (int i = 0; i < IteCount * AntCount; i++)
		{
			SearchAnt.ResetAnt();//先进性蚂蚁信息的初始化
			SearchAnt.Search(start, finish, bike, nowTime);//搜索起点到终点的最短路径，false表示不骑车。
			if (SearchAnt.CurrentCity == finish && SearchAnt.MoveDistance < BestAnt.MoveDistance)
			{
				BestAnt.MoveDistance = SearchAnt.MoveDistance;
				BestAnt.TravelCityCount = SearchAnt.TravelCityCount;
				for (int j = 0; j < NodeCount * 2; j++)
					BestAnt.TravelCityNum[j] = SearchAnt.TravelCityNum[j];
			}
		}
}

void Navigation::Search2(int start, int finish, bool bike, int nowTime)//同一校区两点的最短时间。
{
		BestAnt.MoveTime = MaxValue;//先将最佳路径设置为最大值。
		for (int i = 0; i < IteCount * AntCount; i++)
		{
			SearchAnt.ResetAnt();//先进性蚂蚁信息的初始化
			SearchAnt.Search(start, finish, bike, nowTime);//搜索起点到终点的最短路径，false表示不骑车。
			if (SearchAnt.CurrentCity == finish && SearchAnt.MoveTime < BestAnt.MoveTime)
			{
				BestAnt.MoveTime = SearchAnt.MoveTime;
				BestAnt.TravelCityCount = SearchAnt.TravelCityCount;
				for (int j = 0; j < NodeCount * 2; j++)
					BestAnt.TravelCityNum[j] = SearchAnt.TravelCityNum[j];
			}
		}
}

void Navigation::SearchTime(int start, int finish, bool bike, int nowTime)
{
	if (returnCross(start, finish))
	{
		if (start <= 131 && finish == 165)
		{
			Ant* TempAnt = new Ant();
			Search2(start, 114, bike, nowTime);
			/*for (int i = 0; i < BestAnt.TravelCityCount; i++)
				TempAnt->TravelCityNum[TempAnt->TravelCityCount++] = BestAnt.TravelCityNum[i];
			TempAnt->MoveTime = BestAnt.MoveTime;*/
			*TempAnt = BestAnt;
			TempAnt->MoveTime += TempAnt->FindMinTime(TempAnt->MoveTime + nowTime, 114);
			TempAnt->MoveTime += 2400;
			TempAnt->TravelCityNum[TempAnt->TravelCityCount] = 165;
			TempAnt->TravelCityCount++;
			Ant* Tempant = new Ant();
			Search2(start, 131, bike, nowTime);
			*Tempant = BestAnt;
			Tempant->MoveTime += Tempant->FindMinTime(Tempant->MoveTime + nowTime, 131);
			Tempant->MoveTime += 5400;
			Search2(180, 165, bike, nowTime);
			Tempant->MoveTime += BestAnt.MoveTime;
			if (Tempant->MoveTime < TempAnt->MoveTime)
			{
				int nowCount = Tempant->TravelCityCount, AllCount = Tempant->TravelCityCount + BestAnt.TravelCityCount;
				for (int i = nowCount; i < AllCount; i++)
				{
					Tempant->TravelCityNum[Tempant->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount];
					Tempant->TravelCityCount++;
				}
				BestAnt = *Tempant;
                delete TempAnt;
                delete Tempant;
			}
			else
			{
				BestAnt = *TempAnt;
                delete TempAnt;
                delete Tempant;
			}
		}
		else if (start <= 131 && finish == 180)
		{
			Ant* TempAnt = new Ant();
			Search2(start, 131, bike, nowTime);
			*TempAnt = BestAnt;
			TempAnt->MoveTime += TempAnt->FindMinTime(TempAnt->MoveTime + nowTime, 131);
			TempAnt->MoveTime += 5400;
			TempAnt->TravelCityNum[TempAnt->TravelCityCount] = 180;
			TempAnt->TravelCityCount++;
			Ant* Tempant = new Ant();
			Search2(start, 114, bike, nowTime);
			*Tempant = BestAnt;
			Tempant->MoveTime += Tempant->FindMinTime(Tempant->MoveTime + nowTime, 114);
			Tempant->MoveTime += 2400;
			Search2(165, 180, bike, nowTime);
			Tempant->MoveTime += BestAnt.MoveTime;
			if (Tempant->MoveTime < TempAnt->MoveTime)
			{
				int nowCount = Tempant->TravelCityCount, AllCount = Tempant->TravelCityCount + BestAnt.TravelCityCount;
				for (int i = nowCount; i < AllCount; i++)
				{
					Tempant->TravelCityNum[Tempant->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount];
					Tempant->TravelCityCount++;
				}
				BestAnt = *Tempant;
                delete TempAnt;
                delete Tempant;
			}
			else
			{
				BestAnt = *TempAnt;
                delete TempAnt;
                delete Tempant;
			}
		}
		else if (start <= 131 && finish > 131 && finish != 165 && finish != 180)
		{
			Ant* TempAnt = new Ant();
			Search2(start, 114, bike, nowTime);
			*TempAnt = BestAnt;
			TempAnt->MoveTime += TempAnt->FindMinTime(TempAnt->MoveTime + nowTime, 114);
			TempAnt->MoveTime += 2400;
			Search2(165, finish, bike, nowTime);
			int nowCount = TempAnt->TravelCityCount, AllCount = TempAnt->TravelCityCount + BestAnt.TravelCityCount;
			for (int i = nowCount; i < AllCount; i++)
			{
				TempAnt->TravelCityNum[TempAnt->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount];
				TempAnt->TravelCityCount++;
			}
			TempAnt->MoveTime += BestAnt.MoveTime;
			Ant* Tempant = new Ant();
			Search2(start, 131, bike, nowTime);
			*Tempant = BestAnt;
			Tempant->MoveTime += Tempant->FindMinTime(Tempant->MoveTime + nowTime, 131);
			Tempant->MoveTime += 5400;
			Search2(180, finish, bike, nowTime);
			Tempant->MoveTime += BestAnt.MoveTime;
			if (Tempant->MoveTime < TempAnt->MoveTime)
			{
				int nowCount1 = Tempant->TravelCityCount, AllCount1 = Tempant->TravelCityCount + BestAnt.TravelCityCount;
				for (int i = nowCount1; i < AllCount1; i++)
				{
					Tempant->TravelCityNum[Tempant->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount1];
					Tempant->TravelCityCount++;
				}
                BestAnt = *Tempant;
                delete TempAnt;
                delete Tempant;
			}
			else
			{
                BestAnt = *TempAnt;
                delete TempAnt;
                delete Tempant;
			}
		}
		else if (start > 131 && finish == 114)
		{
			Ant* TempAnt = new Ant();
			Search2(start, 165, bike, nowTime);
			*TempAnt = BestAnt;
			TempAnt->MoveTime += TempAnt->FindMinTime(TempAnt->MoveTime + nowTime, 165);
			TempAnt->MoveTime += 2400;
			TempAnt->TravelCityNum[TempAnt->TravelCityCount] = 114;
			TempAnt->TravelCityCount++;
			Ant* Tempant = new Ant();
			Search2(start, 180, bike, nowTime);
			*Tempant = BestAnt;
			Tempant->MoveTime += Tempant->FindMinTime(Tempant->MoveTime + nowTime, 180);
			Tempant->MoveTime += 5400;
			Search2(131, 114, bike, nowTime);
			Tempant->MoveTime += BestAnt.MoveTime;
			if (Tempant->MoveTime < TempAnt->MoveTime)
			{
				int nowCount = Tempant->TravelCityCount, AllCount = Tempant->TravelCityCount + BestAnt.TravelCityCount;
				for (int i = nowCount; i < AllCount; i++)
				{
					Tempant->TravelCityNum[Tempant->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount];
					Tempant->TravelCityCount++;
				}
                BestAnt = *Tempant;
                delete TempAnt;
                delete Tempant;
			}
			else
			{
                BestAnt = *TempAnt;
                delete TempAnt;
                delete Tempant;
			}
		}
		else if (start > 131 && finish == 131)
		{
			Ant* TempAnt = new Ant();
			Search2(start, 180, bike, nowTime);
			*TempAnt = BestAnt;
			TempAnt->MoveTime += TempAnt->FindMinTime(TempAnt->MoveTime + nowTime, 180);
			TempAnt->MoveTime += 5400;
			TempAnt->TravelCityNum[TempAnt->TravelCityCount] = 131;
			TempAnt->TravelCityCount++;
			Ant* Tempant = new Ant();
			Search2(start, 165, bike, nowTime);
			*Tempant = BestAnt;
			Tempant->MoveTime += Tempant->FindMinTime(Tempant->MoveTime + nowTime, 165);
			Tempant->MoveTime += 2400;
			Search2(114, 131, bike, nowTime);
			Tempant->MoveTime += BestAnt.MoveTime;
			if (Tempant->MoveTime < TempAnt->MoveTime)
			{
				int nowCount = Tempant->TravelCityCount, AllCount = Tempant->TravelCityCount + BestAnt.TravelCityCount;
				for (int i = nowCount; i < AllCount; i++)
				{
					Tempant->TravelCityNum[Tempant->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount];
					Tempant->TravelCityCount++;
				}
                BestAnt = *Tempant;
                delete TempAnt;
                delete Tempant;
			}
			else
			{
                BestAnt = *TempAnt;
                delete TempAnt;
                delete Tempant;
			}
		}
		else if (start > 131 && finish <= 131 && finish >= 0 && finish != 114 && finish != 131)
		{
			Ant* TempAnt = new Ant();
			Search2(start, 165, bike, nowTime);
			*TempAnt = BestAnt;
			TempAnt->MoveTime += TempAnt->FindMinTime(TempAnt->MoveTime + nowTime, 165);
			TempAnt->MoveTime += 2400;
			Search2(114, finish, bike, nowTime);
			int nowCount = TempAnt->TravelCityCount, AllCount = TempAnt->TravelCityCount + BestAnt.TravelCityCount;
			for (int i = nowCount; i < AllCount; i++)
			{
				TempAnt->TravelCityNum[TempAnt->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount];
				TempAnt->TravelCityCount++;
			}
			TempAnt->MoveTime += BestAnt.MoveTime;
			Ant* Tempant = new Ant();
			Search2(start, 180, bike, nowTime);
			*Tempant = BestAnt;
			Tempant->MoveTime += Tempant->FindMinTime(Tempant->MoveTime + nowTime, 180);
			Tempant->MoveTime += 5400;
			Search2(131, finish, bike, nowTime);
			Tempant->MoveTime += BestAnt.MoveTime;
			if (Tempant->MoveTime < TempAnt->MoveTime)
			{
				int nowCount1 = Tempant->TravelCityCount, AllCount1 = Tempant->TravelCityCount + BestAnt.TravelCityCount;
				for (int i = nowCount1; i < AllCount1; i++)
				{
					Tempant->TravelCityNum[Tempant->TravelCityCount] = BestAnt.TravelCityNum[i - nowCount1];
					Tempant->TravelCityCount++;
				}
                BestAnt = *Tempant;
                delete TempAnt;
                delete Tempant;
			}
			else
			{
                BestAnt = *TempAnt;
                delete TempAnt;
                delete Tempant;
			}
		}
	}
	else
		Search2(start, finish, bike, nowTime);
}
