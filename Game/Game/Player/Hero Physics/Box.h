#ifndef BOX
#define BOX

#include "Normal.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class Bob;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobPhsxBox : public BobPhsxNormal
	{
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxBox> instance;
	public:
		const static std::shared_ptr<BobPhsxBox> &getInstance() const;

		// Instancable class
	private:
		bool InitializedAnim;

	public:
		BobPhsxBox();

		virtual void DefaultValues();

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void DuckingPhsx();

	protected:
		virtual void ParentDoXAccel();
	public:
		virtual void DoXAccel();

	protected:
		virtual void ParentGenerateInput( int CurPhsxStep );
	public:
		virtual void GenerateInput( int CurPhsxStep );

	private:
		int StandAnim, JumpAnim, DuckAnim;
		//int StandAnim = 0, JumpAnim = 2, DuckAnim = 3;

	public:
		virtual void AnimStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOX
