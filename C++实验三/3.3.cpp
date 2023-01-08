#include<iostream>
using namespace std;

class vehicle {

public:
	double MaxSpeed, Weight;
	virtual void Run() {
		cout << "好，跑起来了！速度是：" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "好，停了！" << endl;
	}
};

class bicycle :virtual public vehicle {	//虚基类继承

public:
	double Height;
	virtual void Run() {
		cout << "好，自行车跑起来了！速度是：" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "好，自行车停了！" << endl;
	}

};

class motorcar :virtual public vehicle {	//虚基类继承


public:
	int SeatNum;
	virtual void Run() {
		cout << "好，汽车跑起来了！速度是：" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "好，汽车停了！" << endl;
	}
};

class motorcycle :public bicycle, public motorcar {
public:
	virtual void Run() {
		cout << "好，摩托车跑起来了！速度是：" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "好，摩托车停了！" << endl;
	}
};

int main() {

	vehicle v;
	v.MaxSpeed = 0;
	bicycle b;
	b.MaxSpeed = 1;
	motorcar mcar;
	mcar.MaxSpeed = 3;
	motorcycle mb;
	mb.MaxSpeed = 2;

	vehicle* pt = &v;
	pt->Run();
	pt->Stop();

	pt = &b;
	pt->Run();
	pt->Stop();

	pt = &mcar;
	pt->Run();
	pt->Stop();

	pt = &mb;
	pt->Run();
	pt->Stop();

	return 0;
}