#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#include <global_header.h>

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Rand;
}

namespace CloudberryKingdom
{
	class BackgroundTemplate;
}

namespace CloudberryKingdom
{
	class BackgroundCollection;
}

namespace CloudberryKingdom
{
	class TileSet;
}

namespace CloudberryKingdom
{
	class FloatRectangle;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzTexture;
}


using namespace Microsoft::Xna::Framework;







//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


namespace CloudberryKingdom
{
	class Background : public ViewReadWrite
	{
	public:
		static void AddRainLayer( const std::shared_ptr<Background> &b );


		static void TurnOnSnow( const std::shared_ptr<Background> &b );

		static void TurnOffSnow( const std::shared_ptr<Background> &b );

		static void _code_Forest( const std::shared_ptr<Background> &b );


		static void _code_Cloud( const std::shared_ptr<Background> &b );


		static void _code_Cave( const std::shared_ptr<Background> &b );


		static void _code_Hills( const std::shared_ptr<Background> &b );


		static void _code_Castle( const std::shared_ptr<Background> &b );


		static void _code_Sea( const std::shared_ptr<Background> &b );


		int GuidCounter;
		int GetGuid();

		float MyGlobalIllumination;
		bool AllowLava;

		Vector2 Wind;

		std::shared_ptr<Level> MyLevel;
		const std::shared_ptr<Rand> &getRnd() const;

		std::shared_ptr<BackgroundTemplate> MyType;

		std::shared_ptr<BackgroundCollection> MyCollection;
		Vector2 OffsetOffset; // How much the BackgroundQuad offset is offset by (from calls to Move)

		float Light;

		Vector2 BL, TR;

		std::shared_ptr<TileSet> MyTileSet;

		void Release();

		/// <summary>
		/// Reset the list to its start position.
		/// </summary>
		void Reset();

		static std::shared_ptr<Background> UseCode( const std::shared_ptr<BackgroundTemplate> &template_Renamed, const std::shared_ptr<Background> &b );

		static std::shared_ptr<Background> Get( const std::wstring &name );

		static std::shared_ptr<Background> Get( const std::shared_ptr<BackgroundTemplate> &Type );

		Background();

		virtual void Init( const std::shared_ptr<Level> &level );

		virtual void Move( Vector2 shift );

		virtual void SetLevel( const std::shared_ptr<Level> &level );

		virtual void SetBackground( const std::shared_ptr<Background> &b );

		virtual void Absorb( const std::shared_ptr<Background> &background );

		void Clear();

		virtual void Clear( const std::shared_ptr<FloatRectangle> &Area );

		static bool GreenScreen;
	private:
		static std::shared_ptr<QuadClass> TestQuad;
	public:
		static std::shared_ptr<EzTexture> TestTexture;

		static void DrawTest();

		virtual void Draw();

		virtual void DrawForeground();

		void DimAll( float dim );

		virtual std::vector<std::wstring> GetViewables();
		virtual void Read( const std::shared_ptr<StreamReader> &reader );

		void Save( const std::wstring &path );

		void Load( const std::wstring &path );

		void SetWeatherIntensity( float Intensity );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM
