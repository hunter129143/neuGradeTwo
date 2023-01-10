// GA_TSP.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//ʹ���Ŵ��㷨���TSp���⣺�����ɸ����У��κ���������֮��ľ���ʱȷ���ģ���Ҫ��һ�����̴�ĳ���д������뾭��
//ÿһ����������ÿһ�����ж���һ�Σ����ջص������ĳ��У����������ȷ��һ����̵�·���Ա�֤�����еķ������١�

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

//��ص�ϵ��
const double PC = 0.55;//�������
const double PM = 0.05;//�������
const int POP_SIZE = 100;//��Ⱥ��ģ
const int N_GENERATIONS = 700;//��������
const int N_CITIES = 31;//��������
const unsigned int SEEK = 20;//�������

//���������
class Individual
{
private:
	int Sequence[N_CITIES];
	double Fitness;//��Ӧ��
	double P_Fitness;//��Ӧ�ȸ���
	double Sum_P_Fitness;//�ۼ���Ӧ�ȸ���
public:
	Individual() {};//Ĭ�Ϲ��캯��
	Individual(int* m_Sequence);//���캯��
	void chaFitness(const double m_Fitness);//�޸���Ӧ��ֵ
	void chaP_Fitness(const double mP_Fitness);//�޸���Ӧ�ȸ��ʣ�
	void chaSum_P_Fitness(const double mSum_Fitness);//�޸���Ӧ���ۼӸ��ʣ�
	int* Get_Sequence();
	double Get_Fitness()const;
	double Get_P_Fitness()const;
	double Get_Sum_P_Fitness()const;
};

//��������
double random();//
double cal_distance(int city1, int city2);//ǰ�������������������е�ַ�����ؽ�������������еľ���
void initialize();//��ʼ������
void cal_fitness();//ǰ��������ȷ����һ�����з������У����ؽ�������ظ������Ӧ�Ⱥ���ֵ
void cal_P_fitness();//������Ӧ�ȸ���
void cal_Sum_fitness();//������Ӧ�ȸ����ۼ�ֵ
void select();//ѡ������
void crossover();//��������
void mutation();//��������,����ı���ʵ�����ǵ���������������������л���������Ϊ��Ҫ�����ظ�����
void genetic_algorithm();//�Ŵ��㷨������

//Individual��ʵ��
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
			cerr << "���������д����ظ����ʵ����" << endl;
			exit(1);
		}
	}
	if (right)
	{
		for (int i = 0; i < N_CITIES; i++)
			Sequence[i] = m_Sequence[i];
	}
	//��ʼ��
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
//�������������ڴ�Ÿ���
vector<Individual>nowPopulation;//��ŵ�ǰ����
vector<Individual>midPopulation;//���ѡ�����м���壻
vector<Individual>nextPopulation;//p(t+1)������
double city_pos[N_CITIES][2] =
{
	{1304, 2312}, {3639, 1315}, {4177, 2244}, {3712, 1399}, {3488, 1535},
	{3326, 1556}, {3238, 1229}, {4196, 1004}, {4312, 790}, {4386, 570},
	{3007, 1970}, {2562, 1756}, {2788, 1491}, {2381, 1676}, {1332, 695},
	{3715, 1678}, {3918, 2179}, {4061, 2370}, {3780, 2212}, {3676, 2578},
	{4029, 2838}, {4263, 2931}, {3429, 1908}, {3507, 2367}, {3394, 2643},
	{3439, 3201}, {2935, 3240}, {3140, 3550}, {2545, 2357}, {2778, 2826},
	{2370, 2975}
};//��������
//��غ�����ʵ��
double random()
{
	int N = rand() % 999;
	return double(N) / 1000.0;//�������0��1��С��
}
double cal_distance(int city1, int city2)
{
	double x1 = city_pos[city1 - 1][0];//��Ϊ��ߵĳ��������Ǵ�1��ʼ�ģ��������ﶼ��ȥ1
	double y1 = city_pos[city1 - 1][1];
	double x2 = city_pos[city2 - 1][0];
	double y2 = city_pos[city2 - 1][1];
	double dis = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return dis;
}
void initialize()
{
	int X[POP_SIZE][N_CITIES];//�洢����
	default_random_engine e(static_cast<unsigned>(20));
	uniform_int_distribution<>u(1, N_CITIES);
	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < N_CITIES; ++j)
		{
			X[i][j] = u(e);
			int rep_k = 0;
			for (int s = 0; s < j; ++s)//ɾ���ظ�
			{
				if (X[i][s] == X[i][j])
					rep_k++;
			}
			if (rep_k != 0)
				j--;
		}
	}
	//���ɶ��󣬲���������ʼȺ����
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
	////���Գ�ʼ�����
	//for (int i = 0; i < POP_SIZE; i++)
	//{
	//	for (int j = 0; j < N_CITIES; j++)
	//		cout << nowPopulation.at(i).Get_Sequence()[j] << "\t";
	//	cout << endl;
	//}
	////���Գ�ʼ�����
}
void cal_fitness()
{
	double total_distance;//�ܵ�·��
	double path_dis = 0.0;//���ߵ�·��
	int x[N_CITIES];//��ʱ�洢�Ա�����1��2��3��4��5��6��7��8��9��10
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
		//����·������
		for (int m = 0; m < N_CITIES - 1; ++m)
		{
			path_dis += cal_distance(x[m], x[m + 1]);
		}
		total_distance = path_dis + cal_distance(x[N_CITIES - 1], x[0]);

		//������Ӧ��ֵ
		//fitness = double(100000 / total_distance);
		fitness = 50000 - total_distance;
		nowPopulation.at(i).chaFitness(fitness);
	}
}
void cal_P_fitness()
{
	double sum_fitness = 0;//��Ӧ���ۼ�ֵ
	double temp = 0;//��ʱ�����Ӧ�ȸ���
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
	double summation = 0;//�ۼ�ֵ���
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
	double array[newPO_SIZE];//������������
	default_random_engine e(time(0));//���棬�����������
	uniform_real_distribution<double> u(0.0, 1.0); //�ֲ�
	for (int i = 0; i < newPO_SIZE; ++i)
		array[i] = u(e);
	//���̽���ѡ��
	for (int j = 0; j < newPO_SIZE; ++j)
	{
		if (array[j] < nowPopulation.at(0).Get_Sum_P_Fitness())
		{
			midPopulation.push_back(nowPopulation.at(0));//���뵽�м���Ⱥ
		}
		else
		{
			for (int i = 1; i < POP_SIZE; ++i)
			{
				if (array[j] >= nowPopulation.at(i - 1).Get_Sum_P_Fitness() && array[j] <= nowPopulation.at(i).Get_Sum_P_Fitness())
				{
					midPopulation.push_back(nowPopulation.at(i));//���뵽�м���Ⱥ
					break;
				}
			}
		}
	}
	nowPopulation.clear();//���nowpopulation
}
void crossover()
{
	int num = 0;//��¼����
	int crosspos;//����λ��
	int array1[N_CITIES], array2[N_CITIES];//��ʱ�洢���׺�ĸ�׵ķ�������
	vector<int>tem_vec1;//�洢���ڽ����ĸ��׵�����Ƭ��
	vector<int>tem_vec2;//�洢���ڽ�����ĸ�׵�����Ƭ��
	vector<int>tem_vec3;
	int new_arr1[N_CITIES], new_arr2[N_CITIES];//�洢��������ĸ���
	while (num < POP_SIZE - 1)
	{
		double ranC = random();
		tem_vec1.clear();
		tem_vec2.clear();
		tem_vec3.clear();

		if (ranC <= PC)//������С��С�ڽ�����ʣ�����н������
		{
			for (int i = 0; i < N_CITIES; ++i)
			{
				array1[i] = midPopulation.at(num).Get_Sequence()[i];//�õ����׵ķ�������
				array2[i] = midPopulation.at(num + 1).Get_Sequence()[i];//�õ�ĸ�׵ķ�������
			}
			crosspos = rand() % (N_CITIES - 1) + 1;//���ȷ�������1-9

			//��ȡ��������Ƭ��
			for (int j = 0; j < crosspos; ++j)
			{
				tem_vec1.push_back(array1[j]);
				new_arr1[j] = array1[j];
			}
			//ȥ����������Ƭ�������е�
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
			//�¸��岹�丸ĸ�˴˵�Ƭ��
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
	midPopulation.clear();//���midpopulation
}
void mutation()
{
	int mu_arr[2];//�洢����������
	int k;//�ظ�����
	int temp;//�����м����
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
			for (int j = 0; j < 2; ++j)//������������ͬ��������0-9����Ϊ������
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
	double maxFit[N_GENERATIONS];//�洢ÿһ����������Ӧ��ֵ
	double maxFitTemp = 0;//��ʱ�洢ÿһ�������Ӧ��
	int maxFitIndex[N_GENERATIONS];//�洢ÿһ�������Ӧ��ֵ��Ӧ�ĸ���
	time_t startTime, endTime;
	startTime = clock();
	initialize();
	maxFit[0] = maxFitTemp;
	cout << setw(5) << setiosflags(ios::left) << "����" << setw(50) << setiosflags(ios::left) << "                ��������"
		<< setw(10) << setiosflags(ios::left) << "Fitness" << endl;//��ע�⣺���±߲����ÿһ�����������ע�͡�

	//�����Ŵ��㷨�ĵ����������ÿһ���������Ӧ�ȵĸ��弴����Ӧ��ֵ
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
	//�˴����ϱ����һ�е�ֵһ��
	//cout << "ÿһ����Ӧ�����ֵ�ı仯���" << endl;
	//cout << endl;
	//for (int i = 0; i < N_GENERATIONS; i++)
	//{
	//	cout << maxFit[i] << " ";
	//}
	//���ÿһ��������ֵ��ע�⣺�������ÿһ���������Ӽ���ʱ�䡿
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
	
		cout << endl << "���ڽ����д�� data.csv" << endl;
		ofstream fileout("data.csv"); //�����д�� data.csv

		for (int i = 0; i < N_GENERATIONS; i++)
			fileout << maxFit[i] << endl; //���ö��ŷָ���
		fileout.close();
			cout << "д�����" << endl;

	cout << endl;
	int city = 0;
	for (int c = 0; c < N_CITIES - 1; ++c)
	{
		cout << nowPopulation.at(maxFitIndex[N_GENERATIONS - 1]).Get_Sequence()[c] << "->";
	}
	cout << nowPopulation.at(maxFitIndex[N_GENERATIONS - 1]).Get_Sequence()[N_CITIES - 1];
	cout << endl;
	//���·������
	cout << "·������Ϊ��" << endl;
	//cout << double(100000 / maxFit[N_GENERATIONS - 1]) << endl;
	cout << 50000 - maxFit[N_GENERATIONS - 1] << endl;
	cout << "����ʱ��Ϊ" << algo_time << endl;
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

	cout << "��ʱ��Ϊ��" << duration << " ��" << endl;
	system("pause");
	return 0;
}