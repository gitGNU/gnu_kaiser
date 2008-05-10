/*
 * limits.h - define standard architecture limits
 *
 * Copyright (C) 2008 Andrew 'Seadog' Etches
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __ASM_LIMITS_H__
#define __ASM_LIMITS_H__

#define IO_LISTIO_MAX
#define AIO_MAX
#define AIO_PRIO_DELTA_MAX
#define ARG_MAX
#define ATEXIT_MAX
#define CHILD_MAX
#define DELAYTIMER_MAX
#define HOST_NAME_MAX
#define IOV_MAX
#define LOGIN_NAME_MAX
#define MQ_OPEN_MAX
#define MQ_PRIO_MAX
#define OPEN_MAX
#define PAGESIZE
#define PAGE_SIZE PAGESIZE
#define PTHREAD_DESTRUCTOR_ITERATIONS
#define PTHREAD_KEYS_MAX
#define PTHREAD_STACK_MIN
#define PTHREAD_THREADS_MAX
#define RE_DUP_MAX
#define RTSIG_MAX
#define SEM_NSEMS_MAX
#define SEM_VALUE_MAX
#define SIGQUEUE_MAX
#define SS_REPL_MAX
#define STREAM_MAX
#define SYMLOOP_MAX
#define TIMER_MAX
#define TRACE_EVENT_NAME_MAX
#define TRACE_NAME_MAX
#define TRACE_SYS_MAX
#define TRACE_USER_EVENT_MAX
#define TTY_NAME_MAX
#define TZNAME_MAX
#define FILESIZEBITS
#define LINK_MAX
#define MAX_CANON
#define MAX_INPUT
#define NAME_MAX
#define PATH_MAX
#define PIPE_BUF
#define POSIX_ALLOC_SIZE_MIN
#define POSIX_REC_INCR_XFER_SIZE
#define POSIX_REC_MAX_XFER_SIZE
#define POSIX_REC_MIN_XFER_SIZE
#define POSIX_REC_XFER_ALIGN
#define SYMLINK_MAX
#define BC_BASE_MAX
#define BC_DIM_MAX
#define BC_SCALE_MAX
#define BC_STRING_MAX
#define CHARCLASS_NAME_MAX
#define COLL_WEIGHTS_MAX
#define EXPR_NEST_MAX
#define LINE_MAX
#define NGROUPS_MAX
#define RE_DUP_MAX
#define _POSIX_CLOCKRES_MIN
#define _POSIX_AIO_LISTIO_MAX 2
#define _POSIX_AIO_MAX 1
#define _POSIX_ARG_MAX 4096
#define _POSIX_CHILD_MAX 6
#define _POSIX_DELAYTIMER_MAX 32
#define _POSIX_HOST_NAME_MAX
#define _POSIX_LINK_MAX 8
#define _POSIX_LOGIN_NAME_MAX 9
#define _POSIX_MAX_CANON 255
#define _POSIX_MAX_INPUT 255 
#define _POSIX_MQ_OPEN_MAX 8
#define _POSIX_MQ_PRIO_MAX 32
#define _POSIX_NAME_MAX 14
#define _POSIX_NGROUPS_MAX 0
#define _POSIX_OPEN_MAX 16
#define _POSIX_PATH_MAX 255
#define _POSIX_PIPE_BUF 512
#define _POSIX_RE_DUP_MAX 
#define _POSIX_RTSIG_MAX 8
#define _POSIX_SEM_NSEMS_MAX 256
#define _POSIX_SEM_VALUE_MAX 32767
#define _POSIX_SIGQUEUE_MAX 32
#define _POSIX_STREAM_MAX 8
#define _POSIX_SS_REPL_MAX 
#define _POSIX_SYMLINK_MAX
#define _POSIX_SYMLOOP_MAX
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS 4
#define _POSIX_THREAD_KEYS_MAX 128
#define _POSIX_THREAD_THREADS_MAX 64
#define _POSIX_TIMER_MAX 32
#define _POSIX_TRACE_EVENT_NAME_MAX
#define _POSIX_TRACE_NAME_MAX
#define _POSIX_TRACE_SYS_MAX 
#define _POSIX_TRACE_USER_EVENT_MAX
#define _POSIX_TTY_NAME_MAX 9
#define _POSIX_TZNAME_MAX 3
#define _POSIX2_BC_BASE_MAX 99
#define _POSIX2_BC_DIM_MAX 2048
#define _POSIX2_BC_SCALE_MAX 99
#define _POSIX2_BC_STRING_MAX 1000
#define _POSIX2_CHARCLASS_NAME_MAX
#define _POSIX2_COLL_WEIGHTS_MAX 2
#define _POSIX2_EXPR_NEST_MAX 32
#define _POSIX2_LINE_MAX 2048
#define _XOPEN_IOV_MAX 16
#define _XOPEN_NAME_MAX
#define _XOPEN_PATH_MAX
#define CHAR_BIT 8 
#define CHAR_MAX 255
#define CHAR_MIN 0
#define INT_MAX 2147483647
#define LONG_BIT 64
#define LONG_MAX 9223372036854775807L
#define MB_LEN_MAX 2
#define SCHAR_MAX 127
#define SHRT_MAX 32767
#define SSIZE_MAX LONG_MAX
#define _POSIX_SSIZE_MAX LONG_MAX
#define UCHAR_MAX 255
#define UINT_MAX 4294967295
#define ULONG_MAX 18446744073709551615UL
#define USHRT_MAX 65535
#define WORD_BIT 64
#define INT_MIN (-INT_MAX -1)
#define LONG_MIN (-LONG_MAX -1)
#define SCHAR_MIN (-SCHAR_MAX -1)
#define SHRT_MIN (-SHRT_MAX -1)
#define LLONG_MAX 9223372036854775807LL
#define LLONG_MIN (-LLONG_MAX -1)
#define ULLONG_MAX 18446744073709551615ULL
#define NL_ARGMAX
#define NL_LANGMAX
#define NL_MSGMAX
#define NL_NMAX
#define NL_SETMAX
#define NL_TEXTMAX
#define NZERO
#define TMP_MAX 10000

#endif
