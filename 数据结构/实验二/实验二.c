#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//  函数结果状态代码
# define TRUE 1
# define FALSE 0
# define OK 1
# define ERROR 0
# define INFEASIBLE -1
# define OVERFLOW -2
# define MAXSIZE  5        //总共的车位数
#define BUFF_LEN 1024        //每行的长度均为15    前7个字符是汽车牌
//Status是函数类型，其值是函数结果状态代码
typedef int Status;
typedef char SElemType;
//车
typedef struct{
    char name[8];
    int movedtime;//移动次数
}Car;
//停车场
typedef struct {
Car* base;
Car* top;
int stackSize;
}P_SqStack;

Status initParkLot(P_SqStack*p);        //初始化停车场
Status initCar(Car* car);                //初始化汽车
Car Pop(P_SqStack *p);                    //弹出停车场的车或者弹出临时车场的车,并返回汽车
Status Push(P_SqStack *p, Car car);        //把车停入停车场或临时车场


char * left(char *dst, char *src, int n);    //从字符串的左边截取n个字符

//创建停车场或临时车场
Status initParkLot(P_SqStack *p) {
    p->base = (Car*)malloc(MAXSIZE * sizeof(Car));
    if (!p ->base) {
        exit(OVERFLOW);
    }
    p->top = p->base; //栈顶指针指向栈底指针
    p->stackSize = MAXSIZE;
    return OK;
}

//汽车的初始化
Status initCar(Car* car) {

    for(int i=0;i<8;i++){
        car->name[i]  ="";
    }
    car->movedtime = 0;
    return OK;
}

//弹出停车场的车或者弹出临时车场的车,并返回汽车
Car Pop(P_SqStack *p) {
    Car car;
    //关于栈空的判断，写在了主函数里面
    p->top--;
    car = *p->top;
    return car;
}

//把车停入停车场或临时车场
Status Push(P_SqStack *p, Car car) {

    *p->top = car;
    p->top++;
    return OK;
}

    //p->top = (Car*)malloc(sizeof(Car));    //这里绝对不能分配，不然会出现冲突,因为在初始化时，top已经指向了一片空间，不能再多指向一个空间

//从字符串的左边截取n个字符
char * left(char *dst, char *src, int n)
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if (n > len) n = len;
    while (n--) *(q++) = *(p++);
    *(q++) = '\0';     //补回这个字符串的结束符，防止系统没有补'\0'导致出bug
    return dst;
}
//汽车move的次数，取决于它自己离开前，在它底下的车有多少台离开了
int main() {

    //创建栈结构    停车场和汽车都要创建
    P_SqStack pInt;
    P_SqStack pTemp;

    initParkLot(&pInt);
    initParkLot(&pTemp);

    FILE* file;
    FILE* filewrite = fopen("C:\\Users\\29908\\OneDrive\\桌面\\实验数据\\output.txt", "w+");    //写出到output.txt


    char line[BUFF_LEN] = { 0 };

    file = fopen("C:\\Users\\29908\\OneDrive\\桌面\\实验数据\\data.txt","r");
    //IO流一行一行地读取
    while (fgets(line,BUFF_LEN,file) != NULL)
    {
        Car car;
        initCar(&car);
        char temp[10] = "";    //temp[]绝不能开到[7]，因为后面要补一个'\0'表示结束
        if (strstr(line, "arrives")) {//有汽车到达
            left(temp, line, 7);
            for (int i = 0; i < 8;i++) {

            car.name[i] = temp[i];
            }

            if ((pInt.top - pInt.base) !=  MAXSIZE) {
                //此时停车场车位没有满
                Push(&pInt, car);
            }
            else
            {//Sorry PORSCHE, the lot is full
                printf("Sorry %s, the lot is full\n", car.name);
                //输出到output.txt文本文件
                fprintf(filewrite, "Sorry %s, the lot is full\n", car.name);
                continue;
            }
        }

        if (strstr(line, "departs")) {

            left(temp, line, 7);

            //有汽车停在停车场里，才能弹出汽车
            if (pInt.base != pInt.top) {
                car = Pop(&pInt);

                while (strcmp(car.name, temp) != 0 && pInt.base != pInt.top) {
                    //循环条件
                    //把排在要离开的车前面的所有车移入临时车场
                    //还要注意停车场不能为空才可以进行
                    car.movedtime += 1;
                    Push(&pTemp, car);

                    //继续进行挪车，用一个car来接受，便于比较
                    car = Pop(&pInt);
                }
            }

            //跳出while循环时,此时car的名字就是要离开的车的名字
            //COOLONE was moved 0 times while it was here
            printf("%s was moved %d times while it was here\n", car.name, car.movedtime);
            fprintf(filewrite, "%s was moved %d times while it was here\n", car.name, car.movedtime);

            Car cartemp;
            initCar(&cartemp);
            //将临时车场剩余的所有汽车复原回停车场
            while (pTemp.base != pTemp.top)
            {
                cartemp = Pop(&pTemp);
                Push(&pInt, cartemp);
            }
        }

    }
    //打印出最后停留在停车场里没有出去的汽车的信息
    //printStack(pInt);
    while (pInt.base != pInt.top) {
        pInt.top--;
        printf("%s was moved %d times while it was here\n", pInt.top->name, pInt.top->movedtime);
        fprintf(filewrite, "%s was moved %d times while it was here\n", pInt.top->name, pInt.top->movedtime);
    }
    //关闭文件流
    fclose(filewrite);
    return 0;
}
