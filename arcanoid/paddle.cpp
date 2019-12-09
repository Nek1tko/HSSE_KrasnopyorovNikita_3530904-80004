#include "paddle.hpp"
#include "ball.hpp"

Paddle::Paddle():
  spritePaddle_(),
  texturePaddle_()
{
  texturePaddle_.loadFromFile("paddle.png");
  spritePaddle_.setTexture(texturePaddle_);
  spritePaddle_.setPosition((800  - width_) / 2, 600 - height_);
}

void Paddle::move(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::Left)
  {
    if (spritePaddle_.getPosition().x > STEP)
    {
      spritePaddle_.move(-STEP, 0);
    }
    else
    {
      spritePaddle_.setPosition(0, 600 - height_);
    }
  }
  else if (event.key.code == sf::Keyboard::Right)
  {
    if (spritePaddle_.getPosition().x + width_ < 800 - STEP)
    {
      spritePaddle_.move(STEP, 0);
    }
    else
    {
      spritePaddle_.setPosition(800 - width_, 600 - height_);
    }
  }
}

void Paddle::draw(sf::RenderWindow& window)
{
  window.draw(spritePaddle_);
}

size_t Paddle::getWidth()
{
  return width_;
}

size_t Paddle::getHeight()
{
  return height_;
}

bool Paddle::isIntersected(const sf::Vector2f &posBall) const
{
  const sf::Vector2f posPaddle = getPosition();
  size_t side = Ball::getSide();
  if (posBall.y + side > posPaddle.y)
  {
    if ((posBall.x + side > posPaddle.x) && (posBall.x < posPaddle.x + width_))
    {
      return true;
    }
  }

  return false;
}

sf::Vector2f Paddle::getPosition() const
{
  return spritePaddle_.getPosition();
}

void Paddle::setStartPos()
{
  spritePaddle_.setPosition((800  - width_) / 2, 600 - height_);
}

