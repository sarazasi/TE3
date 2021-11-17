#include<stdio.h>
#include<stdlib.h>

//座標を登録する構造体
typedef struct point{
  int x;
  int y;
  int error; //1の場合エラー
}Point;

Point char_num(int); //文字から座標を割り出す
int get_num(Point); //座標から文字を得る

int main(void){
  int  c; //入力文字
  Point p[100]; //cの座標を格納
  int num; //文字数
  int n,m; //シフト数
  int k;

  //文字列の入力
  num = 0;
  while((c = getchar()) != '\n'){
    p[num] = char_num(c);
    if(p[num].error == 1){//入力の失敗
      exit(EXIT_FAILURE);
    }
    num++;
  }

  //シフト数の入力 { 0<n<8 , 0<m<7 }
  do{
    printf("n,m = ");
    scanf("%d,%d",&n,&m);
  }while(!((n > 0 && n < 8)&&(m > 0 && m < 7)));

  //シフト
  for(k = 0;k<num;k++){
    if((p[k].x += m) > 7) p[k].x %= 7;
    if((p[k].y += n) > 8) p[k].y %= 8;
  }

  //出力
  for(k = 0;k<num;k++){
    putchar(get_num(p[k]));
  }

  return 0;
}

// c...座標を割り出す文字
Point char_num(int c){
  int num; //座標と対応した数字
  Point p; //返却値

  p.x = p.y = p.error = 0; //初期化

  if(c >= 'a' && c <= 'z'){ //cが小文字なら
    num = c - 'a' + 1;
    p.y = (num%4 == 0) ? 4 : num%4; //y座標
    p.x = (num - p.y)/4 + 1; //x座標
  }else if(c >= 'A' && c <= 'Z'){ //cが大文字なら
    num = c - 'A' + 29;
    p.y = ((num%4 == 0) ? 4 : num%4) + 4; //y座標
    p.x = (num-p.y)/4 - 5; //x座標
  }else{
    switch (c) //例外
    {
    case ',':
      p.x = 7;
      p.y = 3;
      break;
    case '.':
      p.x = 7;
      p.y = 4;
      break;
    case '!':
      p.x = 7;
      p.y = 7;
      break;
    case '?':
      p.x = 7;
      p.y = 8;
      break;
    default:
      puts("英文字ではない入力");
      p.error = 1;
      break;
    }
  }

  return p;
}

int get_num(Point p){
  int c; //返却値
  if(p.y < 5){ //小文字
    if(p.x == 7){ //例外 , . ! ?
      switch (p.y){
      case 3:
        c = ',';
        break;
      case 4:
        c = '.';
        break;
      default:
        c = 'a' + p.y + 4*p.x - 5;
        break;
      }
    }else{
        c = 'a' + p.y + 4*p.x - 5;
    }

  }else{ //大文字
    if(p.x == 7){ //例外 , . ! ?
      switch (p.y){
      case 7:
        c = '!';
        break;
      case 8:
        c = '?';
        break;
      default:
        c = 'A' + p.y + 4*p.x - 9;
        break;
      }
    }else{
      c = 'A' + p.y + 4*p.x - 9;
    }
  }

  return c;
}