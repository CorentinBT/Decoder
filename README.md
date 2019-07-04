# Sparse Ternary Codes similarity search 

Implementation of the STC similarity search based on https://arxiv.org/pdf/1901.08437.pdf for efficient ANN search.

## Build and Deployment 

### Building the project

Building this project requires a modern C++ compiler, the BOOST library (at least version 1.50), the zlib library and a CMake version 3.5 or
higher.

On linux, building should be as simple as (with git)

    git clone https://github.com/CorentinBT/Decoder.git
    cd Decoder
    mkdir build
    cd build
    cmake ..
    make
    
## Config file

A `config.json` file should be provided at the same location as the executable file. It contains all the configurations for the encoding 
decoding process. 

```
  {
  "parameters": {
    "encoder": {
      "policy": "KeepSign",
      "sparsity": sparsityValue between 0.0 and 1.0 (ex : 0.20)
    },
    "matcher": {
      "policy": "FixedResList" or "FixedThreshold",
      "threshold": thresholdValue
    },
    "miscellaneous": {
      "enableChronos": true or false
    }
  },
  "files": {
    "databaseFile": "databaseFilename.npy",
    "inputVectorFile": "inputQueryFilename.npy",
    "outputIndexesFile": "resultsOfClosestIndexesFilename.npy"
  }
}
```
### Encoding policies

Not implemented yet. Only `KeepSign` available. 

### Matching policies 

- `FixedResList` : the resulting closest indexes list will be of the given size of `threshold` and sorted in decreasing order 
of similarity.  

- `FixedThreshold` : the resulting indexes list will contain index of elements with at least `threshold` common values.

### Database input 

The database should be provided as a `.npy` file with the number of lines corresponding to the number of elements and the number of columns
to the number of features. 

### Query input

The input query should be a vector with the same size as the number of columns of the database.

### Indexes output

Results of the similarity search.
