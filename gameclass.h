#ifndef gameclass
#define gameclass

#include "funcs.h"

class Game{
public:
  Game(Settings& set0,
       std::vector<std::string> words0,
       std::vector<std::string> transs0,
       sf::RenderWindow* window_pointer0);
  
  void step(int ndir);
  
  std::string get_status();
  
  int get_score();
  
  bool digesting();
       
  
  
private:
  sf::RenderWindow* window_pointer;
  Settings set;
  std::vector<GridPoint> sn; //location of the snake
  std::string sn_word = " "; //word displayed by snake
  std::map<GridPoint, char> letters; //map of (coordinate, char) of the letters currently on field
  std::vector<std::string> words;
  std::vector<std::string> transs;
  std::vector<std::string> curr_words;
  std::vector<std::string> curr_transs;
  int dir;
  int score;
  std::string status; // "alive", "dead" or "finished"
  int digest;
  
  void spread_word(std::string word);
  int check_word();
  void draw_snake();
  void draw_letters();
  void draw_score();
  void draw_trans();
  void die();
};

#endif
