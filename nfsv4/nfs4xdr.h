
#define NFS_PROGRAM 0x186a3
#define NFS4_FHSIZE 128
#define NFS4_SESSIONID_SIZE 16
#define NFS4_VERIFIER_SIZE 8
// good job with names IETF, this is the stateid opaque uniquifier
#define NFS4_OTHER_SIZE 12

enum nfs_opnum4 {
 OP_ACCESS               = 3,
 OP_CLOSE                = 4,
 OP_COMMIT               = 5,
 OP_CREATE               = 6,
 OP_DELEGPURGE           = 7,
 OP_DELEGRETURN          = 8,
 OP_GETATTR              = 9,
 OP_GETFH                = 10,
 OP_LINK                 = 11,
 OP_LOCK                 = 12,
 OP_LOCKT                = 13,
 OP_LOCKU                = 14,
 OP_LOOKUP               = 15,
 OP_LOOKUPP              = 16,
 OP_NVERIFY              = 17,
 OP_OPEN                 = 18,
 OP_OPENATTR             = 19,
 OP_OPEN_CONFIRM         = 20, /* Mandatory not-to-implement */
 OP_OPEN_DOWNGRADE       = 21,
 OP_PUTFH                = 22,
 OP_PUTPUBFH             = 23,
 OP_PUTROOTFH            = 24,
 OP_READ                 = 25,
 OP_READDIR              = 26,
 OP_READLINK             = 27,
 OP_REMOVE               = 28,
 OP_RENAME               = 29,
 OP_RENEW                = 30, /* Mandatory not-to-implement */
 OP_RESTOREFH            = 31,
 OP_SAVEFH               = 32,
 OP_SECINFO              = 33,
 OP_SETATTR              = 34,
 OP_SETCLIENTID          = 35, /* Mandatory not-to-implement */
 OP_SETCLIENTID_CONFIRM  = 36, /* Mandatory not-to-implement */
 OP_VERIFY               = 37,
 OP_WRITE                = 38,
 OP_RELEASE_LOCKOWNER    = 39, /* Mandatory not-to-implement */

/* New operations for NFSv4.1 */

 OP_BACKCHANNEL_CTL      = 40,
 OP_BIND_CONN_TO_SESSION = 41,
 OP_EXCHANGE_ID          = 42,
 OP_CREATE_SESSION       = 43,
 OP_DESTROY_SESSION      = 44,
 OP_FREE_STATEID         = 45,
 OP_GET_DIR_DELEGATION   = 46,
 OP_GETDEVICEINFO        = 47,
 OP_GETDEVICELIST        = 48,
 OP_LAYOUTCOMMIT         = 49,
 OP_LAYOUTGET            = 50,
 OP_LAYOUTRETURN         = 51,
 OP_SECINFO_NO_NAME      = 52,
 OP_SEQUENCE             = 53,
 OP_SET_SSV              = 54,
 OP_TEST_STATEID         = 55,
 OP_WANT_DELEGATION      = 56,
 OP_DESTROY_CLIENTID     = 57,
 OP_RECLAIM_COMPLETE     = 58,

/* New operations for NFSv4.2 */
 
 OP_ALLOCATE             = 59,
 OP_COPY                 = 60,
 OP_COPY_NOTIFY          = 61,
 OP_DEALLOCATE           = 62,
 OP_IO_ADVISE            = 63,
 OP_LAYOUTERROR          = 64,
 OP_LAYOUTSTATS          = 65,
 OP_OFFLOAD_CANCEL       = 66,
 OP_OFFLOAD_STATUS       = 67,
 OP_READ_PLUS            = 68,
 OP_SEEK                 = 69,
 OP_WRITE_SAME           = 70,
 OP_CLONE                = 71,
 OP_ILLEGAL              = 10044
};
    


/*
 * REQUIRED attributes
 */
enum nfs4_attrs {
FATTR4_SUPPORTED_ATTRS    = 0,
FATTR4_TYPE               = 1,
FATTR4_FH_EXPIRE_TYPE     = 2,
FATTR4_CHANGE             = 3,
FATTR4_SIZE               = 4,
FATTR4_LINK_SUPPORT       = 5,
FATTR4_SYMLINK_SUPPORT    = 6,
FATTR4_NAMED_ATTR         = 7,
FATTR4_FSID               = 8,
FATTR4_UNIQUE_HANDLES     = 9,
FATTR4_LEASE_TIME         = 10,
FATTR4_RDATTR_ERROR       = 11,
FATTR4_FILEHANDLE         = 19,

/*
 * New to NFSv4.1
 */
 FATTR4_SUPPATTR_EXCLCREAT = 75,

/*
 * RECOMMENDED attributes
 */
FATTR4_ACL                = 12,
FATTR4_ACLSUPPORT         = 13,
FATTR4_ARCHIVE            = 14,
FATTR4_CANSETTIME         = 15,
FATTR4_CASE_INSENSITIVE   = 16,
FATTR4_CASE_PRESERVING    = 17,
FATTR4_CHOWN_RESTRICTED   = 18,
FATTR4_FILEID             = 20,
FATTR4_FILES_AVAIL        = 21,
FATTR4_FILES_FREE         = 22,
FATTR4_FILES_TOTAL        = 23,
FATTR4_FS_LOCATIONS       = 24,
FATTR4_HIDDEN             = 25,
FATTR4_HOMOGENEOUS        = 26,
FATTR4_MAXFILESIZE        = 27,
FATTR4_MAXLINK            = 28,
FATTR4_MAXNAME            = 29,
FATTR4_MAXREAD            = 30,
FATTR4_MAXWRITE           = 31,
FATTR4_MIMETYPE           = 32,
FATTR4_MODE               = 33,
FATTR4_NO_TRUNC           = 34,
FATTR4_NUMLINKS           = 35,
FATTR4_OWNER              = 36,
FATTR4_OWNER_GROUP        = 37,
FATTR4_QUOTA_AVAIL_HARD   = 38,
FATTR4_QUOTA_AVAIL_SOFT   = 39,
FATTR4_QUOTA_USED         = 40,
FATTR4_RAWDEV             = 41,
FATTR4_SPACE_AVAIL        = 42,
FATTR4_SPACE_FREE         = 43,
FATTR4_SPACE_TOTAL        = 44,
FATTR4_SPACE_USED         = 45,
FATTR4_SYSTEM             = 46,
FATTR4_TIME_ACCESS        = 47,
FATTR4_TIME_ACCESS_SET    = 48,
FATTR4_TIME_BACKUP        = 49,
FATTR4_TIME_CREATE        = 50,
FATTR4_TIME_DELTA         = 51,
FATTR4_TIME_METADATA      = 52,
FATTR4_TIME_MODIFY        = 53,
FATTR4_TIME_MODIFY_SET    = 54,
FATTR4_MOUNTED_ON_FILEID  = 55,

/*
 * New to NFSv4.1
 */
 FATTR4_DIR_NOTIF_DELAY    = 56,
 FATTR4_DIRENT_NOTIF_DELAY = 57,
 FATTR4_DACL               = 58,
 FATTR4_SACL               = 59,
 FATTR4_CHANGE_POLICY      = 60,
 FATTR4_FS_STATUS          = 61,
 FATTR4_FS_LAYOUT_TYPES    = 62,
 FATTR4_LAYOUT_HINT        = 63,
 FATTR4_LAYOUT_TYPES       = 64,
 FATTR4_LAYOUT_BLKSIZE     = 65,
 FATTR4_LAYOUT_ALIGNMENT   = 66,
 FATTR4_FS_LOCATIONS_INFO  = 67,
 FATTR4_MDSTHRESHOLD       = 68,
 FATTR4_RETENTION_GET      = 69,
 FATTR4_RETENTION_SET      = 70,
 FATTR4_RETENTEVT_GET      = 71,
 FATTR4_RETENTEVT_SET      = 72,
 FATTR4_RETENTION_HOLD     = 73,
 FATTR4_MODE_SET_MASKED    = 74,
 FATTR4_FS_CHARSET_CAP     = 76,

/*
 * New to NFSv4.2
 */
 FATTR4_CLONE_BLKSIZE      = 77,
 FATTR4_SPACE_FREED        = 78,
 FATTR4_CHANGE_ATTR_TYPE   = 79,
 FATTR4_SEC_LABEL          = 80,
};


enum exchange_id_flags {
    EXCHGID4_FLAG_SUPP_MOVED_REFER    = 0x00000001,
    EXCHGID4_FLAG_SUPP_MOVED_MIGR     = 0x00000002,
    EXCHGID4_FLAG_SUPP_FENCE_OPS      = 0x00000004,
    
    EXCHGID4_FLAG_BIND_PRINC_STATEID  = 0x00000100,
    
    EXCHGID4_FLAG_USE_NON_PNFS        = 0x00010000,
    EXCHGID4_FLAG_USE_PNFS_MDS        = 0x00020000,
    EXCHGID4_FLAG_USE_PNFS_DS         = 0x00040000,
    
    EXCHGID4_FLAG_MASK_PNFS           = 0x00070000,
    
    EXCHGID4_FLAG_UPD_CONFIRMED_REC_A = 0x40000000,
    EXCHGID4_FLAG_CONFIRMED_R         = 0x80000000,
};
    

// NFS4_OK defined in nfs4.h
enum nfsstat4 {
 NFS4ERR_PERM           = 1,     /* caller not privileged     */
 NFS4ERR_NOENT          = 2,     /* no such file/directory    */
 NFS4ERR_IO             = 5,     /* hard I/O error            */
 NFS4ERR_NXIO           = 6,     /* no such device            */
 NFS4ERR_ACCESS         = 13,    /* access denied             */
 NFS4ERR_EXIST          = 17,    /* file already exists       */
 NFS4ERR_XDEV           = 18,    /* different file systems    */

/*
 * Please do not allocate value 19; it was used in NFSv3,
 * and we do not want a value in NFSv3 to have a different
 * meaning in NFSv4.x.
 */

 NFS4ERR_NOTDIR         = 20,    /* should be a directory     */
 NFS4ERR_ISDIR          = 21,    /* should not be a directory */
 NFS4ERR_INVAL          = 22,    /* invalid argument          */
 NFS4ERR_FBIG           = 27,    /* file exceeds server max   */
 NFS4ERR_NOSPC          = 28,    /* no space on file system   */
 NFS4ERR_ROFS           = 30,    /* read-only file system     */
 NFS4ERR_MLINK          = 31,    /* too many hard links       */
 NFS4ERR_NAMETOOLONG    = 63,    /* name exceeds server max   */
 NFS4ERR_NOTEMPTY       = 66,    /* directory not empty       */
 NFS4ERR_DQUOT          = 69,    /* hard quota limit reached  */
 NFS4ERR_STALE          = 70,    /* file no longer exists     */
 NFS4ERR_BADHANDLE      = 10001, /* illegal filehandle        */
 NFS4ERR_BAD_COOKIE     = 10003, /* READDIR cookie is stale   */
 NFS4ERR_NOTSUPP        = 10004, /* operation not supported   */
 NFS4ERR_TOOSMALL       = 10005, /* response limit exceeded   */
 NFS4ERR_SERVERFAULT    = 10006, /* undefined server error    */
 NFS4ERR_BADTYPE        = 10007, /* type invalid for CREATE   */
 NFS4ERR_DELAY          = 10008, /* file "busy" -- retry      */
 NFS4ERR_SAME           = 10009, /* nverify says attrs same   */
 NFS4ERR_DENIED         = 10010, /* lock unavailable          */
 NFS4ERR_EXPIRED        = 10011, /* lock lease expired        */
 NFS4ERR_LOCKED         = 10012, /* I/O failed due to lock    */
 NFS4ERR_GRACE          = 10013, /* in grace period           */
 NFS4ERR_FHEXPIRED      = 10014, /* filehandle expired        */
 NFS4ERR_SHARE_DENIED   = 10015, /* share reserve denied      */
 NFS4ERR_WRONGSEC       = 10016, /* wrong security flavor     */
 NFS4ERR_CLID_INUSE     = 10017, /* client ID in use          */

 /* NFS4ERR_RESOURCE is not a valid error in NFSv4.1. */
 NFS4ERR_RESOURCE       = 10018, /* resource exhaustion       */

 NFS4ERR_MOVED          = 10019, /* file system relocated     */
 NFS4ERR_NOFILEHANDLE   = 10020, /* current FH is not set     */
 NFS4ERR_MINOR_VERS_MISMATCH= 10021, /* minor vers not supp   */
 NFS4ERR_STALE_CLIENTID = 10022, /* server has rebooted       */
 NFS4ERR_STALE_STATEID  = 10023, /* server has rebooted       */
 NFS4ERR_OLD_STATEID    = 10024, /* state is out of sync      */
 NFS4ERR_BAD_STATEID    = 10025, /* incorrect stateid         */
 NFS4ERR_BAD_SEQID      = 10026, /* request is out of seq.    */
 NFS4ERR_NOT_SAME       = 10027, /* verify -- attrs not same  */
 NFS4ERR_LOCK_RANGE     = 10028, /* overlapping lock range    */
 NFS4ERR_SYMLINK        = 10029, /* should be file/directory  */
 NFS4ERR_RESTOREFH      = 10030, /* no saved filehandle       */
 NFS4ERR_LEASE_MOVED    = 10031, /* some file system moved    */
 NFS4ERR_ATTRNOTSUPP    = 10032, /* recommended attr not supp */
 NFS4ERR_NO_GRACE       = 10033, /* reclaim outside of grace  */
 NFS4ERR_RECLAIM_BAD    = 10034, /* reclaim error at server   */
 NFS4ERR_RECLAIM_CONFLICT= 10035, /* conflict on reclaim      */
 NFS4ERR_BADXDR         = 10036, /* XDR decode failed         */
 NFS4ERR_LOCKS_HELD     = 10037, /* file locks held at CLOSE  */
 NFS4ERR_OPENMODE       = 10038, /* conflict in OPEN and I/O  */
 NFS4ERR_BADOWNER       = 10039, /* owner translation bad     */
 NFS4ERR_BADCHAR        = 10040, /* UTF-8 char not supported  */
 NFS4ERR_BADNAME        = 10041, /* name not supported        */
 NFS4ERR_BAD_RANGE      = 10042, /* lock range not supported  */
 NFS4ERR_LOCK_NOTSUPP   = 10043, /* no atomic up/downgrade    */
 NFS4ERR_OP_ILLEGAL     = 10044, /* undefined operation       */
 NFS4ERR_DEADLOCK       = 10045, /* file-locking deadlock     */
 NFS4ERR_FILE_OPEN      = 10046, /* open file blocks op       */
 NFS4ERR_ADMIN_REVOKED  = 10047, /* lock-owner state revoked  */
 NFS4ERR_CB_PATH_DOWN   = 10048, /* callback path down        */

 /* NFSv4.1 errors start here. */

 NFS4ERR_BADIOMODE      = 10049,
 NFS4ERR_BADLAYOUT      = 10050,
 NFS4ERR_BAD_SESSION_DIGEST = 10051,
 NFS4ERR_BADSESSION     = 10052,
 NFS4ERR_BADSLOT        = 10053,
 NFS4ERR_COMPLETE_ALREADY = 10054,
 NFS4ERR_CONN_NOT_BOUND_TO_SESSION = 10055,
 NFS4ERR_DELEG_ALREADY_WANTED = 10056,
 NFS4ERR_BACK_CHAN_BUSY = 10057, /* backchan reqs outstanding */
 NFS4ERR_LAYOUTTRYLATER = 10058,
 NFS4ERR_LAYOUTUNAVAILABLE = 10059,
 NFS4ERR_NOMATCHING_LAYOUT = 10060,
 NFS4ERR_RECALLCONFLICT = 10061,
 NFS4ERR_UNKNOWN_LAYOUTTYPE = 10062,
 NFS4ERR_SEQ_MISORDERED = 10063, /* unexpected seq. ID in req */
 NFS4ERR_SEQUENCE_POS   = 10064, /* [CB_]SEQ. op not 1st op   */
 NFS4ERR_REQ_TOO_BIG    = 10065, /* request too big           */
 NFS4ERR_REP_TOO_BIG    = 10066, /* reply too big             */
 NFS4ERR_REP_TOO_BIG_TO_CACHE =10067, /* rep. not all cached  */
 NFS4ERR_RETRY_UNCACHED_REP =10068, /* retry + rep. uncached  */
 NFS4ERR_UNSAFE_COMPOUND =10069, /* retry/recovery too hard   */
 NFS4ERR_TOO_MANY_OPS   = 10070, /* too many ops in [CB_]COMP */
 NFS4ERR_OP_NOT_IN_SESSION =10071, /* op needs [CB_]SEQ. op   */
 NFS4ERR_HASH_ALG_UNSUPP = 10072,  /* hash alg. not supp      */
                                   /* Error 10073 is unused.  */
 NFS4ERR_CLIENTID_BUSY  = 10074, /* client ID has state       */
 NFS4ERR_PNFS_IO_HOLE   = 10075, /* IO to _SPARSE file hole   */
 NFS4ERR_SEQ_FALSE_RETRY= 10076, /* retry != original req     */
 NFS4ERR_BAD_HIGH_SLOT  = 10077, /* req has bad highest_slot  */
 NFS4ERR_DEADSESSION    = 10078, /* new req sent to dead sess */
 NFS4ERR_ENCR_ALG_UNSUPP= 10079, /* encr alg. not supp        */
 NFS4ERR_PNFS_NO_LAYOUT = 10080, /* I/O without a layout      */
 NFS4ERR_NOT_ONLY_OP    = 10081, /* addl ops not allowed      */
 NFS4ERR_WRONG_CRED     = 10082, /* op done by wrong cred     */
 NFS4ERR_WRONG_TYPE     = 10083, /* op on wrong type object   */
 NFS4ERR_DIRDELEG_UNAVAIL=10084, /* delegation not avail.     */
 NFS4ERR_REJECT_DELEG   = 10085, /* cb rejected delegation    */
 NFS4ERR_RETURNCONFLICT = 10086, /* layout get before return  */
 NFS4ERR_DELEG_REVOKED  = 10087, /* deleg./layout revoked     */

 /* NFSv4.2 errors start here. */

 NFS4ERR_PARTNER_NOTSUPP= 10088, /* s2s not supported         */
 NFS4ERR_PARTNER_NO_AUTH= 10089, /* s2s not authorized        */
 NFS4ERR_UNION_NOTSUPP  = 10090, /* arm of union not supp     */
 NFS4ERR_OFFLOAD_DENIED = 10091, /* dest not allowing copy    */
 NFS4ERR_WRONG_LFS      = 10092, /* LFS not supported         */
 NFS4ERR_BADLABEL       = 10093, /* incorrect label           */
 NFS4ERR_OFFLOAD_NO_REQS= 10094  /* dest not meeting reqs     */
};



static struct codepoint nfsstatus[] = {
    {"everything is okay", 0},
    {"caller not privileged", 1},
    {"no such file/directory", 2},
    {"hard I/O error", 5},
    {"no such device", 6},
    {"access denied", 13},
    {"file already exists", 17},
    {"different file systems", 18},
    {"should be a directory", 20},
    {"should not be a directory", 21},
    {"invalid argument ", 22},
    {"file exceeds server max", 27},
    {"no space on file system", 28},
    {"read-only file system", 30},
    {"too many hard links", 31},
    {"name exceeds server max", 63},
    {"directory not empty", 66},
    {"hard quota limit reached", 69},
    {"file no longer exists", 70},
    {"illegal filehandle", 10001},
    {"READDIR cookie is stale", 10003},
    {"operation not supported", 10004},
    {"response limit exceeded", 10005},
    {"undefined server error", 10006},
    {"type invalid for CREATE", 10007},
    {"file busy -- retry", 10008},
    {"nverify says attrs same", 10009},
    {"lock unavailable ", 10010},
    {"lock lease expired", 10011},
    {"I/O failed due to lock", 10012},
    {"in grace period  ", 10013},
    {"filehandle expired", 10014},
    {"share reserve denied", 10015},
    {"wrong security flavor", 10016},
    {"client ID in use ", 10017},
    {"resource exhaustion", 10018},
    {"file system relocated", 10019},
    {"current FH is not set", 10020},
    {"minor vers not supp", 10021},
    {"server has rebooted", 10022},
    {"server has rebooted", 10023},
    {"state is out of sync", 10024},
    {"incorrect stateid", 10025},
    {"request is out of seq.", 10026},
    {"verify -- attrs not same", 10027},
    {"overlapping lock range", 10028},
    {"should be file/directory", 10029},
    {"no saved filehandle", 10030},
    {"some file system moved", 10031},
    {"recommended attr not supp", 10032},
    {"reclaim outside of grace", 10033},
    {"reclaim error at server", 10034},
    {"conflict on reclaim", 10035},
    {"XDR decode failed", 10036},
    {"file locks held at CLOSE", 10037},
    {"conflict in OPEN and I/O", 10038},
    {"owner translation bad", 10039},
    {"UTF-8 char not supported", 10040},
    {"name not supported", 10041},
    {"lock range not supported", 10042},
    {"no atomic up/downgrade", 10043},
    {"undefined operation", 10044},
    {"file-locking deadlock", 10045},
    {"open file blocks op", 10046},
    {"lock-owner state revoked", 10047},
    {"callback path down", 10048},
    {"bad io mode", 10049},
    {"bad layout", 10050},
    {"bad session digest", 10051},
    {"bad session", 10052},
    {"bad slot", 10053},
    {"complete already", 10054},
    {"conn not bound to session", 10055},
    {"deleg aready wanted", 10056},
    {"backchan reqs outstanding", 10057},
    {"layout try later", 10058},
    {"layout unavailable", 10059},
    {"no matching layout", 10060},
    {"recall conflict", 10061},
    {"laytout type", 10062},
    {"unexpected seq. ID in req", 10063},
    {"[CB_]SEQ. op not 1st op", 10064},
    {"request too big  ", 10065},
    {"reply too big    ", 10066},
    {"rep. not all cached", 10067},
    {"retry uncached rep", 10068},
    {"retry/recovery too hard", 10069},
    {"too many ops in [CB_]COMP", 10070},
    {"op needs [CB_]SEQ. op", 10071},
    {"hash alg. not supp", 10072},
    {"client ID has state", 10074},
    {"IO to _SPARSE file hole", 10075},
    {"retry != original req", 10076},
    {"req has bad highest_slot", 10077},
    {"new req sent to dead sess", 10078},
    {"encr alg. not supp", 10079},
    {"I/O without a layout", 10080},
    {"addl ops not allowed", 10081},
    {"op done by wrong cred", 10082},
    {"op on wrong type object", 10083},
    {"delegation not avail.", 10084},
    {"cb rejected delegation", 10085},
    {"layout get before return", 10086},
    {"deleg./layout revoked", 10087},
    {"s2s not supported", 10088},
    {"s2s not authorized", 10089},
    {"arm of union not supp", 10090},
    {"dest not allowing copy", 10091},
    {"LFS not supported", 10092},
    {"incorrect label  ", 10093},
    {"dest not meeting reqs", 10094},
    {"", 0}};

enum stable_how4 {
        UNSTABLE4       = 0,
        DATA_SYNC4      = 1,
        FILE_SYNC4      = 2
};

enum opentype4 {
    OPEN4_NOCREATE  = 0,
    OPEN4_CREATE    = 1
};

enum limit_by4 {
    NFS_LIMIT_SIZE          = 1,
    NFS_LIMIT_BLOCKS        = 2
    /* others as needed */
};

   /*
    * Share Access and Deny constants for open argument
    */
#define OPEN4_SHARE_ACCESS_READ  0x00000001
#define OPEN4_SHARE_ACCESS_WRITE  0x00000002
#define OPEN4_SHARE_ACCESS_BOTH   0x00000003

#define OPEN4_SHARE_DENY_NONE   0x00000000
#define OPEN4_SHARE_DENY_READ   0x00000001
#define OPEN4_SHARE_DENY_WRITE  0x00000002
#define OPEN4_SHARE_DENY_BOTH   0x00000003


   /* new flags for share_access field of OPEN4args */
#define OPEN4_SHARE_ACCESS_WANT_DELEG_MASK     0xFF00
#define OPEN4_SHARE_ACCESS_WANT_NO_PREFERENCE  0x0000
#define OPEN4_SHARE_ACCESS_WANT_READ_DELEG     0x0100
#define OPEN4_SHARE_ACCESS_WANT_WRITE_DELEG    0x0200
#define OPEN4_SHARE_ACCESS_WANT_ANY_DELEG      0x0300
#define OPEN4_SHARE_ACCESS_WANT_NO_DELEG       0x0400
#define OPEN4_SHARE_ACCESS_WANT_CANCEL         0x0500

#define    OPEN4_SHARE_ACCESS_WANT_SIGNAL_DELEG_WHEN_RESRC_AVAIL  0x10000

#define    OPEN4_SHARE_ACCESS_WANT_PUSH_DELEG_WHEN_UNCONTENDED   0x20000


enum createmode4 {
    UNCHECKED4      = 0,
    GUARDED4        = 1,
    /* Deprecated in NFSv4.1. */
    EXCLUSIVE4      = 2,
    /*
     * New to NFSv4.1. If session is persistent,
     * GUARDED4 MUST be used.  Otherwise, use
     * EXCLUSIVE4_1 instead of EXCLUSIVE4.
     */
    EXCLUSIVE4_1    = 3
};

enum open_delegation_type4 {
    OPEN_DELEGATE_NONE      = 0,
    OPEN_DELEGATE_READ      = 1,
    OPEN_DELEGATE_WRITE     = 2,
    OPEN_DELEGATE_NONE_EXT  = 3 /* new to v4.1 */
};

enum open_claim_type4 {
    /*
     * Not a reclaim.
     */
    CLAIM_NULL              = 0,
    
    CLAIM_PREVIOUS          = 1,
    CLAIM_DELEGATE_CUR      = 2,
    CLAIM_DELEGATE_PREV     = 3,
    
    /*
     * Not a reclaim.
     *
     * Like CLAIM_NULL, but object identified
     * by the current filehandle.
     */
    CLAIM_FH                = 4, /* new to v4.1 */
    
    /*
     * Like CLAIM_DELEGATE_CUR, but object identified
     * by current filehandle.
     */
    CLAIM_DELEG_CUR_FH      = 5, /* new to v4.1 */
    
    /*
     * Like CLAIM_DELEGATE_PREV, but object identified
     * by current filehandle.
     */
    CLAIM_DELEG_PREV_FH     = 6 /* new to v4.1 */
};

enum state_protect_how4 {
    SP4_NONE = 0,
    SP4_MACH_CRED = 1,
    SP4_SSV = 2
};

enum why_no_delegation4 { /* New to NFSv4.1 */
        WND4_NOT_WANTED                 = 0,
        WND4_CONTENTION                 = 1,
        WND4_RESOURCE                   = 2,
        WND4_NOT_SUPP_FTYPE             = 3,
        WND4_WRITE_DELEG_NOT_SUPP_FTYPE = 4,
        WND4_NOT_SUPP_UPGRADE           = 5,
        WND4_NOT_SUPP_DOWNGRADE         = 6,
        WND4_CANCELLED                  = 7,
        WND4_IS_DIR                     = 8
};


#define NFS_LIMIT_SIZE 1
#define NFS_LIMIT_BLOCKS 2

#if NOTYET
*            opaque
bitmap4      [u64]
bool         u32
chg_policy4  {u64, u64}
enum         u32
fs4_status   struct
fsid4        {u64, u64}
fs_locations {string, pathname}
layouthint4  {u32, opaque}
layouttype4<> [u32]
mdsthreshold4 // complicated
mode4          u32
mode_masked4
nfsace4<>      [ace]
nfsacl41       {u32, [ace]}
nfs_fh4  128 bits
nfs_ftype4  u32
nfs_lease4  u32
nfstime4   {64s + 32ns}
retention_get4 {64, time}
retention_set4 {bool, u64}
settime4 // {bool, optional time}
specdata4 {u32, u32}



struct{int, void (*)()} attribute_parsers[] = {
    {FATTR_SUPPORTED_ATTRS    , bitmap4},
    {FATTR_TYPE               , nfs_ftype4 },
    {FATTR_FH_EXPIRE_TYPE     , uint32_t   },
    {FATTR_CHANGE             , uint64_t   },
    {FATTR_SIZE               , uint64_t   },
    {FATTR_LINK_SUPPORT       , bool       },
    {FATTR_SYMLINK_SUPPORT    , bool       },
    {FATTR_NAMED_ATTR         , bool       },
    {FATTR_FSID               , fsid4      },
    {FATTR_UNIQUE_HANDLES     , bool       },
    {FATTR_LEASE_TIME         , nfs_lease4 },
    {FATTR_RDATTR_ERROR       , enum       },
    {FATTR_FILEHANDLE         , nfs_fh4    },
    {FATTR_SUPPATTR_EXCLCREAT , bitmap4    },
    {FATTR_ACL                , nfsace4<>      },
    {FATTR_ACLSUPPORT         , uint32_t       },
    {FATTR_ARCHIVE            , bool           },
    {FATTR_CANSETTIME         , bool           },
    {FATTR_CASE_INSENSITIVE   , bool           },
    {FATTR_CASE_PRESERVING    , bool           },
    {FATTR_CHANGE_POLICY      , chg_policy4    },
    {FATTR_CHOWN_RESTRICTED   , bool           },
    {FATTR_DACL               , nfsacl41       },
    {FATTR_DIR_NOTIF_DELAY    , nfstime4       },
    {FATTR_DIRENT_NOTIF_DELAY , nfstime4       },
    {FATTR_FILEID             , uint64_t       },
    {FATTR_FILES_AVAIL        , uint64_t       },
    {FATTR_FILES_FREE         , uint64_t       },
    {FATTR_FILES_TOTAL        , uint64_t       },
    {FATTR_FS_CHARSET_CAP     , uint32_t       },
    {FATTR_FS_LAYOUT_TYPE     , layouttype4<>  },
    {FATTR_FS_LOCATIONS       , fs_locations   },
    {FATTR_FS_LOCATIONS_INFO  , *              },
    {FATTR_FS_STATUS          , fs4_status     },
    {FATTR_HIDDEN             , bool           },
    {FATTR_HOMOGENEOUS        , bool           },
    {FATTR_LAYOUT_ALIGNMENT   , uint32_t       },
    {FATTR_LAYOUT_BLKSIZE     , uint32_t       },
    {FATTR_LAYOUT_HINT        , layouthint4    },
    {FATTR_LAYOUT_TYPE        , layouttype4<>  },
    {FATTR_MAXFILESIZE        , uint64_t       },
    {FATTR_MAXLINK            , uint32_t       },
    {FATTR_MAXNAME            , uint32_t       },
    {FATTR_MAXREAD            , uint64_t       },
    {FATTR_MAXWRITE           , uint64_t       },
    {FATTR_MDSTHRESHOLD       , mdsthreshold4  },
    {FATTR_MIMETYPE           , utf8str_cs     },
    {FATTR_MODE               , mode4          },
    {FATTR_MODE_SET_MASKED    , mode_masked4   },
    {FATTR_MOUNTED_ON_FILEID  , uint64_t       },
    {FATTR_NO_TRUNC           , bool           },
    {FATTR_NUMLINKS           , uint32_t       },
    {FATTR_OWNER              , utf8str_mixed  },
    {FATTR_OWNER_GROUP        , utf8str_mixed  },
    {FATTR_QUOTA_AVAIL_HARD   , uint64_t       },
    {FATTR_QUOTA_AVAIL_SOFT   , uint64_t       },
    {FATTR_QUOTA_USED         , uint64_t       },
    {FATTR_RAWDEV             , specdata4      },
    {FATTR_RETENTEVT_GET      , retention_get4 },
    {FATTR_RETENTEVT_SET      , retention_set4 },
    {FATTR_RETENTION_GET      , retention_get4 },
    {FATTR_RETENTION_HOLD     , uint64_t       },
    {FATTR_RETENTION_SET      , retention_set4 },
    {FATTR_SACL               , nfsacl41       },
    {FATTR_SPACE_AVAIL        , uint64_t       },
    {FATTR_SPACE_FREE         , uint64_t       },
    {FATTR_SPACE_TOTAL        , uint64_t       },
    {FATTR_SPACE_USED         , uint64_t       },
    {FATTR_SYSTEM             , bool           },
    {FATTR_TIME_ACCESS        , nfstime4       },
    {FATTR_TIME_ACCESS_SET    , settime4       },
    {FATTR_TIME_BACKUP        , nfstime4       },
    {FATTR_TIME_CREATE        , nfstime4       },
    {FATTR_TIME_DELTA         , nfstime4       },
    {FATTR_TIME_METADATA      , nfstime4       },
    {FATTR_TIME_MODIFY        , nfstime4       },
    {FATTR_TIME_MODIFY_SET     settime4       }},

#endif
   
enum fs4_status_type {
        STATUS4_FIXED     = 1,
        STATUS4_UPDATED   = 2,
        STATUS4_VERSIONED = 3,
        STATUS4_WRITABLE  = 4,
        STATUS4_REFERRAL  = 5
};

enum layouttype4 {
        LAYOUT4_NFSV4_1_FILES   = 0x1,
        LAYOUT4_OSD2_OBJECTS    = 0x2,
        LAYOUT4_BLOCK_VOLUME    = 0x3
};
