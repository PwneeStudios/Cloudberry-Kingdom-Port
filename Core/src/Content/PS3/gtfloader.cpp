/*  SCE CONFIDENTIAL
 *  PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *  Copyright (C) 2008 Sony Computer Entertainment Inc.
 *  All Rights Reserved.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <cell/cell_fs.h>
#include <cell/sysmodule.h>

#include "gcmutil_error.h"
#include "gtfloader.h"

namespace{
	class CMyFsPrxLoader{
	protected:
		bool mIsLoadFsPrx;
	public:	
		CMyFsPrxLoader(void): mIsLoadFsPrx(false)
		{
			if(cellSysmoduleIsLoaded(CELL_SYSMODULE_FS) != CELL_SYSMODULE_LOADED){
				mIsLoadFsPrx = true;
				cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
			}
		}
		
		virtual ~CMyFsPrxLoader(void){
			if(mIsLoadFsPrx){
				cellSysmoduleUnloadModule(CELL_SYSMODULE_FS);
			}
		}
	};

	const uint32_t SIZE_MAX = 0xFFFFFFFFUL;
}

static const CellGtfFileHeader* get_header(const uint8_t* gtf_buffer, uint32_t size)
{
	if(!gtf_buffer) return 0;
	if(size < sizeof(CellGtfFileHeader)) return 0;
	
	const CellGtfFileHeader *header = reinterpret_cast<const CellGtfFileHeader *>(gtf_buffer);
	
	if(size < header->size) return 0;
	
	return header;
}

static const CellGtfTextureAttribute* get_attribute(const uint8_t* gtf_buffer, uint32_t size, uint32_t index)
{
	const CellGtfFileHeader *header = get_header(gtf_buffer, size);

	if(!header) return 0;
	
	if(header->numTexture < index) return 0;
	
	const CellGtfTextureAttribute* attr_top = reinterpret_cast<const CellGtfTextureAttribute*>(gtf_buffer + sizeof(CellGtfFileHeader));
	
	return attr_top + index;
}

static bool fileReadFile(const char *fname, uint8_t **buffer, uint32_t *buf_size, uint32_t offset = 0, uint32_t size = SIZE_MAX)
{
	if(!fname) return false;
	if(!buffer) return false;
	if(!buf_size) return false;
	
	*buf_size = 0;
	*buffer = 0;
	
	CMyFsPrxLoader fs_prx_loader;
	
	CellFsStat fstat;
	if(cellFsStat(fname, &fstat) != CELL_FS_SUCCEEDED) return false;
	if(SIZE_MAX < fstat.st_size) return false;
	
	if(size == SIZE_MAX){
		size = static_cast<uint32_t>(fstat.st_size) - offset;
	}
	
	int fd;
	if(cellFsOpen(fname, CELL_FS_O_RDONLY, &fd, NULL, 0) != CELL_FS_SUCCEEDED)
	{
		return false;
	}
	
	// seek
	uint64_t pos;
	if(cellFsLseek(fd, offset, CELL_FS_SEEK_SET, &pos) != CELL_FS_SUCCEEDED){
		return false;
	}
	
	if(size > 0){
		*buffer = new uint8_t[size];

		if(*buffer == 0) return false;
		
		uint64_t nread;
		if(cellFsRead(fd, *buffer, size, &nread) != CELL_FS_SUCCEEDED){
			nread = 0;
		}
		
		if(nread == 0){
			*buf_size = 0;
			delete [] *buffer, *buffer = 0;
		}else{
			*buf_size = size;
		}
	}
	
	cellFsClose(fd);

	return true;
}

uint32_t cellGtfGetPackedTextureNumberFromMemory(const uint8_t* gtf_buffer, uint32_t size)
{
	const CellGtfFileHeader *header = get_header(gtf_buffer, size);

	if(!header) return 0;
	
	return header->numTexture;
}

uint32_t cellGtfGetPackedTextureSizeFromMemory(const uint8_t* gtf_buffer, uint32_t size, uint32_t index)
{
	const CellGtfTextureAttribute* attr = get_attribute(gtf_buffer, size, index);
	
	if(!attr) return 0;
	
	return attr->textureSize;
}

CELL_GTF_RESULT cellGtfLoadPackedTextureFromMemory(const uint8_t* gtf_buffer, uint32_t size, uint32_t index, CellGcmTexture* texture, uint8_t location, void* image)
{
	const CellGtfTextureAttribute* attr = get_attribute(gtf_buffer, size, index);
	
	if(!attr) return CELL_GTF_FAILED;
	if(!texture) return CELL_GTF_FAILED;
	if(!image) return CELL_GTF_FAILED;
	if((location != CELL_GCM_LOCATION_LOCAL) && (location != CELL_GCM_LOCATION_MAIN)) return CELL_GTF_FAILED;
	
	if(size < attr->offsetToTex + attr->textureSize) return CELL_GTF_FAILED;
	*texture = attr->tex;
	
	texture->location = location;
	CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(image, &texture->offset));
	
	memmove(image, gtf_buffer + attr->offsetToTex, attr->textureSize);
	
	return CELL_GTF_OK;
}


uint32_t cellGtfGetPackedTextureNumber(const char* filename)
{
	uint8_t *addr = 0;
	uint32_t size = 0;
	
	fileReadFile(filename, &addr, &size);
	
	uint32_t ret = cellGtfGetPackedTextureNumberFromMemory(addr, size);
	
	if(addr != 0){
		delete [] addr, addr = 0;
		size = 0;
	}
	
	return ret;
}

uint32_t cellGtfGetPackedTextureSize(const char* filename, uint32_t index)
{
	uint8_t *addr = 0;
	uint32_t size = 0;
	
	fileReadFile(filename, &addr, &size);
	
	uint32_t ret = cellGtfGetPackedTextureSizeFromMemory(addr, size, index);
	
	if(addr != 0){
		delete [] addr, addr = 0;
		size = 0;
	}
	
	return ret;
}

CELL_GTF_RESULT cellGtfLoadPackedTexture(const char* filename, uint32_t index, CellGcmTexture* texture, uint8_t location, void* image)
{
	uint8_t *addr = 0;
	uint32_t size = 0;
	
	fileReadFile(filename, &addr, &size);
	
	CELL_GTF_RESULT ret = cellGtfLoadPackedTextureFromMemory(addr, size, index, texture, location, image);
	
	if(addr != 0){
		delete [] addr, addr = 0;
		size = 0;
	}
	
	return ret;
}


uint32_t cellGtfGetTextureSizeFromMemory(const uint8_t* gtf_buffer, uint32_t size)
{
	return cellGtfGetPackedTextureSizeFromMemory(gtf_buffer, size, 0);
}

CELL_GTF_RESULT cellGtfLoadTextureFromMemory(const uint8_t* gtf_buffer, uint32_t size, CellGcmTexture* texture, uint8_t location, void* image)
{
	return cellGtfLoadPackedTextureFromMemory(gtf_buffer, size, 0, texture, location, image);
}

uint32_t cellGtfGetTextureSize(const char* filename)
{
	return cellGtfGetPackedTextureSize(filename, 0);
}

CELL_GTF_RESULT cellGtfLoadTexture(const char* filename, CellGcmTexture* texture, uint8_t location, void* image)
{
	return cellGtfLoadPackedTexture(filename, 0, texture, location, image);
}

CELL_GTF_RESULT cellGtfLoadWholeTextureFromMemory(const uint8_t* gtf_buffer, uint32_t size, CellGcmTexture* texture_array, uint8_t location, void* image)
{
	if(!texture_array) return CELL_GTF_FAILED;
	if(!image) return CELL_GTF_FAILED;

	uint32_t num_tex = cellGtfGetPackedTextureNumberFromMemory(gtf_buffer, size);

	if(num_tex == 0) return CELL_GTF_FAILED;
	
	for(uint32_t index = 0; index < num_tex; ++index){
		const CellGtfTextureAttribute* base_attr = get_attribute(gtf_buffer, size, 0);
		const CellGtfTextureAttribute* attr = get_attribute(gtf_buffer, size, index);
		if(!base_attr) return CELL_GTF_FAILED;
		if(!attr) return CELL_GTF_FAILED;
		
		uint32_t ret = cellGtfLoadPackedTextureFromMemory(gtf_buffer, size, index, texture_array + index, location, reinterpret_cast<uint8_t*>(image) + attr->offsetToTex - base_attr->offsetToTex);
		if(ret != CELL_GTF_OK) return CELL_GTF_FAILED;
	}
	
	return CELL_GTF_OK;
}

CELL_GTF_RESULT cellGtfLoadWholeTexture(const char* filename, CellGcmTexture* texture_array, uint8_t location, void* image)
{
	uint8_t *addr = 0;
	uint32_t size = 0;
	
	fileReadFile(filename, &addr, &size);
	
	CELL_GTF_RESULT ret = cellGtfLoadWholeTextureFromMemory(addr, size, texture_array, location, image);
	
	if(addr != 0){
		delete [] addr, addr = 0;
		size = 0;
	}
	
	return ret;
}

CELL_GTF_RESULT cellGtfCalculateMemorySize(CellGtfTextureAttribute* attrib, uint32_t *size)
{
	if(!size) return CELL_GTF_FAILED;
	
	*size = 0;
	
	if(!attrib) return CELL_GTF_FAILED;
	
	*size = attrib->textureSize;
	
	return CELL_GTF_OK;
}

CELL_GTF_RESULT cellGtfReadFileHeaderFromMemory(const uint8_t* gtfptr, CellGtfFileHeader* header)
{
	if(!header) return CELL_GTF_FAILED;

	const CellGtfFileHeader *ptr_header = get_header(gtfptr, SIZE_MAX);
	if(!ptr_header) return CELL_GTF_FAILED;

	*header = *ptr_header;

	return CELL_GTF_OK;
}

CELL_GTF_RESULT cellGtfReadTextureAttributeFromMemory(const uint8_t* gtfptr, uint32_t id, CellGtfTextureAttribute* attribs)
{
	if(!attribs) return CELL_GTF_FAILED;

	uint32_t num_tex = cellGtfGetPackedTextureNumberFromMemory(gtfptr, SIZE_MAX);

	if(num_tex == 0) return CELL_GTF_FAILED;
	
	for(uint32_t index = 0; index < num_tex; ++index){
		const CellGtfTextureAttribute* base_attr = get_attribute(gtfptr, SIZE_MAX, 0);
		const CellGtfTextureAttribute* attr = get_attribute(gtfptr, SIZE_MAX, index);
		if(!base_attr) return CELL_GTF_FAILED;
		if(!attr) return CELL_GTF_FAILED;

		if(attr->id != id) continue;
		
		*attribs = *attr;
		
		return CELL_GTF_OK;
	}

	return CELL_GTF_FAILED;
}

CELL_GTF_RESULT cellGtfReadFileHeader(const char* filename, CellGtfFileHeader* header)
{
	uint8_t *addr = 0;
	uint32_t size = 0;
	
	fileReadFile(filename, &addr, &size);
	
	CELL_GTF_RESULT ret = cellGtfReadFileHeaderFromMemory(reinterpret_cast<uint8_t*>(addr), header);
	
	if(addr != 0){
		delete [] addr, addr = 0;
		size = 0;
	}
	
	return ret;
}

CELL_GTF_RESULT cellGtfReadTextureAttribute(const char* filename, uint32_t index, CellGtfTextureAttribute* attrib)
{
	uint8_t *addr = 0;
	uint32_t size = 0;
	
	fileReadFile(filename, &addr, &size);
	
	CELL_GTF_RESULT ret = cellGtfReadTextureAttributeFromMemory(reinterpret_cast<uint8_t*>(addr), index, attrib);
	
	if(addr != 0){
		delete [] addr, addr = 0;
		size = 0;
	}
	
	return ret;
}

CELL_GTF_RESULT cellGtfLoad(const char* filename, uint32_t id, CellGcmTexture* texture, uint8_t location, void* image)
{
	return cellGtfLoadPackedTexture(filename, id, texture, location, image);
}

CELL_GTF_RESULT cellGtfGetTextureAttributeFromMappedMainMemory(uint8_t* gtf_buffer_on_mapped_memory, uint32_t size, CellGtfTextureAttribute** attrib)
{
	if(!gtf_buffer_on_mapped_memory) return CELL_GTF_FAILED;
	if(!attrib) return CELL_GTF_FAILED;

	const CellGtfTextureAttribute* attr = get_attribute(gtf_buffer_on_mapped_memory, size, 0);
	
	*attrib = const_cast<CellGtfTextureAttribute*>(attr);
	
	return CELL_GTF_OK;
}
