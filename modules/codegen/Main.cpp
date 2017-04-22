//"MASCHINENBEFEHLE"
//#include <string>
#include <fstream>
using namespace std;

//(optional) LAbel
//CMD
//(optional) argument

int codePointer = 0;


/*
(siehe S. 70)
Befehle:

Integer-Arithmetik

ADD: codeP++; *(stackP-1) = *(stackP-1) + *stackP; stackP--;
SUB: codeP++; *(stackP-1) = *(stackP-1) - *stackP; stackP--;
MUL: codeP++; *(stackP-1) = *(stackP-1) * *stackP; stackP--;
DIV: codeP++; *(stackP-1) = *(stackP-1) / *stackP; stackP--;


*(stackP) = zuletzt gespeicherte Var.
*(stackP-1) = davor gespeicherte Variable

-> zwei zahlen in stack speichern; erste (zuerst gespeicherte) *+-/ rechnen; stackpointer reduzieren

Vergleiche ohne Argument
•Kleiner für Integer – LES codeP++; if (*(stackP-1) < *stackP) *(stackP-1) = 1; else *(stackP-1) = 0; stackP--;
•Gleich für Integer – EQU codeP++; if (*(stackP-1) == *stackP) *(stackP-1) = 1; else *(stackP-1) = 0; stackP--;

Logische Operationen ohne Argument
•Konjunktion für Integer – AND codeP++; if (*(stackP-1) != 0 && *stackP != 0) *(stackP-1) = 1; else *(stackP-1) = 0; stackP--;
•Negation für Integer – NOT codeP++; if (*(stackP) == 0 ) *stackP = 1; else *stackP = 0;

Laden, Speichern
•Laden einer Speicheradresse (mit Argument) – LA variable
codeP += 2; stackP++; *stackP =addr(varianble);
•Laden einer Konstante (int) (mit Argument) – LC c
codeP += 2; stackP++; *stackP = c;
•Laden eines gespeicherten Werts (ohne Argument) – LV
codeP++; *stackP = **stackP;
•Speichern eines Werts (ohne Argument) – STR codeP++; **stackP = *(stackP-1); stackP -=2;

Einlesen und Drucken ohne Argument
•Drucken eines Integers – PRI codeP ++; println(*stackP); stackP--;
•Einlesen eines Integers – REA codeP ++; stackP++; *stackP = read();

Sprünge mit Argument
•Unbedingter Sprung – JMP #label
codeP = *label // springt an die mit // *label markierte Codezeile
•Bedingter Sprung – JIN #label
if(*stackP == 0) codeP = *label; else codeP +=2; stackP--;

Speicher reservieren mit Argument – DS identifier size
codeP+=3;
addr(identifier) = addrP;
addrP += size;

•Was noch fehlt
•Nichts tun (ohne Argument) – NOP codeP++;
•Stoppen (ohne Argument) – STP
exit();

*/
enum types {
	PROG,
	DECLS,
	STATEMENTS,
	ARRAY,
};

class Operation {
	string label;
	string command;
	string argument;
	string delimiter; //????

};

void mainCodeGen() {
	//1.    .code-Datei erzeugen
	//parseTree um makeCode erweitern
}
void makeCode(string input) {
	ofstream fout;
	//fout.open("Ausgabe.code", "w"); //TODO
	if (input == "PROG") {
		makeCode("DECLS");
		makeCode("STATEMENTS");
		fout << "STP\n";
	}

	if (input == "DECLS") { //DECLS::= epsilon ? S.74
		makeCode("DECL");
		makeCode("DECLS");
	}

	if (input == "DECL") {

	}

	if (input == "ARRAY") {

	}

	if (input == "STATEMENTS") {

	}

	if (input == "STATEMENT") {

	}
	 
}