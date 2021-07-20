/* Copyright (C) 2021 David Price - All Rights Reserved
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

#ifndef HEPHAIST_OS_KERNEL_KLIBC_STDIO_SPRINTF_H
#define HEPHAIST_OS_KERNEL_KLIBC_STDIO_SPRINTF_H

namespace kernel::lib {

    template<typename Arg>
    int32_t sprintf(char * buffer, const char * format, Arg arg) {
        int32_t count { 0 };

        while(*format != '\0') {

            if(*format != '%') {
                *buffer = *format;
                format++;
                buffer++;
                count++;
                continue;
            }

            switch (format[1]) {
                case 'c':
                    *buffer = static_cast<char>(arg);
                    format += 2;
                    buffer++;
                    count++;
                    break;
                default:
                    return -1;
            }
        }
        *buffer = '\0';
        return count;
    }

    template<typename Arg, typename ...Args>
    int32_t sprintf(char * buffer, const char * format, Arg arg, Args ...args) {
        int32_t count { 0 };

        while(*format != '\0') {

            if(*format != '%') {
                *buffer = *format;
                format++;
                buffer++;
                count++;
                continue;
            }

            switch (format[1]) {
                case 'c':
                    *buffer = static_cast<char>(arg);
                    format += 2;
                    buffer++;
                    count++;
                    break;

                case '%':
                    *buffer = '%';
                    format += 2;
                    buffer++;
                    count++;
                    break;

                default:
                    return -1;
            }

            return count + sprintf(buffer, format, args...);
        }
        *buffer = '\0';
        return count;
    }
}

#endif // HEPHAIST_OS_KERNEL_KLIBC_STDIO_SPRINTF_H
