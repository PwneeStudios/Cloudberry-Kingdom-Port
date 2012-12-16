#ifndef BACKGROUNDFLOATERLIST
#define BACKGROUNDFLOATERLIST

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BackgroundFloaterList : public boost::enable_shared_from_this<BackgroundFloaterList>
	{
	
		struct ClearBackgroundListLambda : public LambdaFunc_1<boost::shared_ptr<BackgroundFloater>, bool>
		{
		
			boost::shared_ptr<FloatRectangle> Area;
		
			ClearBackgroundListLambda( const boost::shared_ptr<FloatRectangle> &Area );

			bool Apply( const boost::shared_ptr<BackgroundFloater> &floater );
		};

	
		std::wstring Name;

		bool Foreground;
		bool Fixed;

		bool Show;

#if defined(INCLUDE_EDITOR)
		/// <summary>
		/// When locked a layer can not be edited.
		/// </summary>
		bool Lock;

		const bool &getEditable() const;
#endif

		boost::shared_ptr<Level> MyLevel;
		std::vector<boost::shared_ptr<BackgroundFloater> > Floaters;

		float Parallax;

		/// <summary>
		/// Reset the list to its start position.
		/// </summary>
		void Reset();

		void SetParallaxAndPropagate( float Parallax );

		BackgroundFloaterList();

		void Release();

		void SetLevel( const boost::shared_ptr<Level> &level );

//C# TO C++ CONVERTER NOTE: The parameter Background was renamed since it is named the same as a user-defined type:
		void SetBackground( const boost::shared_ptr<Background> &Background_Renamed );

		void Move( Vector2 shift );

		void Clear();

		void Clear( const boost::shared_ptr<FloatRectangle> &Area );

		void Absorb( const boost::shared_ptr<BackgroundFloaterList> &list );

		Vector2 BL, TR;
		void PhsxStep();

		void Draw();
		void Draw( float CamMod );

		bool DoPreDraw;

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BACKGROUNDFLOATERLIST
