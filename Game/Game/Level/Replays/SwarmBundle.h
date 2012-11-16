#ifndef SWARMBUNDLE
#define SWARMBUNDLE

#include <global_header.h>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Vector2;
		}
	}
}

namespace CloudberryKingdom
{
	class SpriteAnim;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class SwarmRecord;
}

namespace CloudberryKingdom
{
	class SpriteAnimGroup;
}

namespace CloudberryKingdom
{
	class BobLink;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class SwarmBundle
	{
	private:
		class BobToSpritesLambda : public Lambda_2<std::unordered_map<int, SpriteAnim*>, Vector2>
		{
		private:
			std::shared_ptr<Bob> bob;
		public:
			BobToSpritesLambda( const std::shared_ptr<Bob> &bob );

			void Apply( std::unordered_map<int, SpriteAnim*> &dict, Vector2 pos );
		};

	private:
		std::vector<SwarmRecord*> Swarms;
	public:
		std::shared_ptr<SwarmRecord> CurrentSwarm;

		bool Initialized;
	private:
		std::vector<SpriteAnimGroup*> AnimGroup;

		std::vector<BobLink*> BobLinks;

	public:
		void Release();

		SwarmBundle();

		void Init( const std::shared_ptr<Level> &level );

		void SetSwarm( const std::shared_ptr<Level> &level, int i );

		const int &getSwarmIndex() const;

		const int &getNumSwarms() const;

		bool GetNextSwarm( const std::shared_ptr<Level> &level );

		bool EndCheck( const std::shared_ptr<Level> &level );

		void StartNewSwarm();

		void Draw( int Step, const std::shared_ptr<Level> &level );
	};
}


#endif	//#ifndef SWARMBUNDLE
