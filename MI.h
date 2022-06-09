/* 
 * File: MI.h.
 * Draft: last modified at 11:00 on 10 January 2014 by WuBin.
 * Last modified at 10:15 on 15 January 2014 by WuBin.
 * Last modified at XXXXX on 18 March 2014 by WuBin - Some modifications helps to deal with the variation of the tone.
 * Last modified at 1:34 on 6 June 2014 by WuBin - Add the Support of the prosodic boundary. && + printWHG()
 *
 * The probSum for MI and the probMax for MLE are the extensions of the normal MI who only needs the bounded proSum.
 * They are implemented in the same class for they are sharing the same WHG structrue.
 *
 * The PinyinToWordsDict:
 *	i.e. an#shi 按时 暗示
 *	     an#shu 谙熟
 *
 * The pinyin format: 
 * i.e. "bei#jing yu#yan da#xue "(For Linux) or "bei#jing yu#yan da#xue"(For windows getline).
 */

#ifndef _mi_h
#define _mi_h

#include "BaseMI.h"
#include <numeric>
#include <set>

/* A WHG node need not the begin position of the word, 
 * which is indicated in the WHG structure. */
struct WHGNode {
	/* The basic WHG node structure. */
	/* The word of WHG node with its begin position. */
	int beginPos;
	string word;

	/* For computing the MI. */
	/* Store the summation of probabilities of pathes ended with 
	 * the word within this WHG node for the bigram model. 
	 */
	Prob biPrSum;
	/* Store the summation of probabilities of pathes ended with the word pair 
	 * whose second entry is the word of this WHG node for the trigram model. 
	 */
	vector<Prob> triPrSum;

	/* For computing the MLE word path of a pinyin sequence. */
	/* Store the maximum of probabilities of pathes ended with 
	 * the word within this WHG node for the bigram model. 
	 * Note: The probabilities are log10 based as in the ARPAfile to add some efficiency.
	 */
	Log10Prob biPrMax;
	/* Store the index of the previous node of this WHG node 
	 * for reconstructing the WHG path with the maximum probability. 
	 */
	int biPreNode;
    /* Store the maximum of probabilities of pathes ended with 
     * the word within this WHG node for the trigram model. 
     * Note: The probabilities are log10 based as in the ARPAfile to add some efficiency.
     */
	vector<Log10Prob> triPrMax;
	/* Store the the index of the first node of the previous node pair 
	 * for the current WHG node pair whose second entry is this node,
	 * which helps reconstructing the WHG path with the maximum probability. 
	 */
	vector<int> triPreNode;

	/* The constructor. */
	WHGNode(int beginPos, string word, Prob biPrSum = .0, vector<Prob> triPrSum = vector<Prob>(), 
		Log10Prob biPrMax = .0, int biPreNode = -1, vector<Log10Prob> triPrMax = vector<Log10Prob>(), vector<int> triPreNode = vector<int>()) : 
	beginPos(beginPos), word(word), biPrSum(biPrSum), triPrSum(triPrSum), biPrMax(biPrMax), biPreNode(biPreNode), triPrMax(triPrMax), triPreNode(triPreNode) {
	}
};

/* The WHG structure classifies WHG nodes according to their end positions,  
 * and the i-th item of which is a vector of WHG nodes whose word is ended at the i-th position.
 */
typedef vector<vector<WHGNode> > WHG;

class MI : public BaseMI {
public:
	MI(int order, string ARPAFile, string pinyinToWordsDict, bool bounded = true);
	bool buildWHG(const string &pinyinSeq, WHG &whg) const;
	virtual Prob probSum(const string &pinyinSeq) const;
	Prob probMax(const string &pinyinSeq, vector<WHGNode> &whgPath) const;
	const LM &getLM() const{ return lm;}
	void printWHG(const WHG &whg) const;

protected:
	/* For the bounded MI.
	 * The function helps building the WHG structure for the bounded pinyin sequence. 
	 * The end position vector helps extract the information of boundaries of the bounded pinyin sequence.
	 * and the start position vector helps in constructing WHG nodes.
	 * i.e. The pinyin sequence:        bei#jing yu#yan da#xue. 
	 *      The begin position vector:  0        2      4 
	 *      The end   position vector:      1       3      5
	 */
	void getPosVec(const vector<string> &pinyinSeq, vector<int> &beginPosV, vector<int> &endPosV) const;
	/* For the unbounded MI.
	 * This functions collects the words whose pinyins have the same end position 
	 * and help constructing WHG for the unbounded pinyin sequence.
	 * i.e. The pinyin sequence: suo you de xiong dou shi bu ru dong wu 
	 *      endPositions: 9   寤 五...务 屋 动物 动武 哺乳动物
	 */
	vector<WHGNode> &getWHGNodesWithSameEndPos(const vector<string> &pinyinSeq, const int &endPos, vector<WHGNode> &v, int &minVacantPos, bool &WHGExists, const set<int> &prosodicBoundaryPos) const;

private:
	bool BOUNDED;
	/* Dynamic programming for a bigram model or a trigram model 
	 * will share the same WHG structure regardless of the boundness. 
	 */
	bool buildBoundedWHG(const vector<string> &pinyinSeq, WHG &whg) const;
	bool buildUnboundedWHG(const vector<string> &pinyinSeq, WHG &whg, const set<int> &prosodicBoundaryPos) const;
	/* For probSum */
	Prob bigramProbSum(WHG &whg) const;
	Prob trigramProbSum(WHG &whg) const;
	/* For probMax. */
	Prob bigramProbMax(WHG &whg) const;
	Prob trigramProbMax(WHG &whg) const;
	void extractBigramWHGPath(const WHG &whg, vector<WHGNode> &whgPath) const;
	void extractTrigramWHGPath(const WHG &whg, vector<WHGNode> &whgPath) const;

	/* Helper functions to get the probability. */
	inline static Prob bigramWHGNodeAccumulate(const Prob &accumulator, const WHGNode &curNode) {
		return accumulator + curNode.biPrSum;
	}
	inline static Prob trigramWHGNodeAccumulate(const Prob &accumulator, const WHGNode &curNode) {
		return accumulator + accumulate(curNode.triPrSum.begin(), curNode.triPrSum.end(), .0);
	}
	inline static bool bigramWHGNodeCmp(const WHGNode &n1, const WHGNode &n2) {
		return n1.biPrMax < n2.biPrMax; 
	}
	inline static bool trigramWHGNodeCmp(const WHGNode &n1, const WHGNode &n2) {
		return *max_element(n1.triPrMax.begin(), n1.triPrMax.end()) < *max_element(n2.triPrMax.begin(), n2.triPrMax.end());
	}
};

#endif
