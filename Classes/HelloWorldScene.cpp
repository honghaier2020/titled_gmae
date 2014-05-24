#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	std::string __file = "02.tmx";
	auto __str = String::createWithContentsOfFile (FileUtils::getInstance()->fullPathForFilename(__file.c_str()).c_str());
	tile_map_ = TMXTiledMap::createWithXML(__str->getCString(),"");
	background_ = tile_map_->layerNamed("Background");
	addChild(tile_map_, -1);

	TMXObjectGroup* __objects = tile_map_->getObjectGroup("Object-Player"); 
	CCASSERT(NULL != __objects, "'Object-Player' object group not found"); 
	auto player_showup_point = __objects->getObject("PlayerShowUpPoint"); 
	CCASSERT(!player_showup_point.empty(), "PlayerShowUpPoint object not found"); 
	int __x = player_showup_point["x"].asInt();  
	int __y = player_showup_point["y"].asInt(); 

	player_ = Sprite::create("029.png");  
	player_->setPosition(__x + tile_map_->getTileSize().width / 2, __y + tile_map_->getTileSize().height / 2);  
	player_->setScale(0.5);     
	addChild(player_); 
	setViewPointCenter(player_->getPosition()); 

	_blockage = tile_map_->layerNamed("Blockage01");
	_blockage->setVisible(false);

	_foreground = tile_map_->getLayer("Foreground01");

	auto listener = EventListenerTouchOneByOne::create();  
	listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};  
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);  
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); 
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::setViewPointCenter( cocos2d::Point __position )
{
	auto __win_size = Director::getInstance()->getWinSize();         
	int __x = MAX(__position.x, __win_size.width / 2);     
	int __y = MAX(__position.y, __win_size.height / 2);     
	__x = MIN(__x, (tile_map_->getMapSize().width * this->tile_map_->getTileSize().width) - __win_size.width / 2);     
	__y = MIN(__y, (tile_map_->getMapSize().height * tile_map_->getTileSize().height) - __win_size.height / 2);     
	auto __actual_position = Point(__x, __y);         
	auto __center_of_view = Point(__win_size.width / 2, __win_size.height / 2);     
	auto __view_point = __center_of_view - __actual_position;     
	this->setPosition(__view_point); 
}

void HelloWorld::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused_event )
{
	auto actionTo1 = RotateTo::create(0, 0, 180);  
	auto actionTo2 = RotateTo::create(0, 0, 0);  
	auto touchLocation = touch->getLocation();     
	touchLocation = this->convertToNodeSpace(touchLocation);      
	auto playerPos = player_->getPosition();  
	auto diff = touchLocation - playerPos;  
	if (abs(diff.x) > abs(diff.y)) 
	{  
		if (diff.x > 0) 
		{ 
			playerPos.x += tile_map_->getTileSize().width / 2;  
			player_->runAction(actionTo2); 
		}  
		else
		{  
			playerPos.x -= tile_map_->getTileSize().width / 2; 
			player_->runAction(actionTo1); 
		} 
	}  
	else
	{  
		if (diff.y > 0)
		{    
			playerPos.y += tile_map_->getTileSize().height / 2;   
		}  
		else 
		{   
			playerPos.y -= tile_map_->getTileSize().height / 2;  
		} 
	}     
	if (playerPos.x <= (tile_map_->getMapSize().width * tile_map_->getMapSize().width) &&   playerPos.y <= (tile_map_->getMapSize().height * tile_map_->getMapSize().height) &&   playerPos.y >= 0 &&   playerPos.x >= 0)  
	{   
		this->setPlayerPosition(playerPos);     
	}      
	this->setViewPointCenter(player_->getPosition()); 
}

void HelloWorld::setPlayerPosition( cocos2d::Point position )
{
	if(0)
	{
		player_->setPosition(position); 
	}
	else
	{
		Point tileCoord = this->tileCoordForPosition(position); 
		int tileGid = _blockage->getTileGIDAt(tileCoord); 
		if (tileGid) { 
			auto properties = tile_map_->getPropertiesForGID(tileGid).asValueMap(); 
			if (!properties.empty()) 
			{ 
				auto collision = properties["Blockage"].asString();
				if ("true" == collision) 
				{ 
					return; 
				} 
				auto collectable = properties["Collectable"].asString(); 
				if ("true" == collectable)
				{    
					_blockage->removeTileAt(tileCoord); 
					_foreground->removeTileAt(tileCoord);     
				}
			} 


		} 
		player_->setPosition(position); 
	}
}

cocos2d::Point HelloWorld::tileCoordForPosition( cocos2d::Point position )
{
	int x = position.x / tile_map_->getTileSize().width;  
	int y = ((tile_map_->getMapSize().height * tile_map_->getTileSize().height) - position.y) / tile_map_->getTileSize().height;  
	return Point(x, y); 
}
