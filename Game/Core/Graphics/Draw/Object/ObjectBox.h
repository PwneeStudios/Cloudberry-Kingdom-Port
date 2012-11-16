#ifndef OBJECTBOX
#define OBJECTBOX

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectVector;
}

namespace CloudberryKingdom
{
	class ObjectClass;
}

namespace CloudberryKingdom
{
	class QuadDrawer;
}


namespace CloudberryKingdom
{
	class ObjectBox
	{
	public:
		std::shared_ptr<ObjectVector> BL, TR;

		std::wstring Name;
		bool Show;

		void Release();

		void SetHold();

		void ReadAnim( int anim, int frame );

		void Record( int anim, int frame, bool UseRelativeCoords );

		void Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t );

		void Calc( int anim, float t, int AnimLength, bool Loop, bool Linear );

		void Write( const std::shared_ptr<BinaryWriter> &writer, const std::shared_ptr<ObjectClass> &MainObject );

		void Read( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<ObjectClass> &MainObject, int VersionNumber );

		ObjectBox( const std::shared_ptr<ObjectBox> &box, bool DeepClone );

		ObjectBox();

		void Update();

		Vector2 Center();

		Vector2 Size();

#if defined(EDITOR)
		std::vector<ObjectVector*> GetObjectVectors();

		void SaveState( int StateIndex );

		void RecoverState( int StateIndex );
#endif

		void DrawExtra( const std::shared_ptr<QuadDrawer> &Drawer, Color clr );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef OBJECTBOX
