/* File: BaseMI.cpp.
 * Last modified at 19:47 on 4 January 2014 by WuBin.
 *
 * The implementation of the BaseMI class.
 * 
 * This abstract class initializes its language model and dictionary structure, preparing to compute MI.
 * It only deals with issues about the lm and the dict, the implementation of the core algorithm - 
 * computing the sum of all the paths in WHG (word hyopthesis graph) will depend on its subclasses. 
 */

#include "BaseMI.h"

/* -----------------------------------------Initialize--------Maps---------------------------------------------------- */
/* The constructor. */
BaseMI::BaseMI(int order, string ARPAFile, string pinyinToWordsDict) : ORDER(order), lm(order, ARPAFile) {
	initDict(pinyinToWordsDict);
}

/* Parse one entry and insert it to the internal dict map. */
void BaseMI::addDictEntry(const string &line) {
	string pinyin;
	vector<string> words;

	/* Parse the line. */
	stringstream converter;
	converter << line;
	converter >> pinyin;
	copy(istream_iterator<string>(converter), istream_iterator<string>(), back_inserter(words));

	/* Insert the entry to the dict map. */
	dict.insert(make_pair(pinyin, words));
}

/* Read entries from the dictionary file and insert them to the internal dict map. */
void BaseMI::initDict(const string &dictFile) {
	ifstream in(dictFile.c_str());
	if(in.fail()) cerr << "Error: BaseMI::initDict: Opening the dict file failed." << endl;

	string line;
	while (true) {
		getline(in, line); chomp(line);
		if (line.empty() || in.fail()) break;
		addDictEntry(line);
	}
    cerr << "MI::initDict done!" << endl;
}

/* -----------------------------------------Getter------------------------------------------------------------- */
/* Given the pinyin, get the corresponding words from the dictionary. 
 * return true if the entry found, otherwise return false.
 * If the pinyin is not found, words will be empty .
 */
bool BaseMI::getDictEntry(const string &pinyin, vector<string> &words) const {
	words.clear();
	
	Dict::const_iterator dictItr = dict.find(pinyin);
	if (dictItr  == dict.end()) return false;
	copy(dictItr->second.begin(), dictItr->second.end(), back_inserter(words));
	return true;
}
