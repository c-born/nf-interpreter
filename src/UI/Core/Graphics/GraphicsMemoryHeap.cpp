//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include "nanoCLR_Types.h"
#include "nanoCLR_Runtime.h"
#include "nanoCLR_Graphics.h"

struct BlockHeader
{
	struct BlockHeader* next;
	struct BlockHeader* prev;
	CLR_UINT32 length;
	CLR_UINT32 signature;
	CLR_UINT32 head_guard;
};


static const CLR_UINT32 c_Free = 0xDEADBEEF;
static const CLR_UINT32 c_Busy = 0xDEADBE5E;
static const CLR_UINT32 c_Guard = 0xbab1f00d;
static struct BlockHeader* g_s_FirstCluster;

void GraphicsMemoryHeap_Initialize( void* buffer, CLR_UINT32 length )
{
    struct BlockHeader **s_FirstCluster = (struct BlockHeader **) &g_s_FirstCluster;
    *s_FirstCluster = (struct BlockHeader *) buffer;
    (*s_FirstCluster)->length     = length;
    (*s_FirstCluster)->next       = NULL;
    (*s_FirstCluster)->prev       = NULL;
    (*s_FirstCluster)->signature  = c_Free;
    (*s_FirstCluster)->head_guard = c_Guard;
}
bool GraphicsMemoryHeap_IsAllocated( void *ptr )
{
    if(ptr)
    {
        struct BlockHeader* blk = (struct BlockHeader*)ptr; blk--;
        if(blk->signature == c_Busy)
        {
            return TRUE;
        }
        else if(blk->signature == c_Free)
        {
            return FALSE;
        }
        else
        {
            // corrupt pointer to memory
            hal_printf( "GraphicsMemoryHeap: Bad Ptr: 0x%08x\r\n", (size_t)ptr );
            ASSERT(0);
            return FALSE;
        }
    }
    return FALSE;
}
void GraphicsMemoryHeap_Release( void* ptr )
{
    if(ptr)
    {
        struct BlockHeader* next;
        struct BlockHeader* prev;
        struct BlockHeader* blk = (struct BlockHeader*)ptr; blk--;
        if(blk->head_guard != c_Guard)
        {
            hal_printf( "GraphicsMemoryHeap_Release: Memory block head corruption: %08x %08x\r\n", blk->head_guard, blk->length );
            HARD_BREAKPOINT();
        }
        if(*(CLR_UINT32*)((CLR_UINT32)&blk[0] + blk->length - sizeof( c_Guard )) != c_Guard)
        {
            hal_printf( "GraphicsMemoryHeap_Release: Memory block tail corruption: %08x %08x\r\n", *(CLR_UINT32 *)((CLR_UINT32)&blk[0] + blk->length - sizeof( c_Guard )), blk->length );
            HARD_BREAKPOINT();
        }
        blk->signature = c_Free;
        //
        // First merge with the following block, if free.
        //
        next = blk->next;
        if(next && next->signature == c_Free)
        {
            struct BlockHeader* nextnext;
            blk->length += next->length;
            nextnext = next->next;
            blk->next = nextnext;
            if(nextnext) nextnext->prev = blk;
        }
        //
        // Then merge with the preceding block, if free.
        //
        prev = blk->prev;
        if(prev && prev->signature == c_Free)
        {
            prev->length += blk->length;
            next = blk->next;
            prev->next = next;
            if(next) next->prev = prev;
        }
    }
    else
    {
        // releasing a null pointer is OK
        //ASSERT(0);
    }
}
void* GraphicsMemoryHeap_Allocate( size_t len )
{
    struct BlockHeader **pptr = (struct BlockHeader **) &g_s_FirstCluster;
    struct BlockHeader *ptr = *pptr;
    len += sizeof( struct BlockHeader );
    len += sizeof( c_Guard );   // leave room for tail guard
	len  = (len + sizeof(CLR_UINT32) - 1) & ~(sizeof(CLR_UINT32)-1);

    while(ptr)
    {
        if(ptr->signature == c_Free && ptr->length >= len)
        {
            if(ptr->length <= (len + sizeof(struct BlockHeader)*2))
            {
                //
                // Perfect or almost perfect fit, nothing else to do.
                //

                // note that ptr->length is set to block size, not allocated size,
                // which then gets lost, so we can only check tail guard
                // based on actual size, not requested size, blah...
                break;
            }
            else
            {
                //
                // Split the block in two.
                //
                struct BlockHeader* prev;
                struct BlockHeader* next;

                prev = ptr;
                ptr = (struct BlockHeader*)((UINT8*)ptr + ptr->length - len);
                next = prev->next;

                ptr->next = next;
                ptr->prev = prev;

                         prev->next = ptr;
                if(next) next->prev = ptr;

                ptr ->length  = (int)len;
                prev->length -= (int)len;
                break;
            }
        }

        ptr = ptr->next;
    }
    if(ptr)
    {
        ptr->signature  = c_Busy;

		ptr->head_guard = c_Guard;                                          // set the head guard word
        *(CLR_UINT32 *)((CLR_UINT32)&ptr[0] + ptr->length - sizeof( c_Guard )) = c_Guard;   // set the tail guard word

		return &ptr[1];
    }
    else
    {
        hal_printf( "    Memory: OUTOFMEMORY!! %d\r\n", len );
        return NULL;
    }
}
void* GraphicsMemoryHeap_ReAllocate( void* ptr, size_t len )
{
    void* p = GraphicsMemoryHeap_Allocate( len ); if(!p) return NULL;
     if(ptr)
     {
        struct BlockHeader* blk = (struct BlockHeader*)ptr; blk--;
        memcpy( p, ptr, len > blk->length ? blk->length : len );
        GraphicsMemoryHeap_Release( ptr );
        ptr = p;
    }
    return p;
}

