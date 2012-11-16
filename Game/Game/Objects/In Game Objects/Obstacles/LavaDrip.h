#ifndef LAVADRIP
#define LAVADRIP

#include <global_header.h>

namespace CloudberryKingdom
{
	class LineSpriteInfo;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}











namespace CloudberryKingdom
{
	class LavaDrip : public _BoxDeath
	{
	public:
		class LavaDripTileInfo : public TileInfoBase
		{
		public:
//C# TO C++ CONVERTER NOTE: The variable Line was renamed since it is named the same as a user-defined type:
			std::shared_ptr<LineSpriteInfo> Line_Renamed;
			Vector2 BoxSize;

		private:
			void InitializeInstanceFields();

public:
			LavaDripTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		int Offset, DownT, WaitT, PeakT;

		Vector2 Start, End;

		bool Exposed;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		LavaDrip( bool BoxesOnly );

		int Period;
		void SetPeriod( float speed );

	protected:
		virtual void ActivePhsxStep();

	public:
		void AnimStep();
		void AnimStep( bool Skip );

	protected:
		virtual void DrawGraphics();

	public:
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef LAVADRIP
