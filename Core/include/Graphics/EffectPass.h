#ifndef _EFFECTPASS_H_
#define _EFFECTPASS_H_

// Forward declarations.
class Effect;

class EffectPass
{

	struct EffectPassInternal *internal_;

public:

	EffectPass( const Effect &effect, unsigned int id );
	~EffectPass();

	void Apply();

};

#endif
