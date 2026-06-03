시스템 호출과 C 라이브러리에 대해 알아보자.

시스템 호출 (System Call)은 
커널에 서비스 요청을 한다. 
OS와 직접 상호작용을 한다는 특징이 있다. 

C 라이브러리 함수는 
시스템 호출을 감싼 함수 (wrapper)이다. 
개발자는 보통 이것만 사용한다고 한다. 

파일 종류로는 텍스트 파일과 이진 파일(Binary)이 있다.

텍스트 파일은 
사람이 읽을 수 있고 
줄 단위 처리가 가능하다.

이진 파일(Binary)은 
그대로 바이트 저장을 할 수 있고 
구조체 그대로 저장이 가능하다.

파일 입출력 기본 흐름으로는 
파일 열기(fopen()), 
입출력 함수 사용, 
파일 닫기(fclose())순서로 진행된다.

fopen() 정리

FILE *fp = fopen("파일명", "모드");

주요 모드로는 
r	읽기, 
r+	읽기/쓰기, 
w	쓰기 (기존 삭제), 
w+	새로 생성, 
a	추가, 
a+	추가 + 읽기가 있다.

표준 입출력으로는 
stdin	키보드, 
stdout	화면, 
stderr	오류 출력이 있다.

문자 단위 입출력은

int c = fgetc(fp);

fputc(c, fp);

EOF 만나면 종료한다.

줄 단위 입출력은

fgets(buffer, size, fp);

fputs(buffer, fp);

대소문자 변환 프로그램 코드

#include <stdio.h>
#include <ctype.h>
int main() {
    char ch;
    while (1) {
        printf("문자 입력 : ");
        scanf(" %c", &ch);

        if (ch == '0') break;

        if (isupper(ch)) {
            printf("%c의 소문자는 %c이다.\n", ch, tolower(ch));
        } else if (islower(ch)) {
            printf("%c의 대문자는 %c이다.\n", ch, toupper(ch));
        } else {
            printf("영문자가 아니다.\n");
        }
    }
    return 0;
}
