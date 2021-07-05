#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 5 //sortする対象の数
#define RANDAM 10 //乱数の値の範囲

typedef struct myst{
  int number;
  struct myst *next;
}Myst;

Myst *add_data(Myst *box,Myst *nt,int n){
  static int count = 1;//この関数を通った回数
  //値の代入
  box->number = n;

  if(count==1){
    box->next = NULL;
  }else{
    box->next = nt;
  }

  count++;
  return box;
}


//inmod ... 判定する場所
//back ... inmodの一個前の要素
//返り値 ... NULL -> 先頭要素が変わらない head2 ... 先頭が変わった時の先頭
Myst *sort(Myst *inmod, Myst *back){
  Myst *flag = NULL; 
  Myst *flagback = NULL; //flagの後ろ要素
  
  flagback = inmod; 
  flag = inmod->next;
  while(1){
    puts("a");
    fflush(stdout);
    if(flag->number < inmod->number){
      if(inmod->next == flag) return NULL; //inmodとflagが隣り合っていたら何もせず処理を終了
      
      //inmodが先頭要素の時　-> 処理後, inmodのnextが先頭になる
      if(back == NULL){
        Myst *head2 = inmod->next;
        inmod->next = flag;
        flagback->next = inmod;
        return head2;
      }

      back->next = inmod->next;
      inmod->next = flag;
      flagback->next = inmod;
      return NULL;
    }
    //最後尾までflag<inmodが成立しなかった -> 最後尾にinmodを入れ込む
    if(flag -> next == NULL){
      //inmodが先頭要素の時　-> 処理後, inmodのnextが先頭になる
      if(back == NULL){ 
        Myst *head2 = inmod->next; 
        inmod -> next = NULL;
        flag ->next = inmod;
        return head2;
      }
      
      back->next = inmod->next;
      flag->next = inmod;
      inmod->next = NULL;
      return NULL;
    }
    //比較する場所をずらす
    flag = flag->next;
    flagback = flagback->next;
  }
}
void show_data(Myst *check){
  int i=1;
  while(check != NULL){
    printf("number%d = %3d\n",i,check->number);
    check = check->next;
    i++;
  }
}

int main(void){
  Myst *head,*h2;
  Myst *p;
  Myst *b; //判定する場所の一個前
  p = NULL;
  head = NULL;
  int i = N,j;

  srand(time(NULL)); //乱数の種
 
  //------自己参照構造体を作成----------
  do{
    head = (Myst *)malloc(sizeof(Myst));
    p = add_data(head,p,rand()%RANDAM); //0 ~ RANDAMの範囲の乱数を作成
    i--;
  }while(i!=0);
  //------------------------------
  show_data(head);
  putchar('\n');

  //sortする (N-1回)
  for(i = N-1;i >= 1;i--){
    puts("b");
    fflush(stdout);
    b = NULL; //bを初期化
    p = head; // pを先頭にする
    for(j = 1;j<i && i!=1;j++){ // pを判定したいやつにする. 最後の一回は通らない-> i!= 1
      puts("d");
      fflush(stdout);
      b = p;
      p = p->next;
    }
    if(b != NULL) printf("p : %d b :%d\n",p->number,b->number);
    fflush(stdout);
    if( (h2 = sort(p,b)) != NULL) head = h2; //NULL以外がかえってきたら先頭の場所を更新
    
    
    show_data(head);
  }

  //全要素を出力
  //show_data(head);

  //空ける
  free(head);
  free(p);
  free(b);
  free(h2);
  
  return 0;
}