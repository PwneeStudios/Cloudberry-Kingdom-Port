#ifndef TODOITEM
#define TODOITEM

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ToDoItem
	{
	
		boost::shared_ptr<LambdaFunc<bool> > MyFunc;
		std::wstring Name;

		int Step;

		/// <summary>
		/// If true the function will be deleted without executing.
		/// </summary>
		const bool &getMarkedForDeletion() const;
		void setMarkedForDeletion( const bool &value );
	
		bool _MarkedForDeltion;

		/// <summary>
		/// Whether the item pauses when the game is paused.
		/// </summary>
	
		bool PauseOnPause;

		bool RemoveOnReset;

		ToDoItem( const boost::shared_ptr<LambdaFunc<bool> > &FuncToDo, const std::wstring &Name, bool PauseOnPause, bool RemoveOnReset );

		/// <summary>
		/// Mark the function for deletion and prevent execution.
		/// </summary>
		void Delete();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TODOITEM
