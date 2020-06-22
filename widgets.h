#ifndef widgets
#define widgets

#include "funcs.h"

class Scroll{
public:
  Scroll (int left, int top, int width, int n_lines_shown, std::vector<std::string> texts, sf::Color color_on, 
          sf::Color color_off, sf::Font font, int selected);
  void draw(sf::RenderWindow& window);
  bool isClicked(sf::Vector2i pos);
  int getSelected();
  
  
private:
  int left;
  int top;
  int width;
  int n_lines_shown;
  int n_lines;
  std::vector<std::string> texts;
  int first_shown;;
  int selected;
  sf::Color color_off;
  sf::Color color_on;
  sf::Font font;
};




class Button{
public:
  Button(int left, int top, int width, int height, 
         std::string text, sf::Color color_on, sf::Color color_off, sf::Font font, bool state);

  void draw(sf::RenderWindow& window);
  bool isClicked(sf::Vector2i pos);
  void setState(bool new_state);
  bool getState();
  
private:
  int left;
  int top;
  int width;
  int height;
  std::string text;
  sf::Color color_off;
  sf::Color color_on;
  sf::Font font;
  bool state;
};

#endif
