#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    int flag = 0;

    #pragma omp parallel num_threads(3)
    {
        if(omp_get_thread_num() == 0){
            // Set the flag to release thread 1
            #pragma omp atomic update
            flag++;
            // Flush of flah is implied by atomic directive
        }
        else if(omp_get_thread_num() == 1)
        {
            // Wait until we see that flah reaches 1
            #pragma omp flush(flag)
            while(flag < 1){
                #pragma omp flush(flag)
            }
            print("Thread 1 finished\n");

            // Let's realse thread 2
            #pragma omp atomic update
            flag++;
        }
        else if(omp_get_thread_num() == 2)
        {
            // Loop until we see that flag reaches 2
            #pragma omp flush(flag)
            while(flag < 2){
                #pragma omp flush(flag)
            }
            print("Thread 2 awoken\n");
        }
    }

    return 0;
}