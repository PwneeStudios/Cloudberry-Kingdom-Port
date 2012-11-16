#ifndef SIMPLEOBJECT
#define SIMPLEOBJECT

#include <global_header.h>

namespace CloudberryKingdom
{
	class SimpleBox;
}

namespace CloudberryKingdom
{
	class AnimQueueEntry;
}

namespace CloudberryKingdom
{
	class EzEffect;
}

namespace CloudberryKingdom
{
	class ObjectClass;
}

namespace CloudberryKingdom
{
	class EzEffectWad;
}

namespace CloudberryKingdom
{
	class QuadDrawer;
}










namespace CloudberryKingdom
{
	class SimpleObject
	{
	public:
		std::vector<SimpleQuad> Quads;
		std::vector<SimpleBox*> Boxes;
		BasePoint Base;

		bool xFlip, yFlip, CenterFlipOnBox;
		Vector2 FlipCenter;

		std::queue<AnimQueueEntry*> AnimQueue;
		std::shared_ptr<AnimQueueEntry> LastAnimEntry;
		std::vector<int> AnimLength;
		std::vector<std::wstring> AnimName;
		std::vector<float> AnimSpeed;
		bool Play, Loop, Transfer, OldLoop, Linear;
		int anim, OldAnim;
		float t, OldT, StartT;

		std::vector<EzEffect*> MyEffects;

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

		SimpleObject( const std::shared_ptr<SimpleObject> &obj, bool BoxesOnly );
	private:
		void Constructor( const std::shared_ptr<SimpleObject> &obj, bool BoxesOnly, bool DeepCopy );

	public:
		SimpleObject( const std::shared_ptr<ObjectClass> &obj );

		Vector2 GetBoxCenter( int i );

		void CopyUpdate( const std::shared_ptr<SimpleObject> &source );

		void UpdateQuads();

		void UpdateBoxes();

		void Update();

		/// <summary>
		/// Shift each quad's absolute vertex coordinates. Does not effect normal coordinates.
		/// </summary>
		/// <param name="shift"></param>
		void UpdatedShift( Vector2 shift );

		void Draw();

		void Draw( const std::shared_ptr<QuadDrawer> &QDrawer, const std::shared_ptr<EzEffectWad> &EffectWad );
		void Draw( const std::shared_ptr<QuadDrawer> &QDrawer, const std::shared_ptr<EzEffectWad> &EffectWad, int StartIndex, int EndIndex );

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
