#include "funcs.h"

bool operator< (const GridPoint a, const GridPoint b){
  return (a.x<b.x or (a.x==b.x and a.y<b.y));
}
bool operator== (const GridPoint a, const GridPoint b){
  return (a.x==b.x and a.y==b.y);
}


