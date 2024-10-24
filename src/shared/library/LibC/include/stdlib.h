// Copyright (C) 2023 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAEST_OS_USER_LIB_C_STDLIB_H
#define HEPHAEST_OS_USER_LIB_C_STDLIB_H

/**
 * size_t is the maximum size an object could be.
 */
typedef long unsigned int size_t;

/**
 * Stubbed Malloc.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 * @param size
 * @return
 */
void* malloc(size_t size);

/**
 * Stubbed Calloc.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 * @param num
 * @param size
 * @return
 */
void* calloc(size_t num, size_t size);

/**
 * Stubbed free.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
void free(void* ptr);

/**
 * Stubbed Abort.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
void abort(void);

/**
 * Stubbed atexit.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int atexit(void (*func)(void));

/**
 * Stubbed exit.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
void exit(int exit_code);

/**
 * Stubbed atoi.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int atoi(const char* str);

/**
 * Stubbed getenv.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
char* getenv(const char* name);

/**
 * Stubbed abs.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int abs(int n);

#endif// HEPHAEST_OS_USER_LIB_C_STDLIB_H
