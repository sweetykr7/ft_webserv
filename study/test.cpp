#include <iostream>
#include <sstream>


using namespace std;

int main()
{
	// int i=0;
	// string str[3], token; 
	// string a="abc def\nghi";
	
	// stringstream ss;
	// ss.str(a);
	// while (ss >> token) {
	// 	str[i++]=token;
	// 	std::cout << token;
	// }

	// int num1,num2;
	// string str1, str2; 
	// string a="abc 123 def 456";
	// istringstream iss;
	// iss.str(a);
	// iss >> str1 >> num1 >> str2 >> num2;
	// std::cout << str1 << num1 << str2 << num2 << std::endl;

	int num;
	string s;
	string str1 = "abc 123 def";
	
	//3개 모두 같은 의미, stream1을 초기화
	stringstream stream1("abc 123 def");
	//stringstream stream1(str1);
	//stream1.str(str1);


	stream1 >> num; //int형에 맞는 string을 찾는다.
	stream1 >> s; //string형에 맞는 string을 찾는다.

	cout << "s : " << s << endl;
	cout << "num : " << num << endl;

	return 0;
}