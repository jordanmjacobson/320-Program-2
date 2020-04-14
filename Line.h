#include<cstdlib>
#include<string>
#ifndef LINE_H
#define LINE_H

class Line{
private:
  std::string f; //the flag
  unsigned long long addr;
public:
  std::string flag(); //returns flag
  unsigned long long address();
  void setFlag(std::string);
  void setAddress(unsigned long long);
  Line(std::string, unsigned long long);

};
#endif
