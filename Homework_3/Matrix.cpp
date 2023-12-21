#include "Matrix.h"
#include <iostream>
Matrix::Matrix(){
    rows  = 0;
    cols = 0;

}

Matrix::Matrix(unsigned int user_rows, unsigned int user_cols, double user_fill) {
    rows = user_rows;
    cols = user_cols;
    fill = user_fill;
    //Creating the matrix using an array of pointers pointing to arrays which serve as rows of the matrix
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for( int z =0; z < cols; z++) {
            matrix[i][z] = fill;
        }
    }
}
Matrix::Matrix(const Matrix &m) {
    // Implementing copy constructor functionality
    rows = m.num_rows();
    cols = m.num_cols();
    fill = m.getFill();
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = m.getMatrix()[i][j];
        }
    }
}


bool Matrix::get(int row, int col, double &val) {
    // Fetching value at specified row and coloumn and setting a variable created in main to that value
    if (row <= rows && col <= cols) {
        val = matrix[row][col];
        return true;
    }
    else {
        return false;
    }
}


bool Matrix::set(int row, int col, double val) {
    // Setting an element of the matrix to a user specified value
    if (row <= rows && col <= cols) {
        matrix[row][col] = val;
        return true;
    }
    else {
        return false;
    }
}

void Matrix::multiply_by_coefficient(double coefficient) {
    //Multipying each element in the matrix by a user specified coefficient through the use of nester for loops
    for (int i = 0; i < rows; i++) {
        for( int z =0; z < cols; z++) {
            matrix[i][z] = matrix[i][z] * coefficient;
        }
    }
}

void Matrix::swap_row(int row_to_swap,int target_row) {
    // Swapping two user specified rows through the use of a temporary double* variable
    double* temp = matrix[row_to_swap];
    matrix[row_to_swap] = matrix[target_row];
    matrix[target_row] = temp;
} 

void Matrix::transpose() {
    // Transposing the matrix by creating a new temporary matrix variable and then setting them equal to each other 
    double** newMatrix = new double*[cols];
    for (int i = 0; i < cols; i++){
        newMatrix[i] = new double[rows];
        for (int j = 0; j < rows; j++){
            newMatrix[i][j] = matrix[j][i];
        }
    }

    for (int i = 0; i < rows; i++){
        delete[] matrix[i];
    }
    delete[] matrix;

    matrix = newMatrix;

    int temp = rows;
    rows = cols;
    cols = temp;

}
bool Matrix::add(Matrix &m2) {
    //Adding values from one matrix to another
    if (rows == m2.num_rows() && cols == m2.num_cols()) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                matrix[i][j] += m2.getMatrix()[i][j];
        }
        }
        return true;
    }
    else {
        return false;
    }
}

bool Matrix::subtract(Matrix &m2) {
    //Subtracting values from one matrix to another
    if (rows == m2.num_rows() && cols == m2.num_cols()) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                matrix[i][j] -= m2.getMatrix()[i][j];
        }
        }
        return true;
    }
    else {
        return false;
    }
}
void Matrix::clear() {
    //Clearing all elements of the matrix and deleting all of the data inside the matrix to prevent memory leaks
    rows = 0;
    cols = 0;

    for (int i = 0; i < rows; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}
double* Matrix::get_row(unsigned int row_num) {
    // returning a whole row 
    if(row_num <= rows) {
        return matrix[row_num];
    }
    else { 
        return nullptr;
    }
}
double* Matrix::get_col(unsigned int col_num) {
    //Returning a whole coloumn through the creation of a temporary array 
    if(col_num <= cols) {
        double *p = new double[rows];
        for(int i = 0; i < rows; i++) {
            p[i] = matrix[i][col_num];
        }
    return p;
    }
    else { 
        return nullptr;
    }
}
Matrix* Matrix::quarter(){
    //Dividing the matrix into 4 quadrants through the use of a nested for loop and the set function

    Matrix* quadrants = new Matrix[4];
    int rows = num_rows();
    int cols = num_cols();
        int new_rows = rows / 2;
        int new_cols = cols / 2;

        quadrants[0] = Matrix(new_rows, new_cols,0);
        quadrants[1] = Matrix(new_rows, new_cols,0);
        quadrants[2] = Matrix(new_rows, new_cols,0);
        quadrants[3] = Matrix(new_rows, new_cols,0);
        for(int i = 0; i < new_rows; i++) {
                for(int j = 0; j < new_cols; j++) {
                    quadrants[0].set(i,j,matrix[i][j]);
                    quadrants[1].set(i,j + new_cols,matrix[i][j]);
                    quadrants[2].set(i+ new_rows,j,matrix[i][j]);
                    quadrants[3].set(i + new_rows,j + new_cols,matrix[i][j]);
                }
            }
            return quadrants;
}


bool Matrix::operator==(const Matrix &b) const { 
    // Implementation of overloading the == operator
    std:: cout << rows << b.num_rows() << cols << b.num_cols() << std::endl;
    if (rows != b.num_rows() || cols != b.num_cols()) {
            return false;
        }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != b.getMatrix()[i][j]) {
                std::cout << "LEFT : " << matrix[i][j] << " RIGHT: " << b.getMatrix()[i][j] << std::endl;
                return false;
                }
            }
        }
    return true;
}

void Matrix::operator=(const Matrix &b){
    rows = b.num_rows();
    cols = b.num_cols(); 
    matrix = b.getMatrix();
    fill = b.getFill();
}

bool Matrix::operator!=(const Matrix &b ) const{
    //Implementation of overloading the != operator
    if (rows != b.num_rows() || cols != b.num_cols()) {
            return true;
        }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != b.getMatrix()[i][j]) {
                return true;
                }
            }
        }
    return false;

}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    //Overloading the << operator so that a matrix is printed in the specified format everytime that the class object is printed
    out << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
    for (int i = 0; i < m.num_rows(); i++) {
        for (int j = 0; j < m.num_cols(); j++) {
            out << m.getMatrix()[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}
