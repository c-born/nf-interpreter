// tinyclr - 
// an implementation of the memory managment system for the JPEG library using tinyclr's
// Allocate() and Release().

extern "C" 
{
#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"
#include "jmemsys.h"
}

struct CLR_RT_Memory
{
    static void  Release ( void*  ptr                     );
    static void* Allocate( CLR_INT32 len, unsigned int flags );
};

extern "C"
{
    void  CLR_RT_Memory__Release ( void*  ptr ) {        CLR_RT_Memory::Release ( ptr    ); }
    void* CLR_RT_Memory__Allocate( CLR_INT32 len ) { return CLR_RT_Memory::Allocate( len, 0 ); }

    
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    GLOBAL(void *)
    jpeg_get_small( j_common_ptr cinfo, CLR_INT32 sizeofobject )
    {
        return (void *) CLR_RT_Memory__Allocate( sizeofobject );
    }

    GLOBAL(void)
    jpeg_free_small( j_common_ptr cinfo, void * object, CLR_INT32 sizeofobject )
    {
        CLR_RT_Memory__Release( object );
    }

    GLOBAL(void FAR *)
    jpeg_get_large( j_common_ptr cinfo, CLR_INT32 sizeofobject )
    {
        return (void *) CLR_RT_Memory__Allocate( sizeofobject );
    }

    GLOBAL(void)
    jpeg_free_large( j_common_ptr cinfo, void FAR * object, CLR_INT32 sizeofobject )
    {
        CLR_RT_Memory__Release( object );
    }

    GLOBAL(long)
    jpeg_mem_available( j_common_ptr cinfo, long min_bytes_needed, long max_bytes_needed, long already_allocated )
    {
        // We don't have a mechanism to tell this, so just promise the sky for now, and let it fail later (if it does fail)
        return max_bytes_needed;
    }

    GLOBAL(void)
    jpeg_open_backing_store( j_common_ptr cinfo, backing_store_ptr info, long total_bytes_needed )
    {
        // We don't support backing stores
        ERREXIT(cinfo, JERR_NO_BACKING_STORE);
    }

    GLOBAL(long)
    jpeg_mem_init( j_common_ptr cinfo )
    {
        // Do nothing
        return 0;
    }

    GLOBAL(void)
    jpeg_mem_term( j_common_ptr cinfo )
    {
        // Do nothing
    }
}
#pragma GCC diagnostic pop