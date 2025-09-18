#include <stdio.h>
#include <string.h>

int main()
{
    FILE *macro, *minput, *moutput;
    char s1[10], s2[10];
    int flag = 0;

    macro = fopen("macro.txt", "r");
    minput = fopen("minput.txt", "r");
    moutput = fopen("moutput.txt", "w");

    while (fscanf(minput, "%s%s", s1, s2) > 0)
    {
        if (strcmp(s2, "**") == 0 && strcmp(s1, "END"))
        {
            char m1[10], m2[10];
            while (fscanf(macro, "%s%s", m1, m2) > 0)
            {
                if (strcmp(m1, "MACRO") == 0 && strcmp(s1, m2) == 0)
                {
                    flag = 1;
                    continue;
                }
                else if (strcmp(m1, "MEND") == 0)
                {
                    flag = 0;
                    break;
                }

                if (flag = 1)
                {
                    fprintf(moutput, "");
                }
            }
        }
    }
}