#include <stdio.h>  
#include <mpi.h> 

int main(int argc, char** argv) {  
    int i,myid, size, tag = 100; //myid will store ranks of processes
    char message_send[50] , message_recv[50];
    MPI_Status status; //datatype MPI_Status

    MPI_Init(&argc, &argv); //first mpi function to be called. All functions start with MPI_. Case sensitive, returns error code / success
   //arguments to be passed to all processes. Else can pass Null. Tells MPI to allocate buffer/ memory to send/ receive. Ready to run code.
    MPI_Comm_size(MPI_COMM_WORLD, &size); //MPI_COMM_WORLD: variables/ macros capitalized. MPI_Comm_size: fills how many processes are there. Returned in arg size.
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); //MPI_Comm_rank: returns id of process that calls it.
    //MPI_COMM_WORLD: Default MPI communicator, set of processes that can talk to each other by send/ recieve commands. 
    //Processes within a communicator can only talk to each other.

    if(myid !=0){ //If not the designated process to receive, just send the data. id =0 will recieve all data and print.
        sprintf(message_send, "Hello from process id : %d \n", myid);
        MPI_Send(message_send, 50, MPI_CHAR, 0, tag, MPI_COMM_WORLD); //send data , 50 values of datatype char, 0: send to 0th process id.
        //sending to 0th process.
    }else{ //when rank = 0
        for(i = 1; i< size; i++){
            MPI_Recv(message_recv, 50, MPI_CHAR, i, tag, MPI_COMM_WORLD, &status); //receive from ith process. 
            printf("\n %s", message_recv);
        }
          sprintf(message_send, "Hello from process id : %d \n", myid);
           printf("\n %s", message_send);
    }
    MPI_Finalize(); //last mpi function to be called. Returns error code/ success code of type int. MPI informed, no more MPI calls. Free memory allocated
    return 0;  
}  