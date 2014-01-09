#ifndef GUI_NEXTLIFE
#define GUI_NEXTLIFE

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Lives.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_LivesLeft.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Grab/Coin.h"
//#include "Game/Objects/Special/TextFloat.h"
//#include "Game/Tools/CkColorHelper.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct GUI_NextLife : public GameObject
	{
	
		virtual ~GUI_NextLife()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_NextLife" );
#endif
		}


		struct OnCoinGrabProxy : public Lambda_1<boost::shared_ptr<ObjectBase> >
		{
		
			boost::shared_ptr<GUI_NextLife> guiNl;

		
			OnCoinGrabProxy( const boost::shared_ptr<GUI_NextLife> &guiNl );

			void Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		virtual std::vector<std::wstring> GetViewables();

		boost::shared_ptr<DrawPile> MyPile;

	
//C# TO C++ CONVERTER NOTE: The variable GUI_Lives was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<GUI_LivesLeft> GUI_Lives_Renamed;

		int Max;

		int _Coins;
		// The time in number of frames
	
		const int &getCoins() const;
		void setCoins( const int &value );

	
		void GiveLife();

		/// <summary>
		/// Return a string representation of the coins grabbed.
		/// </summary>
		/// <returns></returns>
	
		virtual std::wstring ToString();

		void OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj );

	
		boost::shared_ptr<EzText> CoinsText;
		void UpdateCoinsText();

	
//C# TO C++ CONVERTER NOTE: The parameter GUI_Lives was renamed since it is named the same as a user-defined type:
		GUI_NextLife( int CoinsToNextLife, const boost::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed );

	
		void SetPos();

	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_NEXTLIFE
