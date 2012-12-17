#include <global_header.h>

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

	ToDoItem::ToDoItem( const boost::shared_ptr<LambdaFunc<bool> > &FuncToDo, const std::wstring &Name, bool PauseOnPause, bool RemoveOnReset )
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
		_MarkedForDeltion = false;
		PauseOnPause = false;

		RemoveOnReset = false;
	}
}
