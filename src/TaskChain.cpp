/*
 * TaskChain.cpp
 *
 *  Created on: 2018年3月16日
 *      Author: cplusplus
 */

#include "TaskChain.h"

namespace BusinessUtil{
////
TaskChain::TaskChain()
:m_size(0),
 m_pos(0)
{
}

void TaskChain::AddTask(std::shared_ptr<ITask> task)
{
    ++m_size;
    m_task.push_back(task);
}

void TaskChain::ChainProcess(void *obj , TaskChain *taskChain)
{
    if(m_pos >= m_size)
        return ;
    if(taskChain == nullptr)
        taskChain = this;

    m_task.at(m_pos++)->TaskProcess(obj , taskChain);
}



ITask::ITask()
{

}
ITask::~ITask()
{

}

void ITask::TaskProcess(void *obj , TaskChain *taskChain)
{
    DoTask(obj);
    taskChain->ChainProcess(obj , taskChain);
}
}
