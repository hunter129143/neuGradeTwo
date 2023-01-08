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

	for (int x = 0; x < a.size(); x++) { //排序
		for (int y = x; y < a.size(); y++) {
			if (a[x] > a[y]) {
				int z = a[x];
				a[x] = a[y];
				a[y] = z;
			}
		}
	}

	for (int x = 0; x < a.size(); x++) { //第一种方式考虑采用类似于数组的随机访问方法
		cout << a[x] << " ";
	}
	cout << endl;

	vector<int>::iterator start = a.begin();//第二种方式利用Vector<int>的迭代器进行输出
	vector<int>::iterator end = a.end();
	while (start != end) {
		cout << *start << " ";
		start++;
	}
	cout << endl;

	for_each(a.begin(), a.end(), show);//第三种方式则利用STL通用算法for_each进行实现
	cout << endl;

	return 0;
}