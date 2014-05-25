#include "HelloWorldHud.h"

using namespace cocos2d;

void HelloWorldHud::numCollectedChanged( int numCollected )
{
	char showStr[20];     
	sprintf(showStr, "%d", numCollected);    
	label->setString(showStr); 
}

bool HelloWorldHud::init()
{
	if (!Layer::init())    
	{         
		return false;    
	}       
	auto visibleSize = Director::getInstance()->getVisibleSize();     
	label = LabelTTF::create("0", "fonts/Marker Felt.ttf", 18.0f, Size(50, 20), TextHAlignment::RIGHT);    
	label->setColor(Color3B(0, 0, 0));     
	int margin = 10;    
	label->setPosition(visibleSize.width - (label->getDimensions().width / 2) - margin, label->getDimensions().height / 2 + margin);    
	this->addChild(label);       return true; 
}
