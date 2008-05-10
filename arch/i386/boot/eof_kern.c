/*
 * kern_eof.c - Adds word 0x0E0F to the last 2 bytes of the last sector
 * 		of the kernel, so boot1.S knows it's the last sector.
 * Copyright (C) 2008 John 'Ykstort' Doyle
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
#include <stdio.h>
#include <stdlib.h>

#define SECTOR_SZ 512
#define LAST_SEC  0x0E0F
#define ALIGN(x,y) ((x&~(y-1))+y)

int main (int argc, char **argv) {
	long ksz;
	short eof;
	FILE *kelf;

	if (argc < 2) {
		fprintf (stderr, "Usage: %s file\n", argv[0]);
		return EXIT_FAILURE;
	}
	kelf = fopen (argv[1], "rb+");
	if (!kelf) {
		perror (argv[1]);
		return EXIT_FAILURE;
	}
	if (fseek (kelf, 0, SEEK_END) < 0) {
		perror (argv[1]);
		return EXIT_FAILURE;
	}
	if ((ksz = ftell (kelf)) < 0) {
		perror (argv[1]);
		return EXIT_FAILURE;
	}
	eof = LAST_SEC;
	if (fseek (kelf, ALIGN (ksz, SECTOR_SZ) - sizeof (eof), SEEK_SET) < 0) {
		perror (argv[1]);
		return EXIT_FAILURE;
	}
	if (fwrite (&eof, sizeof (eof), 1, kelf) == EOF) {
		perror (argv[1]);
		return EXIT_FAILURE;
	}
	fclose (kelf);
	return EXIT_SUCCESS;
}
