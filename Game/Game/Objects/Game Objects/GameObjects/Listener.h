#ifndef LISTENER
#define LISTENER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Listener : public GUI_Panel
	{

		enum Type
		{
			Type_ON_DOWN,
			Type_ON_PRESSED
		};
	
		Listener();
		void Listener_Construct();
		Listener( ControllerButtons button, const std::shared_ptr<Lambda> &action );
		void Listener_Construct( ControllerButtons button, const std::shared_ptr<Lambda> &action );

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
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LISTENER
