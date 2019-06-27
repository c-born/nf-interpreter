////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "nanoCLR_Types.h"
#include "nanoCLR_Runtime.h"


#ifndef _GraphicsMemoryHeap_H
#define _GraphicsMemoryHeap_H 1


extern int HeapBegin;
extern int HeapEnd;
extern int CustomHeapBegin;
extern int CustomHeapEnd;
extern int StackBottom;
extern int StackTop;


// Registers[n] == Rn in ARM terms, R13=sp, R14=lr, R15=pc
typedef void (*AbortHandlerFunc)(CLR_UINT32 cpsr, CLR_UINT32 Registers[16]);

extern "C"
{
void StackOverflow( CLR_UINT32 sp );

void NULL_Pointer_Write();
}

CLR_UINT32 Stack_MaxUsed();

/******************************************************************************************
// Graphics Memory Heap is for use by Porting Kit users who need private memory allocation.
/******************************************************************************************
** Function: GraphicsMemoryHeap_Allocate
** Synopsis: Initializes Graphics Memory Heap from supplied buffer.
** Pointer to buffer is saved in global variable.
** Later is used for allocation of blocks by GraphicsMemoryHeap_Allocate
** Arguments: [pHeapBuffer] - Pointer to heap buffer. This pointer is saved in global variable,
**                            later used by GraphicsMemoryHeap_* function.
**            [pHeapBuffer] - Size of memory block pointed by pHeapBuffer
**************************************************************************************/
void GraphicsMemoryHeap_Initialize( void* pHeapBuffer, CLR_UINT32 heapBuufferSize );



/**********************************************************************
** Function: GraphicsMemoryHeap_Allocate
** Synopsis: Allocates block of memory from heap buffer initialized by GraphicsMemoryHeap_Initialize
** Arguments: [len]                  - Size of block to allocate.
** Returns:   Pointer to newly allocated memory
              or NULL if there is no free memory to accomodate block of size len
**********************************************************************/
void* GraphicsMemoryHeap_Allocate   ( size_t len );

/**********************************************************************
**
** Function: GraphicsMemoryHeap_Release
**
** Synopsis: Releases memory block allocated by GraphicsMemoryHeap_Allocate
**
**
** Arguments: [pHeapBlock] - Memory block to release.
**
**********************************************************************/
void  GraphicsMemoryHeap_Release    ( void*  pHeapBlock );


/**********************************************************************
**
** Function: GraphicsMemoryHeap_ReAllocate
**
** Synopsis: Reallocates memory on an existing pointer and copies bck the
** data
**
** Arguments: [pHeapBlock] - Memory block to reallocate.
** Arguments: [len]        - Size of block to allocate.
**
**********************************************************************/
void* GraphicsMemoryHeap_ReAllocate( void*  pHeapBlock, size_t len );

/**********************************************************************
**
** Function: GraphicsMemoryHeap_IsAllocated
**
** Synopsis: Checks if pHeapBlock points to memory block allocated by GraphicsMemoryHeap_Allocate
**
** Arguments: [pHeapBlock] - Memory block to release.
**
** Returns:   TRUE if pHeapBlock points to memory allocated, FALSE otherwise.
**********************************************************************/
BOOL  GraphicsMemoryHeap_IsAllocated( void*  pHeapBlock );

/**********************************************************************
**
** Function: HAL_Init_Custom_Heap
**
** Synopsis: Initializes Graphics Memory Heap with memory buffer provided by CustomHeapLocation function.
**
**********************************************************************/
inline void HAL_Init_Custom_Heap()
{
    CLR_UINT8* BaseAddress = 0;
    CLR_UINT32 SizeInBytes = 0;

    // Retrieve location for Custom Heap. The location is defined in scatter file.
    CustomHeapLocation( BaseAddress, SizeInBytes );

    // Initialize custom heap with heap block returned from CustomHeapLocation
    GraphicsMemoryHeap_Initialize( BaseAddress, SizeInBytes );
}


void* private_malloc ( size_t len             );
void  private_free   ( void*  ptr             );
void* private_realloc( void*  ptr, size_t len );


template <typename T> __inline void private_release( T& ref )
{
    T ptr = ref;

    if(ptr)
    {
        ref = NULL;

        private_free( ptr );
    }
}


__inline void* ReAllocate_NotImplemented( void * ptr, size_t len ) { ASSERT(FALSE); return NULL; }


#define HAL_DECLARE_CUSTOM_HEAP(allocFtn,freeFtn,reallocFtn)                           \
    extern "C" {                                                                       \
    void* private_malloc ( size_t len             ) { return allocFtn  ( len      ); } \
    void  private_free   ( void*  ptr             ) {        freeFtn   ( ptr      ); } \
    void* private_realloc( void*  ptr, size_t len ) { return reallocFtn( ptr, len ); } \
    }

#define HAL_DECLARE_NULL_HEAP()                                      \
    extern "C" {                                                     \
    void* private_malloc ( size_t len             ) { return NULL; } \
    void  private_free   ( void*  ptr             ) {              } \
    void* private_realloc( void * ptr, size_t len ) { return NULL; } \
    }


//--//

extern CLR_UINT32 LOAD_IMAGE_Start;
extern CLR_UINT32 LOAD_IMAGE_Length;
extern CLR_UINT32 LOAD_IMAGE_CRC;
extern CLR_UINT32 LOAD_IMAGE_CalcCRC;


#if !defined(BUILD_RTM)

CLR_UINT32 Checksum_RAMConstants();

// prototype this as a continuation capable function

void Verify_RAMConstants( void* arg );

#endif  // !defined(BUILD_RTM)

//--//

struct SECTOR_BIT_FIELD
{
    static const CLR_UINT32 c_MaxSectorCount = 287; // pxa271 has 259 sectors, 287 == 9 * sizeof(CLR_UINT32) - 1, which is the next biggest whole
    static const CLR_UINT32 c_MaxFieldUnits  = (c_MaxSectorCount + 1) / (8 * sizeof(CLR_UINT32)); // bits
    volatile     CLR_UINT32 BitField[c_MaxFieldUnits];
};

struct TINYBOOTER_KEY_CONFIG
{
    CLR_UINT8  SectorKey[260]; //RSAKey 4 bytes (exponent) + 128 bytes (module) + 128 bytes (exponent)
};

struct CONFIG_SECTOR_VERSION
{
    CLR_UINT8 Major;
    CLR_UINT8 Minor;
    CLR_UINT8 TinyBooter;
    CLR_UINT8 Extra;
};

struct SECTOR_BIT_FIELD_TB
{
    static const CLR_UINT32 c_MaxBitCount    = 8640;
    static const CLR_UINT32 c_MaxFieldUnits  = (c_MaxBitCount / (8 * sizeof(CLR_UINT32))); // bits
    volatile     CLR_UINT32 BitField[c_MaxFieldUnits];
};


#endif  // _GraphicsMemoryHeap_H
