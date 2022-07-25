
PS2 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer and at least two lines between your answer and the next question.

.. role:: cpp(code)
   :language: c++


Inner Product
-------------

1. How would you use :cpp:`dot` to implement :cpp:`two_norm`?

   Take the dot product of the input vector with itself and then square root it-
   two_norm = sqrt(dot(x,x))



Tensors
-------

2. What is the formula that we would use for indexing if we wanted "slab-major" ordering?  Hint:  What is the size of a slab?  It might be helpful to draw a picture of the data in 3D and see what the size is of a slab.
   
   Slab major indexing-

   double& operator()(size_t i, size_t j, size_t k) {
       return storage_[i * num_rows_*num_cols_ +j*num_cols_+k];
   }
   const double& operator()(size_t i, size_t j, size_t k) const{
     return storage_[i * num_rows_*num_cols_ +j*num_cols_+k];
   }



3. (Extra credit.) I claim that there are six distinct indexing formulas.  Show that this claim is correct or that it is incorrect.

   True. The ordering for slab, row and column can be permuted with 3! permutations. The 6 formulas are as follows:
   - i * num_rows_*num_cols_ +j*num_cols_+k
   - i * num_rows_*num_cols_ +k*num_rows_+j
   - j * num_slabs_*num_cols_ +i*num_cols_+k
   - j * num_slabs_*num_cols_ +k*num_slabs_+i
   - k * num_cols_*num_slabs_ +i*num_rows_+j
   - k * num_cols_*num_slabs_ +j*num_slabs_+i
