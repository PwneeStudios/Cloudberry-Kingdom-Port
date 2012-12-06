#ifndef DOLL_H
#define DOLL_H

#include <global_header.h>

namespace CloudberryKingdom
{
	class HeroDoll : public CkBaseMenu
	{
	public:
		HeroDoll( int Control );

	protected:
		virtual void ReleaseBody();

	public:
		std::shared_ptr<Bob> MyDoll;
		virtual void Init();

		virtual void OnAdd();

	private:
		std::shared_ptr<PlayerData> player;
	public:
		void MakeHeroDoll( const std::shared_ptr<BobPhsx> &hero );

	private:
		void SetPos();

	public:
		void SetPhsx();

		void UpdateColorScheme();

	protected:
		virtual void MyPhsxStep();

	public:
		void DrawBob();

	protected:
		virtual void MyDraw();
	};
}


#endif	//#ifndef DOLL
