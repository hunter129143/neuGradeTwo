#include<iostream>
using namespace std;

class vehicle {

public:
	double MaxSpeed, Weight;
	virtual void Run() {
		cout << "�ã��������ˣ��ٶ��ǣ�" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "�ã�ͣ�ˣ�" << endl;
	}
};

class bicycle :virtual public vehicle {	//�����̳�

public:
	double Height;
	virtual void Run() {
		cout << "�ã����г��������ˣ��ٶ��ǣ�" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "�ã����г�ͣ�ˣ�" << endl;
	}

};

class motorcar :virtual public vehicle {	//�����̳�


public:
	int SeatNum;
	virtual void Run() {
		cout << "�ã������������ˣ��ٶ��ǣ�" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "�ã�����ͣ�ˣ�" << endl;
	}
};

class motorcycle :public bicycle, public motorcar {
public:
	virtual void Run() {
		cout << "�ã�Ħ�г��������ˣ��ٶ��ǣ�" << MaxSpeed << endl;
	}

	virtual void Stop() {
		cout << "�ã�Ħ�г�ͣ�ˣ�" << endl;
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