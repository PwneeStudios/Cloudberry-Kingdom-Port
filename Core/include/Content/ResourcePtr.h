/**
 * @file
 *
 * Generic resource pointer.
 */
#ifndef _RESOURCE_PTR_H_
#define _RESOURCE_PTR_H_

#include <ForwardDeclarations.h>

/**
 * Indirection layer for resources.
 */
class ResourceHolder
{

	/// Pointer to any resource.
	Resource *resource_;

public:

	ResourceHolder() : resource_( 0 ) { }
	explicit ResourceHolder( Resource *resource ) : resource_( resource ) { }
	ResourceHolder( const ResourceHolder &holder ) : resource_( holder.resource_ ) { }

	ResourceHolder &operator = ( const ResourceHolder &holder )
	{
		resource_ = holder.resource_;
		return *this;
	}

	ResourceHolder &operator = ( Resource *resource )
	{
		resource_ = resource;
		return *this;
	}

	/// Get pointer to internal resource.
	/**
	 * @return Pointer to internal resource.
	 */
	Resource *GetResource() const { return resource_; }

	/// Set the resource for this holder.
	/**
	 * @param resource Pointer to new resource.
	 */
	void SetResource( Resource *resource ) { resource_ = resource; }

};

/**
 * Pointer to any resource.
 * @tparam ResourceType Type of underlying resource.
 */
template < class ResourceType >
class ResourcePtr
{

	/// Holder for resource this pointer refers to.
	ResourceHolder *holder_;

public:

	ResourcePtr() : holder_( 0 ) { } 
	ResourcePtr( ResourceHolder *holder ) :
		holder_( holder ) { }
	ResourcePtr( const ResourcePtr< ResourceType > &ptr ) :
		holder_( ptr.holder_ ) { }

	ResourcePtr< ResourceType > &operator = ( const ResourcePtr< ResourceType > &ptr )
	{
		holder_ = ptr.holder_;
		return *this;
	}

	ResourceType *operator -> () const
	{
		return static_cast< ResourceType * >( holder_->GetResource() );
	}

	ResourceType &operator * () const
	{
		return *static_cast< ResourceType * >( holder_->GetResource() );
	}

	bool operator == ( const ResourcePtr< ResourceType > &ptr )
	{
		return holder_ == ptr.holder_;
	}

};

#endif
