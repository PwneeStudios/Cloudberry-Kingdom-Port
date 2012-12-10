#ifndef CLOUDBERRYKINGDOM_BACKGROUND
#define CLOUDBERRYKINGDOM_BACKGROUND

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background : public std::enable_shared_from_this<Background>
	{
	
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
	
		static std::shared_ptr<QuadClass> TestQuad;
	
		static std::shared_ptr<EzTexture> TestTexture;

		static void DrawTest();

		virtual void Draw();

		virtual void DrawForeground();

		void DimAll( float dim );

		void Save( const std::wstring &path );

		void Load( const std::wstring &path );

		void SetWeatherIntensity( float Intensity );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_BACKGROUND
