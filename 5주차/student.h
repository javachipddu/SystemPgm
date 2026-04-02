#ifndef STUDENT_H
#define STUDENT_H
#define START_ID 1001001
 /* 구조체를 이용하여 학생 정보를 파일에 저장한다. */

struct student {
    int id;
    char name[20];
    short score;
};

#endif