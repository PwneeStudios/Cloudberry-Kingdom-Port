/**
 * @file
 *
 * Base resource.
 */
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

/**
 * Base resource.
 */
class Resource
{

	/// Path to resource.
	std::string path_;

public:

	virtual ~Resource() { }

	/// Load resource data.
	virtual void Load() { }

	/// Unload resource data.
	virtual void Unload() { }

	/// Create GPU counterpart for the resource.
	virtual void GpuCreate() { }

	/// Destroy GPU counterpart for the resource.
	virtual void GpuDestroy() { }

	/// Set resource path.
	/**
	 * @param path Path to resource.
	 */
	void SetPath( const std::string &path ) { path_ = path; }
	
	/// Get resource path.
	/**
	 * @return Resource location.
	 */
	const std::string &GetPath() const { return path_; }

};

#endif
