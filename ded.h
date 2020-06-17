#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "funcs.h"

std::string ded(Settings set, int score, sf::RenderWindow& window){
  std::string s = "You got\n" + std::to_string(score) + " points!";
  window.clear(set.color_bg);
  sf::Text text;
  text.setFont(set.font);
  text.setString(s);
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  text.setPosition(180, 100);
  window.draw(text);
  
  sf::Color color_off{79,215,236,255};
  sf::Color color_on{30,66,244,255};
  Button again(150, 230, 140, 30, "Play again", color_on, color_off, set.font, false);
  again.draw(window);
  Button quit(350, 230, 140, 30, "Quit", color_on, color_off, set.font, false);
  quit.draw(window);
  window.display();

  while (window.isOpen()){
    //Close if user wants to close
    sf::Event e;
    while (window.pollEvent(e)){
      if (e.type == sf::Event::Closed){   
        window.close(); return "quit";
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        while(!sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        }
      }
      if (again.isClicked(sf::Mouse::getPosition(window))){
        again.setState(true);
        again.draw(window);
        window.display();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);
      }
      if (quit.isClicked(sf::Mouse::getPosition(window))){
        quit.setState(true);
        quit.draw(window);
        window.display();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);
      }
    }
    if (again.getState()==true){
      return "again";
    }
    if (quit.getState()==true){
      return "quit";
    }
  }
}


