#include<iostream>
#include "../includes/HashMap.h"

using std::cout;
using std::cerr;
using std::endl;

int main() {
	cout << "Der Test für die HashMap beginnt:" << endl;

	HashMap<int> map;
	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	int* r1 = &i1;
	String s1("Nr.1");
	String s2("2");
	String s3("Nr.3");

	map.insert(s1)->setData(&i1);
	map.insert(s2)->setData(&i2);
	map.insert(s3)->setData(&i3);

	if (*map.get(s1)->getData() != 1)
		cerr << "Fehler in HashMapTest.cpp test() 1" << endl;
	if (*map.get(s2)->getData() != 2)
		cerr << "Fehler in HashMapTest.cpp test() 2" << endl;
	if (*map.get(s3)->getData() != 3)
		cerr << "Fehler in HashMapTest.cpp test() 3" << endl;

	if (map.get(s3)->getName() != s3)
		cerr << "Fehler in HashMapTest.cpp test() 4" << endl;

	cout << "Der Test für die HashMap ist beendet" << endl;
}
