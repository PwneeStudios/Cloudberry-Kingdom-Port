#ifndef SWARMBUNDLE
#define SWARMBUNDLE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct SwarmBundle
	{

	
		struct BobToSpritesLambda : public Lambda_2<std::map<int, std::shared_ptr<SpriteAnim> >, Vector2>
		{
		
			std::shared_ptr<Bob> bob;
		
			BobToSpritesLambda( const std::shared_ptr<Bob> &bob );

			void Apply( const std::map<int, std::shared_ptr<SpriteAnim> > &dict, const Vector2 &pos );
		};

	
		std::vector<std::shared_ptr<SwarmRecord> > Swarms;
	
		std::shared_ptr<SwarmRecord> CurrentSwarm;

		bool Initialized;
	
		std::vector<std::shared_ptr<SpriteAnimGroup> > AnimGroup;

		std::vector<std::shared_ptr<BobLink> > BobLinks;

	
		void Release();

		SwarmBundle();

		void Init( const std::shared_ptr<Level> &level );

		void SetSwarm( const std::shared_ptr<Level> &level, int i );

		const int getSwarmIndex() const;

		const int getNumSwarms() const;

		bool GetNextSwarm( const std::shared_ptr<Level> &level );

		bool EndCheck( const std::shared_ptr<Level> &level );

		void StartNewSwarm();

		void Draw( int Step, const std::shared_ptr<Level> &level );
	};
}


#endif	//#ifndef SWARMBUNDLE
