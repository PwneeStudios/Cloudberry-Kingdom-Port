/**
 * @file
 *
 * Color related functionality.
 */
#ifndef _COLOR_H_
#define _COLOR_H_

struct Color
{
	union
	{
		struct 
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};

		unsigned int PackedValue;
	};
};

#endif
