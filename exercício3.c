/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>


int main ()
{
    int num;
    printf ("Digite um número: ");
    scanf ("%d",&num);
    if (num > 100)
    printf ("\n\nO número é maior que 100.");
    if (num == 100)
    {
    printf ("\n\nVocê acertou!\n");
    printf ("O número é igual a 100.");
    }
    if (num < 100)
    printf ("\n\nO número é menor que 100"); 
    
    return 0;
}

