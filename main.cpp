#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

int main()
{
  const int WINDOW_WIDTH = 750;
  const int WINDOW_HEIGHT = 750;
  const int CELL_SIZE = 15;
  int FPS = 12; //It is a upper limit of frames
  Color GREY = {29,29,29,255};// struct raylib_Color = {red, green, blue, alpha} >=255

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Game of Life");
  SetTargetFPS(FPS);
  Simulation simulation(WINDOW_WIDTH,WINDOW_HEIGHT,CELL_SIZE);

  
  // Simulation Loop

  // Event Handling -> Updating State -> Drawing Objects
  while(WindowShouldClose() == false)
  {
    // 1. Event Handling
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      Vector2 mousePosition = GetMousePosition();
      int row = mousePosition.y / CELL_SIZE;
      int column = mousePosition.x / CELL_SIZE;
      simulation.ToggleCell(row,column);
    }
    if(IsKeyPressed(KEY_ENTER))
    {
      simulation.Start();
      SetWindowTitle("Bruh Chill, Game of Life is running ...");
    }
    else if(IsKeyPressed(KEY_SPACE))
    {
      simulation.Stop();
      SetWindowTitle("Game of Life has been Paused :(");
    }
    else if (IsKeyPressed(KEY_F))
    {
        FPS += 2;
        SetTargetFPS(FPS);
    }
    else if(IsKeyPressed(KEY_S))
    {
      if(FPS > 5)
      {
        FPS -= 2;
        SetTargetFPS(FPS);
      }
    }
    else if (IsKeyPressed(KEY_R))
    {
      simulation.CreateRandomState();
    }
    else if (IsKeyPressed(KEY_C))
    {
      simulation.ClearGrid();
    }
    // 2. Updating State
    simulation.Update();
    // 3. Drawing
    BeginDrawing();
    ClearBackground(GREY);
    simulation.Draw();
    EndDrawing();
  }
  CloseWindow();
}
