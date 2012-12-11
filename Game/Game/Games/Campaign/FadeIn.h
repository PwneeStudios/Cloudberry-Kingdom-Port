#ifndef FADEIN
#define FADEIN

#include <global_header.h>

namespace CloudberryKingdom
{
	struct FadeInObject : public GameObject
	{
	
		struct ReadyProxy : public Lambda
		{
		
			std::shared_ptr<FadeInObject> fio;

		
			ReadyProxy( const std::shared_ptr<FadeInObject> &fio );

			void Apply();
		};

	
		struct EndProxy : public Lambda
		{
		
			std::shared_ptr<FadeInObject> fio;

		
			EndProxy( const std::shared_ptr<FadeInObject> &fio );

			void Apply();
		};

	
		FadeInObject();

		virtual void OnAdd();

	
		void Ready();

		void End();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef FADEIN
