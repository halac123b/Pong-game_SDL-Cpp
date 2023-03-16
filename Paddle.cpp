#include "Paddle.h"

void Paddle::movePaddleAuto(Ball ball)
{
  int center = posY + 25;
  int screenCenter = screen->h / 2 - 25;
  int ballSpeed = ball.velY;

  // Lấy giá trị dương
  if (ballSpeed < 0)
  {
    ballSpeed = -ballSpeed;
  }

  if (ball.velX > 0)
  {
    // Tự di chuyển vào giữa màn hình
    if (center < screenCenter)
    {
      posY += ballSpeed;
    }
    else
    {
      posY -= ballSpeed;
    }
  }
  // Khi ball đang bay về phía paddle auto
  else
  {
    if (ball.velY > 0)
    {
      if (ball.posY > center)
      {
        posY += ballSpeed;
      }
      else
      {
        posY -= ballSpeed;
      }
    }

    else if (ball.velY < 0)
    {
      if (ball.posY < center)
      {
        posY -= ballSpeed;
      }
      else
      {
        posY += ballSpeed;
      }
    }

    // Ball bay thăng về bên trái
    if (ball.velY == 0)
    {
      if (ball.posY < center)
      {
        posY -= 5;
      }
      else
      {
        posY += 5;
      }
    }
  }
}

void Paddle::movePaddle(int upInput)
{
  // Di chuyển đi xuống
  if (upInput == 0)
  {
    // Giữ paddle không đi quá màn hình
    if (posY >= screen->h - height)
    {
      posY = screen->h - height;
    }
    else
    {
      posY += 5;
    }
  }

  else if (upInput == 1)
  {
    if (posY <= 0)
    {
      posY = 0;
    }
    else
    {
      posY -= 5;
    }
  }
}
