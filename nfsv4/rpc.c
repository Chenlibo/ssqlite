#include <nfs4_internal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <errno.h>

static struct codepoint nfsops[] = {
{"ACCESS"               , 3},
{"CLOSE"                , 4},
{"COMMIT"               , 5},
{"CREATE"               , 6},
{"DELEGPURGE"           , 7},
{"DELEGRETURN"          , 8},
{"GETATTR"              , 9},
{"GETFH"                , 10},
{"LINK"                 , 11},
{"LOCK"                 , 12},
{"LOCKT"                , 13},
{"LOCKU"                , 14},
{"LOOKUP"               , 15},
{"LOOKUPP"              , 16},
{"NVERIFY"              , 17},
{"OPEN"                 , 18},
{"OPENATTR"             , 19},
{"OPEN_CONFIRM"         , 20},
{"OPEN_DOWNGRADE"       , 21},
{"PUTFH"                , 22},
{"PUTPUBFH"             , 23},
{"PUTROOTFH"            , 24},
{"READ"                 , 25},
{"READDIR"              , 26},
{"READLINK"             , 27},
{"REMOVE"               , 28},
{"RENAME"               , 29},
{"RENEW"                , 30}, 
{"RESTOREFH"            , 31},
{"SAVEFH"               , 32},
{"SECINFO"              , 33},
{"SETATTR"              , 34},
{"SETCLIENTID"          , 35}, 
{"SETCLIENTID_CONFIRM"  , 36}, 
{"VERIFY"               , 37},
{"WRITE"                , 38},
{"RELEASE_LOCKOWNER"    , 39}, 
{"BACKCHANNEL_CTL"      , 40},
{"BIND_CONN_TO_SESSION" , 41},
{"EXCHANGE_ID"          , 42},
{"CREATE_SESSION"       , 43},
{"DESTROY_SESSION"      , 44},
{"FREE_STATEID"         , 45},
{"GET_DIR_DELEGATION"   , 46},
{"GETDEVICEINFO"        , 47},
{"GETDEVICELIST"        , 48},
{"LAYOUTCOMMIT"         , 49},
{"LAYOUTGET"            , 50},
{"LAYOUTRETURN"         , 51},
{"SECINFO_NO_NAME"      , 52},
{"SEQUENCE"             , 53},
{"SET_SSV"              , 54},
{"TEST_STATEID"         , 55},
{"WANT_DELEGATION"      , 56},
{"DESTROY_CLIENTID"     , 57},
{"RECLAIM_COMPLETE"     , 58},
{"ALLOCATE"             , 59},
{"COPY"                 , 60},
{"COPY_NOTIFY"          , 61},
{"DEALLOCATE"           , 62},
{"IO_ADVISE"            , 63},
{"LAYOUTERROR"          , 64},
{"LAYOUTSTATS"          , 65},
{"OFFLOAD_CANCEL"       , 66},
{"OFFLOAD_STATUS"       , 67},
{"READ_PLUS"            , 68},
{"SEEK"                 , 69},
{"WRITE_SAME"           , 70},
{"CLONE"                , 71},
{"ILLEGAL"              , 10044},
{"", 0}};


struct codepoint nfserrs[] = {
    {"NFS4_OK",                                          0},
    {"NFS4_EPERM    Operation not permitted",           -1},
    {"NFS4_ENOENT   No such file or directory",         -2},
    {"NFS4_EIO      I/O error",                         -5},
    {"NFS4_ENXIO    No such device or address",         -6},
    {"NFS4_EBADF    Bad file number",                   -9},
    {"NFS4_EAGAIN   Try again",                        -11},
    {"NFS4_ENOMEM   Out of memory",                    -12},
    {"NFS4_EACCES   Permission denied",                -13},
    {"NFS4_EFAULT   Bad address",                      -14},
    {"NFS4_ENOTBLK  Block device required",            -15},
    {"NFS4_EBUSY    Device or resource busy",          -16},
    {"NFS4_EEXIST   File exists",                      -17},
    {"NFS4_EXDEV    Cross-device link",                -18},
    {"NFS4_ENODEV   No such device",                   -19},
    {"NFS4_ENOTDIR  Not a directory",                  -20},
    {"NFS4_EISDIR   Is a directory",                   -21},
    {"NFS4_EINVAL   Invalid argument",                 -22},
    {"NFS4_ENFILE   File table overflow",              -23},
    {"NFS4_EMFILE   Too many open files",              -24},
    {"NFS4_ETXTBSY  Text file busy",                   -26},
    {"NFS4_EFBIG    File too large",                   -27},
    {"NFS4_ENOSPC   No space left on device",          -28},
    {"NFS4_ESPIPE   Illegal seek",                     -29},
    {"NFS4_EROFS    Read-only file system",            -30},
    {"NFS4_EMLINK   Too many links",                   -31},
    {"NFS4_PROTOCOL protocol/framing error",           -32},
    {"", 0}};


static void toggle(void *a, buffer b)
{
    *(int *)a = 1;
}

// stack like allocation?
rpc allocate_rpc(nfs4 c, buffer b) 
{
    // can use a single entity or a freelist
    rpc r = allocate(s->h, sizeof(struct rpc));
    r->b = b;
    b->start = b->end = 0;
    r->xid = ++c->xid;
    
    // tcp framer - to be filled on transmit
    push_be32(b, 0);
    
    // rpc layer 
    push_be32(b, r->xid);
    push_be32(b, 0); //call
    push_be32(b, 2); //rpcvers
    push_be32(b, NFS_PROGRAM);
    push_be32(b, 4); //version
    push_be32(b, 1); //proc
    if (config_boolean("NFS_AUTH_NULL", false)) {
        push_auth_null(r->b);
    } else {
        push_auth_sys(r->b);
    }
    push_auth_null(r->b); // verf

    // v4 compound
    push_be32(b, 0); // tag
    push_be32(b, 1); // minor version
    // this deferred count shows up elsewhere - wrap
    r->opcountloc = b->end;
    b->end += 4;
    r->c = c;
    r->opcount = 0;
    
    return r;
}

// sad, but low on memory pressure, and trying to avoid pulling in
// more runtime (i.e. maps)
static void enqueue_completion(nfs4 c, u32 xid, void (*f)(void *, buffer), void *a)
{
    int len = vector_length(c->outstanding);
    int i;
    for (i = 0; i < len; i+=3) 
        if (vector_get(c->outstanding, i) == 0)
            break;
    vector_set(c->outstanding, i, (void *)(u64)xid);
    vector_set(c->outstanding, i + 1, f);
    vector_set(c->outstanding, i + 2, a);
}

static status completion_notify(nfs4 c, u32 xid)
{
    vector p = c->outstanding;
    int len = vector_length(p);
    for (int i = 0; i < len; i+=3) {
        if ((u64)vector_get(p, i) == xid) {
            void (*f)(void *) = vector_get(p, i +1);
            if (f) f(vector_get(p, i+2));
            vector_set(p, i, 0);
            break;
        }
    }

    // compaction
    while (vector_length(p) && !vector_get(p, vector_length(p)-3))
        p->end -= 3*sizeof (void *);
}

status parse_rpc(nfs4 c, buffer b, boolean *badsession)
{
    *badsession = false;
    u32 xid = read_beu32(b);
    status s = completion_notify(c, xid);
    if (s) return(s);
        
    verify_and_adv(b, 1); // rpc reply
    
    u32 rpcstatus = read_beu32(b);
    if (rpcstatus != NFS4_OK) 
        return error(NFS4_EINVAL, codestring(nfsstatus, rpcstatus));

    verify_and_adv(b, 0); // eh?
    verify_and_adv(b, 0); // verf
    verify_and_adv(b, 0); // verf
    u32 nstatus = read_beu32(b);
    if (nstatus != NFS4_OK) {
        if (config_boolean("NFS_TRACE", false))
            eprintf("nfs rpc error %s\n", codestring(nfsstatus, nstatus));

        if (nstatus == NFS4ERR_BADSESSION) {
            printf ("Bad session\n");
            *badsession = true;
        }
        return error(NFS4_EINVAL, codestring(nfsstatus, nstatus));
    }

    verify_and_adv(b, 0); // tag
    return NFS4_OK;
}

static status read_fully(int fd, void* buf, size_t nbyte)
{
    ssize_t sz_read = 0;
    char* ptr = buf;
    while (sz_read < nbyte) {
        ssize_t bread = read(fd, ptr, nbyte);
        if (bread == -1) {
            return error(NFS4_EIO,  strerror(errno));
        } else {
            sz_read += bread;
            // xxx can optimize this out in success case
            ptr += bread;
        }
    }
    return NFS4_OK;
}
 
 
status read_response(nfs4 c, buffer b)
{
    char framing[4];
    check(read_fully(c->fd, framing, 4));
    int frame = ntohl(*(u32 *)framing) & 0x07fffffff;
    buffer_extend(b, frame);
    check(read_fully(c->fd, b->contents + b->start, frame));
    b->end = frame;
    if (config_boolean("NFS_PACKET_TRACE", false)) {
        print_buffer("resp", b);
    }
    return NFS4_OK;
}


static status rpc_send(rpc r)
{
    *(u32 *)(r->b->contents + r->opcountloc) = htonl(r->opcount);
    // framer length
    *(u32 *)(r->b->contents) = htonl(0x80000000 + length(r->b)-4);
    if (config_boolean("NFS_PACKET_TRACE", false))
        print_buffer("sent", r->b);
    
    int res = write(r->c->fd, r->b->contents + r->b->start, length(r->b));
    if (res != length(r->b)) {
        return error(NFS4_EIO, "failed rpc write");
    }
    return NFS4_OK;
}

    
status nfs4_connect(nfs4 c)
{
    int temp;
    struct sockaddr_in a;

    struct hostent *he = gethostbyname(c->hostname->contents);
    memcpy(&c->address, he->h_addr, 4);
    
    c->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);    
    // xxx - abstract
    memcpy(&a.sin_addr, &c->address, 4);
    a.sin_family = AF_INET;
    a.sin_port = htons(2049); //configure

    if (config_boolean("NFS_TCP_NODELAY", true)) {
        unsigned char x = 1;
        setsockopt(c->fd, /*SOL_TCP*/0, TCP_NODELAY,
                   (char *)&x, sizeof(x));
    }
    
    int res = connect(c->fd,
                      (struct sockaddr *)&a,
                      sizeof(struct sockaddr_in));
    if (res != 0) {
        // make printf status variant
        return error(NFS4_ENXIO, "connect failure");
    }
    return NFS4_OK;
}

static status read_until(nfs4 c, buffer b, u32 which)
{
    int opcount = read_beu32(b);
    while (1) {
        int op =  read_beu32(b);
        if (config_boolean("NFS_TRACE", false)) {
            eprintf("received op: %s\n", codestring(nfsops, op));
        }        
        if (op == which) {
            return NFS4_OK;
        }
        u32 code = read_beu32(b);
        if (code != 0) return error(NFS4_EINVAL, codestring(nfsstatus, code));

        switch (op) {
        case OP_SEQUENCE:
            b->start += NFS4_SESSIONID_SIZE; // 16
            u32 seq = read_beu32(b);  // 20
            b->start += 16; // 36
            break;
        case OP_PUTROOTFH:
            break;
        case OP_PUTFH:
            break;
        case OP_LOOKUP:
            break;
        default:
            return error(NFS4_PROTOCOL, "unhandled scan code");
        }
    }
    // fix
    return NFS4_OK;
}

rpc file_rpc(nfs4_file f)
{
    rpc r = allocate_rpc(f->c, f->c->forward);
    push_sequence(r);

    push_op(r, OP_PUTFH);
    push_string(r->b, f->filehandle->contents, length(f->filehandle));
    return (r);
}


status base_transact(rpc r, int op, buffer result, boolean *badsession)
{
    int myself = 0;
    enqueue_completion(r->c, r->xid, toggle, &myself);
    check(rpc_send(r));
    result->start = result->end = 0;
    check(read_response(r->c, result));
    // drain the pipe, this should be per-slot
    while (!myself) check(parse_rpc(r->c, result, badsession));

    check(read_until(r->c, result, op));
    u32 code = read_beu32(result);
    if (code == 0) return NFS4_OK;
    return error(NFS4_EINVAL, codestring(nfsstatus, code));    
}

status exchange_id(nfs4 c)
{
    rpc r = allocate_rpc(c, c->reverse);
    push_exchange_id(r);
    buffer res = c->reverse;
    boolean bs;
    status st = base_transact(r, OP_EXCHANGE_ID, res, &bs);
    if (st) {
        deallocate_rpc(r);    
        return st;
    }
    st = parse_exchange_id(c, res);
    if (st) return st;
    deallocate_rpc(r);
    return NFS4_OK;
}


status get_root_fh(nfs4 c, buffer b)
{
    rpc r = allocate_rpc(c, c->reverse);
    push_sequence(r);
    push_op(r, OP_PUTROOTFH);
    push_op(r, OP_GETFH);
    buffer res = c->reverse;
    boolean bs2;
    status st = base_transact(r, OP_GETFH, res, &bs2);
    if (nfs4_is_error(st)) {
        deallocate_rpc(r);
        return st;
    }
    parse_filehandle(res, b);
    deallocate_rpc(r);
    if (!nfs4_is_error(st)) return st;
    return NFS4_OK;
}

status create_session(nfs4 c)
{
    rpc r = allocate_rpc(c, c->reverse);
    r->c->sequence = 1;  // 18.36.4 says that a new session starts at 1 implicitly
    r->c->lock_sequence = 1;
    push_create_session(r);
    buffer res = c->reverse;
    status st = transact(r, OP_CREATE_SESSION, res);
    if (st) {
        deallocate_rpc(r);    
        return st;
    }    
    st = parse_create_session(c, res);
    if (st) return st;
    deallocate_rpc(r);
    return NFS4_OK;
}

static status replay_rpc(rpc r)
{
    // ok sad, framer + xid + call + rpc + program + version + proc + auth + authbody + verf + verf2
    // tag + minor + opcount + sequence op
    // verify that we're starting with a sequence, which should always be the case
    // except for exchangeid and create session
    u32 offset = 4 * 15;
    memcpy(r->b->contents + offset, r->c->session, NFS4_SESSIONID_SIZE);
    u32 nseq = htonl(r->c->sequence);
    r->c->sequence++;
    memcpy(r->b->contents + offset + NFS4_SESSIONID_SIZE, &nseq, 4);
    u32 nxid = htonl(++r->c->xid);
    memcpy(r->b->contents + 4, &nxid, 4);    
}

static status destroy_session(nfs4 c)
{
    rpc r = allocate_rpc(c, c->reverse);
    push_op(r, OP_DESTROY_SESSION);
    push_session_id(r, c->session);
    boolean bs2;
    return base_transact(r, OP_DESTROY_SESSION, c->reverse, &bs2);
}

status transact(rpc r, int op, buffer result)
{
    int tries = 0;
    boolean badsession = true;
    status s;
    
    while ((tries < 2 ) && (badsession == true)) {
        // xxx - if there are outstanding operations on the
        // old connection .. a late synch() will never
        // complete
        s = base_transact(r, op, result, &badsession);
        if (badsession) {
            status s2 = rpc_connection(r->c);
            if (s2) return s2;
            replay_rpc(r);
            tries++;
        }
    }
    return s;
}

status file_size(nfs4_file f, u64 *dest)
{
    rpc r = file_rpc(f);
    push_op(r, OP_GETATTR);
    push_be32(r->b, 1); 
    u32 mask = 1<<FATTR4_SIZE;
    push_be32(r->b, mask);
    buffer res =f->c->reverse;
    status s = transact(r, OP_GETATTR, res);
    if (s) return s;
    // demux attr more better
    res->start = res->end - 8;
    u64 x = 0;
    *dest = read_beu64(res);  
    return NFS4_OK;
}

// we can actually use the framing length to delineate 
// header and data, and read directly into the dest buffer
// because the data is always at the end
status read_chunk(nfs4_file f, void *dest, u64 offset, u32 length)
{
    rpc r = file_rpc(f);
    push_op(r, OP_READ);
    push_stateid(r, &f->latest_sid);
    push_be64(r->b, offset);
    push_be32(r->b, length);
    buffer res = f->c->reverse;
    status s = transact(r, OP_READ, res);
    if (s) return s;
    // we dont care if its the end of file -- we might for a single round trip read entire
    res->start += 4; 
    u32 len = read_beu32(res);
    // guard against len != length
    memcpy(dest, res->contents+res->start, len);
    return NFS4_OK;
}

// if we break transact, can writev with the header and 
// source buffer as two fragments
// add synch
status write_chunk(nfs4_file f, void *source, u64 offset, u32 length)
{
    rpc r = file_rpc(f);
    push_op(r, OP_WRITE);
    push_stateid(r, &f->latest_sid);
    push_be64(r->b, offset);
    push_be32(r->b, FILE_SYNC4);
    push_string(r->b, source, length);
    buffer b = f->c->reverse;
    return transact(r, OP_WRITE, b);
}


status segment(status (*each)(nfs4_file, void *, u64, u32),
            int chunksize,
            nfs4_file f,
            void *x,
            u64 offset,
            u32 length)
{
    for (u32 done = 0; done < length;) {
        u32 xfer = MIN(length - done, chunksize);
        status s = each(f, x + done, offset+done, xfer);
        if (s) return s;
        done += xfer;
    }
    return NFS4_OK;
}

status reclaim_complete(nfs4 c)
{
    rpc r = allocate_rpc(c, c->reverse);
    push_sequence(r);
    push_op(r, OP_RECLAIM_COMPLETE);
    push_be32(r->b, 0);
    boolean bs;
    status st = base_transact(r, OP_RECLAIM_COMPLETE, c->reverse, &bs);
    deallocate_rpc(r);        
    return st;
}


status rpc_connection(nfs4 c)
{
    check(nfs4_connect(c));
    check(exchange_id(c));
    check(create_session(c));
    if (!config_boolean("NFS_USE_PUTROOTFH", false)) {
        c->root_filehandle = allocate_buffer(0, NFS4_FHSIZE);
        get_root_fh(c, c->root_filehandle);
    }
    return reclaim_complete(c);
}

status rpc_readdir(nfs4_dir d, buffer result)
{
    rpc r = allocate_rpc(d->c, d->c->forward);
    push_sequence(r);
    push_op(r, OP_PUTFH);
    push_string(r->b, d->filehandle->contents, length(d->filehandle));
    push_op(r, OP_READDIR);
    push_be64(r->b, d->cookie); 
    push_bytes(r->b, d->verifier, sizeof(d->verifier));
    push_be32(r->b, 512); // entry length is..meh, this is the per entry length ? 512? wth
    push_be32(r->b, result->capacity);
    push_fattr_mask(r, STANDARD_PROPERTIES);
    check(transact(r, OP_READDIR, result));
    read_buffer(result, d->verifier, NFS4_VERIFIER_SIZE);
    return NFS4_OK;
}


