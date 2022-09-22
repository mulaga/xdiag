#pragma once

#include "extern/armadillo/armadillo"

#include <hydra/blocks/electron/electron.h>
#include <hydra/blocks/spinhalf/spinhalf.h>
#include <hydra/blocks/tj/tj.h>
#include <hydra/linalg/lanczos/tmatrix.h>
#include <hydra/operators/bondlist.h>
#include <hydra/states/state.h>
#include <hydra/symmetries/permutation.h>
#include <hydra/symmetries/permutation_group.h>
#include <hydra/symmetries/representation.h>

namespace hydra::utils {

void PrintPretty(const char *identifier, int number);
void PrintPretty(const char *identifier, uint32_t number);
void PrintPretty(const char *identifier, uint64_t number);
void PrintPretty(const char *identifier, int64_t number);
void PrintPretty(const char *identifier, double number);
void PrintPretty(const char *identifier, complex number);

void PrintPretty(const char *identifier, Bond const &bond);
void PrintPretty(const char *identifier, BondList const &bondlist);
void PrintPretty(const char *identifier, Permutation const &perm);
void PrintPretty(const char *identifier, PermutationGroup const &group);
void PrintPretty(const char *identifier, Representation const &irrep);

template <typename bit_t>
void PrintPretty(const char *identifier, Spinhalf<bit_t> const &block);
template <typename bit_t>
void PrintPretty(const char *identifier, tJ<bit_t> const &block);
template <typename bit_t>
void PrintPretty(const char *identifier, Electron<bit_t> const &block);

void PrintPretty(const char *identifier, const arma::Mat<float> &mat);
void PrintPretty(const char *identifier, const arma::Mat<double> &mat);
void PrintPretty(const char *identifier,
                 const arma::Mat<std::complex<float>> &mat);
void PrintPretty(const char *identifier,
                 const arma::Mat<std::complex<double>> &mat);

void PrintPretty(const char *identifier, const arma::Col<float> &vec);
void PrintPretty(const char *identifier, const arma::Col<double> &vec);
void PrintPretty(const char *identifier,
                 const arma::Col<std::complex<float>> &vec);
void PrintPretty(const char *identifier,
                 const arma::Col<std::complex<double>> &vec);

void PrintPretty(const char *identifier, Tmatrix const &tmat);

template <typename coeff_t, class Block>
void PrintPretty(const char *identifier, State<coeff_t, Block> const &state) {
  printf("%s:\n", identifier);
  if constexpr (is_real<coeff_t>()) {
    printf("  real state\n");
  } else {
    printf("  cplx state\n");
  }
  std::stringstream ss;
  ss.imbue(std::locale("en_US.UTF-8"));
  ss << state.size();
  printf("  dimension: %s\n", ss.str().c_str());
  printf("  norm     : %.9e\n", arma::norm(state.vector()));
  PrintPretty((std::string(identifier) + std::string(".block()")).c_str(),
              state.block());
}

} // namespace hydra::utils
