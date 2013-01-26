#ifndef CLOUDBERRYKINGDOM_BACKGROUND
#define CLOUDBERRYKINGDOM_BACKGROUND

#include <global_header.h>

namespace CloudberryKingdom
{
	
	struct Background : public boost::enable_shared_from_this<Background>
	{

		virtual ~Background() { }
	
		static void AddDarkLayer( const boost::shared_ptr<Background> &b );

		static void AddRainLayer( const boost::shared_ptr<Background> &b );

		static void TurnOnSnow( const boost::shared_ptr<Background> &b );

		static void TurnOffSnow( const boost::shared_ptr<Background> &b );

		static void _code_Forest( const boost::shared_ptr<Background> &b );

		static void _code_Cloud( const boost::shared_ptr<Background> &b );

		static void _code_Cave( const boost::shared_ptr<Background> &b );

		static void _code_Hills( const boost::shared_ptr<Background> &b );

		static void _code_Castle( const boost::shared_ptr<Background> &b );

		static void _code_Sea( const boost::shared_ptr<Background> &b );


		int GuidCounter;
		int GetGuid();

		float MyGlobalIllumination;
		bool AllowLava;

		Vector2 Wind;

		boost::shared_ptr<Level> MyLevel;
		const boost::shared_ptr<Rand> &getRnd() const;

		boost::shared_ptr<BackgroundTemplate> MyType;

		boost::shared_ptr<BackgroundCollection> MyCollection;
		Vector2 OffsetOffset; // How much the BackgroundQuad offset is offset by (from calls to Move)

		float Light;

		Vector2 BL, TR;

		boost::shared_ptr<TileSet> MyTileSet;

		void Release();

		/// <summary>
		/// Reset the list to its start position.
		/// </summary>
		void Reset();

		static boost::shared_ptr<Background> UseCode( const boost::shared_ptr<BackgroundTemplate> &template_Renamed, const boost::shared_ptr<Background> &b );

		static boost::shared_ptr<Background> Get( const std::wstring &name );

		static boost::shared_ptr<Background> Get( const boost::shared_ptr<BackgroundTemplate> &Type );

		Background();

		virtual void Init( const boost::shared_ptr<Level> &level );

		virtual void Move( Vector2 shift );

		virtual void SetLevel( const boost::shared_ptr<Level> &level );

		virtual void SetBackground( const boost::shared_ptr<Background> &b );

		virtual void Absorb( const boost::shared_ptr<Background> &background );

		void Clear();

		virtual void Clear( const boost::shared_ptr<FloatRectangle> &Area );

		static bool GreenScreen;
	
		static boost::shared_ptr<QuadClass> TestQuad;
	
		static boost::shared_ptr<EzTexture> TestTexture;

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
