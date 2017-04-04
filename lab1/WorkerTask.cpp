#include "WorkerTask.h"
#include "Constants.h"
#include "StringUtils.h"
#include <mpi.h>
#include <numeric>

using namespace std;

void WorkerTask::perform(int id, int commSize) {
    logMsg("Waiting for incoming task…");
    MPI_Status status;
    int count;
    MPI_Recv(&count, 1, MPI_INT, FROM_MASTER, COUNT_TAG, MPI_COMM_WORLD, &status);
    logMsg(($("Received count: ") + $int(count)).c_str());
    int numbers[count];
    MPI_Recv(&numbers, count, MPI_INT, FROM_MASTER, ARRAY_TAG, MPI_COMM_WORLD, &status);
    auto stringifiedArray = StringUtils::intArrayToString(numbers, count);
    logMsg(($("Received array: ") + *stringifiedArray).c_str());

    auto sum = accumulate(numbers, numbers + count, int());
    logMsg(($("Sum of my part is ") + $int(sum)).c_str());

    MPI_Send(&sum, 1, MPI_INT, TO_MASTER, SUM_CALCULATED_TAG, MPI_COMM_WORLD);
}

WorkerTask::~WorkerTask() {

}
