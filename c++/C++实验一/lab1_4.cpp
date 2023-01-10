#include <iostream>
using namespace std;

int** matrixTransposed(int** m, int row, int col);

int main() {
	int row, col;
	cout << "Enter the row of the row*col matrix, please: " << endl;
	cin >> row;
	cout << "Enter the col of the row*col matrix, please: " << endl;
	cin >> col;
	cout << "Enter a " << row << "x" << col << " matrix, please." << endl;
	//��̬����һ����ά����
	int** m = new int* [row];
	for (int i = 0; i < row; i++) {
		m[i] = new int[col];
	}
	//�������
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> m[i][j];
		}
	}
	//ת�þ���
	int** mt = new int* [col];
	for (int i = 0; i < col; i++) {
		mt[i] = new int[row];
	}
	mt = matrixTransposed(m, row, col);
	//������
	cout << "The transposed matrix is: " << endl;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			cout << mt[i][j] << " ";
		}
		cout << endl;
	}
	//�ڴ���մ���
	delete[]m;
	delete[]mt;
	return 0;
}

int** matrixTransposed(int** m, int row, int col) {
	int** temp = new int* [col];
	for (int i = 0; i < col; i++) {
		temp[i] = new int[row];
	}
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			temp[i][j] = m[j][i];
		}
	}
	return temp;
}