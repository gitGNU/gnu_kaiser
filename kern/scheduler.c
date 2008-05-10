/*
 * scheduler.h - kernel task scheduler
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

#include <scheduler.h>
#include <errno.h>
#define HACK
#ifdef HACK
#define MA_KERN 0
void *kmalloc (unsigned int x, int y) {
	return (void *) PTR_ERR (ENOMEM);
}

void context_switch (struct task *t) {
}

int gettime () {
	return 5;
}
#endif

link_ptr_t tasks[2];
link_ptr_t *a = tasks, *b = tasks + 1;
struct task *idle_task;
int time;
int firstrun = 1; /* first run is a special case */

/* Place task in schedule queue */
int schedule (task_t *t) {
	link_t *taskl;

	t->timeslice = GENERIC_TIMESLICE;
	taskl = kmalloc (sizeof (*taskl), MA_KERN);
	if (PTR_ISERR (taskl))
		return -ERR_PTR (taskl);
	taskl->task = t;
	taskl->next = a->top;
	if (!a->top)
		a->bottom = taskl;
	else
		a->top->prev = taskl;
	a->top = taskl;
	return 0;
}

/* Run a task */
void sched_invoke () {
	link_t *run;
	link_ptr_t *tmp;
	int dtime = gettime() - time;

	if (firstrun) {
		firstrun = 0;
	} else {
		if (dtime >= a->bottom->task->timeslice) {
			if (!b->top) {
				b->top = a->bottom;
				b->bottom = a->bottom;
			} else {
				a->bottom->next = b->top;
				b->top = a->bottom;
				b->top->next->prev = b->top;
			}
			a->bottom = a->bottom->prev;
			b->top->task->timeslice = GENERIC_TIMESLICE;
		} else {
			a->bottom->task->timeslice -= dtime;
		}
	}
	if (!a->top) {
		tmp = b;
		b = a;
		a = tmp;
	}
	if (!a->top) {
		firstrun = 1;
		context_switch (idle_task);
	} else {
		run = a->top;
		run->next = NULL;
		a->top = a->top->next;
		a->bottom->next = run;
		run->prev = a->bottom;
		a->bottom = run;
		time = gettime();
		context_switch (run->task);
	}
}

/* run task NOW (rude) fuck knows what will happen if you use this with
 * regards to time slicing, please, just don't */
inline void run_task (task_t *t) {
	context_switch (t);
}
