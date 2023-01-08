#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include<stdio.h>
#include "math.h"

using namespace std;

template<class T> class List {
public:
	List() { //构造函数
		pFirst = NULL;
	}

	void Add(T& t) { //在List表头添加新结点
		if (pFirst == NULL) {
			pFirst = new Node;
			*(pFirst->pT) = t;
		}
		else {
			Node* last = pFirst;
			while ((last->pNext) != NULL) {
				last = last->pNext;
			};
			Node* pNewNode = new Node;
			*(pNewNode->pT) = t;

			pNewNode->pNext = NULL;
			last->pNext = pNewNode;
		}
	}

	void Remove(T& t) { //在List中删除含有特定值的元素
		Node* pNode = pFirst;
		if (*(pNode->pT) == t) {
			pFirst = pFirst->pNext;
			delete pNode;
			return;
		}
		while (pNode != NULL) {
			Node* pNextNode = pNode->pNext;
			if (pNextNode != NULL) {
				if (*(pNextNode->pT) == t) {
					pNode->pNext = pNextNode->pNext;
					delete pNextNode;
					return;
				}
			}
			else
				return;//没有相同的
			pNode = pNode->pNext;
		}
	}

	T* Find(T& t) { //查找含有特定值的结点
		Node* pNode = pFirst;
		while (pNode != NULL) {
			if (*(pNode->pT) == t) {
				return pNode->pT;
			}
			pNode = pNode->pNext;
		}
		return NULL;
	}

	void PrintList() { // 打印输出整个链表
		if (pFirst == NULL) {
			cout << "null..." << endl;
			return;
		}
		Node* pNode = pFirst;
		while (pNode != NULL) {
			cout << *(pNode->pT) << endl;
			pNode = pNode->pNext;
		}
	}

	~List() {
		Node* pNode = pFirst;
		while (pNode != NULL) {
			Node* pNextNode = pNode->pNext;
			delete pNode;
			pNode = pNextNode;
		}
	}
protected:
	struct Node {
		Node* pNext;
		T* pT;

		Node() {
			pNext = NULL;
			pT = new T;
		}
		~Node() {
			delete pT;
		}
	};
	Node* pFirst;        //链首结点指针
};

class Student {
public:
	char id[20];    //学号
	char name[20];    //姓名
	int score;    //成绩
	Student() {
	}
	~Student() {
	}
	Student(const char* pid, const char* pname, int _score) {
		strcpy(id, pid);
		strcpy(name, pname);
		score = _score;
	}
	bool operator==(const Student& stu) {
		return strcmp(id, stu.id) == 0 && strcmp(id, stu.id) == 0 && score == stu.score;
	}
	Student& operator=(const Student& stu) {
		strcpy(id, stu.id);
		strcpy(name, stu.name);
		score = stu.score;
		return *this;
	}
	friend ostream& operator<< (ostream& out, const Student& stu);
};

ostream& operator<< (ostream& out, const Student& stu) {
	out << "id:" << stu.id << " name:" << stu.name << " score:" << stu.score << endl;
	return out;
}

int main() {
	List<Student> worldCup;
	cout << "Before the adding:" << endl;
	worldCup.PrintList();
	cout << "\n\n\n";

	Student stu1("1", "Sweden", 6);
	Student stu2("2", "Mexico", 6);
	Student stu3("3", "Korea", 3);
	Student stu4("4", "Germany", 3);

	worldCup.Add(stu1);
	worldCup.Add(stu2);
	worldCup.Add(stu3);
	worldCup.Add(stu4);
	cout << "After the adding:" << endl;
	worldCup.PrintList();
	cout << "\n\n\n";

	Student kidding("4", "Germany", 3);
	Student* pStu = worldCup.Find(kidding);
	cout << "The result of searching for the student \"kidding\": " << *pStu;
	cout << "\n\n\n";

	worldCup.Remove(kidding);
	cout << "After the removing of the student \"kidding\":";
	cout << endl;
	worldCup.PrintList();
	cout << "\n\n\n";

	return 0;
}