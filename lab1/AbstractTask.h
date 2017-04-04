#include <iostream>

#ifndef LAB1_TASK_H
#define LAB1_TASK_H
using std::cout;
using std::string;
using std::basic_ostream;
using std::invalid_argument;
using std::endl;

class AbstractTask {
protected:
    string *taskType;
    int rank;

    void logMsg(string *message) {
        logMsg(message->c_str());
    }

    void logMsg(const char *message) {
        cout << *taskType << " " << rank << ": " << message << endl;
    }

public:
    explicit AbstractTask(string *taskType, int rank) {
        if (taskType == NULL || rank < 0) {
            throw invalid_argument("taskType and rank are required arguments");;
        }
        this->taskType = taskType;
        this->rank = rank;
    }

    ~AbstractTask() {}

    virtual void perform(int id, int commSize)= 0;
};

#endif //LAB1_TASK_H
