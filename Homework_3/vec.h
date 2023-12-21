class Matrix {

    public: 
    Matrix(unsigned int user_rows, unsigned int user_cols, double user_fill);
    int getRows() {return rows;}
    int getCols() {return cols;}
    int getValue(int posx, int posy);
    void setValue(int posx, int posy);
    
    private:
    double fill;
    unsigned int rows;
    unsigned int cols;
    int **data;

};