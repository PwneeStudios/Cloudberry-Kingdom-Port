#ifndef GUI_NEXTLIFE
#define GUI_NEXTLIFE

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class DrawPile;
}

namespace CloudberryKingdom
{
	class GUI_LivesLeft;
}

namespace CloudberryKingdom
{
	class EzText;
}




namespace CloudberryKingdom
{
	class GUI_NextLife : public GameObject
	{
	private:
		class OnCoinGrabProxy : public Lambda_1<ObjectBase*>
		{
		private:
			std::shared_ptr<GUI_NextLife> guiNl;

		public:
			OnCoinGrabProxy( const std::shared_ptr<GUI_NextLife> &guiNl );

			void Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	public:
		virtual std::vector<std::wstring> GetViewables();

		std::shared_ptr<DrawPile> MyPile;

	private:
//C# TO C++ CONVERTER NOTE: The variable GUI_Lives was renamed since it is named the same as a user-defined type:
		std::shared_ptr<GUI_LivesLeft> GUI_Lives_Renamed;

		int Max;

		int _Coins;
		// The time in number of frames
	public:
		const int &getCoins() const;
		void setCoins( const int &value );

	private:
		void GiveLife();

		/// <summary>
		/// Return a string representation of the coins grabbed.
		/// </summary>
		/// <returns></returns>
	public:
		virtual std::wstring ToString();

		void OnCoinGrab( const std::shared_ptr<ObjectBase> &obj );

	private:
		std::shared_ptr<EzText> CoinsText;
		void UpdateCoinsText();

	public:
//C# TO C++ CONVERTER NOTE: The parameter GUI_Lives was renamed since it is named the same as a user-defined type:
		GUI_NextLife( int CoinsToNextLife, const std::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed );

	private:
		void SetPos();

	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

		virtual void MyDraw();

		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_NEXTLIFE
