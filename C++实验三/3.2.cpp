#include<iostream>
#include<cstring>
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
        //            cout<<"copy constructor is invoked."<<endl;
    };
    virtual ~CPoint() { //析构函数
        nCount--;
        //            cout<<"Deconstruction finished"<<endl;
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
    virtual void ShowPoint() {  //此处声明了虚函数！！
        cout << "<" << x << "," << y << ">" << endl;
    };
    CPoint operator+(CPoint pt);
    friend istream& operator>>(istream& is, CPoint& p);
    friend ostream& operator<<(ostream& os, CPoint& p);
};
int CPoint::nCount = 0;

enum ColorType { White, Black, Red, Green, Blue, Yellow, Magenta, Cyan };
//为图形形状定义Shape基类
class Shape {
protected:
    ColorType color;
public:
    Shape(ColorType c) {
        color = c;
    };
    virtual void draw() {
    };
    virtual string getColor(ColorType c) {
        switch (c) {
        case 0:
            return "White";
        case 1:
            return "Black";
        case 2:
            return "Red";
        case 3:
            return "Green";
        case 4:
            return "Blue";
        case 5:
            return "Yellow";
        case 6:
            return "Magenta";
        case 7:
            return "Cyan";
        default:
            return "";

        }

    };

};

class Cline :public Shape {
private:
    CPoint p0, p1;
public:
    Cline(ColorType c, int x0, int y0, int x1, int y1)
        :Shape(c), p0(x0, y0), p1(x1, y1) {};//初始化列表，用于继承
    virtual void draw() {
        cout << "This is a line. And it's color is " << getColor(color) << "."
            << "It is <" << p0.GetX() << "," << p0.GetY() << ">--><"
            << p1.GetX() << "," << p1.GetY() << ">." << endl;
    }
};

class CTriangle :public Shape {
private:
    CPoint p0, p1, p2, p3;
public:
    CTriangle(ColorType c, int x0 = 0, int y0 = 0,
        int x1 = 0, int y1 = 1, int x2 = 1, int y2 = 1, int x3 = 1, int y3 = 0)
        :Shape(c), p0(x0, y0), p1(x1, y1), p2(x2, y2), p3(x3, y3) {}; //初始化列表
    virtual void draw() {
        cout << "This is a rectangle. And it's color is " << getColor(color) << "."
            << "It is <" << p0.GetX() << "," << p0.GetY() << ">--><" << p1.GetX() << ","
            << p1.GetY() << ">-->" << "<" << p2.GetX() << "," << p2.GetY() << ">--><"
            << p3.GetX() << "," << p3.GetY() << ">." << endl;
    }
};

class CCircle :public Shape {
private:
    CPoint p;
public://初始化列表，用于继承
    CCircle(ColorType c, int x, int y) :Shape(c), p(x, y) {};
    virtual void draw() {
        cout << "This is a circle. And it's color is "
            << getColor(color) << "." << "It's center point is: <"
            << p.GetX() << "," << p.GetY() << ">." << endl;
    }
};

int main() {
    Cline l(White, 0, 1, 2, 3);
    CTriangle t(Blue);
    CCircle c(Cyan, 0, 0);
    Shape* p[3];
    p[0] = &l;
    p[1] = &t;
    p[2] = &c;
    for (int i = 0; i < 3; i++) {
        p[i]->draw();
    }
    return 0;
}