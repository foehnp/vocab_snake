#include "widgets.h"


Scroll::Scroll (int left, int top, int width, int n_lines_shown, std::vector<std::string> texts, sf::Color color_on, 
        sf::Color color_off, sf::Font font, int selected):
left(left), top(top), width(width), n_lines_shown(n_lines_shown), 
texts(texts), color_off(color_off), color_on(color_on), font(font), selected(selected){
  n_lines = texts.size();
  first_shown = 0;
}

void Scroll::draw(sf::RenderWindow& window){
  sf::RectangleShape rect_main(sf::Vector2f(width, 20*n_lines_shown));
  rect_main.setPosition(left, top);
  rect_main.setFillColor(color_off);
  window.draw(rect_main);
  
  sf::CircleShape up(10, 3);
  up.setPosition(left +width-20,top);
  up.setFillColor(color_on);
  window.draw(up);
  
  sf::CircleShape down(10, 3);
  down.rotate(180.f);
  down.setPosition(left +width,top+n_lines_shown*20);
  down.setFillColor(color_on);
  window.draw(down);
  
  for (int i=0; i<n_lines_shown and i<n_lines; i++){
    if ((i+first_shown+n_lines)%n_lines==selected){
      sf::RectangleShape rect(sf::Vector2f(width-20, 20));
      rect.setPosition(left, top+20*i);
      rect.setFillColor(color_on);
      window.draw(rect);
    }
    sf::Text t;
    t.setFont(font);  
    t.setString(texts[(i+first_shown)%n_lines]);
    t.setCharacterSize(16);
    t.setFillColor(sf::Color::White);
    t.setPosition(left+10 , top+i*20+1);
    window.draw(t); 
  }
}

bool Scroll::isClicked(sf::Vector2i pos){
  if (!(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))){
    return false;
  }
  if (pos.x>left and pos.x<left+width-25 and pos.y>top and pos.y<top+20*n_lines_shown and pos.y<top+20*n_lines){
    selected = (first_shown+(pos.y-top)/20)%n_lines;
  }
  if (n_lines>n_lines_shown and pos.x>left+width-20 and pos.x<left+width and pos.y>top and pos.y<top+20){
    first_shown = (first_shown-1+n_lines)%n_lines;
  }
  if (n_lines>n_lines_shown and pos.x>left+width-20 and pos.x<left+width and pos.y>top+(n_lines_shown-1)*20 and pos.y<top+n_lines_shown*20){
    first_shown = (first_shown+1+n_lines)%n_lines;
  }
  return true;
}

int Scroll::getSelected(){
  return selected;
}
  




Button::Button(int left, int top, int width, int height, 
        std::string text, sf::Color color_on, sf::Color color_off, sf::Font font, bool state): 
left(left), top(top), width(width), height(height), 
text(text), color_off(color_off), color_on(color_on), font(font), state(state){}

void Button::draw(sf::RenderWindow& window){
  sf::RectangleShape rect(sf::Vector2f(width, height));
  if (state){
    rect.setFillColor(color_on);
  }else{
    rect.setFillColor(color_off);
  }
  rect.setPosition(left, top);
  window.draw(rect);
  
  sf::Text t;
  t.setFont(font);
  t.setString(text);
  t.setCharacterSize(height-8);
  t.setFillColor(sf::Color::White);
  t.setPosition(left+10 , top+2);
  window.draw(t);    
}

bool Button::isClicked(sf::Vector2i pos){
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and
    pos.x>left and pos.x<left+width and pos.y>top and pos.y<top+height){
    return true;
  }
  return false;
}

void Button::setState(bool new_state){
  state = new_state;
}

bool Button::getState(){
  return state;
}

