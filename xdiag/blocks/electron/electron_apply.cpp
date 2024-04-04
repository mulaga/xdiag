#include "electron_apply.h"

#include <xdiag/algebra/fill.h>
#include <xdiag/blocks/electron/compile.h>
#include <xdiag/blocks/electron/dispatch.h>

namespace xdiag {

template <typename coeff_t>
void apply(BondList const &bonds, Electron const &block_in,
           arma::Col<coeff_t> const &vec_in, Electron const &block_out,
           arma::Col<coeff_t> &vec_out) try {
  vec_out.zeros();

  BondList bondsc = electron::compile(bonds, 1e-12);
  auto fill = [&](int64_t idx_in, int64_t idx_out, coeff_t val) {
    return fill_apply(vec_in, vec_out, idx_in, idx_out, val);
  };
  electron::dispatch<coeff_t>(bondsc, block_in, block_out, fill);
} catch (...) {
  XDiagRethrow("Cannot apply bonds on vector for \"Electron\" block");
}

template void apply<double>(BondList const &, Electron const &,
                            arma::Col<double> const &, Electron const &,
                            arma::Col<double> &);

template void apply<complex>(BondList const &, Electron const &,
                             arma::Col<complex> const &, Electron const &,
                             arma::Col<complex> &);

} // namespace xdiag
