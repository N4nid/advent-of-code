#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArr(int len, int arr[len]) {
  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }
}

int isSafe(int len, int arr[len], int index) { // int index is the one to skip
  int prev = -1;
  int ascending = -1;
  int safe = 1;
  for (int i = 0; i < len; i++) {
    if (i != index) {
      int num = arr[i];
      if (prev != -1) {
        int delta = num - prev;
        if (delta == 0 || delta > 3 || delta < -3) {
          // printf("out of range: %d\n", delta);
          safe = 0;
          break;
        }
        if (ascending == -1) { // does not know if ascending or not
          if (delta > 0) {
            ascending = 1;
          } else {
            ascending = 0;
          }
        } else if (ascending == 1) { // unsafe because not ascending anymore
          if (delta < 0) {
            // printf("not asc anymore\n");
            safe = 0;
            break;
          }
        } else {
          if (delta > 0) { // unsafe because not descending anymore
            // printf("not desc anymore\n");
            safe = 0;
            break;
          }
        }

        prev = num;

      } else {
        prev = num;
      }
    }
  }
  return safe;
}

void read_ints(const char *file_name) {
  FILE *file = fopen(file_name, "r");
  char fline[256];
  int amountSafeReports = 0;

  if (file != NULL) {
    while (fgets(fline, sizeof(fline), file)) {
      char line[256];
      memcpy(line, fline, sizeof(line));
      // Print each line to the standard output.
      // printf("%s", line);
      char *delim = " ";
      char *token = strtok(line, delim);

      int count = 0;
      while (token != NULL) { // count for array len
        count++;
        token = strtok(NULL, delim);
      }

      memcpy(line, fline, sizeof(line));
      token = strtok(line, delim);
      // printf("asd %s", line);

      int arr[count];
      int i = 0;

      while (token != NULL) { // write into array
        arr[i] = atoi(token);
        // printf("- %d\n", arr[i]);
        i++;
        token = strtok(NULL, delim);
      }
      // printArr(count, arr);

      int prev = -1;
      int ascending = -1;
      int ind[3];
      int unsafe = 0;

      // check if safe or return possible indices
      for (int i = 0; i < count; i++) {
        int num = arr[i];
        if (prev != -1) {
          int delta = num - prev;
          if (delta == 0 || delta > 3 || delta < -3) {
            // printf("out of range: %d\n", delta);
            ind[0] = i;
            ind[1] = i - 1;
            ind[2] = -1;

            unsafe = 1;
            break;
          }
          if (ascending == -1) { // does not know if ascending or not
            if (delta > 0) {
              ascending = 1;
            } else {
              ascending = 0;
            }
          } else if (ascending == 1) { // unsafe because not ascending anymore
            if (delta < 0) {
              // printf("not asc anymore\n");
              ind[0] = 0;
              ind[1] = i;
              ind[2] = i - 1;
              unsafe = 1;
              break;
            }
          } else {
            if (delta > 0) { // unsafe because not descending anymore
              // printf("not desc anymore\n");
              ind[0] = 0;
              ind[1] = i;
              ind[2] = i - 1;
              unsafe = 1;
              break;
            }
          }

          prev = num;

        } else {
          prev = num;
        }
      }

      if (unsafe != 0) {
        int safe = 0;
        for (int i = 0; i < 3; i++) {
          safe = isSafe(count, arr, ind[i]);
          if (safe == 1) {
            printArr(count, arr);
            printf("worked :%d\n", ind[i]);
            amountSafeReports++;
            break;
          }
        }
      } else {
        amountSafeReports++;
      }
    }
    printf("safe :%d\n", amountSafeReports);

    fclose(file);
  }
}

int main() {
  read_ints("puzzle-input.txt");
  // read_ints("test.txt");
  return 0;
}
