#ifndef _DISPLAYMODE_H_
#define _DISPLAYMODE_H_

struct DisplayMode : public Object
{


	int Width, Height;

	DisplayMode() : Width( 0 ), Height( 0 ) { }

};
/// Gets all supported display modes for the running machine.
inline std::vector<std::shared_ptr<DisplayMode> > GetSupportedDisplayModes()
{
	// FIXME: Implement.
	return std::vector<std::shared_ptr<DisplayMode> >();
}

#endif
