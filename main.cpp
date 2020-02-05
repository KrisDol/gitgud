#include "Matrix.h"
#include <bits/stdc++.h> 
#include <conio.h>
using namespace std;

// Functions for matrix solving
void multiplyMatrices(Matrix* A, Matrix* B, Matrix* C); // Multiply matrices A*B, save in C
void addMatrices(Matrix* A, Matrix* B, Matrix* C);  // Add 2 matrices A+B, save in C
void subMatrices(Matrix* A, Matrix* B, Matrix* C);  // Subtract matrices, A-B, save in C
void solveMatrixEq(Matrix* A, Matrix* B, Matrix* C, Matrix* X); // Solve AX+B=C, where A,B,C are given => ( X = A'*(C-B)  &&  A' = A inverse ), save in X
// Helpers
int readvMatricesIndex(string msg, char* lastOption); // Get matrix name from user and return it as index for vMatrices vector

// ------------------------------------------------------------------------ //
//                              MAIN START                                  //
// ------------------------------------------------------------------------ //

int main(){ 
    // Initialize vector of Matrices
    vector<Matrix*> vMatrices;
    int numOfOpt = 11;
    string options[numOfOpt] = {
        "Add matrix to memory. (Input new matrix)",
        "Change value(s) of matrix.",
        "Display all saved matrices.",

        "Display one saved matrix.",
        "Add 2 matrices (A + B).",
        "Subtract 2 matrices (A - B).",

        "Multiply 2 matrices (A * B).",
        "Calculate determinant of matrix.",
        "Calculate inverse of matrix.",

        "Solve equation AX + B = C, with given A, B and C.",
        "EXIT."
    };
    int optionConstraints[numOfOpt] = {
        0, 1, 1,
        1, 2, 2,
        2, 1, 1,
        3, 0
    };

    // Main loop
    bool bexit = false; // Continue while bexit == false
    while(!bexit){
        // Display menu
        int matricesSaved = vMatrices.size();
        cout << "\n\n";
        cout << "   ----------------------------------------------------------- " << endl;
        cout << "   |   Welcome to Matrix Handler v1.0 by Krzysztof Dolech!   | " << endl;
        cout << "   ----------------------------------------------------------- " << endl;
        cout << "\n You have currently " << matricesSaved << " matrice(s) saved.\n" <<
        " Please choose an action, which You want to perform.\n"<<
        " TIP: Actions with asterisk (*) are not available, probably due to not enough Matrices saved.\n"<<
        "      You can only perform actions on saved Matrices!\n\n";

        for(int i=0; i < numOfOpt; i++){
            if(matricesSaved < optionConstraints[i])
                cout << " *. " << options[i] << endl;
            else
                cout << " " << i+1 << ". " << options[i] << endl;
        }

        int choice;
        cout << endl << "Type # of operation You'd like to choose: " << flush;
        if(!(cin >> choice)){
            cout << "Hey! Can't you distinguish letters from numbers?! Hands on numpad now ya rancid tomato!";
            cin.clear(); // reset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            cout << endl;
            system("PAUSE");
            system ("CLS");
            continue;
        }
        choice = choice - 1; // Move from human friendly index to index for arays
        
        // If user selected blocked option go to next iteration
        if(matricesSaved < optionConstraints[choice]){
            cout << endl << "Ah You pesky human... This option is blocked... Can't You see the asterisk... Aw c'mon, try again!" << endl;
            system("PAUSE");
            system ("CLS");
            continue;
        }

        char lastMatrixName = 64+matricesSaved;
        // If user picked available option...
        switch(choice){
            case 0:  // Add matrix to memory
                { 
                    int s = -1; // Size of new matrix
                    while(s<1){
                        cout << "Enter the size of matrix: ";
                        cin >> s;
                    }
                    vMatrices.push_back(new Matrix(s));
                    vMatrices.back()->enterAllValues();
                    cout << "Yeeee haaaaww! I've saved this matrix as matrix " << vMatrices.back()->getName() << endl;
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            
            case 1:  // Change value(s) of matrix
                { 
                    int matrixIndex = -1;
                    while(matrixIndex < 0 || matrixIndex > matricesSaved-1){
                        matrixIndex = readvMatricesIndex("Select matrix :", &lastMatrixName);  
                    }
                    int m=0, n=0;
                    double newValue=0;
                    Matrix* chosenMatrix = vMatrices[matrixIndex];
                    bool again = true;
                    while(again){
                        while(m <= 0 || n <= 0 || m > chosenMatrix->getSize() || n > chosenMatrix->getSize()){
                            cout << "Enter posision and value of new element in convention \"ROW# <SPACE> COL# <SPACE> NEW_VALUE\": ";
                            cin >> m >> n >> newValue;
                        }
                        chosenMatrix->enterValue(m-1, n-1, newValue);
                        cout << "Do You want to alter more values of this matrix? (Y/N): ";
                        char c;
                        cin >> c;
                        if(c == 89 || c == 121){ // If user typed Y or y
                            m=0; n=0;
                        }else{
                            again = false;
                        }
                    }
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 2:  // Display all saved matrixes
                { 
                    for(auto &Mx : vMatrices){
                        Mx->print();
                    }
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 3:  // Display only 1 saved matrix
                { 
                    int matrixIndex = -1;
                    while(matrixIndex < 0 || matrixIndex > matricesSaved-1){
                        matrixIndex = readvMatricesIndex("Select matrix : ", &lastMatrixName);  
                    }
                    vMatrices[matrixIndex]->print();
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 4:  // ADD 2 matrices
                { 
                    int matrixA4 = -1;
                    int matrixB4 = -1;
                    while(matrixA4 < 0 || matrixA4 > matricesSaved-1){
                        matrixA4 = readvMatricesIndex("Select first matrix: ", &lastMatrixName);  
                    }
                    while(matrixB4 < 0 || matrixB4 > matricesSaved-1){
                        matrixB4 = readvMatricesIndex("Select second matrix: ", &lastMatrixName);  
                    }
                    Matrix* A4 = vMatrices[matrixA4];
                    Matrix* B4 = vMatrices[matrixB4];
                    if(A4->getSize() == B4->getSize()){
                        vMatrices.push_back(new Matrix(A4->getSize()));
                        Matrix* C4 = vMatrices.back();

                        addMatrices(A4, B4, C4);
                        cout << "Sum of given 2 matrices (A + B): " << endl;
                        C4->print();

                        cout << "Do You want to save this matrix as matrix " << C4->getName() << " ?(Y/N): ";
                        char c4;
                        cin >> c4;
                        if(c4 != 89 && c4 != 121){
                            vMatrices.back()->lowerCount();
                            vMatrices.pop_back();
                        }else{
                            cout << "Matrix saved!" << endl;
                        }
                    }else{
                        cout << "Matrix sizes do not match. Falling back to main menu.";
                    }
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 5:  // SUBTRACT 2 matrices
                {  
                    int matrixA5 = -1;
                    int matrixB5 = -1;
                    while(matrixA5 < 0 || matrixA5 > matricesSaved-1){
                        matrixA5 = readvMatricesIndex("Select first matrix: ", &lastMatrixName);  
                    }
                    while(matrixB5 < 0 || matrixB5 > matricesSaved-1){
                        matrixB5 = readvMatricesIndex("Select second matrix: ", &lastMatrixName);  
                    }
                    Matrix* A5 = vMatrices[matrixA5];
                    Matrix* B5 = vMatrices[matrixB5];
                    if(A5->getSize() == B5->getSize()){
                        vMatrices.push_back(new Matrix(A5->getSize()));
                        Matrix* C5 = vMatrices.back();

                        subMatrices(A5, B5, C5);
                        cout << "Result of A - B: " << endl;
                        C5->print();

                        cout << "Do You want to save this matrix as matrix " << C5->getName() << " ?(Y/N): ";
                        char c5;
                        cin >> c5;
                        if(c5 != 89 && c5 != 121){
                            vMatrices.back()->lowerCount();
                            vMatrices.pop_back();
                        }else{
                            cout << "Matrix saved!" << endl;
                        }
                    }else{
                        cout << "Matrix sizes do not match. Falling back to main menu.";
                    }
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 6:  // MULTIPLY 2 matrices
                {
                    int matrixA6 = -1;
                    int matrixB6 = -1;
                    while(matrixA6 < 0 || matrixA6 > matricesSaved-1){
                        matrixA6 = readvMatricesIndex("Select first matrix: ", &lastMatrixName);  
                    }
                    while(matrixB6 < 0 || matrixB6 > matricesSaved-1){
                        matrixB6 = readvMatricesIndex("Select second matrix: ", &lastMatrixName);  
                    }
                    Matrix* A6 = vMatrices[matrixA6];
                    Matrix* B6 = vMatrices[matrixB6];
                    if(A6->getSize() == B6->getSize()){
                        vMatrices.push_back(new Matrix(A6->getSize()));
                        Matrix* C6 = vMatrices.back();

                        multiplyMatrices(A6, B6, C6);
                        cout << "Result of A * B: " << endl;
                        C6->print();

                        cout << "Do You want to save this matrix as matrix " << C6->getName() << " ?(Y/N): ";
                        char c6;
                        cin >> c6;
                        if(c6 != 89 && c6 != 121){
                            vMatrices.back()->lowerCount();
                            vMatrices.pop_back();
                        }else{
                            cout << "Matrix saved!" << endl;
                        }
                    }else{
                        cout << "Matrix sizes do not match. Falling back to main menu.";
                    }
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 7:  // Calculate determinant of matrix
                {
                    int matrixA7 = -1;
                    while(matrixA7 < 0 || matrixA7 > matricesSaved-1){
                        matrixA7 = readvMatricesIndex("Select first matrix: ", &lastMatrixName);  
                    }
                    Matrix* A7 = vMatrices[matrixA7];
                    cout << "Determinant of matrix " << A7->getName() << " is " << A7->getDet() << endl;
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 8:  // Calculate inverse of matrix
                {
                    int matrixA8 = -1;
                    while(matrixA8 < 0 || matrixA8 > matricesSaved-1){
                        matrixA8 = readvMatricesIndex("Select matrix: ", &lastMatrixName);  
                    }
                    Matrix* A8 = vMatrices[matrixA8];
                    if(A8->getDet() != 0){
                        vMatrices.push_back(new Matrix(A8->getSize()));
                        Matrix* Ai = vMatrices.back();
                        A8->calculateInverse(Ai);
                        system("CLS");
                        cout << "Inverse of matrix: " << endl;
                        A8->print();
                        cout << "is matrix: " << endl;
                        Ai->print();

                        cout << "Do You want to save this matrix as matrix " << Ai->getName() << " ?(Y/N): ";
                        char c8;
                        cin >> c8;
                        if(c8 != 89 && c8 != 121){
                            vMatrices.back()->lowerCount();
                            vMatrices.pop_back();
                        }else{
                            cout << "\nMatrix saved!\n";
                        }

                    }else{
                        cout << "Determinant of this matrix is 0. This matrix DOES NOT have an inverse." << endl;
                    }
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 9:  // Solve equation AX + B = C, with given A, B and C
                {
                    int matrixA9 = -1;
                    int matrixB9 = -1;
                    int matrixC9 = -1;
                    while(matrixA9 < 0 || matrixA9 > matricesSaved-1){
                        matrixA9 = readvMatricesIndex("Select first  matrix (A): ", &lastMatrixName);  
                    }
                    while(matrixB9 < 0 || matrixB9 > matricesSaved-1){
                        matrixB9 = readvMatricesIndex("Select second matrix (B): ", &lastMatrixName);  
                    }
                    while(matrixC9 < 0 || matrixC9 > matricesSaved-1){
                        matrixC9 = readvMatricesIndex("Select third  matrix (C): ", &lastMatrixName);  
                    }
                    Matrix* A9 = vMatrices[matrixA9];
                    Matrix* B9 = vMatrices[matrixB9];
                    Matrix* C9 = vMatrices[matrixC9];
                    if(A9->getDet() != 0){
                        vMatrices.push_back(new Matrix(A9->getSize()));
                        Matrix* X = vMatrices.back();
                        solveMatrixEq(A9, B9, C9, X);
                        system("CLS");
                        cout << "Solution of equation AX + B = C for given matrices: " << endl << endl;
                        A9->print();
                        B9->print();
                        C9->print();
                        cout << "is matrix: " << endl << endl;
                        X->print();

                        cout << "Do You want to save this matrix as matrix " << X->getName() << " ?(Y/N): ";
                        char c9;
                        cin >> c9;
                        if(c9 != 89 && c9 != 121){
                            vMatrices.back()->lowerCount();
                            vMatrices.pop_back();
                        }else{
                            cout << "\nMatrix saved!\n";
                        }

                    }else{
                        cout << "Determinant of this matrix is 0. This matrix DOES NOT have an inverse." << endl << "Sorry human, I'm unable to solve this equation *sad PC noises*" << endl;
                    }
                    system("PAUSE");
                    system ("CLS");
                }
                break;
            case 10: // Exit
                cout << "Bye! It was nice to meet You :) " << endl;
                bexit = true;
                system("PAUSE");
                break;
            default:
                cout << "Wait! That's illegal!\nPlease inter number from range 1-" << numOfOpt << ".\nThanks!\n";
                system("PAUSE");
                break;

        } // switch(choice) END

    } // MAIN LOOP END

    
    // Do some housekeeping ;)
    // delete every item in vector
    for(auto &a : vMatrices)
        delete a;    
    // Delete structure of now empty vector
    vMatrices.clear();

    return 0; 
}
// ------------------------------------------------------------------------ //
//                               MAIN END                                   //
// ------------------------------------------------------------------------ //


// Multiply 2 given Matrices AxB and save to matrix C
void multiplyMatrices(Matrix* A, Matrix* B, Matrix* C){
    if(A->getSize() != B->getSize()){
        throw "Can NOT multiply Matrices with different sizes!";
    }else{
        int s = A->getSize();
        // For each row in Matrix
        for(int m=0; m < s; m++){
            // For each cell in row
            for(int n=0; n < s; n++){
                // Initialize value for C[m][n]
                double value = 0.0;
                // Value for C[m][n] is sum of appropreiate multiplications
                for(int i=0; i<s; i++){
                    value += A->getValue(m, i) * B->getValue(i, n);
                }
                C->enterValue(m,n,value);
            }
        }
        cout << "Result of multiplying those 2 Matrices is: " << endl;
        C->print();
    }
}

// Add 2 Matrices and print the result and save to C
void addMatrices(Matrix* A, Matrix* B, Matrix* C){
    if(A->getSize() != B->getSize()){
        throw "Can NOT add Matrices with different sizes!";
    }
    int s = A->getSize();
    for(int m=0; m < s; m++){
        for(int n=0; n < s; n++){
            C->enterValue(m, n, A->getValue(m,n) + B->getValue(m,n));
        }
    }
}

// Subtract 2 Matrices and save to matrix C
void subMatrices(Matrix* A, Matrix* B, Matrix* C){
    if(A->getSize() != B->getSize()){
        throw "Can NOT perform subtraction on Matrices with different sizes!";
    }
    int s = A->getSize();
    for(int m=0; m < s; m++){
        for(int n=0; n < s; n++){
            C->enterValue(m, n, A->getValue(m,n) - B->getValue(m,n));
        }
    }
}

// Get matrix name from user and return it as index for vMatrices vector
int readvMatricesIndex(string msg, char* lastOption){
    char x;
    int wybor=0;
    while(wybor < 65 || wybor > 90){
        cout << msg;
        cin >> x;
        x = toupper(x);
        wybor = int(x);
        if(wybor < 65 || wybor > (int)*lastOption){
            cout << endl << "ERROR! You have specified invalid matrix name.\nWalid matrix names are in range A-" << lastOption << "." << endl; 
        }
    }
    return wybor-65;
    //return wybor;
}

// Solve AX+B=C, where A,B,C are given => ( X = Ai*(C-B)  &&  Ai = A inverse )
void solveMatrixEq(Matrix* A, Matrix* B, Matrix* C, Matrix* X){
    int size = A->getSize();
    if(B->getSize() != size || C->getSize() != size || X->getSize() != size){
        throw "All Matrices must be the same size!";
        return;
    }

    if(A->getDet() == 0){
        throw std::string("Matrix ") + A->getName() + " can not be inversed. Can not solve this equation.";
        return;
    }

    Matrix* Ai = new Matrix(size);  // Inverse of matrix A
    A->calculateInverse(Ai);

    Matrix* CmB = new Matrix(size); // Solution to C-B
    subMatrices(C, B, CmB);

    multiplyMatrices(Ai, CmB, X);  // Insert solution of Ai*CmB to X
    X->print();
}