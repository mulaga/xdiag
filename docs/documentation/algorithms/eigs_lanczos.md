---
title: eigs_lanczos
---

```c++
eigs_lanczos(bondlist, block; neigenvalues, precision, max_iteration, force_complex, random_seed)
```

Computes the eigenvectors of an operator on a block. 

**Source** [eigs_lanczos.hpp](https://github.com/awietek/xdiag/blob/master/xdiag/algorithms/lanczos/eigs_lanczos.hpp)

## Parameters

| Name           | Description                                                            | Default |
|:---------------|:-----------------------------------------------------------------------|---------|
| bondlist       | BondList defining the bonds of the operator                            |         |
| block          | block on which the operator is defined                                 |         |
| neigvals       | number of eigenvectors to build                                 |  1      |
| precision      | accuracy of the computed ground state                                  | 1e-12   |
| max_iterations | maximum number of iterations                                           | 1000    |
| force_complex  | whether or not computation should be forced to have complex arithmetic | false   |
| random_seed    | random seed for setting up the initial vector                          | 42      |

## Returns

| Type                | Description                       |
|:--------------------|:----------------------------------|
| eigs return type | structure type containing results |

| members types       |                                   |
|:--------------------|:----------------------------------|
| alphas              |                                   |
| betas               |                                   |
| eigenvalues         |                                   |
| eigenvectors        |                                   |
| n_iterations        |                                   |
| criterion           |                                   |



## Definition

=== "C++"
    ```c++
    eigs_lanczos_result_t eigs_lanczos(BondList const &bondlist, 			
				   block_variant_t const &block, int64_t neigenvalues = 1,
				   double precision = 1e-12, int64_t max_iterations = 1000,
				   bool force_complex = false, int64_t random_seed = 42);
	```

=== "C++ (explicit state initialization)"
    ```c++
    eigs_lanczos_result_t eigs_lanczos(BondList const &bondlist, 
				block_variant_t const &block, State const &state,
    			int64_t neigenvalues = 1,
				double precision = 1e-12, int64_t max_iterations = 1000,
				bool force_complex = false);
	```

## Usage Example

=== "C++"
	```c++
	--8<-- "examples/usage_examples/main.cpp:eigval0"
	```
	
