#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
using namespace std;

template <class T>
class Stack {
private:
	vector<T> elems;     // 元素

public:
	void push(T const&);  // 入栈
	void pop();               // 出栈
	T top() const;            // 返回栈顶元素
	bool empty() const {      // 如果为空则返回真。
		return elems.empty();
	}
};

template <class T>
void Stack<T>::push(T const& elem) {
	// 追加传入元素的副本
	elems.push_back(elem);
}

template <class T>
void Stack<T>::pop() {
	if (elems.empty()) {
		throw out_of_range("Stack<>::pop(): empty stack");
	}
	// 删除最后一个元素
	elems.pop_back();
}

template <class T>
T Stack<T>::top() const {
	if (elems.empty()) {
		throw out_of_range("Stack<>::top(): empty stack");
	}
	// 返回最后一个元素的副本
	return elems.back();
}

int main() {
	try {
		Stack<int> intStack;  // int 类型的栈
		Stack<char> charStack;    // char 类型的栈
		Stack<float> floatStack;	//float 类型的栈

		// 操作 int 类型的栈
		intStack.push(7);
		cout << "打印intStack栈顶元素:" << intStack.top() << endl;

		// 操作 char 类型的栈
		charStack.push('c');
		charStack.push('h');
		cout << "打印charStack栈顶元素：" << charStack.top() << std::endl;
		charStack.pop();
		charStack.pop();

		//操作float类型的栈
		floatStack.push(1.0);
		cout << "打印floatStack栈顶元素:" << floatStack.top() << std::endl;
		floatStack.pop();
		floatStack.pop();
	}
	catch (exception const& ex) {
		cerr << "Exception: " << ex.what() << endl;
		return -1;
	}
}