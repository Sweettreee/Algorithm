 ##################

  #프로그램명: Grade Management Program

  #작성자: 2022041019 / 김진식

  #작성일: 15 Apr

  #프로그램 설명: 입력으로 학번, 이름을 받고 각 학생의 영어, C언어, python점수를 입력받아, 총점, 평균, 학점, 등수를 계산하는 프로그램입니다.
               #또한 학생을 학번과 이름으로 학생의 정보를 검색하고 80점 이상 학생 수를 카운트하고, 총점에 따라 정렬을 하고, 학생 정보를 삽입, 삭제 할 수 있는 프로그램입니다.

  ###################


class Student:
    def __init__(me, hakbun, name, eng, c, py):
        me.hakbun = hakbun
        me.name = name
        me.eng = eng
        me.c = c
        me.py = py
        me.total = eng + c + py
        me.avg = me.total / 3
        me.grade = me.calc_grade()
        me.rank = None

    def calc_grade(self):
        if self.avg >= 90:
            return 'A'
        elif self.avg >= 80:
            return 'B'
        elif self.avg >= 70:
            return 'C'
        elif self.avg >= 60:
            return 'D'
        else:
            return 'F'

    def __str__(me):
        return f"{me.hakbun}\t{me.name}\t{me.eng}\t{me.c}\t{me.py}\t{me.total}\t{me.avg:.2f}\t{me.grade}\t{me.rank}"

def input_students():
    students = []
    while len(students) < 5:
        hakbun = input(f"{len(students)+1}번째 학생 학번: ")
        # 학번 중복 체크
        if any(s.hakbun == hakbun for s in students):
            print("이미 존재하는 학번입니다.")
            continue
        name = input("이름: ")
        eng = int(input("영어 점수: "))
        c = int(input("C언어 점수: "))
        py = int(input("파이썬 점수: "))
        students.append(Student(hakbun, name, eng, c, py))
    return students

def calc_ranks(students):
    sorted_students = sorted(students, key=lambda x: x.total, reverse=True)
    for i, s in enumerate(sorted_students):
        s.rank = i + 1
    # 원래 순서에 맞게 등수 반영
    hakbun_to_rank = {s.hakbun: s.rank for s in sorted_students}
    for s in students:
        s.rank = hakbun_to_rank[s.hakbun]

def print_students(students):
    print("학번    이름    영어    C언어    파이썬  총점    평균    학점    등수")
    for s in students:
        print(s)

def search_student(students, key, by='hakbun'):
    if by == 'hakbun':
        for s in students:
            if s.hakbun == key:
                return s
    elif by == 'name':
        for s in students:
            if s.name == key:
                return s
    return None

def delete_student(students, key, by='hakbun'):
    for i, s in enumerate(students):
        if (by == 'hakbun' and s.hakbun == key) or (by == 'name' and s.name == key):
            del students[i]
            return True
    return False

def sort_by_total(students):
    return sorted(students, key=lambda x: x.total, reverse=True)

def count_above_80(students):
    return sum(1 for s in students if s.avg >= 80)

def main():
    students = input_students()
    calc_ranks(students)
    while True:
        print("\n1. 전체 출력 2. 학생 검색 3. 학생 삭제 4. 총점순 정렬 출력 5. 80점 이상 학생수 6. 종료")
        sel = input("메뉴 선택: ")
        if sel == '1':
            print_students(students)
        elif sel == '2':
            mode = input("검색 기준(1:학번, 2:이름): ")
            if mode == '1':
                key = input("학번 입력: ")
                s = search_student(students, key, by='hakbun')
            else:
                key = input("이름 입력: ")
                s = search_student(students, key, by='name')
            if s:
                print("학번    이름    영어    C언어    파이썬    총점    평균    학점    등수")
                print(s)
            else:
                print("학생을 찾을 수 없습니다.")
        elif sel == '3':
            mode = input("삭제 기준(1:학번, 2:이름): ")
            if mode == '1':
                key = input("학번 입력: ")
                result = delete_student(students, key, by='hakbun')
            else:
                key = input("이름 입력: ")
                result = delete_student(students, key, by='name')
            if result:
                print("삭제 완료.")
                calc_ranks(students)
            else:
                print("학생을 찾을 수 없습니다.")
        elif sel == '4':
            print("총점순 정렬 결과:")
            print_students(sort_by_total(students))
        elif sel == '5':
            print(f"80점 이상 학생 수: {count_above_80(students)}")
        elif sel == '6':
            print("프로그램 종료.")
            break
        else:
            print("잘못된 입력입니다.")

if __name__ == "__main__":
    main()
