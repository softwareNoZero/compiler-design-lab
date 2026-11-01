- #include <stdio.h> 
#include <ctype.h> 
#include <string.h> 
char keywords[][20] = 
{"int","float","char","double","if","else","while","for","return","break","continue","void","do","switch","
case", 
"default","long","short","unsigned","signed","const","static" 
}; 
int isKeyword(char str[]) 
{ 
} 
int n = sizeof(keywords) / sizeof(keywords[0]); 
for(int i = 0; i < n; i++) 
{ 
} 
if(strcmp(str, keywords[i]) == 0) 
return 1; 
return 0; 
int main() 
{ 
FILE *fp; 
char ch, buffer[100]; 
int i; 
 
    fp = fopen("input.txt", "r"); 
 
    if(fp == NULL) 
    { 
        printf("Cannot open file!\n"); 
        return 0; 
    } 
 
    printf("%-20s %-15s\n", "Lexeme", "Token"); 
 
    while((ch = fgetc(fp)) != EOF) 
    { 
         
        if(isalpha(ch) || ch == '_') 
        { 
            i = 0; 
            buffer[i++] = ch; 
 
            while((ch = fgetc(fp)) != EOF && 
                  (isalnum(ch) || ch == '_')) 
            { 
                buffer[i++] = ch; 
            } 
 
            buffer[i] = '\0'; 
 
            if(ch != EOF) 
                ungetc(ch, fp); 
 
            if(isKeyword(buffer)) 
                printf("%-20s %-15s\n", buffer, "Keyword"); 
            else 
                printf("%-20s %-15s\n", buffer, "Identifier"); 
        } 
 
       
        else if(isdigit(ch)) 
        { 
            i = 0; 
            buffer[i++] = ch; 
 
            while((ch = fgetc(fp)) != EOF && 
                  (isdigit(ch) || ch == '.')) 
            { 
                buffer[i++] = ch; 
            } 
 
            buffer[i] = '\0'; 
 
            if(ch != EOF) 
                ungetc(ch, fp); 
 
            printf("%-20s %-15s\n", buffer, "Number"); 
        } 
 
        
        else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || 
                ch=='=' || ch=='<' || ch=='>' || ch=='%') 
        { 
            printf("%-20c %-15s\n", ch, "Operator"); 
        } 
 
         
        else if(ch=='(' || ch==')' || ch=='{' || ch=='}' || 
                ch=='[' || ch==']' || ch==';' || ch==',') 
        { 
            printf("%-20c %-15s\n", ch, "Delimiters"); 
        } 
 
        
        else if(ch == '"') 
        { 
            i = 0; 
            buffer[i++] = ch; 
 
            while((ch = fgetc(fp)) != EOF) 
            { 
                buffer[i++] = ch; 
                if(ch == '"') 
                    break; 
            } 
 
            buffer[i] = '\0'; 
 
            printf("%-20s %-15s\n", buffer, "String"); 
        } 
 
         
        else if(ch == '\'') 
        { 
            i = 0; 
            buffer[i++] = ch; 
 
            while((ch = fgetc(fp)) != EOF) 
            { 
                buffer[i++] = ch; 
                if(ch == '\'') 
                    break; 
            } 
 
            buffer[i] = '\0'; 
 
            printf("%-20s %-15s\n", buffer, "Character"); 
} 
} 
fclose(fp); 
return 0; 
}
