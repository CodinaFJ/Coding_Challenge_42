#include <stdio.h>
#include <stdlib.h>

int word_puzzle(size_t N, char **words)
{
    int i = 1;
    int j = -1;
    char    last;

    while (words[i][++j])
    {
        ;
    }
    last = words[i][j - 1];
    while(words[++i])
    {
        j = -1;

        if (words[i][0] != last)
            return (1);
        while (words[i][++j])
            ;        
        last = words[i][j - 1]; 
    }
    return (0);
}


int main(int argc, char **argv)
{
    printf("res: %d\n", word_puzzle(argc - 1, argv));
    return (0);
}