#include <iostream>
using namespace std;

void matrixTransposed(int matrix[3][3]);
int main() {
	int matrix[3][3];
	cout << "Enter a 3x3 matrix, please. " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> matrix[i][j];
		}
	}
	matrixTransposed(matrix);
	cout << "The transposed matrix is: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

void matrixTransposed(int matrix[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < i + 1; j++) {
			int temp;
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
}