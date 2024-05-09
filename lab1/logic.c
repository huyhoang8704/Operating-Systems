// logic function is called from display function
#include "calc.h"
void display(char *s) {
    char input[255]; // input a total string to check with the conditions then divide it into 3 parts
    char d[100]; // first part of the string to store in a
    char e[100]; // third part of the string to store in c
    char *endptr; // pointer to the end of the string
    double a, c, res = 0, check  =0; // a and c are the first and third part of the string, res is the result of the operation, check is used to check the syntax error
    char b; // second part of the string to store the operator
    bool ansExists = false; // check if the ans value exists
    double ansValue = 0; // store the ans value

  // open the file to read the ans value to use it across the program
  FILE *file = fopen("ans.txt", "r");
  if (file != NULL)
  {
    fscanf(file, "%lf", &ansValue);
    fclose(file);
    if (ansValue != 0)
    {
        ansExists = true;
    }
    }
    // loop to take the input from the user until the user types EXIT
    while (1) {
        system("clear");
        printf(">> ");

        fgets(input, sizeof(input), stdin);

        if (input[0] == 'E' && input[1] == 'X' && input[2] == 'I' && input[3] == 'T') {
            break; // break the loop if the user types EXIT
        }
        if (sscanf(input, "%s %c %s", d, &b, e) != 3) {
            printf("SYNTAX ERROR\n"); // check if the input is not in the correct format then divide the string into 3 parts
            check = 1;
        }
        a = strtod(d, &endptr); // convert the first part of the string to double
        if (strcmp("ANS", d) == 0 && (check != 1)) {
            a = ansValue; // if the first part of the string is ANS then assign the value of ansValue to a
        }
        else if (*endptr != '\0' && (check != 1)) {
        printf("SYNTAX ERROR\n"); // check if the first part of the string is not a number
            check = 1;

        }
        if ((errno == ERANGE) // check if the number is out of range
        || (errno != 0 && a == 0) && (check != 1)) {
            printf("SYNTAX ERROR\n");
            check = 1;
        }
        c = strtod(e, &endptr); // convert the third part of the string to double
        if (strcmp("ANS", e) == 0 && (check != 1)) {
            c = ansValue;
        }
        else if (*endptr != '\0' && (check != 1)) {
        printf("SYNTAX ERROR\n");
            check = 1;
        }
        if ((errno == ERANGE)
        || (errno != 0 && a == 0) && (check != 1)) {
            printf("SYNTAX ERROR\n");
            check = 1;
        }
        if (!((b == '+') || (b == '*') || (b == '-') || (b == '/') || (b == '%')) && (check != 1)) {
            printf("SYNTAX ERROR\n"); // check if the operator is not one of the 5 operators
            check = 1;
        }
        if( check != 1) { // if there is no syntax error then do the operation
            switch (b) {
                case '+':
                    res = a + c;
                    printf("%.2lf\n", res);
                    break;
                case '-':
                    res = a - c;
                    printf("%.2lf\n", res);
                    break;
                case '*':
                    res = a * c;
                    printf("%.2lf\n", res);
                    break;
                case '/':
                    if (c == 0) {
                        printf("MATH ERROR\n");
                    }else{
                    res = a / c;
                    printf("%.2lf\n", res);
                    }
                    break;
                case '%':
                    if (c == 0) {
                        printf("MATH ERROR\n");
                    }else{
                    res = (int)a % (int)c;
                    printf("%.2lf\n", res);
                    }
                    break;
                default:
                    continue;
            }
            ansExists = true; // if the operation is done then the ans value exists
            res = ansValue; // assign the result to the ansValue
            file = fopen("ans.txt", "w"); // open the file to write the ans value
            if (file != NULL) {
                fprintf(file, "%.2lf", ansValue);
                fclose(file);
            }
        }
        check = 0; // reset the check value
        printf("Press Enter to continue\n"); // ask the user to press enter to continue
        scanf("%c", &b); // take the enter value
        continue; // continue the loop
    }
    return;
}
