/*
 *  (C) 2001 by Argonne National Laboratory.
 *  (C) 2009 by Microsoft Corporation.
 *      See COPYRIGHT in the SDK directory.
 */

#ifndef MPI_INCLUDED
#define MPI_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif


#ifndef MSMPI_VER
#define MSMPI_VER 0x100
#endif


/*---------------------------------------------------------------------------*/
/* SAL ANNOTATIONS                                                           */
/*---------------------------------------------------------------------------*/
/*
 * Define SAL annotations if they aren't defined yet.  Note that if we define
 * them, we undefine them at the end of this file so that future inclusion of
 * sal.h doesn't cause errors.
 */
#ifndef __in
#define MSMPI_DEFINED_SAL
#define __in
#define __in_z
#define __in_opt
#define __out
#define __out_z
#define __out_opt
#define __inout
#define __inout_ecount( x )
#define __in_bcount( x )
#define __in_ecount( x )
#define __out_bcount( x )
#define __out_ecount( x )
#define __out_ecount_z( x )
#define __out_ecount_part( x, y )
#define __out_ecount_part_z( x, y )
#define __deref_ecount_opt( x )
#define __exceptthat
#define __maybenull
#endif


/*---------------------------------------------------------------------------*/
/* MSMPI Calling convention                                                  */
/*---------------------------------------------------------------------------*/

#define MPIAPI __stdcall


/*---------------------------------------------------------------------------*/
/* MPI ERROR CLASS                                                           */
/*---------------------------------------------------------------------------*/

#define MPI_SUCCESS          0      /* Successful return code */

#define MPI_ERR_BUFFER       1      /* Invalid buffer pointer */
#define MPI_ERR_COUNT        2      /* Invalid count argument */
#define MPI_ERR_TYPE         3      /* Invalid datatype argument */
#define MPI_ERR_TAG          4      /* Invalid tag argument */
#define MPI_ERR_COMM         5      /* Invalid communicator */
#define MPI_ERR_RANK         6      /* Invalid rank */
#define MPI_ERR_REQUEST     19      /* Invalid request (handle) */
#define MPI_ERR_ROOT         7      /* Invalid root */
#define MPI_ERR_GROUP        8      /* Invalid group */
#define MPI_ERR_OP           9      /* Invalid operation */
#define MPI_ERR_TOPOLOGY    10      /* Invalid topology */
#define MPI_ERR_DIMS        11      /* Invalid dimension argument */
#define MPI_ERR_ARG         12      /* Invalid argument */
#define MPI_ERR_UNKNOWN     13      /* Unknown error */
#define MPI_ERR_TRUNCATE    14      /* Message truncated on receive */
#define MPI_ERR_OTHER       15      /* Other error; use Error_string */
#define MPI_ERR_INTERN      16      /* Internal error code */
#define MPI_ERR_IN_STATUS   17      /* Error code is in status */
#define MPI_ERR_PENDING     18      /* Pending request */
#define MPI_ERR_KEYVAL      48      /* Invalid keyval  */
#define MPI_ERR_NO_MEM      34      /* Alloc_mem could not allocate memory */
#define MPI_ERR_BASE        46      /* Invalid base passed to MPI_Free_mem */
#define MPI_ERR_INFO_KEY    29      /* Key longer than MPI_MAX_INFO_KEY */
#define MPI_ERR_INFO_VALUE  30      /* Value longer than MPI_MAX_INFO_VAL */
#define MPI_ERR_INFO_NOKEY  31      /* Invalid key passed to MPI_Info_delete */
#define MPI_ERR_SPAWN       42      /* Error in spawning processes */
#define MPI_ERR_PORT        38      /* Invalid port name in MPI_comm_connect*/
#define MPI_ERR_SERVICE     41      /* Invalid service name in MPI_Unpublish_name */
#define MPI_ERR_NAME        33      /* Invalid service name in MPI_Lookup_name */
#define MPI_ERR_WIN         45      /* Invalid win argument */
#define MPI_ERR_SIZE        51      /* Invalid size argument */
#define MPI_ERR_DISP        52      /* Invalid disp argument */
#define MPI_ERR_INFO        28      /* Invalid info argument */
#define MPI_ERR_LOCKTYPE    47      /* Invalid locktype argument */
#define MPI_ERR_ASSERT      53      /* Invalid assert argument */
#define MPI_ERR_RMA_CONFLICT 49     /* Conflicting accesses to window */
#define MPI_ERR_RMA_SYNC    50      /* Wrong synchronization of RMA calls */
#define MPI_ERR_FILE        27      /* Invalid file handle */
#define MPI_ERR_NOT_SAME    35      /* Collective argument/sequence not the same on all processes */
#define MPI_ERR_AMODE       21      /* Error related to amode passed to MPI_File_open */
#define MPI_ERR_UNSUPPORTED_DATAREP   43  /* Unsupported dararep in MPI_File_set_view */
#define MPI_ERR_UNSUPPORTED_OPERATION 44  /* Unsupported operation on file */
#define MPI_ERR_NO_SUCH_FILE 37     /* File does not exist */
#define MPI_ERR_FILE_EXISTS 25      /* File exists */
#define MPI_ERR_BAD_FILE    22      /* Invalid file name (e.g., path name too long) */
#define MPI_ERR_ACCESS      20      /* Premission denied */
#define MPI_ERR_NO_SPACE    36      /* Not enough space */
#define MPI_ERR_QUOTA       39      /* Quota exceeded */
#define MPI_ERR_READ_ONLY   40      /* Read-only file or file system */
#define MPI_ERR_FILE_IN_USE 26      /* File operation could not be completed, file in use */
#define MPI_ERR_DUP_DATAREP 24      /* Data representation identifier already registered */
#define MPI_ERR_CONVERSION  23      /* Error in user data conversion function */
#define MPI_ERR_IO          32      /* Other I/O error */

#define MPI_ERR_LASTCODE    0x3fffffff    /* Last valid error code for a predefined error class */

#define MPICH_ERR_LAST_CLASS 53


/*---------------------------------------------------------------------------*/
/* MPI Basic integer types                                                   */
/*---------------------------------------------------------------------------*/

/* Address size integer */
#ifdef _WIN64
typedef __int64 MPI_Aint;
#else
typedef int MPI_Aint;
#endif

/* Fortran INTEGER */
typedef int MPI_Fint;

/* File offset */
typedef __int64 MPI_Offset;


/*---------------------------------------------------------------------------*/
/* MPI_Datatype                                                              */
/*---------------------------------------------------------------------------*/

typedef int MPI_Datatype;
#define MPI_DATATYPE_NULL  ((MPI_Datatype)0x0c000000)

#define MPI_CHAR           ((MPI_Datatype)0x4c000101)
#define MPI_SIGNED_CHAR    ((MPI_Datatype)0x4c000118)
#define MPI_UNSIGNED_CHAR  ((MPI_Datatype)0x4c000102)
#define MPI_BYTE           ((MPI_Datatype)0x4c00010d)
#define MPI_WCHAR          ((MPI_Datatype)0x4c00020e)
#define MPI_SHORT          ((MPI_Datatype)0x4c000203)
#define MPI_UNSIGNED_SHORT ((MPI_Datatype)0x4c000204)
#define MPI_INT            ((MPI_Datatype)0x4c000405)
#define MPI_UNSIGNED       ((MPI_Datatype)0x4c000406)
#define MPI_LONG           ((MPI_Datatype)0x4c000407)
#define MPI_UNSIGNED_LONG  ((MPI_Datatype)0x4c000408)
#define MPI_FLOAT          ((MPI_Datatype)0x4c00040a)
#define MPI_DOUBLE         ((MPI_Datatype)0x4c00080b)
#define MPI_LONG_DOUBLE    ((MPI_Datatype)0x4c00080c)
#define MPI_LONG_LONG_INT  ((MPI_Datatype)0x4c000809)
#define MPI_UNSIGNED_LONG_LONG ((MPI_Datatype)0x4c000819)
#define MPI_LONG_LONG      MPI_LONG_LONG_INT

#define MPI_PACKED         ((MPI_Datatype)0x4c00010f)
#define MPI_LB             ((MPI_Datatype)0x4c000010)
#define MPI_UB             ((MPI_Datatype)0x4c000011)

/*
 * The layouts for the types MPI_DOUBLE_INT etc. are
 *
 *      struct { double a; int b; }
 */
#define MPI_FLOAT_INT         ((MPI_Datatype)0x8c000000)
#define MPI_DOUBLE_INT        ((MPI_Datatype)0x8c000001)
#define MPI_LONG_INT          ((MPI_Datatype)0x8c000002)
#define MPI_SHORT_INT         ((MPI_Datatype)0x8c000003)
#define MPI_2INT              ((MPI_Datatype)0x4c000816)
#define MPI_LONG_DOUBLE_INT   ((MPI_Datatype)0x8c000004)

/* Fortran types */
#define MPI_COMPLEX           ((MPI_Datatype)0x4c00081e)
#define MPI_DOUBLE_COMPLEX    ((MPI_Datatype)0x4c001022)
#define MPI_LOGICAL           ((MPI_Datatype)0x4c00041d)
#define MPI_REAL              ((MPI_Datatype)0x4c00041c)
#define MPI_DOUBLE_PRECISION  ((MPI_Datatype)0x4c00081f)
#define MPI_INTEGER           ((MPI_Datatype)0x4c00041b)
#define MPI_2INTEGER          ((MPI_Datatype)0x4c000820)
#define MPI_2COMPLEX          ((MPI_Datatype)0x4c001024)
#define MPI_2DOUBLE_COMPLEX   ((MPI_Datatype)0x4c002025)
#define MPI_2REAL             ((MPI_Datatype)0x4c000821)
#define MPI_2DOUBLE_PRECISION ((MPI_Datatype)0x4c001023)
#define MPI_CHARACTER         ((MPI_Datatype)0x4c00011a)

/* Size-specific types (see MPI 2.2, 16.2.5) */
#define MPI_REAL4             ((MPI_Datatype)0x4c000427)
#define MPI_REAL8             ((MPI_Datatype)0x4c000829)
#define MPI_REAL16            ((MPI_Datatype)0x4c00102b)
#define MPI_COMPLEX8          ((MPI_Datatype)0x4c000828)
#define MPI_COMPLEX16         ((MPI_Datatype)0x4c00102a)
#define MPI_COMPLEX32         ((MPI_Datatype)0x4c00202c)
#define MPI_INTEGER1          ((MPI_Datatype)0x4c00012d)
#define MPI_INTEGER2          ((MPI_Datatype)0x4c00022f)
#define MPI_INTEGER4          ((MPI_Datatype)0x4c000430)
#define MPI_INTEGER8          ((MPI_Datatype)0x4c000831)
#define MPI_INTEGER16         ((MPI_Datatype)0x4c001032)


/*---------------------------------------------------------------------------*/
/* MPI_Comm                                                                  */
/*---------------------------------------------------------------------------*/

typedef int MPI_Comm;
#define MPI_COMM_NULL  ((MPI_Comm)0x04000000)

#define MPI_COMM_WORLD ((MPI_Comm)0x44000000)
#define MPI_COMM_SELF  ((MPI_Comm)0x44000001)


/*---------------------------------------------------------------------------*/
/* MPI_Win                                                                   */
/*---------------------------------------------------------------------------*/

typedef int MPI_Win;
#define MPI_WIN_NULL ((MPI_Win)0x20000000)


/*---------------------------------------------------------------------------*/
/* MPI_File                                                                  */
/*---------------------------------------------------------------------------*/

typedef struct ADIOI_FileD* MPI_File;
#define MPI_FILE_NULL ((MPI_File)0)


/*---------------------------------------------------------------------------*/
/* MPI_Op                                                                    */
/*---------------------------------------------------------------------------*/

typedef int MPI_Op;
#define MPI_OP_NULL ((MPI_Op)0x18000000)

#define MPI_MAX     ((MPI_Op)0x58000001)
#define MPI_MIN     ((MPI_Op)0x58000002)
#define MPI_SUM     ((MPI_Op)0x58000003)
#define MPI_PROD    ((MPI_Op)0x58000004)
#define MPI_LAND    ((MPI_Op)0x58000005)
#define MPI_BAND    ((MPI_Op)0x58000006)
#define MPI_LOR     ((MPI_Op)0x58000007)
#define MPI_BOR     ((MPI_Op)0x58000008)
#define MPI_LXOR    ((MPI_Op)0x58000009)
#define MPI_BXOR    ((MPI_Op)0x5800000a)
#define MPI_MINLOC  ((MPI_Op)0x5800000b)
#define MPI_MAXLOC  ((MPI_Op)0x5800000c)
#define MPI_REPLACE ((MPI_Op)0x5800000d)


/*---------------------------------------------------------------------------*/
/* MPI_Info                                                                  */
/*---------------------------------------------------------------------------*/

typedef int MPI_Info;
#define MPI_INFO_NULL         ((MPI_Info)0x1c000000)


/*---------------------------------------------------------------------------*/
/* MPI_Request                                                               */
/*---------------------------------------------------------------------------*/

typedef int MPI_Request;
#define MPI_REQUEST_NULL ((MPI_Request)0x2c000000)


/*---------------------------------------------------------------------------*/
/* MPI_Group                                                                 */
/*---------------------------------------------------------------------------*/

typedef int MPI_Group;
#define MPI_GROUP_NULL  ((MPI_Group)0x08000000)

#define MPI_GROUP_EMPTY ((MPI_Group)0x48000000)


/*---------------------------------------------------------------------------*/
/* MPI_Errhandler                                                            */
/*---------------------------------------------------------------------------*/

typedef int MPI_Errhandler;
#define MPI_ERRHANDLER_NULL  ((MPI_Errhandler)0x14000000)

#define MPI_ERRORS_ARE_FATAL ((MPI_Errhandler)0x54000000)
#define MPI_ERRORS_RETURN    ((MPI_Errhandler)0x54000001)

/*---------------------------------------------------------------------------*/
/* MPI_Status                                                                */
/*---------------------------------------------------------------------------*/

typedef struct MPI_Status
{
    int count;
    int cancelled;
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;

} MPI_Status;

#define MPI_STATUS_IGNORE ((MPI_Status*)(MPI_Aint)1)
#define MPI_STATUSES_IGNORE ((MPI_Status*)(MPI_Aint)1)


/*---------------------------------------------------------------------------*/
/* MISC CONSTANTS                                                            */
/*---------------------------------------------------------------------------*/

/* Used in: Count, Index, Rank, Color, Toplogy, Precision, Exponent range  */
#define MPI_UNDEFINED   (-32766)

/* Used in: Rank */
#define MPI_PROC_NULL   (-1)
#define MPI_ANY_SOURCE  (-2)
#define MPI_ROOT        (-3)

/* Used in: Tag */
#define MPI_ANY_TAG     (-1)

/* Used for: Buffer address */
#define MPI_BOTTOM      ((void*)0)


/*---------------------------------------------------------------------------*/
/* Chapter 3: Point-to-Point Communication                                   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 3.2: Blocking Communication         */
/*---------------------------------------------*/

int
MPIAPI
MPI_Send(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Send(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Recv(
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Recv(
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Get_count(
    __in MPI_Status* status,
    __in MPI_Datatype datatype,
    __out int* count
    );
int
MPIAPI
PMPI_Get_count(
    __in MPI_Status* status,
    __in MPI_Datatype datatype,
    __out int* count
    );


/*---------------------------------------------*/
/* Section 3.4: Communication Modes            */
/*---------------------------------------------*/

int
MPIAPI
MPI_Bsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Bsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Ssend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Ssend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Rsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Rsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 3.6: Buffer Allocation              */
/*---------------------------------------------*/

/* Upper bound on bsend overhead for each message */
#define MSMPI_BSEND_OVERHEAD_V1   95
#define MSMPI_BSEND_OVERHEAD_V2   MSMPI_BSEND_OVERHEAD_V1

#if MSMPI_VER >= 0x300
#  define MPI_BSEND_OVERHEAD  MSMPI_Get_bsend_overhead()
#else
#  define MPI_BSEND_OVERHEAD  MSMPI_BSEND_OVERHEAD_V1
#endif

int
MPIAPI
MPI_Buffer_attach(
    __in void* buffer,
    __in int size
    );
int
MPIAPI
PMPI_Buffer_attach(
    __in void* buffer,
    __in int size
    );

int
MPIAPI
MPI_Buffer_detach(
    __out void* buffer_addr,
    __out int* size
    );
int
MPIAPI
PMPI_Buffer_detach(
    __out void* buffer_addr,
    __out int* size
    );


/*---------------------------------------------*/
/* Section 3.7: Nonblocking Communication      */
/*---------------------------------------------*/

int
MPIAPI
MPI_Isend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Isend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Ibsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Ibsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Issend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Issend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Irsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Irsend(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Irecv(
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Irecv(
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );


/*---------------------------------------------*/
/* Section 3.7.3: Communication Completion     */
/*---------------------------------------------*/

int
MPIAPI
MPI_Wait(
    __inout MPI_Request* request,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Wait(
    __inout MPI_Request* request,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Test(
    __inout MPI_Request* request,
    __out int* flag,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Test(
    __inout MPI_Request* request,
    __out int* flag,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Request_free(
    __inout MPI_Request* request
    );
int
MPIAPI
PMPI_Request_free(
    __inout MPI_Request* request
    );


/*---------------------------------------------*/
/* Section 3.7.5: Multiple Completions         */
/*---------------------------------------------*/

int
MPIAPI
MPI_Waitany(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* index,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Waitany(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* index,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Testany(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* index,
    __out int* flag,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Testany(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* index,
    __out int* flag,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Waitall(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out_ecount(count) MPI_Status* array_of_statuses
    );
int
MPIAPI
PMPI_Waitall(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out_ecount(count) MPI_Status* array_of_statuses
    );

int
MPIAPI
MPI_Testall(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* flag,
    __out_ecount(count) MPI_Status* array_of_statuses
    );
int
MPIAPI
PMPI_Testall(
    __in int count,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* flag,
    __out_ecount(count) MPI_Status* array_of_statuses
    );

int
MPIAPI
MPI_Waitsome(
    __in int incount,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* outcount,
    __out_ecount_part(incount,*outcount) int* array_of_indices,
    __out_ecount_part(incount,*outcount) MPI_Status* array_of_statuses
    );
int
MPIAPI
PMPI_Waitsome(
    __in int incount,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* outcount,
    __out_ecount_part(incount,*outcount) int* array_of_indices,
    __out_ecount_part(incount,*outcount) MPI_Status* array_of_statuses
    );

int
MPIAPI
MPI_Testsome(
    __in int incount,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* outcount,
    __out_ecount_part(incount,*outcount) int* array_of_indices,
    __out_ecount_part(incount,*outcount) MPI_Status* array_of_statuses
    );
int
MPIAPI
PMPI_Testsome(
    __in int incount,
    __inout_ecount(count) MPI_Request* array_of_requests,
    __out int* outcount,
    __out_ecount_part(incount,*outcount) int* array_of_indices,
    __out_ecount_part(incount,*outcount) MPI_Status* array_of_statuses
    );


/*---------------------------------------------*/
/* Section 3.7.6: Test of status               */
/*---------------------------------------------*/

int
MPIAPI
MPI_Request_get_status(
    __in MPI_Request request,
    __out int* flag,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Request_get_status(
    __in MPI_Request request,
    __out int* flag,
    __out MPI_Status* status
    );


/*---------------------------------------------*/
/* Section 3.8: Probe and Cancel               */
/*---------------------------------------------*/

int
MPIAPI
MPI_Iprobe(
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out int* flag,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Iprobe(
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out int* flag,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Probe(
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Probe(
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Cancel(
    __in MPI_Request* request
    );
int
MPIAPI
PMPI_Cancel(
    __in MPI_Request* request
    );

int
MPIAPI
MPI_Test_cancelled(
    __in MPI_Status* status,
    __out int* flag
    );
int
MPIAPI
PMPI_Test_cancelled(
    __in MPI_Status* request,
    __out int* flag
    );


/*---------------------------------------------*/
/* Section 3.9: Persistent Communication       */
/*---------------------------------------------*/

int
MPIAPI
MPI_Send_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Send_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Bsend_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Bsend_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Ssend_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Ssend_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Rsend_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Rsend_init(
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Recv_init(
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Recv_init(
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int source,
    __in int tag,
    __in MPI_Comm comm,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Start(
    __in MPI_Request* request
    );
int
MPIAPI
PMPI_Start(
    __in MPI_Request* request
    );

int
MPIAPI
MPI_Startall(
    __in int count,
    __in_ecount(count) MPI_Request* array_of_requests
    );
int
MPIAPI
PMPI_Startall(
    __in int count,
    __in_ecount(count) MPI_Request* array_of_requests
    );


/*---------------------------------------------*/
/* Section 3.10: Send-Recv                     */
/*---------------------------------------------*/

int
MPIAPI
MPI_Sendrecv(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __in int dest,
    __in int sendtag,
    __out void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int source,
    __in int recvtag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Sendrecv(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __in int dest,
    __in int sendtag,
    __out void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int source,
    __in int recvtag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Sendrecv_replace(
    __inout void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int sendtag,
    __in int source,
    __in int recvtag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Sendrecv_replace(
    __inout void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __in int dest,
    __in int sendtag,
    __in int source,
    __in int recvtag,
    __in MPI_Comm comm,
    __out MPI_Status* status
    );


/*---------------------------------------------------------------------------*/
/* Chapter 4: Datatypes                                                      */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 4.1: Derived Datatypes              */
/*---------------------------------------------*/

int
MPIAPI
MPI_Type_contiguous(
    __in int count,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_contiguous(
    __in int count,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_vector(
    __in int count,
    __in int blocklength,
    __in int stride,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_vector(
    __in int count,
    __in int blocklength,
    __in int stride,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_create_hvector(
    __in int count,
    __in int blocklength,
    __in MPI_Aint stride,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_hvector(
    __in int count,
    __in int blocklength,
    __in MPI_Aint stride,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_indexed(
    __in int count,
    __in_ecount(count) int* array_of_blocklengths,
    __in_ecount(count) int* array_of_displacements,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_indexed(
    __in int count,
    __in_ecount(count) int* array_of_blocklengths,
    __in_ecount(count) int* array_of_displacements,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_create_hindexed(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_hindexed(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_create_indexed_block(
    __in int count,
    __in int blocklength,
    __in_ecount(count) int array_of_displacements[],
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_indexed_block(
    __in int count,
    __in int blocklength,
    __in_ecount(count) int array_of_displacements[],
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_create_struct(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in_ecount(count) MPI_Datatype array_of_types[],
    __in MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_struct(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in_ecount(count) MPI_Datatype array_of_types[],
    __in MPI_Datatype* newtype
    );


#define MPI_ORDER_C         56
#define MPI_ORDER_FORTRAN   57

int
MPIAPI
MPI_Type_create_subarray(
    __in int ndims,
    __in_ecount(ndims) int array_of_sizes[],
    __in_ecount(ndims) int array_of_subsizes[],
    __in_ecount(ndims) int array_of_starts[],
    __in int order,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_subarray(
    __in int ndims,
    __in_ecount(ndims) int array_of_sizes[],
    __in_ecount(ndims) int array_of_subsizes[],
    __in_ecount(ndims) int array_of_starts[],
    __in int order,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );


#define MPI_DISTRIBUTE_BLOCK         121
#define MPI_DISTRIBUTE_CYCLIC        122
#define MPI_DISTRIBUTE_NONE          123
#define MPI_DISTRIBUTE_DFLT_DARG (-49767)

int
MPIAPI
MPI_Type_create_darray(
    __in int size,
    __in int rank,
    __in int ndims,
    __in_ecount(ndims) int array_of_gszies[],
    __in_ecount(ndims) int array_of_distribs[],
    __in_ecount(ndims) int array_of_dargs[],
    __in_ecount(ndims) int array_of_psizes[],
    __in int order,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_darray(
    __in int size,
    __in int rank,
    __in int ndims,
    __in_ecount(ndims) int array_of_gszies[],
    __in_ecount(ndims) int array_of_distribs[],
    __in_ecount(ndims) int array_of_dargs[],
    __in_ecount(ndims) int array_of_psizes[],
    __in int order,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );


/*---------------------------------------------*/
/* Section 4.1.5: Datatype Address and Size    */
/*---------------------------------------------*/

int
MPIAPI
MPI_Get_address(
    __in void* location,
    __out MPI_Aint* address
    );
int
MPIAPI
PMPI_Get_address(
    __in void* location,
    __out MPI_Aint* address
    );

int
MPIAPI
MPI_Type_size(
    __in MPI_Datatype datatype,
    __out int* size
    );
int
MPIAPI
PMPI_Type_size(
    __in MPI_Datatype datatype,
    __out int* size
    );


/*---------------------------------------------*/
/* Section 4.1.7: Datatype Extent and Bounds   */
/*---------------------------------------------*/

int
MPIAPI
MPI_Type_get_extent(
    __in MPI_Datatype datatype,
    __out MPI_Aint* lb,
    __out MPI_Aint* extent
    );
int
MPIAPI
PMPI_Type_get_extent(
    __in MPI_Datatype datatype,
    __out MPI_Aint* lb,
    __out MPI_Aint* extent
    );

int
MPIAPI
MPI_Type_create_resized(
    __in MPI_Datatype oldtype,
    __in MPI_Aint lb,
    __in MPI_Aint extent,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_resized(
    __in MPI_Datatype oldtype,
    __in MPI_Aint lb,
    __in MPI_Aint extent,
    __out MPI_Datatype* newtype
    );


/*---------------------------------------------*/
/* Section 4.1.8: Datatype True Extent         */
/*---------------------------------------------*/

int
MPIAPI
MPI_Type_get_true_extent(
    __in MPI_Datatype datatype,
    __out MPI_Aint* true_lb,
    __out MPI_Aint* true_extent
    );
int
MPIAPI
PMPI_Type_get_true_extent(
    __in MPI_Datatype datatype,
    __out MPI_Aint* true_lb,
    __out MPI_Aint* true_extent
    );


/*---------------------------------------------*/
/* Section 4.1.9: Datatype Commit and Free     */
/*---------------------------------------------*/

int
MPIAPI
MPI_Type_commit(
    __in MPI_Datatype* datatype
    );
int
MPIAPI
PMPI_Type_commit(
    __in MPI_Datatype* datatype
    );

int
MPIAPI
MPI_Type_free(
    __inout MPI_Datatype* datatype
    );
int
MPIAPI
PMPI_Type_free(
    __inout MPI_Datatype* datatype
    );


/*---------------------------------------------*/
/* Section 4.1.10: Datatype Duplication        */
/*---------------------------------------------*/

int
MPIAPI
MPI_Type_dup(
    __in MPI_Datatype type,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_dup(
    __in MPI_Datatype type,
    __out MPI_Datatype* newtype
    );


/*---------------------------------------------*/
/* Section 4.1.11: Datatype and Communication  */
/*---------------------------------------------*/

int
MPIAPI
MPI_Get_elements(
    __in MPI_Status* status,
    __in MPI_Datatype datatype,
    __out int* count
    );
int
MPIAPI
PMPI_Get_elements(
    __in MPI_Status* status,
    __in MPI_Datatype datatype,
    __out int* count
    );


/*---------------------------------------------*/
/* Section 4.1.13: Decoding a Datatype         */
/*---------------------------------------------*/

/* Datatype combiners result */
enum
{
    MPI_COMBINER_NAMED            = 1,
    MPI_COMBINER_DUP              = 2,
    MPI_COMBINER_CONTIGUOUS       = 3,
    MPI_COMBINER_VECTOR           = 4,
    MPI_COMBINER_HVECTOR_INTEGER  = 5,
    MPI_COMBINER_HVECTOR          = 6,
    MPI_COMBINER_INDEXED          = 7,
    MPI_COMBINER_HINDEXED_INTEGER = 8,
    MPI_COMBINER_HINDEXED         = 9,
    MPI_COMBINER_INDEXED_BLOCK    = 10,
    MPI_COMBINER_STRUCT_INTEGER   = 11,
    MPI_COMBINER_STRUCT           = 12,
    MPI_COMBINER_SUBARRAY         = 13,
    MPI_COMBINER_DARRAY           = 14,
    MPI_COMBINER_F90_REAL         = 15,
    MPI_COMBINER_F90_COMPLEX      = 16,
    MPI_COMBINER_F90_INTEGER      = 17,
    MPI_COMBINER_RESIZED          = 18
};

int
MPIAPI
MPI_Type_get_envelope(
    __in MPI_Datatype datatype,
    __out int* num_integers,
    __out int* num_addresses,
    __out int* num_datatypes,
    __out int* combiner
    );
int
MPIAPI
PMPI_Type_get_envelope(
    __in MPI_Datatype datatype,
    __out int* num_integers,
    __out int* num_addresses,
    __out int* num_datatypes,
    __out int* combiner
    );

int
MPIAPI
MPI_Type_get_contents(
    __in MPI_Datatype datatype,
    __in int max_integers,
    __in int max_addresses,
    __in int max_datatypes,
    __out_ecount(max_integers) int array_of_integers[],
    __out_ecount(max_addresses) MPI_Aint array_of_addresses[],
    __out_ecount(max_datatypes) MPI_Datatype array_of_datatypes[]
    );
int
MPIAPI
PMPI_Type_get_contents(
    __in MPI_Datatype datatype,
    __in int max_integers,
    __in int max_addresses,
    __in int max_datatypes,
    __out_ecount(max_integers) int array_of_integers[],
    __out_ecount(max_addresses) MPI_Aint array_of_addresses[],
    __out_ecount(max_datatypes) MPI_Datatype array_of_datatypes[]
    );


/*---------------------------------------------*/
/* Section 4.2: Datatype Pack and Unpack       */
/*---------------------------------------------*/

int
MPIAPI
MPI_Pack(
    __in void* inbuf,
    __in int incount,
    __in MPI_Datatype datatype,
    __out_bcount(outsize) void* outbuf,
    __in int outsize,
    __inout int* position,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Pack(
    __in void* inbuf,
    __in int incount,
    __in MPI_Datatype datatype,
    __out_bcount(outsize) void* outbuf,
    __in int outsize,
    __inout int* position,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Unpack(
    __in_bcount(insize) void* inbuf,
    __in int insize,
    __inout int* position,
    __out void* outbuf,
    __in int outcount,
    __in MPI_Datatype datatype,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Unpack(
    __in_bcount(insize) void* inbuf,
    __in int insize,
    __inout int* position,
    __out void* outbuf,
    __in int outcount,
    __in MPI_Datatype datatype,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Pack_size(
    __in int incount,
    __in MPI_Datatype datatype,
    __in MPI_Comm comm,
    __out int* size
    );
int
MPIAPI
PMPI_Pack_size(
    __in int incount,
    __in MPI_Datatype datatype,
    __in MPI_Comm comm,
    __out int* size
    );


/*---------------------------------------------*/
/* Section 4.3: Canonical Pack and Unpack      */
/*---------------------------------------------*/

int
MPIAPI
MPI_Pack_external(
    __in_z char* datarep,
    __in void* inbuf,
    __in int incount,
    __in MPI_Datatype datatype,
    __out_bcount(outsize) void* outbuf,
    __in MPI_Aint outsize,
    __inout MPI_Aint* position
    );
int
MPIAPI
PMPI_Pack_external(
    __in_z char* datarep,
    __in void* inbuf,
    __in int incount,
    __in MPI_Datatype datatype,
    __out_bcount(outsize) void* outbuf,
    __in MPI_Aint outsize,
    __inout MPI_Aint* position
    );

int
MPIAPI
MPI_Unpack_external(
    __in_z char* datarep,
    __in_bcount(insize) void* inbuf,
    __in MPI_Aint insize,
    __inout MPI_Aint* position,
    __out void* outbuf,
    __in int outcount,
    __in MPI_Datatype datatype
    );
int
MPIAPI
PMPI_Unpack_external(
    __in_z char* datarep,
    __in_bcount(insize) void* inbuf,
    __in MPI_Aint insize,
    __inout MPI_Aint* position,
    __out void* outbuf,
    __in int outcount,
    __in MPI_Datatype datatype
    );

int
MPIAPI
MPI_Pack_external_size(
    __in_z char* datarep,
    __in int incount,
    __in MPI_Datatype datatype,
    __out MPI_Aint* size
    );
int
MPIAPI
PMPI_Pack_external_size(
    __in_z char* datarep,
    __in int incount,
    __in MPI_Datatype datatype,
    __out MPI_Aint* size
    );


/*---------------------------------------------------------------------------*/
/* Chapter 5: Collective Communication                                       */
/*---------------------------------------------------------------------------*/

#define MPI_IN_PLACE ((void*)(MPI_Aint)-1)

/*---------------------------------------------*/
/* Section 5.3: Barrier Synchronization        */
/*---------------------------------------------*/

int
MPIAPI
MPI_Barrier(
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Barrier(
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 5.4: Broadcast                      */
/*---------------------------------------------*/

int
MPIAPI
MPI_Bcast(
    __inout void* buffer,
    __in int count,
    __in MPI_Datatype datatype,
    __in int root,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Bcast(
    __inout void* buffer,
    __in int count,
    __in MPI_Datatype datatype,
    __in int root,
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 5.5: Gather                         */
/*---------------------------------------------*/

int
MPIAPI
MPI_Gather(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Gather(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Gatherv(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int* recvcounts,
    __in int* displs,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Gatherv(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int* recvcounts,
    __in int* displs,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 5.6: Scatter                        */
/*---------------------------------------------*/

int
MPIAPI
MPI_Scatter(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Scatter(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Scatterv(
    __in void* sendbuf,
    __in int* sendcounts,
    __in int* displs,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Scatterv(
    __in void* sendbuf,
    __in int* sendcounts,
    __in int* displs,
    __in MPI_Datatype sendtype,
    __out_opt void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in int root,
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 5.6: Gather-to-all                  */
/*---------------------------------------------*/

int
MPIAPI
MPI_Allgather(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Allgather(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Allgatherv(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int* recvcounts,
    __in int* displs,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Allgatherv(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int* recvcounts,
    __in int* displs,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 5.6: All-to-All Scatter/Gather      */
/*---------------------------------------------*/

int
MPIAPI
MPI_Alltoall(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Alltoall(
    __in void* sendbuf,
    __in int sendcount,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int recvcount,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Alltoallv(
    __in void* sendbuf,
    __in int* sendcounts,
    __in int* sdispls,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int* recvcounts,
    __in int* rdispls,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Alltoallv(
    __in void* sendbuf,
    __in int* sendcounts,
    __in int* sdispls,
    __in MPI_Datatype sendtype,
    __out void* recvbuf,
    __in int* recvcounts,
    __in int* rdispls,
    __in MPI_Datatype recvtype,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Alltoallw(
    __in void* sendbuf,
    __in int sendcounts[],
    __in int sdispls[],
    __in MPI_Datatype sendtypes[],
    __out void* recvbuf,
    __in int recvcounts[],
    __in int rdispls[],
    __in MPI_Datatype recvtypes[],
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Alltoallw(
    __in void* sendbuf,
    __in int sendcounts[],
    __in int sdispls[],
    __in MPI_Datatype sendtypes[],
    __out void* recvbuf,
    __in int recvcounts[],
    __in int rdispls[],
    __in MPI_Datatype recvtypes[],
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 5.9: Global Reduction Operations    */
/*---------------------------------------------*/

typedef
void
(MPIAPI MPI_User_function)(
    __in void* invec,
    __inout void* inoutvec,
    __in int* len,
    __in MPI_Datatype* datatype
    );

int
MPIAPI
MPI_Op_create(
    __in MPI_User_function* function,
    __in int commute,
    __out MPI_Op* op
    );
int
MPIAPI
PMPI_Op_create(
    __in MPI_User_function* function,
    __in int commute,
    __out MPI_Op* op
    );

int
MPIAPI
MPI_Op_free(
    __inout MPI_Op* op
    );
int
MPIAPI
PMPI_Op_free(
    __inout MPI_Op* op
    );

int
MPIAPI
MPI_Reduce(
    __in void* sendbuf,
    __out_opt void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in int root,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Reduce(
    __in void* sendbuf,
    __out_opt void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in int root,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Allreduce(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Allreduce(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Reduce_local(
    __in void *inbuf, 
    __inout void *inoutbuf, 
    __in int count, 
    __in MPI_Datatype datatype, 
    __in MPI_Op op
    );
int
MPIAPI
PMPI_Reduce_local(
    __in void *inbuf, 
    __inout void *inoutbuf, 
    __in int count, 
    __in MPI_Datatype datatype, 
    __in MPI_Op op
    );

/*---------------------------------------------*/
/* Section 5.10: Reduce-Scatter                */
/*---------------------------------------------*/

int
MPIAPI
MPI_Reduce_scatter(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int* recvcounts,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Reduce_scatter(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int* recvcounts,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );


/*---------------------------------------------*/
/* Section 5.11: Scan                          */
/*---------------------------------------------*/

int
MPIAPI
MPI_Scan(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Scan(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );

int
MPIAPI
MPI_Exscan(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );
int
MPIAPI
PMPI_Exscan(
    __in void* sendbuf,
    __out void* recvbuf,
    __in int count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Comm comm
    );


/*---------------------------------------------------------------------------*/
/* Chapter 6: Groups, Contexts, Communicators, and Caching                   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 6.3: Group Management               */
/*---------------------------------------------*/

int
MPIAPI
MPI_Group_size(
    __in MPI_Group group,
    __out int* size
    );
int
MPIAPI
PMPI_Group_size(
    __in MPI_Group group,
    __out int* size
    );

int
MPIAPI
MPI_Group_rank(
    __in MPI_Group group,
    __out int* rank
    );
int
MPIAPI
PMPI_Group_rank(
    __in MPI_Group group,
    __out int* rank
    );

int
MPIAPI
MPI_Group_translate_ranks(
    __in MPI_Group group1,
    __in int n,
    __in_ecount(n) int* ranks1,
    __in MPI_Group group2,
    __out int* ranks2
    );

int
MPIAPI
PMPI_Group_translate_ranks(
    __in MPI_Group group1,
    __in int n,
    __in_ecount(n) int* ranks1,
    __in MPI_Group group2,
    __out int* ranks2
    );

/* Results of the compare operations */
#define MPI_IDENT       0
#define MPI_CONGRUENT   1
#define MPI_SIMILAR     2
#define MPI_UNEQUAL     3

int
MPIAPI
MPI_Group_compare(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out int* result
    );
int
MPIAPI
PMPI_Group_compare(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out int* result
    );

int
MPIAPI
MPI_Comm_group(
    __in MPI_Comm comm,
    __out MPI_Group* group
    );
int
MPIAPI
PMPI_Comm_group(
    __in MPI_Comm comm,
    __out MPI_Group* group
    );

int
MPIAPI
MPI_Group_union(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out MPI_Group* newgroup
    );
int
MPIAPI
PMPI_Group_union(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out MPI_Group* newgroup
    );

int
MPIAPI
MPI_Group_intersection(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out MPI_Group* newgroup
    );
int
MPIAPI
PMPI_Group_intersection(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out MPI_Group* newgroup
    );

int
MPIAPI
MPI_Group_difference(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out MPI_Group* newgroup
    );
int
MPIAPI
PMPI_Group_difference(
    __in MPI_Group group1,
    __in MPI_Group group2,
    __out MPI_Group* newgroup
    );

int
MPIAPI
MPI_Group_incl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int* ranks,
    __out MPI_Group* newgroup
    );
int
MPIAPI
PMPI_Group_incl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int* ranks,
    __out MPI_Group* newgroup
    );

int
MPIAPI
MPI_Group_excl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int* ranks,
    __out MPI_Group* newgroup
    );
int
MPIAPI
PMPI_Group_excl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int* ranks,
    __out MPI_Group* newgroup
    );

int
MPIAPI
MPI_Group_range_incl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int ranges[][3],
    __out MPI_Group* newgroup
    );
int
MPIAPI
PMPI_Group_range_incl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int ranges[][3],
    __out MPI_Group* newgroup
    );

int
MPIAPI
MPI_Group_range_excl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int ranges[][3],
    __out MPI_Group* newgroup
    );
int
MPIAPI
PMPI_Group_range_excl(
    __in MPI_Group group,
    __in int n,
    __in_ecount(n) int ranges[][3],
    __out MPI_Group* newgroup
    );

int
MPIAPI
MPI_Group_free(
    __inout MPI_Group* group
    );
int
MPIAPI
PMPI_Group_free(
    __inout MPI_Group* group
    );


/*---------------------------------------------*/
/* Section 6.4: Communicator Management        */
/*---------------------------------------------*/

int
MPIAPI
MPI_Comm_size(
    __in MPI_Comm comm,
    __out int* size
    );
int
MPIAPI
PMPI_Comm_size(
    __in MPI_Comm comm,
    __out int* size
    );

int
MPIAPI
MPI_Comm_rank(
    __in MPI_Comm comm,
    __out int* rank
    );
int
MPIAPI
PMPI_Comm_rank(
    __in MPI_Comm comm,
    __out int* rank
    );

int
MPIAPI
MPI_Comm_compare(
    __in MPI_Comm comm1,
    __in MPI_Comm comm2,
    __out int* result
    );
int
MPIAPI
PMPI_Comm_compare(
    __in MPI_Comm comm1,
    __in MPI_Comm comm2,
    __out int* result
    );

int
MPIAPI
MPI_Comm_dup(
    __in MPI_Comm comm,
    __out MPI_Comm* newcomm
    );
int
MPIAPI
PMPI_Comm_dup(
    __in MPI_Comm comm,
    __out MPI_Comm* newcomm
    );

int
MPIAPI
MPI_Comm_create(
    __in MPI_Comm comm,
    __in MPI_Group group,
    __out MPI_Comm* newcomm
    );
int
MPIAPI
PMPI_Comm_create(
    __in MPI_Comm comm,
    __in MPI_Group group,
    __out MPI_Comm* newcomm
    );

int
MPIAPI
MPI_Comm_split(
    __in MPI_Comm comm,
    __in int color,
    __in int key,
    __out MPI_Comm* newcomm
    );
int
MPIAPI
PMPI_Comm_split(
    __in MPI_Comm comm,
    __in int color,
    __in int key,
    __out MPI_Comm* newcomm
    );

int
MPIAPI
MPI_Comm_free(
    __inout MPI_Comm* comm
    );
int
MPIAPI
PMPI_Comm_free(
    __inout MPI_Comm* comm
    );


/*---------------------------------------------*/
/* Section 6.6: Inter-Communication            */
/*---------------------------------------------*/

int
MPIAPI
MPI_Comm_test_inter(
    __in MPI_Comm comm,
    __out int* flag
    );
int
MPIAPI
PMPI_Comm_test_inter(
    __in MPI_Comm comm,
    __out int* flag
    );

int
MPIAPI
MPI_Comm_remote_size(
    __in MPI_Comm comm,
    __out int* size
    );
int
MPIAPI
PMPI_Comm_remote_size(
    __in MPI_Comm comm,
    __out int* size
    );

int
MPIAPI
MPI_Comm_remote_group(
    __in MPI_Comm comm,
    __out MPI_Group* group
    );
int
MPIAPI
PMPI_Comm_remote_group(
    __in MPI_Comm comm,
    __out MPI_Group* group
    );

int
MPIAPI
MPI_Intercomm_create(
    __in MPI_Comm local_comm,
    __in int local_leader,
    __in MPI_Comm peer_comm,
    __in int remote_leader,
    __in int tag,
    __out MPI_Comm* newintercomm
    );
int
MPIAPI
PMPI_Intercomm_create(
    __in MPI_Comm local_comm,
    __in int local_leader,
    __in MPI_Comm peer_comm,
    __in int remote_leader,
    __in int tag,
    __out MPI_Comm* newintercomm
    );

int
MPIAPI
MPI_Intercomm_merge(
    __in MPI_Comm intercomm,
    __in int high,
    __out MPI_Comm* newintracomm
    );
int
MPIAPI
PMPI_Intercomm_merge(
    __in MPI_Comm intercomm,
    __in int high,
    __out MPI_Comm* newintracomm
    );


/*---------------------------------------------*/
/* Section 6.7: Caching                        */
/*---------------------------------------------*/

#define MPI_KEYVAL_INVALID  0x24000000

typedef
int
(MPIAPI MPI_Comm_copy_attr_function)(
    __in MPI_Comm oldcomm,
    __in int comm_keyval,
    __in_opt void* extra_state,
    __in void* attribute_val_in,
    __out void* attribute_val_out,
    __out int* flag
    );

typedef
int
(MPIAPI MPI_Comm_delete_attr_function)(
    __in MPI_Comm comm,
    __in int comm_keyval,
    __in void* attribute_val,
    __in_opt void* extra_state
    );

#define MPI_COMM_NULL_COPY_FN ((MPI_Comm_copy_attr_function*)0)
#define MPI_COMM_NULL_DELETE_FN ((MPI_Comm_delete_attr_function*)0)
#define MPI_COMM_DUP_FN ((MPI_Comm_copy_attr_function*)MPIR_Dup_fn)

int
MPIAPI
MPI_Comm_create_keyval(
    __in MPI_Comm_copy_attr_function* comm_copy_attr_fn,
    __in MPI_Comm_delete_attr_function* comm_delete_attr_fn,
    __out int* comm_keyval,
    __in_opt void* extra_state
    );
int
MPIAPI
PMPI_Comm_create_keyval(
    __in MPI_Comm_copy_attr_function* comm_copy_attr_fn,
    __in MPI_Comm_delete_attr_function* comm_delete_attr_fn,
    __out int* comm_keyval,
    __in_opt void* extra_state
    );

int
MPIAPI
MPI_Comm_free_keyval(
    __inout int* comm_keyval
    );
int
MPIAPI
PMPI_Comm_free_keyval(
    __inout int* comm_keyval
    );

int
MPIAPI
MPI_Comm_set_attr(
    __in MPI_Comm comm,
    __in int comm_keyval,
    __in void* attribute_val
    );
int
MPIAPI
PMPI_Comm_set_attr(
    __in MPI_Comm comm,
    __in int comm_keyval,
    __in void* attribute_val
    );


/* Predefined comm attribute key values */
/* C Versions (return pointer to value),
   Fortran Versions (return integer value).

   DO NOT CHANGE THESE.  The values encode:
   builtin kind (0x1 in bit 30-31)
   Keyval object (0x9 in bits 26-29)
   for communicator (0x1 in bits 22-25)

   Fortran versions of the attributes are formed by adding one to
   the C version.
 */
#define MPI_TAG_UB          0x64400001
#define MPI_HOST            0x64400003
#define MPI_IO              0x64400005
#define MPI_WTIME_IS_GLOBAL 0x64400007
#define MPI_UNIVERSE_SIZE   0x64400009
#define MPI_LASTUSEDCODE    0x6440000b
#define MPI_APPNUM          0x6440000d

int
MPIAPI
MPI_Comm_get_attr(
    __in MPI_Comm comm,
    __in int comm_keyval,
    __out void* attribute_val,
    __out int* flag
    );
int
MPIAPI
PMPI_Comm_get_attr(
    __in MPI_Comm comm,
    __in int comm_keyval,
    __out void* attribute_val,
    __out int* flag
    );

int
MPIAPI
MPI_Comm_delete_attr(
    __in MPI_Comm comm,
    __in int comm_keyval
    );
int
MPIAPI
PMPI_Comm_delete_attr(
    __in MPI_Comm comm,
    __in int comm_keyval
    );


typedef
int
(MPIAPI MPI_Win_copy_attr_function)(
    __in MPI_Win oldwin,
    __in int win_keyval,
    __in_opt void* extra_state,
    __in void* attribute_val_in,
    __out void* attribute_val_out,
    __out int* flag
    );

typedef
int
(MPIAPI MPI_Win_delete_attr_function)(
    __in MPI_Win win,
    __in int win_keyval,
    __in void* attribute_val,
    __in_opt void* extra_state
    );

#define MPI_WIN_NULL_COPY_FN ((MPI_Win_copy_attr_function*)0)
#define MPI_WIN_NULL_DELETE_FN ((MPI_Win_delete_attr_function*)0)
#define MPI_WIN_DUP_FN ((MPI_Win_copy_attr_function*)MPIR_Dup_fn)

int
MPIAPI
MPI_Win_create_keyval(
    __in MPI_Win_copy_attr_function* win_copy_attr_fn,
    __in MPI_Win_delete_attr_function* win_delete_attr_fn,
    __out int* win_keyval,
    __in_opt void* extra_state
    );
int
MPIAPI
PMPI_Win_create_keyval(
    __in MPI_Win_copy_attr_function* win_copy_attr_fn,
    __in MPI_Win_delete_attr_function* win_delete_attr_fn,
    __out int* win_keyval,
    __in_opt void* extra_state
    );

int
MPIAPI
MPI_Win_free_keyval(
    __inout int* win_keyval
    );
int
MPIAPI
PMPI_Win_free_keyval(
    __inout int* win_keyval
    );

int
MPIAPI
MPI_Win_set_attr(
    __in MPI_Win win,
    __in int win_keyval,
    __in void* attribute_val
    );
int
MPIAPI
PMPI_Win_set_attr(
    __in MPI_Win win,
    __in int win_keyval,
    __in void* attribute_val
    );


/* Predefined window key value attributes */
#define MPI_WIN_BASE        0x66000001
#define MPI_WIN_SIZE        0x66000003
#define MPI_WIN_DISP_UNIT   0x66000005

int
MPIAPI
MPI_Win_get_attr(
    __in MPI_Win win,
    __in int win_keyval,
    __out void* attribute_val,
    __out int* flag
    );
int
MPIAPI
PMPI_Win_get_attr(
    __in MPI_Win win,
    __in int win_keyval,
    __out void* attribute_val,
    __out int* flag
    );

int
MPIAPI
MPI_Win_delete_attr(
    __in MPI_Win win,
    __in int win_keyval
    );
int
MPIAPI
PMPI_Win_delete_attr(
    __in MPI_Win win,
    __in int win_keyval
    );


typedef
int
(MPIAPI MPI_Type_copy_attr_function)(
    __in MPI_Datatype olddatatype,
    __in int datatype_keyval,
    __in_opt void* extra_state,
    __in void* attribute_val_in,
    __out void* attribute_val_out,
    __out int* flag
    );

typedef
int
(MPIAPI MPI_Type_delete_attr_function)(
    __in MPI_Datatype datatype,
    __in int datatype_keyval,
    __in void* attribute_val,
    __in_opt void* extra_state
    );

#define MPI_TYPE_NULL_COPY_FN ((MPI_Type_copy_attr_function*)0)
#define MPI_TYPE_NULL_DELETE_FN ((MPI_Type_delete_attr_function*)0)
#define MPI_TYPE_DUP_FN ((MPI_Type_copy_attr_function*)MPIR_Dup_fn)

int
MPIAPI
MPI_Type_create_keyval(
    __in MPI_Type_copy_attr_function* type_copy_attr_fn,
    __in MPI_Type_delete_attr_function* type_delete_attr_fn,
    __out int* type_keyval,
    __in_opt void* extra_state
    );
int
MPIAPI
PMPI_Type_create_keyval(
    __in MPI_Type_copy_attr_function* type_copy_attr_fn,
    __in MPI_Type_delete_attr_function* type_delete_attr_fn,
    __out int* type_keyval,
    __in_opt void* extra_state
    );

int
MPIAPI
MPI_Type_free_keyval(
    __inout int* type_keyval
    );
int
MPIAPI
PMPI_Type_free_keyval(
    __inout int* type_keyval
    );

int
MPIAPI
MPI_Type_set_attr(
    __in MPI_Datatype type,
    __in int type_keyval,
    __in void* attribute_val
    );
int
MPIAPI
PMPI_Type_set_attr(
    __in MPI_Datatype type,
    __in int type_keyval,
    __in void* attribute_val
    );

int
MPIAPI
MPI_Type_get_attr(
    __in MPI_Datatype type,
    __in int type_keyval,
    __out void* attribute_val,
    __out int* flag
    );
int
MPIAPI
PMPI_Type_get_attr(
    __in MPI_Datatype type,
    __in int type_keyval,
    __out void* attribute_val,
    __out int* flag
    );

int
MPIAPI
MPI_Type_delete_attr(
    __in MPI_Datatype datatype,
    __in int type_keyval
    );
int
MPIAPI
PMPI_Type_delete_attr(
    __in MPI_Datatype datatype,
    __in int type_keyval
    );


/*---------------------------------------------*/
/* Section 6.8: Naming Objects                 */
/*---------------------------------------------*/

#define MPI_MAX_OBJECT_NAME 128

int
MPIAPI
MPI_Comm_set_name(
    __in MPI_Comm comm,
    __in_z char* comm_name
    );
int
MPIAPI
PMPI_Comm_set_name(
    __in MPI_Comm comm,
    __in_z char* comm_name
    );

int
MPIAPI
MPI_Comm_get_name(
    __in MPI_Comm comm,
    __out_ecount_part_z(MPI_MAX_OBJECT_NAME,*resultlen) char* comm_name,
    __out int* resultlen
    );
int
MPIAPI
PMPI_Comm_get_name(
    __in MPI_Comm comm,
    __out_ecount_part_z(MPI_MAX_OBJECT_NAME,*resultlen) char* comm_name,
    __out int* resultlen
    );

int
MPIAPI
MPI_Type_set_name(
    __in MPI_Datatype type,
    __in_z char* type_name
    );
int
MPIAPI
PMPI_Type_set_name(
    __in MPI_Datatype type,
    __in_z char* type_name
    );

int
MPIAPI
MPI_Type_get_name(
    __in MPI_Datatype type,
    __out_ecount_part_z(MPI_MAX_OBJECT_NAME,*resultlen) char* type_name,
    __out int* resultlen
    );
int
MPIAPI
PMPI_Type_get_name(
    __in MPI_Datatype type,
    __out_ecount_part_z(MPI_MAX_OBJECT_NAME,*resultlen) char* type_name,
    __out int* resultlen
    );

int
MPIAPI
MPI_Win_set_name(
    __in MPI_Win win,
    __in_z char* win_name
    );
int
MPIAPI
PMPI_Win_set_name(
    __in MPI_Win win,
    __in_z char* win_name
    );

int
MPIAPI
MPI_Win_get_name(
    __in MPI_Win win,
    __out_ecount_part_z(MPI_MAX_OBJECT_NAME,*resultlen) char* win_name,
    __out int* resultlen
    );
int
MPIAPI
PMPI_Win_get_name(
    __in MPI_Win win,
    __out_ecount_part_z(MPI_MAX_OBJECT_NAME,*resultlen) char* win_name,
    __out int* resultlen
    );


/*---------------------------------------------------------------------------*/
/* Chapter 7: Process Topologies                                             */
/*---------------------------------------------------------------------------*/

int
MPIAPI
MPI_Cart_create(
    __in MPI_Comm comm_old,
    __in int ndims,
    __in_ecount(ndims) int* dims,
    __in_ecount(ndims) int* periods,
    __in int reorder,
    __out MPI_Comm* comm_cart
    );
int
MPIAPI
PMPI_Cart_create(
    __in MPI_Comm comm_old,
    __in int ndims,
    __in_ecount(ndims) int* dims,
    __in_ecount(ndims) int* periods,
    __in int reorder,
    __out MPI_Comm* comm_cart
    );

int
MPIAPI
MPI_Dims_create(
    __in int nnodes,
    __in int ndims,
    __inout_ecount(ndims) int* dims
    );
int
MPIAPI
PMPI_Dims_create(
    __in int nnodes,
    __in int ndims,
    __inout_ecount(ndims) int* dims
    );

int
MPIAPI
MPI_Graph_create(
    __in MPI_Comm comm_old,
    __in int nnodes,
    __in_ecount(nnodes) int* index,
    __in int* edges,
    __in int reorder,
    __out MPI_Comm* comm_cart
    );
int
MPIAPI
PMPI_Graph_create(
    __in MPI_Comm comm_old,
    __in int nnodes,
    __in_ecount(nnodes) int* index,
    __in int* edges,
    __in int reorder,
    __out MPI_Comm* comm_cart
    );


/* Topology types */
enum
{
    MPI_GRAPH = 1,
    MPI_CART = 2
};

int
MPIAPI
MPI_Topo_test(
    __in MPI_Comm comm,
    __out int* status
    );
int
MPIAPI
PMPI_Topo_test(
    __in MPI_Comm comm,
    __out int* status
    );

int
MPIAPI
MPI_Graphdims_get(
    __in MPI_Comm comm,
    __out int* nnodes,
    __out int* nedges
    );
int
MPIAPI
PMPI_Graphdims_get(
    __in MPI_Comm comm,
    __out int* nnodes,
    __out int* nedges
    );

int
MPIAPI
MPI_Graph_get(
    __in MPI_Comm comm,
    __in int maxindex,
    __in int maxedges,
    __out_ecount(maxindex) int* index,
    __out_ecount(maxedges) int* edges
    );
int
MPIAPI
PMPI_Graph_get(
    __in MPI_Comm comm,
    __in int maxindex,
    __in int maxedges,
    __out_ecount(maxindex) int* index,
    __out_ecount(maxedges) int* edges
    );

int
MPIAPI
MPI_Cartdim_get(
    __in MPI_Comm comm,
    __out int* ndims
    );
int
MPIAPI
PMPI_Cartdim_get(
    __in MPI_Comm comm,
    __out int* ndims
    );

int
MPIAPI
MPI_Cart_get(
    __in MPI_Comm comm,
    __in int maxdims,
    __out_ecount(maxdims) int* dims,
    __out_ecount(maxdims) int* periods,
    __out_ecount(maxdims) int* coords
    );
int
MPIAPI
PMPI_Cart_get(
    __in MPI_Comm comm,
    __in int maxdims,
    __out_ecount(maxdims) int* dims,
    __out_ecount(maxdims) int* periods,
    __out_ecount(maxdims) int* coords
    );

int
MPIAPI
MPI_Cart_rank(
    __in MPI_Comm comm,
    __in int* coords,
    __out int* rank
    );
int
MPIAPI
PMPI_Cart_rank(
    __in MPI_Comm comm,
    __in int* coords,
    __out int* rank
    );

int
MPIAPI
MPI_Cart_coords(
    __in MPI_Comm comm,
    __in int rank,
    __in int maxdims,
    __out_ecount(maxdims) int* coords
    );
int
MPIAPI
PMPI_Cart_coords(
    __in MPI_Comm comm,
    __in int rank,
    __in int maxdims,
    __out_ecount(maxdims) int* coords
    );

int
MPIAPI
MPI_Graph_neighbors_count(
    __in MPI_Comm comm,
    __in int rank,
    __out int* nneighbors
    );
int
MPIAPI
PMPI_Graph_neighbors_count(
    __in MPI_Comm comm,
    __in int rank,
    __out int* nneighbors
    );

int
MPIAPI
MPI_Graph_neighbors(
    __in MPI_Comm comm,
    __in int rank,
    __in int maxneighbors,
    __out_ecount(maxneighbors) int* neighbors
    );
int
MPIAPI
PMPI_Graph_neighbors(
    __in MPI_Comm comm,
    __in int rank,
    __in int maxneighbors,
    __out_ecount(maxneighbors) int* neighbors
    );

int
MPIAPI
MPI_Cart_shift(
    __in MPI_Comm comm,
    __in int direction,
    __in int disp,
    __out int* rank_source,
    __out int* rank_dest
    );
int
MPIAPI
PMPI_Cart_shift(
    __in MPI_Comm comm,
    __in int direction,
    __in int disp,
    __out int* rank_source,
    __out int* rank_dest
    );

int
MPIAPI
MPI_Cart_sub(
    __in MPI_Comm comm,
    __in int* remain_dims,
    __out MPI_Comm* newcomm
    );
int
MPIAPI
PMPI_Cart_sub(
    __in MPI_Comm comm,
    __in int* remain_dims,
    __out MPI_Comm* newcomm
    );

int
MPIAPI
MPI_Cart_map(
    __in MPI_Comm comm,
    __in int ndims,
    __in_ecount(ndims) int* dims,
    __in_ecount(ndims) int* periods,
    __out int* newrank
    );
int
MPIAPI
PMPI_Cart_map(
    __in MPI_Comm comm,
    __in int ndims,
    __in_ecount(ndims) int* dims,
    __in_ecount(ndims) int* periods,
    __out int* newrank
    );

int
MPIAPI
MPI_Graph_map(
    __in MPI_Comm comm,
    __in int nnodes,
    __in_ecount(nnodes) int* index,
    __in int* edges,
    __out int* newrank
    );
int
MPIAPI
PMPI_Graph_map(
    __in MPI_Comm comm,
    __in int nnodes,
    __in_ecount(nnodes) int* index,
    __in int* edges,
    __out int* newrank
    );


/*---------------------------------------------------------------------------*/
/* Chapter 8: Environmental Management                                       */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 8.1: Implementation Information     */
/*---------------------------------------------*/

#define MPI_VERSION     2
#define MPI_SUBVERSION  0

int
MPIAPI
MPI_Get_version(
    __out int* version,
    __out int* subversion
    );
int
MPIAPI
PMPI_Get_version(
    __out int* version,
    __out int* subversion
    );

#define MPI_MAX_PROCESSOR_NAME  128

int
MPIAPI
MPI_Get_processor_name(
    __out_ecount_part_z(MPI_MAX_PROCESSOR_NAME,*resultlen) char* name,
    __out int* resultlen
    );
int
MPIAPI
PMPI_Get_processor_name(
    __out_ecount_part_z(MPI_MAX_PROCESSOR_NAME,*resultlen) char* name,
    __out int* resultlen
    );

/*---------------------------------------------*/
/* Section 8.2: Memory Allocation              */
/*---------------------------------------------*/

int
MPIAPI
MPI_Alloc_mem(
    __in MPI_Aint size,
    __in MPI_Info info,
    __out void* baseptr
    );
int
MPIAPI
PMPI_Alloc_mem(
    __in MPI_Aint size,
    __in MPI_Info info,
    __out void* baseptr
    );

int
MPIAPI
MPI_Free_mem(
    __in void* base
    );
int
MPIAPI
PMPI_Free_mem(
    __in void* base
    );


/*---------------------------------------------*/
/* Section 8.3: Error Handling                 */
/*---------------------------------------------*/

typedef
void
(MPIAPI MPI_Comm_errhandler_fn)(
    __in MPI_Comm* comm,
    __inout int* errcode,
    ...
    );

int
MPIAPI
MPI_Comm_create_errhandler(
    __in MPI_Comm_errhandler_fn* function,
    __out MPI_Errhandler* errhandler
    );
int
MPIAPI
PMPI_Comm_create_errhandler(
    __in MPI_Comm_errhandler_fn* function,
    __out MPI_Errhandler* errhandler
    );

int
MPIAPI
MPI_Comm_set_errhandler(
    __in MPI_Comm comm,
    __in MPI_Errhandler errhandler
    );
int
MPIAPI
PMPI_Comm_set_errhandler(
    __in MPI_Comm comm,
    __in MPI_Errhandler errhandler
    );

int
MPIAPI
MPI_Comm_get_errhandler(
    __in MPI_Comm comm,
    __out MPI_Errhandler* errhandler
    );
int
MPIAPI
PMPI_Comm_get_errhandler(
    __in MPI_Comm comm,
    __out MPI_Errhandler* errhandler
    );


typedef
void
(MPIAPI MPI_Win_errhandler_fn)(
    __in MPI_Win* win,
    __inout int* errcode,
    ...
    );

int
MPIAPI
MPI_Win_create_errhandler(
    __in MPI_Win_errhandler_fn* function,
    __out MPI_Errhandler* errhandler
    );
int
MPIAPI
PMPI_Win_create_errhandler(
    __in MPI_Win_errhandler_fn* function,
    __out MPI_Errhandler* errhandler
    );

int
MPIAPI
MPI_Win_set_errhandler(
    __in MPI_Win win,
    __in MPI_Errhandler errhandler
    );
int
MPIAPI
PMPI_Win_set_errhandler(
    __in MPI_Win win,
    __in MPI_Errhandler errhandler
    );

int
MPIAPI
MPI_Win_get_errhandler(
    __in MPI_Win win,
    __out MPI_Errhandler* errhandler
    );
int
MPIAPI
PMPI_Win_get_errhandler(
    __in MPI_Win win,
    __out MPI_Errhandler* errhandler
    );


typedef
void
(MPIAPI MPI_File_errhandler_fn)(
    __in MPI_File* file,
    __inout int* errcode,
    ...
    );

int
MPIAPI
MPI_File_create_errhandler(
    __in MPI_File_errhandler_fn* function,
    __out MPI_Errhandler* errhandler
    );
int
MPIAPI
PMPI_File_create_errhandler(
    __in MPI_File_errhandler_fn* function,
    __out MPI_Errhandler* errhandler
    );

int
MPIAPI
MPI_File_set_errhandler(
    __in MPI_File file,
    __in MPI_Errhandler errhandler
    );
int
MPIAPI
PMPI_File_set_errhandler(
    __in MPI_File file,
    __in MPI_Errhandler errhandler
    );

int
MPIAPI
MPI_File_get_errhandler(
    __in MPI_File file,
    __out MPI_Errhandler* errhandler
    );
int
MPIAPI
PMPI_File_get_errhandler(
    __in MPI_File file,
    __out MPI_Errhandler* errhandler
    );

int
MPIAPI
MPI_Errhandler_free(
    __inout MPI_Errhandler* errhandler
    );
int
MPIAPI
PMPI_Errhandler_free(
    __inout MPI_Errhandler* errhandler
    );

#define MPI_MAX_ERROR_STRING    512

int
MPIAPI
MPI_Error_string(
    __in int errorcode,
    __out_ecount_part_z(MPI_MAX_ERROR_STRING,*resultlen) char* string,
    __out int* resultlen
    );
int
MPIAPI
PMPI_Error_string(
    __in int errorcode,
    __out_ecount_part_z(MPI_MAX_ERROR_STRING,*resultlen) char* string,
    __out int* resultlen
    );


/*---------------------------------------------*/
/* Section 8.4: Error Codes and Classes        */
/*---------------------------------------------*/

int
MPIAPI
MPI_Error_class(
    __in int errorcode,
    __out int* errorclass
    );
int
MPIAPI
PMPI_Error_class(
    __in int errorcode,
    __out int* errorclass
    );

int
MPIAPI
MPI_Add_error_class(
    __out int* errorclass
    );
int
MPIAPI
PMPI_Add_error_class(
    __out int* errorclass
    );

int
MPIAPI
MPI_Add_error_code(
    __in int errorclass,
    __out int* errorcode
    );
int
MPIAPI
PMPI_Add_error_code(
    __in int errorclass,
    __out int* errorcode
    );

int
MPIAPI
MPI_Add_error_string(
    __in int errorcode,
    __in_z char* string
    );
int
MPIAPI
PMPI_Add_error_string(
    __in int errorcode,
    __in_z char* string
    );

int
MPIAPI
MPI_Comm_call_errhandler(
    __in MPI_Comm comm,
    __in int errorcode
    );
int
MPIAPI
PMPI_Comm_call_errhandler(
    __in MPI_Comm comm,
    __in int errorcode
    );

int
MPIAPI
MPI_Win_call_errhandler(
    __in MPI_Win win,
    __in int errcode
    );
int
MPIAPI
PMPI_Win_call_errhandler(
    __in MPI_Win win,
    __in int errcode
    );

int
MPIAPI
MPI_File_call_errhandler(
    __in MPI_File file,
    __in int errorcode
    );
int
MPIAPI
PMPI_File_call_errhandler(
    __in MPI_File file,
    __in int errorcode
    );


/*---------------------------------------------*/
/* Section 8.6: Timers and Synchronization     */
/*---------------------------------------------*/

double
MPIAPI
MPI_Wtime(
    void
    );
double
MPIAPI
PMPI_Wtime(
    void
    );

double
MPIAPI
MPI_Wtick(
    void
    );
double
MPIAPI
PMPI_Wtick(
    void
    );


/*---------------------------------------------*/
/* Section 8.7: Startup                        */
/*---------------------------------------------*/

int
MPIAPI
MPI_Init(
    __in_opt int* argc,
    __deref_ecount_opt(*argc) char*** argv
    );
int
MPIAPI
PMPI_Init(
    __in_opt int* argc,
    __deref_ecount_opt(*argc) char*** argv
    );

int
MPIAPI
MPI_Finalize(
    void
    );
int
MPIAPI
PMPI_Finalize(
    void
    );

int
MPIAPI
MPI_Initialized(
    __out int* flag
    );
int
MPIAPI
PMPI_Initialized(
    __out int* flag
    );

int
MPIAPI
MPI_Abort(
    __in MPI_Comm comm,
    __in int errorcode
    );
int
MPIAPI
PMPI_Abort(
    __in MPI_Comm comm,
    __in int errorcode
    );

int
MPIAPI
MPI_Finalized(
    __out int* flag
    );
int
MPIAPI
PMPI_Finalized(
    __out int* flag
    );


/*---------------------------------------------------------------------------*/
/* Chapter 9: The Info Object                                                */
/*---------------------------------------------------------------------------*/

#define MPI_MAX_INFO_KEY    255
#define MPI_MAX_INFO_VAL   1024

int
MPIAPI
MPI_Info_create(
    __out MPI_Info* info
    );
int
MPIAPI
PMPI_Info_create(
    __out MPI_Info* info
    );

int
MPIAPI
MPI_Info_set(
    __in MPI_Info info,
    __in_z char* key,
    __in_z char* value
    );
int
MPIAPI
PMPI_Info_set(
    __in MPI_Info info,
    __in_z char* key,
    __in_z char* value
    );

int
MPIAPI
MPI_Info_delete(
    __in MPI_Info info,
    __in_z char* key
    );
int
MPIAPI
PMPI_Info_delete(
    __in MPI_Info info,
    __in_z char* key
    );

int
MPIAPI
MPI_Info_get(
    __in MPI_Info info,
    __in_z char* key,
    __in int valuelen,
    __out_ecount_z(valuelen) char* value,
    __out int* flag
    );
int
MPIAPI
PMPI_Info_get(
    __in MPI_Info info,
    __in_z char* key,
    __in int valuelen,
    __out_ecount_z(valuelen) char* value,
    __out int* flag
    );

int
MPIAPI
MPI_Info_get_valuelen(
    __in MPI_Info info,
    __in_z char* key,
    __out int* valuelen,
    __out int* flag
    );
int
MPIAPI
PMPI_Info_get_valuelen(
    __in MPI_Info info,
    __in_z char* key,
    __out int* valuelen,
    __out int* flag
    );

int
MPIAPI
MPI_Info_get_nkeys(
    __in MPI_Info info,
    __out int* nkeys
    );
int
MPIAPI
PMPI_Info_get_nkeys(
    __in MPI_Info info,
    __out int* nkeys
    );

int
MPIAPI
MPI_Info_get_nthkey(
    __in MPI_Info info,
    __in int n,
    __out_z char* key
    );
int
MPIAPI
PMPI_Info_get_nthkey(
    __in MPI_Info info,
    __in int n,
    __out_z char* key
    );

int
MPIAPI
MPI_Info_dup(
    __in MPI_Info info,
    __out MPI_Info* newinfo
    );
int
MPIAPI
PMPI_Info_dup(
    __in MPI_Info info,
    __out MPI_Info* newinfo
    );

int
MPIAPI
MPI_Info_free(
    __inout MPI_Info* info
    );
int
MPIAPI
PMPI_Info_free(
    __inout MPI_Info* info
    );


/*---------------------------------------------------------------------------*/
/* Chapter 10: Process Creation and Management                               */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 10.3: Process Manager Inerface      */
/*---------------------------------------------*/

#define MPI_ARGV_NULL ((char**)0)
#define MPI_ARGVS_NULL ((char***)0)

#define MPI_ERRCODES_IGNORE ((int*)0)

int
MPIAPI
MPI_Comm_spawn(
    __in_z char* command,
    __in char* argv[],
    __in int maxprocs,
    __in MPI_Info info,
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* intercomm,
    __out_ecount(maxprocs) int array_of_errcodes[]
    );
int
MPIAPI
PMPI_Comm_spawn(
    __in_z char* command,
    __in char* argv[],
    __in int maxprocs,
    __in MPI_Info info,
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* intercomm,
    __out_ecount(maxprocs) int array_of_errcodes[]
    );

int
MPIAPI
MPI_Comm_get_parent(
    __out MPI_Comm* parent
    );
int
MPIAPI
PMPI_Comm_get_parent(
    __out MPI_Comm* parent
    );

int
MPIAPI
MPI_Comm_spawn_multiple(
    __in int count,
    __in_ecount(count) char* array_of_commands[],
    __in_ecount(count) char** array_of_argv[],
    __in_ecount(count) int array_of_maxprocs[],
    __in_ecount(count) MPI_Info array_of_info[],
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* intercomm,
    __out int array_of_errcodes[]
    );
int
MPIAPI
PMPI_Comm_spawn_multiple(
    __in int count,
    __in_ecount(count) char* array_of_commands[],
    __in_ecount(count) char** array_of_argv[],
    __in_ecount(count) int array_of_maxprocs[],
    __in_ecount(count) MPI_Info array_of_info[],
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* intercomm,
    __out int array_of_errcodes[]
    );


/*---------------------------------------------*/
/* Section 10.4: Establishing Communication    */
/*---------------------------------------------*/

#define MPI_MAX_PORT_NAME   256

int
MPIAPI
MPI_Open_port(
    __in MPI_Info info,
    __out_ecount(MPI_MAX_PORT_NAME) char* port_name
    );
int
MPIAPI
PMPI_Open_port(
    __in MPI_Info info,
    __out_ecount(MPI_MAX_PORT_NAME) char* port_name
    );

int
MPIAPI
MPI_Close_port(
    __in_z char* port_name
    );
int
MPIAPI
PMPI_Close_port(
    __in_z char* port_name
    );

int
MPIAPI
MPI_Comm_accept(
    __in_z char* port_name,
    __in MPI_Info info,
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* newcomm
    );
int
MPIAPI
PMPI_Comm_accept(
    __in_z char* port_name,
    __in MPI_Info info,
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* newcomm
    );

int
MPIAPI
MPI_Comm_connect(
    __in_z char* port_name,
    __in MPI_Info info,
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* newcomm
    );
int
MPIAPI
PMPI_Comm_connect(
    __in_z char* port_name,
    __in MPI_Info info,
    __in int root,
    __in MPI_Comm comm,
    __out MPI_Comm* newcomm
    );


/*---------------------------------------------*/
/* Section 10.4.4: Name Publishing             */
/*---------------------------------------------*/

int
MPIAPI
MPI_Publish_name(
    __in_z char* service_name,
    __in MPI_Info info,
    __in_z char* port_name
    );
int
MPIAPI
PMPI_Publish_name(
    __in_z char* service_name,
    __in MPI_Info info,
    __in_z char* port_name
    );

int
MPIAPI
MPI_Unpublish_name(
    __in_z char* service_name,
    __in MPI_Info info,
    __in_z char* port_name
    );
int
MPIAPI
PMPI_Unpublish_name(
    __in_z char* service_name,
    __in MPI_Info info,
    __in_z char* port_name
    );

int
MPIAPI
MPI_Lookup_name(
    __in_z char* service_name,
    __in MPI_Info info,
    __out_ecount(MPI_MAX_PORT_NAME) char* port_name
    );
int
MPIAPI
PMPI_Lookup_name(
    __in_z char* service_name,
    __in MPI_Info info,
    __out_ecount(MPI_MAX_PORT_NAME) char* port_name
    );


/*---------------------------------------------*/
/* Section 10.5: Other Functionality           */
/*---------------------------------------------*/

int
MPIAPI
MPI_Comm_disconnect(
    __in MPI_Comm* comm
    );
int
MPIAPI
PMPI_Comm_disconnect(
    __in MPI_Comm* comm
    );

int
MPIAPI
MPI_Comm_join(
    __in int fd,
    __out MPI_Comm* intercomm
    );
int
MPIAPI
PMPI_Comm_join(
    __in int fd,
    __out MPI_Comm* intercomm
    );


/*---------------------------------------------------------------------------*/
/* Chapter 11: One-Sided Communications                                      */
/*---------------------------------------------------------------------------*/

int
MPIAPI
MPI_Win_create(
    __in void* base,
    __in MPI_Aint size,
    __in int disp_unit,
    __in MPI_Info info,
    __in MPI_Comm comm,
    __out MPI_Win* win
    );
int
MPIAPI
PMPI_Win_create(
    __in void* base,
    __in MPI_Aint size,
    __in int disp_unit,
    __in MPI_Info info,
    __in MPI_Comm comm,
    __out MPI_Win* win
    );

int
MPIAPI
MPI_Win_free(
    __inout MPI_Win* win
    );
int
MPIAPI
PMPI_Win_free(
    __inout MPI_Win* win
    );

int
MPIAPI
MPI_Win_get_group(
    __in MPI_Win win,
    __out MPI_Group* group
    );
int
MPIAPI
PMPI_Win_get_group(
    __in MPI_Win win,
    __out MPI_Group* group
    );

int
MPIAPI
MPI_Put(
    __in void* origin_addr,
    __in int origin_count,
    __in MPI_Datatype origin_datatype,
    __in int target_rank,
    __in MPI_Aint target_disp,
    __in int target_count,
    __in MPI_Datatype datatype,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Put(
    __in void* origin_addr,
    __in int origin_count,
    __in MPI_Datatype origin_datatype,
    __in int target_rank,
    __in MPI_Aint target_disp,
    __in int target_count,
    __in MPI_Datatype datatype,
    __in MPI_Win win
    );

int
MPIAPI
MPI_Get(
    __out void* origin_addr,
    __in int origin_count,
    __in MPI_Datatype origin_datatype,
    __in int target_rank,
    __in MPI_Aint target_disp,
    __in int target_count,
    __in MPI_Datatype datatype,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Get(
    __out void* origin_addr,
    __in int origin_count,
    __in MPI_Datatype origin_datatype,
    __in int target_rank,
    __in MPI_Aint target_disp,
    __in int target_count,
    __in MPI_Datatype datatype,
    __in MPI_Win win
    );

int
MPIAPI
MPI_Accumulate(
    __in void* origin_addr,
    __in int origin_count,
    __in MPI_Datatype origin_datatype,
    __in int target_rank,
    __in MPI_Aint target_disp,
    __in int target_count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Accumulate(
    __in void* origin_addr,
    __in int origin_count,
    __in MPI_Datatype origin_datatype,
    __in int target_rank,
    __in MPI_Aint target_disp,
    __in int target_count,
    __in MPI_Datatype datatype,
    __in MPI_Op op,
    __in MPI_Win win
    );

/* Asserts for one-sided communication */
#define MPI_MODE_NOCHECK    1024
#define MPI_MODE_NOSTORE    2048
#define MPI_MODE_NOPUT      4096
#define MPI_MODE_NOPRECEDE  8192
#define MPI_MODE_NOSUCCEED 16384

int
MPIAPI
MPI_Win_fence(
    __in int assert,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Win_fence(
    __in int assert,
    __in MPI_Win win
    );

int
MPIAPI
MPI_Win_start(
    __in MPI_Group group,
    __in int assert,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Win_start(
    __in MPI_Group group,
    __in int assert,
    __in MPI_Win win
    );

int
MPIAPI
MPI_Win_complete(
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Win_complete(
    __in MPI_Win win
    );

int
MPIAPI
MPI_Win_post(
    __in MPI_Group group,
    __in int assert,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Win_post(
    __in MPI_Group group,
    __in int assert,
    __in MPI_Win win
    );

int
MPIAPI
MPI_Win_wait(
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Win_wait(
    __in MPI_Win win
    );

int
MPIAPI
MPI_Win_test(
    __in MPI_Win win,
    __out int* flag
    );
int
MPIAPI
PMPI_Win_test(
    __in MPI_Win win,
    __out int* flag
    );

#define MPI_LOCK_EXCLUSIVE  234
#define MPI_LOCK_SHARED     235

int
MPIAPI
MPI_Win_lock(
    __in int lock_type,
    __in int rank,
    __in int assert,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Win_lock(
    __in int lock_type,
    __in int rank,
    __in int assert,
    __in MPI_Win win
    );

int
MPIAPI
MPI_Win_unlock(
    __in int rank,
    __in MPI_Win win
    );
int
MPIAPI
PMPI_Win_unlock(
    __in int rank,
    __in MPI_Win win
    );


/*---------------------------------------------------------------------------*/
/* Chapter 12: External Interfaces                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 12.2: Generalized Requests          */
/*---------------------------------------------*/

typedef
int
(MPIAPI MPI_Grequest_query_function)(
    __in_opt void* extra_state,
    __out MPI_Status* status
    );

typedef
int
(MPIAPI MPI_Grequest_free_function)(
    __in_opt void* extra_state
    );

typedef
int
(MPIAPI MPI_Grequest_cancel_function)(
    __in_opt void* extra_state,
    __in int complete
    );

int
MPIAPI
MPI_Grequest_start(
    __in MPI_Grequest_query_function* query_fn,
    __in MPI_Grequest_free_function* free_fn,
    __in MPI_Grequest_cancel_function* cancel_fn,
    __in_opt void* extra_state,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_Grequest_start(
    __in MPI_Grequest_query_function* query_fn,
    __in MPI_Grequest_free_function* free_fn,
    __in MPI_Grequest_cancel_function* cancel_fn,
    __in_opt void* extra_state,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_Grequest_complete(
    __in MPI_Request request
    );
int
MPIAPI
PMPI_Grequest_complete(
    __in MPI_Request request
    );


/*---------------------------------------------*/
/* Section 12.3: Information with Status       */
/*---------------------------------------------*/

int
MPIAPI
MPI_Status_set_elements(
    __in MPI_Status* status,
    __in MPI_Datatype datatype,
    __in int count
    );
int
MPIAPI
PMPI_Status_set_elements(
    __in MPI_Status* status,
    __in MPI_Datatype datatype,
    __in int count
    );

int
MPIAPI
MPI_Status_set_cancelled(
    __in MPI_Status* status,
    __in int flag
    );
int
MPIAPI
PMPI_Status_set_cancelled(
    __in MPI_Status* status,
    __in int flag
    );


/*---------------------------------------------*/
/* Section 12.4: Threads                       */
/*---------------------------------------------*/

#define MPI_THREAD_SINGLE       0
#define MPI_THREAD_FUNNELED     1
#define MPI_THREAD_SERIALIZED   2
#define MPI_THREAD_MULTIPLE     3

int
MPIAPI
MPI_Init_thread(
    __in_opt int* argc,
    __deref_ecount_opt(*argc) __exceptthat __maybenull char*** argv,
    __in int required,
    __out int* provided
    );
int
MPIAPI
PMPI_Init_thread(
    __in_opt int* argc,
    __deref_ecount_opt(*argc) __exceptthat __maybenull char*** argv,
    __in int required,
    __out int* provided
    );

int
MPIAPI
MPI_Query_thread(
    __out int* provided
    );
int
MPIAPI
PMPI_Query_thread(
    __out int* provided
    );

int
MPIAPI
MPI_Is_thread_main(
    __out int* flag
    );
int
MPIAPI
PMPI_Is_thread_main(
    __out int* flag
    );


/*---------------------------------------------------------------------------*/
/* Chapter 13: I/O                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 13.2: File Manipulation             */
/*---------------------------------------------*/

#define MPI_MODE_CREATE              1
#define MPI_MODE_RDONLY              2
#define MPI_MODE_WRONLY              4
#define MPI_MODE_RDWR                8
#define MPI_MODE_DELETE_ON_CLOSE    16
#define MPI_MODE_UNIQUE_OPEN        32
#define MPI_MODE_EXCL               64
#define MPI_MODE_APPEND            128
#define MPI_MODE_SEQUENTIAL        256

int
MPIAPI
MPI_File_open(
    __in MPI_Comm comm,
    __in_z char* filename,
    __in int amode,
    __in MPI_Info info,
    __out MPI_File* newfile
    );
int
MPIAPI
PMPI_File_open(
    __in MPI_Comm comm,
    __in_z char* filename,
    __in int amode,
    __in MPI_Info info,
    __out MPI_File* newfile
    );

int
MPIAPI
MPI_File_close(
    __in MPI_File* file
    );
int
MPIAPI
PMPI_File_close(
    __in MPI_File* file
    );

int
MPIAPI
MPI_File_delete(
    __in_z char* filename,
    __in MPI_Info info
    );
int
MPIAPI
PMPI_File_delete(
    __in_z char* filename,
    __in MPI_Info info
    );

int
MPIAPI
MPI_File_set_size(
    __in MPI_File file,
    __in MPI_Offset size
    );
int
MPIAPI
PMPI_File_set_size(
    __in MPI_File file,
    __in MPI_Offset size
    );

int
MPIAPI
MPI_File_preallocate(
    __in MPI_File file,
    __in MPI_Offset size
    );
int
MPIAPI
PMPI_File_preallocate(
    __in MPI_File file,
    __in MPI_Offset size
    );

int
MPIAPI
MPI_File_get_size(
    __in MPI_File file,
    __out MPI_Offset* size
    );
int
MPIAPI
PMPI_File_get_size(
    __in MPI_File file,
    __out MPI_Offset* size
    );

int
MPIAPI
MPI_File_get_group(
    __in MPI_File file,
    __out MPI_Group* group
    );
int
MPIAPI
PMPI_File_get_group(
    __in MPI_File file,
    __out MPI_Group* group
    );

int
MPIAPI
MPI_File_get_amode(
    __in MPI_File file,
    __out int* amode
    );
int
MPIAPI
PMPI_File_get_amode(
    __in MPI_File file,
    __out int* amode
    );

int
MPIAPI
MPI_File_set_info(
    __in MPI_File file,
    __in MPI_Info info
    );
int
MPIAPI
PMPI_File_set_info(
    __in MPI_File file,
    __in MPI_Info info
    );

int
MPIAPI
MPI_File_get_info(
    __in MPI_File file,
    __out MPI_Info* info
    );
int
MPIAPI
PMPI_File_get_info(
    __in MPI_File file,
    __out MPI_Info* info
    );


/*---------------------------------------------*/
/* Section 13.3: File Views                    */
/*---------------------------------------------*/

#define MPI_DISPLACEMENT_CURRENT (-54278278)

int
MPIAPI
MPI_File_set_view(
    __in MPI_File file,
    __in MPI_Offset disp,
    __in MPI_Datatype etype,
    __in MPI_Datatype filetype,
    __in_z char* datarep,
    __in MPI_Info info
    );
int
MPIAPI
PMPI_File_set_view(
    __in MPI_File file,
    __in MPI_Offset disp,
    __in MPI_Datatype etype,
    __in MPI_Datatype filetype,
    __in_z char* datarep,
    __in MPI_Info info
    );

int
MPIAPI
MPI_File_get_view(
    __in MPI_File file,
    __out MPI_Offset* disp,
    __out MPI_Datatype* etype,
    __out MPI_Datatype* filetype,
    __out_ecount_z(MPI_MAX_DATAREP_STRING) char* datarep
    );
int
MPIAPI
PMPI_File_get_view(
    __in MPI_File file,
    __out MPI_Offset* disp,
    __out MPI_Datatype* etype,
    __out MPI_Datatype* filetype,
    __out_ecount_z(MPI_MAX_DATAREP_STRING) char* datarep
    );


/*---------------------------------------------*/
/* Section 13.4: Data Access                   */
/*---------------------------------------------*/

int
MPIAPI
MPI_File_read_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_read_at_all(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read_at_all(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write_at_all(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_at_all(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_iread_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_File_iread_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_File_iwrite_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_File_iwrite_at(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_File_read(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_read_all(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read_all(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write_all(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_all(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );


int
MPIAPI
MPI_File_iread(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_File_iread(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_File_iwrite(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_File_iwrite(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );


/* File seek whence */
#define MPI_SEEK_SET    600
#define MPI_SEEK_CUR    602
#define MPI_SEEK_END    604

int
MPIAPI
MPI_File_seek(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in int whence
    );
int
MPIAPI
PMPI_File_seek(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in int whence
    );

int
MPIAPI
MPI_File_get_position(
    __in MPI_File file,
    __out MPI_Offset* offset
    );
int
MPIAPI
PMPI_File_get_position(
    __in MPI_File file,
    __out MPI_Offset* offset
    );

int
MPIAPI
MPI_File_get_byte_offset(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out MPI_Offset* disp
    );
int
MPIAPI
PMPI_File_get_byte_offset(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out MPI_Offset* disp
    );

int
MPIAPI
MPI_File_read_shared(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
     );
int
MPIAPI
PMPI_File_read_shared(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
     );

int
MPIAPI
MPI_File_write_shared(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_shared(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_iread_shared(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_File_iread_shared(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_File_iwrite_shared(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );
int
MPIAPI
PMPI_File_iwrite_shared(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Request* request
    );

int
MPIAPI
MPI_File_read_ordered(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read_ordered(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write_ordered(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_ordered(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_seek_shared(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in int whence
    );
int
MPIAPI
PMPI_File_seek_shared(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in int whence
    );

int
MPIAPI
MPI_File_get_position_shared(
    __in MPI_File file,
    __out MPI_Offset* offset
    );
int
MPIAPI
PMPI_File_get_position_shared(
    __in MPI_File file,
    __out MPI_Offset* offset
    );

int
MPIAPI
MPI_File_read_at_all_begin(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );
int
MPIAPI
PMPI_File_read_at_all_begin(
    __in MPI_File file,
    __in MPI_Offset offset,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );

int
MPIAPI
MPI_File_read_at_all_end(
    __in MPI_File file,
    __out void* buf,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read_at_all_end(
    __in MPI_File file,
    __out void* buf,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write_at_all_begin(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );
int
MPIAPI
PMPI_File_write_at_all_begin(
    __in MPI_File file,
    __in MPI_Offset offset,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );

int
MPIAPI
MPI_File_write_at_all_end(
    __in MPI_File file,
    __in void* buf,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_at_all_end(
    __in MPI_File file,
    __in void* buf,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_read_all_begin(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );
int
MPIAPI
PMPI_File_read_all_begin(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );

int
MPIAPI
MPI_File_read_all_end(
    __in MPI_File file,
    __out void* buf,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read_all_end(
    __in MPI_File file,
    __out void* buf,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write_all_begin(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );
int
MPIAPI
PMPI_File_write_all_begin(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );

int
MPIAPI
MPI_File_write_all_end(
    __in MPI_File file,
    __in void* buf,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_all_end(
    __in MPI_File file,
    __in void* buf,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_read_ordered_begin(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );
int
MPIAPI
PMPI_File_read_ordered_begin(
    __in MPI_File file,
    __out void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );

int
MPIAPI
MPI_File_read_ordered_end(
    __in MPI_File file,
    __out void* buf,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_read_ordered_end(
    __in MPI_File file,
    __out void* buf,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_File_write_ordered_begin(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );
int
MPIAPI
PMPI_File_write_ordered_begin(
    __in MPI_File file,
    __in void* buf,
    __in int count,
    __in MPI_Datatype datatype
    );

int
MPIAPI
MPI_File_write_ordered_end(
    __in MPI_File file,
    __in void* buf,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_File_write_ordered_end(
    __in MPI_File file,
    __in void* buf,
    __out MPI_Status* status
    );


/*---------------------------------------------*/
/* Section 13.5: File Interoperability         */
/*---------------------------------------------*/

int
MPIAPI
MPI_File_get_type_extent(
    __in MPI_File file,
    __in MPI_Datatype datatype,
    __out MPI_Aint* extent
    );
int
MPIAPI
PMPI_File_get_type_extent(
    __in MPI_File file,
    __in MPI_Datatype datatype,
    __out MPI_Aint* extent
    );


typedef
int
(MPIAPI MPI_Datarep_conversion_function)(
    __inout void* userbuf,
    __in MPI_Datatype datatype,
    __in int count,
    __inout void* filebuf,
    __in MPI_Offset position,
    __in void* extra_state
    );

typedef
int
(MPIAPI MPI_Datarep_extent_function)(
    __in MPI_Datatype datatype,
    __out MPI_Aint* file_extent,
    __in void* extra_state
    );

#define MPI_CONVERSION_FN_NULL ((MPI_Datarep_conversion_function*)0)

#define MPI_MAX_DATAREP_STRING  128

int
MPIAPI
MPI_Register_datarep(
    __in_z char* datarep,
    __in MPI_Datarep_conversion_function* read_conversion_fn,
    __in MPI_Datarep_conversion_function* write_conversion_fn,
    __in MPI_Datarep_extent_function* dtype_file_extent_fn,
    __in_opt void* extra_state
    );
int
MPIAPI
PMPI_Register_datarep(
    __in_z char* datarep,
    __in MPI_Datarep_conversion_function* read_conversion_fn,
    __in MPI_Datarep_conversion_function* write_conversion_fn,
    __in MPI_Datarep_extent_function* dtype_file_extent_fn,
    __in_opt void* extra_state
    );


/*---------------------------------------------*/
/* Section 13.6: Consistency and Semantics     */
/*---------------------------------------------*/

int
MPIAPI
MPI_File_set_atomicity(
    __in MPI_File file,
    __in int flag
    );
int
MPIAPI
PMPI_File_set_atomicity(
    __in MPI_File file,
    __in int flag
    );

int
MPIAPI
MPI_File_get_atomicity(
    __in MPI_File file,
    __out int* flag
    );
int
MPIAPI
PMPI_File_get_atomicity(
    __in MPI_File file,
    __out int* flag
    );

int
MPIAPI
MPI_File_sync(
    __in MPI_File file
    );
int
MPIAPI
PMPI_File_sync(
    __in MPI_File file
    );


/*---------------------------------------------------------------------------*/
/* Chapter 14: Profiling Interface                                           */
/*---------------------------------------------------------------------------*/

int
MPIAPI
MPI_Pcontrol(
    __in const int level,
    ...);
int
MPIAPI
PMPI_Pcontrol(
    __in const int level,
    ...);


/*---------------------------------------------------------------------------*/
/* Chapter 15: Depricated Functions                                          */
/*---------------------------------------------------------------------------*/

#ifdef MSMPI_NO_DEPRECATE_20
#define MSMPI_DEPRECATE_20( x )
#else
#define MSMPI_DEPRECATE_20( x ) __declspec(deprecated( \
    "Deprecated in MPI 2.0, use '" #x "'.  " \
    "To disable deprecation, define MSMPI_NO_DEPRECATE_20." ))
#endif

MSMPI_DEPRECATE_20( MPI_Type_create_hvector )
int
MPIAPI
MPI_Type_hvector(
    __in int count,
    __in int blocklength,
    __in MPI_Aint stride,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
MSMPI_DEPRECATE_20( PMPI_Type_create_hvector )
int
MPIAPI
PMPI_Type_hvector(
    __in int count,
    __in int blocklength,
    __in MPI_Aint stride,
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

MSMPI_DEPRECATE_20( MPI_Type_create_hindexed )
int
MPIAPI
MPI_Type_hindexed(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );
MSMPI_DEPRECATE_20( PMPI_Type_create_hindexed )
int
MPIAPI
PMPI_Type_hindexed(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in MPI_Datatype oldtype,
    __out MPI_Datatype* newtype
    );

MSMPI_DEPRECATE_20( MPI_Type_create_struct )
int
MPIAPI
MPI_Type_struct(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in_ecount(count) MPI_Datatype array_of_types[],
    __in MPI_Datatype* newtype
    );
MSMPI_DEPRECATE_20( PMPI_Type_create_struct )
int
MPIAPI
PMPI_Type_struct(
    __in int count,
    __in_ecount(count) int array_of_blocklengths[],
    __in_ecount(count) MPI_Aint array_of_displacements[],
    __in_ecount(count) MPI_Datatype array_of_types[],
    __in MPI_Datatype* newtype
    );

MSMPI_DEPRECATE_20( MPI_Get_address )
int
MPIAPI
MPI_Address(
    __in void* location,
    __out MPI_Aint* address
    );
MSMPI_DEPRECATE_20( PMPI_Get_address )
int
MPIAPI
PMPI_Address(
    __in void* location,
    __out MPI_Aint* address
    );

MSMPI_DEPRECATE_20( MPI_Type_get_extent )
int
MPIAPI
MPI_Type_extent(
    __in MPI_Datatype datatype,
    __out MPI_Aint* extent
    );
MSMPI_DEPRECATE_20( PMPI_Type_get_extent )
int
MPIAPI
PMPI_Type_extent(
    __in MPI_Datatype datatype,
    __out MPI_Aint* extent
    );

MSMPI_DEPRECATE_20( MPI_Type_get_extent )
int
MPIAPI
MPI_Type_lb(
    __in MPI_Datatype datatype,
    __out MPI_Aint* displacement
    );
MSMPI_DEPRECATE_20( PMPI_Type_get_extent )
int
MPIAPI
PMPI_Type_lb(
    __in MPI_Datatype datatype,
    __out MPI_Aint* displacement
    );

MSMPI_DEPRECATE_20( MPI_Type_get_extent )
int
MPIAPI
MPI_Type_ub(
    __in MPI_Datatype datatype,
    __out MPI_Aint* displacement
    );
MSMPI_DEPRECATE_20( PMPI_Type_get_extent )
int
MPIAPI
PMPI_Type_ub(
    __in MPI_Datatype datatype,
    __out MPI_Aint* displacement
    );


typedef MPI_Comm_copy_attr_function MPI_Copy_function;
typedef MPI_Comm_delete_attr_function MPI_Delete_function;

#define MPI_NULL_COPY_FN ((MPI_Copy_function*)0)
#define MPI_NULL_DELETE_FN ((MPI_Delete_function*)0)
#define MPI_DUP_FN MPIR_Dup_fn


MSMPI_DEPRECATE_20( MPI_Comm_create_keyval )
int
MPIAPI
MPI_Keyval_create(
    __in MPI_Copy_function* copy_fn,
    __in MPI_Delete_function* delete_fn,
    __out int* keyval,
    __in_opt void* extra_state
    );
MSMPI_DEPRECATE_20( PMPI_Comm_create_keyval )
int
MPIAPI
PMPI_Keyval_create(
    __in MPI_Copy_function* copy_fn,
    __in MPI_Delete_function* delete_fn,
    __out int* keyval,
    __in_opt void* extra_state
    );

MSMPI_DEPRECATE_20( MPI_Comm_free_keyval )
int
MPIAPI
MPI_Keyval_free(
    __inout int* keyval
    );
MSMPI_DEPRECATE_20( PMPI_Comm_free_keyval )
int
MPIAPI
PMPI_Keyval_free(
    __inout int* keyval
    );

MSMPI_DEPRECATE_20( MPI_Comm_set_attr )
int
MPIAPI
MPI_Attr_put(
    __in MPI_Comm comm,
    __in int keyval,
    __in void* attribute_val
    );
MSMPI_DEPRECATE_20( PMPI_Comm_set_attr )
int
MPIAPI
PMPI_Attr_put(
    __in MPI_Comm comm,
    __in int keyval,
    __in void* attribute_val
    );

MSMPI_DEPRECATE_20( MPI_Comm_get_attr )
int
MPIAPI
MPI_Attr_get(
    __in MPI_Comm comm,
    __in int keyval,
    __out void* attribute_val,
    __out int* flag
    );
MSMPI_DEPRECATE_20( PMPI_Comm_get_attr )
int
MPIAPI
PMPI_Attr_get(
    __in MPI_Comm comm,
    __in int keyval,
    __out void* attribute_val,
    __out int* flag
    );

MSMPI_DEPRECATE_20( MPI_Comm_delete_attr )
int
MPIAPI
MPI_Attr_delete(
    __in MPI_Comm comm,
    __in int keyval
    );
MSMPI_DEPRECATE_20( PMPI_Comm_delete_attr )
int
MPIAPI
PMPI_Attr_delete(
    __in MPI_Comm comm,
    __in int keyval
    );


typedef MPI_Comm_errhandler_fn MPI_Handler_function;

MSMPI_DEPRECATE_20( MPI_Comm_create_errhandler )
int
MPIAPI
MPI_Errhandler_create(
    __in MPI_Handler_function* function,
    __out MPI_Errhandler* errhandler
    );
MSMPI_DEPRECATE_20( PMPI_Comm_create_errhandler )
int
MPIAPI
PMPI_Errhandler_create(
    __in MPI_Handler_function* function,
    __out MPI_Errhandler* errhandler
    );

MSMPI_DEPRECATE_20( MPI_Comm_set_errhandler )
int
MPIAPI
MPI_Errhandler_set(
    __in MPI_Comm comm,
    __in MPI_Errhandler errhandler
    );
MSMPI_DEPRECATE_20( PMPI_Comm_set_errhandler )
int
MPIAPI
PMPI_Errhandler_set(
    __in MPI_Comm comm,
    __in MPI_Errhandler errhandler
    );

MSMPI_DEPRECATE_20( MPI_Comm_get_errhandler )
int
MPIAPI
MPI_Errhandler_get(
    __in MPI_Comm comm,
    __out MPI_Errhandler* errhandler
    );
MSMPI_DEPRECATE_20( PMPI_Comm_get_errhandler )
int
MPIAPI
PMPI_Errhandler_get(
    __in MPI_Comm comm,
    __out MPI_Errhandler* errhandler
    );


/*---------------------------------------------------------------------------*/
/* Chapter 16: Language Bindings                                             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------*/
/* Section 16.2: Fortran Support               */
/*---------------------------------------------*/

int
MPIAPI
MPI_Type_create_f90_real(
    __in int p,
    __in int r,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_f90_real(
    __in int p,
    __in int r,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_create_f90_complex(
    __in int p,
    __in int r,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_f90_complex(
    __in int p,
    __in int r,
    __out MPI_Datatype* newtype
    );

int
MPIAPI
MPI_Type_create_f90_integer(
    __in int r,
    __out MPI_Datatype* newtype
    );
int
MPIAPI
PMPI_Type_create_f90_integer(
    __in int r,
    __out MPI_Datatype* newtype
    );

/* typeclasses */
#define MPI_TYPECLASS_REAL      1
#define MPI_TYPECLASS_INTEGER   2
#define MPI_TYPECLASS_COMPLEX   3

int
MPIAPI
MPI_Type_match_size(
    __in int typeclass,
    __in int size,
    __out MPI_Datatype* type
    );
int
MPIAPI
PMPI_Type_match_size(
    __in int typeclass,
    __in int size,
    __out MPI_Datatype* type
    );


/*---------------------------------------------*/
/* Section 16.3: Language Interoperability     */
/*---------------------------------------------*/

#define MPI_Comm_c2f(comm)  (MPI_Fint)(comm)
#define PMPI_Comm_c2f(comm) (MPI_Fint)(comm)

#define MPI_Comm_f2c(comm)  (MPI_Comm)(comm)
#define PMPI_Comm_f2c(comm) (MPI_Comm)(comm)


#define MPI_Type_f2c(datatype)  (MPI_Datatype)(datatype)
#define PMPI_Type_f2c(datatype) (MPI_Datatype)(datatype)

#define MPI_Type_c2f(datatype)  (MPI_Fint)(datatype)
#define PMPI_Type_c2f(datatype) (MPI_Fint)(datatype)


#define MPI_Group_f2c(group)  (MPI_Group)(group)
#define PMPI_Group_f2c(group) (MPI_Group)(group)

#define MPI_Group_c2f(group)  (MPI_Fint)(group)
#define PMPI_Group_c2f(group) (MPI_Fint)(group)


#define MPI_Request_f2c(request)  (MPI_Request)(request)
#define PMPI_Request_f2c(request) (MPI_Request)(request)

#define MPI_Request_c2f(request)  (MPI_Fint)(request)
#define PMPI_Request_c2f(request) (MPI_Fint)(request)


#define MPI_Win_f2c(win)  (MPI_Win)(win)
#define PMPI_Win_f2c(win) (MPI_Win)(win)

#define MPI_Win_c2f(win)  (MPI_Fint)(win)
#define PMPI_Win_c2f(win) (MPI_Fint)(win)


#define MPI_Op_c2f(op)  (MPI_Fint)(op)
#define PMPI_Op_c2f(op) (MPI_Fint)(op)

#define MPI_Op_f2c(op)  (MPI_Op)(op)
#define PMPI_Op_f2c(op) (MPI_Op)(op)


#define MPI_Info_c2f(info)  (MPI_Fint)(info)
#define PMPI_Info_c2f(info) (MPI_Fint)(info)

#define MPI_Info_f2c(info)  (MPI_Info)(info)
#define PMPI_Info_f2c(info) (MPI_Info)(info)


#define MPI_Errhandler_c2f(errhandler)  (MPI_Fint)(errhandler)
#define PMPI_Errhandler_c2f(errhandler) (MPI_Fint)(errhandler)

#define MPI_Errhandler_f2c(errhandler)  (MPI_Errhandler)(errhandler)
#define PMPI_Errhandler_f2c(errhandler) (MPI_Errhandler)(errhandler)


MPI_File
MPIAPI
MPI_File_f2c(
    __in MPI_Fint file
    );
MPI_File
MPIAPI
PMPI_File_f2c(
    __in MPI_Fint file
    );

MPI_Fint
MPIAPI
MPI_File_c2f(
    __in MPI_File file
    );
MPI_Fint
MPIAPI
PMPI_File_c2f(
    __in MPI_File file
    );

int
MPIAPI
MPI_Status_f2c(
    __in MPI_Fint* f_status,
    __out MPI_Status* status
    );
int
MPIAPI
PMPI_Status_f2c(
    __in MPI_Fint* f_status,
    __out MPI_Status* status
    );

int
MPIAPI
MPI_Status_c2f(
    __in MPI_Status* status,
    __out MPI_Fint* f_status
    );
int
MPIAPI
PMPI_Status_c2f(
    __in MPI_Status* status,
    __out MPI_Fint* f_status
    );


#if !defined(_MPICH_DLL_)
#define MPIU_DLL_SPEC __declspec(dllimport)
#else
#define MPIU_DLL_SPEC
#endif

extern MPIU_DLL_SPEC MPI_Fint* MPI_F_STATUS_IGNORE;
extern MPIU_DLL_SPEC MPI_Fint* MPI_F_STATUSES_IGNORE;


/*---------------------------------------------------------------------------*/
/* Implementation Specific                                                   */
/*---------------------------------------------------------------------------*/

int
MPIAPI
MPIR_Dup_fn(
    __in MPI_Comm oldcomm,
    __in int keyval,
    __in_opt void* extra_state,
    __in void* attribute_val_in,
    __out void* attribute_val_out,
    __out int* flag
    );


#if MSMPI_VER >= 0x300

int
MPIAPI
MSMPI_Get_bsend_overhead();

#endif


#if MSMPI_VER >= 0x300

int
MPIAPI
MSMPI_Get_version();

#else
#  define MSMPI_Get_version() (MSMPI_VER)
#endif

typedef void
(MPIAPI MSMPI_Request_callback)(
    __in MPI_Status* status
    );

int
MPIAPI
MSMPI_Request_set_apc(
    __in MPI_Request request,
    __in MSMPI_Request_callback* callback_fn,
    __in MPI_Status* callback_status
    );

typedef struct _MSMPI_LOCK_QUEUE
{
    struct _MSMPI_LOCK_QUEUE* volatile next;
    volatile MPI_Aint flags;

} MSMPI_Lock_queue;

void
MPIAPI
MSMPI_Queuelock_acquire(
    __out MSMPI_Lock_queue* queue
    );

void
MPIAPI
MSMPI_Queuelock_release(
    __in MSMPI_Lock_queue* queue
    );

int
MPIAPI
MSMPI_Waitsome_interruptible(
    __in int incount,
    __inout_ecount(incount) MPI_Request array_of_requests[],
    __out int* outcount,
    __out_ecount_part(incount,*outcount) int array_of_indices[],
    __out_ecount_part(incount,*outcount) MPI_Status array_of_statuses[]
    );


/*---------------------------------------------------------------------------*/
/* SAL ANNOTATIONS                                                           */
/*---------------------------------------------------------------------------*/

#ifdef MSMPI_DEFINED_SAL
#undef MSMPI_DEFINED_SAL
#undef __in
#undef __in_z
#undef __in_opt
#undef __out
#undef __out_z
#undef __out_opt
#undef __inout
#undef __inout_ecount
#undef __in_bcount
#undef __in_ecount
#undef __out_bcount
#undef __out_ecount
#undef __out_ecount_z
#undef __out_ecount_part
#undef __out_ecount_part_z
#undef __deref_ecount_opt
#endif

#if defined(__cplusplus)
}
#endif

#endif /* MPI_INCLUDED */
