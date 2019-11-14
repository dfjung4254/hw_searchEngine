/*

  2019 정보검색 과제
  
  학번 : B354025
  이름 : 정근화

*/

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
  ifstream irdocnames;
  ifstream irinfo;
  for (int i = 0; i < count; i++) {
    Dict_Term current = vDictionary[i];

    /* find word */
    irword.open("ir.words");
    irword.seekg(current.wordpos);
    string dic_word;
    irword >> dic_word;
    // cout << "cur word pos : " << current.wordpos << " / " << dic_word <<
    // '\n';
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
    for (int j = 0; j < current.numposts; j++) {
      Posting curPosting = vPostings[j];
      dic_allCnt += curPosting.freq;
    }

    /* print word informations */
    cout << dic_word << " appeared " << dic_allCnt << " time(s) in "
         << dic_docCnt << " document(s) [ idf = " << dic_idf << " ]" << '\n';

    irdocnames.open("ir.docnames");
    for (int j = 0; j < current.numposts; j++) {
      string docName;
      irdocnames.seekg(vPostings[j].docpos);
      irdocnames >> docName;
      cout << "   " << docName << " " << vPostings[j].freq;
    }
    cout << '\n';
    irdocnames.close();
  }
  /* print collection summary */
  irinfo.open("ir.info");
  string docs;
  string words;
  string maxIdf;
  irinfo >> docs >> words >> maxIdf;

  cout << '\n';
  cout << "<Collection Summary>" << '\n';
  cout << "#Docs = " << docs << "  ";
  cout << "#Words = " << words << "  ";
  cout << "#Max.IDF = " << maxIdf << '\n';
}