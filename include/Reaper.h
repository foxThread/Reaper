#include "AnimationCycle.h"

#define STOPPED 0
#define ANIMATING 1






class Reaper{
    
    private:
        AnimationCycle walkForth;
        AnimationCycle kicking;
        AnimationCycle jumpStart;
        AnimationCycle jumpLoop;
        AnimationCycle *currentAnimation;
        
        AnimationCycle *currentWalkingAnimation;
        AnimationCycle *currentActionAnimation=NULL;

        
        
        

        int framesPerSecond;
        int animationStatus=STOPPED;
        float frameDuration;
        float timeFromLastFrame=0.0;
        int x,y;
        int platformY;

      
        
        int jumpProgress=0;
        int jumpHeight=20;  
        int jh2=40; 
        

        
       
    
    public:

        Reaper();
        
        
        
        void startWalkForth();
        void startKick();
        void startJump();
        void continueJump();

       



        void stopWalking();
        void stopJump();
        
        void draw();
        void init();
        void destroy();
        void setAnimationStatus(int status);
        
        void stepRight();
        void stepLeft();

        void setJumpHeight(int height);
        bool isJumping=false;
        


};