#include <fstream>
#include <iostream>
#include <vector>
#include "dictionary.h"

using namespace std;

int main() {
  ifstream irdictionary;
  irdictionary.open("ir.dictionary", ios::binary);

  irdictionary.seekg(0, ios::end);
  int filesize = irdictionary.tellg();
  irdictionary.seekg(0);
  const size_t count = filesize / sizeof(Dict_Term);
  vector<Dict_Term> vDictionary(count);
  irdictionary.read(reinterpret_cast<char*>(&vDictionary[0]),
                    count * sizeof(Dict_Term));
  irdictionary.close();

  ifstream irword;
  ifstream irpostings;
  for (int i = 0; i < count; i++) {
    Dict_Term current = vDictionary[i];

    /* find word */
    irword.open("ir.word");
    irword.seekg(current.wordpos);
    string dic_word;
    irword >> dic_word;
    irword.close();

    /* find Postings */
    irpostings.open("ir.postings", ios::binary);
    irpostings.seekg(0, ios::end);
    int filesize = irpostings.tellg();
    irpostings.seekg(current.poststart);
    vector<Posting> vPostings(current.numposts);
    irpostings.read(reinterpret_cast<char*>(&vPostings[0]),
                    current.numposts * sizeof(Posting));
    irpostings.close();

    int dic_docCnt = current.numposts;
    double dic_idf = current.idf;
    int dic_allCnt = 0;
    for(int j = 0; j < current.numposts; j++){
      Posting curPosting = vPostings[j];
      dic_allCnt += curPosting.freq;
    }

    cout << dic_word << " appeared " << dic_allCnt << " time(s) in " << dic_docCnt << " document(s) [ idf = " << dic_idf << " ]" << '\n';
    for(int j = 0; j < current.numposts; j++){
      cout << "  " << 
    }

  }
}