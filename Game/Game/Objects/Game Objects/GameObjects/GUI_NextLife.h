#ifndef GUI_NEXTLIFE
#define GUI_NEXTLIFE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ObjectBase;
}

namespace CloudberryKingdom
{
	struct DrawPile;
}

namespace CloudberryKingdom
{
	struct GUI_LivesLeft;
}

namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	struct GUI_NextLife : public GameObject
	{
	
		struct OnCoinGrabProxy : public Lambda_1<std::shared_ptr<ObjectBase> >
		{
		
			std::shared_ptr<GUI_NextLife> guiNl;

		
			OnCoinGrabProxy( const std::shared_ptr<GUI_NextLife> &guiNl );

			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	
		virtual std::vector<std::wstring> GetViewables();

		std::shared_ptr<DrawPile> MyPile;

	
//C# TO C++ CONVERTER NOTE: The variable GUI_Lives was renamed since it is named the same as a user-defined type:
		std::shared_ptr<GUI_LivesLeft> GUI_Lives_Renamed;

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

		void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

	
		std::shared_ptr<EzText> CoinsText;
		void UpdateCoinsText();

	
//C# TO C++ CONVERTER NOTE: The parameter GUI_Lives was renamed since it is named the same as a user-defined type:
		GUI_NextLife( int CoinsToNextLife, const std::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed );

	
		void SetPos();

	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_NEXTLIFE
