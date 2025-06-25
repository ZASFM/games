#include <iostream>
using namespace std;

#include "olcConsoleGameEngine.h"

class OneLoneCoder_FormulaOLC:public olcConsoleGameEngine{
public:
   OneLoneCoder_FormulaOLC(){
      m_sAppName = L"Formula OLC"
   }
protected:
   virtual bool onUserCreate(){
      return false;
   }
   virtual bool OneUserUpdate(float fElapsedTime){
      for(int y=0;y<ScreenHeight()/2;y++){
         for(int x=0;x<ScreenWidth();x++){
            float fMiddlePoint = 0.5f;
            float fRoadWidth = 0.6f;
            float fClipWidth=fRoadWidth*0.15f;

            fRoadWidth*=0.5f;
         }
      }
      return true;
   }
};

int main(){
   OneLoneCoder_FormulaOLC game;
   game.ConstructConsole(160,100,8,8);
   game.Start();
   return 0;
}