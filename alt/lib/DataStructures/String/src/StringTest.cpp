/* String Klasse mit ueberladenen Operatoren (C++)
 *
 * Erstellen Sie eine String-Klasse ohne zu Hilfenahme von STL, die es Ihnen erlaubt, den folgenden Code zu schreiben:
 *
 *  void main() {
 *      String s1;
 *      String s2("Hello");
 *      String s3(s2);
 *      s1 += s2;
 *      s2 = s3;
 *      cout << s2 << endl;
 *      cout << s2[ 2 ] << endl;
 *   };
 *
 */

// TODO Rename file to TestString.cpp
#include "../includes/String.h"

using std::cout;
using std::endl;

#include <iostream>
using namespace std;

void mainTest() {
	String s1;
	String s2("Hello");
	String s3(s2);
	s1 += s2;
	s2 = s3;
	cout << s2 << endl;
	cout << s2[2] << endl;
	cout << endl;
}

void extraTest1() {
	String s2("Hello");
	cout << s2 << endl;
	s2[1] = 'a';
	cout << s2 << endl;
	s2[1]++;
	s2[1] += 3;
	cout << s2 << endl;
	cout << endl;
}

void extraTest2() {
	String s1("Hello");
	String s2("World");
	String s3;
	s3 = s1;
	//s3 += String(" ");
	s3 += s2;
	cout << s3 << endl;
	cout << endl;
}

void extraTest3() {
	String s1("Test ");
	cout << s1 << endl;
	//s1 = s1;
	cout << s1 << endl;
	s1 += s1;
	cout << s1 << endl;
	cout << endl;
}

void testCompare() {
	String s1("Test");
	String s2("Test");
	String s3("test");
	String s4("Test ");
	String s5("");
	String s6("");
	String s7('a');
	String s8('a');
	String s9("a");

	// == operator
	if (!(s1 == s2)) {
		cout << "Fehler in testCompare() 1" << endl;
	}
	if (s1 == s3) {
		cout << "Fehler in testCompare() 2" << endl;
	}
	if (s1 == s4) {
		cout << "Fehler in testCompare() 3" << endl;
	}
	if (!(s5 == s6)) {
		cout << "Fehler in testCompare() 4" << endl;
	}
	if (!(s7 == s8)) {
		cout << "Fehler in testCompare() 5" << endl;
	}
	if (!(s7 == s9)) {
		cout << "Fehler in testCompare() 6" << endl;
	}

	// != operator
	if (s1 != s2) {
		cout << "Fehler in testCompare() 1" << endl;
	}
	if (!(s1 != s3)) {
		cout << "Fehler in testCompare() 2" << endl;
	}
	if (!(s1 != s4)) {
		cout << "Fehler in testCompare() 3" << endl;
	}
	if ((s5 != s6)) {
		cout << "Fehler in testCompare() 4" << endl;
	}
	if ((s7 != s8)) {
		cout << "Fehler in testCompare() 5" << endl;
	}
	if ((s7 != s9)) {
		cout << "Fehler in testCompare() 6" << endl;
	}
}

void testBitShift() {
	const int digits = 1;

	String s = "3230987654324 badr & az;";

	cout << "Normal" << "  " << s << endl;
	for (int var = 0; var < s.getLength(); ++var) {
		char c = s[var];
		cout << "  " << "Shift" << "  " << c << "  " << (c << digits) << "  " << (char) (c << digits) << endl;
		s[var] = (c << digits);
	}

	cout << "Shifted" << "  " << s << endl;
}

int main() {
	String s;
	String s2('H');

	cout << s << endl;
	cout << s2 << endl;
	cout << endl;

	mainTest();
	extraTest1();
	extraTest2();
	extraTest3();
	testCompare();
	testBitShift();
}
