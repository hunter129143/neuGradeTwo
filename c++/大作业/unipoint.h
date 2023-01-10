#pragma once
#ifndef UNIPOINT_H
#define UNIPOINT_H


//UniPoint �ࡣͨ�õĵ��࣬��Ϊ Point �Ļ���
class UniPoint
{
public:
    UniPoint(double x, double y);
    double GetX(void);
    double GetY(void);
    void SetX(double x);
    void SetY(double y);

protected:
    double x; //��� x ����
    double y; //��� y ����
};


//Point �ࡣÿ�����Ӧһ������
class Point : public UniPoint
{
public:
    Point(double x, double y);
    int GetClusterID(void);
    void SetClusterID(int cluster_id);

private:
    int cluster_id; //�������ľ���� id���� 0 ��ʼ
};


//Cluster ��Ϊ UniPoint �ı�����������ʵ�������þ����ֵ���ʾ��
typedef UniPoint Cluster;


#endif //UNIPOINT_H