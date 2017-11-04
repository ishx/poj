//Problem Id:1048
 
#include <stdio.h> 

#define SIZE    200 

char* genFormula(char* f, char g[SIZE][SIZE], int row, int col) { 
    int op, ch; 
    if ((op = g[row][col]) == 'o' || op == '>' || op == ')') { 
        /* 
        *f ++ = op; 
        */ 
        g[row][col] = '*'; 
        if (op != 'o') { 
            f = genFormula(f, g, row - 1, col - 1); 
            f = genFormula(f, g, row + 1, col - 1); 
            *f ++ = op; *f = 0; 
            return f; 
        } 
    } 
    else if (op >= 'A' && op <= 'Z' ) { 
        *f ++ = op; g[row][col] = '*'; *f = 0; return f; 
    } 
    else g[row][col] = '*'; 
    if ((ch = g[row - 1][col] ) != ' ' && ch != '*') { 
        while (ch == '|') { g[row -- - 1][col] = '*'; ch = g[row - 1][col]; } 
        f = genFormula(f, g, row - 1, col); 
    } 
    if ((ch = g[row + 1][col] ) != ' ' && ch != '*') { 
        while (ch == '|') { g[row ++ + 1][col] = '*'; ch = g[row + 1][col]; } 
        f = genFormula(f, g, row + 1, col); 
    } 
    if ((ch = g[row][col - 1] ) != ' ' && ch != '*') { 
        while (ch == '-') { g[row][col -- - 1] = '*'; ch = g[row][col - 1]; } 
        f = genFormula(f, g, row, col - 1); 
    } 
    if ((ch = g[row][col + 1] ) != ' ' && ch != '*') { 
        while (ch == '-') { g[row][col ++ + 1] = '*'; ch = g[row][col + 1]; } 
        f = genFormula(f, g, row, col + 1); 
    } 
    if (op == 'o') { *f ++ = op; *f = 0; } 
    return f; 
} 

int logicValue(char* m, char* f) { 
    static int stack[32], top; 
    static char ch; 
    top = 0; 
    while (ch = *f ++) { 
        if (ch >= 'A' && ch <= 'Z') stack[top ++] = m[ch - 'A'] - '0'; 
        else if (ch == 'o') stack[top - 1] = !stack[top - 1]; 
        else if (ch == '>') { top --; stack[top - 1] |= stack[top]; } 
        else if (ch == ')') { top --; stack[top - 1] &= stack[top]; } 
    } 
    return stack[top - 1]; 
} 

int main (void) { 
    int set = 0, r, c, i; 
    char g[SIZE][SIZE], m[28], f[256]; 
    int row, col; 

    while (1) { 
        row = col = - 1; memset(g, ' ', sizeof(g) ); 
        for (r = 1; (g[r][c = 1] = getchar() ) != EOF && g[r][c] != '*'; r ++) { 
            while (g[r][c] != '\n' && (g[r][++ c] = getchar() ) != '\n') 
                if (row < 0 && g[r][c] == '?') { row = r; col = c; } 
            g[r][c] = ' '; 
        } 
        if (r == 1) break; 
#ifdef __DEBUG__ 
        for (i = 1; i < r; i ++) g[i][101] = 0, printf("%s\n", &(g[i][1]) ); 
#endif 
        genFormula(f, g, row, col); 
#ifdef __DEBUG__ 
        for (i = 1; i < r; i ++) g[i][101] = 0, printf("%s\n", &(g[i][1]) ); 
        printf("Formula: %s\n", f); 
#endif 
        while (scanf("%s", m) == 1 && getchar() && m[0] != '*') { 
#ifdef __DEBUG__ 
            printf("%s\n", m); 
#endif 
            printf("%d\n", logicValue(m, f) ); 
        } 
putchar('\n'); 
    } 

    return 0; 
}