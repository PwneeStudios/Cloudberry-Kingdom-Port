#include <global_header.h>

namespace CloudberryKingdom
{

	BobInput::BobInput() :
		A_Button( false ), B_Button( false )
	{
	}

	void BobInput::Clean()
	{
		A_Button = B_Button = false;
		xVec = Vector2();
	}

	void BobInput::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		writer->Write( A_Button );
		writer->Write( B_Button );
		writer->Write( xVec );
	}

	void BobInput::Read( const boost::shared_ptr<BinaryReader> &reader )
	{
		A_Button = reader->ReadBoolean();
		B_Button = reader->ReadBoolean();
		xVec = reader->ReadVector2();
	}

}
