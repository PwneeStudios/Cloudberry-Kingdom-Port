#ifndef AABOX
#define AABOX

namespace CloudberryKingdom
{
	struct FloatRectangle;
}

namespace CloudberryKingdom
{
	struct QuadDrawer;
}


namespace CloudberryKingdom
{
	struct AABox
	{
	
		bool Invalidated;

		Vector2 BL, TR;
		boost::shared_ptr<FloatRectangle> Current, Target;
		bool TopOnly;

		Vector2 RealTR();
		Vector2 RealBL();

		void MakeNew();

		AABox();

		AABox( Vector2 center, Vector2 size );

		void Move( Vector2 shift );

		void Clone( const boost::shared_ptr<AABox> &A );

		void Write( const boost::shared_ptr<BinaryWriter> &writer );
		void Read( const boost::shared_ptr<BinaryReader> &reader );

		void Extend( Side side, float pos );

		void DrawFilled( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color );

		void Draw( Color color, float Width );
		void Draw( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color, float Width );
		void Draw( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color, float Width, bool DisregardTopOnly );

		void DrawT( Color color, float Width );
		void DrawT( const boost::shared_ptr<QuadDrawer> &QDrawer, Color color, float Width );

		void Initialize( Vector2 center, Vector2 size );

		Vector2 GetTR();

		Vector2 GetBL();

		float BoxSize();

		void CalcBounds();

		void CalcBounds_Full();

		void Validate();

		void SetCurrent( Vector2 center, Vector2 size );

		void SetTarget( Vector2 center, Vector2 size );

		void SwapToCurrent();

		float xSpeed();

		float RightSpeed();

		float LeftSpeed();

		void Scale( float scale );

		void Invalidate();
	};
}


#endif	//#ifndef AABOX
