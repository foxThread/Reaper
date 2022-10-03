

#include "MyGame.h"

#include "raylib.h"
#include <list>

#include<string>


using std::string;









MyGame::MyGame()
{
    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "MyGame");
    SetTargetFPS(60);
    reaper.init();
    reaper.setJumpHeight(20);
      
   
}






void MyGame::run()
{

    int walkingKeysDown=0; 
  
   
    

    while (!WindowShouldClose())
    {

   
         
         if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)){
            reaper.startWalkForth();
         }
         
         if(IsKeyDown(KEY_LEFT)){
            walkingKeysDown++;
           
            reaper.stepLeft();
            
        }
        
        
        
        if(IsKeyDown(KEY_RIGHT)){

            walkingKeysDown++;
            reaper.stepRight();

        }

        if(reaper.isJumping){
            walkingKeysDown++;
        }

        if(IsKeyPressed(KEY_SPACE)){
            reaper.startKick();
        }

         if(IsKeyPressed(KEY_LEFT_CONTROL) && !reaper.isJumping){
            reaper.startJump();
            walkingKeysDown++;
            
        }

        if(walkingKeysDown==0){
           
            reaper.stopWalking();
        }

       
        walkingKeysDown=0;
        reaper.continueJump();
        BeginDrawing();

        ClearBackground(RAYWHITE);
        reaper.draw();
       
     
       
             
       
        EndDrawing();
    }

   
    reaper.destroy();
    CloseWindow();

    
}
