#include <iostream>
#include <time.h>
//#include <conio.h>
#include <termios.h> 
#include <unistd.h>  

using namespace std;

//possible directions and positions
enum eDir{ 
   STOP = 0, 
   LEFT = 1, 
   UPLEFT = 2, 
   DOWNLEFT = 3, 
   RIGHT = 4, 
   UPRIGHT = 5, 
   DOWNRIGHT = 6
};

class cBall{
private:
   //pos of ball in screen   
   int x,y;
   int originalX, originalY;
   eDir direction;
public:
   //constructor, saves original position, so we can reset game later
   cBall(int posX, int posY){
      originalX=posX;
      originalY=posY;
      x=posX; y=posY;
      direction=STOP;
   }
   
   void Reset(){
      x=originalX; y=originalY;
      direction=STOP;  
   }

   //funcs for changing direction
   void changeDirection(eDir d){
      direction=d;
   }
   //funcs to get x and y
   inline int getX(){return x;}
   inline int getY(){return y;}
   inline eDir getDirection(){return direction;}

   //to have random directions 1-6
   void randomDirection(){
      direction=(eDir)(rand()%6+1);
   }

   //moving functions, in a polar coordinates, follows the classic cartesian movement from origin (0,0) 
   void Move(){
      switch(direction){
         case STOP:
            break;
         case LEFT:
            x--;
            break;
         case RIGHT:
            x++;
            break;
         case UPLEFT:
            x--; y--;
            break;
         case DOWNLEFT:
            x--; y++;
            break;
         case UPRIGHT:
            x++;y--;
            break;
         case DOWNRIGHT:
            x++;y++;
            break;
         default:
            break;
      }
   }

   friend ostream& operator<<(ostream& out, cBall c){
      out<<"Paddle ["<<c.x<<","<<c.y<<"]["<<c.direction<<"]"<<endl;
      return out;
   }
};

class cPaddle{
private:
   int x,y;
   int originalX, originalY;
public:
   cPaddle(){x=y=0;}
   cPaddle(int posX, int posY):cPaddle(){
      originalX=posX;
      originalY=posY;
      x=posX;
      y=posY;
   }    
   inline void Reset(){x=originalX;y=originalY;}
   inline int getX(){return x;}
   inline int getY(){return y;}
   inline void moveUp(){y--;}
   inline void moveDown(){y++;}
   friend ostream& operator<<(ostream& out, cPaddle c){
      out<<"Ball ["<<c.x<<","<<c.y<<"]"<<endl;
      return out;
   }
};

class cGameManager{
private:
   int width,height;
   int score1, score2;
   char up1, down1, up2, down2;
   bool quit;
   cBall * ball;
   cPaddle * player1; 
   cPaddle * player2; 

public:
   cGameManager(int w, int h){
      srand(time(NULL));
      quit=false;
      up1='w'; up2='i';
      down1='s', down2='k';
      score1=score2=0;
      width=w; height=h;
      ball=new cBall(w/2,h/2);
      player1= new cPaddle(1,h/2-3);
      player2=new cPaddle(w-2,h/2-3);
   }
   ~cGameManager(){
      delete ball, player1, player2;
   }
   void scoreUp(cPaddle * player){
      //here if else block checks, the addresses of the player, if the address of the player im passing matches the player1 or player2
      if(player==player1){
         //based on if address of player matches player1, i increment the score of player1
         score1++;
      }else if (player==player2){
         //based on if address of player matches player2, i increment the score of player2
         score2++;
      }
      ball->Reset();
      player1->Reset();
      player2->Reset();
   }
};

int main(){
   
   cBall c(0,0);
   cout<<c<<endl;
   c.randomDirection();
   cout<<c<<endl;
   c.Move();
   cout<<c<<endl;
   c.randomDirection();
   c.Move();
   cout<<c<<endl;

   cPaddle p1(0,0);
   cPaddle p2(0,0);
   cout<<p1<<endl;
   cout<<p2<<endl;
   p1.moveUp();
   p1.moveDown();
   cout<<p1<<endl;
   cout<<p2<<endl;
   return 0;
}