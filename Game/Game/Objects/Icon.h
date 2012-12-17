#ifndef ICON
#define ICON

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ObjectIcon
	{

	
		static void InitializeStatics();

	
		enum IconScale
		{
			IconScale_WIDGET,
			IconScale_FULL,
			IconScale_NEARLY_FULL
		};
	

		bool Flipped;

		static boost::shared_ptr<ObjectIcon> RobotIcon, PathIcon, SlowMoIcon;
		static boost::shared_ptr<ObjectIcon> CheckpointIcon, RandomIcon, CustomIcon, CustomHoverIcon_Renamed;
		//public static ObjectIcon UncheckedIcon, CheckIcon

		static std::map<Upgrade, boost::shared_ptr<ObjectIcon> > UpgradeIcons;
		static std::map<ObjectType, boost::shared_ptr<ObjectIcon> > ObjIcons;

		static boost::shared_ptr<ObjectIcon> CreateIcon( Upgrade upgrade );
		static boost::shared_ptr<ObjectIcon> CreateIcon( Upgrade upgrade, bool big );

		static Localization::Words UpgradeName( Upgrade upgrade );

		static boost::shared_ptr<ObjectIcon> CreateIcon( ObjectType obj );

		static void InitIcons();

		boost::shared_ptr<QuadClass> Backdrop;
		Color BarColor;

		Localization::Words DisplayText;

		boost::shared_ptr<FancyVector2> FancyPos;

		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );

		OscillateParams MyOscillateParams;
		ObjectIcon();

		virtual void SetShadow( Color color );

		virtual void SetShadow( bool Shadow );

		virtual void Fade( bool fade );

		virtual boost::shared_ptr<ObjectIcon> Clone( IconScale ScaleType );

		virtual boost::shared_ptr<ObjectIcon> Clone();

		float PrevSetRatio;
		virtual void SetScale( float Ratio );

		virtual void Draw( bool Selected );

#if defined(WINDOWS)
		virtual bool HitTest( Vector2 pos );
#endif

	
		void InitializeInstanceFields();
	};

	struct PictureIcon : public ObjectIcon
	{
	
		virtual std::vector<std::wstring> GetViewables();

		boost::shared_ptr<QuadClass> IconQuad;

		boost::shared_ptr<EzTexture> IconTexture;
		float NormalWidth;

		PictureIcon( const boost::shared_ptr<SpriteInfo> &info );

		PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width );
		PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width, Vector2 HitPadding );
		PictureIcon( const std::wstring &IconTextureString, Color BarColor, float Width );
		PictureIcon( const boost::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width );

	
		void Init( const boost::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width );

	
		virtual void SetShadow( Color color );

		virtual void SetShadow( bool Shadow );

		virtual void Fade( bool fade );

		virtual boost::shared_ptr<ObjectIcon> Clone( IconScale ScaleType );

		virtual void SetScale( float Ratio );

		virtual void Draw( bool Selected );

		Vector2 HitPadding;
#if defined(WINDOWS)
		virtual bool HitTest( Vector2 pos );
#endif
	};

	struct CustomHoverIcon : public ObjectIcon
	{
	
		virtual std::vector<std::wstring> GetViewables();

		boost::shared_ptr<QuadClass> GearQuad, YQuad;

		CustomHoverIcon();

		virtual void Draw( bool Selected );
	};
}


#endif	//#ifndef ICON
