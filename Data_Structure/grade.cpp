#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;

struct Subject {// 과목 정보
    char SubName[30]; // 과목이름
    int Hakjum; // 과목학점
    char Grade[10]; // 과목등급
    float GPA; // 과목 평점
};

struct Student {// 학생 정보
    char StdName[30]; // 학생 이름
    int Hakbun; // 학번
    Subject *Sub; // 과목
    int SubNum; // 과목수
    float AveGPA; // 교과목 평균 평점
};

inline void PrintMenu()
{
    cout << "===== 메뉴 =====" << "\n";
    cout << "1.  학생 성적 입력" << "\n";
    cout << "2.  전체 학생 성적 보기" << "\n";
    cout << "3. 학생 이름 검색" << "\n";
    cout << "4. 전체 학생 목록 보기" << "\n";
    cout << "5. 학생 정보 수정" << "\n";
    cout << "6.  프로그램 종료" << "\n";

    cout << "원하는 기능을 입력하세요 : ";
}

inline void InputValue(char *str)
{
    cin >> str;
}
inline void InputValue(int &i)
{
    cin >> i;
}

void CalcGPA(Subject *Sub, int SubNum)
{
    for(int j=0; j<SubNum; j++){
        if(strcmp(Sub[j].Grade,"A+")==0){
            Sub[j].GPA = (4.5) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"A")==0){
            Sub[j].GPA = (4.0) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"B+")==0){
            Sub[j].GPA = (3.5) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"B")==0){
            Sub[j].GPA = (3.0) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"C+")==0){
            Sub[j].GPA = (2.5) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"C")==0){
            Sub[j].GPA = (2.0) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"D+")==0){
            Sub[j].GPA = (1.5) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"D")==0){
            Sub[j].GPA = (1.0) * Sub[j].Hakjum;
        }
        else if(strcmp(Sub[j].Grade,"F")==0){
            Sub[j].GPA = (0.0) * Sub[j].Hakjum;
        }
    }
}

float CalcAveGPA(Subject *Sub, int SubNum)
{
    float tmp=0.0;
    for(int i=0; i<SubNum; i++){
        tmp += Sub[i].GPA;
    }
    return tmp/SubNum;
}

void InputData(Student *pSt, int StudentNum)
{
    cout << "\n\n";
    for(int i=0; i<StudentNum; i++){
        cout << "\n";
        cout << "* " << i+1 << "번째 학생 이름과 학번을 입력하세요" << "\n";
        cout << "이름 : ";
        InputValue(pSt[i].StdName);
        cout << "학번 : ";
        InputValue(pSt[i].Hakbun);
        cout << "과목 수를 입력하세요 : ";
        InputValue(pSt[i].SubNum);
        pSt[i].Sub = new Subject[pSt[i].SubNum];

        cout << "\n\n* 수강한 과목3개와 각 교과목명, 과목학점, 과목등급을 입력하세요." << "\n";
        for(int j=0; j<pSt[i].SubNum; j++){
            cout << "교과목명 : ";
            InputValue(pSt[i].Sub[j].SubName);
            cout << "과목학점수 : ";
            InputValue(pSt[i].Sub[j].Hakjum);
            cout << "과목 등급(A+ ~ F) : ";
            InputValue(pSt[i].Sub[j].Grade);
            cout << "\n";
        }
        CalcGPA(pSt[i].Sub, pSt[i].SubNum);
        pSt[i].AveGPA = CalcAveGPA(pSt[i].Sub,pSt[i].SubNum);
    }
    cout << "\n\n";
}

void PrintAllData(const Student *stu, int StudentNum)
{
    for(int i=0; i<StudentNum; i++){
        cout << "   " << "전체 학생 성적 보기" << '\n';
        cout << "=========================================================================" << "\n";
        cout << "이름 : " << stu[i].StdName << "   학번 : " << stu[i].Hakbun << "\n";
        cout << "=========================================================================" << "\n";
        cout << "   " << "과목명" << "   " << "과목학점" << "   " << "과목학점" << "   " << "과목평점" << "\n";
        cout << "=========================================================================" << "\n";
        for(int j=0; j<stu->SubNum; j++){
            cout << setw(10)<< stu[i].Sub[j].SubName << setw(10) << stu[i].Sub[j].Hakjum << setw(10) << stu[i].Sub[j].Grade << setw(10);
            cout << fixed;
            cout.precision(2);
            cout << stu[i].Sub[j].GPA << "\n";
        }
        cout << "=========================================================================" << "\n";
        cout << "                           " << "평균평점" << "   " << stu[i].AveGPA << "\n\n\n";
    }   
}

Student* StdSearch(Student *pSt, int StudentNum)
{
    char tmpName[30];
    cout << "검색 할 학생 이름 : " << " ";
    cin >> tmpName;
    for(int i=0; i<StudentNum; i++){
        if(strcmp(tmpName,pSt[i].StdName)==0){
            return &pSt[i];
        }
    }
    return nullptr;
}

void PrintOneData(const Student* rSt)
{
    cout << "이름 : " << rSt->StdName << "   학번 : " << rSt->Hakbun << "\n";
    cout << "=========================================================================" << "\n";
    cout << "   " << "과목명" << "   " << "과목학점" << "   " << "과목학점" << "   " << "과목평점" << "\n";
    cout << "=========================================================================" << "\n";
    for(int j=0; j<rSt->SubNum; j++){
        cout << setw(10)<< rSt->Sub[j].SubName << setw(10) << rSt->Sub[j].Hakjum << setw(10) << rSt->Sub[j].Grade << setw(10);
        cout << fixed;
        cout.precision(2);
        cout << rSt->Sub[j].GPA << "\n";
    }
    cout << "=========================================================================" << "\n";
    cout << "                           " << "평균평점" << "   " << rSt->AveGPA << "\n\n\n";
}

void modifyStdInfo(Student *stu, int StdNum)
{
    Student* tmp = StdSearch(stu, StdNum);
    cout << "\n";
        cout << "변경할 이름과 학번을 입력하세요" << "\n";
        cout << "이름 : ";
        cin >> tmp->StdName;
        cout << "학번 : ";
        cin >> tmp->Hakbun;

        cout << "\n\n* 수강한 과목3개와 각 교과목명, 과목학점, 과목등급을 입력하세요." << "\n";
        for(int j=0; j<tmp->SubNum; j++){
            cout << "교과목명 : ";
            cin >> tmp->Sub[j].SubName;
            cout << "과목학점수 : ";
            cin >> tmp->Sub[j].Hakjum;
            cout << "과목 등급(A+ ~ F) : ";
            cin >> tmp->Sub[j].Grade;
            cout << "\n";
            if(strcmp(stu->Sub[j].Grade,"A+")==0){
                tmp->Sub[j].GPA = (4.5) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"A")==0){
                tmp->Sub[j].GPA = (4.0) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"B+")==0){
                tmp->Sub[j].GPA = (3.5) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"B")==0){
                tmp->Sub[j].GPA = (3.0) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"C+")==0){
                tmp->Sub[j].GPA = (2.5) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"C")==0){
                tmp->Sub[j].GPA = (2.0) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"D+")==0){
                tmp->Sub[j].GPA = (1.5) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"D")==0){
                tmp->Sub[j].GPA = (1.0) * tmp->Sub[j].Hakjum;
            }
            else if(strcmp(stu->Sub[j].Grade,"F")==0){
                tmp->Sub[j].GPA = (0.0) * tmp->Sub[j].Hakjum;
            }
            tmp->AveGPA += tmp->Sub[j].GPA;
        }
        tmp->AveGPA /= tmp->SubNum;
}

void PrintAllStdList(const Student *pSt, int StudentNum = 2)
{
    cout << "=========================================================================" << "\n";
    cout << setw(10) << "학번" << setw(10) << "이름" <<"\n";
    for(int i=0; i<StudentNum; i++){
        cout <<pSt[i].Hakbun << setw(10) << pSt[i].StdName << "\n";
    }
}

int programExit()
{
    cout << "프로그램을 종료합니다." << "\n";
    cout << "계속하려면 아무 키나 누르십시오 . . ." << "\n";
    return 0;
}

int main(void)
{
    
    int StdNum;
    cout << "학생 수를 입력하시오 : ";
    cin >> StdNum;
    Student *St = new Student[StdNum];
    while(1)
    {
        int n;
        PrintMenu(); // 메뉴 출력
        cin >> n;
        cout << "\n\n";
        if(n==1){
            InputData(St,StdNum); // 학생 정보 입력, 평점 계산, 개인 학생의 교과목 평균 평점 계산
        }
        else if(n==2){
            PrintAllData(St,StdNum); // 전체 학생의 신상/성적 정보 출력
        }
        else if(n==3){
            Student* tmp = StdSearch(St,StdNum);
            PrintOneData(tmp);
        }
        else if(n==4){
            PrintAllStdList(St); // 전체 학생 목록 보기
        }
        else if(n==5){
            modifyStdInfo(St,2);
        }
        else{
            cout << "2022041019 김진식" << "\n";
            delete[] St;
            return programExit(); // 프로그램 종료
        }
    }
    
    return 0;
}