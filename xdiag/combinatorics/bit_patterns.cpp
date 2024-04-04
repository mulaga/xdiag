#include "bit_patterns.h"
#include "binomial.h"

namespace xdiag::combinatorics {

template <typename bit_t>
bit_t get_nth_pattern(int64_t n, int64_t n_sites, int64_t n_upspins) {
  bit_t state = 0;
  bit_t counter = n;
  for (int64_t n_varying_bits = n_upspins - 1; n_varying_bits >= 0;
       --n_varying_bits) {
    bit_t n_combinations = 0;
    for (int64_t n_allowed_pos = n_varying_bits; n_allowed_pos <= n_sites;
         ++n_allowed_pos) {
      n_combinations += binomial(n_allowed_pos, n_varying_bits);

      if (n_combinations > counter) {
        counter -= n_combinations - binomial(n_allowed_pos, n_varying_bits);
        state |= (bit_t(1) << n_allowed_pos);
        break;
      }
    }
  }
  return state;
}

template <typename bit_t>
int64_t get_n_for_pattern(bit_t pattern, int64_t n_sites, int64_t n_upspins) {
  int64_t n = 0;
  bit_t workpattern = pattern;
  for (int64_t n_varying_bits = n_upspins - 1; n_varying_bits >= 0;
       --n_varying_bits) {
    for (int64_t i = 0; i <= n_sites; ++i) {
      // MSB is at 2^i
      if ((bit_t(1) << (i + 1)) > workpattern) {
        n += binomial(i, n_varying_bits + 1);
        workpattern ^= (bit_t(1) << i);
        break;
      }
    }
  }
  return n;
}

template uint16_t get_nth_pattern<uint16_t>(int64_t n, int64_t n_sites,
                                            int64_t n_upspins);
template uint32_t get_nth_pattern<uint32_t>(int64_t n, int64_t n_sites,
                                            int64_t n_upspins);
template uint64_t get_nth_pattern<uint64_t>(int64_t n, int64_t n_sites,
                                            int64_t n_upspins);

template int64_t get_n_for_pattern<uint16_t>(uint16_t pattern, int64_t n_sites,
                                             int64_t n_upspins);
template int64_t get_n_for_pattern<uint32_t>(uint32_t pattern, int64_t n_sites,
                                             int64_t n_upspins);
template int64_t get_n_for_pattern<uint64_t>(uint64_t pattern, int64_t n_sites,
                                             int64_t n_upspins);
} // namespace xdiag::combinatorics
