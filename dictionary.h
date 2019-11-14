/*

  2019 정보검색 과제
  
  학번 : B354025
  이름 : 정근화

*/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cstring>
#include <fstream>
#include <iostream>
#define MAXLEN 256

using namespace std;

template <class T>
void changeSize1D(T*& a, const int oldSize, const int newSize) {
  /* 배열크기 변경 프로그램 : DS교재 참조 */
  if (newSize < 0) throw "뭐야 이거!";
  T* temp = new T[newSize];
  int number = min(oldSize, newSize);
  copy(a, a + number, temp);
  delete[] a;
  a = temp;
}

/* 어느 문서에 몇 차례 */
struct Posting {
  int docpos;  // ir.docnames 내의 문서위치
  int freq;    // 해당단어의 문서내 빈도
  Posting(int dp = -1, int fr = 0) : docpos(dp), freq(fr) {}
};

/* 사전내의 entry */
struct Dict_Term {
  int wordpos;    // ir.words 내의 위치
  int poststart;  // 1번째 post위치 in ir.postings
  int numposts;   // 관련 posting의 수
  double idf;     // idf of this word
};

bool isAlpha(int c);
bool isDigit(int c);
bool isBlank(int c);
bool isOtherCode(int c);  // not ascii, not EOF
bool isLetter(int c);

void skipBlanks(istream& in);
void capital2Lower(char* word);
void filepos2Str(istream& in, int pos, char* str);

bool nextWord(istream& in, char* word);
bool isStopWord(char* word);
bool nextNonStopWord(istream& in, char* word);

bool binarySearchDictionary(ifstream& din, char* word, Dict_Term& tm);
int numDocs();
int numWords();
double maxIDF();  // max IDF in the collection

#endif