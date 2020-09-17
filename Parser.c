#include <stdio.h>
#include <string.h>

enum commands {SECRET = 2, LOCK = 1, UNLOCK = 0};
enum commands currentCmd;

char unlock[] = "UNLOCK";
char lock[] = "LOCK";
char secret[] = "SECRET";
char pass[] = "1234";

char buff[256];
char cmd[10];
char pos = 0;
char isLocked = 1;

static void feed(int c){
  
  buff[pos] = (char)c;

  if(buff[pos] != '\n'){
    pos++;
    return;
  }
  else{     

    if(pos > 6){
      memset(&cmd[0], 0, sizeof(cmd));
      memcpy(&cmd[0], &buff[0], 6); 
    }
    else{
      memset(&cmd[0], 0, sizeof(cmd));
      memcpy(&cmd[0], &buff[0], pos); 
    }

    if (strcmp(cmd, unlock) == 0)
      currentCmd = UNLOCK;
    else if (strcmp(cmd, lock) == 0)
      currentCmd = LOCK;
    else if (strcmp(cmd, secret) == 0)
      currentCmd = SECRET;
    else {
      pos = 0;
      memset(&buff[0], 0, sizeof(buff));
      memset(&cmd[0], 0, sizeof(cmd));
      printf("FAIL\n");
      return;
    }

    switch (currentCmd){
      case UNLOCK:{

        memcpy(&cmd[0], &buff[0], pos); 

        int passPosition = -1;

        for(int i = 0; i < pos; i ++){
          if(cmd[i] == ' ') {
            passPosition = i + 1; 
            break;           
          }
        }        
        char incomePass[4];

        if(passPosition != -1){       
          memcpy(&incomePass[0], &cmd[passPosition], 5);        

          if(strcmp(incomePass, pass) == 0){
            isLocked = 0;
            printf("OK\n");
          }
          else
          printf("FAIL\n");
        }        
        else 
          printf("FAIL\n");
          
        break;    
      }  

      case LOCK:{
        isLocked = 1;
        printf("OK\n");
        break;
      }
      
      case SECRET:{
        if(isLocked == 1)
          printf("FAIL\n");
        else 
          printf("OK My super secret!\n");
          break;
      }

      default:
        return;
    }
    
    memset(&buff[0], 0, sizeof(buff));
    memset(&cmd[0], 0, sizeof(cmd));
    pos = 0;
  }
}

int main(void) {
  do{
    int c = getc(stdin);
    
    if (c == EOF)
      break;

    feed(c);  
  } while (1);  
  return 0;
}
