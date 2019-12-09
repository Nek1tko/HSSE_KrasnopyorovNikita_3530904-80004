#include "game.hpp"
#include "axis.hpp"
#include <unordered_map>
#include <stdio.h>

const int OFFSETX = 44;

Game::Game():
  Ball(),
  Paddle(),
  textureBG_(),
  spriteBG_(),
  count_(0),
  score_(0),
  font_()
{
  font_.loadFromFile("text1.otf");
  textureBG_.loadFromFile("bg.png");
  spriteBG_.setTexture(textureBG_);
}

void Game::mainMenu(sf::RenderWindow& window)
{
  window.clear();
  sf::Texture textureMainMenu;
  textureMainMenu.loadFromFile("main-menu.jpg");
  sf::Sprite spriteMainMenu(textureMainMenu);
  window.draw(spriteMainMenu);

  sf::Text textPlay;
  textPlay.setFont(font_);
  textPlay.setPosition(20, 400);
  textPlay.setFillColor(sf::Color::Black);
  textPlay.setString("Play");
  window.draw(textPlay);


  sf::Text textInfo;
  textInfo.setFont(font_);
  textInfo.setPosition(20, 450);
  textInfo.setFillColor(sf::Color::White);
  textInfo.setString("Info");
  window.draw(textInfo);

  sf::Text textExit;
  textExit.setFont(font_);
  textExit.setPosition(20, 500);
  textExit.setFillColor(sf::Color::White);
  textExit.setString("Exit");
  window.draw(textExit);


  window.display();

  size_t numSubMenu = 1;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Down)
        {
          switch (numSubMenu)
          {
          case 1:
          {
            textInfo.setFillColor(sf::Color::Black);
            textPlay.setFillColor(sf::Color::White);
            ++numSubMenu;
            break;
          }

          case 2:
          {
            textExit.setFillColor(sf::Color::Black);
            textInfo.setFillColor(sf::Color::White);
            ++numSubMenu;
            break;
          }

          case 3:
          {
            textPlay.setFillColor(sf::Color::Black);
            textExit.setFillColor(sf::Color::White);
            numSubMenu = 1;
            break;
          }
          }
        }
        else if (event.key.code == sf::Keyboard::Up)
        {

          switch (numSubMenu)
          {
          case 1:
          {
            textExit.setFillColor(sf::Color::Black);
            textPlay.setFillColor(sf::Color::White);
            numSubMenu = 3;
            break;
          }

          case 2:
          {
            textPlay.setFillColor(sf::Color::Black);
            textInfo.setFillColor(sf::Color::White);
            --numSubMenu;
            break;
          }

          case 3:
          {
            textInfo.setFillColor(sf::Color::Black);
            textExit.setFillColor(sf::Color::White);
            --numSubMenu;
            break;
          }
          }
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
          switch (numSubMenu)
          {
          case 1:
          {
            newGame(window);
            break;
          }

          case 2:
          {
            sf::Text smallReview;
            smallReview.setFont(font_);
            smallReview.setString("This is an arcanoid game. Press Up Arrow to throw a\nball and start the game.  Control the paddle using\nLeft and Right arrows. Press Enter when you lose or\nwin to rerun the game.\nHave fun :)");
            smallReview.setFillColor(sf::Color::White);
            window.clear();
            window.draw(smallReview);
            window.display();
            while (window.isOpen())
            {
              while (window.pollEvent(event))
              {
                if (event.type == sf::Event::Closed)
                {
                  window.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                  if (event.key.code == sf::Keyboard::Escape)
                  {
                    break;
                  }
                }
              }
              if (event.key.code == sf::Keyboard::Escape)
              {
                break;
              }
            }
            break;
          }

          case 3:
          {
            window.close();
            break;
          }
          }
        }
      }
    }
    window.clear();
    window.draw(spriteMainMenu);
    window.draw(textPlay);
    window.draw(textInfo);
    window.draw(textExit);
    window.display();
  }

}

void Game::makeLevel(std::vector<std::vector<Block>>& blocks)
{
  const size_t height = Block::getHeight();
  const size_t width = Block::getWidth();
  std::vector<Block> tmp;

  for (size_t i = 0; i < 16; ++i)
  {
    tmp.push_back(Block(Block::WHITE));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 1 + (width * i), 0));
    ++count_;
  }

  blocks.push_back(tmp);
  tmp.clear();

  for (size_t i = 0; i < 14; ++i)
  {
    tmp.push_back(Block(Block::ORANGE));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 2 + (width * i), height * 1));
    ++count_;
  }

  blocks.push_back(tmp);
  tmp.clear();

  for (size_t i = 0; i < 12; ++i)
  {
    tmp.push_back(Block(Block::BLUE));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 3 + (width * i), height * 2));
    ++count_;
  }

  blocks.push_back(tmp);
  tmp.clear();

  for (size_t i = 0; i < 10; ++i)
  {
    tmp.push_back(Block(Block::GREEN));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 4 + (width * i), height * 3));
    ++count_;
  }

  blocks.push_back(tmp);
  tmp.clear();

  for (size_t i = 0; i < 8; ++i)
  {
    tmp.push_back(Block(Block::RED));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 5 + (width * i), height * 4));
    ++count_;
  }

  blocks.push_back(tmp);
  tmp.clear();

  for (size_t i = 0; i < 6; ++i)
  {
    tmp.push_back(Block(Block::PINK));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 6 + (width * i), height * 5));
    ++count_;
  }

  blocks.push_back(tmp);
  tmp.clear();

  for (size_t i = 0; i < 4; ++i)
  {
    tmp.push_back(Block(Block::YELLOW));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 7 + (width * i), height * 6));
    ++count_;
  }

  blocks.push_back(tmp);
  tmp.clear();

  for (size_t i = 0; i < 2; ++i)
  {
    tmp.push_back(Block(Block::LIGHTBLUE));
    tmp.at(i).setPosition(sf::Vector2f(OFFSETX * 8 + (width * i), height * 7));
    ++count_;
  }

  tmp.push_back(Block(Block::GREY));
  tmp.at(2).setPosition(sf::Vector2f(OFFSETX * 8 + width / 2, height * 8));
  ++count_;

  blocks.push_back(tmp);
  tmp.clear();
}

void Game::update(sf::RenderWindow& window, sf::Event& event)
{
  window.clear();
  window.draw(spriteBG_);
  Paddle::draw(window);
  Ball::draw(window);
  std::for_each(blocks_.begin(), blocks_.end(), [&](const std::vector<Block>& vectorOfBlock){
    std::for_each(vectorOfBlock.begin(), vectorOfBlock.end(), [&](const Block& block){block.draw(window);});});
  window.display();

  if (!Ball::move())
  {
    gameOver(window);
  }

  if (Paddle::isIntersected(Ball::getPosition()))
  {
    Ball::genNewAngle(Paddle::getPosition());
  }

  Axis direction = NOPE;
  std::find_if(blocks_.begin(), blocks_.end(), [&](std::vector<Block>& vector){
    auto iter = std::find_if(vector.begin(), vector.end(), [&](Block& block)
    {
        direction = block.getInterAxes(Ball::getPosition());
        if (direction != NOPE)
    {
        if (block.isDeleted())
    {
        addPoints(block);
        --count_;
  }
        return true;
  }
        return false;
  });
    if (iter != vector.end())
    {
      Ball::changeDirection(direction);
      return true;
    }
    return false;
  });

  if (count_ == 0)
  {
    win(window);
  }

  if (event.type == sf::Event::KeyPressed)
  {
    Paddle::move(event);
  }
}

void Game::gameOver(sf::RenderWindow &window)
{
  window.clear();
  sf::Texture textureGameOver;
  textureGameOver.loadFromFile("game-over.jpg");
  sf::Sprite spriteGameOver(textureGameOver);
  window.draw(spriteGameOver);

  sf::Text textRerun;
  textRerun.setFont(font_);
  textRerun.setString("Press Enter to restart");
  textRerun.setFillColor(sf::Color::Black);
  textRerun.setPosition(230, 50);
  window.draw(textRerun);

  sf::Text textScore;
  textScore.setFont(font_);
  char string[10];
  sprintf(string, "%d", score_);
  textScore.setString(sf::String("Your score: ") + string);
  textScore.setFillColor(sf::Color::Black);
  textScore.setPosition(300, 520);
  window.draw(textScore);


  window.display();

  while(window.isOpen())
  {
    sf::Event event;

    while(window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          window.close();
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
          newGame(window);
          break;
        }
      }
    }
  }
}

void Game::newGame(sf::RenderWindow& window)
{
  count_ = 0;
  score_ = 0;
  blocks_.clear();
  makeLevel(blocks_);
  Paddle::setStartPos();
  Ball::setStartPos();

  while (window.isOpen())
  {
    window.clear();
    window.draw(spriteBG_);
    Paddle::draw(window);
    Ball::draw(window);
    std::for_each(blocks_.begin(), blocks_.end(), [&](const std::vector<Block>& vectorOfBlock){
      std::for_each(vectorOfBlock.begin(), vectorOfBlock.end(), [&](const Block& block){block.draw(window);});});
    window.display();

    sf::Event event;
    while(window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    if (event.type == sf::Event::KeyPressed)
    {
      Paddle::move(event);
      Ball::move(event);

      if (event.key.code == sf::Keyboard::Up)
      {
        while(window.isOpen())
        {
          while(window.pollEvent(event))
          {
            if (event.type == sf::Event::Closed)
            {
              window.close();
            }
          }

          update(window, event);
        }
      }
    }
  }
}

void Game::win(sf::RenderWindow &window)
{
  sf::Texture textureWin;
  textureWin.loadFromFile("win.jpg");
  sf::Sprite spriteWin(textureWin);

  window.clear();
  window.draw(spriteWin);

  sf::Text textRerun;
  textRerun.setFont(font_);
  textRerun.setString("Press Enter to restart");
  textRerun.setFillColor(sf::Color::Black);
  textRerun.setPosition(230, 50);
  window.draw(textRerun);

  sf::Text textScore;
  textScore.setFont(font_);
  char string[10];
  sprintf(string, "%d", score_);
  textScore.setString(sf::String("Your score: ") + string);
  textScore.setFillColor(sf::Color::Black);
  textScore.setPosition(300, 520);
  window.draw(textScore);

  window.display();

  while(window.isOpen())
  {
    sf::Event event;

    while(window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          window.close();
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
          newGame(window);
          break;
        }
      }
    }
  }
}

void Game::addPoints(Block &block)
{
  std::unordered_map<Block::Color, size_t> map ={
    {Block::Color::WHITE, 200},
    {Block::Color::ORANGE, 100},
    {Block::Color::BLUE, 50},
    {Block::Color::GREEN, 30},
    {Block::Color::RED, 20},
    {Block::Color::PINK, 10},
    {Block::Color::YELLOW, 5},
    {Block::Color::LIGHTBLUE, 2},
    {Block::Color::DESTROYEDGREY, 300}
  };

  auto iter = map.find(block.color_);
  if (iter != map.end())
  {
    score_ += iter->second;
  }

}
