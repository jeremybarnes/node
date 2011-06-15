/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "../uv.h"
#include "task.h"
#include <string.h>

#define PATHMAX 1024
extern char executable_path[];

TEST_IMPL(get_currentexe) {
  char buffer[PATHMAX];
  size_t size;
  char* match;
  int r;

  size = sizeof(buffer) / sizeof(buffer[0]);
  r = uv_get_exepath(buffer, &size);
  ASSERT(!r);

  match = strstr(buffer, executable_path);
  /* Verify that the path returned from uv_get_exepath is a subdirectory of executable_path */
  ASSERT(match && !strcmp(match, executable_path));
  ASSERT(size == strlen(buffer));

  /* Negative tests */
  size = sizeof(buffer) / sizeof(buffer[0]);
  r = uv_get_exepath(NULL, &size);
  ASSERT(r == -1);

  r = uv_get_exepath(buffer, NULL);
  ASSERT(r == -1);

  return 0;
}
