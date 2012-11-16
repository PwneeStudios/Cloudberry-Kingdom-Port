#ifndef _BOXDEATH
#define _BOXDEATH

#include <global_header.h>

namespace CloudberryKingdom
{
	class AABox;
}

namespace CloudberryKingdom
{
	class Level;
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
	class _BoxDeath : public _Death
	{
	protected:
		std::shared_ptr<AABox> Box;
	public:
		Vector2 BoxSize;

		virtual void MakeNew();

		_BoxDeath();
		_BoxDeath( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		virtual Vector2 GetBoxPos();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		virtual void Scale( float scale );

	protected:
		void TargetPos();

		virtual void ActivePhsxStep();

	public:
		virtual void PhsxStep2();

		virtual void OnMarkedForDeletion();

	protected:
		virtual void DrawBoxes();

	public:
		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef _BOXDEATH
