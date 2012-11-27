#ifndef ICON
#define ICON

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectIcon
	{
	public:
		enum IconScale
		{
			IconScale_WIDGET,
			IconScale_FULL,
			IconScale_NEARLY_FULL
		};
	public:

		bool Flipped;

		static std::shared_ptr<ObjectIcon> RobotIcon, PathIcon, SlowMoIcon;
//C# TO C++ CONVERTER NOTE: The variable CustomHoverIcon was renamed since it is named the same as a user-defined type:
		static std::shared_ptr<ObjectIcon> CheckpointIcon, RandomIcon, CustomIcon, CustomHoverIcon_Renamed;
		//public static ObjectIcon UncheckedIcon, CheckIcon

		static std::map<Upgrade, ObjectIcon*> UpgradeIcons;
		static std::map<ObjectType, ObjectIcon*> ObjIcons;

		static std::shared_ptr<ObjectIcon> CreateIcon( Upgrade upgrade );
		static std::shared_ptr<ObjectIcon> CreateIcon( Upgrade upgrade, bool big );

		static Localization::Words UpgradeName( Upgrade upgrade );

		static std::shared_ptr<ObjectIcon> CreateIcon( ObjectType obj );

		static void InitIcons();

		std::shared_ptr<QuadClass> Backdrop;
		Color BarColor;

		Localization::Words DisplayText;

		std::shared_ptr<FancyVector2> FancyPos;

		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );

		OscillateParams MyOscillateParams;
		ObjectIcon();

		virtual void SetShadow( Color color );

		virtual void SetShadow( bool Shadow );

		virtual void Fade( bool fade );

		virtual std::shared_ptr<ObjectIcon> Clone( IconScale ScaleType );

		virtual std::shared_ptr<ObjectIcon> Clone();

		float PrevSetRatio;
		virtual void SetScale( float Ratio );

		virtual void Draw( bool Selected );

#if defined(WINDOWS)
		virtual bool HitTest( Vector2 pos );
#endif

	private:
		void InitializeInstanceFields();
	};

	class PictureIcon : public ObjectIcon
	{
	public:
		virtual std::vector<std::wstring> GetViewables();

		std::shared_ptr<QuadClass> IconQuad;

		std::shared_ptr<EzTexture> IconTexture;
		float NormalWidth;

		PictureIcon( const std::shared_ptr<SpriteInfo> &info );

		PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width );
		PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width, Vector2 HitPadding );
		PictureIcon( const std::wstring &IconTextureString, Color BarColor, float Width );
		PictureIcon( const std::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width );

	private:
		void Init( const std::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width );

	public:
		virtual void SetShadow( Color color );

		virtual void SetShadow( bool Shadow );

		virtual void Fade( bool fade );

		virtual std::shared_ptr<ObjectIcon> Clone( IconScale ScaleType );

		virtual void SetScale( float Ratio );

		virtual void Draw( bool Selected );

		Vector2 HitPadding;
#if defined(WINDOWS)
		virtual bool HitTest( Vector2 pos );
#endif
	};

	class CustomHoverIcon : public ObjectIcon
	{
	public:
		virtual std::vector<std::wstring> GetViewables();

		std::shared_ptr<QuadClass> GearQuad, YQuad;

		CustomHoverIcon();

		virtual void Draw( bool Selected );
	};
}


#endif	//#ifndef ICON
