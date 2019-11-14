#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "dictionary.h"

using namespace std;

int main() {
  ofstream irwords;
  ofstream irpostings;
  ofstream irdictionary;
  ofstream irinfo;
  ifstream irinforead;

  irwords.open("ir.words", ios::out | ios::trunc);
  irwords.close();
  irpostings.open("ir.postings", ios::out | ios::trunc | ios::binary);
  irpostings.close();
  irdictionary.open("ir.dictionary", ios::out | ios::trunc | ios::binary);
  irdictionary.close();

  string w_buff;
  vector<Dict_Term> vDictionary;

  irinforead.open("ir.info");
  string tp;
  irinforead >> tp;
  irinforead.close();
  int docCntAll = stoi(tp);
  cerr << "docCntAll : " << docCntAll << '\n';
  int lineCnt = 0;
  int inLineCnt = 0;
  double maxIdf = -1;

  int docCnt = 0;
  int freq = 0;

  while ((cin >> w_buff)) {
    lineCnt++;
    Dict_Term cur_DictTerm;

    /* FIXME: DIC_TERMS */
    irwords.open("ir.words", ios::out | ios::app | ios::ate);
    cur_DictTerm.wordpos = irwords.tellp();

    irwords << w_buff << " ";
    if (++inLineCnt == 5) {
      irwords << '\n';
      inLineCnt = 0;
    }
    irwords.close();

    cin >> docCnt >> freq;

    /* FIXME: DIC_TERMS */
    /* 아직 idf 는 전체 문서의 수가 구해지지 않았다. 나중에 전체 문서의 수가
     * 구해지면 나눠주고 log 취해야 함 */
    irpostings.open("ir.postings", ios::out | ios::app | ios::ate | ios::binary);
    cur_DictTerm.poststart = irpostings.tellp();
    cur_DictTerm.numposts = docCnt;
    cur_DictTerm.idf = log2((double)docCntAll / (double)docCnt);
    if(maxIdf < cur_DictTerm.idf){
      maxIdf = cur_DictTerm.idf;
    }

    vector<Posting> postings;

    while (docCnt--) {
      int docPos = 0;
      int docFreq = 0;
      cin >> docPos >> docFreq;
      Posting newPost(docPos, docFreq);
      postings.push_back(newPost);
    }

    irpostings.write(reinterpret_cast<const char*>(&postings[0]),
                     postings.size() * sizeof(Posting));
    irpostings.close();

    vDictionary.push_back(cur_DictTerm);
  }

  /* write ir.info */
  irinfo.open("ir.info", ios::out | ios::app | ios::ate);
  irinfo << lineCnt << " ";
  irinfo << maxIdf;
  irinfo.close();

  /* write ir.dictionary */
  irdictionary.open("ir.dictionary", ios::out | ios::app | ios::ate | ios::binary);
  irdictionary.write(reinterpret_cast<const char*>(&vDictionary[0]),
                     vDictionary.size() * sizeof(Dict_Term));
  irdictionary.close();
  
}