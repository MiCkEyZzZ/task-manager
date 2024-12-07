#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "includes/task.h"
#include "includes/user_input.h"
#include "includes/task_operations.h"

Task tasks[MAX_TASKS];
int taskCount = 0;

void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Список задач заполнен\n");
        return;
    }

    Task newTask;
    // Ввод описания задачи с валидацией
    getValidatedString(newTask.description, MAX_DESC_LENGTH, "Введите описание задачи");
    // Ввод приоритета задачи с валидацией
    newTask.description[strcspn(newTask.description, "\n")] = '\0';
    // Новая задача по умолчанию не выполнена
    newTask.completed = 0;
    tasks[taskCount++] = newTask;
    printf("Задача добавлена!\n");
}

void viewTasks() {
    const int PAGE_SIZE = 5; // Количество задач на одной странице
    int currentPage = 0;
    int totalPages = (taskCount + PAGE_SIZE - 1) / PAGE_SIZE;

    if (taskCount == 0) {
        printf("Список задач пуст. Добавьте задачи через меню.\n");
        return;
    }

    while (1) {
        printf("\nСтраница %d из %d\n", currentPage + 1, totalPages);
        printf("===================\n");

        for (int i = currentPage * PAGE_SIZE; i < (currentPage + 1) * PAGE_SIZE && i < taskCount; i++) {
            printf("%d. [%c] %s (Приоритет: %d)\n",
                    i + 1,
                    tasks[i].completed ? 'X' : ' ',
                    tasks[i].description,
                    tasks[i].priority);
        }

        printf("\nУправление страницами:\n");
        printf(" [N] - следующая страница\n");
        printf(" [P] - предыдущая страница\n");
        printf(" [Q] - вернуться в главное меню\n");

        char choice = getValidatedChoice("Введите команду", "NnPpQq");

        if (choice == 'N' || choice == 'n') {
            if (currentPage < totalPages - 1) {
                currentPage++;
            } else {
                printf("Вы на последней странице.\n");
            }
        } else if (choice == 'P' || choice == 'p') {
            if (currentPage > 0) {
                currentPage--;
            } else {
                printf("Вы на первой странице.\n");
            }
        } else if (choice == 'Q' || choice == 'q') {
            break;
        }
    }
}

void editTask() {
    if (taskCount == 0) {
        printf("Список задач пуст. Нет задач для редактирования.\n");
        return;
    }

    int taskIndex;
    printf("Введите номер задачи для редактирования: ");
    if (scanf("%d", &taskIndex) != 1 || taskIndex < 1 || taskIndex > taskCount) {
        printf("Ошибка: Неверный номер задачи.\n");
        while (getchar() != '\n'); // Очистка буфера ввода
        return;
    }
    getchar(); // Очистка буфера ввода после успешного scanf

    Task *task = &tasks[taskIndex - 1];

    printf("\nРедактирование задачи %d:\n", taskIndex);
    printf("1. Изменить описание (текущее: %s)\n", task->description);
    printf("2. Изменить приоритет (текущий: %d)\n", task->priority);
    printf("3. Изменить статус (текущий: %s)\n", task->completed ? "Выполнена" : "Не выполнена");
    printf("4. Выйти из редактирования\n");

    char choice = getValidatedChoice("Выберите опцию", "1234");

    switch (choice) {
        case '1':
            printf("Введите новое описание: ");
            getValidatedString(task->description, MAX_DESC_LENGTH, "Введите описание");
            printf("Описание обновлено!\n");
            break;
        case '2':
            task->priority = getValidatedInteger(1, 3, "Введите новый приоритет (1-Высокий, 2-Средний, 3-Низкий)");
            printf("Приоритет обновлён!\n");
            break;
        case '3':
            task->completed = !task->completed;
            printf("Статус задачи изменён на: %s\n", task->completed ? "Выполнена" : "Не выполнена");
            break;
        case '4':
            printf("Выход из редактирования.\n");
            break;
    }
}

void deleteTask() {
    if (taskCount == 0) {
        printf("Список задач пуст.\n");
        return;
    }

    int taskIndex;
    printf("Введите номер задачи для удаления: ");
    scanf("%d", &taskIndex);
    getchar();

    if (taskIndex < 1 || taskIndex > taskCount) {
        printf("Неверный номер задачи!\n");
        return;
    }

    // Сдвигаем все задачи на место удалённой
    for (int i = taskIndex - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    taskCount--;

    printf("Задача удалена!\n");
}

void markTaskAsCompleted() {
    if (taskCount == 0) {
        printf("Список задач пуст.\n");
        return;
    }

    int taskIndex;
    printf("Введите номер задачи для отметки как выполненная: ");

    if (scanf("%d", &taskIndex) != 1) {
        printf("Ошибка ввода! Пожалуйста, введите корректное число.\n");
        while (getchar() != '\n'); // Очистка буфера ввода
        return;
    }

    while (getchar() != '\n'); // Очистка буфера ввода после успешного ввода

    if (taskIndex < 1 || taskIndex > taskCount) {
        printf("Неверный номер задачи. Попробуйте снова.\n");
        return;
    }

    tasks[taskIndex - 1].completed = 1; // Помечаем задачу как выполненную
    printf("Задача %d отмечена как выполненная!\n", taskIndex);
}

void sortTasksByPriority() {
    if (taskCount == 0) {
        printf("Список задач пуст.\n");
        return;
    }

    // Простая сортировка пузырьком
    for (int i = 0;  i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    printf("Задачи отортированы по приоритету!\n");
}

void searchTasks() {
    if (taskCount == 0) {
        printf("Список задач пуст.\n");
        return;
    }

    char keyword[MAX_DESC_LENGTH];
    printf("Введите ключевое слово для поиска: ");
    fgets(keyword, MAX_DESC_LENGTH, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    printf("\nРезультат поиска:\n");
    int found = 0;

    for (int i = 0; i < taskCount; i++) {
        if (strstr(tasks[i].description, keyword) != NULL) {
            printf("%d. [%c] %s (Приоритет: %d)\n",
                    i + 1,
                    tasks[i].completed ? 'x' : ' ',
                    tasks[i].description,
                    tasks[i].priority);
            found = 1;
        }
    }

    if (!found) {
        printf("Задачи с ключевым словом \"%s\" не найдены.\n", keyword);
    }
}

void showHelp() {
    printf("\n--- Помощь ---\n");
    printf("Меню программы:\n");
    printf("A: Добавить задачу — добавляет новую задачу в список.\n");
    printf("V: Просмотреть задачи — отображает текущие задачи.\n");
    printf("E: Редактировать задачу — позволяет изменить описание, приоритет или статус задачи.\n");
    printf("D: Удалить задачу — удаляет выбранную задачу из списка.\n");
    printf("C: Отметить задачу как выполненную — отмечает задачу как завершённую.\n");
    printf("S: Сохранить задачи в файл — сохраняет текущий список задач на диск.\n");
    printf("L: Загрузить задачи из файла — загружает задачи из сохранённого файла.\n");
    printf("H: Помощь — показывает это меню справки.\n");
    printf("Q: Выйти — завершает программу.\n");
    printf("\nДля управления используйте буквы, указанные в меню.\n");
    printf("Примеры ввода: 'A' для добавления задачи или 'Q' для выхода.\n");
}
