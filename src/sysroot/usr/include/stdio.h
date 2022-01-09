/* Copyright (C) 2022 David Price - All Rights Reserved
 * This file is part of HephaistOS.
 *
 * HephaistOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaistOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HEPHAIST_OS_USER_LIB_C_STDIO_H
#define HEPHAIST_OS_USER_LIB_C_STDIO_H

#include <stdarg.h>

/**
 * size_t is the maximum size an object could be.
 */
typedef long unsigned int size_t;

/* */
typedef int* FILE;

/* */
FILE stderr;

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int fclose(FILE *stream);

FILE *fopen(const char *filename, const char *mode);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

int fseek(FILE *stream, long int offset, int whence);

long int ftell(FILE *stream);

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

void setbuf(FILE *stream, char *buffer);

int vfprintf(FILE *stream, const char *format, va_list arg);

/**
 * Stubbed fflush.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int fflush(FILE *stream);

/**
 * Stubbed fprintf.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int fprintf(FILE *stream, const char *format, ...);


#endif // HEPHAIST_OS_USER_LIB_C_STDIO_H