/**
 * ArrayList.h
 *
 * Implementiert eine dynamische, indizierte, generische Liste.
 *
 */

#include <iostream>

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

// TODO - Rename class to ArrayList
template<class T> class List {
private:
	static const int INITIAL_CAPACITY = 10;
	T *elemente;
	int size;
	int capacity;
	void ensureCapacity(int minCapacity);

public:
	List<T>();
	List<T>(int capacity);
	List<T>(int capacity, T initalValue);
	~List();

	T get(int index);
	void set(T, int);
	void add(T, int);
	void add(T);
	void addAll(List<T>*);
	T remove(int);
	void clear();
	int getSize();

};

template<class T>
List<T>::List() {
	elemente = NULL;
	this->capacity = 0;
	this->size = 0;
	ensureCapacity(INITIAL_CAPACITY);
}

template<class T>
List<T>::List(int capacity) {
	elemente = NULL;
	this->capacity = 0;
	this->size = 0;
	ensureCapacity(capacity);
}

template<class T>
List<T>::List(int size, T initalValue) {
	elemente = NULL;
	this->capacity = 0;
	this->size = 0;
	ensureCapacity(size);

	for (int i = 0; i < size; i++) {
		elemente[i] = initalValue;
	}
	this->size = size;
}

template<class T>
List<T>::~List() {
	delete[] elemente;
}

template<class T>
void List<T>::ensureCapacity(int minCapacity) {
	int oldCapacity = capacity;

	if (minCapacity > oldCapacity) {
		int newCapacity = (oldCapacity * 3) / 2 + 1;
		if (newCapacity < minCapacity) {
			newCapacity = minCapacity;
		}
		// minCapacity is usually close to size, so this is a win:

		T *cp = new T[newCapacity];
		for (int i = 0; i < size; i++) {
			cp[i] = elemente[i];
		}
		delete[] elemente;
		elemente = cp;
		capacity = newCapacity;
	}
}

template<class T>
T List<T>::get(int index) {
	return elemente[index];
}

template<class T>
void List<T>::set(T object, int index) {
	elemente[index] = object;
}

/**
 * Inserts the Object at the index. Any Objects with higher index will be at index+1.
 */
template<class T>
void List<T>::add(T object, int index) {
	T *cp = new T[size + 1];
	for (int i = 0; i < index; i++) {
		cp[i] = elemente[i];
	}
	cp[index] = object;
	for (int i = index + 1; i < size + 1; i++) {
		cp[i] = elemente[i - 1];
	}
	delete[] elemente;
	elemente = cp;
	size++;
	capacity = size;
}

/**
 * Inserts the Object at the End of the list.
 */
template<class T>
void List<T>::add(T object) {
	ensureCapacity(size + 1);
	elemente[size++] = object;
}

template<class T>
void List<T>::addAll(List<T>* list) {
	ensureCapacity(size + list->size);
	for (int i = 0; i < list->size; i++) {
		elemente[size++] = list->elemente[i];
	}
}

/**
 * Removes the object at the index and returns it.
 */
template<class T>
T List<T>::remove(int index) {
	T *cp = new T[size - 1];
	for (int i = 0; i < index; i++) {
		cp[i] = elemente[i];
	}
	for (int i = index; i < size - 1; i++) {
		cp[i] = elemente[i + 1];
	}
	T erg = elemente[index];
	delete[] elemente;
	elemente = cp;
	size--;
	capacity = size;
	return erg;
}

template<class T>
void List<T>::clear() {
	for (int i = 0; i < size; i++) {
		elemente[i] = NULL;
	}
	size = 0;
}

template<class T>
int List<T>::getSize() {
	return size;
}

#endif /* ARRAYLIST_H_ */

