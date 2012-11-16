#ifndef GUI_MULTIPLIER
#define GUI_MULTIPLIER

#include "GUI_Panel.h"
#include "GUI_Text.h"
#include "../Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "../Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "../Core/Text/EzText.h"
#include <string>
#include <tchar.h>
#include "stringconverter.h"

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
