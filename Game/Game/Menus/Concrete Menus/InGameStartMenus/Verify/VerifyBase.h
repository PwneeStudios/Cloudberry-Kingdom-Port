#ifndef VERIFYBASE
#define VERIFYBASE

#include <global_header.h>

namespace CloudberryKingdom
{
	class Multicaster_1;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class VerifyBaseMenu : public CkBaseMenu
	{
		/// <summary>
		/// Called when the user chooses yes/no.
		/// Bool is set to the user's choice.
		/// </summary>
	public:
		std::shared_ptr<Multicaster_1<bool> > OnSelect;

	protected:
		void DoSelect( bool choice );

		virtual void ReleaseBody();

	public:
		VerifyBaseMenu();

		VerifyBaseMenu( int Control );

		VerifyBaseMenu( bool CallBaseConstructor );

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		std::shared_ptr<QuadClass> Backdrop;
	public:
		virtual void MakeBackdrop();

	protected:
		Vector2 HeaderPos;
	public:
		virtual void Init();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef VERIFYBASE
