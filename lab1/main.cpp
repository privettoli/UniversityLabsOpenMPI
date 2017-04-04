#include <iostream>
#include <mpi.h>
#include <zconf.h>
#include "TaskRunner.h"

using namespace std;


int main() {
    srand((unsigned) time(NULL) * getpid());
    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
    auto taskRunner = new TaskRunner();

    taskRunner->runTask(rank, size);

    MPI_Finalize();
    delete taskRunner;
    return 0;
}