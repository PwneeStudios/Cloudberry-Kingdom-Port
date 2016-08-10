#ifndef _EFFECTPASS_H_
#define _EFFECTPASS_H_

// Forward declarations.
class Effect;

class EffectPass
{

	struct EffectPassInternal *internal_;

public:

	EffectPass( Effect &effect, unsigned int id );
	~EffectPass();

	void Apply();

};

#endif
