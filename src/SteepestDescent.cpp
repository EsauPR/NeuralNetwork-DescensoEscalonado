/*
    Adjusting weights for Adaline Neuron by steepest Descent
    Multiple Inputs - One Output

    @author Oscar Esaú Peralta Rosales
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <time.h>
#include "processInput.cpp"

using namespace std;

void readParams( int *T, double *miu, double *factorMiu ); // Read algorithm parameters
void help();  // Show the program help

vector<double> steepestDescent( vector<vector<double> > X ); // Adjusting weights by steepest Descent

int main(int argc, char const *argv[]) {

    vector<vector<double> > X; // Data input, the las element of the each row i represents the value di
    vector<double> W; // Weights
    if ( argc < 2 ) {
        printf("Error: Enter a input file as argument\n");
        help();
        exit( EXIT_FAILURE );
    }

    srand(time(NULL));
    X = readInput( argv[1]);
    //printf("n = %d,  p = %d\n", n, p );
    //printVec( X );

    W = steepestDescent( X );
    puts("Solución");
    printVec( W );


    exit(EXIT_SUCCESS);
}

// Adjusting weights by steepest Descent
vector<double> steepestDescent( vector<vector<double> > X ) {
    int T; // Number of presentations
    int n = X.size(), p = X[0].size() - 1;
    double miu, factorMiu;
    vector<double> W; // Solution weights

    readParams( &T, &miu, &factorMiu );
    printf("T = %d, miu = %lf, factorMiu = %lf\n", T, miu, factorMiu );

    W.resize( p );
    for (int i = 0; i < p; i++) {
        W[i] = 2 - (double)( rand() % 10 ) / 5.0;
    }

    puts("Solución inicial");
    printVec( W );

    for (int t = 0; t < T; t++) {
        for (int m = 0; m < n; m++) {
            //printVec( W );
            // Getting the error of each xi
            double error = 0.0;
            for (int i = 0; i < p; i++) {
                error += W[i] * X[m][i];
            }
            // The las element of the each row of X represents the value di
            error = X[m][p] - error;

            //printf("error: %lf\n\n", error);

            // Computing the gradient
            vector<double> D_Wm;
            D_Wm.resize( p );
            for (int i = 0; i < p; i++) {
                D_Wm[i] = 2 * error * X[m][i] * miu;
            }
            for (int i = 0; i < p; i++) {
                W[i] += D_Wm[i];
            }
            miu *= factorMiu;
        }
    }

    return W;
}

// Reading parameters
void readParams( int *T, double *miu, double *factorMiu ) {
    FILE *file = NULL;

    file = fopen( "config", "r" );
    if( file == NULL ) {
		printf("Error: The config file does not exist\n");
		exit(EXIT_FAILURE);
	}

    *miu = nextParam( file );
    *factorMiu = nextParam( file );
    *T = (int) nextParam( file );

    fclose( file );
}

// Show the program help
void help() {
    printf("\nHow to use:\n");
    printf("\n\tSteepestDescent [file_input]\n" );
}
