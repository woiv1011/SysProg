#include <string.h>
#include <math.h>
#include <stdio.h>
#include "geklautCustomizedcpp.h"
#include <fstream>

using namespace std;

//TODO änderungen ws 2014 -> heute einbauen

CodeGen::CodeGen() :
nrOfLabels(0),
maxNrOfLabels(10),
labels(new const char*[maxNrOfLabels])
{
}

CodeGen::~CodeGen()
{
	for (unsigned i = 0; i < nrOfLabels; ++i)
		delete[] labels[i];
	delete[] labels;
}

void CodeGen::makeCode(Node *node)
{
	ofstream fout; //TODO Buffer verwenden ???
	//fout.open("Ausgabe.code", "w"); //TODO


	if (node->type() == Prog) {
		makeCode(node->decls());
		makeCode(node->stmts());
		fout << "STP\n";
	}

	if (node->type() == Decls) {
		makeCode(node->decl());
		makeCode(node->nextDecl());
	}

	if (node->type() == DeclArray) {
		fout << "DS $" << node->symbol()->ident;
		makeCode(node->arr());
	}

	if (node->type() == DeclIdent) {
		fout << "DS $" << node->symbol()->ident << " 1\n";
	}

	if (node->type() == Array) {
		fout << " " << node->intValue() << "\n";
	}

	if (node->type() == Statements) {
		makeCode(node->stmt());
		makeCode(node->nextStmt());
	}

	if (node->type() == StatementIdent) {
		makeCode(node->exp());
		fout << "LA $" << node->symbol()->ident << "\n";
		makeCode(node->index());
		fout << "STR\n";
	}

	if (node->type() == StatementWrite) {
		makeCode(node->exp());
		fout << "PRI\n";
	}

	if (node->type() == StatementRead) {
		fout << "REA\n";
		fout << "LA $" << node->symbol()->ident;
		makeCode(node->index());
		fout << "\nSTR\n";
	}

	if (node->type() == StatementIf) {
		makeCode(node->exp());
		auto l1 = mkLabel();
		fout << "JIN #" << l1 << "\n";
		makeCode(node->ifStmt());
		auto l2 = mkLabel();
		fout << "JMP #" << l2 << "\n";
		fout << "#" << l1 << " NOP\n";
		makeCode(node->elseStmt());
		fout << "#" << l2 << " NOP\n";
	}
	if (node->type() == StatementWhile) {
		auto l1 = mkLabel();
		fout << "#" << l1 << " NOP\n";
		makeCode(node->exp());
		auto l2 = mkLabel();
		fout << "JIN #" << l2 << "\n";
		makeCode(node->stmt());
		fout << "JMP #" << l1 << "\n";
		fout << "#" << l2 << " NOP\n";
	}

	if (node->type() == StatementBlock) {
		makeCode(node->stmts());
	}

	if (node->type() == Exp) {
		auto ot = node->op()->type();
		if (ot == Type::NoType)
			makeCode(node->exp2());
		else {
			auto oet = node->op()->op()->token()->getTokenType();
			if (oet == Tokens::Greater) {
				makeCode(node->op());
				makeCode(node->exp2());
				fout << "LES\n";
			}
			else if (oet == Tokens::SmallerColonGreater) {
				makeCode(node->exp2());
				makeCode(node->op());
				fout << "NOT\n";
			}
			else {
				makeCode(node->exp2());
				makeCode(node->op());
			}
		}
	}


	if (node->type() == Exp2) {
		makeCode(node->exp());
	}

	if (node->type() == Exp2Ident) {
		fout << "LA $" << node->symbol()->ident << "\n";
		makeCode(node->index());
		fout << "LV\n";
	}

	if (node->type() == Exp2Int) {
		fout << "LC " << node->intValue() << "\n";
	}

	if (node->type() == Exp2Minus) {
		fout << "LC 0\n";
		makeCode(node->exp2());
		fout << "SUB\n";
	}

	if (node->type() == Exp2Neg) {
		makeCode(node->exp2());
		fout << "NOT\n";
	}

	if (node->type() == Index) {
		makeCode(node->exp());
		fout << "ADD\n";
	}

	if (node->type() == OpExp) {
		makeCode(node->exp());
		makeCode(node->op());
	}


	if (node->type() == Op) {
		switch (node->token()->getTokenType()) {
		case Tokens::Plus:
			fout << "ADD\n";
			break;

		case Tokens::Minus:
			fout << "SUB\n";
			break;

		case Tokens::Mul:
			fout << "MUL\n";
			break;

		case Tokens::Div:
			fout << "DIV\n";
			break;

		case Tokens::Smaller:
			fout << "LES\n";
			break;

		case Tokens::Greater:
			// see rule for Exp
			break;

		case Tokens::Equals:
			fout << "EQU\n";
			break;

		case Tokens::SmallerColonGreater:
			fout << "EQU\n"; // see rule for Exp
			break;

		case Tokens::And:
			fout << "AND\n";
			break;

		default:
			break;
		}
	}

	if (node->type() == Nil) {
		//nichts
	}
	
}


void CodeGen::resize()
{
	auto old = labels; //old = Pointer auf altes Labels-Array mit allen Label-Pointern
	labels = new const char*[maxNrOfLabels * 2]; //labels-Array-Pointer überschreiben mit doppelt so großem Speicherplatz
	for (unsigned i = 0; i < nrOfLabels; ++i) //alle Daten (Label-Pointer) in den neuen Speicherplatz rüberkopieren
		labels[i] = old[i];
	maxNrOfLabels *= 2; //verdoppeltes Maximum (s.o.)
	delete[] old; //alten Speicherplatz freigeben
}


/** 

*/
const char *CodeGen::mkLabel()
{
	if (nrOfLabels >= maxNrOfLabels) { //wenn anzahl der Labels Maximum erreicht hat, resize()
		resize();
	}

	auto nrOfDigits = nrOfLabels >= 1 //Digit-Anzahl muss groß genug sein um die Zahl des neuen Labels speichern zu können (Dezimalsystem)
		? ((int)log10(nrOfLabels) + 1)
		: 1;
	auto n = strlen("label") + nrOfDigits;
	auto buf = new char[n + 1]; //"buffer-Speicherplatz anlegen für "Label" + n digits als chars zu je 1 byte plus 1 für Stringende

	sprintf(buf, "label%u", nrOfLabels); //Labelname in buffer-Speicherplatz reinschreiben
	buf[n] = 0; //Stringende-Zeichen anhängen
	labels[nrOfLabels] = buf; //den Pointer für das neue Label in die Gesamtmenge(Array) der Label-Pointer einfügen
	++nrOfLabels; //anzahl der Labels plus 1
	return buf; //Pointer des neuen Labels zurückgeben
}
