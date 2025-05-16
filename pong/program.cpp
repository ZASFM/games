#include<iostream>

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
      out<<"Ball ["<<c.x<<","<<c.y<<"]["<<c.direction<<"]"<<endl;
      return out;
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

   return 0;
}