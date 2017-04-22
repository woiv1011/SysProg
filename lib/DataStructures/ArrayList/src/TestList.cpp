/**
 * Main.cpp
 *
 * Testfile for the class List.
 */

#include<iostream>
#include "../includes/List.h"

void test1();
void test2();

int main() {
	std::cout << "Dies ist der Test für die Klasse Liste." << std::endl;
	test1();
	test2();
	std::cout << "Der Test für die Klasse Liste ist beendet." << std::endl;
}

void test1() {
	List<int> list;
	list.add(3, 0);
	list.add(4, 1);
	if (list.getSize() != 2) {
		throw "Exception in Test1.1";
	}
	if (list.get(1) != 4) {
		throw "Exception in Test1.2";
	}

}

void test2() {
	List<char*> list;
	char str1[] = "Hallo";
	char str2[] = "Welt";
	list.add(str2);
	list.add(str1);
	if (list.get(0) != str1) {
		std::cerr << "Fehler in /List/debug/Test.cpp test2().1" << std::endl;
	}
	char* erg1 = list.remove(0);
	char* erg2 = list.remove(0);
	if (erg2 != str2) {
		std::cerr << "Fehler in /List/debug/Test.cpp test2().2" << std::endl;
		std::cerr << erg1 << std::endl;
		std::cerr << erg2 << std::endl;
	}
	if (list.getSize() != 0) {
		std::cerr << "Fehler in /List/debug/Test.cpp test2().3" << std::endl;
	}
}
