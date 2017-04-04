#include "MasterTask.h"
#include "StringUtils.h"
#include "Constants.h"
#include <random>
#include <mpi.h>

using std::string;
using std::cout;
using std::runtime_error;
using std::to_string;
using std::endl;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::generate;

void MasterTask::perform(int masterId, int commSize) {
    auto workersCount = commSize - 1;
    if (masterId != TO_MASTER) {
        logMsg("Bad TO_MASTER define. The app won't work properly");
        MPI_Abort(MPI_COMM_WORLD, BAD_TO_MASTER_DEFINE_ERROR);
        return;
    }
    if (workersCount < 1) {
        logMsg("No workers available");
        MPI_Abort(MPI_COMM_WORLD, NO_WORKERS_RUNNING_ERROR);
        return;
    }
    logMsg("Up and running");
    {
        auto arraySize = rand() % MAX_RANDOM_GENERATED_ARRAY_SIZE;
        auto array = generateRandomArray(arraySize);
        auto stringifiedArray = StringUtils::intArrayToString(array, arraySize);
        logMsg(($("Randomly generated array of size ") + $int(arraySize) + $(" is ") + *stringifiedArray).c_str());
        sendAccumulationTasksToWorkers(array, arraySize, workersCount);
        delete[] array;
    }
    logMsg("All parts were sent. Requesting accumulation results…");
    auto sum = receiveAccumulationResultsFromWorkers(workersCount);
    logMsg(($("Total sum is ") + $int(sum)).c_str());
}

void MasterTask::sendAccumulationTasksToWorkers(int *array, int arraySize, int workersCount) {
    auto defaultStep = (int) ceil((double) arraySize / workersCount);
    auto countRequests = new MPI_Request[workersCount];
    auto requests = new MPI_Request[workersCount];
    auto statuses = new MPI_Status[workersCount];
    for (auto requestsCounter = 0, shift = 0; shift < arraySize; shift += defaultStep, requestsCounter++) {
        auto actualStep = shift + defaultStep < arraySize ? defaultStep : arraySize - shift;
        auto toWorkerId = requestsCounter + 1;
        logMsg(($("Sending to Worker ") + $int(toWorkerId) + $(" from ") + $int(shift) + $(" to ") +
                $int(shift + actualStep)).c_str());
        MPI_Isend(&actualStep, 1, MPI_INT, toWorkerId, COUNT_TAG, MPI_COMM_WORLD,
                  &(countRequests)[requestsCounter]);
        MPI_Isend(array + shift, actualStep, MPI_INT, toWorkerId, ARRAY_TAG, MPI_COMM_WORLD,
                  &(requests)[requestsCounter]);
        logMsg(($("Sent to Worker ") + $int(toWorkerId)).c_str());
    }
    MPI_Waitall(workersCount, countRequests, statuses);
    MPI_Waitall(workersCount, requests, statuses);
    delete[] countRequests;
    delete[] requests;
    delete[] statuses;
}

long MasterTask::receiveAccumulationResultsFromWorkers(int workersCount) {
    auto sum = 0L;
    for (auto i = 0; i < workersCount; ++i) {
        MPI_Status status;
        int partSum;
        MPI_Recv(&partSum, 1, MPI_INT, MPI_ANY_SOURCE, SUM_CALCULATED_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_ERROR != MPI_SUCCESS) {
            throw runtime_error($("Request from worker ") + $int(i + 1) + $(" failed. ") +
                                $int(status.MPI_ERROR));
        }
        logMsg(($("From Worker ") + $int(status.MPI_SOURCE) + $(" part sum ") + $int(partSum)).c_str());
        sum += partSum;
    }
    return sum;
}

int *MasterTask::generateRandomArray(int size) {
    random_device rd;
    default_random_engine dre(rd());
    uniform_int_distribution<int> uid(MIN_RANDOM_GENERATED_NUMBER, MAX_RANDOM_GENERATED_NUMBER);
    int *array = new int[size];
    generate(array, array + size, [&]() { return uid(dre); });
    return array;
}
