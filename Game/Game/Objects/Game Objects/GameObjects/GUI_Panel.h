#ifndef GUI_PANEL
#define GUI_PANEL

#include <global_header.h>

#include "Core/Lambdas/Lambda.h"
#include "Core/Lambdas/LambdaFunc_1.h"

#include "Core/FancyVector2.h"
#include "Core/FancyColor.h"
#include "Core/PhsxData.h"
#include "Core/Animation/SpriteAnim.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Graphics/MainRender.h"
#include "Core/Graphics/QuadDrawer.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"

namespace CloudberryKingdom
{

	struct GUI_Panel : public GameObject
	{

		virtual ~GUI_Panel()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_Panel" );
#endif
		}

	
		struct ReturnToCallerHelper : public Lambda
		{
		
			boost::shared_ptr<GUI_Panel> panel;

		
			ReturnToCallerHelper( const boost::shared_ptr<GUI_Panel> &panel );

			void Apply();
		};

	
		struct ItemReturnToCallerProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<GUI_Panel> guiPanel;

		
			ItemReturnToCallerProxy( const boost::shared_ptr<GUI_Panel> &guiPanel );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct MenuReturnToCallerProxy : public Lambda_1<boost::shared_ptr<Menu> >
		{
		
			boost::shared_ptr<GUI_Panel> guiPanel;

		
			MenuReturnToCallerProxy( const boost::shared_ptr<GUI_Panel> &guiPanel );

			void Apply( const boost::shared_ptr<Menu> &menu );
		};

	
		struct MenuReturnToCallerLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<GUI_Panel> panel;
		
			MenuReturnToCallerLambda( const boost::shared_ptr<GUI_Panel> &panel );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct MenuReturnToCallerLambdaFunc : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<GUI_Panel> panel;
		
			MenuReturnToCallerLambdaFunc( const boost::shared_ptr<GUI_Panel> &panel );

			bool Apply( const boost::shared_ptr<Menu> &menu );
		};

	
		struct CallHelper : public Lambda
		{
		
			boost::shared_ptr<GUI_Panel> panel;
			boost::shared_ptr<GUI_Panel> child;

		
			CallHelper( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<GUI_Panel> &child );

			void Apply();
		};

	
		enum PresetPos
		{
			PresetPos_LEFT,
			PresetPos_RIGHT,
			PresetPos_TOP,
			PresetPos_BOTTOM
		};
	
		virtual std::vector<std::wstring> GetViewables();

	
		int _Control; // MUST be initialized to something negative
	
		void setControl( const int &value );
		const int &getControl() const;

		boost::shared_ptr<Menu> MyMenu;
		boost::shared_ptr<DrawPile> MyPile;

		/// <summary>
		/// The accumulation of all shifts
		/// </summary>
		Vector2 AmountShifted;

		/// <summary>
		/// Shift the DrawPile and Menu
		/// </summary>
		void Shift( Vector2 shift );

		/// <summary>
		/// Whether the Panel's physics is running. Set to false when slid out.
		/// </summary>
		bool Active;

		bool BubblingOut;

		/// <summary>
		/// The GUI_Panel that called up this GUI_Panel, if it exists.
		/// </summary>
		boost::shared_ptr<GUI_Panel> Caller;

		/// <summary>
		/// When ReturnToCaller is called, this is the number of frames to wait before showing the parent.
		/// </summary>
		int ReturnToCallerDelay;

		/// <summary>
		/// When calling a child panel, this is the number of frames to wait before showing the child.
		/// </summary>
		int CallDelay;

		/// <summary>
		/// Don't allow the menu to back out if there is no parent menu that called it.
		/// </summary>
		bool NoBackIfNoCaller;

		/// <summary>
		/// Hide the panel and return to its parent.
		/// </summary>
		virtual void ReturnToCaller();

		/// <summary>
		/// When true the Panel will release itself once all animations are finished.
		/// </summary>
		bool ReleaseWhenDone;

		/// <summary>
		/// When true the Panel will release itself once all scaling animations are finished.
		/// </summary>
	
		bool ReleaseWhenDoneScaling;

	
		virtual void ItemReturnToCaller( const boost::shared_ptr<MenuItem> &item );

		virtual bool MenuReturnToCaller( const boost::shared_ptr<Menu> &menu );

		/// <summary>
		/// Called when a child panel is exiting to this parent panel.
		/// </summary>
		virtual void OnReturnTo();

		/// <summary>
		/// Called to deactivate this panel and bring a child panel.
		/// </summary>
		void Call( const boost::shared_ptr<GUI_Panel> &child );
		virtual void Call( const boost::shared_ptr<GUI_Panel> &child, int Delay );

	
		virtual void SetChildControl( const boost::shared_ptr<GUI_Panel> &child );

		/// <summary>
		/// Called to show the Panel. By default, called by OnReturnTo.
		/// </summary>
	
		virtual void Show();

		/// <summary>
		/// Called to hide the Panel. By default, called by ReturnToCaller.
		/// </summary>
		virtual void Hide();

		bool Hid;

		boost::shared_ptr<FancyVector2> Pos;

		GUI_Panel();
		boost::shared_ptr<GUI_Panel> GUI_Panel_Construct();

		GUI_Panel( bool CallBaseConstructor );
		boost::shared_ptr<GUI_Panel> GUI_Panel_Construct( bool CallBaseConstructor );

		virtual void Constructor();

		virtual void Init();

		bool FixedToCamera;
		virtual void OnCameraChange();
		virtual void OnAdd();

		void SlideIn();
		virtual void SlideIn( int Frames );

		/// <summary>
		/// Copy the slide in and out lengths from a source panel.
		/// </summary>
		void CopySlideLengths( const boost::shared_ptr<GUI_Panel> &source );

		/// <summary>
		/// The number of frames a slide in/out lasts.
		/// </summary>
		int SlideOutLength, SlideInLength;

		/// <summary>
		/// The number of frames a slide lasts.
		/// </summary>
		virtual void setSlideLength( const int &value );

		void SlideOut( PresetPos Preset );
		virtual void SlideOut( PresetPos Preset, int Frames );

		/// <summary>
		/// When sliding out this is the number of camera widths/heights to move the panel.
		/// </summary>
		Vector2 DestinationScale;

		/// <summary>
		/// Where a panel slides out to (in relative screen coordinates)
		/// </summary>
		virtual Vector2 SlideOutDestination( PresetPos Preset );

		/// <summary>
		/// Make sure that DrawPiles and Menus have FancyPos positions
		/// </summary>
	
		void EnsureFancy();

	
		virtual bool OnScreen();

	
		Vector2 _MyCameraZoom;
		/// <summary>
		/// The value of the camera zoom the last time this panel was drawn
		/// </summary>
	
		const Vector2 &getMyCameraZoom() const;
		void setMyCameraZoom( const Vector2 &value );

	
		bool IsOnScreen;
		virtual void MyDraw();

		/// <summary>
		/// Ensures that the DrawPile's position is attached to the GUI_Panels's center
		/// </summary>
	
		void EnsurePileFancyPos();

		/// <summary>
		/// Ensures that the menu's position is attached to the GUI_Panels's center
		/// </summary>
		void EnsureMenuFancyPos();



	
		virtual void DrawNonText();
		void DrawNonText2();
		void DrawText();

	
		virtual void ReleaseBody();

	
		void PauseAnimation();
		void UnpauseAnimation();

	
		virtual void MyPhsxStep();

	
		virtual void OnRightShoulder();

		virtual bool HitTest( Vector2 pos );

		bool CheckForOutsideClick;
	
		bool outside;
	
		boost::shared_ptr<Lambda> OnOutsideClick;
	
		void CheckForBackFromOutsideClick();

		bool IsOutside();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_PANEL
