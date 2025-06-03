#include <iostream>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


using namespace std;


//simulates _kbhit()
int kbhit() {
    termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // disable buffering
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

//simulates _getch()
char getch() {
    char buf = 0;
    termios old = {};
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcgetattr()");
    termios newt = old;
    newt.c_lflag &= ~(ICANON | ECHO); // disable buffering
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0)
        perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}


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

   void Draw(){
      system("cls");
      for(int i=0;i<width+2;i++){
         cout<<"#";
      }
      cout<<endl;
      for(int i=0;i<height;i++){
         for(int j=0;j<width;j++){
            int ballx=ball->getX();
            int bally=ball->getY();
            int player1x=player1->getX();
            int player2x=player2->getX();
            int player1y=player1->getY();
            int player2y=player2->getY();

            if(j==0){
               cout<<"\xB2";
            }

            if(ballx==j && bally==i){
               //printin ball with o
               cout<<"O";
            }else if(player1x==j && player1y==i){
               cout<<"\xDB";//player 1
            }else if(player2x==j && player2y==i){
               cout<<"\xDB";//player 2
            }else if(player1x==j && player1y+1==i){
               cout<<"\xDB";//player 1
            }else if(player1x==j && player1y+2==i){
               cout<<"\xDB";//player 1
            }else if(player1x==j && player1y+3==i){
               cout<<"\xDB";//player 1
            }else if(player2x==j && player2y+1==i){
               cout<<"\xDB";//player 1
            }else if(player2x==j && player2y+2==i){
               cout<<"\xDB";//player 1
            }else if(player2x==j && player2y+3==i){
               cout<<"\xDB";//player 1
            }else{
               cout<<" ";
            }

            if(j==width-1){
               cout<<"\xB2";
            }
         }
         cout<<endl;
      }
      for(int i=0;i<width+2;i++){
         cout<<"\xB2";
      }
      cout<<endl;

      //printing score:
      cout<<"Score 1:"<<score1<<endl;cout<<"Score 2"<<score2<<endl;
   }

   void Input(){
      ball->Move();
      int ballx=ball->getX();
      int bally=ball->getY();
      int player1x=player1->getX();
      int player2x=player2->getX();
      int player1y=player1->getY();
      int player2y=player2->getY();

      if(kbhit()){
         char current=getch();

         if(current==up1){
            if(player1y>0){
               player1->moveUp();
            }
         }

         if(current==up2){
            if(player2y>0){
               player2->moveUp();
            }
         }

         if(current==down1){
            if(player1y+4<height){
               player1->moveDown();
            }
         }

         if(current==down2){
            if(player2y+4<height){
               player2->moveDown();
            }
         }

         if(ball->getDirection()==STOP){
            ball->randomDirection();
         }

         if(current=='q'){
            quit=true;
         }

      }
   }

   void Logic(){
      int ballx=ball->getX();
      int bally=ball->getY();
      int player1x=player1->getX();
      int player2x=player2->getX();
      int player1y=player1->getY();
      int player2y=player2->getY();

      //left paddle
      for(int i=0;i<4;i++){
         if(ballx==player1x+1){
            if(bally==player1y+i){
               ball->changeDirection((eDir)((rand()%3)+4));
            }
         }
      }

      //right paddle
      for(int i=0;i<4;i++){
         if(ballx==player2x-1){
            if(bally==player2y+i){
               ball->changeDirection((eDir)((rand()%3)+1));
            }
         }
      }

      //bottom wall
      if(bally==height-1){
         ball->changeDirection(ball->getDirection()==DOWNRIGHT?UPRIGHT:UPLEFT);
      }
      //top wall
      if(bally==0){
         ball->changeDirection(ball->getDirection()==UPRIGHT?DOWNRIGHT:DOWNLEFT);
      }
      //right wall;
      if(ballx==width-1){
         scoreUp(player1);
      }
      //left wall
      if(ballx==0){
         scoreUp(player2);
      }
   }

   void Run(){
      while(not quit){
         Draw();
         Input();
         Logic();
      }
   }
};

int main(){
   cGameManager c(40,20);
   c.Run();
   return 0;
}