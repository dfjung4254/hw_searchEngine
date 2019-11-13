#include "dictionary.h"

bool isAlpha(int c) { return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'; }

bool isDigit(int c) { return c >= '0' && c <= '9'; }

bool isBlank(int c) { return c == ' ' || c == '\t' || c == '\n'; }

/* 한글, 한문 등 */
bool isOtherCode(int c) {
  /* ascii 나 eof 는 아님 */
  return c < -1 || c > 127;
}

bool isLetter(int c) { return isAlpha(c) || isOtherCode(c); }

void skipBlanks(istream& in) {
  char c;
  while ((c = in.peek()) != EOF && isBlank(c)) {
    in.get();
  }
}

void capital2Lower(char* word) {
  /* TODO: word 내의 대문자를 모두 소문자로 바꿈 */
  string str_word(word);
  int size = str_word.size();
  for(int i = 0; i < size; i++){
    if(str_word[i] >= 'A' && str_word[i] <= 'Z'){
      str_word[i] += 32;
    }
  }
  strcpy(word, str_word.c_str());
}

void filepos2Str(istream& in, int pos, char* str) {
  /* pos 위치에서 문자열 읽음 */
  if (!(in.seekg(pos, ios::beg))) {
    throw "Seekg Failed";
  }
  in >> str;
}

bool nextWord(istream& in, char* word) {
  /* [a-zA-Z]+ 를 찾아 word 에 저장 */
  char c;
  while (!isLetter(c = in.peek())) {
    if (c == EOF) return false;
    in.get();
  }
  int wordlen = 0;
  while (isLetter(in.peek())) {
    word[wordlen++] = in.get();
    if (wordlen == MAXLEN) break;
  }
  word[wordlen] = '\0';
  return true;
}

bool isStopWord(char* word) {
  /* TODO: 필요시 구현 할 것 */
  return false;
}

bool nextNonStopWord(istream& in, char* word) {
  while (true) {
    if (!nextWord(in, word)) return false;
    if (!isStopWord(word)) return true;
  }
}

/* consult 에서 필요한 함수들 */
/* "ir.info" 에 저장된 3값 중 1개 반환 함수들 */
int numDocs() {
  ifstream iin("ir.info");
  int numdocs, numwords;
  float maxidf;
  if (!(iin >> numdocs >> numwords >> maxidf)) throw "ir.info does not exist";
  iin.close();
  return numdocs;
}

int numWords() { /* TODO: NumDocs 와 유사 */ }

double maxIDF() { /* TODO: NumDocs 와 유사 */ }

bool binarySearchDictionary(ifstream& din, char* word, Dict_Term& tm) {
  /* TODO: 사전인 ir.dictionary 의 이진탐색 */
  /* word에 해당되는 Dict_Term을 찾는다. */
}