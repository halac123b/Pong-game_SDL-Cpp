#include "Global.h"
#include "Ball.h"
#include "Paddle.h"

int score[] = {0, 0};

SDL_Texture *screenTexture;
Ball ball;
Paddle paddle[2]; // 2 tấm ván
int width, height;

static void initGameData()
{
  ball.posX = screen->w / 2;
  ball.posY = screen->h / 2;
  ball.width = ball.height = 10;
  ball.velX = ball.velY = 1;

  paddle[0].posX = 20;
  paddle[0].posY = screen->h / 2 - 50;
  paddle[0].width = 10;
  paddle[0].height = 50;

  paddle[1].posX = screen->w - 30;
  paddle[1].posY = screen->h / 2 - 50;
  paddle[1].width = 10;
  paddle[1].height = 50;
}

int checkScore()
{
  for (int i = 0; i < 2; i++)
  {
    // Check if the score reach score limit
    if (score[i] == 10)
    {
      // Reset score
      score[0] = score[1] = 0;

      // Return player win
      if (i == 0)
      {
        return 1;
      }
      else
      {
        return 2;
      }
    }
  }
  return 0;
}

// Check 2 quả bóng có va chạm với nhau hay không
int checkCollision(Ball a, Paddle b)
{
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  // Top-left corner of 2 Balls
  leftA = a.posX;
  topA = a.posY;
  leftB = b.posX;
  topB = b.posY;

  // Right-bottom corner
  rightA = a.posX + a.width;
  bottomA = a.posY + a.height;
  rightB = b.posX + b.width;
  bottomB = b.posY + b.height;

  if (leftA > rightB || leftA < leftB || topA > bottomB || bottomA < topB)
  {
    return 0;
  }
  return 1;
}

void moveBall()
{
  ball.posX += ball.velX;
  ball.posY += ball.velY;

  // Nếu bóng chạm cạnh trái/phải, player goal
  if (ball.posX < 0)
  {
    score[1] += 1;
    initGameData();
  }
  if (ball.posX > screen->w - 10)
  {
    score[0] += 1;
    initGameData();
  }

  // Bóng chạm cạnh trên dưới thì nảy lại
  if (ball.posY < 0 || ball.posX > screen->h)
  {
    ball.velY = -ball.velY;
  }

  for (int i = 0; i < 2; i++)
  {
    int collision = checkCollision(ball, paddle[i]);
    if (collision == 1)
    {
      // Tăng tốc độ, sau đó đổi chiều
      if (ball.velX < 0)
      {
        ball.velX -= 1;
      }
      else
      {
        ball.velX += 1;
      }
      ball.velX = -ball.velX;

      // Thay đổi góc bay của ball tùy vào vị trí nó chạm vào paddle
      int hitPos = (paddle[i].posY + paddle[i].height) - ball.posY;

      if (hitPos >= 0 && hitPos < 7)
      {
        ball.velY = 4;
      }
      else if (hitPos >= 7 && hitPos < 14)
      {
        ball.velY = 3;
      }
      else if (hitPos >= 14 && hitPos < 21)
      {
        ball.velY = 2;
      }
      else if (hitPos >= 21 && hitPos < 28)
      {
        ball.velY = 1;
      }
      else if (hitPos >= 28 && hitPos < 32)
      {
        ball.velY = 0;
      }
      else if (hitPos >= 32 && hitPos < 39)
      {
        ball.velY = -1;
      }
      else if (hitPos >= 39 && hitPos < 46)
      {
        ball.velY = -2;
      }
      else if (hitPos >= 46 && hitPos < 53)
      {
        ball.velY = -3;
      }
      else if (hitPos >= 53 && hitPos <= 60)
      {
        ball.velY = -4;
      }

      // Dịch chuyển ball ra xa ngay để tránh nhiễu khi va chạm liên tục
      if (ball.velX > 0 && ball.posX < 30)
      {
        ball.posX = 30;
      }
      else if (ball.posX > 600)
      {
        ball.posX = 600;
      }
    }
  }
}

void drawGameOver(int p)
{
  SDL_Rect p1;
  SDL_Rect p2;
  SDL_Rect cpu;
  SDL_Rect dest;

  p1.x = p1.y = 0;
  p1.w = endScreen->w;
  p1.h = 75;

  p2.x = 0;
  p2.y = 75;
  p2.w = endScreen->w;
  p2.h = 75;

  cpu.x = 0;
  cpu.y = 150;
  cpu.w = endScreen->w;
  cpu.h = 75;

  dest.x = (screen->w / 2) - (endScreen->w / 2);
  dest.y = (screen->h / 2) - (75 / 2);
  dest.w = endScreen->w;
  dest.h = 75;

  switch (p)
  {
  case 1:
    SDL_BlitSurface(endScreen, &p1, screen, &dest);
    break;
  case 2:
    SDL_BlitSurface(endScreen, &p2, screen, &dest);
    break;
  default:
    SDL_BlitSurface(endScreen, &cpu, screen, &dest);
  }
}

void drawMenu()
{
  SDL_Rect src;
  SDL_Rect dest;

  src.x = src.y = 0;
  src.w = title->w;
  src.h = title->h;

  dest.x = (screen->w / 2) - (src.w / 2);
  dest.y = (screen->h / 2) - (src.h / 2);
  dest.w = title->w;
  dest.h = title->h;

  SDL_BlitSurface(title, &src, screen, &dest);
}

void drawBackground()
{
  SDL_Rect src;

  src.x = src.y = 0;
  src.w = screen->w;
  src.h = screen->h;
}

void drawNet()
{
  SDL_Rect net;

  net.x = screen->w / 2;
  net.y = 20;
  net.w = 20;
  net.h = 15;

  for (int i = 0; i < 15; i++)
  {
    int r = SDL_FillRect(screen, &net, 0xffffffff);

    if (r != 0)
    {
      printf("Fill rectangle failed in function drawNet()");
    }
    net.y += 30;
  }
}

void drawBall()
{
  SDL_Rect src;

  src.x = ball.posX;
  src.y = ball.posY;
  src.w = ball.width;
  src.h = ball.height;

  int r = SDL_FillRect(screen, &src, 0xffffffff);

  if (r != 0)
  {
    printf("Fill rectangle failed in func drawBall()");
  }
}

void drawPaddle()
{
  SDL_Rect src;
  for (int i = 0; i < 2; i++)
  {
    src.x = paddle[i].posX;
    src.y = paddle[i].posY;
    src.w = paddle[i].width;
    src.h = paddle[i].height;

    int r = SDL_FillRect(screen, &src, 0xffffffff);
    if (r != 0)
    {
      printf("Fill rectangle faliled in func drawPaddle()");
    }
  }
}

void drawPlayerScore(int team)
{
  SDL_Rect src;
  SDL_Rect dest;

  src.x = src.y = 0;
  src.w = src.h = 64;

  if (team == 0)
  {
    dest.x = (screen->w / 2) - src.w - 12;
  }
  else
  {
    dest.x = (screen->w / 2) + 12;
  }
  dest.y = 0;
  dest.w = dest.h = 64;

  if (score[team] > 0 && score[team] < 10)
  {
    src.x += src.w * score[team];
  }

  SDL_BlitSurface(scoreMap, &src, screen, &dest);
}

int main(int argc, char *argv[])
{
  if (initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, argc, argv) == 1)
  {
    return 0;
  }

  SDL_GetWindowSize(g_window, &width, &height);

  int sleep = 0;
  int quit = 0;
  int state = 0;
  int r = 0;
  Uint32 nextGameTick = SDL_GetTicks();

  initGameData();

  while (quit == 0)
  {
    SDL_PumpEvents();
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_ESCAPE])
    {
      quit = 1;
    }
    if (keyState[SDL_SCANCODE_DOWN])
    {
      paddle[1].movePaddle(0);
    }
    if (keyState[SDL_SCANCODE_UP])
    {
      paddle[1].movePaddle(1);
    }

    // Draw background
    SDL_RenderClear(g_screen);
    SDL_FillRect(screen, NULL, 0x000000ff);

    // Display main menu
    if (state == 0)
    {
      if (keyState[SDL_SCANCODE_SPACE])
      {
        state = 1;
      }
      drawMenu();
    }
    else if (state == 2)
    {
      // Display gameover
      if (keyState[SDL_SCANCODE_SPACE])
      {
        state = 0;
        // Delay 1 khoảng để tránh việc nhấn Space bị kích hoạt 2 lần
        SDL_Delay(500);
      }
      if (r == 1)
      {
        drawGameOver(3);
      }
      else
      {
        drawGameOver(r);
      }
    }
    else if (state == 1)
    {
      // Display the game
      r = checkScore();
      // Nếu có 1 trong 2 win, end game
      if (r == 1 || r == 2)
      {
        state = 2;
      }
      paddle[0].movePaddleAuto(ball);
      moveBall();
      drawNet();
      drawPaddle();
      drawBall();
      drawPlayerScore(0);
      drawPlayerScore(1);
    }

    SDL_UpdateTexture(screenTexture, NULL, screen->pixels, screen->w * sizeof(Uint32));
    SDL_RenderCopy(g_screen, screenTexture, NULL, NULL);

    SDL_RenderPresent(g_screen);

    // Control time to display 60FPS
    nextGameTick += 1000 / 60;
    sleep = nextGameTick - SDL_GetTicks();
    if (sleep >= 0)
    {
      SDL_Delay(sleep);
    }
  }

  // Free loaded images
  SDL_FreeSurface(screen);
  SDL_FreeSurface(title);
  SDL_FreeSurface(scoreMap);
  SDL_FreeSurface(endScreen);

  SDL_DestroyRenderer(g_screen);
  SDL_DestroyWindow(g_window);

  SDL_Quit();
  return 0;
}

int initSDL(int width, int height, int argc, char *args[])
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {

    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

    return 1;
  }

  int i;

  for (i = 0; i < argc; i++)
  {

    // Create window
    if (strcmp(args[i], "-f"))
    {

      SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &g_window, &g_screen);
    }
    else
    {

      SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP, &g_window, &g_screen);
    }
  }

  if (g_window == NULL)
  {

    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

    return 1;
  }

  // create the screen sruface where all the elemnts will be drawn onto (ball, paddles, net etc)
  screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

  if (screen == NULL)
  {

    printf("Could not create the screen surfce! SDL_Error: %s\n", SDL_GetError());

    return 1;
  }

  // create the screen texture to render the screen surface to the actual display
  screenTexture = SDL_CreateTextureFromSurface(g_screen, screen);

  if (screenTexture == NULL)
  {

    printf("Could not create the screen_texture! SDL_Error: %s\n", SDL_GetError());

    return 1;
  }

  // Load the title image
  title = SDL_LoadBMP("title.bmp");

  if (title == NULL)
  {

    printf("Could not Load title image! SDL_Error: %s\n", SDL_GetError());

    return 1;
  }

  // Load the numbermap image
  scoreMap = SDL_LoadBMP("numbermap.bmp");

  if (scoreMap == NULL)
  {

    printf("Could not Load numbermap image! SDL_Error: %s\n", SDL_GetError());

    return 1;
  }

  // Load the gameover image
  endScreen = SDL_LoadBMP("gameover.bmp");

  if (endScreen == NULL)
  {

    printf("Could not Load title image! SDL_Error: %s\n", SDL_GetError());

    return 1;
  }

  // Set the title colourkey.
  Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
  SDL_SetColorKey(title, SDL_TRUE, colorkey);
  SDL_SetColorKey(scoreMap, SDL_TRUE, colorkey);

  return 0;
}