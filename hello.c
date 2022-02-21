//writes hello + user input

#include<stdio.h>
#include<cs50.h>

int main(void)
{
    // use var to get name of user
    string name = get_string("What is your name?\n");

    // print hello and usr name
    printf("hello ,%s\n", name);
}
