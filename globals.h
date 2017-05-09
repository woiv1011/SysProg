
//STATES for tokenizer->getNextToken() state machine
#define ST_NONE        0
#define ST_START       1
#define ST_INTEGER     2
#define ST_IDENTIFIER  3
#define ST_STRING  4
#define ST_SIGN 5

/*Nochmals zur Aufgabe: Der Scanner liest nach der Aufforderung nextToken() solange mittels
getChar() das nächste Zeichen, bis er ein Zeichen oder einen Bezeichner erkannt hat. Ist
dieses ein Bezeichner, wird über die Symboltabelle mittels (insert) eine eindeutige Referenz
(inofKey) auf das eigentliche Informationsobjekt angefordert. Falls der Bezeichner neu war,
wird dieses erzeugt und mit dem Bezeichner verknüpft; ansonsten lediglich dessen Referenz
zurückgeliefert.*/

//TODO kategorien und einzelwerte mergen ?
#define NOTHING 0x0

//tokentype Kategorien, jeweils 1 Bit gesetzt
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


typedef tokennode_t struct {
  long         index;
  tokennode_t *next;
  tokennode_t *previous;
  token_t      content;
}

typedef tokentype_t short;

typedef token_t struct {
  tokentype_t  type; //16 bit; oberes/linkes byte für Kategorie, unteres/rechtes byte für Wert innerhalb Kategorie
  short        length; //aus wievielen chars besteht das token, fängt bei 1 an, kein "Stringende-Zeichen" notwendig, max 65536 tokenLength //TODO warnung und fehler ausgeben wenn tokenlength > MAX (beim lesen in getNextToken)
  char        *value; //string bei identifier / int
}

/*typedef bool unsigned char;
#define true 1
#define false 0*/