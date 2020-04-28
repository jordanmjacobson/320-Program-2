#include<cstdlib>
#include<vector>
#include"Line.h"
class Set{
private:
  unsigned long long assoc;
  std::vector<Line> ways;
  bool alloc_on_miss = true;
public:
bool insert(Line);
void set_idles();
void set_alloc(bool);
Set(int a);
Set();
};
