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

int open(const char *path, int oflag, [mode_t mode]);

oflag 옵션으로는 기본 모드와 추가 옵션이 있는데 기본 모드로는 
O_RDONLY : 읽기 
O_WRONLY : 쓰기 
O_RDWR : 읽기/쓰기가 있다.

그리고 추가 옵션으로는 
O_APPEND : 파일 끝에 추가, 
O_CREAT : 파일 생성, 
O_TRUNC : 기존 내용 삭제, 
O_EXCL : 파일 존재 시 오류, 
O_NONBLOCK : 논블로킹, 
O_SYNC : 디스크에 실제 기록 후 반환으로 구성되어 있다.

파일 열기(fopen.c)

if ((fd = open(argv[1], O_RDWR)) == -1)
    printf("파일 열기 오류\n");
else
    printf("파일 %s 열기 성공 : %d\n", argv[1], fd);

파일 생성(creat())

int creat(const char *path, mode_t mode);

파일 닫기(close())

int close(int fd);

데이터 읽기(read())

ssize_t read(int fd, void *buf, size_t nbytes);

데이터 쓰기(write())

ssize_t write(int fd, void *buf, size_t nbytes);

임의 접근(lseek())

off_t lseek(int fd, off_t offset, int whence);

dbcreate.c(저장)는 
학번 기준 위치에 저장하는 역할을 하고 
lseek + write를 사용한다.

dbquery.c(조회)는 
학번 입력 후 해당 위치 이동시키는 역할을 한다. 
그리고 read 후 출력한다.
