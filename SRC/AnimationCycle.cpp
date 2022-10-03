#include "AnimationCycle.h"
#include <list>

#include <iostream>
#include <dirent.h>
#include <sys/types.h>

using std::list;

AnimationCycle::AnimationCycle(){
    
}

AnimationCycle::AnimationCycle(int width,int height,char *path,
            bool infiniteAnimation){
    this->width=width;
    this->height=height;
    this->infiniteAnimation=infiniteAnimation;

    
    addFramesFromDirectory(path);
   

}

void AnimationCycle::addFrameFromPng(string path){
    Image image=LoadImage(path.c_str());
    ImageResize(&image,width,height);
    
    Texture frame=LoadTextureFromImage(image);
    
    frames.push_back(frame);
    UnloadImage(image);
}

void AnimationCycle::resetAnimation(){
    currentFrame=frames.begin();
}

int AnimationCycle::nextFrame(){
    currentFrame++;
    if(currentFrame==frames.end()){
         
             resetAnimation();
             return NO_MORE_FRAMES;       
    } 

    return 0;     
        
}
   



void AnimationCycle::draw(int x,int y){
    DrawTexture(*currentFrame,x,y,WHITE);

}

void AnimationCycle::freeResources(){
    for( list<Texture>::iterator frame=frames.begin();frame!=frames.end();frame++){
        UnloadTexture(*frame);
    }
    frames.clear();
}

void AnimationCycle::drawAllFrames(){
int x=10;
int y=10;



    for( list<Texture>::iterator frame=frames.begin();frame!=frames.end();frame++){
        DrawRectangle(x,y,40,40,RED);
        DrawTexture(*frame,x,y,WHITE);
        x+=50;
   
        if(x>750){
            y+=50;
            x=10;
        }

    }
    
}




bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


void AnimationCycle::addFramesFromDirectory(char *path){
    
   
    DIR *dr;
    struct dirent *f;

    dr=opendir(path);
    printf("IN dir\n");
    if(dr){
        while( (f=readdir(dr)) !=NULL){
          
           string spath=string(path);
           string sname=string(f->d_name);
           
           if(hasEnding(sname,"png")){
                addFrameFromPng((spath+"\\"+sname).c_str());
           }    
           
        }

        closedir(dr);
    resetAnimation();
     
}
}


bool  AnimationCycle::isAnimationInfinite(){
    return infiniteAnimation;
}
















