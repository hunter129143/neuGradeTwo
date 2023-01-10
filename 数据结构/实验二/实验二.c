#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//  �������״̬����
# define TRUE 1
# define FALSE 0
# define OK 1
# define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2
# define MAXSIZE  5        //�ܹ��ĳ�λ��
#define BUFF_LEN 1024        //ÿ�еĳ��Ⱦ�Ϊ15    ǰ7���ַ���������
//Status�Ǻ������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
typedef char SElemType;
//��
typedef struct{
    char name[8];
    int movedtime;//�ƶ�����
}Car;
//ͣ����
typedef struct {
Car* base;
Car* top;
int stackSize;
}P_SqStack;

Status initParkLot(P_SqStack*p);        //��ʼ��ͣ����
Status initCar(Car* car);                //��ʼ������
Car Pop(P_SqStack *p);                    //����ͣ�����ĳ����ߵ�����ʱ�����ĳ�,����������
Status Push(P_SqStack *p, Car car);        //�ѳ�ͣ��ͣ��������ʱ����


char * left(char *dst, char *src, int n);    //���ַ�������߽�ȡn���ַ�

//����ͣ��������ʱ����
Status initParkLot(P_SqStack *p) {
    p->base = (Car*)malloc(MAXSIZE * sizeof(Car));
    if (!p ->base) {
        exit(OVERFLOW);
    }
    p->top = p->base; //ջ��ָ��ָ��ջ��ָ��
    p->stackSize = MAXSIZE;
    return OK;
}

//�����ĳ�ʼ��
Status initCar(Car* car) {

    for(int i=0;i<8;i++){
        car->name[i]  ="";
    }
    car->movedtime = 0;
    return OK;
}

//����ͣ�����ĳ����ߵ�����ʱ�����ĳ�,����������
Car Pop(P_SqStack *p) {
    Car car;
    //����ջ�յ��жϣ�д��������������
    p->top--;
    car = *p->top;
    return car;
}

//�ѳ�ͣ��ͣ��������ʱ����
Status Push(P_SqStack *p, Car car) {

    *p->top = car;
    p->top++;
    return OK;
}

    //p->top = (Car*)malloc(sizeof(Car));    //������Բ��ܷ��䣬��Ȼ����ֳ�ͻ,��Ϊ�ڳ�ʼ��ʱ��top�Ѿ�ָ����һƬ�ռ䣬�����ٶ�ָ��һ���ռ�

//���ַ�������߽�ȡn���ַ�
char * left(char *dst, char *src, int n)
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if (n > len) n = len;
    while (n--) *(q++) = *(p++);
    *(q++) = '\0';     //��������ַ����Ľ���������ֹϵͳû�в�'\0'���³�bug
    return dst;
}
//����move�Ĵ�����ȡ�������Լ��뿪ǰ���������µĳ��ж���̨�뿪��
int main() {

    //����ջ�ṹ    ͣ������������Ҫ����
    P_SqStack pInt;
    P_SqStack pTemp;

    initParkLot(&pInt);
    initParkLot(&pTemp);

    FILE* file;
    FILE* filewrite = fopen("C:\\Users\\29908\\OneDrive\\����\\ʵ������\\output.txt", "w+");    //д����output.txt


    char line[BUFF_LEN] = { 0 };

    file = fopen("C:\\Users\\29908\\OneDrive\\����\\ʵ������\\data.txt","r");
    //IO��һ��һ�еض�ȡ
    while (fgets(line,BUFF_LEN,file) != NULL)
    {
        Car car;
        initCar(&car);
        char temp[10] = "";    //temp[]�����ܿ���[7]����Ϊ����Ҫ��һ��'\0'��ʾ����
        if (strstr(line, "arrives")) {//����������
            left(temp, line, 7);
            for (int i = 0; i < 8;i++) {

            car.name[i] = temp[i];
            }

            if ((pInt.top - pInt.base) !=  MAXSIZE) {
                //��ʱͣ������λû����
                Push(&pInt, car);
            }
            else
            {//Sorry PORSCHE, the lot is full
                printf("Sorry %s, the lot is full\n", car.name);
                //�����output.txt�ı��ļ�
                fprintf(filewrite, "Sorry %s, the lot is full\n", car.name);
                continue;
            }
        }

        if (strstr(line, "departs")) {

            left(temp, line, 7);

            //������ͣ��ͣ��������ܵ�������
            if (pInt.base != pInt.top) {
                car = Pop(&pInt);

                while (strcmp(car.name, temp) != 0 && pInt.base != pInt.top) {
                    //ѭ������
                    //������Ҫ�뿪�ĳ�ǰ������г�������ʱ����
                    //��Ҫע��ͣ��������Ϊ�ղſ��Խ���
                    car.movedtime += 1;
                    Push(&pTemp, car);

                    //��������Ų������һ��car�����ܣ����ڱȽ�
                    car = Pop(&pInt);
                }
            }

            //����whileѭ��ʱ,��ʱcar�����־���Ҫ�뿪�ĳ�������
            //COOLONE was moved 0 times while it was here
            printf("%s was moved %d times while it was here\n", car.name, car.movedtime);
            fprintf(filewrite, "%s was moved %d times while it was here\n", car.name, car.movedtime);

            Car cartemp;
            initCar(&cartemp);
            //����ʱ����ʣ�������������ԭ��ͣ����
            while (pTemp.base != pTemp.top)
            {
                cartemp = Pop(&pTemp);
                Push(&pInt, cartemp);
            }
        }

    }
    //��ӡ�����ͣ����ͣ������û�г�ȥ����������Ϣ
    //printStack(pInt);
    while (pInt.base != pInt.top) {
        pInt.top--;
        printf("%s was moved %d times while it was here\n", pInt.top->name, pInt.top->movedtime);
        fprintf(filewrite, "%s was moved %d times while it was here\n", pInt.top->name, pInt.top->movedtime);
    }
    //�ر��ļ���
    fclose(filewrite);
    return 0;
}
