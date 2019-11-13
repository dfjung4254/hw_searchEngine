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

  irwords.open("ir.words", ios::out | ios::app | ios::trunc);
  irpostings.open("ir.postings",
                  ios::out | ios::app | ios::trunc | ios::binary);
  irdictionary.open("ir.dictionary",
                    ios::out | ios::app | ios::trunc | ios::binary);
  irinfo.open("ir.info", ios::out | ios::ate | ios::app);

  string w_buff;
  vector<Dict_Term> vDictionary;

  int lineCnt = 0;
  int inLineCnt = 0;

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
    cur_DictTerm.idf = (double)docCnt;

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

  /* set idf and get maxIdf */
  double maxIdf = -1;
  for (int i = 0; i < lineCnt; i++) {
    vDictionary[i].idf = log10(lineCnt / vDictionary[i].idf);
    if (maxIdf < vDictionary[i].idf) {
      maxIdf = vDictionary[i].idf;
    }
  }

  /* write ir.info */
  irinfo.open("ir.info", ios::out | ios::app | ios::ate);
  irinfo << " " << lineCnt << " ";
  irinfo << maxIdf;
  irinfo.close();

  /* write ir.dictionary */
  irdictionary.open("ir.dictionary", ios::out | ios::app | ios::ate | ios::binary);
  irdictionary.write(reinterpret_cast<const char*>(&vDictionary[0]),
                     vDictionary.size() * sizeof(Dict_Term));
  irdictionary.close();
  
}