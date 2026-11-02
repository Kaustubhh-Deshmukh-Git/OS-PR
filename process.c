
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int a[20], b[20], n, i, j, temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    int pid = fork();

    if(pid < 0)
    {
        printf("Process creation failed!");
    }

    // Child Process
    else if(pid == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());

        // Bubble Sort
        for(i = 0; i < n-1; i++)
        {
            for(j = 0; j < n-i-1; j++)
            {
                if(a[j] > a[j+1])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }
            }
        }

        printf("Child sorted array: ");
        for(i = 0; i < n; i++)
            printf("%d ", a[i]);

        printf("\n");

        exit(0);
    }

    // Parent Process
    else
    {
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());

        // Selection Sort
        for(i = 0; i < n-1; i++)
        {
            for(j = i+1; j < n; j++)
            {
                if(b[i] > b[j])
                {
                    temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                }
            }
        }

        printf("Parent sorted array: ");
        for(i = 0; i < n; i++)
            printf("%d ", b[i]);

        printf("\n");

        wait(NULL);

        printf("Child process completed.\n");
    }

    // Zombie Process Demonstration
    if(pid > 0)
    {
        printf("\nZombie Process Demonstration\n");

        int z = fork();

        if(z == 0)
        {
            printf("Zombie child terminated.\n");
            exit(0);
        }
        else
        {
            sleep(5);
            printf("Parent now calls wait().\n");
            wait(NULL);
        }
    }

    // Orphan Process Demonstration
    if(pid > 0)
    {
        printf("\nOrphan Process Demonstration\n");

        int o = fork();

        if(o == 0)
        {
            sleep(3);
            printf("Orphan Child PID: %d\n", getpid());
            printf("New Parent PID: %d\n", getppid());
        }
        else
        {
            printf("Parent is terminating.\n");
            exit(0);
        }
    }

    return 0;
}
