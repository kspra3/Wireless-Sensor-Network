#include "master.h"

//This is the master, which is also rank 20, which also denotes the base station.
void base_station(char* c_time_string, time_t what_time) {
    FILE *fp;
    fp = fopen("log.txt","w+");
    int size;
    int no_msg;
    int recv_arr[4];
    double recv;
    MPI_Status status;
    MPI_Status timestat;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //Getting the messages from any source if available
    while ((size - 1)>0){
        c_time_string = ctime(&what_time);
        MPI_Recv(recv_arr, 4, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        double endtime = MPI_Wtime();
        double encrypt_start_time = MPI_Wtime();
        encrypt_decrypt(recv_arr,4);
        double encrypt_end_time = MPI_Wtime();
        double encrypt_time = encrypt_end_time - encrypt_start_time;
        MPI_Recv(&recv, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 12, MPI_COMM_WORLD, &timestat);
        double timespent = endtime - recv;
        switch(status.MPI_TAG){
            case MSG_EXIT: size--;
            break;
            case MSG_SEND:     
            fprintf(fp, "==========================================================\n");
            fprintf(fp, "Reference Node: %d  \nNeighbours: (%d,%d,%d,%d) \nCommunication Time: %lf\nTimestamp: %s\nEncrypt Time: %lf", status.MPI_SOURCE, recv_arr[0] , recv_arr[1], recv_arr[2], recv_arr[3], timespent, c_time_string, encrypt_time);
            printf("==========================================================\n");
            printf("Reference Node: %d  \nNeighbours: (%d,%d,%d,%d) \nCommunication Time: %lf\nTimestamp: %s\nEncrypt Time: %lf", status.MPI_SOURCE, recv_arr[0] , recv_arr[1], recv_arr[2], recv_arr[3], timespent, c_time_string, encrypt_time);  
        }  
    }
}