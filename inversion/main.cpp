//
//  main.cpp
//  inversion
//
//  Created by Zhongzhou Cai on 10/10/14.
//  Copyright (c) 2014 Zhongzhou Cai. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    int size = 10;
    /*
    float data[9];
    data[0] =0.2;
    data[1] =0.1;
    data[2] =-0.34;
    data[3] =0.5;
    data[4] =0.35;
    data[5] =0;
    data[6] =-23;
    data[7] =-1.2;
    data[8] =4.56;
    */
    float dum = rand();
    float data[size*size];
    for (int i=0; i<size*size; i++) {
        data[i] = 100. *rand()/RAND_MAX;
    }
    for (int i = 0;i<size*size;i++) {
        cout << data[i] << " ";
        if (i%size == size-1) {
            cout << endl;
        }
    }
    cout <<endl;
    int actualsize = size;
    int maxsize = size;
    //if (actualsize <= 0) return;  // sanity check
    //if (actualsize == 1) return;  // must be of dimension >= 2
    for (int i=1; i < actualsize; i++) data[i] /= data[0]; // normalize row 0
    for (int i=1; i < actualsize; i++)  {
        for (int j=i; j < actualsize; j++)  { // do a column of L
            float sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += data[j*maxsize+k] * data[k*maxsize+i];
            data[j*maxsize+i] -= sum;
        }
        if (i == actualsize-1) continue;
        for (int j=i+1; j < actualsize; j++)  {  // do a row of U
            float sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += data[i*maxsize+k]*data[k*maxsize+j];
            data[i*maxsize+j] =
            (data[i*maxsize+j]-sum) / data[i*maxsize+i];
        }
    }
    for ( int i = 0; i < actualsize; i++ )  // invert L
        for ( int j = i; j < actualsize; j++ )  {
            float x = 1.0;
            if ( i != j ) {
                x = 0.0;
                for ( int k = i; k < j; k++ )
                    x -= data[j*maxsize+k]*data[k*maxsize+i];
            }
            data[j*maxsize+i] = x / data[j*maxsize+j];
        }
    for ( int i = 0; i < actualsize; i++ )   // invert U
        for ( int j = i; j < actualsize; j++ )  {
            if ( i == j ) continue;
            float sum = 0.0;
            for ( int k = i; k < j; k++ )
                sum += data[k*maxsize+j]*( (i==k) ? 1.0 : data[i*maxsize+k] );
            data[i*maxsize+j] = -sum;
        }
    for ( int i = 0; i < actualsize; i++ )   // final inversion
        for ( int j = 0; j < actualsize; j++ )  {
            float sum = 0.0;
            for ( int k = ((i>j)?i:j); k < actualsize; k++ )
                sum += ((j==k)?1.0:data[j*maxsize+k])*data[k*maxsize+i];
            data[j*maxsize+i] = sum;
        }
    
    for (int i = 0;i<size*size;i++) {
        cout << data[i] << " ";
        if (i%size == size-1) {
            cout << endl;
        }
    }
    cout << endl;
    cout << "Hello, World!\n";
    return 0;
}
