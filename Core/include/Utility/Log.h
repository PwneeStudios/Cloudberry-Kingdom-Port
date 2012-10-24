/**
 * @file
 *
 * Logging subsystem.
 */
#ifndef _LOG_H_
#define _LOG_H_

#include <Architecture/Singleton.h>
#include <string>
#include <vector>

/**
 * Listener intrerface for receiving log messages.
 */
class LogListener
{
	
public:

	virtual ~LogListener() { }

	virtual void Write( const std::string &text ) = 0;

};

class Log : public Singleton< Log >
{

	typedef std::vector< LogListener * > ListenerList;
	ListenerList listeners_;

public:

	Log();
	~Log();

	void AddListener( LogListener &listener );
	void RemoveListener( LogListener &listener );

	void Write( const char *fmt, ... );

	static Log &GetSingleton();

};

#define LOG Log::GetSingleton()

#endif
