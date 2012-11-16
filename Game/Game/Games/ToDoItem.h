#ifndef TODOITEM
#define TODOITEM

#include <string>

namespace CloudberryKingdom
{
	class LambdaFunc;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
using namespace Microsoft::Xna::Framework;

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
