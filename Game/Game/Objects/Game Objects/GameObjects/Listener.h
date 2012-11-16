#ifndef LISTENER
#define LISTENER

#include <global_header.h>

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class ButtonClass;
}
namespace CloudberryKingdom
{
	class Listener : public GUI_Panel
	{
	public:
		enum Type
		{
			Type_ON_DOWN,
			Type_ON_PRESSED
		};
	public:
		Listener();

		Listener( ControllerButtons button, const std::shared_ptr<Lambda> &action );

		Type MyType;

		std::shared_ptr<Lambda> MyAction;
		int TriggeringPlayerIndex;

		/// <summary>
		/// If true the listener is removed immediately after it activates
		/// </summary>
		bool RemoveAfterActivation;

		virtual void Activate();

		ControllerButtons MyButton;
		std::shared_ptr<ButtonClass> MyButton2;
	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LISTENER
