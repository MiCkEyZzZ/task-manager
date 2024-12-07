#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "includes/task.h"
#include "includes/file_operations.h"

void saveTasksToFile() {
    FILE *file = fopen("data/tasks.txt", "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s|%d|%d\n",
            tasks[i].description,
            tasks[i].priority,
            tasks[i].completed);
    }

    fclose(file);
    printf("Задачи успешно сохранены в файл!\n");
}

void loadTasksFromFile() {
    FILE *file = fopen("data/tasks.txt", "r");
    if (file == NULL) {
        printf("Файл задач не найден, начат новый список.\n");
        return;
    }

    taskCount = 0; // Очищаем текущий список
    while (!feof(file) && taskCount < MAX_TASKS) {
        Task newTask;
        if (fscanf(file, "%[^|]|%d|%d\n",
                    newTask.description,
                    &newTask.priority,
                    &newTask.completed) == 3) {
            tasks[taskCount++] = newTask;
        }
    }

    fclose(file);
    printf("Задачи успешно загружены из файла!\n");
}

void exportTasksToCSV() {
    FILE *file = fopen("data/tasks.csv", "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи!\n");
        return;
    }

    // Записываем заголовки столбцов
    fprintf(file, "Описание,Приоритет,Статус\n");

    // Записываем задачи
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "\"%s\",%d,%s\n",
                tasks[i].description,
                tasks[i].priority,
                tasks[i].completed ? "Выполнен" : "Не выполнен");
    }

    fclose(file);
    printf("Задачи успешно экспортированы в файл data/tasks.csv!\n");
}

void importTasksFromCSV() {
    FILE *file = fopen("data/tasks.csv", "r");
    if (file == NULL) {
        printf("Файл data/tasks.csv не найден! Убедитесь, что файл существует.\n");
        return;
    }

    char line[512];
    int importedCount = 0;

    // Пропускаем заголовок
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (taskCount >= MAX_TASKS) {
            printf("Достигнут максимальный лимит задач! Некоторые задачи не были импортированы.\n");
            break;
        }

        Task newTask;
        char status[20];

        // Парсим строку CSV
        if (sscanf(line, "\"%[^\"]\",%d,%[^,\n]",
                    newTask.description,
                    &newTask.priority,
                    status) == 3) {
            // Конвертируем статус
            newTask.completed = (strcmp(status, "Выполнена") == 0) ? 1 : 0;
            tasks[taskCount++] = newTask;
            importedCount++;
        }
    }

    fclose(file);
    printf("Импортировано задач: %d\n", importedCount);
}
