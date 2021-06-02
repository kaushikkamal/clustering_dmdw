#include <stdio.h>
    int
    main()
{
    FILE *file;
    int a;
    float b, c, d;
    char ch;

    file = fopen("dataset.txt", "r");

    if (file == NULL)
    {
        printf("Cannot open file!\n");
        return 0;
    }

    ch = fscanf(file, "%d\t%f\t%f\t%f\n", &a, &b, &c, &d);

    while (ch != EOF)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n", a, b, c, d);
        ch = fscanf(file, "%d\t%f\t%f\t%f\n", &a, &b, &c, &d);
    }

    fclose(file);
    return 0;
}
