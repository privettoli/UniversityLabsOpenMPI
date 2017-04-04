#include "TaskRunner.h"
#include "AbstractTask.h"
#include "MasterTask.h"
#include "WorkerTask.h"
#include "Constants.h"

using std::string;
using std::map;

typedef AbstractTask *(*AbstractTaskInitializer)(int);

AbstractTask *getMasterTask(int rank) {
    return new MasterTask(new string("Master"), rank);
}

AbstractTask *getWorkerTask(int rank) {
    return new WorkerTask(new string("Worker"), rank);
}

map<int, AbstractTaskInitializer> *initSpecialTasks() {
    auto tasks = new map<int, AbstractTaskInitializer>();
    tasks->emplace(TO_MASTER, &getMasterTask);
    return tasks;
}

auto specialTasks = initSpecialTasks();
auto defaultTask = getWorkerTask;

void TaskRunner::runTask(int rank, int commSize) {
    auto taskInitializerIter = specialTasks->find(rank);
    AbstractTaskInitializer taskInitializer = NULL;
    if (taskInitializerIter != specialTasks->end()) {
        taskInitializer = taskInitializerIter->second;
    } else {
        taskInitializer = defaultTask;
    }
    auto task = taskInitializer(rank);
    task->perform(rank, commSize);
    delete task;
}

TaskRunner::~TaskRunner() {
    delete specialTasks;
}
