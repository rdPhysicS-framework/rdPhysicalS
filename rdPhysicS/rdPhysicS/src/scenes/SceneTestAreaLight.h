#ifndef	__SCENE_TEST_AREA_LIGHT_H__
#define	__SCENE_TEST_AREA_LIGHT_H__

#include "..\rdps.h"

class SceneTestAreaLight : public rdps::SceneBase
{
public:
	SceneTestAreaLight();
	~SceneTestAreaLight();

	virtual void Init();
	virtual void Update(const float secs);
};

#endif//__SCENE_TEST_AREA_LIGHT_H__
