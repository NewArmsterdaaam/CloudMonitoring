// 여기서 서버 프로세스 생성

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h> // read() 함수를 위해 
#include "Timeout.h"
#include <time.h>

using std::cout;
using std::cin;
using std::endl;

#define PORT 9999

int main(){
    int server_fd, new_socket, valread;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "서버에서 전송합니다";
    const char* monitor = "자원을 모니터링합니다";

    // application와 바로 맞닿아 있는 커널 소켓 디스크립터
    // 해당 소켓을 생성하여 각 버퍼를 생성하고,
    // 소켓은 하나의 파일이므로 그 반환 값을 파일 디스크립터 배열에 반환
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "Setsockopt error" << std::endl;
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //socket을 실행 할 프로세스의 포트 9999에 바인딩하기. 
    //socket과 파일 디스크립터 연결인지 확인
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }
    
    if (listen(server_fd, 3)<0){
        std::cerr << "Listen error" << std::endl;
        return -1;
    }
    
    // accept는 clinet에서 연결 요청이 들어오면 큐잉에 맞춰 연결을 허락하는 시스템 함수. 이제부터 연결이 되었으니, 애플리케이션 간 정책으로 통신 가능.
    // 여기서 소켓을 만드는 것 같긴 한데 accept 함수
    if ((new_socket=accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        /* code */
        std::cerr<<"Listen error"<<std::endl;
        return -1;
    }
    
    /*
    valread = read(new_socket, buffer, 1024);
    std::cout<<buffer<<std::endl;

    send(new_socket, hello, strlen(hello), 0);
    std::cout<<"hello message sent"<<std::endl;
    */

    cout << "몇 번 문제:";
    int number = 0;
    cin >> number;
    

    if (number == 1)
    {
        cout << "heart beat check" << endl;

        int i = 0;
        while (i<5)
        {
            send(new_socket, hello, strlen(hello), 0);
            
            int setting_timer = 3;
            Timeout timer(setting_timer);
            timer.StartTimeout();

            std::cout << setting_timer << "초가 지나도 연락이 없습니다" << std::endl;
            i++;
        }
        cout << "문제 발생" << endl;
    }
    
    else {
        cout << "monitoring check" << endl;

        send(new_socket, monitor, strlen(monitor), 0);

        FILE* fp;
        fp = fopen("/share/comnetwork/c++/monitor_log", "wb");  // 이 함수를 호출함으로써 반환되는 값은 생성된 파일 스크립터의 인덱스 값?
        int nbyte = 1024;
        while (nbyte >= 1024)
        {
            nbyte = recv(new_socket, buffer, 1024, 0);  // recv()가 반환하는 int 값이 의미하는 값.
            fwrite(buffer, sizeof(char), nbyte, fp);
        }
        fclose(fp);
        cout << "파일 다운로드 완료" << endl;
    }

    return 0;
}