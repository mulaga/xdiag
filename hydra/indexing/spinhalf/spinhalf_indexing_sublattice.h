#pragma once

#include <lila/external/gsl/span>
#include <unordered_map>

#include <hydra/common.h>
#include <hydra/symmetries/group_action/group_action_sublattice.h>
#include <hydra/symmetries/permutation_group.h>
#include <hydra/symmetries/representation.h>

namespace hydra::indexing {

constexpr int maximum_prefix_bits = 27;

template <typename bit_t, int n_sublat> class SpinhalfIndexingSublattice {
public:
  SpinhalfIndexingSublattice() = default;
  SpinhalfIndexingSublattice(int n_sites, PermutationGroup permutation_group,
                             Representation irrep);
  SpinhalfIndexingSublattice(int n_sites, int n_up,
                             PermutationGroup permutation_group,
                             Representation irrep);

  inline int n_sites() const { return n_sites_; }
  inline bool sz_conserved() const { return sz_conserved_; }
  inline int n_up() const { return n_up_; }
  GroupActionSublattice<bit_t, n_sublat> const &group_action() const {
    return group_action_;
  }
  Representation const &irrep() const { return irrep_; }
  inline idx_t size() const { return reps_.size(); }

  inline bit_t state(idx_t idx) const { return reps_[idx]; }
  inline bit_t representative(bit_t state) const {
    return group_action_.representative(state);
  }
  inline double norm(idx_t idx) const { return norms_[idx]; }

  idx_t index(bit_t state) const;
  std::pair<idx_t, int> index_sym(bit_t raw_state) const;
  std::pair<idx_t, gsl::span<int const>> index_syms(bit_t raw_state) const;

private:
  int n_sites_;
  bool sz_conserved_;
  int n_up_;
  int n_postfix_bits_;

  GroupActionSublattice<bit_t, n_sublat> group_action_;
  Representation irrep_;

  std::vector<bit_t> reps_;
  std::vector<double> norms_;
  std::unordered_map<bit_t, gsl::span<bit_t const>> rep_search_range_;

  idx_t index_of_representative(bit_t rep) const;
};

} // namespace hydra::indexing
