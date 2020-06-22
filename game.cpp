#include "game.h"


int play(Settings set,
       std::vector<std::string> words,
       std::vector<std::string> transs,
       sf::RenderWindow &window){
  //Set time
  sf::Clock clock;
  float timer=0;
  int dir=0, ndir=0; //temporary direction of snake
  //Initialise Game object
  Game gameT(set, words, transs, &window);
  
  while (window.isOpen()){
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer+=time;
    //Close if user wants to close
    sf::Event e;
    while (window.pollEvent(e)){
      if (e.type == sf::Event::Closed){   
        window.close();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        while(!sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        }
      }
    }
    //Update temporary direction if key is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ndir=0;   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ndir=1;    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ndir=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ndir=3;

    if (timer>set.delay*(1+gameT.digesting()*1.5)){
      timer=0;
      gameT.step(ndir);
    }
    std::string status = gameT.get_status();
    if (status=="dead" or status=="finished"){
      break;
    }
  }
  return gameT.get_score();
      
}
         
