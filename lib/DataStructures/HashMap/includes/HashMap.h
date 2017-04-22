/**
 * HashMap.h
 *
 * Implementiert eine generische HashMap. Das Einfügen ist relativ leicht.
 * Das Finden und Entfernen von Objekten muss noch teilweise selbst gemacht werden.
 * Mittels get bekommt man die Liste in der das gewünschte Objekt liegen sollte,
 * die Liste muss allerdings selbst durchsucht werden um das Objekt zu finden oder zu entfernen.
 *
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

// andere Programmiermöglichkeit, in LinkedList zu jedem Objekt einen Namen dazu geben. dann kann das finden des Objekts vereinfacht werden.

#include <iostream>
#include "../../LinkedList/includes/LinkedList.h"
#include "../../String/includes/String.h"

// #define TABLE_SIZE 22147
// Diese Konstante kann nicht für die Größe der Hashmap verwendet werden, es gibt einen syntax fehler

enum table_size_t {
	table_size_11 = 11,
	table_size_653 = 653,
	table_size_1999 = 1999,
	table_size_3041 = 3041,
	table_size_4001 = 4001,
	table_size_5021 = 5021,
	table_size_10007 = 10007,
	table_size_22147 = 22147,
	table_size_33629 = 33629,
	table_size_49999 = 49999,
	table_size_99991 = 99991
};

template<typename T> class HashMap {
private:
	int tableSize;
	LinkedList<T>* * map; // muss eine Primzahl sein, damit die Hashfunktion gut funktioniert
// verschiedene Primzahlen: 1999, 3041, 4001, 5021, 10007, 22147, 33629, 49999, 99991
	int hashFunc(String&);

public:
	HashMap();
	HashMap(table_size_t size);

	Node<T>* insert(String& key);
	Node<T>* get(String& key);
	void insertValue(String key, T* value);
	void insertValue(String& key, T* value);
	T* getValue(String& key);
	T* remove(String& key);

	~HashMap();
};
template<typename T>
HashMap<T>::HashMap() {
	this->tableSize = table_size_10007;
	map = new LinkedList<T>*[tableSize];
	for (int i = 0; i < tableSize; i++) {
		map[i] = new LinkedList<T>();
	}
}

template<typename T>
HashMap<T>::HashMap(table_size_t size) {
	this->tableSize = size;
	map = new LinkedList<T>*[tableSize];
	for (int i = 0; i < tableSize; i++) {
		map[i] = new LinkedList<T>();
	}
}

/**
 * Berechnet aus dem Namen des Objekts den Index in der Hashtabelle.
 */
template<typename T>
int HashMap<T>::hashFunc(String& string) {
	int i = 0;
	unsigned int key = 4001;
	while (string[i]) {
		unsigned int c = (static_cast<unsigned int>(string[i]));
		key = c + (key << 6) + (key << 16) - key;
		i++;
	}
	key = key * 49999; // multipliziert mit großer Primzahl
	key = key % this->tableSize; // Gr��e der Tabelle
	return key;
}

/**
 * Setzt die Referenz für das Objekt V mit dem Namen key in die HashMap.
 * Wenn schon ein Ojekt mit dem Namen key existiert gib die Referenz auf dieses zurück und setze die neue Referenz NICHT hinein.
 */
template<typename T>
Node<T>* HashMap<T>::insert(String& key) {
	int index = hashFunc(key);
	int linkedListIndex = map[index]->find(key);
	if (linkedListIndex != -1) {
		return map[index]->get(linkedListIndex);
	}
	return map[index]->add(key);
}

/**
 * Gibt die Liste, in der die Referenz für das Objekt V ist, dessen Name key, ist zurück.
 */
template<typename T>
Node<T>* HashMap<T>::get(String& key) {
	int index = hashFunc(key);
	return map[index]->get(key);
}

template<typename T>
inline void HashMap<T>::insertValue(String key, T* value) {
	insert(key)->setData(value);
}

template<typename T>
inline void HashMap<T>::insertValue(String& key, T* value) {
	insert(key)->setData(value);
}

template<typename T>
inline T* HashMap<T>::getValue(String& key) {
	return get(key)->getData();
}

/**
 * Entfernt das Objekt mit dem angegebene Key (Namen) aus der Hashtabelle.
 * Gibt die Referenz auf das Objekt zurück.
 */
template<typename T>
T* HashMap<T>::remove(String& key) {
	int index = hashFunc(key);
	return map[index]->remove(key);
}

template<typename T>
HashMap<T>::~HashMap() {
	for (int i = 0; i < this->tableSize; i++) {
		delete map[i];
	}
	delete[] map;
}

#endif /* HASHMAP_H_ */
