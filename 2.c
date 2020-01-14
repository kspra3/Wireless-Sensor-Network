#include "master.h"

//Main driver function to run the MPI program
int main(argc, argv)
int argc;
char **argv;
{
    time_t what_time;
    double start_time, end_time;
    double time_spent;
    char* c_time;

    //open file for writing
    FILE *fptr;

    //Initialization of local variables
    int size, rank;
    int rand_val;
    int x_pos, y_pos;
    int rows = 4, columns = 5;

    //Initialization of MPI Commands
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   
    MPI_Status stat;

    //Initialization of local variables
    int values[4] = {-1, -1, -1, -1};
    int neighbours[4] = {-1, -1, -1, -1};
    int i;
    int neighbour;
    int iterations = 100;
    int grid[rows][columns][4];
    int up = 0;
    int down = 1;
    int left = 2;
    int right = 3;
    int counter = 0;
    char emptystring[10];
    
    //open file to write the messages into log.txt
    FILE *fp;
    fp = fopen("log.txt","w+");
    int random[1];
    if (rank != 20) {
        int buffer[1];
        while (iterations > 0){
            char messagepass[256];
            
            srand(clock());
            random[0] = rand()%5+1;

            x_pos = rank / columns;
            y_pos = rank % columns;

            //Top case
            if (x_pos - 1 >= 0) {
            neighbour = y_pos + (x_pos - 1)*columns;
            encrypt_decrypt(random,1);
            MPI_Send(random, 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD);
            counter++;
            MPI_Recv(&grid[rows][columns][up], 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD, &stat);
            encrypt_decrypt(&grid[rows][columns][up],1);
            values[0] = grid[rows][columns][up];
            neighbours[0] = neighbour;
            }

            //Bottom case
            if (x_pos + 1 <= rows-1) {
            neighbour = y_pos + (x_pos + 1)*columns;
            encrypt_decrypt(random,1);
            MPI_Send(random, 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD);
            counter++;
            MPI_Recv(&grid[rows][columns][down], 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD, &stat);
            encrypt_decrypt(&grid[rows][columns][down],1);
            values[1] = grid[rows][columns][down];   
            neighbours[1] = neighbour;
            }

            //Left case
            if (y_pos - 1 >= 0) {
            neighbour = (y_pos - 1) + (x_pos)*columns;
            encrypt_decrypt(random,1);
            MPI_Send(random, 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD);
            counter++;
            MPI_Recv(&grid[rows][columns][left], 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD, &stat);
            encrypt_decrypt(&grid[rows][columns][left],1);
            values[2] = grid[rows][columns][left];
            neighbours[2] = neighbour;
            }

            //Right case
            if (y_pos + 1 <= columns - 1) {
            neighbour = (y_pos + 1) + (x_pos)*columns;
            encrypt_decrypt(random,1);
            MPI_Send(random, 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD);
            counter++;
            MPI_Recv(&grid[rows][columns][right], 1, MPI_INT, neighbour, 0, MPI_COMM_WORLD, &stat);
            encrypt_decrypt(&grid[rows][columns][right],1);
            values[3] = grid[rows][columns][right];
            neighbours[3] = neighbour;
            }

            if (counter >= 3){
                start_time = MPI_Wtime();
                encrypt_decrypt(neighbours,4);
                MPI_Send(neighbours, 4, MPI_INT, 20, MSG_SEND, MPI_COMM_WORLD);
                MPI_Send(&start_time, 1, MPI_DOUBLE, 20, 12, MPI_COMM_WORLD);
                MPI_Send(buffer,0,MPI_INT, 20, MSG_EXIT, MPI_COMM_WORLD);
            }
            iterations -= 1;
        }
    
    }
    //This is the master, which is also rank 20, which also denotes the base station.
    else if (rank==20){
        base_station(c_time, what_time);
    }
    fclose(fp);
    MPI_Finalize();
    return 0;
}