/*挿入ソート　自己参照構造体　双方向自己参照構造体*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10 //ソートする数
#define RANDOM 100 //乱数の値の範囲

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

//挿入ソート
//inmod...場所を決定するポインタ
Myst *in_sort(Myst *inmod){
  Myst *temp = NULL;
  Myst *flag = NULL; //比較する場所
  flag = inmod->next;
  while(1){
    temp = inmod->back;
    if(flag->number <= inmod->number){
      if(temp != NULL){
        //inmodの後の処理
        inmod->back->next = inmod->next;
        //inmodの前の処理
        inmod->next->back = inmod->back;
        //flagの後の処理
        flag->back->next = inmod;
        inmod->back = flag->back;
        //flagの処理
        flag->back = inmod;
        inmod->next = flag;
      }else{
        if(flag->back == inmod){
          return temp;
        }
        //inmodの前
        inmod->next->back = NULL;
        //inmod
        inmod->next = flag;
        inmod->back = flag->back;

        //flagの後
        flag->back->next = inmod;

        //flag
        flag->back = inmod;
      }
      return temp;
    }
    if( flag->next == NULL){ //先頭まで来た時の処理
      
      //inmodの前の処理
      inmod->next->back = inmod->back; //nextのbackをinmodのbackに連結
      //if(inmod->next->next == NULL) inmod->next->next = inmod; //nextのnextをinmodに連結
      flag->next = inmod;
      
      //inmodの後の処理
      if(inmod->back != NULL){
        inmod->back->next = inmod->next; //backをnextに連結
      }
      //inmodの処理
      inmod->next = NULL;
      inmod->back = flag;

      return temp;
    }
    flag = flag->next;
  }
}

//先頭要素を返す
Myst *heading(Myst *head){
  while(head->next != NULL){
    head = head->next;
  }
  return head;
}

//nextを使った全要素出力
void show_data(Myst *check){
  Myst *f;
  int i=1;
  while(check != NULL){
    printf("number%4d = %d\n",i,check->number);
    check = check->next;
    i++;
  }
}

//backを使った全要素出力
void show_data_hip(Myst *check){
  int i=1;
  while(check != NULL){
    printf("number%4d = %d\n",i,check->number);
    fflush(stdout);
    check = check->back;
    i++;
  }
}

int main(void){
  Myst *p;
  Myst *head,*afhead;
  p = NULL;
  head = NULL;
  int i = N,j;
  
  srand(time(NULL)); //乱数の種

  //------五個の乱数の自己参照構造体(0 ~ N-1)----------
  do{
    head = (Myst *)malloc(sizeof(Myst));
    p = add_data(head,p,rand()%RANDOM); //0 ~ RANDOM
    i--;
  }while(i!=0);
  //backをつなげていく
  //pはNULLの直前
  head->back = NULL;
  p = add_back(head);
  //--------------------------------------------------

  show_data(head); //nextを使って全部出力
  putchar('\n');

  putchar('\n');
  //挿入ソート
  p = p->back;
  while(p!=NULL){
    p = in_sort(p);
  }

  putchar('\n');

  //全要素を出力
  afhead = heading(head); //aheadを先頭に持っていく
  show_data_hip(afhead); //backを使って全部出力
  //空ける
  free(afhead);
  free(head);
  free(p);
  
  return 0;
}
