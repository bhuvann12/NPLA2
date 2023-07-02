#include <stdio.h>
#include <stdlib.h>

int main()
{
    int input[10] = {0}, rem = 0, sent = 0, cap = 0, orate = 0;
    printf("Enter the bucket size: ");
    scanf("%d", &cap);
    printf("Enter the flowrate: ");
    scanf("%d", &orate);
    int i = 0, choice;
    do
    {
        printf("Data entered in second %d: ", i + 1);
        scanf("%d", &input[i]);
        if (input[i] > cap)
        {
            printf("Bucket overflow\n");
            exit(0);
        }
        i++;
        printf("Enter 1 for continue 0 for stop: ");
        scanf("%d", &choice);
    } while (choice);

    int n = i, drop = 0, x = 0;
    printf("Len %d\n", n);
    printf("\tSecond\t    Recieved\tSent\tDropped\t     Remaining\n");
    for (int i = 0; rem || i < n; i++)
    {
        printf("\t%d\t", i + 1);
        printf("\t%d\t", input[i]);
        printf("%d\t", (input[i] + rem) < orate ? (input[i] + rem) : orate);
        x = input[i] + rem - orate;
        if (x > 0)
        {
            if (x > cap)
            {
                rem = cap;
                drop = x - cap;
            }
            else
            {
                rem = x;
                drop = 0;
            }
        }
        else
        {
            rem = 0;
            drop = 0;
        }
        printf("%d\t", drop);
        printf("\t%d\n", rem);
    }
    return 0;
}
