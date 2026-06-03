
# 1. 파일 및 디렉토리 관리 명령어

파일 시스템을 조작, 관리하는 데에 기본적으로 사용되는 명령어이다.

## `pwd` : 현재 작업 디렉토리의 전체 경로를 출력한다.
```bash
pwd                      # 현재 위치의 절대 경로 출력
```

## `cd` : 현재 작업 디렉토리를 변경한다.
```bash
cd /path/to/directory    # 절대 경로로 이동
cd ..                    # 상위 디렉토리로 이동
cd ~                     # 홈 디렉토리로 이동
cd -                     # 이전 디렉토리로 이동
```

## `ls` : 디렉토리의 내용(파일 및 하위 디렉토리)을 나열한다.
```bash
ls                  # 현재 디렉토리 내용 표시
ls -la              # 자세한 정보와 숨김 파일 포함하여 표시
ls -lh              # 파일 크기를 읽기 쉬운 형태로 표시
```

## `mkdir` : 새로운 디렉토리를 생성한다.
```bash
mkdir new_directory      # 단일 디렉토리 생성
mkdir -p path/to/nested  # 중첩된 디렉토리 생성
```

## `rmdir` : 비어 있는 디렉토리를 삭제한다.
```bash
rmdir empty_directory    # 빈 디렉토리 삭제
```

## `cp` : 파일이나 디렉토리를 복사한다.
```bash
cp file1 file2           # 파일 복사
cp -r dir1 dir2          # 디렉토리 재귀적 복사
cp *.txt backup/         # 특정 패턴 파일들 복사
```

## `mv` : 파일이나 디렉토리의 이름을 변경하거나 이동한다.
```bash
mv oldname newname       # 파일/디렉토리 이름 변경
mv file.txt /path/to/    # 파일 이동
```

## `rm` : 파일이나 디렉토리를 삭제한다.
```bash
rm file.txt              # 파일 삭제
rm -r directory          # 디렉토리 재귀적 삭제
rm -f file.txt           # 강제 삭제
```

## `cat` : 파일의 내용을 터미널에 출력하거나 여러 파일을 연결한다.
```bash
cat file.txt             # 파일 내용 출력
cat file1 file2 > merged # 여러 파일을 합쳐서 새 파일 생성
```

## `head` : 파일의 시작 부분을 출력한다.
```bash
head file.txt            # 첫 10줄 출력
head -n 20 file.txt      # 첫 20줄 출력
```

## `tail` : 파일의 끝 부분을 출력한다.
```bash
tail file.txt            # 마지막 10줄 출력
tail -f logfile.log      # 실시간으로 파일 끝 부분 모니터링
```

## `chmod` : 파일 또는 디렉토리의 접근 권한(읽기, 쓰기, 실행)을 변경한다.
```bash
chmod 755 file.txt       # 숫자 방식으로 권한 설정
chmod +x script.sh       # 실행 권한 추가
chmod -w file.txt        # 쓰기 권한 제거
```

---

# 2. 프로세스 관리 명령어

시스템에서 실행 중인 프로세스를 확인, 제어하는 데에 사용되는 명령어이다.

## `top` : 시스템의 프로세스 상태, CPU 및 메모리 사용량 등을 실시간으로 모니터링한다.
```bash
top                      # 실시간 프로세스 모니터링
top -u username          # 특정 사용자의 프로세스만 표시
```

## `bg` : 중단된 작업을 백그라운드로 보낸다.
```bash
bg                       # 가장 최근에 중단된 작업을 백그라운드로
bg %1                    # 작업 번호 1을 백그라운드로
```

## `kill` : 특정 프로세스에 시그널을 보내어 종료하거나 제어한다.
```bash
kill 1234                # PID 1234 프로세스 종료
kill -9 1234             # 강제 종료
kill -STOP 1234          # 프로세스 일시 중단
```

## `killall` : 특정 이름을 가진 모든 프로세스에 시그널을 보낸다.
```bash
killall firefox          # firefox 이름의 모든 프로세스 종료
killall -9 chrome        # chrome 프로세스 강제 종료
```

---

# 3. 시스템 정보 및 네트워크 명령어

시스템의 상태를 확인하고 네트워크 연결을 관리하는 데에 사용되는 명령어이다.

## `who` / `w` : 현재 시스템에 로그인한 사용자 정보를 보여준다.
```bash
who                      # 로그인한 사용자 목록
w                        # 사용자 활동 정보와 함께 표시
whoami                   # 현재 사용자명 표시
```

## `df` : 디스크 파티션별 사용 가능한 공간 및 사용량을 보고한다.
```bash
df                       # 모든 파일시스템의 디스크 사용량 표시
df -h                    # 읽기 쉬운 형태로 표시
df /                     # 루트 파티션의 사용량만 표시
```

## `du` : 파일이나 디렉토리가 차지하는 디스크 공간을 요약하여 보여준다.
```bash
du -h directory          # 디렉토리 크기를 읽기 쉬운 형태로 표시
du -s *                  # 현재 디렉토리의 각 항목 크기 요약
du -sh ~/.cache          # 특정 디렉토리의 총 크기
```

## `hostname` : 시스템의 호스트 이름을 표시하거나 설정한다.
```bash
hostname                 # 현재 호스트 이름 표시
hostname newname         # 호스트 이름 변경 (임시)
```

## `uname` : 시스템 커널 이름, 호스트 이름, 커널 버전 등 시스템 정보를 출력한다.
```bash
uname -a                 # 모든 시스템 정보 표시
uname -r                 # 커널 버전 표시
uname -m                 # 머신 아키텍처 표시
```

## `ifconfig` / `ip` : 네트워크 인터페이스의 설정 및 상태 정보를 확인하거나 변경한다.
```bash
ifconfig                 # 모든 네트워크 인터페이스 정보 표시
ifconfig eth0            # 특정 인터페이스 정보 표시
ip addr show             # 네트워크 인터페이스 정보 표시 (현대적)
ip route                 # 라우팅 테이블 표시
```

## `ping` : 네트워크 호스트와의 연결성을 테스트하고 응답 시간을 측정한다.
```bash
ping google.com          # 호스트 연결성 테스트
ping -c 4 8.8.8.8        # 4번만 ping 전송
ping -i 2 localhost      # 2초 간격으로 ping
```

## `last` : 시스템의 최근 로그인 기록을 보여준다.
```bash
last                     # 최근 로그인 기록 표시
last username            # 특정 사용자의 로그인 기록
last -n 10               # 최근 10개 기록만 표시
```

---

# 4. 개발 및 유틸리티 명령어

프로그램 개발, 시스템 관리에 유용한 도구와 C/C++ 프로그램에서 핵심 기능을 수행하는 라이브러리 함수가 포함된다.

## `echo` : 터미널에 문자열을 출력한다. (쉘 스크립트에서 변수 값 확인 등에 사용한다)
```bash
echo "Hello World"       # 문자열 출력
echo $PATH               # 환경 변수 값 출력
echo -n "No newline"     # 줄바꿈 없이 출력
```

## `alias` : 기존 명령어에 대한 짧은 별칭(별명)을 생성한다.
```bash
alias ll='ls -la'        # ll을 ls -la의 별명으로 설정
alias ..='cd ..'         # ..을 상위 디렉토리 이동의 별명으로
alias                    # 현재 설정된 별명 목록 표시
```

## `man` : 명령어의 매뉴얼 페이지를 열어 자세한 사용법과 옵션을 제공한다.
```bash
man ls                   # ls 명령어의 매뉴얼 페이지 열기
man -k keyword           # 키워드로 매뉴얼 페이지 검색
man 3 printf             # 특정 섹션의 매뉴얼 페이지 열기
```

## `which` : 특정 명령어의 실행 파일이 위치한 경로를 찾아준다.
```bash
which python             # python 실행 파일 경로 찾기
which -a gcc             # 모든 해당 실행 파일 경로 표시
```

## `whereis` : 명령어의 바이너리, 소스 코드, 매뉴얼 페이지 파일의 위치를 찾아준다.
```bash
whereis ls               # ls 관련 파일들의 위치 찾기
whereis -b gcc           # 바이너리 파일만 찾기
whereis -m python        # 매뉴얼 페이지만 찾기
```

## `tar` : 여러 파일을 하나의 아카이브 파일로 묶거나 해제하는 데 사용된다. (압축 기능을 포함할 수 있다)
```bash
tar -czf archive.tar.gz files/  # 디렉토리를 gzip 압축하여 아카이브
tar -xzf archive.tar.gz         # gzip 아카이브 해제
tar -tf archive.tar             # 아카이브 내용 목록 보기
```

---

- 
