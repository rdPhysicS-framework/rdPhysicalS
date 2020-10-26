#ifndef	__REAL_TIME_H__
#define	__REAL_TIME_H__

#include "..\rdps.h"


class RealTime : public rdps::SceneBase
{
private:
	int id1;
	int id2;

public:
	RealTime();
	~RealTime();

	virtual void Init();
	virtual void Update(const float secs);
};

#endif//__REAL_TIME_H__
