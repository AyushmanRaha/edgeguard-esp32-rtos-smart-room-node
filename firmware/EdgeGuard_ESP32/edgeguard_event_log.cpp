#include "edgeguard_event_log.h"

#include <string.h>

void EdgeGuardEventLog::push(const char* message) {
  if (message == nullptr) {
    message = "";
  }
  strncpy(events_[head_], message, kMaxEventLength - 1);
  events_[head_][kMaxEventLength - 1] = '\0';
  head_ = (head_ + 1) % kCapacity;
  if (count_ < kCapacity) {
    ++count_;
  }
}

size_t EdgeGuardEventLog::count() const { return count_; }

const char* EdgeGuardEventLog::get(size_t chronologicalIndex) const {
  if (chronologicalIndex >= count_) {
    return "";
  }
  const size_t start = (head_ + kCapacity - count_) % kCapacity;
  return events_[(start + chronologicalIndex) % kCapacity];
}

void EdgeGuardEventLog::clear() {
  head_ = 0;
  count_ = 0;
  for (size_t i = 0; i < kCapacity; ++i) {
    events_[i][0] = '\0';
  }
}
