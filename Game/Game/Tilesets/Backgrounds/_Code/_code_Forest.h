#ifndef _CODE_FOREST
#define _CODE_FOREST

#include <global_header.h>

namespace CloudberryKingdom
{
	class Background;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Background_Forest : public BackgroundTemplate
	{
	public:
		Background_Forest( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

	class Background_ForestSnow : public BackgroundTemplate
	{
	public:
		Background_ForestSnow( const std::wstring &Name );

		virtual void Code( const std::shared_ptr<Background> &b );
	};

}


#endif	//#ifndef _CODE_FOREST
