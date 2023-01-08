#pragma once
#ifndef KMEANS_H
#define KMEANS_H

//ȡ���˴�ע�ͣ������ÿ�ֵ����Ľ��
//#define OUTPUT_EVERY_ITERATION


#include <vector>

#include "unipoint.h"


//KMeans �ࡣһ�� K-Means �����Ӧһ������
class KMeans
{
public:
    //���ι��졣�����ֱ�Ϊ���������������ֵ��������������������
    KMeans(int point_num, double max_point_crood, int cluster_num, int max_iteration_times);
    std::vector<Point> Result(void); //���㲢���ؽ��

private:
    int point_num; //����
    double max_point_crood; //�������ֵ
    std::vector<Point> points; //��ŵ������

    int cluster_num; //������
    std::vector<Cluster> clusters; //��ž��������
    std::vector<int> next_clusters_point_num; //��Ŵ��ֵ����������Ӧ�����е�����������ڼ�����һ���ж�Ӧ����ľ�ֵ��
    std::vector<double> next_clusters_x_sum; //��Ŵ��ֵ����������Ӧ�����е�� x ����͡����ڼ�����һ���ж�Ӧ����ľ�ֵ��
    std::vector<double> next_clusters_y_sum; //��Ŵ��ֵ����������Ӧ�����е�� y ����͡����ڼ�����һ���ж�Ӧ����ľ�ֵ��

    int max_iteration_times; //����������

    void InitPoints(void); //��ʼ����
    void InitClusters(void); //��ʼ�����ࣨ��ֵ�㣩
    void AssignPoints(void); //�����
    bool UpdateClusters(void); //���¾��ࡣ�����о����ֵ������ƶ������� false
};


#endif //KMEANS_H