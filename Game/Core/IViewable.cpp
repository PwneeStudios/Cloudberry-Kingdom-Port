#include <global_header.h>







namespace CloudberryKingdom
{

	InstancePlusName::InstancePlusName( const std::shared_ptr<ViewReadWrite> &i, const std::wstring &n )
	{
		instance = i;
		name = n;
	}

	std::wstring ViewReadWrite::GetConstructorString()
	{
		return 0;
	}

	std::vector<std::wstring> ViewReadWrite::GetViewables()
	{
		return std::vector<std::wstring*> ();
	}

	void ViewReadWrite::Write( const std::shared_ptr<StreamWriter> &writer )
	{
		Tools::WriteFields( this, writer, GetViewables() );
	}

	void ViewReadWrite::Read( const std::shared_ptr<StreamReader> &reader )
	{
		Tools::ReadFields( this, reader );
	}

	void ViewReadWrite::WriteCode( const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer )
	{
		Tools::WriteFieldsToCode( this, prefix, writer, GetViewables() );
	}

	void ViewReadWrite::ProcessMouseInput( Vector2 shift, bool ShiftDown )
	{
	}

	std::wstring ViewReadWrite::CopyToClipboard( const std::wstring &suffix )
	{
		return _T( "" );
	}
}
