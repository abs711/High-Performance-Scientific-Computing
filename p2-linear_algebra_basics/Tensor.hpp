#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <cstddef>
#include <vector>


class Tensor {
public:
    Tensor(size_t L, size_t M, size_t N): num_slabs_(L), num_rows_(M), num_cols_(N), storage_(num_slabs_*num_rows_*num_cols_) {}

    double& operator()(size_t i, size_t j, size_t k) {
        return storage_[i * num_rows_*num_cols_ +j*num_cols_+k];
    }
    const double& operator()(size_t i, size_t j, size_t k) const{
        return storage_[i * num_rows_*num_cols_ +j*num_cols_+k];
    }


    size_t num_slabs() const { return num_slabs_; }
    size_t num_rows() const { return num_rows_; }
    size_t num_cols() const { return num_cols_; }


private:
    size_t           num_slabs_, num_rows_,num_cols_;
    std::vector<double> storage_;

};

#endif    // T_HPP