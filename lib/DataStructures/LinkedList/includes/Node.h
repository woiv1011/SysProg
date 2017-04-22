/*
 * Node.h
 *
 * Implementiert ein Element einer LinkedList.
 * Es enthält eine Referenz auf das eigentliche Datenobjekt und den Namen des Datenobjekts.
 *
 *
 *  Created on: Nov 09, 2015
 *      Author: lejo1015
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include "../../String/includes/String.h"

template<typename T> class Node {
private:
	T* data;
	String name;

public:
	Node<T> *next;
	Node<T> *prev;

	Node();
	Node(String&);
	Node(T*, String&);

	T* getData();
	String& getName();
	void setData(T*, String&);
	void setData(T*);

	//todo
	~Node();
};

template<typename T>
Node<T>::Node() {
	data = 0;
	name = NULL;
	next = NULL;
	prev = NULL;
}

template<typename T>
Node<T>::Node(String& _name) {
	data = NULL;
	name = _name;
	next = NULL;
	prev = NULL;
}

template<typename T>
Node<T>::Node(T* _data, String& _name) {
	data = _data;
	name = _name;
	next = NULL;
	prev = NULL;
}

/**
 * Gibt den Inhalt des Elements zurück.
 */
template<typename T>
T* Node<T>::getData() {
	return data;
}

/**
 * Gibt den Namen des Elementes zurück.
 */
template<typename T>
String& Node<T>::getName() {
	return name;
}

/**
 * Setzt die Attribute des Objektes
 */
template<typename T>
void Node<T>::setData(T* _data, String& _name) {
	data = _data;
	name = _name;
}

/**
 * Setzt die Attribute des Objektes
 */
template<typename T>
void Node<T>::setData(T* _data) {
	data = _data;
}

template<typename T>
Node<T>::~Node() {
	delete data;
}

#endif /* NODE_H_ */
