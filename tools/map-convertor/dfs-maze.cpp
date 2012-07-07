#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>


enum direction
{
  up = 1,
  down = 2,
  right = 4,
  left = 8
};

#define SIZE_X 80
#define SIZE_Y 100


struct cell
{
  unsigned walls;
  int ident; // start , end, ...
  
  bool visited;
  
  
  cell() : walls(up | down | right | left), ident(0), visited(false) {}
  
  bool has_wall(direction d)
  {
    return walls & d;
  }
  
  void break_wall(direction d)
  {
    walls = ~(~walls | d);
  }
};


// ---
cell maze[SIZE_X][SIZE_Y];

direction random_dir()
{
  int r = rand() % 4;
  switch(r)
  {
    case 0: return up;
    case 1: return down;
    case 2: return right;
    case 3: return left;
  }
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

#define RAND_FREEZE ((!(rand()%40))?'-':' ')

int main()
{
  srand(time(0));
  
  // start(end) point 
  
  int startx = rand() % SIZE_X;
  int starty = rand() % SIZE_Y;
  fill_maze(startx, starty);
  // maze is filled
  std::cout << endlen << std::endl;
  
  char buffer[SIZE_Y * 3][SIZE_X * 3 + 1]; // each cell is 3x3 tiles
  for(int y = 0; y < SIZE_Y; y++)
  {
    int by = y * 3;
    for(int x = 0; x < SIZE_X; x++)
    {
      int bx = x * 3;
      
      cell& cur = maze[x][y];
      
      // fill corners
      /*
       * X-X
       * ---
       * X-X
       * */
      buffer[by][bx] = buffer[by+2][bx] = buffer[by][bx+2] = buffer[by+2][bx+2] = 'X';
      
      // fill walls
      buffer[by][bx+1] =  cur.has_wall(up) ? 'O' : RAND_FREEZE;
      buffer[by+2][bx+1] =  cur.has_wall(down) ? 'O' : RAND_FREEZE;
      buffer[by+1][bx] =  cur.has_wall(left) ? 'O' : RAND_FREEZE;
      buffer[by+1][bx+2] =  cur.has_wall(right) ? 'O' : RAND_FREEZE;
      
      // center is empty
      buffer[by+1][bx+1] = ' ';
    }
    buffer[by][SIZE_X * 3] = buffer[by+1][SIZE_X * 3] = buffer[by+2][SIZE_X * 3] = buffer[by+3][SIZE_X * 3] = '\0'; // end of line
  }
  
  for(int y = 0; y < 3; y++)
    for(int x = 0; x < 3; x++)
    {
      buffer[starty * 3 + y][startx * 3 + x] = ((y == 2) ? 's' : 'S');
      buffer[endy * 3 + y][endx * 3 + x] = 'e';
    }
  //buffer[endy * 3 + 1][endx * 3 + 1] = 'e';
  
  // output
  
  std::ofstream out("maze.txt");
  out << SIZE_X * 3 << ' ' << SIZE_Y * 3 << '\n';
  for(int y = 0; y < SIZE_Y * 3; y++)
    out << buffer[y] << '\n';
  
  return 0;
}

