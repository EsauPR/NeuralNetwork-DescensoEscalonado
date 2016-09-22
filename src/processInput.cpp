/*
    Extra functions to process data input

    @author Oscar Esaú Peralta Rosales
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define STR_DIMENSION 150

using namespace std;
/*
 Process the input file
*/

vector<vector< double> > readInput( const char *fname ) {
	char str[STR_DIMENSION], *token, delim[3] = " \n";
    vector<vector< double > > X;

    FILE *file = NULL;
    file = fopen( fname, "r");

	if( file == NULL ) {
		printf("Error: The file does not exist: %s\n", fname);
        //help();
		exit(EXIT_FAILURE);
	}

    // Processing input data line by line
    while( fgets( str, STR_DIMENSION, file ) != NULL ) {
        vector <double> xi;

        /*
            d = b + [k = 1 to p]Σ( w[k] * x[k] )

            Adding b to the the sum:
                Becoming b = w[0] and x[0] = 1, then
                d = [k = 0 to p]Σ( w[k] * x[k] )
        */

        xi.push_back( 1.0 );

        token = strtok(str, delim);
        while( token != NULL ) {
            xi.push_back( atof( token ) );
            token = strtok(NULL, delim);
        }
        X.push_back( xi );
    }

	fclose(file);
    return X;
}


double nextParam( FILE *file ) {
	int pos = 0;
    char token [STR_DIMENSION];

	/* Label */
	while( ( token[pos] = getc(file) ) != EOF && token[pos] != ':' );
	/* Value */
	while( ( token[pos] = getc(file) ) != EOF && token[pos++] != '\n' );

	token[pos-1] = '\0';
    return atof( token );
}

void printVec( vector<vector<double> > X ) {
    for (int i = 0; i < X.size() ; i++) {
        for (int j = 0; j < X[0].size(); j++) {
            printf("%.4lf ", X[i][j]);
        }
        puts("");
    }
    puts("");
}

void printVec( vector<double> X ) {
	printf("d = ");
    for (int i = 0; i < X.size() ; i++) {
		if ( i == 0 ) {
			printf("%.4lf ", X[i]);
		}
		else {
			printf("%.4lfX%d ", X[i], i);
		}
    }
    puts("");
}
