/*
 * scheduler.h - structs
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

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include <asm/stddef.h>

#define GENERIC_TIMESLICE 7	/* 7 pwns 5 4reel */

struct link {
        struct task *task;
        struct link *next, *prev;
};
typedef struct link link_t;
struct link_ptr {
        struct link *top;
        struct link *bottom;
};
typedef struct link_ptr link_ptr_t;
struct task {
        int priority;
	int timeslice;
};
typedef struct task task_t;

void sched_invoke(void);
void run_task(task_t * t);
int schedule(task_t *t);

#endif /* !__SCHEDULER_H__ */
