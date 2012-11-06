/**
 * @file
 *
 * Input abstraction.
 */
#ifndef _INPUT_H_
#define _INPUT_H_

#include <Architecture/Singleton.h>

// Pick implementation.
#ifdef CAFE
	#include "InputWiiU.h"
#else
	#include "InputPc.h"
#endif

/// Input subsystem.
class Input : public Singleton< Input >
{

	/// Core implementation.
#ifdef CAFE
	InputWiiU impl_;
#else
	InputPc impl_;
#endif

public:

	/// Update input subsystem.
	void Update()
	{
		impl_.Update();
	}

	/// Get input singleton.
	static Input &GetSingleton();
};

// Nice alias for input subsystem.
#define INPUT Input::GetSingleton()

#endif
