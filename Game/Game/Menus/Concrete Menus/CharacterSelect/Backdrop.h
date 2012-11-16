#ifndef BACKDROP
#define BACKDROP

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class CharSelectBackdrop : public CkBaseMenu
	{
	public:
		CharSelectBackdrop();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void OnAdd();

		virtual void Init();

	private:
		void SetPos();
	};
}


#endif	//#ifndef BACKDROP
