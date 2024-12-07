#ifndef TASK_H
#define TASK_H

#define MAX_TASKS 100
#define MAX_DESC_LENGTH 256

// Структура для описания задачи
typedef struct {
    char description[MAX_DESC_LENGTH];
    int priority;                       // 1 - Высокий, 2 - Средний, 3 - Низкий
    int completed;                      // 0 - не выполнена, 1 - выполнена
} Task ;

// Глобальные переменные
extern Task tasks[MAX_TASKS];
extern int taskCount;

#endif // TASK_H
