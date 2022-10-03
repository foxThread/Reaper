
#include "Reaper.h"
#include <list>


using std::list;

Reaper::Reaper(){
   
}





void Reaper::init(){
    walkForth=AnimationCycle(400,400,
    "E:\\raylib\\mygame\\res\\reaper\\walking",true);
    kicking=AnimationCycle(400,400,
    "E:\\raylib\\mygame\\res\\reaper\\slashing",false);
    jumpStart=AnimationCycle(400,400,
    "E:\\raylib\\mygame\\res\\reaper\\JumpStart",false);
    jumpLoop=AnimationCycle(400,400,
    "E:\\raylib\\mygame\\res\\reaper\\JumpLoop",true);




    framesPerSecond=60;
    frameDuration=(float)1/(float)framesPerSecond;


   

   
    x=0;
    y=100;
    startWalkForth();
    walkForth.isActive=false;
    jumpHeight=20;
    platformY=y;
    
    
  

}

void Reaper::startWalkForth(){
    
    walkForth.isActive=true;
    walkForth.resetAnimation();
    currentWalkingAnimation=&walkForth;
    currentActionAnimation=NULL;
  
}


void Reaper::startKick(){
    kicking.isActive=true;
    kicking.resetAnimation();
    currentActionAnimation=&kicking;
 
}

void Reaper::startJump(){
    startWalkForth();
    currentActionAnimation=NULL;

   
    
    
    isJumping=true;
    jumpProgress=0;


 
}

void Reaper::stopJump(){
    stopWalking();
    startWalkForth();
    walkForth.isActive=false;

}


void Reaper::stopWalking(){
    currentWalkingAnimation->resetAnimation();
    currentWalkingAnimation->isActive=false;
}

void Reaper::draw()
{
    timeFromLastFrame += GetFrameTime();

    if(currentActionAnimation !=NULL){
            currentActionAnimation->draw(x,y);
            
    } else {
            currentWalkingAnimation->draw(x,y);
    }

           
    if (timeFromLastFrame > frameDuration){
        if(currentActionAnimation !=NULL){
            
            if(currentActionAnimation->nextFrame()==NO_MORE_FRAMES){
                currentActionAnimation=NULL;
            }
        } 
        
        
        else if(currentWalkingAnimation->isActive) {
            
            if(currentWalkingAnimation->nextFrame()==NO_MORE_FRAMES){
                currentWalkingAnimation->resetAnimation();
            }
    
    
        }

        timeFromLastFrame = 0;
               


    }




}


   

void Reaper::setAnimationStatus(int status){
    animationStatus=status;
}


void Reaper::stepRight(){
    x+=5;
}

void Reaper::stepLeft(){
    x-=5;
}


void Reaper::setJumpHeight(int jumpHeight){
    this->jumpHeight=jumpHeight;
    jh2=jumpHeight*2;
}

void Reaper::continueJump(){
    if(isJumping){
        jumpProgress++;
        
        if(jumpProgress>jumpHeight*2){
            isJumping=false;
            y=platformY;


        }
        
        if(jumpProgress>jumpHeight){
            y+=5;
        } else {
            y-=5;
        }
    }


}


void Reaper::destroy(){
    walkForth.freeResources();

}




