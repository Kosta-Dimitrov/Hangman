#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void clearConsole()
{
	system("CLS");
}
int main()
{
	fstream testFile5;
	fstream testFile7;
	fstream testFileRandom;
	testFile5.open("fiveLength.txt", ios::in | ios::app | ios::out);
	testFile7.open("sevenLength.txt", ios::in | ios::app | ios::out);
	testFileRandom.open("randomLength.txt", ios::in | ios::app | ios::out);
	string str;
	while (getline(testFile7, str))
	{
		cout << str << " " << str.length() << "\n";
	}
	cout << "5 length words" << endl;
	while (getline(testFile5, str))
	{
		cout << str << " " << str.length() << "\n";
	}
	cout << "random length words" << endl;
	while (getline(testFileRandom, str))
	{
		cout << str << " " << str.length() << "\n";
	}
}
