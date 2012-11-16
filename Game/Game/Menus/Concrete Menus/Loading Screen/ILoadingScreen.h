#ifndef ILOADINGSCREEN
#define ILOADINGSCREEN

namespace CloudberryKingdom
{
	class Camera;
}




namespace CloudberryKingdom
{
	class ILoadingScreen
	{
	public:
		virtual void AddHint( const std::wstring &hint, int extra_wait ) = 0;

		virtual void Start() = 0;
		virtual void End() = 0;

		virtual void PreDraw() = 0;
		virtual void Draw( const std::shared_ptr<Camera> &cam ) = 0;

		virtual void MakeFake() = 0;
	};
}


#endif	//#ifndef ILOADINGSCREEN
