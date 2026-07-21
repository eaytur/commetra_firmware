#ifndef HEARTBEAT_TASK_H
#define HEARTBEAT_TASK_H

typedef enum
{
    HEARTBEAT_TASK_OK = 0,
    HEARTBEAT_TASK_CREATION_FAILED
} HeartbeatTaskStatus;

HeartbeatTaskStatus HeartbeatTask_Create(void);

#endif // HEARTBEAT_TASK_H