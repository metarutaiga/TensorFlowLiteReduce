/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <windows.h>

#include <stdarg.h>

#include <cstdio>

#include "tensorflow/lite/minimal_logging.h"

namespace tflite {
namespace logging_internal {

void MinimalLogger::LogFormatted(LogSeverity severity, const char* format,
                                 va_list args) {
  const int size = 4095;
  char buffer[size + 1];
  int index = 0;
  index += snprintf(buffer + index, size - index, "%s: ", GetSeverityName(severity));
  index += vsnprintf(buffer + index, size - index, format, args);
  OutputDebugStringA(buffer);
  OutputDebugStringA("\n");
}

}  // namespace logging_internal
}  // namespace tflite
