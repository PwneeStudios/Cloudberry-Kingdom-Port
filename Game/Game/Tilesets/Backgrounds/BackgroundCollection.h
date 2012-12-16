#ifndef BACKGROUNDCOLLECTION
#define BACKGROUNDCOLLECTION

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BackgroundCollection
	{
	
		boost::shared_ptr<Level> MyLevel;

		std::vector<boost::shared_ptr<BackgroundFloaterList> > Lists;

		BackgroundCollection( const boost::shared_ptr<Level> &level );

		void Release();

		/// <summary>
		/// Reset the lists to their start position.
		/// </summary>
		void Reset();

		void SetLevel( const boost::shared_ptr<Level> &level );

		void SetBackground( const boost::shared_ptr<Background> &b );

		void Move( Vector2 shift );

		void Clear();
		void Clear( const boost::shared_ptr<FloatRectangle> &Area );

		void Absorb( const boost::shared_ptr<BackgroundCollection> &collection );

		void DrawLayer( int Layer );

		void FinishDraw();

		void Draw();
		void Draw( float CamMod, bool Foreground );

		void PhsxStep();
	};
}


#endif	//#ifndef BACKGROUNDCOLLECTION
