#ifndef BOBINPUT
#define BOBINPUT












namespace CloudberryKingdom
{
	class BobInput
	{
	public:
		bool A_Button, B_Button;
		Vector2 xVec;

		void Clean();

		void Write( const std::shared_ptr<BinaryWriter> &writer );

		void Read( const std::shared_ptr<BinaryReader> &reader );
	};
}


#endif	//#ifndef BOBINPUT
