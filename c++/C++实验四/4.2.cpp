#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
using namespace std;

template <class T>
class Stack {
private:
	vector<T> elems;     // Ԫ��

public:
	void push(T const&);  // ��ջ
	void pop();               // ��ջ
	T top() const;            // ����ջ��Ԫ��
	bool empty() const {      // ���Ϊ���򷵻��档
		return elems.empty();
	}
};

template <class T>
void Stack<T>::push(T const& elem) {
	// ׷�Ӵ���Ԫ�صĸ���
	elems.push_back(elem);
}

template <class T>
void Stack<T>::pop() {
	if (elems.empty()) {
		throw out_of_range("Stack<>::pop(): empty stack");
	}
	// ɾ�����һ��Ԫ��
	elems.pop_back();
}

template <class T>
T Stack<T>::top() const {
	if (elems.empty()) {
		throw out_of_range("Stack<>::top(): empty stack");
	}
	// �������һ��Ԫ�صĸ���
	return elems.back();
}

int main() {
	try {
		Stack<int> intStack;  // int ���͵�ջ
		Stack<char> charStack;    // char ���͵�ջ
		Stack<float> floatStack;	//float ���͵�ջ

		// ���� int ���͵�ջ
		intStack.push(7);
		cout << "��ӡintStackջ��Ԫ��:" << intStack.top() << endl;

		// ���� char ���͵�ջ
		charStack.push('c');
		charStack.push('h');
		cout << "��ӡcharStackջ��Ԫ�أ�" << charStack.top() << std::endl;
		charStack.pop();
		charStack.pop();

		//����float���͵�ջ
		floatStack.push(1.0);
		cout << "��ӡfloatStackջ��Ԫ��:" << floatStack.top() << std::endl;
		floatStack.pop();
		floatStack.pop();
	}
	catch (exception const& ex) {
		cerr << "Exception: " << ex.what() << endl;
		return -1;
	}
}