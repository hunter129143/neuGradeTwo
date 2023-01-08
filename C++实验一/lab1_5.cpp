#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cassert>
#include <string>

#include <stdio.h>

using namespace std;

void printTxt(string file);
int main(int argc, char* argv[]) { 
	string filename = argv[1];
	printTxt(filename);
	return 0;
}
void printTxt(string file) {
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

	string c;
	int i = 0;
	while (true) {
		i++;
		getline(infile, c);
		if (infile.eof())
			break;
		cout << i << ":" << c << endl;
	}
	infile.close();             //关闭文件输入流
}