#ifndef _EFFECTPASS_H_
#define _EFFECTPASS_H_

class EffectPass
{

	unsigned int progId_;

public:

	EffectPass( unsigned int progId );
	void Apply();

};

#endif
