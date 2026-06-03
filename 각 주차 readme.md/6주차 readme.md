유닉스 커널(kernel)은 
파일 관리 (File management) 
프로세스 관리 (Process management) 
메모리 관리 (Memory management) 
통신 관리 (Communication management) 
주변장치 관리 (Device management)와 같은 서비스를 제공한다.

시스템 호출(System Call)은 커널에 서비스 요청을 위한 프로그래밍 인터페이스이다. 
응용 프로그램은 직접 하드웨어를 접근하지 않고 시스템 호출을 통해 커널에 요청한다.

시스템 호출 과정의 동작 흐름으로는 
사용자 프로그램에서 함수 호출 (예: open()) -> 
라이브러리 함수가 trap 명령어 실행 -> 
CPU가 커널 모드로 전환 -> 
커널 내부 해당 시스템 호출 실행 -> 
결과 반환 → 사용자 모드 복귀

파일 열기(open())
