#ifndef REGION
#define REGION

#include <global_header.h>

namespace CloudberryKingdom
{
	class AABox;
}

namespace CloudberryKingdom
{
	class Door;
}








namespace CloudberryKingdom
{
	class Region : public GUI_Panel
	{
	public:
		Region( Vector2 pos, Vector2 size );

	private:
		std::shared_ptr<AABox> Box;
	public:
		void Init( Vector2 pos, Vector2 size );

		std::shared_ptr<Door> AttachedDoor;
	protected:
		virtual void MyPhsxStep();

	public:
		virtual bool OnScreen();

	protected:
		virtual void MyDraw();
	};
}


#endif	//#ifndef REGION
