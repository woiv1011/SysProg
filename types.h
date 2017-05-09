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