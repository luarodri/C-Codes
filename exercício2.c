/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>


int main ()
{
    char str[10] = "Luanda";
    printf("\n\nString: %s", str);
    printf("\nSegunda letra: %c", str[1]);
    str[4] = 'n';
    printf("\nAgora a segunda letra é: %c", str[4]);
    printf("\n\nString resultante: %s", str);
 
    return 0;
}

