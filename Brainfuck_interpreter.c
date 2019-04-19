#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef unsigned char Byte;

const int PROGRAM_MAX_LENGTH = 2000; // Максимальный размер программы
const int MEMORY_SIZE = 2000; // Объём памяти исполнителя
const int CYCLES_DEPTH = 30; // Максимальная глубина вложенности циклов

int main(int argc, char *argv[]){
  char program[PROGRAM_MAX_LENGTH]; // Программа
  Byte memory[MEMORY_SIZE]; // Память исполнителя
  int cp = 0; // Номер исполняемой инструкции
  int mp = 0; // Номер активной ячейки памяти
  int cycles[CYCLES_DEPTH]; // Для создания циклов
  int cyclesDepth = -1; // Глубина циклов
  int buffer;
  int i;
  for(i = 0; i < MEMORY_SIZE; i++) memory[i] = 0;
  for(i = 0; i < PROGRAM_MAX_LENGTH; i++) program[i] = 0;
  for(i = 0; i < CYCLES_DEPTH; i++) cycles[i] = 0;
//=====================================
  strcpy(program, // Запись программы
  // Эта программа была взята из одного интересного видео
"+++++[>+++++[>+++<-]<-]>>+++.<++++[>+++++<-]>+++.<+++[>+++++<-]>.>"
"++++[>++++++++<-]>.<<--------.-------.++.++++.++++.--------.++++++"
"++.>>.<<+++.-------------.++++++++++++++.-----------.---.+++++++++."
"-----.<++++[>++++<-]>.<++++[>------<-]>."
  );
//=====================================
  while(program[cp] != '\0'){
    switch(program[cp]){
      case '>':
        mp++;
        break;
      case '<':
        mp--;
        break;
      case '+':
        memory[mp]++;
        break;
      case '-':
        memory[mp]--;
        break;
      case '.':
        printf("%c", memory[mp]);
        break;
      case ',':
        memory[mp] = getch();
        break;
      case '[':
        if(memory[mp]){
          cyclesDepth++;
          cycles[cyclesDepth] = cp;
        }else{
          buffer = 0;
          for(; buffer != 0 && program[mp] != ']'; cp++)
            if(program[mp] == '[') buffer++;
            else if(program[mp] == ']') buffer--;
        }
        break;
      case ']':
        if(memory[mp])
          cp = cycles[cyclesDepth];
        else
          cyclesDepth--;
        break;
    }
    cp++;
  }
  getch();	
  return 0;
}
