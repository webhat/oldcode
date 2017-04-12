# 23 "main.c"
# 1 "/usr/local/include/stdio.h" 1 3
# 28 "/usr/local/include/stdio.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 283 "/usr/local/include/features.h" 3
# 1 "/usr/local/include/sys/cdefs.h" 1 3
# 284 "/usr/local/include/features.h" 2 3
# 312 "/usr/local/include/features.h" 3
# 1 "/usr/include/gnu/stubs.h" 1 3
# 313 "/usr/local/include/features.h" 2 3
# 29 "/usr/local/include/stdio.h" 2 3





# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 199 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 3
typedef unsigned int size_t;
# 35 "/usr/local/include/stdio.h" 2 3

# 1 "/usr/local/include/bits/types.h" 1 3
# 26 "/usr/local/include/bits/types.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 27 "/usr/local/include/bits/types.h" 2 3


# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 30 "/usr/local/include/bits/types.h" 2 3


typedef unsigned char __u_char;
typedef unsigned short __u_short;
typedef unsigned int __u_int;
typedef unsigned long __u_long;

__extension__ typedef unsigned long long int __u_quad_t;
__extension__ typedef long long int __quad_t;
# 49 "/usr/local/include/bits/types.h" 3
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;

typedef __quad_t *__qaddr_t;

typedef __u_quad_t __dev_t;
typedef __u_int __uid_t;
typedef __u_int __gid_t;
typedef __u_long __ino_t;
typedef __u_int __mode_t;
typedef __u_int __nlink_t;
typedef long int __off_t;
typedef __quad_t __loff_t;
typedef int __pid_t;
typedef int __ssize_t;
typedef __u_long __rlim_t;
typedef __u_quad_t __rlim64_t;
typedef __u_int __id_t;

typedef struct
  {
    int __val[2];
  } __fsid_t;


typedef int __daddr_t;
typedef char *__caddr_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __swblk_t;

typedef long int __clock_t;


typedef int __clockid_t;


typedef int __timer_t;






typedef int __key_t;


typedef unsigned short int __ipc_pid_t;



typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef __quad_t __blkcnt64_t;


typedef __u_long __fsblkcnt_t;
typedef __u_quad_t __fsblkcnt64_t;


typedef __u_long __fsfilcnt_t;
typedef __u_quad_t __fsfilcnt64_t;


typedef __u_quad_t __ino64_t;


typedef __loff_t __off64_t;


typedef long int __t_scalar_t;
typedef unsigned long int __t_uscalar_t;


typedef int __intptr_t;


typedef unsigned int __socklen_t;




# 1 "/usr/local/include/bits/pthreadtypes.h" 1 3
# 23 "/usr/local/include/bits/pthreadtypes.h" 3
# 1 "/usr/local/include/bits/sched.h" 1 3
# 68 "/usr/local/include/bits/sched.h" 3
struct __sched_param
  {
    int __sched_priority;
  };
# 24 "/usr/local/include/bits/pthreadtypes.h" 2 3


struct _pthread_fastlock
{
  long int __status;
  int __spinlock;

};



typedef struct _pthread_descr_struct *_pthread_descr;





typedef struct __pthread_attr_s
{
  int __detachstate;
  int __schedpolicy;
  struct __sched_param __schedparam;
  int __inheritsched;
  int __scope;
  size_t __guardsize;
  int __stackaddr_set;
  void *__stackaddr;
  size_t __stacksize;
} pthread_attr_t;



typedef struct
{
  struct _pthread_fastlock __c_lock;
  _pthread_descr __c_waiting;
} pthread_cond_t;



typedef struct
{
  int __dummy;
} pthread_condattr_t;


typedef unsigned int pthread_key_t;





typedef struct
{
  int __m_reserved;
  int __m_count;
  _pthread_descr __m_owner;
  int __m_kind;
  struct _pthread_fastlock __m_lock;
} pthread_mutex_t;



typedef struct
{
  int __mutexkind;
} pthread_mutexattr_t;



typedef int pthread_once_t;
# 140 "/usr/local/include/bits/pthreadtypes.h" 3
typedef unsigned long int pthread_t;
# 144 "/usr/local/include/bits/types.h" 2 3
# 37 "/usr/local/include/stdio.h" 2 3
# 45 "/usr/local/include/stdio.h" 3
typedef struct _IO_FILE FILE;
# 55 "/usr/local/include/stdio.h" 3
typedef struct _IO_FILE __FILE;
# 65 "/usr/local/include/stdio.h" 3
# 1 "/usr/local/include/libio.h" 1 3
# 32 "/usr/local/include/libio.h" 3
# 1 "/usr/local/include/_G_config.h" 1 3
# 9 "/usr/local/include/_G_config.h" 3
# 1 "/usr/local/include/bits/types.h" 1 3
# 10 "/usr/local/include/_G_config.h" 2 3




# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 287 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 3
typedef long int wchar_t;
# 312 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 3
typedef unsigned int wint_t;
# 15 "/usr/local/include/_G_config.h" 2 3
# 24 "/usr/local/include/_G_config.h" 3
# 1 "/usr/local/include/wchar.h" 1 3
# 48 "/usr/local/include/wchar.h" 3
# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 49 "/usr/local/include/wchar.h" 2 3

# 1 "/usr/local/include/bits/wchar.h" 1 3
# 51 "/usr/local/include/wchar.h" 2 3
# 67 "/usr/local/include/wchar.h" 3
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 25 "/usr/local/include/_G_config.h" 2 3

typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
# 44 "/usr/local/include/_G_config.h" 3
# 1 "/usr/local/include/gconv.h" 1 3
# 26 "/usr/local/include/gconv.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 27 "/usr/local/include/gconv.h" 2 3

# 1 "/usr/local/include/wchar.h" 1 3
# 48 "/usr/local/include/wchar.h" 3
# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 49 "/usr/local/include/wchar.h" 2 3

# 1 "/usr/local/include/bits/wchar.h" 1 3
# 51 "/usr/local/include/wchar.h" 2 3
# 29 "/usr/local/include/gconv.h" 2 3


# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 32 "/usr/local/include/gconv.h" 2 3





enum
{
  __GCONV_OK = 0,
  __GCONV_NOCONV,
  __GCONV_NODB,
  __GCONV_NOMEM,

  __GCONV_EMPTY_INPUT,
  __GCONV_FULL_OUTPUT,
  __GCONV_ILLEGAL_INPUT,
  __GCONV_INCOMPLETE_INPUT,

  __GCONV_ILLEGAL_DESCRIPTOR,
  __GCONV_INTERNAL_ERROR
};



enum
{
  __GCONV_IS_LAST = 0x0001,
  __GCONV_IGNORE_ERRORS = 0x0002
};



struct __gconv_step;
struct __gconv_step_data;
struct __gconv_loaded_object;
struct __gconv_trans_data;



typedef int (*__gconv_fct) (struct __gconv_step *, struct __gconv_step_data *,
                            __const unsigned char **, __const unsigned char *,
                            unsigned char **, size_t *, int, int);


typedef int (*__gconv_init_fct) (struct __gconv_step *);
typedef void (*__gconv_end_fct) (struct __gconv_step *);



typedef int (*__gconv_trans_fct) (struct __gconv_step *,
                                  struct __gconv_step_data *, void *,
                                  __const unsigned char *,
                                  __const unsigned char **,
                                  __const unsigned char *, unsigned char **,
                                  size_t *);


typedef int (*__gconv_trans_context_fct) (void *, __const unsigned char *,
                                          __const unsigned char *,
                                          unsigned char *, unsigned char *);


typedef int (*__gconv_trans_query_fct) (__const char *, __const char ***,
                                        size_t *);


typedef int (*__gconv_trans_init_fct) (void **, const char *);
typedef void (*__gconv_trans_end_fct) (void *);

struct __gconv_trans_data
{

  __gconv_trans_fct __trans_fct;
  __gconv_trans_context_fct __trans_context_fct;
  __gconv_trans_end_fct __trans_end_fct;
  void *__data;
  struct __gconv_trans_data *__next;
};



struct __gconv_step
{
  struct __gconv_loaded_object *__shlib_handle;
  __const char *__modname;

  int __counter;

  char *__from_name;
  char *__to_name;

  __gconv_fct __fct;
  __gconv_init_fct __init_fct;
  __gconv_end_fct __end_fct;



  int __min_needed_from;
  int __max_needed_from;
  int __min_needed_to;
  int __max_needed_to;


  int __stateful;

  void *__data;
};



struct __gconv_step_data
{
  unsigned char *__outbuf;
  unsigned char *__outbufend;



  int __flags;



  int __invocation_counter;



  int __internal_use;

  __mbstate_t *__statep;
  __mbstate_t __state;



  struct __gconv_trans_data *__trans;
};



typedef struct __gconv_info
{
  size_t __nsteps;
  struct __gconv_step *__steps;
  __extension__ struct __gconv_step_data __data [];
} *__gconv_t;
# 45 "/usr/local/include/_G_config.h" 2 3
typedef union
{
  struct __gconv_info __cd;
  struct
  {
    struct __gconv_info __cd;
    struct __gconv_step_data __data;
  } __combined;
} _G_iconv_t;

typedef int _G_int16_t __attribute__ ((__mode__ (__HI__)));
typedef int _G_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int _G_uint16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int _G_uint32_t __attribute__ ((__mode__ (__SI__)));
# 33 "/usr/local/include/libio.h" 2 3
# 53 "/usr/local/include/libio.h" 3
# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stdarg.h" 1 3
# 43 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 54 "/usr/local/include/libio.h" 2 3
# 160 "/usr/local/include/libio.h" 3
struct _IO_jump_t; struct _IO_FILE;
# 170 "/usr/local/include/libio.h" 3
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 193 "/usr/local/include/libio.h" 3
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 261 "/usr/local/include/libio.h" 3
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _blksize;
  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
# 305 "/usr/local/include/libio.h" 3
  __off64_t _offset;





  void *__pad1;
  void *__pad2;

  int _mode;

  char _unused2[15 * sizeof (int) - 2 * sizeof (void *)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 344 "/usr/local/include/libio.h" 3
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, __const char *__buf,
                                 size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 396 "/usr/local/include/libio.h" 3
extern int __underflow (_IO_FILE *) ;
extern int __uflow (_IO_FILE *) ;
extern int __overflow (_IO_FILE *, int) ;
extern wint_t __wunderflow (_IO_FILE *) ;
extern wint_t __wuflow (_IO_FILE *) ;
extern wint_t __woverflow (_IO_FILE *, wint_t) ;
# 426 "/usr/local/include/libio.h" 3
extern int _IO_getc (_IO_FILE *__fp) ;
extern int _IO_putc (int __c, _IO_FILE *__fp) ;
extern int _IO_feof (_IO_FILE *__fp) ;
extern int _IO_ferror (_IO_FILE *__fp) ;

extern int _IO_peekc_locked (_IO_FILE *__fp) ;





extern void _IO_flockfile (_IO_FILE *) ;
extern void _IO_funlockfile (_IO_FILE *) ;
extern int _IO_ftrylockfile (_IO_FILE *) ;
# 456 "/usr/local/include/libio.h" 3
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
                        __gnuc_va_list, int *__restrict) ;
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
                         __gnuc_va_list) ;
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t) ;
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t) ;

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int) ;
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int) ;

extern void _IO_free_backup_area (_IO_FILE *) ;
# 66 "/usr/local/include/stdio.h" 2 3
# 80 "/usr/local/include/stdio.h" 3
typedef _G_fpos_t fpos_t;
# 129 "/usr/local/include/stdio.h" 3
# 1 "/usr/local/include/bits/stdio_lim.h" 1 3
# 130 "/usr/local/include/stdio.h" 2 3



extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (__const char *__filename) ;

extern int rename (__const char *__old, __const char *__new) ;




extern FILE *tmpfile (void) ;
# 161 "/usr/local/include/stdio.h" 3
extern char *tmpnam (char *__s) ;




extern char *tmpnam_r (char *__s) ;
# 178 "/usr/local/include/stdio.h" 3
extern char *tempnam (__const char *__dir, __const char *__pfx)
             __attribute__ ((__malloc__));




extern int fclose (FILE *__stream) ;

extern int fflush (FILE *__stream) ;



extern int fflush_unlocked (FILE *__stream) ;
# 201 "/usr/local/include/stdio.h" 3
extern FILE *fopen (__const char *__restrict __filename,
                    __const char *__restrict __modes) ;

extern FILE *freopen (__const char *__restrict __filename,
                      __const char *__restrict __modes,
                      FILE *__restrict __stream) ;
# 231 "/usr/local/include/stdio.h" 3
extern FILE *fdopen (int __fd, __const char *__modes) ;
# 254 "/usr/local/include/stdio.h" 3
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) ;



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
                    int __modes, size_t __n) ;




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
                       size_t __size) ;


extern void setlinebuf (FILE *__stream) ;




extern int fprintf (FILE *__restrict __stream,
                    __const char *__restrict __format, ...) ;

extern int printf (__const char *__restrict __format, ...) ;

extern int sprintf (char *__restrict __s,
                    __const char *__restrict __format, ...) ;


extern int vfprintf (FILE *__restrict __s, __const char *__restrict __format,
                     __gnuc_va_list __arg) ;

extern int vprintf (__const char *__restrict __format, __gnuc_va_list __arg)
            ;

extern int vsprintf (char *__restrict __s, __const char *__restrict __format,
                     __gnuc_va_list __arg) ;



extern int snprintf (char *__restrict __s, size_t __maxlen,
                     __const char *__restrict __format, ...)
             __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
                      __const char *__restrict __format, __gnuc_va_list __arg)
             __attribute__ ((__format__ (__printf__, 3, 0)));
# 325 "/usr/local/include/stdio.h" 3
extern int fscanf (FILE *__restrict __stream,
                   __const char *__restrict __format, ...) ;

extern int scanf (__const char *__restrict __format, ...) ;

extern int sscanf (__const char *__restrict __s,
                   __const char *__restrict __format, ...) ;
# 351 "/usr/local/include/stdio.h" 3
extern int fgetc (FILE *__stream) ;
extern int getc (FILE *__stream) ;


extern int getchar (void) ;







extern int getc_unlocked (FILE *__stream) ;
extern int getchar_unlocked (void) ;




extern int fgetc_unlocked (FILE *__stream) ;




extern int fputc (int __c, FILE *__stream) ;
extern int putc (int __c, FILE *__stream) ;


extern int putchar (int __c) ;







extern int fputc_unlocked (int __c, FILE *__stream) ;




extern int putc_unlocked (int __c, FILE *__stream) ;
extern int putchar_unlocked (int __c) ;





extern int getw (FILE *__stream) ;


extern int putw (int __w, FILE *__stream) ;




extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
            ;
# 417 "/usr/local/include/stdio.h" 3
extern char *gets (char *__s) ;
# 441 "/usr/local/include/stdio.h" 3
extern int fputs (__const char *__restrict __s, FILE *__restrict __stream)
            ;
# 451 "/usr/local/include/stdio.h" 3
extern int puts (__const char *__s) ;



extern int ungetc (int __c, FILE *__stream) ;



extern size_t fread (void *__restrict __ptr, size_t __size,
                     size_t __n, FILE *__restrict __stream) ;

extern size_t fwrite (__const void *__restrict __ptr, size_t __size,
                      size_t __n, FILE *__restrict __s) ;



extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
                              size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (__const void *__restrict __ptr, size_t __size,
                               size_t __n, FILE *__restrict __stream) ;




extern int fseek (FILE *__stream, long int __off, int __whence) ;

extern long int ftell (FILE *__stream) ;

extern void rewind (FILE *__stream) ;
# 495 "/usr/local/include/stdio.h" 3
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos)
            ;

extern int fsetpos (FILE *__stream, __const fpos_t *__pos) ;
# 531 "/usr/local/include/stdio.h" 3
extern void clearerr (FILE *__stream) ;

extern int feof (FILE *__stream) ;

extern int ferror (FILE *__stream) ;



extern void clearerr_unlocked (FILE *__stream) ;
extern int feof_unlocked (FILE *__stream) ;
extern int ferror_unlocked (FILE *__stream) ;




extern void perror (__const char *__s) ;




extern int sys_nerr;
extern __const char *__const sys_errlist[];
# 562 "/usr/local/include/stdio.h" 3
extern int fileno (FILE *__stream) ;




extern int fileno_unlocked (FILE *__stream) ;






extern FILE *popen (__const char *__command, __const char *__modes) ;


extern int pclose (FILE *__stream) ;





extern char *ctermid (char *__s) ;
# 609 "/usr/local/include/stdio.h" 3
extern void flockfile (FILE *__stream) ;



extern int ftrylockfile (FILE *__stream) ;


extern void funlockfile (FILE *__stream) ;
# 24 "main.c" 2
# 1 "/usr/local/include/sys/types.h" 1 3
# 26 "/usr/local/include/sys/types.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 27 "/usr/local/include/sys/types.h" 2 3



# 1 "/usr/local/include/bits/types.h" 1 3
# 31 "/usr/local/include/sys/types.h" 2 3



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
# 61 "/usr/local/include/sys/types.h" 3
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 99 "/usr/local/include/sys/types.h" 3
typedef __pid_t pid_t;




typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 132 "/usr/local/include/sys/types.h" 3
# 1 "/usr/local/include/time.h" 1 3
# 67 "/usr/local/include/time.h" 3
# 1 "/usr/local/include/bits/types.h" 1 3
# 68 "/usr/local/include/time.h" 2 3


typedef __time_t time_t;
# 79 "/usr/local/include/time.h" 3
# 1 "/usr/local/include/bits/types.h" 1 3
# 80 "/usr/local/include/time.h" 2 3


typedef __clockid_t clockid_t;
# 91 "/usr/local/include/time.h" 3
# 1 "/usr/local/include/bits/types.h" 1 3
# 92 "/usr/local/include/time.h" 2 3


typedef __timer_t timer_t;
# 133 "/usr/local/include/sys/types.h" 2 3
# 146 "/usr/local/include/sys/types.h" 3
# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 147 "/usr/local/include/sys/types.h" 2 3



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 190 "/usr/local/include/sys/types.h" 3
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));
# 212 "/usr/local/include/sys/types.h" 3
# 1 "/usr/local/include/endian.h" 1 3
# 22 "/usr/local/include/endian.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 23 "/usr/local/include/endian.h" 2 3
# 37 "/usr/local/include/endian.h" 3
# 1 "/usr/local/include/bits/endian.h" 1 3
# 38 "/usr/local/include/endian.h" 2 3
# 213 "/usr/local/include/sys/types.h" 2 3


# 1 "/usr/local/include/sys/select.h" 1 3
# 25 "/usr/local/include/sys/select.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 26 "/usr/local/include/sys/select.h" 2 3


# 1 "/usr/local/include/bits/types.h" 1 3
# 29 "/usr/local/include/sys/select.h" 2 3


# 1 "/usr/local/include/bits/select.h" 1 3
# 32 "/usr/local/include/sys/select.h" 2 3


# 1 "/usr/local/include/bits/sigset.h" 1 3
# 23 "/usr/local/include/bits/sigset.h" 3
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 35 "/usr/local/include/sys/select.h" 2 3



typedef __sigset_t sigset_t;





# 1 "/usr/local/include/time.h" 1 3
# 106 "/usr/local/include/time.h" 3
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 45 "/usr/local/include/sys/select.h" 2 3

# 1 "/usr/local/include/bits/time.h" 1 3
# 63 "/usr/local/include/bits/time.h" 3
# 1 "/usr/local/include/bits/types.h" 1 3
# 64 "/usr/local/include/bits/time.h" 2 3



struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 47 "/usr/local/include/sys/select.h" 2 3


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;







typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 102 "/usr/local/include/sys/select.h" 3
extern int select (int __nfds, fd_set *__restrict __readfds,
                   fd_set *__restrict __writefds,
                   fd_set *__restrict __exceptfds,
                   struct timeval *__restrict __timeout) ;
# 216 "/usr/local/include/sys/types.h" 2 3


# 1 "/usr/local/include/sys/sysmacros.h" 1 3
# 219 "/usr/local/include/sys/types.h" 2 3
# 230 "/usr/local/include/sys/types.h" 3
typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 25 "main.c" 2
# 1 "/usr/local/include/sys/stat.h" 1 3
# 26 "/usr/local/include/sys/stat.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 27 "/usr/local/include/sys/stat.h" 2 3

# 1 "/usr/local/include/bits/types.h" 1 3
# 29 "/usr/local/include/sys/stat.h" 2 3
# 98 "/usr/local/include/sys/stat.h" 3
# 1 "/usr/local/include/bits/stat.h" 1 3
# 36 "/usr/local/include/bits/stat.h" 3
struct stat
  {
    __dev_t st_dev;
    unsigned short int __pad1;

    __ino_t st_ino;



    __mode_t st_mode;
    __nlink_t st_nlink;
    __uid_t st_uid;
    __gid_t st_gid;
    __dev_t st_rdev;
    unsigned short int __pad2;

    __off_t st_size;



    __blksize_t st_blksize;


    __blkcnt_t st_blocks;



    __time_t st_atime;
    unsigned long int __unused1;
    __time_t st_mtime;
    unsigned long int __unused2;
    __time_t st_ctime;
    unsigned long int __unused3;

    unsigned long int __unused4;
    unsigned long int __unused5;



  };
# 99 "/usr/local/include/sys/stat.h" 2 3
# 200 "/usr/local/include/sys/stat.h" 3
extern int stat (__const char *__restrict __file,
                 struct stat *__restrict __buf) ;



extern int fstat (int __fd, struct stat *__buf) ;
# 228 "/usr/local/include/sys/stat.h" 3
extern int lstat (__const char *__restrict __file,
                  struct stat *__restrict __buf) ;
# 249 "/usr/local/include/sys/stat.h" 3
extern int chmod (__const char *__file, __mode_t __mode) ;



extern int fchmod (int __fd, __mode_t __mode) ;





extern __mode_t umask (__mode_t __mask) ;
# 268 "/usr/local/include/sys/stat.h" 3
extern int mkdir (__const char *__path, __mode_t __mode) ;





extern int mknod (__const char *__path, __mode_t __mode, __dev_t __dev)
            ;




extern int mkfifo (__const char *__path, __mode_t __mode) ;
# 306 "/usr/local/include/sys/stat.h" 3
extern int __fxstat (int __ver, int __fildes, struct stat *__stat_buf) ;
extern int __xstat (int __ver, __const char *__filename,
                    struct stat *__stat_buf) ;
extern int __lxstat (int __ver, __const char *__filename,
                     struct stat *__stat_buf) ;
# 337 "/usr/local/include/sys/stat.h" 3
extern int __xmknod (int __ver, __const char *__path, __mode_t __mode,
                     __dev_t *__dev) ;




extern __inline__ int stat (__const char *__path,
                            struct stat *__statbuf)
{
  return __xstat (3, __path, __statbuf);
}


extern __inline__ int lstat (__const char *__path,
                             struct stat *__statbuf)
{
  return __lxstat (3, __path, __statbuf);
}


extern __inline__ int fstat (int __fd, struct stat *__statbuf)
{
  return __fxstat (3, __fd, __statbuf);
}


extern __inline__ int mknod (__const char *__path, __mode_t __mode,
                             __dev_t __dev)
{
  return __xmknod (1, __path, __mode, &__dev);
}
# 26 "main.c" 2
# 1 "/usr/local/include/unistd.h" 1 3
# 26 "/usr/local/include/unistd.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 27 "/usr/local/include/unistd.h" 2 3
# 175 "/usr/local/include/unistd.h" 3
# 1 "/usr/local/include/bits/posix_opt.h" 1 3
# 176 "/usr/local/include/unistd.h" 2 3
# 190 "/usr/local/include/unistd.h" 3
# 1 "/usr/local/include/bits/types.h" 1 3
# 191 "/usr/local/include/unistd.h" 2 3
# 199 "/usr/local/include/unistd.h" 3
# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 200 "/usr/local/include/unistd.h" 2 3
# 240 "/usr/local/include/unistd.h" 3
typedef __intptr_t intptr_t;






typedef __socklen_t socklen_t;
# 260 "/usr/local/include/unistd.h" 3
extern int access (__const char *__name, int __type) ;
# 290 "/usr/local/include/unistd.h" 3
extern __off_t lseek (int __fd, __off_t __offset, int __whence) ;
# 306 "/usr/local/include/unistd.h" 3
extern int close (int __fd) ;



extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;


extern ssize_t write (int __fd, __const void *__buf, size_t __n) ;
# 353 "/usr/local/include/unistd.h" 3
extern int pipe (int __pipedes[2]) ;
# 362 "/usr/local/include/unistd.h" 3
extern unsigned int alarm (unsigned int __seconds) ;
# 371 "/usr/local/include/unistd.h" 3
extern unsigned int sleep (unsigned int __seconds) ;






extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
            ;



extern int usleep (__useconds_t __useconds) ;





extern int pause (void) ;



extern int chown (__const char *__file, __uid_t __owner, __gid_t __group)
            ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) ;




extern int lchown (__const char *__file, __uid_t __owner, __gid_t __group)
            ;




extern int chdir (__const char *__path) ;



extern int fchdir (int __fd) ;
# 423 "/usr/local/include/unistd.h" 3
extern char *getcwd (char *__buf, size_t __size) ;
# 436 "/usr/local/include/unistd.h" 3
extern char *getwd (char *__buf) ;




extern int dup (int __fd) ;


extern int dup2 (int __fd, int __fd2) ;


extern char **__environ;







extern int execve (__const char *__path, char *__const __argv[],
                   char *__const __envp[]) ;
# 467 "/usr/local/include/unistd.h" 3
extern int execv (__const char *__path, char *__const __argv[]) ;



extern int execle (__const char *__path, __const char *__arg, ...) ;



extern int execl (__const char *__path, __const char *__arg, ...) ;



extern int execvp (__const char *__file, char *__const __argv[]) ;




extern int execlp (__const char *__file, __const char *__arg, ...) ;




extern int nice (int __inc) ;




extern void _exit (int __status) __attribute__ ((__noreturn__));





# 1 "/usr/local/include/bits/confname.h" 1 3
# 25 "/usr/local/include/bits/confname.h" 3
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG

  };





enum
  {
    _CS_PATH,
# 563 "/usr/local/include/bits/confname.h" 3
    _CS_V6_WIDTH_RESTRICTED_ENVS

  };
# 501 "/usr/local/include/unistd.h" 2 3


extern long int pathconf (__const char *__path, int __name) ;


extern long int fpathconf (int __fd, int __name) ;


extern long int sysconf (int __name) __attribute__ ((__const__));



extern size_t confstr (int __name, char *__buf, size_t __len) ;




extern __pid_t getpid (void) ;


extern __pid_t getppid (void) ;




extern __pid_t getpgrp (void) ;
# 536 "/usr/local/include/unistd.h" 3
extern __pid_t __getpgid (__pid_t __pid) ;
# 545 "/usr/local/include/unistd.h" 3
extern int setpgid (__pid_t __pid, __pid_t __pgid) ;
# 562 "/usr/local/include/unistd.h" 3
extern int setpgrp (void) ;
# 580 "/usr/local/include/unistd.h" 3
extern __pid_t setsid (void) ;







extern __uid_t getuid (void) ;


extern __uid_t geteuid (void) ;


extern __gid_t getgid (void) ;


extern __gid_t getegid (void) ;




extern int getgroups (int __size, __gid_t __list[]) ;
# 613 "/usr/local/include/unistd.h" 3
extern int setuid (__uid_t __uid) ;




extern int setreuid (__uid_t __ruid, __uid_t __euid) ;




extern int seteuid (__uid_t __uid) ;






extern int setgid (__gid_t __gid) ;




extern int setregid (__gid_t __rgid, __gid_t __egid) ;




extern int setegid (__gid_t __gid) ;






extern __pid_t fork (void) ;






extern __pid_t vfork (void) ;





extern char *ttyname (int __fd) ;



extern int ttyname_r (int __fd, char *__buf, size_t __buflen) ;



extern int isatty (int __fd) ;





extern int ttyslot (void) ;




extern int link (__const char *__from, __const char *__to) ;



extern int symlink (__const char *__from, __const char *__to) ;




extern int readlink (__const char *__restrict __path, char *__restrict __buf,
                     size_t __len) ;



extern int unlink (__const char *__name) ;


extern int rmdir (__const char *__path) ;



extern __pid_t tcgetpgrp (int __fd) ;


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) ;



extern char *getlogin (void) ;
# 717 "/usr/local/include/unistd.h" 3
extern int setlogin (__const char *__name) ;
# 726 "/usr/local/include/unistd.h" 3
# 1 "/usr/local/include/getopt.h" 1 3
# 47 "/usr/local/include/getopt.h" 3
extern char *optarg;
# 61 "/usr/local/include/getopt.h" 3
extern int optind;




extern int opterr;



extern int optopt;
# 145 "/usr/local/include/getopt.h" 3
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts);
# 727 "/usr/local/include/unistd.h" 2 3







extern int gethostname (char *__name, size_t __len) ;






extern int sethostname (__const char *__name, size_t __len) ;



extern int sethostid (long int __id) ;





extern int getdomainname (char *__name, size_t __len) ;
extern int setdomainname (__const char *__name, size_t __len) ;





extern int vhangup (void) ;


extern int revoke (__const char *__file) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
                   size_t __offset, unsigned int __scale) ;





extern int acct (__const char *__name) ;



extern char *getusershell (void) ;
extern void endusershell (void) ;
extern void setusershell (void) ;





extern int daemon (int __nochdir, int __noclose) ;






extern int chroot (__const char *__path) ;



extern char *getpass (__const char *__prompt) ;





extern int fsync (int __fd) ;






extern long int gethostid (void) ;


extern void sync (void) ;




extern int getpagesize (void) __attribute__ ((__const__));




extern int truncate (__const char *__file, __off_t __length) ;
# 841 "/usr/local/include/unistd.h" 3
extern int ftruncate (int __fd, __off_t __length) ;
# 857 "/usr/local/include/unistd.h" 3
extern int getdtablesize (void) ;
# 866 "/usr/local/include/unistd.h" 3
extern int brk (void *__addr) ;





extern void *sbrk (intptr_t __delta) ;
# 887 "/usr/local/include/unistd.h" 3
extern long int syscall (long int __sysno, ...) ;
# 907 "/usr/local/include/unistd.h" 3
extern int lockf (int __fd, int __cmd, __off_t __len) ;
# 938 "/usr/local/include/unistd.h" 3
extern int fdatasync (int __fildes) ;
# 983 "/usr/local/include/unistd.h" 3
extern int pthread_atfork (void (*__prepare) (void),
                           void (*__parent) (void),
                           void (*__child) (void)) ;
# 27 "main.c" 2
# 1 "/usr/local/include/stdlib.h" 1 3
# 25 "/usr/local/include/stdlib.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 26 "/usr/local/include/stdlib.h" 2 3







# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 34 "/usr/local/include/stdlib.h" 2 3
# 94 "/usr/local/include/stdlib.h" 3
typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;
# 133 "/usr/local/include/stdlib.h" 3
extern size_t __ctype_get_mb_cur_max (void) ;



extern double atof (__const char *__nptr) __attribute__ ((__pure__));

extern int atoi (__const char *__nptr) __attribute__ ((__pure__));

extern long int atol (__const char *__nptr) __attribute__ ((__pure__));



__extension__ extern long long int atoll (__const char *__nptr)
             __attribute__ ((__pure__));



extern double strtod (__const char *__restrict __nptr,
                      char **__restrict __endptr) ;
# 163 "/usr/local/include/stdlib.h" 3
extern long int strtol (__const char *__restrict __nptr,
                        char **__restrict __endptr, int __base) ;

extern unsigned long int strtoul (__const char *__restrict __nptr,
                                  char **__restrict __endptr, int __base)
            ;



__extension__
extern long long int strtoq (__const char *__restrict __nptr,
                             char **__restrict __endptr, int __base) ;

__extension__
extern unsigned long long int strtouq (__const char *__restrict __nptr,
                                       char **__restrict __endptr, int __base)
            ;






__extension__
extern long long int strtoll (__const char *__restrict __nptr,
                              char **__restrict __endptr, int __base) ;

__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
                                        char **__restrict __endptr, int __base)
            ;
# 250 "/usr/local/include/stdlib.h" 3
extern double __strtod_internal (__const char *__restrict __nptr,
                                 char **__restrict __endptr, int __group)
            ;
extern float __strtof_internal (__const char *__restrict __nptr,
                                char **__restrict __endptr, int __group)
            ;
extern long double __strtold_internal (__const char *__restrict __nptr,
                                       char **__restrict __endptr,
                                       int __group) ;

extern long int __strtol_internal (__const char *__restrict __nptr,
                                   char **__restrict __endptr,
                                   int __base, int __group) ;



extern unsigned long int __strtoul_internal (__const char *__restrict __nptr,
                                             char **__restrict __endptr,
                                             int __base, int __group) ;




__extension__
extern long long int __strtoll_internal (__const char *__restrict __nptr,
                                         char **__restrict __endptr,
                                         int __base, int __group) ;



__extension__
extern unsigned long long int __strtoull_internal (__const char *
                                                   __restrict __nptr,
                                                   char **__restrict __endptr,
                                                   int __base, int __group)
            ;
# 384 "/usr/local/include/stdlib.h" 3
extern char *l64a (long int __n) ;


extern long int a64l (__const char *__s) __attribute__ ((__pure__));


# 1 "/usr/local/include/sys/types.h" 1 3
# 391 "/usr/local/include/stdlib.h" 2 3






extern long int random (void) ;


extern void srandom (unsigned int __seed) ;





extern char *initstate (unsigned int __seed, char *__statebuf,
                        size_t __statelen) ;



extern char *setstate (char *__statebuf) ;







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
                     int32_t *__restrict __result) ;

extern int srandom_r (unsigned int __seed, struct random_data *__buf) ;

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
                        size_t __statelen,
                        struct random_data *__restrict __buf) ;

extern int setstate_r (char *__restrict __statebuf,
                       struct random_data *__restrict __buf) ;





extern int rand (void) ;

extern void srand (unsigned int __seed) ;



extern int rand_r (unsigned int *__seed) ;







extern double drand48 (void) ;
extern double erand48 (unsigned short int __xsubi[3]) ;


extern long int lrand48 (void) ;
extern long int nrand48 (unsigned short int __xsubi[3]) ;


extern long int mrand48 (void) ;
extern long int jrand48 (unsigned short int __xsubi[3]) ;


extern void srand48 (long int __seedval) ;
extern unsigned short int *seed48 (unsigned short int __seed16v[3]) ;
extern void lcong48 (unsigned short int __param[7]) ;





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
                      double *__restrict __result) ;
extern int erand48_r (unsigned short int __xsubi[3],
                      struct drand48_data *__restrict __buffer,
                      double *__restrict __result) ;


extern int lrand48_r (struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;
extern int nrand48_r (unsigned short int __xsubi[3],
                      struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;


extern int mrand48_r (struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;
extern int jrand48_r (unsigned short int __xsubi[3],
                      struct drand48_data *__restrict __buffer,
                      long int *__restrict __result) ;


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
            ;

extern int seed48_r (unsigned short int __seed16v[3],
                     struct drand48_data *__buffer) ;

extern int lcong48_r (unsigned short int __param[7],
                      struct drand48_data *__buffer) ;
# 527 "/usr/local/include/stdlib.h" 3
extern void *malloc (size_t __size) __attribute__ ((__malloc__));

extern void *calloc (size_t __nmemb, size_t __size)
             __attribute__ ((__malloc__));





extern void *realloc (void *__ptr, size_t __size) __attribute__ ((__malloc__));

extern void free (void *__ptr) ;



extern void cfree (void *__ptr) ;



# 1 "/usr/local/include/alloca.h" 1 3
# 22 "/usr/local/include/alloca.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 23 "/usr/local/include/alloca.h" 2 3


# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 26 "/usr/local/include/alloca.h" 2 3







extern void *alloca (size_t __size) ;
# 547 "/usr/local/include/stdlib.h" 2 3




extern void *valloc (size_t __size) __attribute__ ((__malloc__));
# 561 "/usr/local/include/stdlib.h" 3
extern void abort (void) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) ;




extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
            ;





extern void exit (int __status) __attribute__ ((__noreturn__));
# 587 "/usr/local/include/stdlib.h" 3
extern char *getenv (__const char *__name) ;



extern char *__secure_getenv (__const char *__name) ;





extern int putenv (char *__string) ;





extern int setenv (__const char *__name, __const char *__value, int __replace)
            ;


extern int unsetenv (__const char *__name) ;






extern int clearenv (void) ;
# 623 "/usr/local/include/stdlib.h" 3
extern char *mktemp (char *__template) ;







extern int mkstemp (char *__template) ;
# 650 "/usr/local/include/stdlib.h" 3
extern char *mkdtemp (char *__template) ;




extern int system (__const char *__command) ;
# 672 "/usr/local/include/stdlib.h" 3
extern char *realpath (__const char *__restrict __name,
                       char *__restrict __resolved) ;






typedef int (*__compar_fn_t) (__const void *, __const void *);
# 689 "/usr/local/include/stdlib.h" 3
extern void *bsearch (__const void *__key, __const void *__base,
                      size_t __nmemb, size_t __size, __compar_fn_t __compar);



extern void qsort (void *__base, size_t __nmemb, size_t __size,
                   __compar_fn_t __compar);



extern int abs (int __x) __attribute__ ((__const__));
extern long int labs (long int __x) __attribute__ ((__const__));
# 710 "/usr/local/include/stdlib.h" 3
extern div_t div (int __numer, int __denom)
             __attribute__ ((__const__));
extern ldiv_t ldiv (long int __numer, long int __denom)
             __attribute__ ((__const__));
# 728 "/usr/local/include/stdlib.h" 3
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign) ;




extern char *gcvt (double __value, int __ndigit, char *__buf) ;




extern char *qecvt (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign) ;
extern char *qfcvt (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign, char *__restrict __buf,
                   size_t __len) ;
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
                   int *__restrict __sign, char *__restrict __buf,
                   size_t __len) ;

extern int qecvt_r (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign,
                    char *__restrict __buf, size_t __len) ;
extern int qfcvt_r (long double __value, int __ndigit,
                    int *__restrict __decpt, int *__restrict __sign,
                    char *__restrict __buf, size_t __len) ;






extern int mblen (__const char *__s, size_t __n) ;


extern int mbtowc (wchar_t *__restrict __pwc,
                   __const char *__restrict __s, size_t __n) ;


extern int wctomb (char *__s, wchar_t __wchar) ;



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
                        __const char *__restrict __s, size_t __n) ;

extern size_t wcstombs (char *__restrict __s,
                        __const wchar_t *__restrict __pwcs, size_t __n)
            ;







extern int rpmatch (__const char *__response) ;
# 858 "/usr/local/include/stdlib.h" 3
extern int getloadavg (double __loadavg[], int __nelem) ;
# 28 "main.c" 2
# 1 "/usr/local/include/getopt.h" 1 3
# 47 "/usr/local/include/getopt.h" 3
extern char *optarg;
# 61 "/usr/local/include/getopt.h" 3
extern int optind;




extern int opterr;



extern int optopt;
# 94 "/usr/local/include/getopt.h" 3
struct option
{

  const char *name;





  int has_arg;
  int *flag;
  int val;
};
# 145 "/usr/local/include/getopt.h" 3
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts);





extern int getopt_long (int ___argc, char *const *___argv,
                        const char *__shortopts,
                        const struct option *__longopts, int *__longind);
extern int getopt_long_only (int ___argc, char *const *___argv,
                             const char *__shortopts,
                             const struct option *__longopts, int *__longind);


extern int _getopt_internal (int ___argc, char *const *___argv,
                             const char *__shortopts,
                             const struct option *__longopts, int *__longind,
                             int __long_only);
# 29 "main.c" 2
# 1 "/usr/local/include/string.h" 1 3
# 26 "/usr/local/include/string.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 27 "/usr/local/include/string.h" 2 3






# 1 "/usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.0.1/include/stddef.h" 1 3
# 34 "/usr/local/include/string.h" 2 3



extern void *memcpy (void *__restrict __dest,
                     __const void *__restrict __src, size_t __n) ;


extern void *memmove (void *__dest, __const void *__src, size_t __n)
            ;





extern void *memccpy (void *__restrict __dest, __const void *__restrict __src,
                      int __c, size_t __n)
            ;




extern void *memset (void *__s, int __c, size_t __n) ;


extern int memcmp (__const void *__s1, __const void *__s2, size_t __n)
             __attribute__ ((__pure__));


extern void *memchr (__const void *__s, int __c, size_t __n)
              __attribute__ ((__pure__));
# 77 "/usr/local/include/string.h" 3
extern char *strcpy (char *__restrict __dest, __const char *__restrict __src)
            ;

extern char *strncpy (char *__restrict __dest,
                      __const char *__restrict __src, size_t __n) ;


extern char *strcat (char *__restrict __dest, __const char *__restrict __src)
            ;

extern char *strncat (char *__restrict __dest, __const char *__restrict __src,
                      size_t __n) ;


extern int strcmp (__const char *__s1, __const char *__s2)
             __attribute__ ((__pure__));

extern int strncmp (__const char *__s1, __const char *__s2, size_t __n)
             __attribute__ ((__pure__));


extern int strcoll (__const char *__s1, __const char *__s2)
             __attribute__ ((__pure__));

extern size_t strxfrm (char *__restrict __dest,
                       __const char *__restrict __src, size_t __n) ;
# 120 "/usr/local/include/string.h" 3
extern char *strdup (__const char *__s) __attribute__ ((__malloc__));
# 155 "/usr/local/include/string.h" 3
extern char *strchr (__const char *__s, int __c) __attribute__ ((__pure__));

extern char *strrchr (__const char *__s, int __c) __attribute__ ((__pure__));
# 167 "/usr/local/include/string.h" 3
extern size_t strcspn (__const char *__s, __const char *__reject)
             __attribute__ ((__pure__));


extern size_t strspn (__const char *__s, __const char *__accept)
             __attribute__ ((__pure__));

extern char *strpbrk (__const char *__s, __const char *__accept)
             __attribute__ ((__pure__));

extern char *strstr (__const char *__haystack, __const char *__needle)
             __attribute__ ((__pure__));
# 187 "/usr/local/include/string.h" 3
extern char *strtok (char *__restrict __s, __const char *__restrict __delim)
            ;



extern char *__strtok_r (char *__restrict __s,
                         __const char *__restrict __delim,
                         char **__restrict __save_ptr) ;

extern char *strtok_r (char *__restrict __s, __const char *__restrict __delim,
                       char **__restrict __save_ptr) ;
# 218 "/usr/local/include/string.h" 3
extern size_t strlen (__const char *__s) __attribute__ ((__pure__));
# 229 "/usr/local/include/string.h" 3
extern char *strerror (int __errnum) ;



extern char *strerror_r (int __errnum, char *__buf, size_t __buflen) ;




extern void __bzero (void *__s, size_t __n) ;



extern void bcopy (__const void *__src, void *__dest, size_t __n) ;


extern void bzero (void *__s, size_t __n) ;


extern int bcmp (__const void *__s1, __const void *__s2, size_t __n)
             __attribute__ ((__pure__));


extern char *index (__const char *__s, int __c) __attribute__ ((__pure__));


extern char *rindex (__const char *__s, int __c) __attribute__ ((__pure__));



extern int ffs (int __i) __attribute__ ((__const__));
# 272 "/usr/local/include/string.h" 3
extern int strcasecmp (__const char *__s1, __const char *__s2)
             __attribute__ ((__pure__));


extern int strncasecmp (__const char *__s1, __const char *__s2, size_t __n)
             __attribute__ ((__pure__));
# 294 "/usr/local/include/string.h" 3
extern char *strsep (char **__restrict __stringp,
                     __const char *__restrict __delim) ;
# 30 "main.c" 2
# 1 "/usr/local/include/errno.h" 1 3
# 29 "/usr/local/include/errno.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 30 "/usr/local/include/errno.h" 2 3






# 1 "/usr/local/include/bits/errno.h" 1 3
# 25 "/usr/local/include/bits/errno.h" 3
# 1 "/usr/include/linux/errno.h" 1 3



# 1 "/usr/include/asm/errno.h" 1 3
# 5 "/usr/include/linux/errno.h" 2 3
# 26 "/usr/local/include/bits/errno.h" 2 3
# 36 "/usr/local/include/bits/errno.h" 3
extern int errno;


extern int *__errno_location (void) __attribute__ ((__const__));
# 37 "/usr/local/include/errno.h" 2 3
# 31 "main.c" 2
# 1 "/usr/local/include/error.h" 1 3
# 47 "/usr/local/include/error.h" 3
extern void error (int status, int errnum, const char *format, ...)
     __attribute__ ((__format__ (__printf__, 3, 4)));

extern void error_at_line (int status, int errnum, const char *fname,
                           unsigned int lineno, const char *format, ...)
     __attribute__ ((__format__ (__printf__, 5, 6)));




extern void (*error_print_progname) (void);
# 66 "/usr/local/include/error.h" 3
extern unsigned int error_message_count;



extern int error_one_per_line;
# 32 "main.c" 2

# 1 "/usr/include/redlib/mem.h" 1 3
# 25 "/usr/include/redlib/mem.h" 3
# 1 "/usr/include/redlib/default.h" 1 3
# 29 "/usr/include/redlib/default.h" 3
# 1 "/usr/local/include/features.h" 1 3
# 30 "/usr/include/redlib/default.h" 2 3
# 26 "/usr/include/redlib/mem.h" 2 3

# 1 "/usr/local/include/stdlib.h" 1 3
# 28 "/usr/include/redlib/mem.h" 2 3


extern void _init_mem(void);
extern void _fini_mem(void);
extern void set_mmessage( const char *message);
extern void unset_mmessage(void);
extern void *xcalloc(size_t nmemb, size_t size);
extern void *xmalloc(size_t size);
extern void *xrealloc(void *ptr, size_t size);
# 34 "main.c" 2

# 1 "../include/main.h" 1
# 26 "../include/main.h"
# 1 "../include/default.h" 1
# 27 "../include/main.h" 2






static struct option option_list[] = {
                { "block", 1, ((void *)0), 'b' },
                { "char", 1, ((void *)0), 'c' },



                { ((void *)0), 0, 0, 0 }
};

static const char option_string[] = "b:c:";

static const struct option_help_text {
                char *name;
                char *help;
} option_help[] = {
                { "block", "block device" },
                { "char", "character device" },
                { ((void *)0), ((void *)0) }
};

struct arguments {
                char *idev;
                char *odev;
                int type;
} arg;

static void __attribute__ ((__noreturn__)) usage(const char *prog);
# 36 "main.c" 2

extern const char version[];

int main( argc, argv, envp)
                int argc;
                char *argv[];
                char *envp[];
{
                int opt, option_index = 0;
                struct stat *dev_stat = xcalloc( 0, sizeof(stat));

                if(argc < 2)
                                usage(argv[0]);

                while((opt = getopt_long( argc,
                                                                                argv,
                                                                                option_string,
                                                                                option_list,
                                                                                &option_index)
                                                                ) != -1) {
                                if(opt == -1)
                                                break;
                                switch(opt) {
                                                case 'b':
                                                                if(optarg) {
                                                                                arg.idev = xcalloc(0, strlen(optarg));
                                                                                arg.odev = "/dev/viaductb";
                                                                                arg.type = 1;
                                                                                if(lstat(arg.idev, dev_stat) && ((((dev_stat)) & 0170000) == (0060000))) {
                                                                                                fprintf(stderr, "%s\n", strerror((*__errno_location ())));
                                                                                }
                                                                                break;
                                                                }
                                                case 'c':
                                                                if(optarg) {
                                                                                arg.idev = xcalloc(0, strlen(optarg));
                                                                                arg.odev = "/dev/viaductc";
                                                                                arg.type = 2;
                                                                                break;
                                                                }
                                                case 0:
                                                default:
                                                                usage(argv[0]);
                                }
                }
                return 0;
}

static void __attribute__ ((__noreturn__)) usage(prog)
                const char *prog;
{
                int i;
                printf( "%s\nUsage : %s -%s\n"
                                                "",
                                                version,
                                                prog,
                                                option_string
                                                );
                for(i = 0; i < sizeof(option_list) && option_list[i].name != ((void *)0); i++)
                                printf( "  --%s%s\t%s\n",
                                                                option_list[i].name,
                                                                option_list[i].has_arg?" <arg>\t":"\t",
                                                                option_help[i].help);
                exit(-1);
}
