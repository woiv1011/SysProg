#include <stddef.h>
#include <fstream>
#include <iostream>

#include "../../Buffer/includes/Buffer.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../includes/Scanner.h"
#include "../includes/Token.h"
#include "../includes/TokenType.h"

using namespace std;

int main(int argc, const char* argv[]) {
	if (argc < 3) {
		cerr << "Invalid options! Use: " << argv[0] << " input.txt output.txt [error.txt]" << endl;
		return -1;
	}

	const char* inputfilename = argv[1];
	const char* outputfilename = argv[2];
	const char* errorfilename = argc > 3 ? argv[3] : "";

	Scanner* scanner = new Scanner(inputfilename);
	Symboltable* symboltable = scanner->getSymboltable();

	if (!scanner->getBuffer()->isValid()) {
		cerr << "Failed to open the inputfile: " << inputfilename << endl;
		return -1;
	}

	ofstream outputfile;
	outputfile.open(outputfilename);
	if (!outputfile.is_open()) {
		cerr << "Failed to open the outputfile: " << outputfilename << endl;
		return -1;
	}

	ostream * errstream = &cerr;
	ofstream errorfile;
	if (argc > 3) {
		errorfile.open(errorfilename);
		if (!errorfile.is_open()) {
			cerr << "Failed to open the errorfile: " << errorfilename << endl;
			return -1;
		}
		errstream = &errorfile;
	}

	cout << "processing ..." << endl;

	Token * token;
	token = scanner->nextToken();
	while (token != NULL) {

		switch (token->getType()) {
		case TokenType::Undefined:
			*errstream << token << endl;
			break;
		case TokenType::Ignored:
			break;
		case TokenType::IntegerError:
			*errstream << token << endl;
			break;
		default:
			outputfile << token << endl;
			break;
		}

		delete token;
		token = scanner->nextToken();
	}

	if (outputfile.is_open()) {
		outputfile.close();
	}

	if (errorfile.is_open()) {
		errorfile.close();
	}

	cout << "completed ..." << endl;

	delete scanner;
}
