#include <Gamebuino-Meta.h>
int16_t snakex[400];
int16_t snakey[400];
int8_t direction = 0;
int16_t length = 3;
int16_t width = 2;
int8_t frame = 0;
int16_t apple[2];
int16_t apple2[2];
uint16_t scene = 0;
const uint16_t maxTail = 200;
uint16_t animD;
uint8_t askedDir = 0;
uint8_t walls = 0;
uint8_t wallBlocks[20][2] = {
    {50, 10},
    {50, 12},
    {50, 14},
    {50, 16},
    {50, 18},
    {50, 20},
    {50, 22},
    {50, 24},
    {50, 26},
    {50, 28},
    {50, 30},
    {50, 32},
    {20, 40},
    {22, 40},
    {24, 40},
    {26, 40},
    {28, 40},
    {30, 40},
    {32, 40},
    {34, 40}};

//uint8_t difficulty = 1;
//const uint8_t maxDif = 10;

void setup()
{
  gb.begin();
}
void loop(/* arguments */)
{
  while (!gb.update())
    ;

  if (scene == 0)
  {
    gb.display.clear();
    gb.display.fill(GREEN);
    gb.display.setCursor(5, 5);
    gb.display.setFontSize(3);
    gb.display.print("SNAKE");
    gb.display.setCursor(60, 59);
    gb.display.setFontSize(1);
    gb.display.print("v 0.3");
    //  if (gb.buttons.pressed(BUTTON_RIGHT) and difficulty < maxDif)
    // {
    //   difficulty += 1;
    //  }
    //  if (gb.buttons.pressed(BUTTON_RIGHT) and difficulty > 1)
    //  {
    //    difficulty -= 1;
    //  }
    if (gb.buttons.pressed(BUTTON_B))
    {
      scene = 1;
      for (int i = 0; i < maxTail; i++)
      {
        snakex[i] = 0;
        snakey[i] = 0;
      }
      direction = 0;
      walls = 1;
      length = 3;
      snakex[0] = 20;
      snakey[0] = 20;
      apple[0] = random(1 * width, (80 / width) - 1) * width;
      apple[1] = random(1 * width, (64 / width) - 1) * width;
      animD = 0;
    }
    if (gb.buttons.pressed(BUTTON_A))
    {
      scene = 1;
      for (int i = 0; i < maxTail; i++)
      {
        snakex[i] = 0;
        snakey[i] = 0;
      }
      direction = 0;
      walls = 0;
      length = 3;
      snakex[0] = 20;
      snakey[0] = 20;
      apple[0] = random(1 * width, (80 / width) - 1) * width;
      apple[1] = random(1 * width, (64 / width) - 1) * width;
      animD = 0;
    }
  }
  else if (scene == 2)
  {
    if (frame > 1)
    {

      if (animD <= length)
      {

        gb.display.setColor(ORANGE);
        gb.display.fillRect(snakex[animD], snakey[animD], width, width);
        animD += 1;
      }
      else
      {
        gb.display.setColor(GREEN);
        gb.display.setCursor(0, 0);
        gb.display.print("score :");
        gb.display.setCursor(30, 0);
        gb.display.print(animD - 4);
      }
      frame = 0;
    }
    frame += 1;
    if (gb.buttons.pressed(BUTTON_A))
    {
      scene = 0;
    }
  }
  else if (scene == 1)
  {
    if (gb.buttons.pressed(BUTTON_UP) && direction % 2 != 1)
    {
      askedDir = 3;
    }
    else if (gb.buttons.pressed(BUTTON_DOWN) && direction % 2 != 1)
    {
      askedDir = 1;
    }

    else if (gb.buttons.pressed(BUTTON_RIGHT) && direction % 2 == 1)
    {
      askedDir = 0;
    }

    else if (gb.buttons.pressed(BUTTON_LEFT) && direction % 2 == 1)
    {
      askedDir = 2;
    }
    if (frame > 1)
    {
      direction = askedDir;
      if (snakex[0] == apple[0] && snakey[0] == apple[1])
      {
        length += 1;
        eatApple();
      }
      if (length >= 50)
      {
        if (snakex[0] == apple2[0] and snakey[0] == apple2[1])
        {
          length += 1;
          eatApple2();
        }
      }

      frame = 0;
      for (int i = 0; i < length; i++)
      {
        snakex[length - i] = snakex[length - i - 1];
        snakey[length - i] = snakey[length - i - 1];
      }
      switch (direction)
      {
      case 0:
        snakex[0] += width;
        break;
      case 1:
        snakey[0] += width;
        break;

      case 2:
        snakex[0] -= width;
        break;
      case 3:
        snakey[0] -= width;
        break;
      }

      gb.display.clear();

      gb.display.setColor(GREEN);
      for (int i = 1; i <= length; i++)
      {
        gb.display.fillRect(snakex[i], snakey[i], width, width);
      }
      if (walls == 1)
      {
        gb.display.setColor(WHITE);
        for (int i = 0; i < 20; i++)
        {
          gb.display.fillRect(wallBlocks[i][0], wallBlocks[i][1], 2, 2);
        }
      }
      gb.display.setColor(RED);
      gb.display.fillRect(apple[0], apple[1], width, width);
      if (length >= 50)
      {
        gb.display.fillRect(apple2[0], apple2[1], width, width);
      }
      gb.display.setColor(YELLOW);
      gb.display.fillRect(snakex[0], snakey[0], width, width);
      for (int i = 1; i <= length; i++)
      {
        if (snakex[i] == snakex[0] and snakey[i] == snakey[0])
        {
          scene = 2;
        }
      }
      if (walls == 1)
      {
        for (int i = 0; i < 20; i++)
        {
          if (wallBlocks[i][0] == snakex[0] and wallBlocks[i][1] == snakey[0])
          {
            scene = 2;
          }
        }
      }
      if (snakex[0] >= 80 or snakey[0] >= 64 or snakex[0] < 0 or snakey[0] < 0)
      {
        scene = 2;
      }
    }
    frame += 1;
  }
}
void eatApple()
{

  apple[0] = random(1 * width, (80 / width) - 1) * width;
  apple[1] = random(1 * width, (64 / width) - 1) * width;
  if (walls == 1)
  {
    for (int i = 0; i < 20; i++)
    {
      if (apple[0] == wallBlocks[i][0] and apple[1] == wallBlocks[i][1])
      {
        eatApple();
      }
    }
  }
  if (length == 50)
  {
    eatApple2();
  }
}
void eatApple2()
{

  apple2[0] = random(1 * width, (80 / width) - 1) * width;
  apple2[1] = random(1 * width, (64 / width) - 1) * width;

  if (walls == 1)
  {
    for (int i = 0; i < 20; i++)
    {
      if (apple2[0] == wallBlocks[i][0] and apple2[1] == wallBlocks[i][1])
      {
        eatApple2();
      }
    }
  }
}