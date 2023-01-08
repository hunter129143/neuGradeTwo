#include<iostream>
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

//空间中的点类
class CThreePoint :public CPoint {
private:
    int z;
public:
    CThreePoint() {};
    CThreePoint(int px = 0, int py = 0, int pz = 0) {
        SetX(px);
        SetY(py);
        z = pz;
    };
    int GetZ() {
        return z;
    };
    void SetZ(int pz) {
        z = pz;
    };
    virtual void ShowPoint() {  //此处virtual关键字可省略。不过习惯上不省略，方便阅读
        cout << "<" << GetX() << "," << GetY() << "," << z << ">" << endl;
    };
};


int main() {
    CPoint a(1, 2);
    CThreePoint b(3, 4, 5);
    CPoint* p;
    p = &a;
    cout << "基类指针指向基类函数示例：" << endl;
    p->ShowPoint();
    p = &b;
    cout << "基类指针指向派生类函数示例：" << endl;
    p->ShowPoint();
    return 0;
}
