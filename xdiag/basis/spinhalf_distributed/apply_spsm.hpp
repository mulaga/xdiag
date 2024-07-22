#pragma once
#include <xdiag/extern/armadillo/armadillo>
#include <xdiag/operators/op.hpp>
#include <xdiag/parallel/mpi/buffer.hpp>
namespace xdiag::basis::spinhalf_distributed {

template <class basis_t, typename coeff_t>
void apply_spsm_postfix(Op const &op, basis_t const &basis_in,
                        arma::Col<coeff_t> const &vec_in,
                        basis_t const &basis_out,
                        arma::Col<coeff_t> &vec_out) try {
  using bit_t = typename basis_t::bit_t;
  assert(basis_in.size() == vec_in.size());
  assert(basis_out.size() == vec_out.size());
  assert((op.type() == "S+") || (op.type() == "S-"));
  assert(op.size() == 1);
  std::string type = op.type();

  int64_t s = op[0];
  bit_t mask = ((bit_t)1 << s);
  assert(s >= 0);

  assert(op.coupling().is<coeff_t>());
  coeff_t H = op.coupling().as<coeff_t>();

  int64_t n_postfix_bits = basis_in.n_postfix_bits();
  assert(s < n_postfix_bits);

  int64_t idx = 0;
  for (auto prefix : basis_in.prefixes()) {

    auto const &postfixes = basis_in.postfix_states(prefix);
    auto const &lintable = basis_out.postfix_lintable(prefix);

    int64_t idx_prefix = basis_out.prefix_begin(prefix);

    if (type == "S+") {
      for (auto postfix_in : postfixes) {
        if (!(postfix_in & mask)) {
          bit_t postfix_out = postfix_in | mask;
          int64_t idx_out = idx_prefix + lintable.index(postfix_out);
          vec_out(idx_out) += H * vec_in(idx);
        }
        ++idx;
      }
    } else if (type == "S-") {
      for (auto postfix_in : postfixes) {
        if (postfix_in & mask) {
          bit_t postfix_out = postfix_in ^ mask;
          int64_t idx_out = idx_prefix + lintable.index(postfix_out);
          vec_out(idx_out) += H * vec_in(idx);
        }
        ++idx;
      }
    }
  }
} catch (Error const &e) {
  XDIAG_RETHROW(e);
}

template <class basis_t, typename coeff_t>
void apply_spsm_prefix(Op const &op, basis_t const &basis_in,
                       basis_t const &basis_out) try {
  using bit_t = typename basis_t::bit_t;
  assert(basis_in.size() == vec_in.size());
  assert(basis_out.size() == vec_out.size());
  assert((op.type() == "S+") || (op.type() == "S-"));
  assert(op.size() == 1);
  std::string type = op.type();

  int64_t s = op[0];
  assert(s >= 0);

  int64_t n_prefix_bits = basis_in.n_prefix_bits();
  int64_t n_postfix_bits = basis_in.n_postfix_bits();
  assert(s >= n_postfix_bits);

  bit_t mask = ((bit_t)1 << (s - n_postfix_bits));

  assert(op.coupling().is<coeff_t>());
  coeff_t H = op.coupling().as<coeff_t>();

  int64_t buffer_size = basis_in.size_max();
  mpi::buffer.reserve<coeff_t>(buffer_size);
  coeff_t *send_buffer = mpi::buffer.send<coeff_t>();
  coeff_t *recv_buffer = mpi::buffer.recv<coeff_t>();

  // loop through all postfixes
  int64_t idx = 0;
  for (auto postfix : basis_in.postfixes()) {

    auto const &prefixes = basis_in.prefix_states(postfix);
    auto const &lintable = basis_out.prefix_lintable(postfix);
    int64_t idx_postfix = basis_out.postfix_begin(postfix);

    if (type == "S+") {
      for (auto prefix_in : prefixes) {
        if (!(prefix_in & mask)) {
          bit_t prefix_out = prefix_in | mask;
          int64_t idx_out = idx_postfix + lintable.index(prefix_out);
          recv_buffer[idx_out] += H * send_buffer[idx];
        }
        ++idx;
      }

    } else if (type == "S-") {
      for (auto prefix_in : prefixes) {
        if (prefix_in & mask) {
          bit_t prefix_out = prefix_in ^ mask;
          int64_t idx_out = idx_postfix + lintable.index(prefix_out);
          recv_buffer[idx_out] += H * send_buffer[idx];
        }
        ++idx;
      }
    }
  }
} catch (Error const &e) {
  XDIAG_RETHROW(e);
}
} // namespace xdiag::basis::spinhalf_distributed
