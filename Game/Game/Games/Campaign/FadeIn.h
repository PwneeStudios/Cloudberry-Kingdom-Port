#ifndef FADEIN
#define FADEIN

#include <global_header.h>

namespace CloudberryKingdom
{
	struct FadeInObject : public GameObject
	{
		virtual ~FadeInObject() { }

		struct ReadyProxy : public Lambda
		{
		
			boost::shared_ptr<FadeInObject> fio;

		
			ReadyProxy( const boost::shared_ptr<FadeInObject> &fio );

			void Apply();
		};

	
		struct EndProxy : public Lambda
		{
		
			boost::shared_ptr<FadeInObject> fio;

		
			EndProxy( const boost::shared_ptr<FadeInObject> &fio );

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
