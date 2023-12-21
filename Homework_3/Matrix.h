#ifndef _Matrix_h_
#define _Matrix_h_

#include <iostream>

class Matrix {

    public: 
    //Basic constructors 
    Matrix();
    Matrix(unsigned int user_rows, unsigned int user_cols, double user_fill);
    //Creating the copy constructor
    Matrix(const Matrix &m);
    // Establishing the getter constructors
    int num_rows() const {return rows;}
    int num_cols() const {return cols;}
    double getFill() const {return fill;}
    double** getMatrix() const {return matrix;}
    // Creating all necessary constructors for matrix_main.cpp to work
    bool get(int row, int col, double &val);
    bool set(int posx, int posy, double val);
    void multiply_by_coefficient(double coefficient);
    void swap_row(int row_to_swap, int target_row);
    void transpose();
    bool add(Matrix &m2);
    bool subtract(Matrix &m2);
    double* get_row(unsigned int row_num);
    double* get_col(unsigned int col_num);
    Matrix* quarter();
    void clear();
    // Overloading operators
    void operator=(const Matrix &b);
    bool operator==(const Matrix &b) const;
    bool operator!=(const Matrix &b) const;
    std::ostream& operator<<(const Matrix& m);
    private:
    double fill;
    unsigned int rows;
    unsigned int cols;
    double **matrix;

};
std::ostream& operator<<(std::ostream& out, const Matrix& m);

#endif