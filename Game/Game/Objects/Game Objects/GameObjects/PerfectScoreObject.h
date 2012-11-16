#ifndef PERFECTSCOREOBJECT
#define PERFECTSCOREOBJECT

#include "GUI_Panel.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Games/Campaign/CampaignSequence.h"
#include "CoinScoreMultiplierObject.h"
#include "GUI_NextLife.h"
#include "GUI_Timer.h"
#include "../Core/Lambdas/Lambda.h"
#include <string>
#include <vector>
#include <cmath>
#include <tchar.h>
#include "stringconverter.h"

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	/// <summary>
	/// This object tracks a player's action.
	/// When a level is finished without dying and with every coin grabbed, a bonus is given.
	/// Doing this multiple times increases the bonus.
	/// </summary>
	class PerfectScoreObject : public GUI_Panel
	{
	private:
		class OnCoinGrabProxy : public Lambda_1<ObjectBase*>
		{
		private:
			std::shared_ptr<PerfectScoreObject> pso;

		public:
			OnCoinGrabProxy( const std::shared_ptr<PerfectScoreObject> &pso );

			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class OnLevelRetryProxy : public Lambda
		{
		private:
			std::shared_ptr<PerfectScoreObject> pso;

		public:
			OnLevelRetryProxy( const std::shared_ptr<PerfectScoreObject> &pso );

			void Apply();
		};

		/// <summary>
		/// Whether the players are eligible for the bonus.
		/// </summary>
	private:
		bool Eligible;

		/// <summary>
		/// Whether the bonus has been obtained this level.
		/// </summary>
		const bool &getObtained() const;
		void setObtained( const bool &value );
		bool _Obtained;

	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

		/// <summary>
		/// The base value for the perfect bonus.
		/// </summary>
	public:
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
	private:
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
	public:
		void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

		/// <summary>
		/// The value of the current bonus, factoring in score multipliers the current game might have.
		/// </summary>
	private:
		int BonusValue();

		/// <summary>
		/// The effect that is created when a player gets the bonus.
		/// </summary>
		void Effect( Vector2 pos );

		/// <summary>
		/// If true the player can not get the bonus on this level once they have died once.
		/// </summary>
	public:
		bool IneligibleOnDeath;

	private:
		int Count;
		/// <summary>
		/// When the players die reset the multiplier
		/// </summary>
	public:
		void OnLevelRetry();

	private:
		void ResetMultiplier();

	public:
		static bool GlobalObtained;
		static int GlobalBonus;
		bool Global;
		bool ShowMultiplier;
		PerfectScoreObject( bool Global, bool ShowMultiplier );

		const float &getMultiplier() const;

	protected:
		virtual void MyPhsxStep();


		/// <summary>
		/// Gui code.
		/// </summary>
		#pragma region GUI_Code
		/// <summary>
		/// Return a string representation of the score
		/// </summary>
	public:
		virtual std::wstring ToString();

	private:
		bool AddedOnce;
		void OnAdd_GUI();

		std::shared_ptr<EzText> Text;
		void UpdateScoreText();

		void Init_GUI();

	protected:
		virtual void MyDraw();
		#pragma endregion

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PERFECTSCOREOBJECT
