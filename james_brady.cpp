#include<iostream>
#include<pthread.h>
#include<cstdlib>
#include<ctime>

int CirclePoints=0; // points in circle
int AllCPoints = 0; // all points in circle in each thread
int points = 500; // total number of random points to generate
int totalPoints = 0; // all points plotted in each thread

double pRand() {
        double pMax = 1;
        double pMin = -1;
        double p = (double)rand() / RAND_MAX;
        return pMin + p * (pMax - pMin);
}

void *plot(void *X) {
        CirclePoints = 0;
        for(int i = 0; i < points; i++) { // creating 500 random points
                double X = pRand();
                double Y = pRand();
                if(X * X + Y * Y <= 1) {
                        CirclePoints++; // if a point is found in the circle
                }
        }
    return NULL;
}

int main() {
        srand(time(NULL));

        pthread_t thread[10]; // creating an array of 10 threads
        
        for (int i = 0; i < 10; i++) { // creating 10 threads
                
                totalPoints = totalPoints + points; // adding all plotted points
                
                pthread_create(&thread[i], NULL, &plot, NULL);
                pthread_join(thread[i], NULL);
                points = points + 500;
                AllCPoints = AllCPoints + CirclePoints; // adding all plotted points in circle
                double PI = (4.0 * AllCPoints) / totalPoints; // calulating pie
                
        std::cout<< "thread " << i << " pi = " << PI << "\n";
        }

        return 0;
}