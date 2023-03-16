#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int 
get_str_(char *buf, char *temp, int buf_len, int temp_len)
{
    int cnt = 0, cnt_begin;
    while (buf[cnt] == ' ' && (cnt < buf_len && cnt < temp_len))
        cnt++;
    if (cnt == buf_len || cnt == temp_len)
        return -1;
    cnt_begin = cnt;
    while (buf[cnt] != ' ' && (cnt < buf_len && cnt < temp_len))
    {
        temp[cnt - cnt_begin] = buf[cnt];
        cnt++;
    }
    temp[cnt - cnt_begin] = '\0';
    return cnt - cnt_begin;
}

int 
main(int argc, char **argv)
{
    int i, j;
    char *filename = "coef1";
    char *out_filename = "coef1_bin";
    FILE *f;

    char buf[301], temp[101], *buf2, *cur_buf;
    double *points, cur_val = 0.0;
    int num = 0, len;
    int cnt, len2 = 300;

    if (argc >= 3){
        for (i = 1; i < argc - 1; i++){
            if (strcmp(argv[i], "-in") == 0){
                filename = argv[i + 1];
            }
            else if(strcmp(argv[i], "-out") == 0){
                out_filename = argv[i + 1];
            }
        }
    }
    printf("Input file: %s\n", filename);
    printf("Output file: %s\n", out_filename);
    f = fopen(filename, "r");
    assert(f != NULL);
    
    while (fgets(buf, 300, f))
    {
        if (strcmp(buf, "\n") == 0)
            continue;
        cnt = get_str_(buf, temp, len2, 100);
        if (cnt == -1)
            continue;
        num = atoi(temp);

        len2 -= cnt;
        cnt = get_str_(buf + cnt, temp, len2, 100);
        if (cnt == -1)
            continue;
        len = atoi(temp);

        break;
    }
    printf("Coef num = %d, Coef len = %d\n", num, len);
    buf2 = (char *)malloc(sizeof(char) * len * 100);
    points = (double *)malloc(sizeof(double) * len * num);

    i = 0;
    while (i < num && fgets(buf2, len * 100, f))
    {
        cur_buf = buf2;
        len2 = len * 100;
        if (strcmp(cur_buf, "\n") == 0)
            continue;
        for (j = 0; j < len; j++)
        {
            cnt = get_str_(cur_buf, temp, len2, 100);
            if (cnt == -1)
                continue;
            len2 -= cnt;
            cur_buf = cur_buf + cnt;
            cur_val = atof(temp);
            points[len * i + j] = cur_val;
            // printf("%lf ", cur_val);
        }
        // printf("\n");
        ++i;
    }
    fclose(f);

    f = fopen(out_filename, "wb");
    fwrite(&num, sizeof(int), 1, f);
    fwrite(&len, sizeof(int), 1, f);
    fwrite(points, sizeof(double), len * num, f);
    fclose(f);

    free(points);
    free(buf2);
    return 0;
}
