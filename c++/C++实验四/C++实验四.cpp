#include<iostream>
#include<cstring>
using namespace std;
 
template<class T>
T min(T& a, T& b) {
	return (a<b)?a:b;
}
//char* min(char*, char*)无法将参数 1 从“const char[8]”转换为“char * ”

const char* min(const char* a, const char* b) {
	return (strcmp(a,b)<0)?a:b; //strcmp()函数
}
 
int main() {
	cout<<"the min one of 1 and 3 is:"
	    <<min(1,3)<<endl;
	cout<<"the min one of \"computer\" and \"compare\" is:"
	    <<min("compare","computer")<<endl;
	return 0;
}