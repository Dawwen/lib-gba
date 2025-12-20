/*
 mgba.h
 Copyright (c) 2016 Jeffrey Pfau

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef MGBA_H
#define MGBA_H

#ifdef __cplusplus
extern "C" {
#endif

#define MGBA_LOG_FATAL 0
#define MGBA_LOG_ERROR 1
#define MGBA_LOG_WARN 2
#define MGBA_LOG_INFO 3
#define MGBA_LOG_DEBUG 4

bool mgba_open(void);
void mgba_close(void);

void mgba_printf(int level, const char* string, ...);
bool mgba_console_open(void);

#if defined(__cplusplus) && defined(__GNUC__)
#define LOG_FUNC_NAME __PRETTY_FUNCTION__
#else
#define LOG_FUNC_NAME __func__
#endif

#define LOG_ERROR(fmt, ...) mgba_printf(MGBA_LOG_ERROR, "%s: " fmt, LOG_FUNC_NAME, ##__VA_ARGS__);
#define LOG_WARNING(fmt, ...) mgba_printf(MGBA_LOG_WARN, "%s: " fmt, LOG_FUNC_NAME, ##__VA_ARGS__);
#define LOG_DEBUG(fmt, ...) mgba_printf(MGBA_LOG_DEBUG, "%s: " fmt, LOG_FUNC_NAME, ##__VA_ARGS__);
#define LOG_INFO(fmt, ...) mgba_printf(MGBA_LOG_INFO, "%s: " fmt, LOG_FUNC_NAME, ##__VA_ARGS__);

#ifdef __cplusplus
}
#endif



#endif