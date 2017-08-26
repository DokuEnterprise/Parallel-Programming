#include <iostream>
#include <omp.h>
#include <stdio.h>


//Function Declarations
void parallel_lp();

using namespace std;
// OpenMP Playground
int main(){
    int x;
    // We will have only 2 threads
    x = 2;
    #pragma omp parallel num_threads(2) shared(x)
    {
        if(omp_get_thread_num() == 0){
            x = 5;
        }else{
            cout << "1: The following read of x = " << x <<  " has a race" << endl;
        }

        // The Barrier Provides Synchnization as well as a flush to ensure 
        // X has been set as 5
        #pragma omp barrier

        #pragma omp parllel shared(x) num_threads(3) 

        if(omp_get_thread_num() == 1){
            cout << "2: The following read of x = " << x <<  " has a race" << endl;
        }else{
            cout << "3: The following read of x = " << x <<  " has a race" << endl;
        }
    }

}

void parallel_lp(){
    #pragma omp parallel for
        for(int i = 0; i < 9; i++){
            cout << i << endl;
        }
}