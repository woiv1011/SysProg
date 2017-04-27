/* String class with overloaded operators (C++)
 *
 */

#ifndef STRING_H_
#define STRING_H_

#include <iostream>

using namespace std;

class String {

private:
	static const int INITIAL_CAPACITY = 32;
	int length;
	int capacity;
	char* str; // 'String' is represented internally as a plain C-style string.

public:
	String();
	String(char c);
	String(const char* s);
	String(const String&);
	~String();

private:
	bool compareString(char* input, char* search); // Check if the input string equals with the search string.
	int countChars(const char* input); // Computes the length of the given character string.
	void copyContent(char* dest, const char* src, int length); // copy the string from src to dest until length elements are copied.
	void changeSize(int newCapacity); // Create a string with the specified capacity, preserving the old data.
	void ensureCapacity(int minCapacity);

public:
	const char* getData();
	int getLength();
	int isEmpty();
	String& clear();

	String& operator=(const String& s);
	String& operator+=(const String& s);
	String& operator+=(char& s);
	char& operator[](int index);
	bool operator==(const String& s);
	bool operator==(const char*& s);
	bool operator!=(const String& s);

	// make friend, so we can access private members
	friend ostream& operator<<(ostream &out, String &s);

};

#endif /* STRING_H_ */

