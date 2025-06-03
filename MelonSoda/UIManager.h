#pragma once
#include <iostream>
#include "Player.h"
#include "Monster.h"

class UIManager {
private:
    Player* player;
    Monster* monster;

    //정수형 자릿수 세는 함수
    int DigitCount(int num);

    //현재 출력하고 있는 줄
    int Current_Line = 0;

public:
    UIManager(Player* p, Monster* m);

    // 줄 위치 설정
    void setLine(int line);

    // 줄 위치 가져오기
    int getLine() const;

    //줄 위치 증감
    void incrementLine(int delta = 1);
    void decrementLine(int delta = 1);

    //커서 위치 이동시키는 함수
    void moveCursorTo(int x, int y);

    //플레이어 박스 초기화후 출력 함수
    void showPstats();
    //몬스터 박스 초기화후 출력 함수
    void showMstats();

    //함수 오버로딩 이용해서 체력줄만 갱신시키는 함수
    //플레이어
    void showPstats(int dmg);
    //몬스터
    void showMstats(int dmg);

    //화면 다지워버리는 함수
    void clearALL();
    //플레이어 박스 지우는 함수
    void clearP();
    //플레이어 박스 지우는 함수
    void clearM();

    //상단부 스탯 지우고 보여주는 함수
    void RefreshStats();
    //하단부 로그 지우는 함수
    void showLog();
    //위에 두개 합쳐놓은 함수
    void RefreshScreen();

    //로그 출력하는 함수들 템플릿화 + 인자수로 오버로딩
    // 양식 복붙하면 5개 6개까지 증가 가능
    //1.일반 텍스트만 출력 (1개면 사실상 이경우만 할듯)
    void PrintLog(const std::string& log);
    //2. 2개짜리 출력
    template<typename T1, typename T2>
    void PrintLog(T1 a, T2 b);
    //3. 3개짜리 출력
    template<typename T1, typename T2, typename T3>
    void PrintLog(T1 a, T2 b, T3 c);
    //4. 4개짜리 출력
    template<typename T1, typename T2, typename T3, typename T4>
    void PrintLog(T1 a, T2 b, T3 c, T4 d);
    //5.  5개짜리 출력
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    void PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e);
    //6.  6개짜리 출력
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    void PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f);
    //7.  7개짜리 출력
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    void PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f, T7 g);

    //타이틀 출력
    void PrintTitle();
    //인트로 출력
    void PrintIntro();
    //트루엔딩 출력
    void PrintTrueEnd();
};

//여기에 함수정의를 안하면 에러생김 
//생 노가다로 7개까지 정의했는데 더 좋은 방법 있으면 수정해주셔도 됩니다.
//저는 더 좋은 방법을 모르겟어요

//2. 2개짜리 정의
template<typename T1, typename T2>
void UIManager::PrintLog(T1 a, T2 b) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//3. 3개짜리 정의
template<typename T1, typename T2, typename T3>
void UIManager::PrintLog(T1 a, T2 b, T3 c) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//4. 4개짜리 정의
template<typename T1, typename T2, typename T3, typename T4>
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//5. 5개짜리 정의
template<typename T1, typename T2, typename T3, typename T4, typename T5>
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d << e;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//6. 6개짜리 정의
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d << e<< f;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//7. 7개짜리 정의
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f, T7 g)
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d << e << f << g;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}


//전역 포인터 선언
extern UIManager* G_UI;