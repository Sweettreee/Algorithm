import mysql.connector

# DB 연결 정보 상수로 선언
DB_CONFIG = {
    'host': 'localhost',
    'user': 'root',
    'password': 'password',
    'database': 'schooldb'
}

def create_database_and_table():
    # 1. MySQL 서버에 접속 (데이터베이스 지정 X)
    conn = mysql.connector.connect(
        host=DB_CONFIG['host'],
        user=DB_CONFIG['user'],
        password=DB_CONFIG['password']
    )
    cur = conn.cursor()
    # 2. 데이터베이스 생성
    cur.execute("CREATE DATABASE IF NOT EXISTS schooldb")
    conn.commit()
    cur.close()
    conn.close()

    # 3. 생성한 데이터베이스에 접속
    conn = mysql.connector.connect(**DB_CONFIG)
    cur = conn.cursor()
    # 4. 테이블 생성
    cur.execute("""
CREATE TABLE IF NOT EXISTS students (
    student_id VARCHAR(20) PRIMARY KEY,
    name VARCHAR(50),
    english INT,
    c_lang INT,
    python INT,
    total INT,
    average FLOAT,
    grade CHAR(1),
    `rank` INT
)
""")

    conn.commit()
    cur.close()
    conn.close()
    print("데이터베이스와 테이블이 준비되었습니다.")

def connect_db():
    return mysql.connector.connect(**DB_CONFIG)

def calculate_grade(avg):
    if avg >= 90:
        return 'A'
    elif avg >= 80:
        return 'B'
    elif avg >= 70:
        return 'C'
    elif avg >= 60:
        return 'D'
    else:
        return 'F'

def insert_student():
    conn = connect_db()
    cur = conn.cursor() # SQL 실행을 위한 커서를 만든다.
    student_id = input("학번: ")
    name = input("이름: ")
    english = int(input("영어 점수: "))
    c_lang = int(input("C-언어 점수: "))
    python_score = int(input("파이썬 점수: "))
    total = english + c_lang + python_score
    average = total / 3
    grade = calculate_grade(average)
    sql = """INSERT INTO students (student_id, name, english, c_lang, python, total, average, grade, `rank`)
             VALUES (%s, %s, %s, %s, %s, %s, %s, %s, 0)"""
    try:
        cur.execute(sql, (student_id, name, english, c_lang, python_score, total, average, grade))
        conn.commit()
        print("학생이 추가되었습니다.")
    except mysql.connector.IntegrityError:
        print("이미 존재하는 학번입니다. 다른 학번을 입력하세요.")
    except mysql.connector.Error as err:
        print("에러:", err)
    finally:
        cur.close()
        conn.close()

def delete_student():
    conn = connect_db()
    cur = conn.cursor()
    student_id = input("삭제할 학생의 학번: ")
    cur.execute("DELETE FROM students WHERE student_id=%s", (student_id,))
    conn.commit()
    cur.close()
    conn.close()
    print("삭제되었습니다.")

def update_ranks():
    conn = connect_db()
    cur = conn.cursor()
    cur.execute("SELECT student_id FROM students ORDER BY total DESC")
    students = cur.fetchall()
    for idx, (student_id,) in enumerate(students):
        cur.execute("UPDATE students SET `rank`=%s WHERE student_id=%s", (idx+1, student_id))
    conn.commit()
    cur.close()
    conn.close()

def print_students():
    conn = connect_db()
    cur = conn.cursor()
    cur.execute("SELECT * FROM students ORDER BY `rank` ASC")
    rows = cur.fetchall()
    print("학번\t이름\t영어\tC-언어\t파이썬\t총점\t평균\t학점\t등수")
    for row in rows:
        print(f"{row[0]}\t{row[1]}\t{row[2]}\t{row[3]}\t{row[4]}\t{row[5]}\t{row[6]:.2f}\t{row[7]}\t{row[8]}")
    cur.close()
    conn.close()

def search_student_by_id():
    conn = connect_db()
    cur = conn.cursor()
    student_id = input("검색할 학번: ")
    cur.execute("SELECT * FROM students WHERE student_id=%s", (student_id,))
    row = cur.fetchone()
    if row:
        print("학번\t이름\t영어\tC-언어\t파이썬\t총점\t평균\t학점\t등수")
        print(f"{row[0]}\t{row[1]}\t{row[2]}\t{row[3]}\t{row[4]}\t{row[5]}\t{row[6]:.2f}\t{row[7]}\t{row[8]}")
    else:
        print("해당 학번의 학생이 없습니다.")
    cur.close()
    conn.close()

def search_student_by_name():
    conn = connect_db()
    cur = conn.cursor()
    name = input("검색할 이름: ")
    cur.execute("SELECT * FROM students WHERE name=%s", (name,))
    rows = cur.fetchall()
    if rows:
        print("학번\t이름\t영어\tC-언어\t파이썬\t총점\t평균\t학점\t등수")
        for row in rows:
            print(f"{row[0]}\t{row[1]}\t{row[2]}\t{row[3]}\t{row[4]}\t{row[5]}\t{row[6]:.2f}\t{row[7]}\t{row[8]}")
    else:
        print("해당 이름의 학생이 없습니다.")
    cur.close()
    conn.close()

def count_above_80():
    conn = connect_db()
    cur = conn.cursor()
    cur.execute("SELECT COUNT(*) FROM students WHERE average >= 80")
    count = cur.fetchone()[0]
    print(f"평균 80점 이상 학생 수: {count}")
    cur.close()
    conn.close()

def main():
    while True:
        print("\n1. 전체 출력\n2. 학생 추가\n3. 학생 삭제\n4. 학번 검색\n5. 이름 검색\n6. 등수 갱신\n7. 80점 이상 학생 수\n8. 종료")
        choice = input("선택: ")
        if choice == '1':
            print_students()
        elif choice == '2':
            insert_student()
            update_ranks()
        elif choice == '3':
            delete_student()
            update_ranks()
        elif choice == '4':
            search_student_by_id()
        elif choice == '5':
            search_student_by_name()
        elif choice == '6':
            update_ranks()
            print("등수 갱신 완료.")
        elif choice == '7':
            count_above_80()
        elif choice == '8':
            print("프로그램 종료.")
            break
        else:
            print("잘못된 입력입니다.")

if __name__ == "__main__":
    create_database_and_table()
    main()
