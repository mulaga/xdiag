#pragma once

namespace xdiag {

class U1 {
public:
  inline bool operator==(U1 const &rhs) const {
    (void)rhs;
    return true;
  }
  inline bool operator!=(U1 const &rhs) const { return !operator==(rhs); }
};

} // namespace xdiag
