/*-------------------------------------------------------------------------
 *  DgEcho.c - Reads a string from Client and writes it back to Client
 *  Version:	$Name:  $
 *  Module:	
 *
 *  Purpose:	
 *  See:	
 *
 *  Author:	Hema Murthy (hema@bhairavi.iitm.ernet.in)
 *
 *  Created:        Sat 17-Mar-2007 10:58:43
 *  Last modified:  Sat 17-Mar-2007 14:12:40 by hema
 *  $Id: DgEcho.c,v 1.1 2007/03/26 04:26:09 hema Exp hema $
 *
 *  Bugs: 
 *
 *  Change Log: <Date> <Author>
 *      <Changes>
 -------------------------------------------------------------------------*/
 
#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include "string.h"
#include "stdlib.h"
#include "crc.c"


#define  MAXMESG 8

#define P 0.01

int flagOpen = 0;
static int count = 0;

/*-------------------------------------------------------------------------
 *  DgEcho -- Reads a packet from client and sends it back to client
 *    Args: 
 *    Returns:  Nothing
 *    Throws: 
 *    See:  UNIX Network Programming - Richard Stevens: Vol I
 *    Bugs: 
 -------------------------------------------------------------------------*/
char* genbitstr(int c){
  char *str = malloc(9);
  int i;
  for(i = 0;i<8;i++){
    str[7-i] = (c%2)?'1':'0';
    c /= 2;
  }
  str[8] = '\0';
  return str;
}

int p(){
  if (((double)rand() / (double)RAND_MAX) < P)
    return 1;
  return 0;
}

void prob(char *t){
  int i;
  for(i=0; i < strlen(t); i++)
    if(p()){
      if(t[i] == '0')
        t[i] = '1';
      else
        t[i] = '0';
    }
}

int workwith(int c){
  printf("%d\n",++count);
  // static FILE *fp;
  static FILE *fp2;
  
  if(!flagOpen){
    flagOpen = 1;
    // fp = fopen("../output/transmitted","a");
    fp2 = fopen("../output/recvd","w");
  }
  
  int flag = 0;

  char *temp = genbitstr(c);
  prob(temp);
  char *temp2 = computeCRC(temp, "1011");
  if(strcmp(temp2,"000")){
    printf("%s\n", temp2);
    printf("%s\n", "Error");
    flag = 1;
  }

  if(flag == 1){
    count--;
    return 0;
  }

  // fprintf(fp, "%c%c%c%c%c",temp[0],temp[1],temp[2],temp[3],temp[4]);
  fprintf(fp2, "%d\n",c);

  if(count%100){
    fflush(fp2);
    // fflush(fp);
  }

  return 1;
}

void DgEcho(int sockFd, struct sockaddr *pcliAddr, socklen_t  maxCliLen)
{
    int       n;
    socklen_t cliLen;
    char mesg[MAXMESG];
    printf("entered dgecho\n");
    for( ; ;)
    {
      cliLen = maxCliLen;
      n = recvfrom(sockFd, mesg, MAXMESG, 0, pcliAddr, &cliLen);

  		if (n < 0) {
		   printf("dg_echo : recvfrom error");
		   exit(-1);
  		}	

      int res;
      if(mesg[0] == '1')
        if(mesg[1] >= 0)
          res = workwith(mesg[1]);
        else
          res = workwith(mesg[1]+256);
      else
        res = workwith(0);

      if (res == 0){
        char t[2];
        t[0] = '0';
        t[1] = '\0';
        if (sendto (sockFd, t, strlen(t), 0, pcliAddr, cliLen) != strlen(t)) {
           printf("dg_echo : sendto  error\n");
           exit(-1);
        }
      }
      else{
      	char t[2];
        t[0] = '1';
        t[1] = '\0';
        if (sendto (sockFd, t, strlen(t), 0, pcliAddr, cliLen) != strlen(t)) {
		   printf("dg_echo : sendto  error\n");
           exit(-1);
		}
      }
    }
}	/*  End of DgEcho		End of DgEcho   */

/*-------------------------------------------------------------------------
 * $Log: DgEcho.c,v $
 * Revision 1.1  2007/03/26 04:26:09  hema
 * Initial revision
 *
 *
 * Local Variables:
 * time-stamp-active: t
 * time-stamp-line-limit: 20
 * time-stamp-start: "Last modified:[ 	]+"
 * time-stamp-format: "%3a %02d-%3b-%:y %02H:%02M:%02S by %u"
 * time-stamp-end: "$"
 * End:
 *                        End of DgEcho.c
 -------------------------------------------------------------------------*/