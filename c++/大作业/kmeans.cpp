#include <ctime>
#include <cmath>
#include <omp.h>

#include "kmeans.h"


//���д����������ÿ�ֵ����Ľ��
#ifdef OUTPUT_EVERY_ITERATION

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#endif //OUTPUT_EVERY_ITERATION


//���ι��졣�����ֱ�Ϊ���������������ֵ��������������������
KMeans::KMeans(int point_num, double max_point_crood, int cluster_num, int max_iteration_times)
{
    this->point_num = point_num;
    this->max_point_crood = max_point_crood;
    this->cluster_num = cluster_num;
    this->max_iteration_times = max_iteration_times;

    srand((unsigned int)time(NULL)); //�����������

    //�ڳ�ʼ�����������ò��м��㡣�ò�ͬ�߳̽��е�;���ĳ�ʼ��
#pragma omp parallel sections
    {
#pragma omp section
        InitPoints(); //��ʼ����

#pragma omp section
        InitClusters(); //��ʼ������
    }
}


//��ʼ����
void KMeans::InitPoints(void)
{
    for (int i = 0; i < point_num; i++)
    {
        Point point((double)rand() / (double)RAND_MAX * max_point_crood,
            (double)rand() / (double)RAND_MAX * max_point_crood);

        points.push_back(point);
    }
}


//��ʼ�����ࣨ��ֵ�㣩
void KMeans::InitClusters(void)
{
    for (int i = 0; i < cluster_num; i++)
    {
        Cluster cluster((double)rand() / (double)RAND_MAX * max_point_crood,
            (double)rand() / (double)RAND_MAX * max_point_crood);

        clusters.push_back(cluster);

        next_clusters_point_num.push_back(0); //���� next_clusters_point_num ��ʼֵΪ 0

        next_clusters_x_sum.push_back(0.0); //���� next_clusters_x_sum ��ʼֵΪ 0.0
        next_clusters_y_sum.push_back(0.0); //���� next_clusters_y_sum ��ʼֵΪ 0.0
    }
}


//���� point �� cluster �ľ���
inline double CalcDistance(Point& point, Cluster& cluster)
{
    return sqrt(pow(point.GetX() - cluster.GetX(), 2.0) +
        pow(point.GetY() - cluster.GetY(), 2.0));
}


//�����
void KMeans::AssignPoints(void)
{
    int min_cluster_id;
    double min_distance;

    //�� for ѭ�������ò��м��㡣���� min_distance min_cluster_id Ϊ�߳� private ���������������������̹߳���
#pragma omp parallel private(min_distance, min_cluster_id)
#pragma omp for
    for (int i = 0; i < point_num; i++) //������
    {
        min_cluster_id = 0; //�ٶ� 0 �ž���Ϊ�� points[i] ����ľ���
        min_distance = CalcDistance(points[i], clusters[0]); //�ٶ� 0 �ž���Ϊ�� points[i] ����ľ���

        for (int j = 1; j < cluster_num; j++) //��������
        {
            double distance = CalcDistance(points[i], clusters[j]); //�������

            if (distance < min_distance) //�Ƚ�
            {
                min_distance = distance;
                min_cluster_id = j;
            }
        }

        points[i].SetClusterID(min_cluster_id); //���µ������ľ��� id
        next_clusters_point_num[min_cluster_id]++; //���Ӷ�Ӧ�����е������
        next_clusters_x_sum[min_cluster_id] += points[i].GetX(); //���Ӷ�Ӧ�����е�� x �����
        next_clusters_y_sum[min_cluster_id] += points[i].GetY(); //���Ӷ�Ӧ�����е�� y �����
    }
}


//���¾��ࡣ�����о����ֵ������ƶ������� false
bool KMeans::UpdateClusters(void)
{
    bool is_cluster_move = false; //�ٶ����о����ֵ�㶼���ƶ�

    double next_x;
    double next_y;

    //�� for ѭ�������ò��м��㡣���� next_x next_y Ϊ�߳� private ���������������������̹߳���
#pragma omp parallel private(next_x, next_y)
#pragma omp for    
    for (int i = 0; i < cluster_num; i++)
    {
        next_x = next_clusters_x_sum[i] / (double)next_clusters_point_num[i]; //���º�ľ�ֵ�� x ����
        next_y = next_clusters_y_sum[i] / (double)next_clusters_point_num[i]; //���º�ľ�ֵ�� y ����

        if (clusters[i].GetX() != next_x || clusters[i].GetY() != next_y)
        {
            is_cluster_move = true; //�������ƶ����� is_cluster_move ��Ϊ true
            clusters[i].SetX(next_x); //���¾�ֵ�� x ����
            clusters[i].SetY(next_y); //���¾�ֵ�� y ����
        }

        next_clusters_point_num[i] = 0; //���� next_clusters_point_num ֵΪ 0
        next_clusters_x_sum[i] = 0.0; //���� next_clusters_x_sum ֵΪ 0.0
        next_clusters_y_sum[i] = 0.0; //���� next_clusters_y_sum ֵΪ 0.0
    }

    return is_cluster_move;
}


//���㲢���ؽ��
std::vector<Point> KMeans::Result(void)
{
    bool is_cluster_move = true;
    int iteration_times = 0;

    while (is_cluster_move && iteration_times < max_iteration_times) //�����о��಻���ƶ��򳬳�����������ʱ����ѭ��
    {
        AssignPoints(); //�����
        is_cluster_move = UpdateClusters(); //���¾���

        iteration_times++;

        //���д����������ÿ�ֵ����Ľ��
#ifdef OUTPUT_EVERY_ITERATION

        std::cout << "��" << iteration_times << "�ε�����ɣ�д�� step �ļ�" << std::endl;

        std::stringstream str_stream;
        str_stream << "step" << iteration_times << ".csv";
        std::ofstream fileout(str_stream.str());

        for (int i = 0; i < (int)points.size(); i++)
            fileout << points[i].GetX() << "," << points[i].GetY() << "," << points[i].GetClusterID() << std::endl;

        fileout.close();

#endif //OUTPUT_EVERY_ITERATION
    }

    return points;
}