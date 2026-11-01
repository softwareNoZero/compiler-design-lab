#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include<string.h> 
 
#define SIZE 10 
 
char buffer1[SIZE+1], buffer2[SIZE+1]; 
FILE *fp; 
int currentBuffer = 1, forward = 0; 
int lexemeBegin = 0, line = 1; 
 
void loadBuffer(int buf) 
{ 
    int n; 
 
    if(buf == 1) 
    { 
        n = fread(buffer1, 1, SIZE, fp); 
        buffer1[n] = '\0'; 
    } 
    else 
    { 
        n = fread(buffer2, 1, SIZE, fp); 
        buffer2[n] = '\0'; 
    } 
} 
 
char getChar() 
{ 
    char ch; 
 
    if(currentBuffer == 1) 
    { 
        ch = buffer1[forward]; 
 
        if(ch == '\0') 
        { 
            currentBuffer = 2; 
            loadBuffer(2); 
            forward = 0; 
            lexemeBegin = 0; 
            ch = buffer2[forward]; 
        } 
    } 
    else 
    { 
        ch = buffer2[forward]; 
 
        if(ch == '\0') 
        { 
            currentBuffer = 1; 
            loadBuffer(1); 
            forward = 0; 
            ch = buffer1[forward]; 
        } 
    } 
 
    forward++; 
    return ch; 
} 
 
int iskeyword(char word[]) 
{ 
    char *keyword[] = { 
        "int","float","char","double", 
        "if","else","while","for", 
        "return","main" 
    }; 
 
    int i; 
 
    for(i = 0; i < 10; i++) 
    { 
        if(strcmp(word, keyword[i]) == 0) 
            return 1; 
    } 
 
    return 0; 
} 
 
void retract() 
{ 
    if(forward > 0) 
    { 
        forward--; 
    } 
} 
 
int main() 
{ 
    fp = fopen("input.txt", "r"); 
 
    if(fp == NULL) 
    { 
        printf("file not found\n"); 
        return 0; 
    } 
 
    loadBuffer(1); 
 
    char ch; 
    char lexeme[50]; 
    int i; 
 
    printf("\n%-15s %-15s %s\n", 
           "lexeme", "token", "line"); 
 
    while((ch = getChar()) != '\0') 
    { 
        if(ch == '\n') 
        { 
            line++; 
            continue; 
        } 
 
        if(isspace(ch)) 
            continue; 
 
        if(isalpha(ch) || ch == '_') 
        { 
            lexemeBegin = forward - 1; 
            i = 0; 
            lexeme[i++] = ch; 
 
            while(1) 
            { 
                ch = getChar(); 
 
                if(isalpha(ch) || ch == '_') 
                { 
                    lexeme[i++] = ch; 
                } 
                else 
                { 
                    retract(); 
                    break; 
                } 
            } 
 
            lexeme[i] = '\0'; 
 
            if(iskeyword(lexeme)) 
                printf("%-15s %-15s %d\n", 
                       lexeme, "keyword", line); 
            else 
                printf("%-15s %-15s %d\n", 
                       lexeme, "identifier", line); 
        } 
    } 
fclose(fp); 
return 0; 
}
