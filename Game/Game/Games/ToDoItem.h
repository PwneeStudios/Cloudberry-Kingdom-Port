#ifndef TODOITEM
#define TODOITEM

#include <global_header.h>

namespace CloudberryKingdom
{
	class ToDoItem
	{
	public:
		std::shared_ptr<LambdaFunc<bool> > MyFunc;
		std::wstring Name;

		int Step;

		/// <summary>
		/// If true the function will be deleted without executing.
		/// </summary>
		const bool &getMarkedForDeletion() const;
		void setMarkedForDeletion( const bool &value );
	private:
		bool _MarkedForDeltion;

		/// <summary>
		/// Whether the item pauses when the game is paused.
		/// </summary>
	public:
		bool PauseOnPause;

		bool RemoveOnReset;

		ToDoItem( const std::shared_ptr<LambdaFunc<bool> > &FuncToDo, const std::wstring &Name, bool PauseOnPause, bool RemoveOnReset );

		/// <summary>
		/// Mark the function for deletion and prevent execution.
		/// </summary>
		void Delete();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TODOITEM
