#include "AbstractTask.h"

#ifndef LAB1_MASTERTASK_H
#define LAB1_MASTERTASK_H

class MasterTask : public AbstractTask {
public:
    MasterTask(string *taskType, int rank) : AbstractTask(taskType, rank) {
    }

    void perform(int id, int commSize);

private:

    void sendAccumulationTasksToWorkers(int *array, int arraySize, int workersCount);

    long receiveAccumulationResultsFromWorkers(int workersCount);

    int *generateRandomArray(int size);
};

#endif //LAB1_MASTERTASK_H
