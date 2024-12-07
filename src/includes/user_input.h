#ifndef USER_INPUT_H
#define USER_INPUT_H

char getValidatedChoice(const char *prompt, const char validChoices[]);
void getValidatedString(char *buffer, int maxLength, const char *prompt);
int getValidatedInteger(int min, int max, const char *prompt);

#endif // USER_INPUT_H
