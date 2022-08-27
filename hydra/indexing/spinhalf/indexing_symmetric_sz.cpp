#include "indexing_symmetric_sz.h"

#include <hydra/blocks/utils/block_utils.h>
#include <hydra/symmetries/operations/representative_list.h>
#include <hydra/utils/logger.h>

#ifdef HYDRA_ENABLE_OPENMP
#include <hydra/parallel/omp/omp_utils.h>
#endif

namespace hydra::indexing::spinhalf {

template <class bit_t>
IndexingSymmetricSz<bit_t>::IndexingSymmetricSz(
    int n_sites, int n_up, PermutationGroup permutation_group,
    Representation irrep)
    : n_sites_(n_sites), n_up_(n_up),
      group_action_(allowed_subgroup(permutation_group, irrep)), irrep_(irrep),
      combinations_indexing_(n_sites, n_up) {
  utils::check_nup_spinhalf(n_sites, n_up, "IndexingSymmetricSz");
  utils::check_n_sites(n_sites, permutation_group);

  std::tie(reps_, index_for_rep_, syms_, sym_limits_for_rep_, norms_) =
      symmetries::representatives_indices_symmetries_limits_norms<bit_t>(
          combinations_indexing_, group_action_, irrep);

  size_ = (idx_t)reps_.size();
  begin_ = iterator_t(reps_, 0);
  end_ = iterator_t(reps_, size_);
}

#ifdef HYDRA_ENABLE_OPENMP
template <class bit_t>
typename IndexingSymmetricSz<bit_t>::iterator_t
IndexingSymmetricSz<bit_t>::thread_begin() const {
  idx_t start = omp::get_omp_start(size_);
  return iterator_t(reps_, start);
}

template <class bit_t>
typename IndexingSymmetricSz<bit_t>::iterator_t
IndexingSymmetricSz<bit_t>::thread_end() const {
  idx_t end = omp::get_omp_end(size_);
  return iterator_t(reps_, end);
}
#endif

template class IndexingSymmetricSz<uint16_t>;
template class IndexingSymmetricSz<uint32_t>;
template class IndexingSymmetricSz<uint64_t>;

} // namespace hydra::indexing::spinhalf
