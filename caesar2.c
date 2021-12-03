#include<stdio.h>
#include<stdlib.h>

//座標を登録する構造体
typedef struct point{
  int x;
  int y;
  int error; //1の場合エラー
  int space;
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

  //全パターンを出力
  for(m=0;m<=6;m++){ //7回
    for(n=1;n<=8;n++){ //8回  
      for(k = 0;k<num;k++){
        if((n == 1)&&((p[k].x += 1) > 7)) p[k].x %= 7; 
        if((p[k].y += 1) > 8) p[k].y %= 8; 
        putchar(get_num(p[k]));
      }
      putchar('\n');
    }
  }

  return 0;
}

// c...座標を割り出す文字
Point char_num(int c){
  int num; //座標と対応した数字
  Point p; //返却値

  p.x = p.y = p.error = p.space = 0; //初期化

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
    case ' ':
      p.space = 1;
      break;
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

  if(p.space == 1) return ' '; //スペースがあったらスペースを返す

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