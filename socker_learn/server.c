#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888

int main()

{
 
   int sfd,cfd,len,i;
   struct sockaddr_in  serv_addr,clie_addr;
  
   char buf[BUFSIZ]; 
  
   serv_addr.sin_family = AF_INET;
   inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);    
 // serv_addr.sin_addr.s_addr=htonl(SERV_IP);
   serv_addr.sin_port=htons(SERV_PORT);
    
   sfd=socket(AF_INET,SOCK_STREAM,0);
   bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

   listen(sfd,10);
   socklen_t clie_addr_len;
   clie_addr_len = sizeof(clie_addr_len);
   cfd = accept(sfd,(struct sockaddr *)&clie_addr,&clie_addr_len);

      while (1) {
        /*读取客户端发送数据*/
        len = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);

        /*处理客户端数据*/
        for (i = 0; i < len; i++)
            buf[i] = toupper(buf[i]);

        /*处理完数据回写给客户端*/
        write(cfd, buf, len); 
    }

    /*关闭链接*/
    close(sfd);
    close(cfd);

    return 0;

}
