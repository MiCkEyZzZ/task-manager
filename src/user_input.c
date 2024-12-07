#include <stdio.h>
#include <string.h>

#include "includes/user_input.h"

char getValidatedChoice(const char *prompt, const char validChoices[]) {
    char choice;
    while (1) {
        printf("%s (%s):", prompt, validChoices);
        choice = getchar();
        while (getchar() != '\n'); // Очистка буфера
        if (strchr(validChoices, choice)) {
            return choice;
        }
        printf("Ошибка: Введите один из допустимых символов (%s).\n", validChoices);
    }
}

void getValidatedString(char *buffer, int maxLength, const char *prompt) {
    while (1) {
        printf("%s (до %d символов): ", prompt, maxLength - 1);
        if (fgets(buffer, maxLength, stdin)) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Удаление символов новой строки
            if (strlen(buffer) > 0) {
                return;
            }
        }
        printf("Ошибка: Введите непустую строку.\n");
    }
}

int getValidatedInteger(int min, int max, const char *prompt) {
    int number;
    while (1) {
        printf("%s (от 0 %d до %d): ", prompt, min, max);
        if (scanf("%d", &number) == 1 && number >= min && number <= max) {
            while (getchar() != '\n'); // Очистка буфера
            return number;
        }
        printf("Ошибка: Введите корректное число от %d до %d.\n", min, max);
        while(getchar() != '\n'); // Очистка буфера ввода при ошибке
    }
}
