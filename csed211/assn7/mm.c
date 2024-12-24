/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* single word (4) or double word (8) alignment */
typedef size_t word_t;
#define WORD (sizeof(word_t))
#define WORD_ALIGNMENT 2
#define ALIGNMENT ((WORD) * (WORD_ALIGNMENT))

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT) - 1) & ~((ALIGNMENT) - 1))
/* rounds down to the nearest multiple of ALIGNMENT */
#define TRUNCATE(size) ((size) & ~((ALIGNMENT) - 1))

typedef struct block {
    word_t header;
    uint8_t payload[0];
} block_t;

word_t b_get_size(block_t *block)
{
    return block->header & ~((word_t) 0x1);
}

bool b_get_alloc(block_t *block)
{
    return block->header & 0x1;
}

word_t b_header(word_t size, bool alloc)
{
    return size | alloc;
}

void b_write_header(block_t *block, word_t size, bool alloc)
{
    block->header = b_header(size, alloc);
}

block_t *b_from_payload(uint8_t *payload)
{
    return (block_t *) (payload - WORD);
}

block_t *heap_start(void)
{
    return (block_t *) (mem_heap_lo() + ALIGN(WORD) - WORD);
}

block_t *heap_end(void)
{
    return (block_t *) (mem_heap_lo() + TRUNCATE(mem_heapsize()) - WORD);
}

block_t *find_next(block_t *block)
{
    return (block_t *) ((uint8_t *) block + b_get_size(block));
}

block_t *find_first_fit(word_t asize)
{
    block_t *it;
    word_t sum;
    for (it = heap_start(); it->header != b_header(0, 1); it = find_next(it))
    {
        if (b_get_alloc(it))
        {
            if (sum >= asize)
                return it;
            sum = 0;
        }
        else
            sum += b_get_size(it);
    }
    return NULL;
}

word_t get_contiguous_free(block_t *block)
{
    word_t sum = 0;
    for (; !b_get_alloc(block); block = find_next(block))
        sum += b_get_size(block);
    return sum;
}

block_t *emplace_block(block_t *block, word_t asize)
{
    word_t free = get_contiguous_free(block);
    if (free >= ALIGN(asize))
    {
        b_write_header(block, ALIGN(asize), 1);
        b_write_header(find_next(block), free - ALIGN(asize), 0);
        return block;
    }
    return NULL;
}

block_t *extend_heap(word_t incr)
{
    b_write_header(heap_end(), ALIGN(incr), 0);
    if (mem_sbrk(TRUNCATE(mem_heapsize()) + ALIGN(incr) - mem_heapsize()) == (void *) -1)
        return NULL;
    b_write_header(heap_end(), 0, 1);
    return heap_end();
}

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    b_write_header(heap_start(), TRUNCATE(mem_heapsize()) - ALIGNMENT, 0);
    b_write_header(heap_end(), 0, 1);
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    word_t block_size = ALIGN(size + WORD);
    block_t *block = find_first_fit(block_size);
    if (!block)
        block = extend_heap(block_size);
    emplace_block(block, block_size);
    return (void *) block->payload;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    ((block_t *) ptr)->header &= ~((word_t) 0x1);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    block_t *block = b_from_payload(ptr);
    word_t avail = b_get_size(block) + get_contiguous_free(find_next(block));
    if (avail >= ALIGN(size))
    {
        emplace_block(block, ALIGN(size));
        return block->payload;
    }
    else
    {
        block_t *newblock = find_first_fit(ALIGN(size));
        if (!newblock)
            newblock = extend_heap(ALIGN(size));
        b_write_header(newblock, ALIGN(size), 1);
        memcpy(newblock, block, b_get_size(block));
        mm_free(block);
        return newblock->payload;
    }
}
