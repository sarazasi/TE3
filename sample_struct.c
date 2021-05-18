#include<stdio.h>
#include<stdlib.h>

#define N 100

typedef struct myst{
  int number;
  struct myst *next;
}Myst;

Myst *add_data(Myst *box,Myst *nt,int n){
  //値の代入
  box->number = n;

  if(n==1){
    box->next = NULL;
  }else{
    box->next = nt;
  }
  return box;
}

//*backにdelの一個前を入れる、delにけしたい要素
void *delete_data(Myst *back,Myst *del){
  back->next = del->next;
}

void show_data(Myst *check){
  int i=1;
  while(check != NULL){
    printf("number%d = %3d\n",i,check->number);
    check = check->next;
    i++;
  }
}

//check_対象、f_対象を判定する数字
//判定,headの先頭をflagに入れる->入れた値で割っていき、割り切れるのはけしていく
void check_data(Myst *check,int fg){
  //前のcheckを保持
  Myst *back;
  back = check;
  check = check->next;

  while(check != NULL){
    if(( check->number % fg)==0){
      //printf("前back:%d,check:%d\n",back->number,check->number);
      
      //要素をけす
      //back->next = check->next;
      delete_data(back,check);
      //printf("あとback:%d,check:%d\n",back->number,check->number);
    }
      back = check;
      check = check->next;
  }
}

int main(void){
  Myst *head;
  Myst *p;
  p = NULL;
  head = NULL;
  int i = N,j;
 
  //------探索リストを作成----------
  do{
    head = (Myst *)malloc(sizeof(Myst));
    p = add_data(head,p,i);
    i--;
  }while(i!=1);
  //------------------------------

  //判定,headの先頭をflagに入れる->入れた値で割っていき、割り切れるのはけしていく
  //printf("head:%d\n",head->number); 2
  int flag;
  check_data(head,flag);
  p = head;
  
  while(head!=NULL){
    //先頭を入れる
    flag=head->number;

    //判定
    check_data(head,flag);

    //判定が終わったので次の値を先頭に
    head = head->next;
  }

  //全要素を出力
  show_data(p);

  //空ける
  free(head);
  free(p);
  
  return 0;
}