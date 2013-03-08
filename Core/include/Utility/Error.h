#ifndef _ERROR_H_
#define _ERROR_H_

#if defined( CAFE ) || defined( PS3 )

#ifdef CAFE
	#include <cafe.h>
#endif

	#include <string>

	class ErrorType
	{
	public:
		enum MessageType
		{
			CODE,
			STRING,
		};

		enum InputType
		{
			DEFAULT,
			YESNO,
			OK,
			NONE
		};

		// If this method returns true, the error dialog will be closed.
		typedef bool (*AutoCloseCallback)();

		// Function to be called when dialog box completes.
		typedef void (*CompleteCallback)(bool);

	private:
		int			code_;
		std::string	message_;
		bool		fatal_;
		MessageType	messageType_;
		InputType inputType_;
		AutoCloseCallback	autoClose_;
		CompleteCallback	complete_;

	public:
		ErrorType( int code, CompleteCallback complete = NULL, InputType inputType = DEFAULT, AutoCloseCallback autoClose = NULL, bool fatal = false )
			: code_( code )
			, fatal_( fatal )
			, messageType_( CODE )
			, inputType_( inputType )
			, autoClose_( autoClose )
			, complete_( complete )
		{
		}

		ErrorType( const std::string &message, CompleteCallback complete = NULL, InputType inputType = DEFAULT, AutoCloseCallback autoClose = NULL, bool fatal = false )
			: code_( 0 )
			, message_( message )
			, fatal_( fatal )
			, messageType_( STRING )
			, inputType_( inputType )
			, autoClose_( autoClose )
			, complete_( complete )
		{
		}

		int GetCode() const { return code_; }
		const std::string &GetMessage() const { return message_; }
		bool IsFatal() const { return fatal_; }
		MessageType GetMessageType() const { return messageType_; }
		InputType GetInputType() const { return inputType_; }
		AutoCloseCallback GetAutoClose() const { return autoClose_; }
		CompleteCallback GetComplete() const { return complete_; }
	};
#else
typedef unsigned int ErrorType;
#endif

/// Display a system error.
/**
 * @param errorCode Current error code.
 */
void DisplayError( const ErrorType &errorCode );

#endif