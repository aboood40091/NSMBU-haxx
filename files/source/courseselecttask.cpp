#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>

#include <log.h>

class CourseSelectTask : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(CourseSelectTask)

public:
    CourseSelectTask(const sead::TaskConstructArg& arg);
    virtual ~CourseSelectTask();

    void prepare() override;
    void enter() override;
    void exit() override;
    void calc() override;

private:
};

SEAD_TASK_SINGLETON_DISPOSER_IMPL(CourseSelectTask)

CourseSelectTask::CourseSelectTask(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "CourseSelectTask")
{
}

CourseSelectTask::~CourseSelectTask()
{
}

void CourseSelectTask::prepare()
{
    LOG("CourseSelectTask::prepare")
}

void CourseSelectTask::enter()
{
    LOG("CourseSelectTask::enter")
}

void CourseSelectTask::exit()
{
    LOG("CourseSelectTask::exit")
}

void CourseSelectTask::calc()
{
}
