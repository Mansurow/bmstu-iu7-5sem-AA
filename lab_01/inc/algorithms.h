#ifndef LAB_01_ALGORITHMS_H
#define LAB_01_ALGORITHMS_H

#include <iostream>
#include "allocate.h"

using namespace std;

int lev_mtr(wstring &str1, wstring &str2, bool print=false);
int dameray_lev_mtr(wstring &str1, wstring &str2, bool print=false);

int dameray_lev_rec(wstring &str1, wstring &str2);
int dameray_lev_rec_hash(wstring &str1, wstring &str2, bool print=false);
#endif //LAB_01_ALGORITHMS_H
