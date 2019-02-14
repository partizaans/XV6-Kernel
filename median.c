#include "types.h"
#include "stat.h"
#include "user.h"

#define O_RDONLY 0x000
#define O_WRONLY 0x001
#define O_RDWR 0x002
#define O_CREATE 0x200

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

char *convertToString(int number) {
    int numberImage = number;
    int length = 0;
    while (numberImage != 0) {
        numberImage = numberImage / 10;
        length++;
    }
    char *string;
    string = (char *) malloc(length + 1);
    int i;
    for (i = length - 1; i >= 0; i--) {
        string[i] = (char) (number % 10 + 48);
        number = number / 10;
    }
    string[length] = '\n';
    return string;
}


int findLen(int number) {
    int len = 0;
    while (number != 0) {
        number = number / 10;
        len++;
    }
    return len;
}

int main(int argc, char *argv[]) {
    int argv_i[7];
    char *temp;
    int median_len;

    for (int i = 1; i < argc; ++i)
        argv_i[i - 1] = atoi(argv[i]);

    bubbleSort(argv_i, 7);
    //printf(1,"median : %d\n",argv_i[3] );

    int fd = open("result.txt", O_CREATE);
    close(fd);

    fd = open("result.txt", O_WRONLY);
    temp = convertToString(argv_i[3]);
    median_len = findLen(argv_i[3]);
    write(fd, temp, median_len + 1);
    close(fd);

    printf(1, "get pid result: %d\n", getpid());
    exit();
}
