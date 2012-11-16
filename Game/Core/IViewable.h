#ifndef IVIEWABLE
#define IVIEWABLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class ViewReadWrite;
}








namespace CloudberryKingdom
{
	class InstancePlusName
	{
	public:
		std::shared_ptr<ViewReadWrite> instance;
		std::wstring name;
		InstancePlusName( const std::shared_ptr<ViewReadWrite> &i, const std::wstring &n );
	};

	class IReadWrite
	{
	public:
		virtual void Write( const std::shared_ptr<StreamWriter> &writer ) = 0;
		virtual void Read( const std::shared_ptr<StreamReader> &reader ) = 0;

		virtual void WriteCode( const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer ) = 0;
	};

	class ViewReadWrite : public IReadWrite
	{
	public:
		virtual std::wstring GetConstructorString();

		virtual std::vector<std::wstring> GetViewables();

		virtual void Write( const std::shared_ptr<StreamWriter> &writer );

		virtual void Read( const std::shared_ptr<StreamReader> &reader );

		virtual void WriteCode( const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer );

		virtual void ProcessMouseInput( Vector2 shift, bool ShiftDown );

		virtual std::wstring CopyToClipboard( const std::wstring &suffix );
	};

	class IViewableList
	{
	public:
		virtual void GetChildren( std::vector<InstancePlusName*> &ViewableChildren ) = 0;
	};
}


#endif	//#ifndef IVIEWABLE
