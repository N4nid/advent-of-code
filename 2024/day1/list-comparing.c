#include <stdio.h>
#include <stdlib.h>

void printArr(int len,int arr[len]){
  for(int i = 0; i < len; i++) {
    printf("%d \n",  arr[i]);
  }
}

void insertionSort(int len,int arr[len]){
  for(int i = 0; i < len; i++) {
    int newVal = arr[i];
    int newPos = -1;
    //printf("%d\n",  arr[i]);

    //find positon to insert newVal
    for(int j = 0; j <= i; j++) {
      if(newVal < arr[j]){
        newPos = j;
        break;
      }
    }

    //insert
    if(newPos != -1 && newPos != i){
      for(int j = i; j >= newPos; j--) {
        arr[j] = arr[j-1];
      }
      arr[newPos] = newVal;
    }

  }
  //printArr(len, arr);

}

void read_ints (const char* file_name,int len, int arr[len])
{
  FILE* file = fopen (file_name, "r");
  int i = 0;
  int j = 0;

  fscanf (file, "%d", &i);    
  while (!feof (file))
    {  
      //printf ("%d\n", i);
      arr[j] = i;
      j++;
      fscanf (file, "%d", &i);      
    }
  fclose (file);        
}

int calcTotalDelta(int len, int list1[len], int list2[len]){ // only works if lists are same size
  int total = 0;
  for (int i = 0; i < len; i++) {
    int dist = list1[i] - list2[i];
    if(dist < 0){
      dist = dist * -1;
    }
    //printf ("1: %d 2: %d delta = %d \n", list1[i], list2[i],dist);
    total += dist;
  }
  return total;
}

int countAppearences(int num, int len, int list[len]){
  int count = 0;
  for (int i = 0; i < len; i++) {
    if(num == list[i]){
      count++;
      
    }else if (num < list[i]) {
      break;
    }
  }
  if(count > 0){
    printf ("num: %d count: %d\n", num, count);
  }
  return count;
}

int calcSimilarity(int len, int list1[len], int list2[len]){
  int total = 0;
  for (int i = 0; i < len; i++) {
     total += list1[i] * countAppearences(list1[i],len,list2);
  }
  printf ("---total:  %d\n", total);
  for (int i = 0; i < len; i++) {
     total += list2[i] * countAppearences(list2[i],len,list1);
  }
  return total;
}

int main(){
  int len = 1000;
  int list1[len];
  int list2[len];
  read_ints("puzzle-list1.txt",len,list1);
  read_ints("puzzle-list2.txt",len,list2);
  insertionSort(len, list1);
  insertionSort(len, list2);
  int total = calcTotalDelta(len,list1,list2);
  printf ("Total delta = %d \n", total);
  int count = calcSimilarity(len,list1,list2);
  printf ("Total sim= %d \n", count);

  return 0;
}

