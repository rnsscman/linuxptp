/**
 * @file missing.h
 * @note Copyright (C) 2011 Richard Cochran <richardcochran@gmail.com>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * When glibc offers the syscall, this will go away.
 */
#ifndef HAVE_MISSING_H
#define HAVE_MISSING_H

#include <time.h>
#include <sys/syscall.h>
#include <sys/timex.h>
#include <unistd.h>

#ifndef ADJ_NANO
#define ADJ_NANO 0x2000
#endif

#ifndef ADJ_SETOFFSET
#define ADJ_SETOFFSET 0x0100
#endif

#ifndef CLOCK_INVALID
#define CLOCK_INVALID -1
#endif

#define CLOCKFD 3
#define FD_TO_CLOCKID(fd)	((~(clockid_t) (fd) << 3) | CLOCKFD)
#define CLOCKID_TO_FD(clk)	((unsigned int) ~((clk) >> 3))

static inline int clock_adjtime(clockid_t id, struct timex *tx)
{
	return syscall(__NR_clock_adjtime, id, tx);
}

#ifndef __uClinux__

#include <sys/timerfd.h>

#else

static inline int timerfd_create(int clockid, int flags)
{
	return syscall(__NR_timerfd_create, clockid, flags);
}

static inline int timerfd_settime(int fd, int flags,
				  const struct itimerspec *new_value,
				  struct itimerspec *old_value)
{
	return syscall(__NR_timerfd_settime, fd, flags, new_value, old_value);
}

#endif

#endif
