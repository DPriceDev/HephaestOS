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

#ifndef HEPHAIST_OS_KERNEL_LIB_STDIO_SPRINTF_H
#define HEPHAIST_OS_KERNEL_LIB_STDIO_SPRINTF_H

namespace kernel::lib {

    /**
     * TODO: Comment
     * TODO: Move to strings.h
     * @param buffer
     * @param length
     * @return
     */
    char * reverseBuffer(char * buffer, uint32_t length) {
        for (uint32_t index = 0; index < length / 2; ++index) {
            char character = buffer[index];
            buffer[index] = buffer[length - index - 1];
            buffer[length - index - 1] = character;
        }
        return buffer;
    }

    /**
     * TODO: Comment
     * TODO: Move to stdlib.h
     * @param value
     * @param buffer
     * @param base
     * @return
     */
    char * convertNumberToString(
            int32_t value,
            char * buffer,
            int32_t base
    ) {
        char * bufferStart = buffer;
        auto shouldAddMinus = value < 0 && base == 10;
        if(shouldAddMinus) {
            value *= -1;
        }

        do {
            const auto number = value % base;
            *buffer = static_cast<char>(number + 48);
            ++buffer;
            value /= base;
        } while (value);

        if(shouldAddMinus) {
            *buffer = '-';
            ++buffer;
        }

        reverseBuffer(bufferStart, static_cast<uint32_t>(buffer - bufferStart));
        return buffer;
    }

    /**
     * TODO: Comment
     * TODO: Should be in common or lowest printf header?
     * @tparam Type
     * @param buffer
     * @param format
     * @param arg
     * @return
     */
    template<typename Type>
    int32_t formatBuffer(char* buffer, const char format, Type arg) {
        switch (format) {
            case 'c':
                *buffer = static_cast<char>(arg);
                return 1;

            case '%':
                *buffer = '%';
                return 1;

            case 'i':
            case 'd':
                return static_cast<int32_t>(
                        convertNumberToString(
                            static_cast<int32_t>(arg),
                            buffer,
                            10
                        ) - buffer
                );

            case 'u':
                return static_cast<int32_t>(
                        convertNumberToString(
                                static_cast<uint32_t>(arg),
                                buffer,
                                10
                        ) - buffer
                );


            case 'n':
                return 0;

            default:
                return -1;
        }
    }

    /**
     * TODO: Comment
     * @tparam Arg
     * @param buffer
     * @param format
     * @param arg
     * @return
     */
    template<typename Arg>
    int32_t sprintf(char * buffer, const char * format, Arg arg) {
        int32_t count { 0 };
        while(*format != '\0') {

            //
            if(*format != '%') {
                *buffer = *format;
                ++format;
                ++buffer;
                ++count;
                continue;
            }

            //
            auto added = formatBuffer(buffer, format[1], arg);
            if(added < 0) {
                return added;
            }

            count += added;
            buffer += added;
            format += 2;
        }

        //
        *buffer = '\0';
        return count;
    }

    /**
     * TODO: Comment
     * @tparam Arg
     * @tparam Args
     * @param buffer
     * @param format
     * @param arg
     * @param args
     * @return
     */
    template<typename Arg, typename ...Args>
    int32_t sprintf(char * buffer, const char * format, Arg arg, Args ...args) {
        int32_t count { 0 };

        while(*format != '\0') {

            //
            if(*format != '%') {
                *buffer = *format;
                ++format;
                ++buffer;
                ++count;
                continue;
            }

            //
            auto added = formatBuffer(buffer, format[1], arg);
            if(added < 0) {
                return added;
            }

            count += added;
            buffer += added;
            format += 2;

            //
            if(*(format-1) != '%' && *(format-1) != 'n') {
                return count + sprintf(buffer, format, args...);
            }
        }

        //
        *buffer = '\0';
        return count;
    }
}

#endif // HEPHAIST_OS_KERNEL_LIB_STDIO_SPRINTF_H
