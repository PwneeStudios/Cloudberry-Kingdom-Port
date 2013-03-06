#ifndef _BOXDEATH
#define _BOXDEATH

#include <global_header.h>

namespace CloudberryKingdom
{
	
	struct _BoxDeath : public _Death
	{
	
		virtual ~_BoxDeath()
		{
#ifdef BOOST_BIN
			OnDestructor( "_BoxDeath" );
#endif
		}


		boost::shared_ptr<AABox> Box;
	
		Vector2 BoxSize;

		virtual void MakeNew();

		_BoxDeath();
		_BoxDeath( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		virtual Vector2 GetBoxPos();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		virtual void Scale( float scale );

	
		void TargetPos();

		virtual void ActivePhsxStep();

	
		virtual void PhsxStep2();

		virtual void OnMarkedForDeletion();

	
		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef _BOXDEATH
