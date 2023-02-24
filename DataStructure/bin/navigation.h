#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <time.h>

#define B_NodeNum			132		//0-131Ϊ�������
#define NodeCount			181		//132-180Ϊɳ�ӽ��
#define B_SchoolBusNodeNum	114		//����У�������
#define B_BusNodeNum		131		//�����������������
#define S_SchoolBusNodeNum	165		//ɳ��У�������
#define S_BusNodeNum		180		//ɳ�ӹ������������
#define MaxValue			99999999//��ʼ��̾�������ʱ��
#define IteCount			1000	//��������
#define AntCount			100		//����������ѭ������

struct Node
{
	std::string Name;//�������
	int LX, LY, PX, PY;//�߼�λ�ú�ʵ��λ��
	int ConnectionNodeNum[4];//��Χ�Ľ����
	double ConnectionNodeDistance[4];//����Χ���ľ���
	double Crowed;//�ý���ӵ���̶�
	bool RideAllow;//�ý���Ƿ������������г�
	bool ServiceNode;
};

struct Road
{
	int NodeNum;//�����
	int LX, LY;//���λ��
	int MoveDirection;//����һ�������ƶ�����8246��Ӧ��������
	double Crowed;//�ýڵ��ӵ���̶�
	int WaitCount;//�ȴ�ʱ����������������ʾģ���н��������ڶ�Ӧλ�õĵȴ�ʱ��
};

class Ant
{
public:
	Node MapNodes[NodeCount];//���еĽڵ���Ϣ
	bool CityVisited[NodeCount];//���н��ķ�����Ϣ
	int TravelCityNum[NodeCount * 2];//�߹��Ľ����Ϣ
	int TravelCityCount;//�߹������еĽ������----�洢���·��ʱ����������Ϊ�жϱ�־�����ж��У��֮��ĵ�������
	int CurrentCity;//��ǰ���ڽ����
	double MoveSpeed;//�ƶ��ٶ�--���ڼ���ʱ��------�����ٶ�ΪĬ���ƶ��ٶȳ��Խ�㷽���ϵ�ӵ���̶�
	double MoveDistance;//�ƶ��ľ���
	double MoveTime;//�ƶ����ѵ�ʱ��
	Ant();
	~Ant();
	void ResetAnt();//����������Ϣ---���˵�ͼ�����Ϣ��ȫ������
	int FindMinTime(int, int);
	int SelectNextCityNum(bool);//ѡ����һ��ǰ���Ľ��----��Ѱ�ҵ�һ��·�������յ㣬Ȼ���ټ�������ʱ������ȳ̶�
	void MoveAnt(bool, int);//�ƶ�����λ�ã��������ƶ�����ͻ���ʱ��
	void Search(int, int, bool, int);//����һ����㵽�յ��·�����������ݲ��������ж��Ƿ�����ƶ��ٶ�
};

class Navigation
{
public:
	Ant SearchAnt;//��������·��������
	Ant BestAnt;//�����洢���·��������
	Navigation();
	~Navigation();
	bool returnCross(int, int);
	void ResetResult();//����и��̵�·�����֡������һ�������ڵĽ����Ϣ
	void Search1(int, int, bool, int);//����һ�����·��������ͬһУ�������ⲻͬ����֮������·��·�߳���
	void Search2(int, int, bool, int);//���Զ������ʱ�䡣����ͬһУ�������ⲻͬ����֮������ʱ��·�߳���
	void SearchTime(int, int, bool, int);
};

#endif