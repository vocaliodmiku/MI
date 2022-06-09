/*
 * File: MIDemo.cpp.
 * Implemented at 23:07 on 20 March 2016 by WuBin.
 * Basic facilities to mutual information of text and phonological units
 *
 */

#include "MI.h"
using namespace std;

void printWHG(const MI &mi, const string &pinyinSeq) {
  WHG whg;
  mi.buildWHG(pinyinSeq, whg);
  cout << "------------------------------------------------------" << endl;
  cout << "The Word Hypothesis Graph (WHG) of '"<< pinyinSeq << "' is: " << endl;
  mi.printWHG(whg);
}

int main() {
  MI mi(2, "TVTri.lm", "HomoDictPoly+Tone.txt", false);
  printWHG(mi, "bu3 ru3 dong4 wu4");

  cout << "------------------------------------------------------" << endl;
  cout << "The sum of probability WHG (unbounded) of \"bu3 ru3 dong4 wu4\" is " << mi.probSum("bu3 ru3 dong4 wu4") << endl;

  vector<WHGNode> whgPath;
  cout << "The max of probability WHG (unbounded) of \"bu3 ru3 dong4 wu4\" is " << mi.probMax("bu3 ru3 dong4 wu4", whgPath) << endl;
  cout << "The whg Path of \"bu3 ru3 dong4 wu4\" is: " << endl;
  for (vector<WHGNode>::iterator itr = whgPath.begin(); itr != whgPath.end(); ++itr) cout << itr->word << "\t";
  cout << endl;

  whgPath.clear();
  cout << "The max of probability WHG (unbounded) of \"zhong1 guo2 ren2 min2 sheng1 huo2\" is " << mi.probMax("zhong1 guo2 ren2 min2 sheng1 huo2", whgPath) << endl;
  cout << "The whg Path of \"zhong1 guo2 ren2 min2 sheng1 huo2\" is: " << endl;
  for (vector<WHGNode>::iterator itr = whgPath.begin(); itr != whgPath.end(); ++itr) cout << itr->word << "\t";
  cout << endl;

  cout << "------------------------------------------------------" << endl;
  cout << "The unbouned version will remove the boundaries automatically." << endl;
  MI bmi(3, "TVTri.lm", "HomoDictPoly+Tone.txt", true);
  cout << "The sum of probability WHG (unbounded) of \"bu3#ru3 dong4#wu4\" is " << mi.probSum("bu3#ru3 dong4#wu4") << endl;
  cout << "The sum of probability WHG (bounded) of \"bu3#ru3 dong4#wu4\" is " << bmi.probSum("bu3#ru3 dong4#wu4") << endl;

  cout << "------------------------------------------------------" << endl;
  cout << "For prosodic boundary, the version of MI must be bounded." << endl;
  
  cout << "The sum of probability WHG (unbounded) of \"zhong1 guo2 ren2 min2 sheng1 huo2\" is " << mi.probSum("zhong1 guo2 ren2 min2 sheng1 huo2") << endl << endl;
 
  cout << "The insertion of prosodic boundaries at the beginning or end of pinyin sequence doesn't work." << endl;
  cout << "The sum of probability WHG of \"| zhong guo ren min sheng huo |\" is " << mi.probSum("| zhong1 guo2 ren2 min2 sheng1 huo2 |") << endl << endl;
  cout << "The sum of probability WHG of \" | | zhong guo ren min | sheng huo | \" is " << mi.probSum("| | zhong1 guo2 ren2 min2 | sheng1 huo2 |") << endl << endl;
}
