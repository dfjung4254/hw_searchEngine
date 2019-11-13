#include <fstream>
#include <iostream>
#include "dictionary.h"

using namespace std;

struct Line {
  /* variables */
  string word;
  int totalfreq;
  int numposts;  // how many terms stored
  int capacity;  // max no. terms storable
  Posting *pArray;

  /* constructor */
  Line() : capacity(8), numposts(0) { pArray = new Posting[capacity]; }

  /* functions */
  void print() {
    totalfreq = 0;
    for (int i = 0; i < numposts; i++) totalfreq += pArray[i].freq;
    cout << word << " " << numposts << " " << totalfreq << " ";
    for (int i = 0; i < numposts; i++)
      cout << " " << pArray[i].docpos << " " << pArray[i].freq;
    cout << '\n';
  }

  void newWord(string wd) {
    word = wd;
    numposts = 0;
  }

  void newPosting(Posting pst) {
    if (numposts == capacity) {
      /* double mem */
      changeSize1D(pArray, capacity, 2 * capacity);
      capacity *= 2;
    }
    pArray[numposts++] = pst;
  }
};

int main() {
  Line line;
  Posting pst;
  string word;
  int docpos;

  if (!(cin >> word >> pst.docpos)) {
    cerr << "Empty input" << '\n';
    return 1;
  }
  
  line.newWord(word);
  pst.freq = 1;

  while (cin >> word >> docpos) {
    if (word != line.word) {
      line.newPosting(pst);
      line.print();

      /* start new line with new word */
      line.newWord(word);

      /* insert new posting */
      pst.docpos = docpos;
      pst.freq = 1;

    } else if (docpos != pst.docpos) {
      line.newPosting(pst);
      /* start new posting */
      pst.docpos = docpos;
      pst.freq = 1;
    } else {
      pst.freq++;
    }
  }

  line.newPosting(pst);
  line.print();
}