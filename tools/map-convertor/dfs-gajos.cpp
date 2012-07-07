#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE_X 20
#define SIZE_Y 20

#define CELL_X 15
#define CELL_Y 15

enum direction
{
  up = 1,
  down = 2,
  right = 4,
  left = 8
};

//#define RANDOM_BLOCK ((!(rand()%(CELL_Y * CELL_X * 2)))?'X':' ')
//#define RANDOM_BLOCK ((!(rand()%((CELL_Y - 5) * (CELL_X - 4) + int(lenght * 0.5))))?'X':' ')
#define RANDOM_BLOCK ((!(rand()%(8 + int(lenght / 5))))?'X':' ')

struct cell
{
  unsigned walls;
  int lenght; // from beginning
  
  bool visited;
  
  
  cell() : walls(up | down | right | left), visited(false) {}
  
  bool has_wall(direction d)
  {
    return walls & d;
  }
  
  void break_wall(direction d)
  {
    walls = ~(~walls | d);
  }
  
  void fill_row(char * buf, int row)
  {
    if(row < 3 || row > CELL_Y - 3)
      for(int i = 0; i < CELL_X; i++)
        buf[i] = ' ';
    else
      for(int i = 0; i < CELL_X; i++)
        buf[i] = (i == 1 || i == CELL_X - 2) ? ' ' : RANDOM_BLOCK;
      
    if(has_wall(up))
    {
      int i0 = 0, i1 = 1;      
      if(row == i0)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = 'O';
      if(row == i1)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = '-';
      //
    }
    if(has_wall(down))
    {
      int i0 = CELL_Y - 1, i1 = CELL_Y - 2;
      if(row == i0)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = 'O';
      if(row == i1)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = '-';
    }

    
    //
    if(has_wall(left))
    {
      int i0 = 0, i1 = 1;
      
      buf[i0] = 'O';
      if(buf[i1] == ' ')
        buf[i1] = '-';
    }
    if(has_wall(right))
    {
      int i0 = CELL_X - 1, i1 = CELL_X - 2;
      
      buf[i0] = 'O';
      if(buf[i1] == ' ')
        buf[i1] = '-';
    }
    
    if(row == 0 || row == CELL_Y - 1)
    {
      buf[0] = 'O';
      buf[CELL_X-1] = 'O';
      buf[1] = '-';      
      buf[CELL_X-2] = '-';
    }
    if(row == 1 || row == CELL_Y - 2)
    {
      buf[0] = '-';
      buf[CELL_X-1] = '-';
      buf[1] = '-';      
      buf[CELL_X-2] = '-';
    }
  }
};


// ---
cell maze[SIZE_X][SIZE_Y];

direction random_dir()
{

  return direction(1 << rand() % 4);
}

bool offset(direction d, int& x, int& y)
{
  switch(d)
  {
    case up: y--; break;
    case down: y++; break;
    case right: x++; break;
    case left: x--; break;
  }
  if(x >= SIZE_X || x < 0 || y >= SIZE_Y || y < 0)
    return false;
  return true;
}



direction opposite(direction d)
{
  switch(d)
  {
    case up: return down;
    case down: return up;
    case right: return left;
    case left: return right;
  }  
}

static int endx, endy, endlen = 0;


void fill_maze(int x, int y, int lenght = 0)
{
  cell& cur = maze[x][y];
  cur.visited = true;
  cur.lenght = lenght;
  if(lenght > endlen)
  {
    endx = x;
    endy = y;
    endlen = lenght;
  }
  for(int i = 0; i < 30; i++) // all directions in random order
  {
    direction dir = random_dir();
    int cx = x, cy = y; // neightbor
    if(!offset(dir, cx, cy))
      continue;
    cell& n = maze[cx][cy];
    if(n.visited)
      continue;
    
    // make path
    cur.break_wall(dir);
    n.break_wall(opposite(dir));
    
    
    // recursion
    fill_maze(cx, cy, lenght + 1);
  }
}

void fill_special_row(char * buf, int row, char filler_spawn, char filler_start) // start, end
{
  for(int i = 0; i < CELL_X; i++)
    buf[i] = filler_spawn;
  int centerx = (CELL_X / 2);
  int centery = (CELL_Y / 2);
  if(row != centery) 
  {
    // shell
    buf[0] = 'O';
    buf[CELL_X-1] = 'O';
    
    // start
    buf[centerx] = filler_start;
  }
  else
  {
    for(int i = 0; i < CELL_X; i++)
      buf[i] = filler_start;
  }
  if(row == 0 || row == CELL_Y - 1)
  {
    for(int i = 0; i < CELL_X; i++)
    {
      if(i != centerx)
        buf[i] = 'O';
      else
        buf[i] = filler_start;
    }
  }

}


int main()
{
  srand(time(0));
  //srand(0);
  
  // start(end) point 
  
  int startx = rand() % SIZE_X;
  int starty = rand() % SIZE_Y;
  fill_maze(startx, starty);
  // maze is filled
  std::cout << endlen << std::endl;
  
  // output
  
  std::ofstream out("maze.txt");
  out << SIZE_X * CELL_X << ' ' << SIZE_Y * CELL_Y << '\n';
  
  for(int y = 0; y < SIZE_Y; y++)
  {
    for(int row = 0; row < CELL_Y; row++)
    {
      char row_buf[CELL_X+1];
      row_buf[CELL_X] = '\0';
      for(int x = 0; x < SIZE_X; x++)
      {
        cell& cur = maze[x][y];
        if(x == startx && y == starty)
          fill_special_row(row_buf, row, 'S', 's');
        else if(x == endx && y == endy)
          fill_special_row(row_buf, row, ' ', 'e');
        else
        {
          cur.fill_row(row_buf, row);
        }
        
        out << row_buf;
      }
      
      out << '\n';
    }
    //out << '\n';
  }
  
  //for(int i = 0; i < SIZE_X * CELL_X; i++)
    //out << '.';
  //out << '\n';
  
  return 0;
}

