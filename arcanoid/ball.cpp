#include "ball.hpp"
#include <cmath>
#include "paddle.hpp"

Ball::Ball():
  angle_(-80),
  delta_(5),
  textureBall_(),
  spriteBall_()
{
  textureBall_.loadFromFile("ball.png");
  spriteBall_.setTexture(textureBall_);
  spriteBall_.setPosition((800 - side_) / 2, 600 - side_ - Paddle::getHeight());
}

void Ball::draw(sf::RenderWindow& window)
{
  window.draw(spriteBall_);
}

bool Ball::move()
{
  sf::Vector2f pos = spriteBall_.getPosition();

  if (pos.y > 600 - side_)
  {
    return false;
  }

  if ((pos.x > (800 - side_)) || (pos.x < 0))
  {
    changeDirection(VERTICAL);
  }
  else if (pos.y < 0)
  {
    changeDirection(HORIZONTAL);
  }

  pos.x += delta_ * cos(M_PI * angle_ / 180);
  pos.y += delta_ * sin(M_PI * angle_ / 180);

  spriteBall_.setPosition(pos);

  return true;
}

sf::Vector2f Ball::getPosition()
{
  return spriteBall_.getPosition();
}

size_t Ball::getSide()
{
  return side_;
}

void Ball::changeDirection(const Axis& direction)
{
  if (direction == VERTICAL)
  {
    angle_ = 180 - angle_;
  }
  else if (direction == HORIZONTAL)
  {
    angle_ = 360 - angle_;
  }

  if (angle_ > 360)
  {
    angle_ -= 360;
  }

  delta_ += 0.5;
}

void Ball::setStartPos()
{
   spriteBall_.setPosition((800 - side_) / 2, 600 - side_ - Paddle::getHeight());
}

void Ball::move(sf::Event event)
{
  double dx = Paddle::getWidth() / 2;
  if (event.key.code == sf::Keyboard::Left)
  {
    if (spriteBall_.getPosition().x  > STEP + dx - side_ / 2)
    {
      spriteBall_.move(-STEP, 0);
    }
    else
    {
      spriteBall_.setPosition(dx - side_ / 2, 600 - side_ - Paddle::getHeight());
    }
  }
  else if (event.key.code == sf::Keyboard::Right)
  {
    if (spriteBall_.getPosition().x + side_ / 2 + dx < 800 - STEP)
    {
      spriteBall_.move(STEP, 0);
    }
    else
    {
      spriteBall_.setPosition(800 - dx - side_ / 2, 600 - side_ - Paddle::getHeight());
    }
  }
}

void Ball::genNewAngle(const sf::Vector2f& posPaddle)
{
  sf::Vector2f posBall = getPosition();
  double relativeValue = ((posBall.x + side_ / 2 - posPaddle.x) / Paddle::getWidth());

  angle_ = (200 + (340 - 200) * relativeValue);
}

