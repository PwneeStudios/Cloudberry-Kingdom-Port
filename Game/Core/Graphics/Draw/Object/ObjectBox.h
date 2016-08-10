#ifndef OBJECTBOX
#define OBJECTBOX

#include <small_header.h>

//#include "Core/Graphics/QuadDrawer.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/ObjectVector.h"


#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"

namespace CloudberryKingdom
{

	struct ObjectBox
	{
	
		boost::shared_ptr<ObjectVector> BL, TR;

		std::wstring Name;
		bool Show;

		void Release();

		void SetHold();

		void ReadAnim( int anim, int frame );

		void Record( int anim, int frame, bool UseRelativeCoords );

		void Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t );

		void Calc( int anim, float t, int AnimLength, bool Loop, bool Linear );

		void Write( const boost::shared_ptr<BinaryWriter> &writer, const boost::shared_ptr<ObjectClass> &MainObject );

		void Read( const boost::shared_ptr<BinaryReader> &reader, const boost::shared_ptr<ObjectClass> &MainObject, int VersionNumber );

		ObjectBox( const boost::shared_ptr<ObjectBox> &box, bool DeepClone );

		ObjectBox();

		void Update();

		Vector2 Center();

		Vector2 Size();

		void DrawExtra( const boost::shared_ptr<QuadDrawer> &Drawer, Color clr );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef OBJECTBOX
