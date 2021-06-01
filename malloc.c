#include<stdio.h>
#include<stdlib.h>


int main(void){
  int *p1,*p2;
  int i,j;

  p1 = (int *)malloc(sizeof(int));

  for(i =0;scanf("%d",p1+i)!=EOF;i++){
      p2 = (int *)malloc(sizeof(int)*1+i);
      for(j = 0;j<i+1;j++){
          p2[j]=p1[j];
      }
      free(p1);
      p1 = (int *)malloc(sizeof(int)*2+i);
      for(j =0;j<i+1;j++){
          p1[j] = p2[j];
      }
      free(p2);
  }
  putchar('\n');

  for(j =0;j<i;j++){
      printf("%3d",p1[j]);
  }
  putchar('\n');

  return 0;
}