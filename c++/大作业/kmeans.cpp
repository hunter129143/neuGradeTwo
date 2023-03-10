#include <ctime>
#include <cmath>
#include <omp.h>

#include "kmeans.h"


//下列代码用于输出每轮迭代的结果
#ifdef OUTPUT_EVERY_ITERATION

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#endif //OUTPUT_EVERY_ITERATION


//含参构造。参数分别为：点数、坐标最大值、聚类数、最大迭代次数
KMeans::KMeans(int point_num, double max_point_crood, int cluster_num, int max_iteration_times)
{
    this->point_num = point_num;
    this->max_point_crood = max_point_crood;
    this->cluster_num = cluster_num;
    this->max_iteration_times = max_iteration_times;

    srand((unsigned int)time(NULL)); //设置随机种子

    //在初始化过程中启用并行计算。用不同线程进行点和聚类的初始化
#pragma omp parallel sections
    {
#pragma omp section
        InitPoints(); //初始化点

#pragma omp section
        InitClusters(); //初始化聚类
    }
}


//初始化点
void KMeans::InitPoints(void)
{
    for (int i = 0; i < point_num; i++)
    {
        Point point((double)rand() / (double)RAND_MAX * max_point_crood,
            (double)rand() / (double)RAND_MAX * max_point_crood);

        points.push_back(point);
    }
}


//初始化聚类（均值点）
void KMeans::InitClusters(void)
{
    for (int i = 0; i < cluster_num; i++)
    {
        Cluster cluster((double)rand() / (double)RAND_MAX * max_point_crood,
            (double)rand() / (double)RAND_MAX * max_point_crood);

        clusters.push_back(cluster);

        next_clusters_point_num.push_back(0); //设置 next_clusters_point_num 初始值为 0

        next_clusters_x_sum.push_back(0.0); //设置 next_clusters_x_sum 初始值为 0.0
        next_clusters_y_sum.push_back(0.0); //设置 next_clusters_y_sum 初始值为 0.0
    }
}


//计算 point 和 cluster 的距离
inline double CalcDistance(Point& point, Cluster& cluster)
{
    return sqrt(pow(point.GetX() - cluster.GetX(), 2.0) +
        pow(point.GetY() - cluster.GetY(), 2.0));
}


//分配点
void KMeans::AssignPoints(void)
{
    int min_cluster_id;
    double min_distance;

    //在 for 循环中启用并行计算。设置 min_distance min_cluster_id 为线程 private 变量，其他变量被所有线程共享
#pragma omp parallel private(min_distance, min_cluster_id)
#pragma omp for
    for (int i = 0; i < point_num; i++) //遍历点
    {
        min_cluster_id = 0; //假定 0 号聚类为与 points[i] 最近的聚类
        min_distance = CalcDistance(points[i], clusters[0]); //假定 0 号聚类为与 points[i] 最近的聚类

        for (int j = 1; j < cluster_num; j++) //遍历聚类
        {
            double distance = CalcDistance(points[i], clusters[j]); //计算距离

            if (distance < min_distance) //比较
            {
                min_distance = distance;
                min_cluster_id = j;
            }
        }

        points[i].SetClusterID(min_cluster_id); //更新点所属的聚类 id
        next_clusters_point_num[min_cluster_id]++; //增加对应聚类中点的数量
        next_clusters_x_sum[min_cluster_id] += points[i].GetX(); //增加对应聚类中点的 x 坐标和
        next_clusters_y_sum[min_cluster_id] += points[i].GetY(); //增加对应聚类中点的 y 坐标和
    }
}


//更新聚类。若所有聚类均值点均不移动，返回 false
bool KMeans::UpdateClusters(void)
{
    bool is_cluster_move = false; //假定所有聚类均值点都不移动

    double next_x;
    double next_y;

    //在 for 循环中启用并行计算。设置 next_x next_y 为线程 private 变量，其他变量被所有线程共享
#pragma omp parallel private(next_x, next_y)
#pragma omp for    
    for (int i = 0; i < cluster_num; i++)
    {
        next_x = next_clusters_x_sum[i] / (double)next_clusters_point_num[i]; //更新后的均值点 x 坐标
        next_y = next_clusters_y_sum[i] / (double)next_clusters_point_num[i]; //更新后的均值点 y 坐标

        if (clusters[i].GetX() != next_x || clusters[i].GetY() != next_y)
        {
            is_cluster_move = true; //若发生移动，则 is_cluster_move 改为 true
            clusters[i].SetX(next_x); //更新均值点 x 坐标
            clusters[i].SetY(next_y); //更新均值点 y 坐标
        }

        next_clusters_point_num[i] = 0; //设置 next_clusters_point_num 值为 0
        next_clusters_x_sum[i] = 0.0; //设置 next_clusters_x_sum 值为 0.0
        next_clusters_y_sum[i] = 0.0; //设置 next_clusters_y_sum 值为 0.0
    }

    return is_cluster_move;
}


//计算并返回结果
std::vector<Point> KMeans::Result(void)
{
    bool is_cluster_move = true;
    int iteration_times = 0;

    while (is_cluster_move && iteration_times < max_iteration_times) //当所有聚类不再移动或超出最大迭代次数时结束循环
    {
        AssignPoints(); //分配点
        is_cluster_move = UpdateClusters(); //更新聚类

        iteration_times++;

        //下列代码用于输出每轮迭代的结果
#ifdef OUTPUT_EVERY_ITERATION

        std::cout << "第" << iteration_times << "次迭代完成，写入 step 文件" << std::endl;

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