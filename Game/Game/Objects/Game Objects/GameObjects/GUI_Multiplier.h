#ifndef GUI_MULTIPLIER
#define GUI_MULTIPLIER

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class GUI_Multiplier : public GUI_Panel
	{
		/// <summary>
		/// Return a string representation of the Multiplier
		/// </summary>
	public:
		virtual std::wstring ToString();

	private:
		bool AddedOnce;
	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

		virtual int GetMultiplier();

	private:
		int Multiplier;
		void SetMultiplier( int Multiplier );

		std::shared_ptr<EzText> MultiplierText;
		void UpdateMultiplierText();

		bool DoSlideIn;
	public:
		GUI_Multiplier( int Style );
		GUI_Multiplier( int Style, bool SlideIn );

	private:
		void DoInit( int Style, bool SlideIn );

	protected:
		virtual void MyDraw();

		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_MULTIPLIER
