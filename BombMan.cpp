
#include <cstdlib>
#include <iostream>

#include "Windows.h"

const int TotalNum = 400;
int BombNum = 100;
char Ground = '.';

#define XA A2
#define YA A4
#define Button 3

char BombText = 'O';

char PlayerText = 'P';



char matrix[TotalNum];



int percolumn = 40;
int playerCur = 0;
int stepCount = 0;




void fillTheMatrix(char c)
{

  for(int i = 0; i < TotalNum; ++i)
  {

    matrix[i] = c;
  }
}

void genBomb()
{
  for(int j = 0 ; j < BombNum; ++j)
  {
    matrix[(rand() % TotalNum)] = BombText;
  
  }
}



void letBombManOut()
{
  std::cout << "BBBB   OOO  M   M  BBBB      M   M   A   N   N\n";
  std::cout << "B   B O   O MM MM  B   B     MM MM  A A  NN  N\n";
  std::cout << "BBBB  O   O M M M  BBBB      M M M AAAAA N N N\n";
  std::cout << "B   B O   O M   M  B   B     M   M A   A N  NN\n";
  std::cout << "BBBB   OOO  M   M  BBBB      M   M A   A N   N\n";
}


void printMat()
{
  for(int i = 0; i < TotalNum / percolumn ; ++i)
  {
    for(int j = 0; j < percolumn; ++j)
    {
      std::cout << matrix[i * percolumn + j];
      //Serial.print(matrix[i * percolumn + j]);
    }

    //Serial.println(' ');

    std::cout << ' ' << std::endl;
  
  }
  
  //Serial.println(' ');
  std::cout << ' ' << std::endl;

}
void clearScreen()
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord = {0,0};
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD charsWriten;
  DWORD consoleSize;

  GetConsoleScreenBufferInfo(hConsole,&csbi);
  consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

  FillConsoleOutputCharacter(hConsole,' ',consoleSize,coord,&charsWriten);
  SetConsoleCursorPosition(hConsole,coord);
}
void reset()
{
  clearScreen();
  playerCur = 0;
  stepCount = 0;
  letBombManOut();
  fillTheMatrix(Ground);
  genBomb();
  
  
  
  matrix[0] = Ground;
  matrix[TotalNum - 1] = 'Q';

  matrix[playerCur] = PlayerText;

}


void setup()
{
  SetConsoleOutputCP(CP_UTF8);
  // put your setup code here, to run once:
  //pinMode(3,INPUT);
  //Serial.begin(9600);
  reset();


}




// 0 died, 1 suc
void ongameEnd(int reason)
{
  if(reason == 0)
  {
    fillTheMatrix('F');
    clearScreen();
    printMat();
    
    std::cout << "输了吧，垃圾 所用步数: " << stepCount <<  std::endl;
  }
  else if(reason == 1)
  {

    fillTheMatrix('X');
    clearScreen();
    printMat();
    std::cout << "您赢了！所用步数 : " << stepCount <<  std::endl;
  }

  std::cout << "按 F 键 重开";

  while (true)
  {
    if(GetAsyncKeyState('F') & 0x8000 )
    {
      break;
    }
    else
    {
      Sleep(100);
    }

    
  }

  reset();
  
}
void move(int pos)
{
  
  matrix[playerCur] = Ground;
  if(pos == 1)
  {

    if((playerCur % percolumn) == 0)
    {
      ongameEnd(0);
      return;
    }
    --playerCur;
    
  }
  else if(pos == -1)
  {

    if(((playerCur + 1) % percolumn) == 0)
    {
      ongameEnd(0);
      return;
    }
  ++playerCur;
    
  
  }
  else if(pos == -2)
  {
   // up 
   playerCur += percolumn;
    
  }
  else 
  {
    // down
    playerCur -= percolumn;
  }
  
  stepCount++;
  

  if(playerCur < 0 || playerCur >= TotalNum)
  {
    ongameEnd(0);
    return;
  }
if(matrix[playerCur] ==BombText)
{
  ongameEnd(0);
//tone(A0,800,500);

  
  return;
  
}
  matrix[playerCur] = PlayerText;
  //printMat();

  
  if(playerCur == TotalNum - 1)
  {
    ongameEnd(1);
    return;
   }

  clearScreen();
}
void loop() 
{
  // put your main code here, to run repeatedly:

  /*int x = analogRead(X);
int y = analogRead(Y);


while(x == 1023 || x == 0 || y == 1023 || y == 0)
{
  
{
  if(x == 1023)
{
  // left
  move(-1);
}
else if(x == 0)
{
  //right
  move(1);
} else if(y == 1023)
{
 move(2); 
 }
 else
 {
  
  move(-2);
  }

printMat();

}
  //x = analogRead(X);
  //y = analogRead(Y);

}
delay(100);*/

}





int main(int argc, char* argv[])
{
  setup();
  uint32_t* f = new uint32_t();
  std::cout << "按S,D中的任意键开始，不要按A或W键，否则会撞墙而死";
  
  while (true)
    {
    if (GetAsyncKeyState('Q') & 0x8000)
    {
      std::cout << *f << std::endl;
      
      
    }
    if (GetAsyncKeyState('C') & 0x8000)
    {
      //std::cout << f << std::endl;
      
      *f+=1;
    }
    if (GetAsyncKeyState('W') & 0x8000)
    { 
      move(2);
      
      printMat();
    }

    if (GetAsyncKeyState('S') & 0x8000)
    {
      move(-2);
      printMat();
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
      move(1);
      printMat();
    }

    if (GetAsyncKeyState('D') & 0x8000)
    {
      
      move(-1);
      printMat();
    }
    
    Sleep(150);
  }
  
    
  return 0;
}
