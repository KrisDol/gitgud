#pragma once

// A Class to represent SQUARE Matrices
class Matrix { 
    int M;    // Side length of matrix of size  m x m
    char Name; // Unique, A-Z
    static int NameCounter; // Srart at 65 -> ASCII representation of letter "A"
  
    double **values; // values[][] represents values in matrix of a size MxM
    double det; // Determinant of matrix
    bool isDetTrue = false;  // Flag, false if matrix was changed and determinant may no longer be true
  
public: 
    Matrix(int M);  // Constructor, where M is length of side of matrix

    // ------------------------ Getters --------------------------------- //
    int getSize(); // Get M of matrix with dimensions M x M
    char getName(); // Get name of matrix
    double getValue(int m, int n); // Get value from specified cell
    double getDet(); // Get determinant of matrix

    // ----------------------- Setters --------------------------------- //
    // function to populate value in matrix 
    void enterValue(int m, int n, double value);  
    void enterAllValues(); 

    // ------------------------ Other -----------------------------------//
    int    getNameCounter(); // Get current count of objects (starts at 65)
    double calculateDet(); // Calculate determinant of matrix
    double calculateDetSarrus(); // Only for Matrices 3X3
    double calcMinorDet(int m, int n); // Calculate determinant of matrix without M-th row and N-th column
    void   print();   // Print values of matrix
    void   calculateInverse(Matrix* Ai); // Calculate inverse of matrix and store it in matrix Ai
    void   lowerCount(); // Call during pop_back, decrements nameCounter by 1
}; 