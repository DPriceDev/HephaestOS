// Copyright (C) 2022 David Price - All Rights Reserved
// This file is part of HephaistOS.
//
// HephaistOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaistOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAIST_OS_USER_LIB_C_UNISTD_H
#define HEPHAIST_OS_USER_LIB_C_UNISTD_H

/* pid_t is the definition of a process ID */
typedef signed int pid_t;

/**
 * Stubbed fork.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
pid_t fork(void);

/**
 * Stubbed execv.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int execv(const char *, char *const []);

/**
 * Stubbed execve.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int execve(const char *, char *const [], char *const []);

/**
 * Stubbed execvp.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
int execvp(const char *, char *const []);

#endif // HEPHAIST_OS_USER_LIB_C_UNISTD_H