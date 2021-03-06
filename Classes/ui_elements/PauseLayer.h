/*
 * PauseLayer.h
 *
 *  Created on: Nov 13, 2013
 *      Author: "Sebastian Wilzbach <sebi@wilzbach.me>"
 */

#ifndef PAUSELAYER_H_
#define PAUSELAYER_H_

#include "cocos2d.h"
#include "../helper/SoundEffectHelper.h"



class PauseLayer : public cocos2d::CCLayer {
public:
	PauseLayer();
	virtual ~PauseLayer();

	static CCLayer* create(int level);
	int level;
	virtual bool init();
	void DrawHUD();
	void OnMenu(CCObject* pSender);
	void didSwipe(CCObject* sender);
	CREATE_FUNC(PauseLayer);
private:
	cocos2d::CCMenu* levelMenu;
};



#endif /* PAUSELAYER_H_ */
