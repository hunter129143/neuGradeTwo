#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void show(int n) {
	cout << n << " ";
};

int main() {
	vector<int> a;
	int n = 0;
	do {
		cin >> n;
		a.push_back(n);
	} while (n != 0);

	for (int x = 0; x < a.size(); x++) { //����
		for (int y = x; y < a.size(); y++) {
			if (a[x] > a[y]) {
				int z = a[x];
				a[x] = a[y];
				a[y] = z;
			}
		}
	}

	for (int x = 0; x < a.size(); x++) { //��һ�ַ�ʽ���ǲ��������������������ʷ���
		cout << a[x] << " ";
	}
	cout << endl;

	vector<int>::iterator start = a.begin();//�ڶ��ַ�ʽ����Vector<int>�ĵ������������
	vector<int>::iterator end = a.end();
	while (start != end) {
		cout << *start << " ";
		start++;
	}
	cout << endl;

	for_each(a.begin(), a.end(), show);//�����ַ�ʽ������STLͨ���㷨for_each����ʵ��
	cout << endl;

	return 0;
}