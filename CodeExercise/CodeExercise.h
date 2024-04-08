#ifndef CODEEXERCISE_H_
#define CODEEXERCISE_H_
#include <string>
using namespace std;

struct Trade
{
  long long timeStamp;
  string symbol;
  int quantity;
  int price;
};

void processTrades(const string& filename);

#endif
