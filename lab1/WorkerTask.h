#include "AbstractTask.h"

#ifndef LAB1_WORKERTASK_H
#define LAB1_WORKERTASK_H

class WorkerTask : public AbstractTask {
public:
    WorkerTask(string *taskType, int rank) : AbstractTask(taskType, rank) {
    }

    ~WorkerTask();

    void perform(int id, int commSize);
};

#endif //LAB1_WORKERTASK_H
