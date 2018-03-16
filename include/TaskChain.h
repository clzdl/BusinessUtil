/*
 * TaskChain.h
 *
 *  Created on: 2018年3月16日
 *      Author: cplusplus
 */

#ifndef INCLUDE_TASKCHAIN_H_
#define INCLUDE_TASKCHAIN_H_

#include <vector>
#include <memory>

namespace BusinessUtil{
class ITask;

class TaskChain
{
public:
    TaskChain();

    void AddTask(std::shared_ptr<ITask> task);
    void ChainProcess(void *obj , TaskChain *taskChain = nullptr);
private:
    TaskChain(const TaskChain &tc) = delete;
    TaskChain& operator = (const TaskChain &tc) = delete;
    TaskChain(TaskChain &&tc) = delete;
    TaskChain& operator = (TaskChain &&tc) = delete;

    std::vector< std::shared_ptr<ITask> > m_task;
    int m_size; ///任务数
    int m_pos;  ///当前执行的任务偏移量
};



class ITask
{
public:
    ITask();
    virtual ~ITask();
    virtual void DoTask(void *obj) = 0;
    void TaskProcess(void *obj , TaskChain *taskChain);
};

}

#endif /* INCLUDE_TASKCHAIN_H_ */
