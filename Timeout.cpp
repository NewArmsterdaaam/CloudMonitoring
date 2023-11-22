#include "Timeout.h"

using std::cout;
using std::endl;

Timeout::Timeout(){
	sec = 5;
	// cout<<sec<<"초 타이머가 작동합니다"<<endl;
	}
Timeout::Timeout(int s){
	sec = s;
	// cout<<sec<<"초 타이머가 작동합니다"<<endl;
	}
void Timeout::StartTimeout(){
	// time_t 구조체겠지, 이 자료를 메모리에 적재하고, 구조체 포인터에 접근하여 타이머 시작
	time_t begin;
	time(&begin);

	sleep(sec);

	time_t end;
	time(&end);

	// cout<<"타임 아웃 시간은 다음과 같습니다:"<<difftime(end, begin)<<endl;
	}
