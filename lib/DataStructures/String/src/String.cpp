#include "../includes/String.h"

#include <cstddef>

String::String() {
	length = 0;
	capacity = INITIAL_CAPACITY;
	str = new char[capacity + 1];
	str[length] = '\0';
}

String::String(char c) {
	length = 1;
	capacity = INITIAL_CAPACITY;
	str = new char[capacity + 1];
	str[0] = c;
	str[length] = '\0';
}

String::String(const char* s) {
	length = countChars(s); // Set the size of the new string.
	capacity = length > INITIAL_CAPACITY ? length : INITIAL_CAPACITY;
	str = new char[capacity + 1]; // Initialize the content of the new string
	copyContent(str, s, length); // Copy from s excluding the terminal character.
	str[length] = '\0';
}

String::String(const String& s) {
	length = s.length; // Set the size of the new string.
	capacity = length > INITIAL_CAPACITY ? length : INITIAL_CAPACITY;
	str = new char[capacity + 1]; // Initialize the content of the new string
	copyContent(str, s.str, length); // Copy content from s excluding the terminal character.
	str[length] = '\0';
}

String::~String() {
	delete[] str;
	str = NULL;
}

// Check if the input string equals with the search string. If the search string is empty and the input string is not empty, then they are not equals.
bool String::compareString(char* input, char* search) {
	char * i = NULL;
	char * s = NULL;

	if (input == NULL) {
		return search == NULL; // return false if the input string is NULL and the search string is not NULL, then they are not equals. If the input string is NULL and the search string is NULL they are equals.
	}

	if (search == NULL) {
		return false; // return false if the input string is not NULL (specified) but the search string is NULL (not specified).
	}

	if (*input == '\0') {
		return *search == '\0'; // return false if the input string is empty and the search string is not empty, then they are not equals. If the input string is empty and the search string is empty they are equals.
	}

	if (*search == '\0') {
		return *input == '\0'; // return false if the search string is empty and the input string is not empty, then they are not equals. If the search string is empty and the input string is empty they are equals.
	}

	for (i = input, s = search; (*i != '\0' && *s != '\0'); i++, s++) {
		if (*i != *s) {
			return false;
		}
	}

	return (*i == '\0') && (*s == '\0'); // return true only if the end of input string and the end of search string was reached.
}

// Computes the length of the given character string.
int String::countChars(const char* input) {
	int size = 0;

	if (input == NULL) {
		return 0;
	}

	for (const char *i = input; *i != '\0'; i++) {
		size++;
	}

	return size;
}

// Copy the content of src into dest until size characters are copied.
// The parameter offset defines the offset index where the first character is stored.
void String::copyContent(char* dest, const char* src, int length) {
	if ((src == NULL) || (dest == NULL))
		return;

	for (int i = 0; i < length; i++) {
		*dest++ = *src++; // Copies element *(src) to *(dest), then increments both pointers.
	}
}

// Change the size of the internal array, preserving the old data.
void String::changeSize(int newCapacity) {
	char* newstr = new char[newCapacity + 1];

	copyContent(newstr, str, newCapacity > length ? length : newCapacity); // Preserve content and handle a smaller capacity.

	newstr[newCapacity] = '\0'; // Set the terminal character at the end.

	delete[] str;
	str = newstr;
	length = newCapacity > length ? length : newCapacity;
	capacity = newCapacity;
}

void String::ensureCapacity(int minCapacity) {
	int oldCapacity = capacity;

	if (minCapacity > oldCapacity) {
		int newCapacity = (oldCapacity * 3) / 2 + 1;
		if (newCapacity < minCapacity) {
			newCapacity = minCapacity;
		}
		// minCapacity is usually close to size, so this is a win:

		changeSize(newCapacity);
	}

}

const char* String::getData() {
	return str;
}

int String::getLength() {
	return length;
}

int String::isEmpty() {
	return length == 0;
}

String& String::clear() {
	length = 0;
	str[length] = '\0';
	return *this;
}

String& String::operator=(const String& s) {
	if (this == &s)
		return *this; // Prevent delete of array, when this and s are the same instance.

	ensureCapacity(s.length); // Allocate content for the new String.
	copyContent(str, s.str, s.length); // Copy content from s.str excluding the terminal character.
	length = s.length;
	str[length] = '\0';
	return *this;
}

String& String::operator+=(const String& s) {
	int s_size = s.length; // Store s.size, to handle size changes when this and s are the same instance.
	int s_offset = length; // Store beginning of second string, before resize the own array.
	ensureCapacity(length + s_size); // Increase the own string array capacity, and preserve the content.
	copyContent(str + s_offset, s.str, s_size); // Copy content from s excluding the terminal character.
	length = s_offset + s_size;
	str[length] = '\0';
	return *this;
}

String& String::operator+=(char& s) {
	int s_size = 1; // Store s.size, to handle size changes when this and s are the same instance.
	int s_offset = length; // Store beginning of second string, before resize the own array.
	ensureCapacity(length + s_size); // Increase the own string array capacity, and preserve the content.
	copyContent(str + s_offset, &s, s_size); // Copy content from s excluding the terminal character.
	length = s_offset + s_size;
	str[length] = '\0';
	return *this;
}

char& String::operator[](int index) {
	return str[index];
}

/**
 * Compares the two Strings and return true, if they are equals.
 */
bool String::operator==(const String& s) {
	if (this->length != s.length) {
		return false;
	}

	return compareString(this->str, s.str);
}

bool String::operator==(const char*& s) {
	return (*this == String(s));
}

bool String::operator!=(const String& s) {
	return !(this->operator ==(s));
}

ostream& operator<<(ostream &out, String &s) {
	for (int i = 0; i < s.length; i++) {
		out << s.str[i];
	}
	return out;
}

