#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include <vector>
#include "cocos2d.h"
class HelloWorldHud;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void setViewPointCenter(cocos2d::Point __position); 

	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event); 

	void setPlayerPosition(cocos2d::Point position); 

	cocos2d::Point tileCoordForPosition(cocos2d::Point position); 

	void addEnemyAtPos(cocos2d::Point pos);

	void animateEnemy(cocos2d::Sprite *enemy);

	void enemyMoveFinished(cocos2d::Ref *pSender) ;

	void projectileMoveFinished(cocos2d::Ref *pSender);

private:
	cocos2d::TMXTiledMap* tile_map_;

	cocos2d::TMXLayer* background_;

	cocos2d::Sprite* player_;

	cocos2d::TMXLayer*	_blockage;

	cocos2d::TMXLayer *_foreground;

	int _numCollected; 
	static HelloWorldHud *_hud;

	std::vector<cocos2d::Sprite*>	_enemies;

};

#endif // __HELLOWORLD_SCENE_H__
