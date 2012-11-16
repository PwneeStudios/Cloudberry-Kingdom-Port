#ifndef FADEIN
#define FADEIN

#include <global_header.h>


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	class FadeInObject : public GameObject
	{
	private:
		class ReadyProxy : public Lambda
		{
		private:
			std::shared_ptr<FadeInObject> fio;

		public:
			ReadyProxy( const std::shared_ptr<FadeInObject> &fio );

			void Apply();
		};

	private:
		class EndProxy : public Lambda
		{
		private:
			std::shared_ptr<FadeInObject> fio;

		public:
			EndProxy( const std::shared_ptr<FadeInObject> &fio );

			void Apply();
		};

	public:
		FadeInObject();

		virtual void OnAdd();

	private:
		void Ready();

		void End();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef FADEIN
