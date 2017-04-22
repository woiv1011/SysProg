/**
 * LinkedList.h
 *
 * Diese Klasse implementiert eine generische doppelt verkettete Liste.
 *
 * Hinweis: Die Konstruktoren und Methoden werden im Header File definiert,
 * weil es der Compiler nicht versteht wenn Deklaration und Definition von
 * Templates getrennt werden. Für genaueres siehe Internet.
 *
 *  Created on: Nov 09, 2015
 *      Author: lejo1015
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include<iostream>
#include "../includes/Node.h"
#include "../../String/includes/String.h"

template<typename T>
class LinkedList {

private:

	// Segmentationfault in add() mittels prüfen von size umgehen
	Node<T> *start;
	int size;

public:
	LinkedList();

	Node<T>* add(String& name);
	T* remove(int index);
	T* remove(String& name);
	Node<T>* get(int index);
	Node<T>* get(String& name);
	int find(String& name);
	String find(int index);

	int getSize();

	~LinkedList();
};

template<typename T>
LinkedList<T>::LinkedList() {
	this->start = NULL;
	size = 0;
}

/**
 * Fügt an den Anfang der Liste ein neues Element ein mit einer Referenz auf T ein.
 * Erzeuge keine Objekte mit demselben Namens
 */
template<typename T>
Node<T>* LinkedList<T>::add(String& name) {
	Node<T>* node = new Node<T>(name);
	//if(start) { // accepts if pointer isn't pointing on null
	if (size != 0) {
		this->start->prev = node;
		node->next = this->start;
	}
	this->start = node;
	size++;
	return node;
}

/**
 * Entfernt das Objekt am angegebenen Index.
 */
template<typename T>
T* LinkedList<T>::remove(int index) {
	if (size > index && index >= 0) {
		Node<T>* node = this->start;
		for (int i = 0; i < index; i++) {
			node = node->next;
		}
		T* data = node->getData();

		Node<T>* after = NULL;
		Node<T>* before = NULL;
		if (node->next && node->prev) {
			after = node->next;
			before = node->prev;
			after->prev = before;
			before->next = after;
		} else if (node->next) {
			after = node->next;
			after->prev = NULL;
			this->start = after;
		} else if (node->prev) {
			before = node->prev;
			before->next = NULL;
		} else {
			this->start = NULL;
		}
		//node->~Node();
		size--;
		return data;
	} else {
		throw "Das ist richtige scheiße";
	}
}

/**
 * Entfernt das Objekt mit dem angegeben Namen.
 * Gibt das entfernte Objekt zurück.
 * Existiert das Objekt nicht wird NULL zurück geliefert.
 */
template<typename T>
T* LinkedList<T>::remove(String& name) {
	return remove(find(name));
}

/**
 * Gibt das Objekt am angegebenen Index zurück.
 * Falls der Index nicht existiert wird ein Fehler geworfen.
 */
template<typename T>
Node<T>* LinkedList<T>::get(int index) {
	if (size > index && index >= 0) {
		Node<T>* node = this->start;
		for (int i = 0; i < index; i++) {
			node = node->next;
		}
		return node;
	} else {
		throw "falscher Index";
	}
}

/**
 * Gibt das Objekt mit dem angegebenen Namen zurück.
 * Wenn das Objekt nicht enthalten ist wird NULL zurückgegeben.
 */
template<typename T>
Node<T>* LinkedList<T>::get(String& name) {
	Node<T>* node = this->start;
	if (node->getName() == name) { // checkt erstes Element
		return node;
	}
	if (node) {
		while (node->next) { // solange nächstes Element existiert
			node = node->next;
			if (node->getName() == name) { // checkt nächstes Element
				return node;
			}
		}
		return NULL; // es gibt kein Element mehr
	} else {
		return NULL; // es gibt nur ein Element
	}
}

/**
 * Returns the size of the LinkedList.
 */
template<typename T>
int LinkedList<T>::getSize() {
	return size;
}

/**
 * Findet das Objekt mit dem angegeben Namen und gibt dessen Index zurück.
 * Gibt -1 zurück wenn das Objekt nicht enthalten ist.
 */
template<typename T>
int LinkedList<T>::find(String& name) {
	// The mistake is either in here or in remove
	// the old indexes of the objects are returned, before they were removed,
	// but the indexs should be -1
	if (this->start) {
		Node<T> *node = this->start;
		int index = 0;
		if (node->getName() == name) {
			return index;
		}
		while (node->next) {
			node = node->next;
			index++;
			if (node->getName() == name) {
				return index;
			}
		}
	}
	return -1;
}
/**
 * Findet den Namen des Objekts am angegebenen Index und gibt ihn zurück.
 * Gibt den String "" zurücke wenn der Index nicht existiert.
 */
template<typename T>
String LinkedList<T>::find(int index) {
	if (size > index && index >= 0) {
		Node<T>* node = this->start;
		for (int i = 0; i < index; i++) {
			node = node->next;
		}
		return node->getName();
	} else {
		return String("");
	}
}

template<typename T>
LinkedList<T>::~LinkedList() {
	Node<T>* nextElem = start;
	while (nextElem) {
		Node<T>* node = nextElem;
		nextElem = node->next;
		delete node;
	}
}

#endif /* LINKEDLIST_H_ */
