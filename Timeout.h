#ifndef TIMEOUT_H 
#define TIMEOUT_H

#include <iostream>
#include <time.h>
#include <unistd.h>

class Timeout{
	private:
		int sec;
	public:
		Timeout();
		Timeout(int s);
		void StartTimeout();
	};

#endif /*Timeout.h*/

/*
이 경로에 작성이 되어 있지만 실제 g++ 컴파일러가 동작하는 경로에 있지 않으므로
/usr/include 경로에 파일 복사하기
*/
/*
추가로 #include ""로 구현한 것은 
경로가 알아서 이 폴더로 작동되게 한다는 점 
*/

//그리고 전처리하는 ifndef의 의미는 if not define