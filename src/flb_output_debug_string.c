/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2015-2022 The Fluent Bit Authors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <fluent-bit/flb_time.h>
#include <fluent-bit/flb_output_debug_string.h>

void flb_output_debug_string(const char *format, ...)
{
    char buffer[256];
    int length;
    va_list args;
    struct flb_time tms;
    struct tm tm;

    flb_time_get(&tms);
    gmtime_r(&tms.tm.tv_sec, &tm);
    length = strftime(buffer, sizeof(buffer) - 2, "[%Y-%m-%d %H:%M:%S] ", &tm);

    length += snprintf(buffer + length, sizeof(buffer) - 2 - length, "[%x.%x] ", GetCurrentProcessId(), GetCurrentThreadId());

    va_start(args, format);
    length += vsnprintf(buffer + length, sizeof(buffer) - 2 - length, format, args);
    va_end(args);

    buffer[length++] = '\n';
    buffer[length++] = '\0';

    OutputDebugStringA(buffer);
}
