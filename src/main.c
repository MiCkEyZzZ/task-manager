#include <stdio.h>

#include "includes/file_operations.h"
#include "includes/task_operations.h"

int main() {
    loadTasksFromFile();
    do {
        printf("\nМенеджер задач\n");
        printf("===========================================================================\n");
        printf("[A] Добавить задачу (ввод описания и приоритета задачи)\n");
        printf("[V] Просмотреть задачи (вывод задач с возможностью переключения страниц)\n");
        printf("[D] Удалить задачу (удаление задачи по её номеру)\n");
        printf("[E] Редактировать задачу\n");
        printf("[M] Отметить задачу как выполненную (по её номеру)\n");
        printf("[S] Сортировать задачи по приоритету (от высокого к низкому)\n");
        printf("[F] Найти задачу по ключевому слову\n");
        printf("[X] Экспортировать задачи в CSV\n");
        printf("[I] Импортировать задачи из CSV\n");
        printf("[H] Помощь\n");
        printf("[Q] Выйти из программы (сохранение текущего состояния в файл)\n");
        printf("===========================================================================\n");
        printf("Выберите опцию: ");

        char choice = getchar();
        getchar(); // Удаляем символ новой строки из буфера

        switch (choice) {
            case 'A':
            case 'a':
                addTask();
                break;
            case 'V':
            case 'v':
                viewTasks();
                break;
            case 'D':
            case 'd':
                deleteTask();
                break;
            case 'E':
            case 'e':
                editTask();
                break;
            case 'M':
            case 'm':
                markTaskAsCompleted();
                break;
            case 'S':
            case 's':
                sortTasksByPriority();
                break;
            case 'F':
            case 'f':
                searchTasks();
                break;
            case 'X':
            case 'x':
                exportTasksToCSV();
                break;
            case 'I':
            case 'i':
                importTasksFromCSV();
                break;
            case 'H':
            case 'h':
                showHelp(); break;
            case 'Q':
            case 'q':
                saveTasksToFile();
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (1);

    return 0;
}
