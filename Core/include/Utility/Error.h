#ifndef _ERROR_H_
#define _ERROR_H_

#ifdef CAFE
	#include <cafe.h>

	typedef s32 ErrorType;
#else
	#include <string>

	class ErrorType
	{
	public:
		enum MessageType
		{
			CODE,
			STRING,
		};

	private:
		int			code_;
		std::string	message_;
		bool		fatal_;
		MessageType	messageType_;

	public:
		ErrorType( int code, bool fatal = false )
			: code_( code )
			, fatal_( fatal )
			, messageType_( CODE )
		{
		}

		ErrorType( const std::string &message, bool fatal = false )
			: code_( 0 )
			, message_( message )
			, fatal_( fatal )
			, messageType_( STRING )
		{
		}

		int GetCode() const { return code_; }
		const std::string &GetMessage() const { return message_; }
		bool IsFatal() const { return fatal_; }
		MessageType GetMessageType() const { return messageType_; }
	};
#endif

/// Display a system error.
/**
 * @param errorCode Current error code.
 */
void DisplayError( const ErrorType &errorCode );

#endif