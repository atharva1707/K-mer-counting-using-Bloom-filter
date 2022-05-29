## K-mer counting using BLOOM filters

### Approach 1  (main.cpp)
using one to one hash maps

### Bloom Filter (bloom.cpp)
> - inputs a genomic sequence, applies a bloom filter and stores the results in a single or multiple output files

### Sorting (sorting.cpp)
> - Takees the output of bloom filters as input and applies sorting algorithm to find the frequently occuring kmers.

## Used openmp for parallelisation, to make the program more efficient