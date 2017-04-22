/*
 * LinkedListTest.cpp
 *
 * Zum Testen der LinkedList
 *
 *  Created on: Nov 10, 2015
 *      Author: lejo1015
 */

#include<iostream>
#include "../includes/LinkedList.h"
#include "../../String/includes/String.h"

int main() {
	std::cout << "Der Test für die LinkedList beginnt" << std::endl;
	LinkedList<int> list;
	int a = 1;
	int b = 2;
	int c = 3;
	int* z = &a;
	int* y = &b;
	int* x = &c;
	String strz("Nr.1");
	String stry("Nr.2");
	String strx("Nr.3");

	list.add(strz)->setData(z);
	list.add(stry)->setData(y);
	list.add(strx)->setData(x);

	if (*list.get(strz)->getData() != 1)
		cerr << "Fehler in LinkedListTest.cpp 1" << endl;
	if (list.get(strz)->getName() != strz)
		cerr << "Fehler in LinkedListTest.cpp 2" << endl;

	if (list.find(1) != stry)
		cerr << "Fehler in LinkedListTest.cpp 3" << endl;
	if (list.find(stry) != 1)
		cerr << "Fehler in LinkedListTest.cpp 4" << endl;

	if (list.getSize() != 3)
		cerr << "Fehler in LinkedListTest.cpp 5" << endl;

	std::cout << "Der Test für die LinkedList abgeschlossen" << std::endl;
}

