#include<iostream>
#include<cmath>
using namespace std;

//平面上的点类
class CPoint {
private:
	int x, y;
public:
	static int nCount;   // nCount用于保存点的个数
	CPoint(int px = 0, int py = 0) { //构造函数
		x = px;
		y = py;
		nCount++;
	};
	CPoint(CPoint& p) { //拷贝构造
		x = p.x;
		y = p.y;
		nCount++;
		//			cout<<"copy constructor is invoked."<<endl;
	};
	~CPoint() { //析构函数
		nCount--;
		//			cout<<"Deconstruction finished"<<endl;
	};
	int GetX() {
		return x;
	};
	int GetY() {
		return y;
	};
	void SetX(int px) {
		x = px;
	};
	void SetY(int py) {
		y = py;
	};
	void ShowPoint() {
		cout << "<" << x << "," << y << ">" << endl;
	};
	CPoint operator+(CPoint pt);
	friend istream& operator>>(istream& is, CPoint& p);
	friend ostream& operator<<(ostream& os, CPoint& p);
};
int CPoint::nCount = 0;
//平面上的直线类
class CLine {
private:
	CPoint pt1, pt2;  //pt1和pt2分别代表该线段的起点和终点
public:
	CLine() {
	};
	CLine(int x1, int y1, int x2, int y2)
		:pt1(x1, y1), pt2(x2, y2) {
	};
	CLine(CPoint p1, CPoint p2)
		:pt1(p1), pt2(p2) {
	};
	double Distance() { //计算该线段长度的成员函数
		int x_x = pt1.GetX() - pt2.GetX();
		int y_y = pt1.GetY() - pt2.GetY();
		double dis = pow((double)(pow(x_x, 2) + pow(y_y, 2)), 0.5);
		return dis;
	};
	void ShowLine() {
		cout << "<" << pt1.GetX() << "," << pt1.GetY() << ">"
			<< "-->"
			<< "<" << pt2.GetX() << "," << pt2.GetY() << ">"
			<< endl;
	};
};

CPoint CPoint::operator+(CPoint pt) { //成员函数重载+
	CPoint sumPoint;
	sumPoint.SetX(pt.GetX() + this->GetX());
	sumPoint.SetY(pt.GetY() + this->GetY());
	return sumPoint;
}

CPoint operator- (CPoint pt1, CPoint pt2) { //全局重载-
	CPoint difPoint;
	difPoint.SetX(pt1.GetX() - pt2.GetX());
	difPoint.SetY(pt1.GetY() - pt2.GetY());
	return difPoint;
}

istream& operator>>(istream& is, CPoint& p) { //成员函数重载》
	is >> p.x >> p.y;
	return is;
}

ostream& operator<<(ostream& os, CPoint& p) { //成员函数重载《
	os << "<" << p.x << "," << p.y << ">";
	return os;
}
int main() {
	//验证点类的正确实现
	CPoint a(1, 2), b(3, 4), c(a);
	cout << "the first point is:a";
	a.ShowPoint();
	cout << "the second point is:b";
	b.ShowPoint();
	cout << "the third point is:c";
	a.ShowPoint();
	cout << "the nCount is:" << CPoint::nCount << endl;

	//验证线类的正确实现
	CLine d, e(1, 1, 1, 1), f(a, b);
	cout << "the first line is:";
	d.ShowLine();
	cout << "the second line is:";
	e.ShowLine();
	cout << "the third line is:";
	f.ShowLine();
	cout << "the third line's distance is:";
	cout << f.Distance() << endl;

	//验证+，-重载运行符的正确实现
	CPoint sumAB, difAB;
	sumAB = a + b;
	difAB = a - b;
	cout << "the result of a+b is: ";
	sumAB.ShowPoint();
	cout << "the result of a-b is: ";
	difAB.ShowPoint();

	//验证 》，《 重载运算符的实现
	CPoint overloadCP;
	cout << "Enter two numbers to make a point: " << endl;
	cin >> overloadCP;
	cout << "Your point is: ";
	cout << overloadCP << endl;
	return 0;
}