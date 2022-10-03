
#include "raylib.h"
#include <list>
#include<string>



using   std::list;
using   std::string;

#define NO_MORE_FRAMES -1


class AnimationCycle{
    private:
        bool infiniteAnimation;
        int width;
        int height;
        list<Texture> frames=list<Texture>(); 
        list<Texture>::iterator currentFrame;

        void addFrameFromPng(string path);
        void addFramesFromDirectory(char *path);


    public:
        
        bool isActive=false;
        
        AnimationCycle();
        AnimationCycle(int width,int height,char *path,
        bool infiniteAnimation);
       
        void resetAnimation();
        int nextFrame(); //returns -1 if there no frames more and we reset to first frame
        void draw(int x,int y);
        void freeResources();
        void drawAllFrames();
        bool isAnimationInfinite();





};