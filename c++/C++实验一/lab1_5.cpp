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
	infile.open(file.data());   //���ļ����������ļ���������
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ��������

	string c;
	int i = 0;
	while (true) {
		i++;
		getline(infile, c);
		if (infile.eof())
			break;
		cout << i << ":" << c << endl;
	}
	infile.close();             //�ر��ļ�������
}