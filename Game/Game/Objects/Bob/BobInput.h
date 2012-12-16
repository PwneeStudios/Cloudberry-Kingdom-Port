#ifndef BOBINPUT
#define BOBINPUT


namespace CloudberryKingdom
{
	struct BobInput
	{
	
		bool A_Button, B_Button;
		Vector2 xVec;

		void Clean();

		void Write( const boost::shared_ptr<BinaryWriter> &writer );

		void Read( const boost::shared_ptr<BinaryReader> &reader );
	};
}


#endif	//#ifndef BOBINPUT
