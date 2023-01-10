#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
typedef float Num;//为防止以后变换操作数类型需要
typedef struct
{
	Num data[MAX];
	int top;
}StackNum;//运算数栈
typedef struct
{
	char data[MAX];
	int top;
}StackChar;//运算符栈
//------函数声明---------
void InitNum(StackNum *p);//运算数栈初始化
void PushNum(StackNum *p, Num e);//运算数压栈
void PopNum(StackNum *p, Num *e);//运算数出栈
Num GetNum(StackNum p);//取栈顶元素
//-----------------------
void InitChar(StackChar *p);//运算符栈初始化
void PushChar(StackChar *p, char e);//运算符压栈
void PopChar(StackChar *p, char *e);//运算符出栈
//-----------------------
void Fun(StackNum *p, char e);//计算并压入运算数栈
//-----------------------
int main()
{
	int i;//循环变量
	Num temp;//存放一个临时转换数
	char str[MAX], ch;//存放中缀表达式原式，临时运算符
	//-----------
	StackNum n1;
	StackChar c1;
	InitNum(&n1);
	InitChar(&c1);
	//------------
	for (;;)
	{
		printf("请输入中缀表达式：");
		gets(str);

		for (i = 0; str[i] != '\0'; i++)//读完整字符串-----字符串结束标志'\0'
		{
			if (str[i] >= '0'&&str[i] <= '9')//分岔点一：----------------------------------------------------------------如果为数字
			{
				temp = str[i] - '0';//-----将字符转换为数值


				while (str[i + 1] != '\0')//多位数值获取
				{
					if (str[i + 1] >= '0'&&str[i + 1] <= '9')
					{
						temp = temp * 10 + str[i + 1] - '0';//------注意！

						i++;
					}
					else
						break;//如果不是多位数字，则跳出多位获取循环
				}
				PushNum(&n1, temp);//将获取来的数值入栈
			}
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')')
				switch (str[i])//表达式可为：整型/字符型/枚举型-----C语言中
				{
					//case 后可为 整型，字符型----C语言中
				case '+':
					if (c1.data[c1.top - 1] != '+'&&c1.data[c1.top - 1] != '-'&&c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '+');
					}
					else//如果不然，则将之前的先都出栈并计算，然后再入栈
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')//将优先级高的运算符先输出计算，其中括号内的优先级最高
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);//计算，并压运算数栈

						}
						PushChar(&c1,'+');
					}
					; break;
				case '-':
					if (c1.data[c1.top - 1] != '+'&&c1.data[c1.top - 1] != '-'&&c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '-');
					}
					else//如果不然，则将之前的先都出栈并计算，然后再入栈
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')//将优先级高的运算符先输出计算，其中括号内的优先级最高
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);//计算，并压运算数栈

						}
						PushChar(&c1, '-');
					}
					; break;
				case '*':
					if (c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '*');
					}
					else//如果不然，则将之前的先都出栈并计算，然后再入栈
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')//将优先级高的运算符先输出计算，其中括号内的优先级最高
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);//计算，并压运算数栈

						}
						PushChar(&c1, '*');
					}
					; break;
				case '/':
					if (c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '/');
					}
					else//如果不然，则将之前的先都出栈并计算，然后再入栈
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')//将优先级高的运算符先输出计算，其中括号内的优先级最高
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);//计算，并压运算数栈

						}
						PushChar(&c1, '/');
					}
					; break;
				case '(':

					PushChar(&c1, '(');

					; break;
				case ')'://并没有将'('压入栈中，只是当作一种出栈信号
					while (c1.data[c1.top - 1] != '(')
					{
						PopChar(&c1, &ch);
						Fun(&n1, ch);//计算，并压运算数栈
					}
					PopChar(&c1, &ch);//将'('也出栈，但并不计算
					; break;
				}

			}
		}
		while (c1.top > 0)//将剩余的运算符出栈并计算
		{
			PopChar(&c1, &ch);
			Fun(&n1, ch);
		}
		printf("\t\t%s=%.2f", str, GetNum(n1));
		printf("\n");
		system("pause");
	}

}
void InitNum(StackNum *p)
{
	p->top = 0;
}
void InitChar(StackChar *p)
{
	p->top = 0;
}
void PushNum(StackNum *p, Num e)
{
	if (p->top == MAX)
		printf("运算数栈满！\n");
	else
	{
		p->data[p->top] = e;
		p->top++;
	}
}
void PushChar(StackChar *p, char e)
{
	if (p->top == MAX)
		printf("运算符栈满！\n");
	else
	{
		p->data[p->top] = e;
		p->top++;
	}
}
void PopNum(StackNum *p, Num *e)
{
	if (p->top == 0)
		printf("运算数栈空！\n");
	else
	{
		p->top--;
		*e = p->data[p->top];
	}
}
void PopChar(StackChar *p, char *e)
{
	if (p->top == 0)
		printf("运算符栈空！\n");
	else
	{
		p->top--;
		*e = p->data[p->top];
	}
}
void Fun(StackNum *p, char e)
{
	Num temp1, temp2;//存放两个临时操作数
	PopNum(p, &temp2);
	PopNum(p, &temp1);
	switch (e)
	{
	case '+':PushNum(p, temp1 + temp2); break;
	case '-':PushNum(p, temp1 - temp2); break;
	case '*':PushNum(p, temp1*temp2); break;
	case '/':PushNum(p, temp1 / temp2); break;

	}
}
Num GetNum(StackNum p)
{
	return p.data[p.top - 1];
}
