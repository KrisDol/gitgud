#include "Matrix.h"
#include <bits/stdc++.h> 
using namespace std; 
int Matrix::NameCounter = 65; // Initialize namecounter to start at "A"

// Construct matrix with sze MxM
Matrix::Matrix(int M) { 
    this->M = M; 
    this->Name = Matrix::getNameCounter();
  
    // Create a dynamic array of pointers 
    values = new double* [M]; 
  
    // Create a row for every pointer 
    for (int i=0; i<M; i++) {  
       values[i] = new double[M]{ 0 };  
    } 
} 

void Matrix::lowerCount(){
    int curr = Matrix::NameCounter;
    Matrix::NameCounter = curr-1;
}

// Get determinant of matrix
double Matrix::getDet(){
    if(isDetTrue){return det;} 
    else{
        if(M==1)
            det = values[0][0];
        else if(M==2)
            det = values[0][0]*values[1][1] - values[0][1]*values[1][0];
        //else if(M==3)
        //    det = this->calculateDetSarrus();
        else
            det = this->calculateDet();

        isDetTrue = true;
        return det;
    }
}

// Get value from specified cell
double Matrix::getValue(int m, int n){
    return this->values[m][n];
}

// Get M of matrix with dimensions M x M
int Matrix::getSize(){
    return this->M;
}
    
// Get name of matrix
char Matrix::getName(){
    return this->Name;
}

// Enter value from variable value and insert it to matrix in A[m][n]
void Matrix::enterValue(int m, int n, double value){
    isDetTrue = false;
    values[m][n] = value;
}

// Create encapsulaton for entering whole matrix using enterValue()
void Matrix::enterAllValues(){
    for(int i=0; i < M; i++){
        for(int j=0; j < M; j++){
            double tmp;
            cout << "Enter value of matrix for " << i+1 << ", " << j+1 << ": ";
            cin >> tmp;
            this->enterValue(i, j, tmp);
        }
    }
}
  
// Utility method to print adjacency matrix 
void Matrix::print() { 
    cout << "Matrix " << this->getName() << " :\n";
    for (int m=0; m<M; m++) { 
        for (int n=0; n<M; n++) 
            cout << values[m][n] << " "; 
        cout << endl; 
    } 
    cout << endl << endl;
} 

// Get current name as ASCII value and increment it by 1
int Matrix::getNameCounter(){
    int curr = Matrix::NameCounter;
    Matrix::NameCounter = curr+1;
    return curr;
}

// Calculate determinator of matrix using Sarrus method
double Matrix::calculateDetSarrus(){
    if(M != 3)
        throw "Sarrus method only applies to 3x3 matrices!";
    double part1 = 0.0;
    double part2 = 0.0;
    // Calculate part1
    for(int j=0; j < M; j++){
        double tmp = 1.0;
        for(int i=0; i < M; i++){
            tmp = tmp*values[(i+j)%M][i];
        }
        part1 += tmp;
    }

    // Calculate part2
    for(int s=0; s < M; s++){ // Add shift
        double tmp = 1.0;
        int j = M-1;
        for(int i=0; i < M; i++){
            tmp = tmp*values[(i+s)%M][j];
            j--;
        }
        part2 += tmp;
    }

    return part1-part2;
}

// Reduce matrix
double Matrix::calculateDet(){
    double v[M][M];

    for(int i=0; i < M; i++){
        for(int j=0; j < M; j++){
            v[i][j] = values[i][j];
        }
    }

    for(int i=0; i < M; i++){
        for(int j=0; j < M; j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    for(int i=0; i < M-1; i++){
        for(int m=i+1; m < M; m++){
            for(int n=i+1; n < M; n++){
                v[m][n] = v[m][n] - v[m][i]/v[i][i] * v[i][n];
                if(isnan(v[m][n]))
                    v[m][n] = 0;
            }
            cout << endl;
        }
    }

    for(int i=0; i < M; i++){
        for(int j=0; j < M; j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    double d = 1.0;
    for(int i=0; i < M; i++){
        d *= v[i][i];
    }
    return d;
}

// Calculate determinant of matrix without M-th row and N-th column
double Matrix::calcMinorDet(int n, int m){
    double v[M-1][M-1];

    // Create copy of matrix without M-th row and N-th column
    int i = 0, j = 0;
    for (int r= 0; r<M; r++) {
        for (int c = 0; c<M; c++) //Copy only those elements which are not in given row r and column c: {
            if (r != m && c != n) { 
                v[i][j++] = values[r][c]; //If row is filled increase r index and reset c index
                if (j == M - 1) {
                    j = 0; i++;
                }
            }
    }

    if(M-1==1)
        return v[0][0];
    else if(M-1 == 2)
        return v[0][0]*v[1][1] - v[0][1]*v[1][0];
    else{
        // Reduce matrix so determinant is on diagonal
        for(int i=0; i < M-2; i++){
            for(int m=i+1; m < M-1; m++){
                for(int n=i+1; n < M-1; n++){
                     v[m][n] = v[m][n] - v[m][i]/v[i][i] * v[i][n];
                    if(isnan(v[m][n]))
                        v[m][n] = 0;
                }
            }
        }

        // Calculate and return determinant
        double d = 1.0;
        for(int i=0; i < M-1; i++){
            d *= v[i][i];
        }
        return d;
    }
}

// Ai = inverse of matrix A
// Calculate inverse of matrix A and store it in given matrix Ai
void Matrix::calculateInverse(Matrix* Ai){
    // Check if matrix has already calculated determinant
    if(!isDetTrue)
        this->getDet();

    // Check if matrix can be inversed
    if(det == 0){
        // Matrix can not be inversed
        cout << "This matrix has no inverse\n";
        throw "Determinant of this matrix is 0. This matrix can not be inverted.";
    }else{
        // Calculate inverse of matrix
        for(int i = 0; i < M; i++){
            for(int j = 0; j < M; j++){
                double tmp = pow(-1, i+j) * this->calcMinorDet(i, j)/ this->getDet();
                Ai->enterValue(i, j, tmp);
            }
	    }
        
    }

}
 
