//���ܣ���һ����Ԫ���������ֵ�����������Ԫ���������ֵ��f(x1,x2) = 21.5+x1*sin(4pi*x1)+x2*sin(20pi*x2)��
#pragma once//��֤�ļ�ֻ������һ��
#include<random>
#include<vector>
#include<iostream>
#include<cmath>
#include<ctime>
#include <cstdlib>
#include <bitset>
#include<iomanip>
using namespace std;
const double PI = 3.141592653589793;//����һ�����ɸı�ĳ���ֵPI
const int Po_Size = 50;//��Ⱥ��ģ
const int Ev_Algebra = 500;//��������
const double Ov_Probability = 0.850; //�������,������������ж����������Ƿ���Ҫ����
const double Va_Probability = 0.050;//�������,������������ж���һ�����Ƿ���Ҫ����
const int De_Variable = 2;//�����Ա����ĸ���,���Ҫ���ж�Ԫ��������ֵ��⣬ֱ���޸��Ա�������De_Variable����
const int length1 = 24;//��ȷ��6λС������24λ�����Ʊ���
const int length2 = 23;//��ȷ��6λС������23λ�����Ʊ���
class X_Range //�Ա���ȡֵ��Χ�࣬�����ڶ������
{
private:
    double Upper;//�������Ͻ�ȡֵ
    double Lower;//�������½�ȡֵ
public:
    X_Range(double m_Upper, double m_Lower);//���캯��
    double GetUpper()const;//��ȡ��������
    double GetLower()const;//��ȡ��������
};
class Individual //���������
{
private:
    double Variable[De_Variable];//��ű���x1,x2,x3........
    double Fitness;//��Ӧֵ
    double ReFitness;//��Ӧֵ����
    double SumFitness;//�ۼӸ��ʣ�Ϊ����ת��׼��
public:
    Individual() {}//Ĭ�Ϲ��캯��
    Individual(double* m_Variable);//���캯��
    double* GetVariable();//��ȡ����ֵ
    void ChaFitness(const double m_fitness);//�޸���Ӧֵ
    void ChaReFitness(const double m_ReFitness);//�޸���Ӧֵ����
    void ChaSumFitness(const double m_SumFitness);//�޸��ۼӸ���
    double GetFitness()const;//��ȡ��Ӧֵ
    double GetReFitness()const;//��ȡ��Ӧֵ����
    double GetSumFitness()const;//��ȡ�ۼӸ���
};
void Initialize();//�����ʼ����Ⱥ���õ���һ������
void CaculaFitness();//����������Ӧֵ
void CaculaReFitness();//����������Ӧֵ����
void CalculaSumFitness();//�����ۼӸ������
void seclect();//��Ⱥѡ��
double Scand();//�������0��1�����С��
void crossing();//�ӽ�
void variating();//����
void genetic_algorithm();//�Ŵ��㷨