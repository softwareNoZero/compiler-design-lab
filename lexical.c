#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][20] = {
    "int", "float", "char", "double", "if", "else",
    "while", "for", "return", "break", "continue",
    "void", "do", "switch", "case", "default",
    "long", "short", "unsigned", "signed", "const",
    "static"
};

// Function to check whether a word is a keyword
int isKeyword(char str[])
{
    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp;
    int ch;
    char buffer[100];
    int i;

    // Open the source code file
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open file!\n");
        return 1;
    }

    printf("%-20s %-15s\n", "Lexeme", "Token");
    printf("-----------------------------------\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        // Ignore whitespace
        if (isspace(ch))
        {
            continue;
        }

        // Identify keywords and identifiers
        if (isalpha(ch) || ch == '_')
        {
            i = 0;
            buffer[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_'))
            {
                if (i < (int)sizeof(buffer) - 1)
                    buffer[i++] = (char)ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(buffer))
                printf("%-20s %-15s\n", buffer, "Keyword");
            else
                printf("%-20s %-15s\n", buffer, "Identifier");
        }

        // Identify numeric constants
        else if (isdigit(ch))
        {
            i = 0;
            buffer[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.'))
            {
                if (i < (int)sizeof(buffer) - 1)
                    buffer[i++] = (char)ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            printf("%-20s %-15s\n", buffer, "Number");
        }

        // Identify operators
        else if (ch == '+' || ch == '-' || ch == '*' ||
                 ch == '/' || ch == '=' || ch == '<' ||
                 ch == '>' || ch == '%' || ch == '!')
        {
            char op[3];
            op[0] = (char)ch;
            op[1] = '\0';
            op[2] = '\0';

            int next = fgetc(fp);

            // Recognize common two-character operators
            if (next != EOF &&
                ((ch == '=' && next == '=') ||
                 (ch == '!' && next == '=') ||
                 (ch == '<' && next == '=') ||
                 (ch == '>' && next == '=') ||
                 (ch == '+' && next == '+') ||
                 (ch == '-' && next == '-') ||
                 (ch == '+' && next == '=') ||
                 (ch == '-' && next == '=') ||
                 (ch == '*' && next == '=') ||
                 (ch == '/' && next == '=') ||
                 (ch == '%' && next == '=') ||
                 (ch == '&' && next == '&') ||
                 (ch == '|' && next == '|')))
            {
                op[1] = (char)next;
                op[2] = '\0';
            }
            else if (next != EOF)
            {
                ungetc(next, fp);
            }

            printf("%-20s %-15s\n", op, "Operator");
        }

        // Identify delimiters and punctuation
        else if (ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' ||
                 ch == '[' || ch == ']' ||
                 ch == ';' || ch == ',' ||
                 ch == '.' || ch == ':')
        {
            printf("%-20c %-15s\n", ch, "Delimiter");
        }

        // Identify string literals
        else if (ch == '"')
        {
            i = 0;
            buffer[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF)
            {
                if (i < (int)sizeof(buffer) - 1)
                    buffer[i++] = (char)ch;

                if (ch == '"')
                    break;
            }

            buffer[i] = '\0';

            printf("%-20s %-15s\n", buffer, "String");
        }

        // Identify character literals
        else if (ch == '\'')
        {
            i = 0;
            buffer[i++] = (char)ch;

            while ((ch = fgetc(fp)) != EOF)
            {
                if (i < (int)sizeof(buffer) - 1)
                    buffer[i++] = (char)ch;

                if (ch == '\'')
                    break;
            }

            buffer[i] = '\0';

            printf("%-20s %-15s\n", buffer, "Character");
        }

        // Report unrecognized symbols
        else
        {
            printf("%-20c %-15s\n", ch, "Unknown");
        }
    }

    fclose(fp);

    return 0;
}
