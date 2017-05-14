
//STATES for tokenizer->getNextToken() state machine
//#define ST_NONE        0
//#define ST_START       1
//#define ST_INTEGER     2
//#define ST_IDENTIFIER  3
//#define ST_STRING  4
//#define ST_SIGN 5

/*Nochmals zur Aufgabe: Der Scanner liest nach der Aufforderung nextToken() solange mittels
getChar() das nächste Zeichen, bis er ein Zeichen oder einen Bezeichner erkannt hat. Ist
dieses ein Bezeichner, wird über die Symboltabelle mittels (insert) eine eindeutige Referenz
(inofKey) auf das eigentliche Informationsobjekt angefordert. Falls der Bezeichner neu war,
wird dieses erzeugt und mit dem Bezeichner verknüpft; ansonsten lediglich dessen Referenz
zurückgeliefert.*/

//TODO kategorien und einzelwerte mergen ?
#define ERROR 0xFFFF //max value of unsigned short int, bzw -1 bei signed
#define TOKENMAXLENGTH 0xFFFF

//tokentype Kategorien, jeweils 1 Bit gesetzt
//prefix hinzufügen ?
#define ERROR 0xFFFF
#define INTEGER    0x100
#define IDENTIFIER 0x200
//#define KEYWORD    0x400
//#define SIGN       0x800

//KEYWORD Werte
//TODO unterschiedliche Werte verwenden  als Sign ?
#define KW_WRITE    0x1   // write Keyword
#define KW_READ     0x2   // read
#define KW_INT      0x3   // int
#define KW_IF       0x4   // if/IF
#define KW_ELSE     0x5   // else/ELSE
#define KW_WHILE    0x6   // while/WHILE
#define KW_INT      0x7   // int

//SIGN Werte
#define S_ADD         0x8   // + Sign Add
#define S_SUB         0x9   // -
#define S_MUL         0xA   // *
#define S_DIV         0xB   // :
#define S_EQ          0xC   // =   equals
#define S_DIV_EQ      0xD   // :=
#define S_EQ_DIV_EQ   0xE   // =:=
#define S_NOT         0xF   // !
#define S_AND         0x10  // &&
#define S_SEMICOLON   0x11  // ;
//TODO rename SEMICOLON to SEMI ?

//Brackets B_*
//TODO einzelnen bits Bedeutungen zuweisen ? opening vs closing oder so
#define B_SQUARE_O  0x12    // [ Square brackets; opening
#define B_SQUARE_C  0x13    // ] Square brackets; closing
#define B_CURLY_O   0x14    // { curly brackets; opening
#define B_CURLY_C   0x15    // } curly brackets; closing
#define B_ROUND_O   0x16    // ( round brackets; opening
#define B_ROUND_C   0x17    // ) round brackets; closing
#define B_ANGLE_O   0x18    // < angle brackets; opening
#define B_ANGLE_C   0x19    // < angle brackets; closing
//TODO angle brackets <> stattdessen als compare größer kleineR ?



/*typedef bool unsigned char;
#define true 1
#define false 0*/



void tokenize() {
  long position = 0;
  token_t temp;
  while(!EOF) {
    temp = getNextToken()
    appendTokenToList(temp)
    //position = position + temp.length;
  }
}


void appendTokenToList(token_t tok) {

}