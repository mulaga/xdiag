---
title: eigval_lanczos
---
Computes the eigenvectors of an operator on a block. 

**Source** [eigval_lanczos.hpp](https://github.com/awietek/xdiag/blob/master/xdiag/algorithms/lanczos/eigval_lanczos.hpp)

## Parameters

| Name           | Description                                                            | Default |
|:---------------|:-----------------------------------------------------------------------|---------|
| bondlist       | BondList defining the bonds of the operator                            |         |
| block          | block on which the operator is defined                                 |         |
| precision      | accuracy of the computed ground state                                  | 1e-12   |
| max_iterations | maximum number of iterations                                           | 1000    |
| force_complex  | whether or not computation should be forced to have complex arithmetic | false   |
| random_seed    | random seed for setting up the initial vector                          | 42      |

## Returns

| Type                | Description                       |
|:--------------------|:----------------------------------|
| eigvals return type | structure type containing results |

| members types       |                                   |
|:--------------------|:----------------------------------|
| alphas              |                                   |
| betas               |                                   |
| eigenvalues         |                                   |
| n_iterations        |                                   |
| criterion           |                                   |



## Definition

=== "C++"
    ```c++
    eigvals_lanczos_result_t eigvals_lanczos(BondList const &bondlist, 
	  			block_variant_t const &block,
				double precision = 1e-12, int64_t max_iterations = 1000,
				bool force_complex = false, int64_t random_seed = 42);
	```

=== "C++ (explicit state initialization)"
    ```c++
    eigvals_lanczos_result_t eigvals_lanczos(BondList const &bondlist,
	   			block_variant_t const &block, State const &state,
	            double precision = 1e-12, int64_t max_iterations = 1000,
			    bool force_complex = false);
	```

=== "C++ (in place version, WILL change the input state)"
    ```c++
    eigvals_lanczos_result_t eigvals_lanczos_inplace(BondList const &bondlist,
		    	block_variant_t const &block, State &state,
				double precision = 1e-12, int64_t max_iterations = 1000,
				bool force_complex = false);
	```

## Usage Example

=== "C++"
	```c++
	--8<-- "examples/usage_examples/main.cpp:eigvals_lanczos"
	```
	
=== "C++ (explicit state initialization)"
	```c++
	--8<-- "examples/usage_examples/main.cpp:eigvals_lanczos_2"
	```
