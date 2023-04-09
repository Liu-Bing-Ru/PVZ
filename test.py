#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


class Tester {
public:
	int key;
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
	int f6;
	int f7;
	int class_type;

};



int main()
{

	Tester array[5000];
	ifstream inputfile;
	//inputfile 是名稱
	inputfile.open("Missing_Data_7features.csv");
	//line 是 string datatype
	string line = "";
	while (getline(inputfile, line)) {
		
		int key;
		/*int f1;
		int f2;
		int f3;
		int f4;
		int f5;
		int f6;
		int f7;
		int class_type;*/
		string tempstring; //用來轉換 文字 to 數字
		string tem;

		stringstream inputString(line); //不知道這行意思

		// 要用單引號 因為CHAR
		getline(inputString, tem, ',');
		key = atoi(tem.c_str());
		array[0].key = key;
		/*getline(inputString, f1, ",");
		getline(inputString, f2, ",");
		getline(inputString, f3, ",");
		getline(inputString, f4, ",");
		getline(inputString, f5, ",");
		getline(inputString, f6, ",");
		getline(inputString, f7, ",");
		getline(inputString, class_type, ",");*/
		cout << array[0].key;
		//line = "";

	}


	return 0;

}
