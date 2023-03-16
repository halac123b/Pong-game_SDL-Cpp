#ifndef PADDLE_H
#define PADDLE_H

#include "Global.h"
#include "Ball.h"
// Tấm ván để hứng bóng
class Paddle
{
public:
  int posX, posY;
  int width, height;

  // Paddle tự di chuyển
  void movePaddleAuto(Ball ball);
  // Paddle điều khiển bằng tay
  void movePaddle(int upInput);
};
#endif