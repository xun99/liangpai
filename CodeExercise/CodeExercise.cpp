#include "CodeExercise.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void processTrades(const string &filename)
{
  ifstream inputFile(filename);

  std::string line;
  std::vector<Trade> trades;

  while (getline(inputFile, line, ',')){
    cout<<line<<endl;
  }
  
  inputFile.close();
}
