#include "welcome.h"

namespace fs = std::experimental::filesystem;

void menu(Settings& set, std::string& path, sf::RenderWindow& window){
  
  sf::Color color_bg{170,230,240,255};
  sf::Color color_off{79,215,236,255};
  sf::Color color_on{30,66,244,255};
//   color_on = sf::Color::Red;
//   color_off = sf::Color::Yellow;   
  
  // Title text
  window.clear(color_bg);
  sf::Text title;
  title.setFont(set.font);
  title.setString("S N E K   W I T H\n   L E T T E R S!");
  title.setCharacterSize(33);
  title.setFillColor(sf::Color::White);
  title.setPosition((set.total_w-title.getGlobalBounds().width)/2, 60);
  window.draw(title);
  
  //Select speed text
  sf::Text choosetext;
  choosetext.setFont(set.font);
  choosetext.setString("Select speed:");
  choosetext.setCharacterSize(20);
  choosetext.setFillColor(sf::Color::White);
  choosetext.setPosition(50, 175);
//   window.draw(choosetext);
  
  //Speed setting buttons
  Button slow(150, 180, 80, 20, "Slow", color_on, color_off, set.font, true);
  slow.draw(window);
  Button medium(250, 180, 80, 20, "Medium", color_on, color_off, set.font, false);
  medium.draw(window);
  Button fast(350, 180, 80, 20, "Fast", color_on, color_off, set.font, false);
  fast.draw(window);
  //Start Button
  Button start(280, 330, 180, 30, "Let's go!", color_on, color_off, set.font, false);
  start.draw(window);
  
  // File scroll list
  std::vector<std::string> texts;
  std::string p = "/home/philip/Documents/snake/wsnake6/vocab";
  for (const auto & entry : fs::directory_iterator(p)){
    texts.push_back(entry.path().filename().string());
  }
  Scroll scroll(150, 220, 400, 4, texts, color_on, 
          color_off, set.font, 2);
  scroll.draw(window);
  
  
  
  
  window.display();
  
  while (window.isOpen()){
    //Close if user wants to close
    sf::Event e;
    while (window.pollEvent(e)){
      if (e.type == sf::Event::Closed){   
        window.close(); return;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        while(!sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        }
      }
      if (slow.isClicked(sf::Mouse::getPosition(window))){
        slow.setState(true);
        medium.setState(false);
        fast.setState(false);
        slow.draw(window);
        medium.draw(window);
        fast.draw(window);
        window.display();
      }
      if (medium.isClicked(sf::Mouse::getPosition(window))){
        slow.setState(false);
        medium.setState(true);
        fast.setState(false);
        slow.draw(window);
        medium.draw(window);
        fast.draw(window);
        window.display();
      }
      if (fast.isClicked(sf::Mouse::getPosition(window))){
        slow.setState(false);
        medium.setState(false);
        fast.setState(true);
        slow.draw(window);
        medium.draw(window);
        fast.draw(window);
        window.display();
      }
      if (scroll.isClicked(sf::Mouse::getPosition(window))){
        scroll.draw(window);
        window.display();
      }
      if (start.isClicked(sf::Mouse::getPosition(window))){
        start.setState(true);
        start.draw(window);
        window.display();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);
      }
    }
    //Get out of loop to start game, if start has been clicked
    if (start.getState()){
      break;
    }
  }
  // Adjust delay of game to selected speed
  if (slow.getState()){
    set.delay=0.4;
  } else if (medium.getState()){
    set.delay=0.25;
  } else{
    set.delay=0.12;
  }
  path = texts[scroll.getSelected()];
  
}
