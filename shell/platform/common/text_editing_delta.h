// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_COMMON_TEXT_EDITING_DELTA_H_
#define FLUTTER_SHELL_PLATFORM_COMMON_TEXT_EDITING_DELTA_H_
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <codecvt>
#include <string>

#include "flutter/shell/platform/common/text_range.h"

namespace flutter {

/// A change in the state of an input field.
struct TextEditingDelta {
  TextEditingDelta(const std::u16string& text_before_change,
                   TextRange range,
                   const std::u16string& text);

  TextEditingDelta(const std::string& text_before_change,
                   TextRange range,
                   const std::string& text);

  TextEditingDelta(const std::u16string& text);

  TextEditingDelta(const std::string& text);

  virtual ~TextEditingDelta() = default;

  /// Get the old_text_ value.
  ///
  /// All strings are stored as UTF16 but converted to UTF8 when accessed.
  std::string old_text() const { return Utf16ToUtf8(old_text_); }

  /// Get the delta_text value.
  ///
  /// All strings are stored as UTF16 but converted to UTF8 when accessed.
  std::string delta_text() const { return Utf16ToUtf8(delta_text_); }

  /// Get the delta_start_ value.
  int delta_start() const { return delta_start_; }

  /// Get the delta_end_ value.
  int delta_end() const { return delta_end_; }

  bool operator==(const TextEditingDelta& rhs) const {
    return old_text_ == rhs.old_text_ && delta_text_ == rhs.delta_text_ &&
           delta_start_ == rhs.delta_start_ && delta_end_ == rhs.delta_end_;
  }

  bool operator!=(const TextEditingDelta& rhs) const { return !(*this == rhs); }

  TextEditingDelta(const TextEditingDelta& other) = default;

  TextEditingDelta& operator=(const TextEditingDelta& other) = default;

 private:
  std::u16string old_text_;
  std::u16string delta_text_;
  int delta_start_;
  int delta_end_;

  void set_old_text(const std::u16string& old_text) { old_text_ = old_text; }

  void set_delta_text(const std::u16string& delta_text) {
    delta_text_ = delta_text;
  }

  void set_delta_start(int delta_start) { delta_start_ = delta_start; }

  void set_delta_end(int delta_end) { delta_end_ = delta_end; }

  // Given a UTF16-encoded string, returns the string encoded in UTF8.
  static std::string Utf16ToUtf8(const std::u16string& string) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>
        utf8_converter;
    return utf8_converter.to_bytes(string);
  }

  // Given a UTF8-encoded string, returns the string encoded in UTF16.
  static std::u16string Utf8ToUtf16(const std::string& string) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>
        utf16_converter;
    return utf16_converter.from_bytes(string);
  }
};

}  // namespace flutter

#endif  // FLUTTER_SHELL_PLATFORM_COMMON_TEXT_EDITING_DELTA_H_
