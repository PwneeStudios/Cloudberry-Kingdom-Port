/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#ifndef __HLPLAYER_INTERNAL_ALLOCATOR_H__
#define __HLPLAYER_INTERNAL_ALLOCATOR_H__

#include <stdlib.h>
#include <string.h>
#include <cell/cell_fs.h>

namespace cell {
namespace Sail {

class fsallocator
{
public:
	fsallocator() {}
	virtual ~fsallocator() {}

	virtual int FsOpen(const char *pPath,
					int         flag,
					int        *pFd,
					void       *arg  /*must be NULL*/,
					uint64_t    size /*must be 0*/)
	{
		return cellFsOpen(pPath,flag,pFd,arg,size);
	};

	virtual int FsOpenSecond(const char *pPath,
					int         flag,
					int         fd,
					void       *arg  /*must be NULL*/,
					uint64_t    size /*must be 0*/)
	{
		return cellFsOpen(pPath,flag,&fd,arg,size);
	};

	virtual int FsClose(int fd)
	{
		return cellFsClose(fd);
	};

	virtual int FsFstat(int fd, struct CellFsStat *pStat)
	{
		return cellFsFstat(fd,pStat);
	};

	virtual int FsRead(int       fd,
					void     *pBuf,
					uint64_t  numBytes,
					uint64_t *pNumRead)
	{
		return cellFsRead(fd,pBuf,numBytes,pNumRead);
	};

	virtual int FsLseek(int       fd,
                   int64_t   offset,
                   int       whence,
                   uint64_t *pPosition)
	{
		return cellFsLseek(fd,offset,whence,pPosition);
	};

	virtual int FsCancel(int fd)
	{
        (void)fd;
		return CELL_OK;
	};
};
class memallocator
{
public:
	memallocator(void) { }
	virtual ~memallocator(void) { }
	virtual void* Allocate(uint32_t size, uint32_t alignment=0) {
        if (alignment==0) {
			return malloc(size);
		} else {
			return memalign(alignment, size);
        }
	};

	virtual void Deallocate(void* pMemory) {
		free(pMemory);
	};

	virtual void* AllocateTexture(uint32_t size, uint32_t alignment=0) {
		return memalign(alignment, size);	
	};

	virtual void DeallocateTexture(void* pMemory) {
		free(pMemory);
	};
};

} // namespace Sail
} // namespace cell

#endif //  __HLPLAYER_INTERNAL_ALLOCATOR_H__

