#include "simulation.hpp"

void Simulation::Draw()
{
  grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
  grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbor(int row, int column)
{
  int liveNeighbors = 0;
  std::vector<std::pair<int,int>> neigborOffsets =
  {
    {-1,0}, //Directly Above
    {1,0}, //Directly Below
    {0,1}, //To the Right
    {0,-1}, //To the Left
    {-1,-1}, //Upper Left Corner
    {-1,1}, //Upper Right Corner
    {1,-1}, //Lower Left
    {1,1}  //Lower Right
  };

  for (const auto& offset : neigborOffsets) {
      int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
      int neighborColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
 
      // I'll do something with neighborRow and neighborColumn here.
      liveNeighbors += grid.GetValue(neighborRow,neighborColumn);
    }
  return liveNeighbors;
}


void Simulation::Update()
{
  if (IsRunning())
  {
    for (int row = 0; row < grid.GetRows(); row++)
    {
      for (int column = 0; column < grid.GetColumns(); column++)
      {
        int liveNeighbors = CountLiveNeighbor(row, column);
        int cellValue = grid.GetValue(row, column);
        
        if (cellValue == 1)
        {
          if (liveNeighbors > 3 || liveNeighbors < 2)
          {
            tempGrid.SetValue(row, column, 0);
          }
          else
          {
            tempGrid.SetValue(row, column, 1);
          }
        }
        else
        {
          if (liveNeighbors == 3)
          {
            tempGrid.SetValue(row, column, 1);
          }
          else
          {
            tempGrid.SetValue(row, column, 0);
          }
        }
      }
    }
    grid = tempGrid;
  }
}

void Simulation::ClearGrid()
{
  if (!IsRunning())
  {
    grid.Clear();
  }
}

void Simulation::CreateRandomState()
{
  if (!IsRunning())
  {
    grid.FillRandom();
  }
}

void Simulation::ToggleCell(int row, int column)
{
  if(!IsRunning())
  {
    grid.ToggleCell(row, column);
  }
}
