#ifndef _DISPLAYMODE_H_
#define _DISPLAYMODE_H_

struct DisplayMode : public Object
{


	int Width, Height;

};
/// Gets all supported display modes for the running machine.
inline std::vector<std::shared_ptr<DisplayMode> > GetSupportedDisplayModes()
{
	// FIXME: Implement.
	return std::vector<std::shared_ptr<DisplayMode> >();
}

#endif
