#ifndef PERFECTSCOREOBJECT
#define PERFECTSCOREOBJECT

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
//#include "Core/Texture/EzTexture.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Objects/Game Objects/GameObjects/Cheer.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/Special/TextFloat.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	/// <summary>
	/// This object tracks a player's action.
	/// When a level is finished without dying and with every coin grabbed, a bonus is given.
	/// Doing this multiple times increases the bonus.
	/// </summary>
	struct PerfectScoreObject : public GUI_Panel
	{

		virtual ~PerfectScoreObject()
		{
#ifdef BOOST_BIN
			OnDestructor( "PerfectScoreObject" );
#endif
		}


		struct TextEffectProxy : public Lambda
		{
			boost::shared_ptr<PerfectScoreObject> pso;
		
			TextEffectProxy( const boost::shared_ptr<PerfectScoreObject> &pso );

			void Apply();
		};

		struct OnCoinGrabProxy : public Lambda_1<boost::shared_ptr<ObjectBase> >
		{
		
			boost::shared_ptr<PerfectScoreObject> pso;

		
			OnCoinGrabProxy( const boost::shared_ptr<PerfectScoreObject> &pso );

			void Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct OnLevelRetryProxy : public Lambda
		{
		
			boost::shared_ptr<PerfectScoreObject> pso;

		
			OnLevelRetryProxy( const boost::shared_ptr<PerfectScoreObject> &pso );

			void Apply();
		};

		/// <summary>
		/// Whether the players are eligible for the bonus.
		/// </summary>
	
		bool Eligible;

		/// <summary>
		/// Whether the bonus has been obtained this level.
		/// </summary>
		const bool &getObtained() const;
		void setObtained( const bool &value );
		bool _Obtained;

	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

		/// <summary>
		/// The base value for the perfect bonus.
		/// </summary>
	
		const int &getBaseBonus() const;
		void setBaseBonus( const int &value );
		int _BaseBonus;

		/// <summary>
		/// How much the value of the bonus increases each time it is obtained.
		/// </summary>
		int BonusIncrement;

		/// <summary>
		/// The largest the bonus can be
		/// </summary>
		int MaxBonus;

		/// <summary>
		/// The value the next perfect bonus is worth.
		/// </summary>
	
		const int &getNextBonus() const;
		void setNextBonus( const int &value );
		int _NextBonus;


		/// <summary>
		/// How many times a bonus has been gotten in a row
		/// </summary>
		int BonusCount;

		/// <summary>
		/// Every time a coin is grabbed check to see if it was the last coin on the level.
		/// </summary>
	
		void OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj );

		/// <summary>
		/// The value of the current bonus, factoring in score multipliers the current game might have.
		/// </summary>
	
		int BonusValue();

		/// <summary>
		/// The effect that is created when a player gets the bonus.
		/// </summary>
		void Effect( Vector2 pos );

		/// <summary>
		/// If true the player can not get the bonus on this level once they have died once.
		/// </summary>
	
		bool IneligibleOnDeath;

	
		int Count;


		void MyGame_OnCompleteLevel( boost::shared_ptr<Level> obj );
		void TextEffect();

		/// <summary>
		/// When the players die reset the multiplier
		/// </summary>
		void OnLevelRetry();

	
		void ResetMultiplier();

		bool Campaign;
		static bool GlobalObtained;
		static int GlobalBonus;
		bool Global;
		bool ShowMultiplier;
		PerfectScoreObject( bool Global, bool ShowMultiplier, bool Campaign );
		boost::shared_ptr<PerfectScoreObject> PerfectScoreObject_Construct( bool Global, bool ShowMultiplier, bool Campaign );

		const float getMultiplier() const;

	
		virtual void MyPhsxStep();


		/// <summary>
		/// Gui code.
		/// </summary>
		#pragma region GUI_Code
		/// <summary>
		/// Return a string representation of the score
		/// </summary>
	
		virtual std::wstring ToString();

	
		bool AddedOnce;
		void OnAdd_GUI();

		std::vector<boost::shared_ptr<QuadClass> > Dots;
		boost::shared_ptr<EzTexture> Full, Empty;
		boost::shared_ptr<EzText> Text;
		void UpdateScoreText();

		void Init_GUI();

		void SetPos();
	    void Release();
	
		virtual void MyDraw();
		#pragma endregion

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef PERFECTSCOREOBJECT
