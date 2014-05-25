#ifndef HelloWorldHud_h__
#define HelloWorldHud_h__
#include "cocos2d.h"

class HelloWorldHud : public cocos2d::Layer 
{ 
	public:     
		void numCollectedChanged(int numCollected);     
		virtual bool init();     
		CREATE_FUNC(HelloWorldHud);       
		cocos2d::LabelTTF *label; 
private:

};
#endif // HelloWorldHud_h__
