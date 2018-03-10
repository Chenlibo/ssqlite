#ifndef _TCBL_H
#define _TCBL_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define TCBL_OK 0
#define TCBL_NOT_IMPLEMENTED 1
#define TCBL_ALLOC_FAILURE 2
#define TCBL_BAD_ARGUMENT 3
#define TCBL_BOUNDS_CHECK 4
#define TCBL_TXN_ACTIVE 5
#define TCBL_NO_TXN_ACTIVE 6
#define TCBL_INVALID_LOG 7
#define TCBL_CONFLICT_ABORT 7


typedef struct vfs *vfs;
typedef struct tvfs *tvfs;
typedef struct vfs_fh * vfs_fh;

typedef struct vfs_info {
    size_t vfs_obj_size;
    size_t vfs_fh_size;
    int (*x_open)(vfs, const char *file_name, vfs_fh* file_handle_out);
    int (*x_close)(vfs_fh);
    int (*x_read)(vfs_fh, char *data, size_t offset, size_t len);
    int (*x_write)(vfs_fh, const char *data, size_t offset, size_t len);
    int (*x_file_size)(vfs_fh, size_t* size_out);
    int (*x_free)(vfs);
} *vfs_info;

typedef struct tvfs_info {
    int (*x_begin_txn)(vfs_fh);
    int (*x_commit_txn)(vfs_fh);
    int (*x_abort_txn)(vfs_fh);
} *tvfs_info;

struct vfs_fh {
    vfs vfs;
};

struct vfs {
    vfs_info vfs_info;
};

struct tvfs {
    vfs_info vfs_info;
    tvfs_info tvfs_info;
};

typedef struct tcbl_vfs {
    vfs_info vfs_info;
    tvfs_info tvfs_info;
    size_t page_size;
    vfs underlying_vfs;
} *tcbl_vfs;

typedef struct tcbl_fh {
    vfs vfs;
    vfs_fh underlying_fh;
    vfs_fh underlying_log_fh;
    bool txn_active;
    uint64_t txn_shapshot_lsn;
    size_t txn_begin_log_size;
    struct tcbl_change_log* change_log;
} *tcbl_fh;


int tcbl_allocate(tvfs* tvfs, vfs underlying_vfs, size_t page_size);

int vfs_open(vfs vfs, const char* file_name, vfs_fh* file_handle_out);
int vfs_close(vfs_fh file_handle);
int vfs_read(vfs_fh file_handle, char* data, size_t offset, size_t len);
int vfs_write(vfs_fh file_handle, const char* data, size_t offset, size_t len);
int vfs_file_size(vfs_fh file_handle, size_t *out);
//int vfs_sync(tcbl_fh file_handle);
int vfs_free(vfs vfs);

int vfs_txn_begin(vfs_fh vfs_fh);
int vfs_txn_commit(vfs_fh vfs_fh);
int vfs_txn_abort(vfs_fh vfs_fh);


#endif