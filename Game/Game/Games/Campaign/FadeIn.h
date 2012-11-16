#ifndef FADEIN
#define FADEIN

#include <global_header.h>


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
