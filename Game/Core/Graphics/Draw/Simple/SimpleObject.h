#ifndef SIMPLEOBJECT
#define SIMPLEOBJECT

#include <small_header.h>

//#include "Core/Animation/AnimQueue.h"
//#include "Core/Effects/EzEffect.h"
//#include "Core/Effects/EzEffectWad.h"
//#include "Core/Graphics/QuadDrawer.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/Quad.h"
//#include "Core/Graphics/Draw/Simple/BasePoint.h"
//#include "Core/Graphics/Draw/Simple/SimpleBox.h"
//#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
//#include "Game/Tools/Tools.h"


#include "Core/Graphics/Draw/Simple/BasePoint.h"

namespace CloudberryKingdom
{

	struct SimpleObject
	{
	
		std::vector<SimpleQuad> Quads;
		std::vector<boost::shared_ptr<SimpleBox> > Boxes;
		BasePoint Base;

		bool xFlip, yFlip, CenterFlipOnBox;
		Vector2 FlipCenter;

		std::queue<boost::shared_ptr<AnimQueueEntry> > AnimQueue;
		boost::shared_ptr<AnimQueueEntry> LastAnimEntry;
		std::vector<int> AnimLength;
		std::vector<std::wstring> AnimName;
		std::vector<float> AnimSpeed;
		bool Play, Loop, Transfer, OldLoop, Linear;
		int anim, OldAnim;
		float t, OldT, StartT;

		std::vector<boost::shared_ptr<EzEffect> > MyEffects;

		bool Released;

		void Release();

		/// <summary>
		/// Update the list of effects associated with the object's quads
		/// </summary>
		void UpdateEffectList();

		/// <summary>
		/// Find the index of a quad of the given name.
		/// </summary>
		int GetQuadIndex( const std::wstring &name );

		void Scale( float scale );

		void SetColor( Color color );

		SimpleObject( const boost::shared_ptr<SimpleObject> &obj, bool BoxesOnly );
	
		void Constructor( const boost::shared_ptr<SimpleObject> &obj, bool BoxesOnly, bool DeepCopy );

	
		SimpleObject( const boost::shared_ptr<ObjectClass> &obj );

		Vector2 GetBoxCenter( int i );

		void CopyUpdate( const boost::shared_ptr<SimpleObject> &source );

		void UpdateQuads();

		void UpdateBoxes();

		void Update();

		/// <summary>
		/// Shift each quad's absolute vertex coordinates. Does not effect normal coordinates.
		/// </summary>
		/// <param name="shift"></param>
		void UpdatedShift( Vector2 shift );

		void Draw();

		void Draw( const boost::shared_ptr<QuadDrawer> &QDrawer, const boost::shared_ptr<EzEffectWad> &EffectWad );
		void Draw( const boost::shared_ptr<QuadDrawer> &QDrawer, const boost::shared_ptr<EzEffectWad> &EffectWad, int StartIndex, int EndIndex );

//C# TO C++ CONVERTER NOTE: The parameter Quad was renamed since it is named the same as a user-defined type:
		void DrawQuad( SimpleQuad &Quad_Renamed );

		void EnqueueTransfer( int _anim, float _destT, float speed, bool DestLoop );

		void EnqueueAnimation( int _anim, float startT, bool loop );

		int DestinationAnim();

		void DequeueTransfers();

		void PlayUpdate( float DeltaT );

		void SetHold();

		void Read( int anim, int frame );
	};
}


#endif	//#ifndef SIMPLEOBJECT
