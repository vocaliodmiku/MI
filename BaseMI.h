/*
 * File: BaseMI.h.
 * Last modified at 19:47 on 4 January 2014 by WuBin.
 *
 * This abstract class initializes its language model and dictionary structure, preparing to compute MI.
 * It only deals with issues about the lm and the dict, the implementation of the core algorithm - 
 * computing the sum of all the paths in WHG (word hyopthesis graph) will depend on its subclasses. 
 * 
 * The format of the pinyinToWords dictionary:
 * a#si#pi#lin 阿斯匹林 阿司匹林
 *
 */

#ifndef _basemi_h
#define _basemi_h

#define LN2 .69314718055994530941723212145818

#include "LM.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
using namespace std;

/* Hash from a pinyin to its words. */
typedef map<string, vector<string> > Dict;

class BaseMI {
public:
	BaseMI(int order, string ARPAFile, string pinyinToWordsDict);
	virtual Prob probSum(const string &pinyinSeq) const = 0;

	const Dict &getDict() const {return dict;}
	void setDict(const Dict &newDict) {dict = newDict;};
	bool getDictEntry(const string &pinyin, vector<string> &words) const;

	/* For Linux. */
	/* When getline() from the windows file in linux, a dummy '\r' should be discarded. */
	static inline void chomp(string &line) {
		if (line.size() != 0 && line[line.size() - 1] == '\r') line = line.substr(0, line.size() - 1);
	}

	/* Push the tokens from a segmented sequence to a specified vector. */
	inline static void segmentedStringToVector(const string &seq, vector<string> &vec) {
		stringstream converter(seq);
		copy(istream_iterator<string>(converter), istream_iterator<string>(), back_inserter(vec));
	}

	inline static string removeBoundaries(string pinyin) {
		replace(pinyin.begin(), pinyin.end(), '#', ' ');
		return pinyin;
	}

	/* For Linux. A more user-friendly version than chmop().*/
	inline static string &GetLine(ifstream &in, string &line) {
	  getline(in, line);
	  if (!line.empty() && line.at(line.length() - 1) == '\r') line.erase(line.end() - 1);
	  return line; 
	}

	inline static double log2(double value) {
		 return log(value) / LN2;
	}

protected:
	/* For language modeling. */
	/* The order of the a language model. */
	const int ORDER;
	/* A language model to get probabilities of grams. */
	const LM lm;

private:
	/* For the dictionary. */
	/* The dictionary map stores lines of the pinyin to its words. */
	Dict dict;
    void initDict(const string &dictFile);
    void addDictEntry(const string &line);
};

#endif