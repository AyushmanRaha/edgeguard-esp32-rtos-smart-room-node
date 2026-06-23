#pragma once

#include <stddef.h>
#include <stdint.h>

class EdgeGuardEventLog {
 public:
  static constexpr size_t kCapacity = 20;
  static constexpr size_t kMaxEventLength = 96;

  void push(const char* message);
  size_t count() const;
  const char* get(size_t chronologicalIndex) const;
  void clear();

 private:
  char events_[kCapacity][kMaxEventLength] = {};
  size_t head_ = 0;
  size_t count_ = 0;
};
