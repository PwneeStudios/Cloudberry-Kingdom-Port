#ifndef COMPUTERRECORDING
#define COMPUTERRECORDING

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ComputerRecording : public boost::enable_shared_from_this<ComputerRecording>
	{

	
		static void InitializeStatics();

	
		static std::stack<boost::shared_ptr<ComputerRecording> > Pool;

		bool IsFromPool;
		static void FillPool();

	
		static void InitPool();

		static boost::shared_ptr<ComputerRecording> FromPool();

		static void ToPool( const boost::shared_ptr<ComputerRecording> &record );




		bool Sparse, SuperSparse;

		std::vector<BobInput> Input;
		std::vector<int> AutoJump;
		std::vector<Vector2> AutoLocs, AutoVel, BoxCenter;
		std::vector<bool> AutoOnGround;
		std::vector<unsigned char> Anim;
		std::vector<float> t;
		std::vector<bool> Alive;

		void Shift( Vector2 shift );

		static int PareDivider;

		void Write( const boost::shared_ptr<BinaryWriter> &writer, int Length );

		void Read( const boost::shared_ptr<BinaryReader> &reader, int Length );

		void Clean();

		bool GetAlive( int Step );

		unsigned char GetAnim( int Step );

		float Gett( int Step );

		Vector2 GetBoxCenter( int Step );



		template<typename T>
		std::vector<T> PareDown( std::vector<T> SourceArray );

		void ConvertToSuperSparse();

		void Release();

		void Init( int length );
		void Init( int length, bool Sparse );
	};
}


#endif	//#ifndef COMPUTERRECORDING
