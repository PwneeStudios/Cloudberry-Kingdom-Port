#ifndef BACKGROUNDFLOATERLIST
#define BACKGROUNDFLOATERLIST

#include <global_header.h>

namespace CloudberryKingdom
{
	class BackgroundFloater;
}

namespace CloudberryKingdom
{
	class FloatRectangle;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Background;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class BackgroundFloaterList : public ViewReadWrite
	{
	private:
		class ClearBackgroundListLambda : public LambdaFunc_1<BackgroundFloater*, bool>
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
		std::vector<BackgroundFloater*> Floaters;

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

		virtual std::vector<std::wstring> GetViewables();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BACKGROUNDFLOATERLIST
