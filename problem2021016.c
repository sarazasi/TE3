#include<stdio.h>
#include<stdlib.h>

typedef struct MEMBERCARD{
  int no;
  char name[32];
  double point;
} mc;

int main(void){
  mc *p1,*p2;
  int i,j;

  p1 = (mc *)malloc(sizeof(mc));

  printf("ナンバー:");
  for(i =0;scanf("%d",&p1[i].no) != EOF;i++){
    printf("名前:"); scanf("%s",p1[i].name);
    printf("ポイント"); scanf("%lf",&p1[i].point);

    p2 = p1;

    p1 = (mc *)malloc(sizeof(mc) * (i+2));
    for(j =0;j<i+1;j++){
      p1[j] = p2[j];
    }
    free(p2);
    printf("ナンバー");
  }
  putchar('\n');
  printf("\n-------結果---------\n\n");

  for(j =0;j<i;j++){
    printf("%d人目\n",j+1);
    printf("ナンバー：%d\n",p1[j].no);
    printf("名前：%s\n",p1[j].name);
    printf("ポイント：%f\n",p1[j].point);
    putchar('\n');

  }
  putchar('\n');

  return 0;

}
