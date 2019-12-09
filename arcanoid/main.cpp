#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "game.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600, 100), "Arcanoid");
  window.setFramerateLimit(60);

  Game game;
  game.mainMenu(window);

  return 0;
}
