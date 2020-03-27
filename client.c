#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 1024

void main(int argc, char **argv)
{
    int client_socket;

    int fd;
    char buf[BUFSIZE];
    char filename[BUFSIZE];

    int len;

    struct sockaddr_in server_addr;

    if (argv[1] == NULL)
    {
        printf("메세지 입력 필요\n");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));         // 0으로 초기화
    server_addr.sin_family = AF_INET;                     // AF_INET은 주소 체계에서 IPv4를 의미
    server_addr.sin_port = htons(4000);                   // htons 함수를 통해서 Little Endian일 경우 Big Endian으로 변경하여 포트 번호 대입
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 32bit IPv4 주소로 초기화

    client_socket = socket(PF_INET, SOCK_STREAM, 0); // PF_INET은 프로토콜 체계에서 IPv4, SOCK_STREAM은 TCP를 의미

    if (-1 == client_socket)
    {
        printf("socket 생성 실패\n");
        exit(1);
    }

    if (-1 == connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    { // 연결 요청
        printf("접속 실패\n");
        exit(1);
    }

    strcpy(filename, argv[1]);                          // 입력받은 값을 filename에 저장
    write(client_socket, argv[1], strlen(argv[1]) + 1); // 파일이름을 NULL까지 포함해서 전송하기 위해 +1

    fd = open(filename, O_RDONLY); // 해당 파일을 읽음

    if (-1 == fd)
    {
        printf("File Open Error\n"); // 실패시 종료
        exit(1);
    }

    while ((len = read(fd, buf, BUFSIZE)) != 0)
    {                                   // 파일의 끝까지 버퍼사이즈 단위로 읽음
        write(client_socket, buf, len); // 버퍼사이즈 단위로 서버에 전송
    }

    close(fd);            // 파일 닫기
    close(client_socket); // 소켓 닫기
}
