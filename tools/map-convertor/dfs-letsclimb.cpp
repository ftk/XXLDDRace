#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE_X 30 // amount of cells horizontally
#define SIZE_Y 45 

#define CELL_X 9
#define CELL_Y 9 // amount of tiles in each cell vertically

enum direction
{
  up = 1,
  down = 2,
  right = 4,
  left = 8
};

#define RANDOM_BLOCK ((!(rand()%(50 + (SIZE_Y - self_y))))?'X':' ')

struct cell
{
  unsigned walls;
  int lenght; // from beginning
  
  bool visited;
  
  int self_x, self_y;
  
  
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
    if(row < 2 || row > CELL_Y - 2)
      for(int i = 0; i < CELL_X; i++)
        buf[i] = ' ';
    else
      for(int i = 0; i < CELL_X; i++)
        buf[i] = /*(i == 1 || i == CELL_X - 2) ? ' ' :*/ RANDOM_BLOCK;
      
    if(has_wall(up))
    {
      int i0 = 0, i1 = 1;      
      if(row == i0)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = '-';
      /*if(row == i1)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = '-';*/
      //
    }
    if(has_wall(down))
    {
      int i0 = CELL_Y - 1, i1 = CELL_Y - 2;
      if(row == i0)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = '-';
      /*if(row == i1)
        for(int i = 0; i < CELL_X; i++)
          buf[i] = '-';*/
    }

    
    //
    if(has_wall(left))
    {
      int i0 = 0, i1 = 1;
      
      buf[i0] = '-';
      /*if(buf[i1] == ' ')
        buf[i1] = '-';*/
    }
    if(has_wall(right))
    {
      int i0 = CELL_X - 1, i1 = CELL_X - 2;
      
      buf[i0] = '-';
      /*if(buf[i1] == ' ')
        buf[i1] = '-';*/
    }
    
    if(row == 0 || row == CELL_Y - 1)
    {
      buf[0] = '-';
      buf[CELL_X-1] = '-';
      /*
      buf[1] = '-';      
      buf[CELL_X-2] = '-';*/
    }
    /*
    if(row == 1 || row == CELL_Y - 2)
    {
      buf[0] = '-';
      buf[CELL_X-1] = '-';
      buf[1] = '-';      
      buf[CELL_X-2] = '-';
    }*/
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
  cur.self_x = x; cur.self_y = y;
  
  if(y > endy || (y == endy && lenght > endlen)) // the longest & the lowest
  {
    endx = x;
    endy = y;
    endlen = lenght;
  }
  for(int i = 0; i < 5; i++) // all directions in random order
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

void fill_special_row(char * buf, int row, char filler_spawn, char filler_start, char filler_exit) // start, end
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
      if(i == 0 || i == CELL_X - 1)
        buf[i] = filler_exit;
      else
        buf[i] = filler_start;
  }
  if(row == 0 || row == CELL_Y - 1)
  {
    for(int i = 0; i < CELL_X; i++)
    {
      if(i != centerx)
        buf[i] = 'O';
      else
        buf[i] = filler_exit;
    }
  }

}


int main()
{
  srand(time(0));
  //srand(0);
  
  // start(end) point 
  
  int startx = rand() % SIZE_X;
  int starty = 0;
  fill_maze(startx, starty);
  // maze is filled
  std::cout << endlen << std::endl; // finish, not start !
  
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
          fill_special_row(row_buf, row, ' ', ' ', 'e');
        else if(x == endx && y == endy)
          fill_special_row(row_buf, row, 'S', 's', 'h');
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

