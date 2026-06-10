# **1.pwd**: 현재 경로를 추력하는 명령어
```c
#include <stdio.h>
#include <unistd.h>   // getcwd 함수
#include <limits.h>   // PATH_MAX 상수

int main() {
    char cwd[PATH_MAX];  // 현재 작업 디렉토리를 저장할 버퍼

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);  // 현재 디렉토리 경로를 출력
    } else {
        perror("getcwd 오류");  // 오류 메시지를 출력
        return 1;
    }
    return 0;
}
```
## 설명
- ``getcwd(char *buf, size_t size)`` 함수를 통해서 현재 위치를 저장할 수 있다.
- **PATH_MAX**는 ``limits.h``에 정의된 상수이다. (크기: 4096)

## 컴파일 및 실행화면
![Image](https://github.com/user-attachments/assets/fa61f2c7-2b38-476d-b91d-fc9fd3e5c13a)

# **2.ls**: 현재 디렉토리의 파일/디렉토리 이름 출력
```c
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");  // 현재 디렉토리 열기
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리에서 항목 하나씩 출력
        if (entry->d_name[0] != '.') {
           printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
    return 0;
}
```
## 설명
- **opendir()**: ``dirent.h`` 라이브러리를 통해서 DIR 타입의 포인터 변수를 만들고 ``opendir(".")`` 을 통해서 현재 디렉토리의 정보를 dir 변수에 넣는다.
- **if(entry->d_name[0] != '.')**: 숨김 파일은 출력하지 못하게 하기 위해 구현한다.
- **entry = readdir(dir) != NULL**: 현재 디렉토리의 항목을 하나씩 읽고 **NULL**이 아니면 출력, **NULL**이면 while문을 나가고 ``closedir()``을 통해서 디렉토리를 닫는다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/2c473170-4cfe-4976-be23-fab44ac7efc9)

# **3.ls -a**: 현재 디렉토리의 파일/디렉토리, 숨김처리 파일/디렉토리 이름 출력
```c
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");  // 현재 디렉토리 열기
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리에서 항목 하나씩 출력
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
```
## 설명
- **opendir()**: ``dirent.h`` 라이브러리를 통해서 DIR 타입의 포인터 변수를 만들고 ``opendir(".")`` 을 통해서 현재 디렉토리의 정보를 dir 변수에 넣는다.
- **entry = readdir(dir) != NULL**: 현재 디렉토리의 항목을 하나씩 읽고 **NULL**이 아니면 출력, **NULL**이면 while문을 나가고 ``closedir()``을 통해서 디렉토리를 닫는다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/5f2176f8-07ae-4799-bf14-aa121b18ca59)

# **4.ls -l**: 현재 디렉토리의 파일/디렉토리 상세 정보 출력

```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_mode(mode_t mode) {
    printf(S_ISDIR(mode) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat st;

    dir = opendir(".");
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // 숨김 파일 제외
        if (entry->d_name[0] == '.')
            continue;

        if (stat(entry->d_name, &st) == -1) {
            perror("stat 실패");
            continue;
        }

        print_mode(st.st_mode);
        printf(" %ld", st.st_nlink);

        struct passwd *pw = getpwuid(st.st_uid);
        struct group *gr = getgrgid(st.st_gid);
        printf(" %s", pw ? pw->pw_name : "unknown");
        printf(" %s", gr ? gr->gr_name : "unknown");

        printf(" %5ld", st.st_size);

        char timebuf[64];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st.st_mtime));
        printf(" %s", timebuf);
        printf(" %s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
```
## 설명
- ``dirent.h`` 라이브러리로 현재 디렉토리 열기, **dirent** 구조체 선언, **readdir()** 함수를 통해서 파일/디렉토리 항목 하나씩 읽기 등을 구현했다.
- ``sys/stat.h`` 라이브러리에 정의된 파일 권한 관련 상수들로 파일의 권한을 구분 및 stat 구조체를 사용했다.
- ``stat``, ``dirent`` **구조체**들로 필요한 정보들 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/2d941b6c-5a1a-420d-8a58-19c0504a13de)

# **5.ls -al**: 현재 디렉토리의 파일/디렉토리 및 숨김처리 파일/디렉토리 상세 정보 출력

```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_mode(mode_t mode) {
    printf(S_ISDIR(mode) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat st;

    dir = opendir(".");
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &st) == -1) {
            perror("stat 실패");
            continue;
        }

        print_mode(st.st_mode);
        printf(" %ld", st.st_nlink);

        struct passwd *pw = getpwuid(st.st_uid);
        struct group *gr = getgrgid(st.st_gid);
        printf(" %s", pw ? pw->pw_name : "unknown");
        printf(" %s", gr ? gr->gr_name : "unknown");

        printf(" %5ld", st.st_size);

        char timebuf[64];
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st.st_mtime));
        printf(" %s", timebuf);
        printf(" %s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
```
## 설명
- ``dirent.h`` 라이브러리로 현재 디렉토리 열기, **dirent** 구조체 선언, **readdir()** 함수를 통해서 파일/디렉토리 항목 하나씩 읽기 등을 구현한다.
- ``sys/stat.h`` 라이브러리에 정의된 파일 권한 관련 상수들로 파일의 권한을 구분 및 stat 구조체를 사용한다.
- ``stat``, ``dirent`` **구조체**들로 필요한 정보들을 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/081cd7ec-6993-4ed8-b839-2993d7dc9156)

# **6.id**: 사용자 정보 출력
```c
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main() {
    uid_t uid = getuid();                 // 사용자 UID
    gid_t gid = getgid();                 // 그룹 GID

    struct passwd *pw = getpwuid(uid);    // 사용자 정보
    struct group *gr = getgrgid(gid);     // 그룹 정보

    if (pw == NULL || gr == NULL) {
        perror("사용자 또는 그룹 정보를 가져올 수 없습니다");
        return 1;
    }
    printf("uid=%d(%s) gid=%d(%s)\n", uid, pw->pw_name, gid, gr->gr_name);
    return 0;
}
```
## 설명
- **getuid()**: **사용자 UID(User ID)** 를 반환한다.
- **getgid()**: **그룹 ID** 를 반환한다.
- **getpwuid()**: ``UID``를 통해서 **구조체** 를 반환한다.
- **getgrgid()**: ``GID``를 통해서 **구조체** 를 반환한다.
- **구조체**: ``UID``, ``GID`` 구조체를 통해서 각 name을 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/c4943a63-cec3-4a79-83b6-2cec0b2d7aac)

# **7.id -u**: 현재 사용자의 **UID(User ID)** 만 출력하는 명령어
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    uid_t uid = getuid();   // 현재 사용자 UID 가져오기
    printf("%d\n", uid);    // UID 출력
    return 0;
}
```
## 설명
- ``unistd.h``에 정의된 ``getuid()`` 함수를 사용하여 현재 사용자 UID(User ID)를 가져온다.
- ``printf()``로 UID를 출력한다.
- ``id -u`` 명령어와 같은 방식으로 현재 사용자의 UID만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/a9d83a92-881e-4175-b415-e9a3082e6a86)

# **8.id -g**: 현재 사용자의 **GID(기본 그룹 ID)** 만 출력하는 명령어
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    gid_t gid = getgid();   // 현재 사용자 GID 가져오기
    printf("%d\n", gid);    // GID 출력
    return 0;
}
```
## 설명
- ``unistd.h``에 정의된 ``getgid()`` 함수를 사용하여 현재 사용자의 GID(Group ID)를 가져온다.
- ``printf()``로 GID를 출력한다.
- ``id -g`` 명령어와 같은 방식으로 현재 사용자의 기본 그룹 ID만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/60805165-0b0f-4e58-904a-460a34704931)

# **9.hostname**: 호스트 이름 출력
```c
#include <stdio.h>
#include <unistd.h>     // gethostname
#include <limits.h>     // HOST_NAME_MAX

int main() {
    char hostname[HOST_NAME_MAX + 1];  // 널 문자 포함 공간 확보

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("%s\n", hostname);
    } else {
        perror("gethostname 오류");
        return 1;
    }
    return 0;
}
```
## 설명
- **HOST_NAME_MAX**: ``limits.h`` 헤더에 정의된 상수이며 1을 더하는 이유는 문자열의 끝에 있는 ``널 문자(\\0)`` 때문이다. **※크기는 리눅스에서 64이다.**
- **gethostname(char *name, size_t len)**: hostname을 반환하는 함수이다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/cf991eaa-861a-49dd-a505-9b53ba464ee3)

**※ hostname이 ip주소가 뜨는이유는 AWS를 사용하면 hostname이 기본적으로 ip주소로 만들어지기 때문이다.**

# **10.hostname -I**: 명령어 관련 파일(실행파일, man 파일 등) 위치 모두 확인

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    struct ifaddrs *ifaddr, *ifa;
    char ip[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs 오류");
        return 1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        if (ifa->ifa_addr->sa_family == AF_INET) { // IPv4
            void *addr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, addr, ip, sizeof(ip));

            // 루프백(127.0.0.1)은 제외
            if (strncmp(ip, "127.", 4) != 0) {
                printf("%s ", ip);
            }
        }
    }
    printf("\n");
    freeifaddrs(ifaddr);
    return 0;
}
```
## 설명
- `getifaddrs()` 함수로 현재 네트워크 인터페이스들의 리스트를 얻는다.
- 각 인터페이스에 대해 IPv4 주소(AF_INET)인 경우 `inet_ntop()`으로 문자열 IP 주소로 변환한다.
- 루프백 주소(127.0.0.1)는 제외하고 출력한다.
- 여러 개의 IP가 있을 수 있으므로 공백으로 구분해 모두 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/48f2136b-0305-4924-9568-5b4d10297ac3)

# **11.uname**: 커널 이름 출력
```c
#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname buffer;

    if (uname(&buffer) == 0) {
        printf("%s\n", buffer.sysname);  // 커널 이름만 출력 (예: Linux)
    } else {
        perror("uname 오류");
        return 1;
    }
    return 0;
}
```
## 설명
- ``sys/utsname.h``에 정의된 **uname()** 함수로 커널 이름을 들고 온다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/8ac5f987-7d49-4a68-ba1c-f333b1f1f282)

# **12.uname -a**: 운영체제에 대한 전체 시스템 정보를 출력하는 명령어

```c
#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname buffer;

    if (uname(&buffer) == -1) {
        perror("uname 실패");
        return 1;
    }

    printf("%s %s %s %s %s\n",
           buffer.sysname,   // 운영 체제 이름
           buffer.nodename,  // 호스트 이름
           buffer.release,   // 커널 릴리즈
           buffer.version,   // 커널 버전
           buffer.machine    // 하드웨어 정보
    );
    return 0;
}
```
## 설명
- ``sys/utsname.h``의 ``uname()`` 함수는 시스템 정보를 담은 ``utsname`` 구조체를 반환한다.
- 구조체의 각 필드를 활용하여 운영 체제, 노드 이름, 커널 버전, 하드웨어 정보 등을 출력한다.
- ``uname -a`` 명령어와 동일하게 전체 시스템 정보를 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/d32af6a2-3b5c-4f39-b4ab-5aeb58d905dc)

# **13.whoami**: 현재 사용자 출력
```c
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL) {
        printf("%s\n", pw->pw_name);
    } else {
        perror("getpwuid 오류");
        return 1;
    }
    return 0;
}
```
## 설명
- **getuid()**: 현재 사용자의 UID(User ID)를 반환한다.
- **getpwuid(uid)**: ``getuid``로 얻은 ``uid``를 통해서 사용자 정보를 담은 **구조체(struct)** 를 반환한다.
- **passwd 구조체**: ``getpwuid``를 통해 얻은 구조체에서 ``pw_name``을 출력한다.
```c
#include <pwd.h>

struct passwd {
    char   *pw_name;       // 사용자 이름 ← 우리가 원하는 정보
    char   *pw_passwd;     // 암호 (대개 x 또는 *)
    uid_t   pw_uid;        // 사용자 ID
    gid_t   pw_gid;        // 그룹 ID
    char   *pw_gecos;      // 사용자 전체 이름
    char   *pw_dir;        // 홈 디렉토리
    char   *pw_shell;      // 로그인 셸
};
```


## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/e6e82748-e627-457c-a39e-b3f24ed39bf0)

# **14.file**: 파일의 **종류(type)**를 출력하는 명령어
```c
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }
    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat 실패");
        return 1;
    }
    printf("%s: ", argv[1]);

    if (S_ISREG(st.st_mode)) {
        printf("regular file\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("directory\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("symbolic link\n");
    } else if (S_ISCHR(st.st_mode)) {
        printf("character device\n");
    } else if (S_ISBLK(st.st_mode)) {
        printf("block device\n");
    } else if (S_ISFIFO(st.st_mode)) {
        printf("FIFO/pipe\n");
    } else if (S_ISSOCK(st.st_mode)) {
        printf("socket\n");
    } else {
        printf("unknown type\n");
    }
    return 0;
}
```
## 설명
- ``sys/stat.h``의 ``stat()`` 함수로 파일 메타데이터를 구조체로 받아온다.
- ``st_mode``의 비트 값을 ``S_ISREG()``, ``S_ISDIR()`` 등 매크로로 검사하여 파일의 타입을 판별한다.
- ``file`` 명령어처럼 해당 파일이 일반 파일인지, 디렉토리인지, 심볼릭 링크인지 등을 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/5972b3a6-46f1-42d5-85e0-405cb818d92e)

# **15.head**: 파일의 처음 몇 줄을 출력하는 명령어 ``[ 기본값:10줄 ]``

```c
#include <stdio.h>

#define MAX_LINE 1024
#define DEFAULT_LINE_COUNT 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("파일 열기 실패");
        return 1;
    }
    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL && count < DEFAULT_LINE_COUNT) {
        printf("%s", line);
        count++;
    }
    fclose(fp);
    return 0;
}
```
## 설명
- ``stdio.h``의 ``fopen()`` 함수를 사용하여 입력된 텍스트 파일을 **읽기 전용 모드("r")**로 연다.
- ``fgets()``를 통해 파일에서 한 줄씩 읽고, ``printf()``를 사용하여 화면에 출력한다.
- 출력된 줄의 수가 10줄이 되면 반복을 종료한다.
- 파일을 모두 출력한 뒤 ``fclose()``를 사용하여 파일을 닫는다.
- ``head`` 명령어와 동일하게 텍스트 파일의 처음 10줄만 출력하는 동작을 수행한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/6b00072c-0de1-46ca-b7de-65a9f119d6dd)

# **16.tail**: 파일의 마지막 몇 줄을 출력하는 명령어 ``[ 기본값: 10줄 ]``

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024
#define MAX_LINE_LENGTH 1024
#define DEFAULT_TAIL_LINES 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("파일 열기 실패");
        return 1;
    }
    char *lines[MAX_LINES];
    int count = 0;

    // 한 줄씩 읽고 배열에 저장
    while (!feof(fp)) {
        char buffer[MAX_LINE_LENGTH];
        if (fgets(buffer, sizeof(buffer), fp)) {
            lines[count % MAX_LINES] = strdup(buffer);
            count++;
        }
    }
    fclose(fp);

    // 출력 시작 인덱스 계산
    int start = count > DEFAULT_TAIL_LINES ? count - DEFAULT_TAIL_LINES : 0;

    // 출력
    for (int i = start; i < count; i++) {
        printf("%s", lines[i % MAX_LINES]);
        free(lines[i % MAX_LINES]); // 메모리 해제
    }
    return 0;
}
```
## 설명
- ``fopen()`` 함수로 텍스트 파일을 읽기 전용 모드로 연다.
- ``fgets()``를 사용해 한 줄씩 읽고, ``strdup()``으로 문자열을 동적으로 저장한다.
- 최대 1024줄까지 순환 버퍼 형태로 저장하여, 최근 줄만 유지하도록 한다.
- 읽은 줄의 총 개수가 10줄보다 많으면, ``count - 10``부터 출력한다.
- 출력 후 ``free()`` 함수를 통해 메모리를 해제한다.
- ``tail`` 명령어와 동일하게, 파일의 마지막 10줄만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/22668243-a17e-45ed-ad25-ea98bfa352d7)

# **17.mkdir**: 디렉토리 생성 명령어

```c
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [디렉토리 이름]\n", argv[0]);
        return 1;
    }
    const char *dirname = argv[1];

    // 0755 권한: rwxr-xr-x
    if (mkdir(dirname, 0755) == -1) {
        perror("디렉토리 생성 실패");
        return 1;
    }
    printf("디렉토리 '%s' 생성 완료\n", dirname);
    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현함
- ``sys/stat.h`` 헤더에 있는 **mkdir()** 함수를 통해서 디렉토리를 생성하며, 권한으로 **0755(사용자 rwx, 그룹 r-x, 기타 r-x)**를 준다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/ba940adc-f71a-4d68-af67-316888af008b)

# **18.rmdir**: 디렉토리 삭제 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [디렉토리 이름]\n", argv[0]);
        return 1;
    }
    const char *dirname = argv[1];

    if (rmdir(dirname) == -1) {
        perror("디렉토리 삭제 실패");
        return 1;
    }
    printf("디렉토리 '%s' 삭제 완료\n", dirname);
    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현함
- ``unistd.h`` 헤더에 있는 **rmdir()** 함수를 통해서 디렉토리를 삭제한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/51d0c882-8c09-49a1-8179-39fb2d338f3c)

# **19.touch**: 파일이 없으면 생성, 있으면 마지막 수정 시간 갱신 명령어

```c
#include <stdio.h>
#include <fcntl.h>
#include <utime.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    int fd;

    // 파일 열기 (없으면 생성), O_WRONLY 안 써도 시간 갱신 가능
    fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("파일 열기 실패");
        return 1;
    }
    close(fd);  // 파일만 열고 닫기

    // 시간 정보 갱신
    if (utime(filename, NULL) == -1) {
        perror("시간 갱신 실패");
        return 1;
    }
    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현함
- ``open()`` 에서 ``fcntl.h`` 에 정의된 **상수(O_CREAT, O_WRONLY)**들을 사용하여 파일이 존재하면 열고, 없으면 **0644권한(사용자 rw-, 그룹 r--, 기타 r--)**의 파일을 생성한 뒤, 즉시 닫는다.
- ``utime.h``에 정의된 **utime()** 함수로 파일의 접근시간과 수정시간을 변경한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/f5fe9a37-3288-4518-aa50-6a7cd76493a4)

# **20.cat**: 파일 내용을 출력하는 명령어

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("파일 열기 실패");
        return 1;
    }
    int c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
    fclose(fp);
    return 0;
}
```
## 설명
- ``stdio.h``의 ``fopen()`` 함수를 사용하여 입력된 텍스트 파일을 **읽기 전용 모드("r")**로 연다.
- ``fgetc()``를 통해 파일에서 한 문자씩 읽어오고, ``putchar()``로 화면에 출력한다.
- 파일의 끝(`EOF`)까지 반복하며 출력한 뒤, ``fclose()``로 파일을 닫는다.
- 텍스트 파일 하나의 전체 내용을 터미널에 출력하는 ``cat`` 명령어와 동일한 방식으로 동작한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/b0c6d522-ff02-4bbf-83b1-16b8d69db1c2)

# **21.cat -n**: 텍스트 파일의 각 줄 앞에 줄 번호를 붙여 출력하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일명]\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("파일 열기 실패");
        return 1;
    }
    int c;
    int line = 1;
    int new_line = 1;

    while ((c = fgetc(file)) != EOF) {
        if (new_line) {
            printf("%6d  ", line++);
            new_line = 0;
        }
        putchar(c);

        if (c == '\n') {
            new_line = 1;
        }
    }
    fclose(file);
    return 0;
}
```
## 설명
- fopen() 함수로 파일을 읽기 전용 모드 "r"로 연다.
- fgetc()로 파일을 한 문자씩 읽어오고, putchar()로 출력한다.
- 줄 바꿈 문자 \n이 나오면 줄 번호를 증가시키고 다음 줄에도 번호를 붙인다.
- cat -n 명령어처럼 각 줄 앞에 줄 번호를 출력한다.
- 출력 포맷은 printf("%6d ", line++)처럼 줄 번호가 6자리로 정렬된다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/a9b68d70-299b-40b3-97ab-56ba843da718)

# **22.clear**: 화면 지우기
```c
#include <stdio.h>

int main() {
    // ANSI 이스케이프 시퀀스로 화면 지우고, 커서 맨 위로 이동
    printf("\033[2J");   // 화면 전체 지우기
    printf("\033[H");    // 커서를 좌측 상단으로 이동
    fflush(stdout);      // 출력 즉시 반영
    return 0;
}
```

## 설명
- ``printf("\033[2J")``와 ``printf("\033[H")``를 이용해 직접 **ANSI escape 코드** 를 출력하여 화면을 지우고 커서를 초기 위치로 이동시켰다.

## 컴파일 및 실행화면
- 실행 전

![Image](https://github.com/user-attachments/assets/2cd401e1-03fb-4983-9c29-e9fd4364c783)

- 실행 후

![Image](https://github.com/user-attachments/assets/e3f4da39-3a70-42a8-aeb7-aa658925ac0b)

# **23.date**: 현재 시간 출력
```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    const char *weekdays[] = { "일", "월", "화", "수", "목", "금", "토" };

    if (t != NULL) {
        printf("%04d년 %02d월 %02d일 (%s) %02d:%02d:%02d\n",
               t->tm_year + 1900,
               t->tm_mon + 1,
               t->tm_mday,
               weekdays[t->tm_wday],  // 여기만 수정
               t->tm_hour,
               t->tm_min,
               t->tm_sec);
    } else {
        perror("localtime 오류");
        return 1;
    }
    return 0;
}
```
## 설명
- **time()**: 현재 시각을 **1970년 1월 1일 기준**으로 **초 단위**로 반환한다.
- **localtime()**: ``time_t`` 형식의 시간을 ``struct tm`` **구조체**로 변환하여 **년, 월, 일, 시, 분, 초** 등의 정보로 나눠줍니다.
- **tm 구조체**: ``localtime``을 통해서 얻은 구조체에서 시간, 날짜, 요일 등을 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/a8fbd1b7-e720-493a-85ef-31f70db7fc8a)

# **24.dirname**: 경로에서 디렉토리 이름만 추출하는 명령어

```c
#include <stdio.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [경로]\n", argv[0]);
        return 1;
    }
    char path[1024];
    snprintf(path, sizeof(path), "%s", argv[1]);

    printf("%s\n", dirname(path));  // 경로에서 디렉토리 경로 추출
    return 0;
}
```
## 설명
- libgen.h에 정의된 dirname() 함수는 문자열에서 마지막 '/' 앞부분을 반환한다.
- dirname()은 원본 문자열을 수정하므로, snprintf()로 복사한 후 사용한다.
- 경로가 포함된 파일이나 디렉토리 경로를 받아 디렉토리 부분만 출력한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/828d918e-2cb0-43a3-80dd-ea761ad958b0)

# **25.sleep**: 주어진 초(seconds)만큼 프로그램 실행을 일시 중지하는 명령어

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [초 단위 시간]\n", argv[0]);
        return 1;
    }
    int seconds = atoi(argv[1]);  // 문자열 → 정수 변환
    if (seconds < 0) {
        fprintf(stderr, "양의 정수를 입력하세요.\n");
        return 1;
    }
    sleep(seconds);  // 실행 일시 정지
    return 0;
}
```
## 설명
- unistd.h에 정의된 sleep() 함수는 초 단위로 프로그램을 일시 중지시킨다.
- atoi() 함수로 입력 문자열을 정수로 바꾼 뒤, 음수면 오류 처리한다.
- ./sleep_c 5라고 실행하면 5초 동안 멈췄다가 종료된다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/11664e4f-fafd-47e7-ba48-30b2e22ad1e8)

# **26.exit**: 프로그램 종료 명령어
```c
#include <stdlib.h>

int main() {
    exit(0);  // 0은 정상 종료를 의미
}

```
## 설명
- **exit()**을 이용해서 구현함

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/4ecf80b8-c6d1-4c0c-8df0-3d159adcb7df)

# **27.echo**: 문자열 출력
```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    // 인자가 1개 이상 있으면 (argv[0]은 실행 파일 이름)
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" "); // 단어 사이 공백
        }
    }
    printf("\n"); // 마지막에 줄바꿈
    return 0;
}
```
## 설명
- **명령줄 인자(argc, argv)** 를 활용하여 구현했음

## 컴파일 및 실행화면
![Image](https://github.com/user-attachments/assets/615196a4-a22e-459f-ba3b-cc73a21c90ab)

# **28.rm**: 파일 삭제 명령어

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [파일 이름]\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];

    if (unlink(filename) == -1) {
        perror("파일 삭제 실패");
        return 1;
    }
    printf("파일 '%s' 삭제 완료\n", filename);
    return 0;
}
```
## 설명
- ``unistd.h``에 정의된 **unlink()** 함수로 파일을 삭제한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/b183c897-4e00-4e43-8d3a-db87833a3d82)

# **29.rm -f**: 파일 조용한 삭제 명령어

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // 사용법 출력 (rm -f 형식이므로 인자는 1개만 받음)
        return 0;  // 조용히 종료
    }
    const char *filename = argv[1];

    // 삭제 시도 (실패해도 아무 메시지 없이 무시)
    unlink(filename);

    // 에러 메시지 없음 → rm -f는 조용히 실패를 무시함
    return 0;
}

```
## 설명
- ``unistd.h``에 정의된 **unlink()** 함수로 파일을 삭제한다.
- 에러가 나도 무시하기 때문에 별도의 ``if문``은 없다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/d52b9881-f300-4195-a440-1f3b4cbe1a23)

# **30.rm -r**: 디렉토리 및 내부 파일/디렉토리 재귀적 삭제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int remove_recursive(const char *path) {
    struct stat st;

    if (lstat(path, &st) == -1) {
        perror("lstat 실패");
        return -1;
    }

    // 파일 또는 심볼릭 링크면 unlink()
    if (!S_ISDIR(st.st_mode)) {
        return unlink(path);
    }

    // 디렉토리인 경우
    DIR *dir = opendir(path);
    if (!dir) {
        perror("디렉토리 열기 실패");
        return -1;
    }

    struct dirent *entry;
    char fullpath[1024];

    while ((entry = readdir(dir)) != NULL) {
        // "." ".." 무시
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // 재귀적으로 삭제
        if (remove_recursive(fullpath) == -1) {
            closedir(dir);
            return -1;
        }
    }

    closedir(dir);

    // 디렉토리 자체 삭제
    return rmdir(path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s [디렉토리 또는 파일]\n", argv[0]);
        return 1;
    }

    if (remove_recursive(argv[1]) == -1) {
        perror("삭제 실패");
        return 1;
    }

    printf("'%s' 삭제 완료\n", argv[1]);
    return 0;
}
```
## 설명

- ``sys/stat.h`` 헤더에 정의된 **`lstat()`** 함수를 사용하여, 입력된 경로가 **파일인지 디렉토리인지** 판별한다.
- 경로가 **파일**일 경우, ``unlink()`` 함수를 이용해 삭제한다.
- 경로가 **디렉토리**일 경우, ``dirent.h``의 ``readdir()``을 사용해 내부 항목을 하나씩 확인하고,
  각 항목에 대해 **재귀적으로 `remove_recursive()`**를 호출한다.
- 내부 항목이 파일이면 ``unlink()``로 삭제하고, 디렉토리면 다시 ``remove_recursive()``를 통해 같은 과정을 반복한다.
- 디렉토리 내부가 모두 비워진 뒤에는 ``rmdir()`` 함수를 사용하여 **디렉토리 자체를 삭제**한다.

## 컴파일 및 실행화면

![Image](https://github.com/user-attachments/assets/3bd44a32-10cc-48c4-98e9-995acf8616bc)
