#ifndef _PRESENTATIONPARAMETERS_H_
#define _PRESENTATIONPARAMETERS_H_

struct PresentationParameters
{

	int BackBufferFormat;
	int DepthStencilFormat;
	int MultiSampleCount;
	int BackBufferWidth;
	int BackBufferHeight;

	PresentationParameters()
	{
		BackBufferFormat = DepthStencilFormat = MultiSampleCount = 0;
		BackBufferWidth = BackBufferHeight = 0;
	}

};

#endif
