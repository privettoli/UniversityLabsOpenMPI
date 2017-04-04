#include <map>

#ifndef LAB1_TASKINITIALIZER_H
#define LAB1_TASKINITIALIZER_H

class TaskRunner {
public:
    void runTask(int rank, int commSize);

    ~TaskRunner();
};

#endif //LAB1_TASKINITIALIZER_H
