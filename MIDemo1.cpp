/*
 * File: MIDemo.cpp.
 * Implemented at 23:07 on 20 March 2016 by WuBin.
 * Basic facilities to mutual information of text and phonological units
 *
 */
#include <pybind11/pybind11.h>
#include "MI.h"
using namespace std;

void printWHG(const MI &mi, const string &pinyinSeq) {
  WHG whg;
  mi.buildWHG(pinyinSeq, whg);
  cout << "------------------------------------------------------" << endl;
  cout << "The Word Hypothesis Graph (WHG) of '"<< pinyinSeq << "' is: " << endl;
  mi.printWHG(whg);
}

PYBIND11_MODULE(MI, m){
  pybind11::class_<MI>(m, "MI")
    .def(pybind11::init<int, string, string, bool>())
    .def("probSum", &MI::probSum);
}