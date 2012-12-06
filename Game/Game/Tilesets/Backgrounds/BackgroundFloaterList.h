#ifndef BACKGROUNDFLOATERLIST
#define BACKGROUNDFLOATERLIST

#include <global_header.h>

namespace CloudberryKingdom
{
	class BackgroundFloaterList : public std::enable_shared_from_this<BackgroundFloaterList>
	{
	private:
		class ClearBackgroundListLambda : public LambdaFunc_1<std::shared_ptr<BackgroundFloater>, bool>
		{
		private:
			std::shared_ptr<FloatRectangle> Area;
		public:
			ClearBackgroundListLambda( const std::shared_ptr<FloatRectangle> &Area );

			bool Apply( const std::shared_ptr<BackgroundFloater> &floater );
		};

	public:
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

		std::shared_ptr<Level> MyLevel;
		std::vector<std::shared_ptr<BackgroundFloater> > Floaters;

		float Parallax;

		/// <summary>
		/// Reset the list to its start position.
		/// </summary>
		void Reset();

		void SetParallaxAndPropagate( float Parallax );

		BackgroundFloaterList();

		void Release();

		void SetLevel( const std::shared_ptr<Level> &level );

//C# TO C++ CONVERTER NOTE: The parameter Background was renamed since it is named the same as a user-defined type:
		void SetBackground( const std::shared_ptr<Background> &Background_Renamed );

		void Move( Vector2 shift );

		void Clear();

		void Clear( const std::shared_ptr<FloatRectangle> &Area );

		void Absorb( const std::shared_ptr<BackgroundFloaterList> &list );

		Vector2 BL, TR;
		void PhsxStep();

		void Draw();
		void Draw( float CamMod );

		bool DoPreDraw;

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BACKGROUNDFLOATERLIST
