#include "../includes/Buffer.h"

void printWithPrevious(Buffer* buf) {
	for (unsigned int i = 0; i <= buf->getLength(); i++) {
		cout << buf->previous();
	}
}

int main(int argc, char **argv) {
	/*Buffer*  buffer;
	 buffer = new Buffer("/home/ivar/workspace/data.txt");

	 buffer->readBlockFromFile();
	 buffer->printMemory();*/

	Buffer peter("/home/ivar/workspace/data.txt");

}

