#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888
int main()
{
   int sfd,len;
   struct sockaddr_in  serv_addr;
   
   char buf[BUFSIZ];

   serv_addr.sin_family = AF_INET;
   inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);   
// serv_addr.sin_addr.s_addr=htonl(SERV_IP);
   serv_addr.sin_port=htons(SERV_PORT);

   sfd=socket(AF_INET,SOCK_STREAM,0);
       
   connect(sfd,( struct sockaddr *)&serv_addr,sizeof(serv_addr));

       while (1) {
        /*从标准输入获取数据*/
        fgets(buf, sizeof(buf), stdin);
        /*将数据写给服务器*/
        write(sfd, buf, strlen(buf));       //写个服务器
        /*从服务器读回转换后数据*/
        len = read(sfd, buf, sizeof(buf));
        /*写至标准输出*/
        write(STDOUT_FILENO, buf, len);
     }
    /*关闭链接*/
    close(sfd);
   
   
  return 0;


}
