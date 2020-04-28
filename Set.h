#include<cstdlib>
#include<vector>
#include"Line.h"
class Set{
private:
  unsigned long long assoc;
  std::vector<Line> ways;
public:
bool insert(Line);
Set(int a);
Set();
};
