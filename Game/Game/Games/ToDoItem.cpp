#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;


namespace CloudberryKingdom
{

	const bool &ToDoItem::getMarkedForDeletion() const
	{
		return _MarkedForDeltion;
	}

	void ToDoItem::setMarkedForDeletion( const bool &value )
	{
		_MarkedForDeltion = value;
	}

	ToDoItem::ToDoItem( const std::shared_ptr<LambdaFunc<bool> > &FuncToDo, const std::wstring &Name, bool PauseOnPause, bool RemoveOnReset )
	{
		InitializeInstanceFields();
		MyFunc = FuncToDo;
		this->Name = Name;
		this->PauseOnPause = PauseOnPause;
		this->RemoveOnReset = RemoveOnReset;
	}

	void ToDoItem::Delete()
	{
		setMarkedForDeletion( true );
	}

	void ToDoItem::InitializeInstanceFields()
	{
		Step = 0;
	}
}
