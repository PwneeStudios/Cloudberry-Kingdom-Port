#include <cafe/mem.h>

MEMHeapHandle gThreadsafeHeap = MEM_HEAP_INVALID_HANDLE;

static void *AllocFromDefaultHeap( u32 size )
{
	return MEMAllocFromExpHeapEx( gThreadsafeHeap, size, PPC_IO_BUFFER_ALIGN );
}

static void *AllocFromDefaultHeapEx( u32 size, int alignment )
{
	return MEMAllocFromExpHeapEx( gThreadsafeHeap, size, alignment );
}

static void FreeToDefaultHeap( void *block )
{
	MEMFreeToExpHeap( gThreadsafeHeap, block );
}

static MEMHeapHandle InitDefaultHeap(void *startAddress, u32 size)
{
	gThreadsafeHeap = MEMCreateExpHeapEx( startAddress, size, MEM_HEAP_OPT_THREAD_SAFE );
	return gThreadsafeHeap;
}

#define MIN_DEFAULTHEAP_ALIGNMENT 4

int App_DynLoad_DefaultAlloc( int aMemBytes, int aMemAlign, void **appRetPtr )
{
	if( !appRetPtr )
		return OSDYNLOAD_ERR_ALLOCATOR_PTR_BAD;

	if( aMemAlign < 0 )
	{
		if( aMemAlign > -MIN_DEFAULTHEAP_ALIGNMENT )
			aMemAlign = -MIN_DEFAULTHEAP_ALIGNMENT;
	}
	else
	{
		if( aMemAlign < MIN_DEFAULTHEAP_ALIGNMENT )
			aMemAlign = MIN_DEFAULTHEAP_ALIGNMENT;
	}

	*appRetPtr = MEMAllocFromDefaultHeapEx( aMemBytes, aMemAlign );
	if( *appRetPtr )
		return 0;

	return OSDYNLOAD_ERR_MEMORY_ALLOCATION_FAILURE;
}

void App_DynLoad_DefaultFree( void *pAddr )
{
	MEMFreeToDefaultHeap( pAddr );
}

void __preinit_user(MEMHeapHandle *aMEM1_heap, MEMHeapHandle *aMEMFG_heap, MEMHeapHandle *aMEM2_heap)
{
	MEMHeapHandle	defaultHeap	= *aMEM2_heap;
	u32				freeBytes	= MEMGetAllocatableSizeForExpHeap( defaultHeap );
	void *			ptr			= MEMAllocFromDefaultHeapEx( freeBytes, 4 );

	MEMAllocFromDefaultHeap = AllocFromDefaultHeap;
	MEMAllocFromDefaultHeapEx = AllocFromDefaultHeapEx;
	MEMFreeToDefaultHeap = FreeToDefaultHeap;

	*aMEM2_heap = InitDefaultHeap( ptr, freeBytes );

	OSDynLoad_SetAllocator( App_DynLoad_DefaultAlloc, App_DynLoad_DefaultFree );
}
