// GA_TSP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//使用遗传算法求解TSp问题：有若干个城市，任何两个城市之间的距离时确定的，现要求一旅行商从某城市触发必须经过
//每一个城市且在每一个城市逗留一次，最终回到触发的城市，问如何事先确定一条最短的路线以保证期旅行的费用最少。

#include<random>
#include<vector>
#include<iostream>
#include<cmath>
#include<ctime>
#include <cstdlib>
#include <bitset>
#include<iomanip>
#include <fstream>
using namespace std;

//相关的系数
const double PC = 0.55;//交叉概率
const double PM = 0.05;//变异概率
const int POP_SIZE = 100;//种群规模
const int N_GENERATIONS = 700;//进化代数
const int N_CITIES = 31;//城市数量
const unsigned int SEEK = 20;//随机种子

//定义个体类
class Individual
{
private:
	int Sequence[N_CITIES];
	double Fitness;//适应度
	double P_Fitness;//适应度概率
	double Sum_P_Fitness;//累加适应度概率
public:
	Individual() {};//默认构造函数
	Individual(int* m_Sequence);//构造函数
	void chaFitness(const double m_Fitness);//修改适应度值
	void chaP_Fitness(const double mP_Fitness);//修改适应度概率；
	void chaSum_P_Fitness(const double mSum_Fitness);//修改适应度累加概率；
	int* Get_Sequence();
	double Get_Fitness()const;
	double Get_P_Fitness()const;
	double Get_Sum_P_Fitness()const;
};

//函数声明
double random();//
double cal_distance(int city1, int city2);//前提条件：输入两个城市地址；返回结果：计算两城市的距离
void initialize();//初始化函数
void cal_fitness();//前提条件：确定了一个城市访问序列；返回结果：返回个体的适应度函数值
void cal_P_fitness();//计算适应度概率
void cal_Sum_fitness();//计算适应度概率累计值
void select();//选择算子
void crossover();//交叉算子
void mutation();//变异算子,这里的变异实际上是单个序列中随机找两个城市互换次序，因为需要考虑重复问题
void genetic_algorithm();//遗传算法主函数

//Individual类实现
Individual::Individual(int* m_Sequence)
{
	bool right = true;
	for (int i = 1; i < N_CITIES - 1; i++)
	{
		int rep_sum = 0;
		for (int j = i + 1; j < N_CITIES; j++)
		{
			if (m_Sequence[j] == m_Sequence[i])
				rep_sum++;
		}
		if (rep_sum != 0)
		{
			right = false;
			cerr << "访问序列中存在重复访问的情况" << endl;
			exit(1);
		}
	}
	if (right)
	{
		for (int i = 0; i < N_CITIES; i++)
			Sequence[i] = m_Sequence[i];
	}
	//初始化
	this->Fitness = 0;
	this->P_Fitness = 0;
	this->Sum_P_Fitness = 0;

}
int* Individual::Get_Sequence()
{
	return Sequence;
}
double Individual::Get_Fitness()const
{
	return Fitness;
}
double Individual::Get_P_Fitness()const
{
	return P_Fitness;
}
double Individual::Get_Sum_P_Fitness()const
{
	return Sum_P_Fitness;
}
void Individual::chaFitness(const double m_Fitness)
{
	this->Fitness = m_Fitness;
}
void Individual::chaP_Fitness(const double mP_Fitness)
{
	this->P_Fitness = mP_Fitness;
}
void Individual::chaSum_P_Fitness(const double mSum_P_Fitness)
{
	this->Sum_P_Fitness = mSum_P_Fitness;
}
//定义向量，用于存放个体
vector<Individual>nowPopulation;//存放当前个体
vector<Individual>midPopulation;//存放选择后的中间个体；
vector<Individual>nextPopulation;//p(t+1)代个体
double city_pos[N_CITIES][2] =
{
	{1304, 2312}, {3639, 1315}, {4177, 2244}, {3712, 1399}, {3488, 1535},
	{3326, 1556}, {3238, 1229}, {4196, 1004}, {4312, 790}, {4386, 570},
	{3007, 1970}, {2562, 1756}, {2788, 1491}, {2381, 1676}, {1332, 695},
	{3715, 1678}, {3918, 2179}, {4061, 2370}, {3780, 2212}, {3676, 2578},
	{4029, 2838}, {4263, 2931}, {3429, 1908}, {3507, 2367}, {3394, 2643},
	{3439, 3201}, {2935, 3240}, {3140, 3550}, {2545, 2357}, {2778, 2826},
	{2370, 2975}
};//城市坐标
//相关函数的实现
double random()
{
	int N = rand() % 999;
	return double(N) / 1000.0;//随机产生0到1的小数
}
double cal_distance(int city1, int city2)
{
	double x1 = city_pos[city1 - 1][0];//因为后边的城市序列是从1开始的，所以这里都减去1
	double y1 = city_pos[city1 - 1][1];
	double x2 = city_pos[city2 - 1][0];
	double y2 = city_pos[city2 - 1][1];
	double dis = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return dis;
}
void initialize()
{
	int X[POP_SIZE][N_CITIES];//存储变量
	default_random_engine e(static_cast<unsigned>(20));
	uniform_int_distribution<>u(1, N_CITIES);
	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < N_CITIES; ++j)
		{
			X[i][j] = u(e);
			int rep_k = 0;
			for (int s = 0; s < j; ++s)//删除重复
			{
				if (X[i][s] == X[i][j])
					rep_k++;
			}
			if (rep_k != 0)
				j--;
		}
	}
	//生成对象，并将其加入初始群体中
	for (int i = 0; i < POP_SIZE; ++i)
	{
		int temp_seq[N_CITIES];
		for (int j = 0; j < N_CITIES; ++j)
		{
			temp_seq[j] = X[i][j];
		}
		Individual indivi(temp_seq);
		nowPopulation.push_back(indivi);
	}
	////测试初始化结果
	//for (int i = 0; i < POP_SIZE; i++)
	//{
	//	for (int j = 0; j < N_CITIES; j++)
	//		cout << nowPopulation.at(i).Get_Sequence()[j] << "\t";
	//	cout << endl;
	//}
	////测试初始化结果
}
void cal_fitness()
{
	double total_distance;//总的路程
	double path_dis = 0.0;//单线的路程
	int x[N_CITIES];//临时存储自变量；1，2，3，4，5，6，7，8，9，10
	double fitness;
	for (int i = 0; i < POP_SIZE; ++i)
	{
		total_distance = 0;
		fitness = 0;
		path_dis = 0.0;
		for (int j = 0; j < N_CITIES; ++j)
		{
			x[j] = nowPopulation.at(i).Get_Sequence()[j];
		}
		//计算路径距离
		for (int m = 0; m < N_CITIES - 1; ++m)
		{
			path_dis += cal_distance(x[m], x[m + 1]);
		}
		total_distance = path_dis + cal_distance(x[N_CITIES - 1], x[0]);

		//计算适应度值
		//fitness = double(100000 / total_distance);
		fitness = 50000 - total_distance;
		nowPopulation.at(i).chaFitness(fitness);
	}
}
void cal_P_fitness()
{
	double sum_fitness = 0;//适应度累计值
	double temp = 0;//临时存放适应度概率
	for (int i = 0; i < POP_SIZE; ++i)
	{
		sum_fitness += nowPopulation.at(i).Get_Fitness();
	}
	for (int j = 0; j < POP_SIZE; ++j)
	{
		temp = nowPopulation.at(j).Get_Fitness() / sum_fitness;
		nowPopulation.at(j).chaP_Fitness(temp);
	}

}
void cal_Sum_fitness()
{
	double summation = 0;//累加值存放
	for (int i = 0; i < POP_SIZE; ++i)
	{
		summation += nowPopulation.at(i).Get_P_Fitness();
		nowPopulation.at(i).chaSum_P_Fitness(summation);
	}
}
void select()
{
	double max_fitness = nowPopulation.at(0).Get_Fitness();
	int max_id = 0;
	for (int p = 0; p < POP_SIZE; ++p)
	{
		if (max_fitness < nowPopulation.at(p).Get_Fitness())
		{
			max_fitness = nowPopulation.at(p).Get_Fitness();
			max_id = p;
		}
	}
	for (int i = 0; i < POP_SIZE / 4; ++i)
	{
		midPopulation.push_back(nowPopulation.at(max_id));
	}
	const int newPO_SIZE = POP_SIZE - POP_SIZE / 4;
	double array[newPO_SIZE];//随机数保存变量
	default_random_engine e(time(0));//引擎，生成随机序列
	uniform_real_distribution<double> u(0.0, 1.0); //分布
	for (int i = 0; i < newPO_SIZE; ++i)
		array[i] = u(e);
	//轮盘进行选择
	for (int j = 0; j < newPO_SIZE; ++j)
	{
		if (array[j] < nowPopulation.at(0).Get_Sum_P_Fitness())
		{
			midPopulation.push_back(nowPopulation.at(0));//加入到中间种群
		}
		else
		{
			for (int i = 1; i < POP_SIZE; ++i)
			{
				if (array[j] >= nowPopulation.at(i - 1).Get_Sum_P_Fitness() && array[j] <= nowPopulation.at(i).Get_Sum_P_Fitness())
				{
					midPopulation.push_back(nowPopulation.at(i));//加入到中间种群
					break;
				}
			}
		}
	}
	nowPopulation.clear();//清空nowpopulation
}
void crossover()
{
	int num = 0;//记录次数
	int crosspos;//交叉位置
	int array1[N_CITIES], array2[N_CITIES];//临时存储父亲和母亲的访问序列
	vector<int>tem_vec1;//存储用于交换的父亲的序列片段
	vector<int>tem_vec2;//存储用于交换的母亲的序列片段
	vector<int>tem_vec3;
	int new_arr1[N_CITIES], new_arr2[N_CITIES];//存储交叉产生的个体
	while (num < POP_SIZE - 1)
	{
		double ranC = random();
		tem_vec1.clear();
		tem_vec2.clear();
		tem_vec3.clear();

		if (ranC <= PC)//如果随机小数小于交叉概率，则进行交叉操作
		{
			for (int i = 0; i < N_CITIES; ++i)
			{
				array1[i] = midPopulation.at(num).Get_Sequence()[i];//得到父亲的访问序列
				array2[i] = midPopulation.at(num + 1).Get_Sequence()[i];//得到母亲的访问序列
			}
			crosspos = rand() % (N_CITIES - 1) + 1;//随机确定交叉点1-9

			//提取交叉序列片段
			for (int j = 0; j < crosspos; ++j)
			{
				tem_vec1.push_back(array1[j]);
				new_arr1[j] = array1[j];
			}
			//去除父亲序列片段中已有的
			for (int jj = 0; jj < N_CITIES; ++jj)
			{
				vector<int>::iterator  temp_find;
				temp_find = find(tem_vec1.begin(), tem_vec1.end(), array2[jj]);
				if (temp_find == tem_vec1.end())
					tem_vec2.push_back(array2[jj]);
				else
				{
					tem_vec3.push_back(array2[jj]);
				}
			}
			//新个体补充父母彼此的片段
			for (int b = 0; b < crosspos; ++b)
				new_arr2[b] = tem_vec3[b];
			for (int a = crosspos; a < N_CITIES; ++a)
			{
				new_arr1[a] = tem_vec2[a - crosspos];
				new_arr2[a] = array1[a];
			}
			Individual newChild1(new_arr1);
			Individual newChild2(new_arr2);
			nextPopulation.push_back(newChild1);
			nextPopulation.push_back(newChild2);
		}
		else
		{
			nextPopulation.push_back(midPopulation.at(num));
			nextPopulation.push_back(midPopulation.at(num + 1));
		}
		num += 2;
	}
	midPopulation.clear();//清空midpopulation
}
void mutation()
{
	int mu_arr[2];//存储两个交换点
	int k;//重复计数
	int temp;//交换中间变量
	for (int i = 0; i < POP_SIZE; ++i)
	{
		int temp_seq[N_CITIES];
		double ranM = random();
		for (int a = 0; a < N_CITIES; ++a)
		{
			temp_seq[a] = nextPopulation.at(i).Get_Sequence()[a];
		}
		if (ranM <= PM)
		{
			for (int j = 0; j < 2; ++j)//生成两个不相同的整数（0-9）作为交换点
			{
				k = 0;
				mu_arr[j] = rand() % N_CITIES;
				if (mu_arr[1] == mu_arr[0])
					k++;
				if (k != 0)
					j--;
			}
			temp = temp_seq[mu_arr[0]];
			temp_seq[mu_arr[0]] = temp_seq[mu_arr[1]];
			temp_seq[mu_arr[1]] = temp;

			Individual muChild(temp_seq);
			nowPopulation.push_back(muChild);
		}
		else
			nowPopulation.push_back(nextPopulation.at(i));
	}
	nextPopulation.clear();
}
void genetic_algorithm()
{
	double maxFit[N_GENERATIONS];//存储每一代的最大的适应度值
	double maxFitTemp = 0;//临时存储每一代最大适应度
	int maxFitIndex[N_GENERATIONS];//存储每一代最大适应度值对应的个体
	time_t startTime, endTime;
	startTime = clock();
	initialize();
	maxFit[0] = maxFitTemp;
	cout << setw(5) << setiosflags(ios::left) << "代数" << setw(50) << setiosflags(ios::left) << "                访问序列"
		<< setw(10) << setiosflags(ios::left) << "Fitness" << endl;//【注意：若下边不输出每一代，则这里可注释】

	//进行遗传算法的迭代，并输出每一代的最大适应度的个体即其适应度值
	for (int i = 0; i < N_GENERATIONS; ++i)
	{
		maxFitTemp = 0;
		cal_fitness();
		for (int s = 0; s < POP_SIZE; ++s)
		{
			if (maxFitTemp < nowPopulation.at(s).Get_Fitness())
			{
				maxFitTemp = nowPopulation.at(s).Get_Fitness();
				maxFitIndex[i] = s;
			}
		}
		maxFit[i] = maxFitTemp;


		cal_P_fitness();
		cal_Sum_fitness();
		select();
		crossover();
		mutation();
	}
	endTime = clock();
	double algo_time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	//此处和上边最后一列的值一样
	//cout << "每一代适应度最大值的变化情况" << endl;
	//cout << endl;
	//for (int i = 0; i < N_GENERATIONS; i++)
	//{
	//	cout << maxFit[i] << " ";
	//}
	//输出每一代的最优值【注意：这里输出每一代会大大增加计算时间】
	//for (int i = 0; i < N_GENERATIONS; i++)
	//{
	//	cout << endl << setw(5) << setiosflags(ios::left) << i << "|";
	//	for (int c = 0; c < N_CITIES - 1; c++)
	//	{
	//		cout << nowPopulation.at(maxFitIndex[i]).Get_Sequence()[c] << "->";
	//	}
	//	cout << nowPopulation.at(maxFitIndex[i]).Get_Sequence()[N_CITIES - 1];
	//	cout << "   " << maxFit[i];
	//}
	
		cout << endl << "正在将结果写入 data.csv" << endl;
		ofstream fileout("data.csv"); //将结果写入 data.csv

		for (int i = 0; i < N_GENERATIONS; i++)
			fileout << maxFit[i] << endl; //采用逗号分隔符
		fileout.close();
			cout << "写入完成" << endl;

	cout << endl;
	int city = 0;
	for (int c = 0; c < N_CITIES - 1; ++c)
	{
		cout << nowPopulation.at(maxFitIndex[N_GENERATIONS - 1]).Get_Sequence()[c] << "->";
	}
	cout << nowPopulation.at(maxFitIndex[N_GENERATIONS - 1]).Get_Sequence()[N_CITIES - 1];
	cout << endl;
	//输出路径长度
	cout << "路径长度为：" << endl;
	//cout << double(100000 / maxFit[N_GENERATIONS - 1]) << endl;
	cout << 50000 - maxFit[N_GENERATIONS - 1] << endl;
	cout << "计算时间为" << algo_time << endl;
}

int main()
{
	cout << "START" << endl;
	cout << endl;
	double duration = 0;
	time_t start_time, end_time;
	start_time = clock();
	genetic_algorithm();
	end_time = clock();
	duration = (double)((end_time - start_time)) / CLOCKS_PER_SEC;

	cout << "总时间为：" << duration << " 秒" << endl;
	system("pause");
	return 0;
}