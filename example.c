#include <stdio.h>

int add(int a, int b)
{
    int sum = a + b;
    return sum;
}

int main()
{   
    printf("hello world\n");
    printf("%i\n", add(1,2));


    int input = 0;
    scanf("%i", &input);

    return 0;
}
