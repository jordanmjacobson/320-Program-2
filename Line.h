#include<cstdlib>
#include<string>
#ifndef LINE_H
#define LINE_H

class Line{
private:
  std::string f; //the flag
  unsigned long long addr;
  unsigned long long t;
  unsigned long long index;
  unsigned long long total_idle = 0;
  bool just_updated = false;
public:
  std::string flag(); //returns flag
  unsigned long long address();
  unsigned long long tag();
  unsigned long long idle();
  bool updated();
  void setFlag(std::string);
  void setAddress(unsigned long long);
  void setTag(unsigned long long);
  void setIndex(unsigned long long);
  void update();
  void reset();
  void plus_one();
  Line(std::string, unsigned long long);
  Line();

};
#endif
