#ifndef	__TEST_H__
#define	__TEST_H__

#include "..\rdps-frwk\base\SceneBase.h"

RDPS_BEGIN

	class Test : public FRWK SceneBase
	{
	private:
		int id;

	public:
		Test();
		~Test();

		virtual void Init();
		virtual void Update(const float secs);
	};

RDPS_END

#endif//__TEST_H__