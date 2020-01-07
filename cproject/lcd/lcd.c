#include "lcd.h"

int fd = -1;
static unsigned char (*pShowBuffer)[800][4];
void initLcd(){
	fd=open("/dev/fb0",O_RDWR);
	if(fd<0){
		perror("ope lcd error:");
		return;	
	}
	pShowBuffer=(unsigned char (*)[800][4])mmap(NULL,LCD_SHOW_BUFFER,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(pShowBuffer==MAP_FAILED){
		perror("Cannot map:");
		close(fd);
		return;
	}
	printf("Succeed in initing lcd!\n");
	memcpy(pShowBuffer,getBackgroundImg(),LCD_SHOW_BUFFER);
}

//改变LCD上的值只改变5位
void changeValueA(char* val){
	int index = 0;
	char ch = val[index];
	while(ch != '\0'){//&& index <= 5
		ch = val[index];
		const unsigned char *v = getNumImg(ch);
		if(v == NULL){
			// printf("error for change value:%s\n",val);
			return;
		}else{
			int q=0;
			for(int i=50;i<100;i++){
				for(int j=350+25*index;j<375+25*index;j++){
					// pShowBuffer[i][j][0]=0xFF;
					// pShowBuffer[i][j][1]=0xFF;
					// pShowBuffer[i][j][2]=0xFF;
					// pShowBuffer[i][j][3]=0x00;
					pShowBuffer[i][j][0]=v[q++];
					pShowBuffer[i][j][1]=v[q++];
					pShowBuffer[i][j][2]=v[q++];
					pShowBuffer[i][j][3]=0x00;
				}
			}
		}
		index++;
	}
}


void changeValueB(char* val){
	int index = 0;
	char ch = val[index];
	while(ch != '\0'){//&& index <= 5
		ch = val[index];
		const unsigned char *v = getNumImg(ch);
		if(v == NULL){
			printf("error for change value:%s\n",val);
			return;
		}else{
			int q=0;
			for(int i=200;i<250;i++){
				for(int j=350+25*index;j<375+25*index;j++){
					// pShowBuffer[i][j][0]=0xFF;
					// pShowBuffer[i][j][1]=0xFF;
					// pShowBuffer[i][j][2]=0xFF;
					// pShowBuffer[i][j][3]=0x00;
					pShowBuffer[i][j][0]=v[q++];
					pShowBuffer[i][j][1]=v[q++];
					pShowBuffer[i][j][2]=v[q++];
					pShowBuffer[i][j][3]=0x00;
				}
			}
		}
		index++;
	}
}

// void main(){
//     initLcd();
// 	changeValueA("012.");
// }