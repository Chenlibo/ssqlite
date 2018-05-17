#ifndef TCBL_CACHEDVFS_H
#define TCBL_CACHEDVFS_H

#include <stddef.h>

#include "vfs.h"

typedef struct cvfs_entry *cvfs_entry;

struct cvfs_entry {
    size_t offset;
    size_t len;
    char* data;
    size_t entry_len;
    cvfs_entry lru_next; // TODO use when implementing delete
    cvfs_entry lru_prev;
};

typedef struct cvfs {
    cvfs_entry cache_index;
    char* cache_data;
    char* cache_free_list;
    cvfs_entry lru_first;
    cvfs_entry lru_last;
    size_t page_size;
    size_t num_pages;
    size_t num_index_entries;
    size_t len;
    uint64_t cache_hit_ct;
    uint64_t cache_miss_ct;
} *cvfs;

typedef struct cvfs_h {
    cvfs cvfs;
    int (*fill_fn)(void *, void *, size_t, size_t, size_t *);
    void *fill_ctx;
} *cvfs_h;


/*
 * Cache semantics are read-through but not write-through, so updating
 * the cache does not update the underlying data file.
 */
int vfs_cache_allocate(cvfs *, size_t page_size, size_t num_pages);

int vfs_cache_open(cvfs, cvfs_h *,
                   int (*fill_fn)(void *ctx, void *data, size_t offset, size_t len, size_t *out_len),
                   void* fill_ctx);
int vfs_cache_close(cvfs_h);
int vfs_cache_get(cvfs_h, void* data, size_t offset, size_t len, size_t *out_len);
int vfs_cache_update(cvfs_h, void* data, size_t offset, size_t len);
int vfs_cache_clear(cvfs_h);
int vfs_cache_len_get(cvfs_h, size_t*);
int vfs_cache_len_update(cvfs_h, size_t);
int vfs_cache_free(cvfs);

#endif //TCBL_CACHEDVFS_H
