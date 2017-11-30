#ifndef	__TEST_H__
#define	__TEST_H__

//#include "..\rdps-frwk\base\SceneBase.h"
#include "..\rdps.h"


class Test : public rdps::SceneBase
{
private:
	int id1;
	int id2;

public:
	Test();
	~Test();

	virtual void Init();
	virtual void Update(const float secs);
};



#endif//__TEST_H__