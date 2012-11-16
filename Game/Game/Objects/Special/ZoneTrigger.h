#ifndef ZONETRIGGER
#define ZONETRIGGER

#include <global_header.h>

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class AABox;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}






namespace CloudberryKingdom
{
	class ZoneTrigger : public ObjectBase
	{
	public:
		std::shared_ptr<Lambda_1<ZoneTrigger*> > MyContainsEvent;

	private:
		std::shared_ptr<AABox> Box;

	public:
		virtual void MakeNew();

		ZoneTrigger();

		void Init( Vector2 center, Vector2 size );

		void Update();

		virtual void Reset( bool BoxesOnly );

		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );


		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef ZONETRIGGER
