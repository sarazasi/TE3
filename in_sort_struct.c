/*挿入ソート　自己参照構造体*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 5

typedef struct myst{
  int number;
  struct myst *next;
  struct myst *back;
}Myst;

//i... numberに代入する値
//box... head, 
//nt... 一個前の物, nextに入る
Myst *add_data(Myst *box,Myst *nt,int n){
  static int flag = 1; //この関数を通った回数
  //値の代入
  box->number = n;

  /*nextのポインタを代入　一回目だけNULLを代入*/
  if(flag==1){
    box->next = NULL;
  }else{
    box->next = nt;
  }
  
  flag++;
  return box;
}

//backを作る
//NULLの直前をリターン
Myst *add_back(Myst *header){
  Myst *bk;

  while(header->next != NULL){
    bk = header; //一個前のポインタを保持

    header = header->next;
    //backに代入
    header->back = bk;
  }
  return header;
}

//nextを使った全要素出力
void show_data(Myst *check){
  Myst *f;
  int i=1;
  while(check != NULL){
    printf("number%d = %3d\n",i,check->number);
    check = check->next;
    i++;
  }
}

//backを使った全要素出力
void show_data_hip(Myst *check){
  int i=1;
  while(check != NULL){
    printf("number%d = %3d\n",i,check->number);
    fflush(stdout);
    check = check->back;
    i++;
  }
}

int main(void){
  Myst *head;
  Myst *p;
  p = NULL;
  head = NULL;
  int i = N,j;
  
  srand(time(NULL)); //乱数の種

  //------五個の乱数の自己参照構造体(0 ~ N-1)----------
  do{
    head = (Myst *)malloc(sizeof(Myst));
    p = add_data(head,p,i);
    i--;
  }while(i!=1);
  //--------------------------------------------------

  //backをつなげていく
  head->back = NULL;
  //pはNULLの直前
  p = add_back(head);

  //全要素を出力
  show_data(head);
  putchar('\n');
  show_data_hip(p);

  //空ける
  free(head);
  free(p);
  
  return 0;
}