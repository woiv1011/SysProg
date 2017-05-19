//Helper methoden zum testen, umwandeln etc ??
//Codegenerator konstruktor wird aufgerufen mit filename der output datei als parameter (xxx.code)
//parseTree klasse um die Operation makeCode erweitern

char* getLabel() {
  char result[512];
  result = "Identifier mit führendem '#'"; //TODO
  return result;
}

char* getCommand() {
  //zwingend
  //schlüsselwort
  char result[512];
  //ggf umwandeln in einzelnen integer wert der in switch case verwendet werden kann
  switch(einzelnerWert) {
    case 0:   result = "DS";
              break;
    case 1:   result = "LC";
              break;
    case 2:   result = "ADD";
              break;
    case 3:   result = "LA";
              break;
    case 4:   result = "STR";
              break;  
    case 5:   result = "LV";
              break; 
    case 6:   result = "SUB";
              break;
    case 7:   result = "PRI";
              break;
    case 8:   result = "NOP";
              break;
    case 9:   result = "STP";
              break;
    case 10:  result = "MUL";
              break;
    case 11:  result = "DIV";
              break;                                                                                            
  }
  return result;
}

char* getArgs() {
  char result[512];
  //optional: Integer, Variable(Identifier mit führendem '$''), Label (Identifier mit führendem '#')
}

void makeCode(ASTNode node) { //parameter ?
//TODO Ausnahme: Kommando zur Speicherreservierung
  cout << getLabel(); //optional
  cout << getCommand();
  cout << getArgs(); //optional
  cout << endl;
}