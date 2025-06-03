#include "UIManager.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

//현재 코드 유의사항 ui 출력위치를 전부다 포인터로 통제중이라 줄넘김했을떄 꼬일 가능성이 존재함 이점 주의!
//커서이동 시키는애 public 으로 빼두었으니 이용해주시면 감사하겠습니다.
//(0,0) ~ (약100,9) 영역이 상단 플레이어 몬스터 ui 영역
//(0,10) 부터 스토리나 기타 로그 나오게 되잇는데 필요시 조정

UIManager::UIManager(Player* p, Monster* m) : player(p), monster(m) {}

//정수형 자릿수 카운팅 
int UIManager::DigitCount(int num)
{
    return std::to_string(num).length();
}


//위는 함수를 위한 함수(private)들 아래는 여러모로 쓸 함수들


//커서 이동함수
void UIManager::moveCursorTo(int x, int y)
{
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 커서 줄 위치 설정
void UIManager::setLine(int line) {
    if (line >= 0) {
        Current_Line = line;
    }
}

// 줄 위치 가져오기
int UIManager::getLine() const {
    return Current_Line;
}

// 줄 위치 증가
void UIManager::incrementLine(int delta) {
    Current_Line += delta;
    if (Current_Line > 99) Current_Line = 99; // 화면 영역 고려
}

// 줄 위치 감소
void UIManager::decrementLine(int delta) {
    Current_Line -= delta;
    if (Current_Line < 0) Current_Line = 0;
}
//상단부 갱신시켜서 보여주는 함수
void UIManager::RefreshStats()
{
    clearP();
    clearM();
    showPstats();
    showMstats();
}

//플레이어칸 지우는 함수
void UIManager::clearP()
{
    for (int j = 0; j < 9; j++)
    {
        moveCursorTo(0, 0 + j);
        std::cout << "                                                ";
    }
}

//몬스터칸 지우는 함수
void UIManager::clearM()
{
    for (int j = 0; j < 9; j++)
    {
        moveCursorTo(50, 0 + j);
        std::cout << "                                                ";
    }
}

//로그창 포함 다 지우는 함수
void UIManager::clearALL()
{
    for (int j = 0; j < 100; j++)
    {
        moveCursorTo(0, 0 + j);
        std::cout << "                                                                                                                                                                                                         ";
    }
    moveCursorTo(0, 0);
    Current_Line = 0;
}


//플레이어 스탯 보여주는 함수
void UIManager::showPstats()
{
    for (int j = 0; j < 6; j++) // 플레이어 박스영역만 지우기 (공백칸수 및 시작지점 조정)
    {
        moveCursorTo(0, 0 + j);
        std::cout << "                                                ";
    }

    for (int j = 0; j < 9; j++)
    {
        moveCursorTo(0, 0 + j);

        if (j == 0) { std::cout << "┌────── 플레이어의 스탯 ──────┐     "; }
        if (j == 1) { std::cout << "│이름: " << player->name << std::setw(25 + 0 - player->name.length()) << "│"; }
        if (j == 2) { std::cout << "│HP: " << player->HP << std::setw(25 + 2 - DigitCount(player->HP)) << "│"; }
        if (j == 3) { std::cout << "│MP: " << player->MP << std::setw(25 + 2 - DigitCount(player->MP)) << "│"; }
        if (j == 4) { std::cout << "│ATK: " << player->ATK << std::setw(25 + 1 - DigitCount(player->ATK)) << "│"; }
        if (j == 5) { std::cout << "│DEF: " << player->DEF << std::setw(25 + 1 - DigitCount(player->DEF)) << "│"; }
        if (j == 6) { std::cout << "│참기: " << player->concentration << std::setw(25 + 0 - DigitCount(player->concentration)) << "│"; }
        if (j == 7) { std::cout << "└─────────────────────────────┘"; }
        if (j == 8) { std::cout << " "; }
        
    }
}

//몬스터 스탯 보여주는 함수
void UIManager::showMstats()
{
    for (int j = 0; j < 6; j++)// 몬스터 박스영역만 지우기 (공백칸수 및 시작지점 조정)
    {
        moveCursorTo(50, 0 + j);
        std::cout << "                                                ";
    }

    if (monster->HP < 0) { return; } //몬스터 없으면 박스 출력 X

    if (monster->name == "마녀")
    {
        for (int j = 0; j < 9; j++)
        {
            moveCursorTo(50, 0 + j);
            if (j == 0) { std::cout << "┌────── 적몬스터의 스탯 ──────┐     "; }
            if (j == 1) { std::cout << "│이름: " << monster->name << std::setw(25 + 0 - monster->name.length()) << "│"; }
            if (j == 2) { std::cout << "│HP: " << monster->HP << std::setw(25 + 2 - DigitCount(monster->HP)) << "│"; }
            if (j == 3) { std::cout << "│MP: " << monster->MP << std::setw(25 + 2 - DigitCount(monster->MP)) << "│"; }
            if (j == 4) { std::cout << "│ATK: " << monster->ATK << std::setw(25 + 1 - DigitCount(monster->ATK)) << "│"; }
            if (j == 5) { std::cout << "│DEF: " << monster->DEF << std::setw(25 + 1 - DigitCount(monster->DEF)) << "│"; }
            if (j == 6) { std::cout << "│미래: " << monster->Get_Stack() << std::setw(25 + 0 - DigitCount(monster->Get_Stack())) << "│"; }
            if (j == 7) { std::cout << "└─────────────────────────────┘"; }
            if (j == 8) { std::cout << " "; }
        }
    }
    else
    {
        for (int j = 0; j < 9; j++)
        {
            moveCursorTo(50, 0 + j);
            if (j == 0) { std::cout << "┌────── 적몬스터의 스탯 ──────┐     "; }
            if (j == 1) { std::cout << "│이름: " << monster->name << std::setw(25 + 0 - monster->name.length()) << "│"; }
            if (j == 2) { std::cout << "│HP: " << monster->HP << std::setw(25 + 2 - DigitCount(monster->HP)) << "│"; }
            if (j == 3) { std::cout << "│MP: " << monster->MP << std::setw(25 + 2 - DigitCount(monster->MP)) << "│"; }
            if (j == 4) { std::cout << "│ATK: " << monster->ATK << std::setw(25 + 1 - DigitCount(monster->ATK)) << "│"; }
            if (j == 5) { std::cout << "│DEF: " << monster->DEF << std::setw(25 + 1 - DigitCount(monster->DEF)) << "│"; }
            if (j == 6) { std::cout << "│"<<std::setw(31) << "│"; }
            if (j == 7) { std::cout << "└─────────────────────────────┘"; }
            if (j == 8) { std::cout << " "; }
        }
    }
}

//함수 오버로딩 써서 데미지값 있을때 hp열만 갱신
void UIManager::showPstats(int dmg)
{
    if (player->hitDamage <= 0) return;
    moveCursorTo(0, 2);
    std::cout << "│HP: " << player->HP << std::setw(5) << "(-" << dmg << ")" << std::setw(20 + 1 - DigitCount(player->HP) - DigitCount(dmg)) << "│";
}

void UIManager::showMstats(int dmg)
{
    if (monster->HP < 0) return;
    if (monster->hitDamage <= 0) return;
    moveCursorTo(50, 2);
    std::cout << "│HP: " << monster->HP << std::setw(5) << "(-" << dmg << ")" << std::setw(20 + 1 - DigitCount(monster->HP) - DigitCount(dmg)) << "│";
}



//로그창 리셋후 로그창 위치로 커서 이동하는 함수
void UIManager::showLog()
{
    for (int j = 0; j < 30; j++)
    {
        moveCursorTo(0, 10 + j);
        std::cout << "                                                                                                              ";
    }
    moveCursorTo(0, 10);
    Current_Line = 10;
}

//화면갱신
void UIManager::RefreshScreen()
{
    RefreshStats();
    showLog();
}

//텍스트만 출력
void UIManager::PrintLog(const std::string& log) 
{
    if (Current_Line > 30)
    {
        Current_Line = 10;
        showLog();
    }
    moveCursorTo(0, Current_Line++);
    std::cout << log;
}

//타이틀 출력
void UIManager::PrintTitle()
{
    for (int j = 0; j < 12; j++)
    {
        moveCursorTo(30, 5 + j);
        if (j == 0) { std::cout << "┌─────────────────────────────────────────────────────┐     "; }
        if (j == 1) { std::cout <<"│"<<std::setw(55) << "│"; }
        if (j == 2) { std::cout << "│"<<std::setw(55) << "│"; }
        if (j == 3) { std::cout << "│" << std::setw(40) << "누가 내 멜론소다에 독 탔어?" << std::setw(15) << "│";}
        if (j == 4) { std::cout << "│" << std::setw(55) << "│";}
        if (j == 5) { std::cout << "│" << std::setw(27) << "TEAM: 자몽소다" << std::setw(28) << "│";; }
        if (j == 6) { std::cout << "│" << std::setw(55) << "│";}
        if (j == 7) { std::cout << "└─────────────────────────────────────────────────────┘"; }
        if (j == 8) { std::cout << " "; }
        if (j == 11) { std::cout << std::setw(20) << "성함을 입력해주세요 : "; }
       

    }
}

//인트로랑 트루엔딩 묶어둔거
void UIManager::PrintIntro()
{
    clearALL();
    PrintLog("<프롤로그>");
    Sleep(500);
    PrintLog("과학보단 마법이 발전한 도시 <아쿠아>");
    Sleep(500);
    PrintLog("그곳의 명물인 멜론 소다는 빛나는 갑옷을 두른 용사에게는 하루를 살아가는 유일한 낙이었다.");
    Sleep(500);
    PrintLog("용사 : (씩 웃으며)좋았어, 오늘도 살아가기위해 멜론 소다 한 잔하러 가야지~");
    Sleep(500);
    PrintLog("하지만 거리를 걷던 중 보인 펫말의 한마디");
    Sleep(500);
    PrintLog("<멜론 소다 일시 품절>");
    Sleep(500);
    PrintLog("용사 : 뭐라고? 일...시..품..절? 이거 완전 콩없는 콩밥이잖아!");
    Sleep(500);
    PrintLog("(매장 안에서 식사하고 있는 한 토끼 수인에게 말을 건다) 이봐, 왜 갑자기 멜론이 동난거지?");
    Sleep(500);
    PrintLog("토끼 수인 : 나도 몰라, 하지만 들리는 소문에 의하면 마을 근처 숲에서 거주하고 있는 마녀가 멜론 밭에다가 독을 풀었나봐.");
    Sleep(500);
    PrintLog("            궁금하면 직접 물어보러 가봐 (당근을 마저 먹는다)");
    Sleep(500);
    PrintLog("용사 : 음, 마녀라 언제부터 그런 존재가 근처에 있었던거지?");
    Sleep(500);
    PrintLog("       내가 이렇게 둔감했던가? (한숨을 쉬며) 가서 확인을 해봐야겠어.");
    Sleep(500);
    PrintLog("       가보자고 오랜만에 모험이다.");
    Sleep(6000);

    clearALL();

    PrintLog("<낯선 멜로디>");
    Sleep(500);
    PrintLog("용사 : 드디어 도......착.....?? 여기가 마녀의 성이라고? 평범한 탑 같이 생겨먹었네.");
    Sleep(500);
    PrintLog("         분위기가 안살잖아..... 뭐, 일단 들어가볼...");
    Sleep(500);
    PrintLog("탑에 들어가려고 하자 한 소녀의 실루엣이 탑 위에 비쳐졌다.");
    Sleep(500);
    PrintLog("용사 : 뭐여 이건?");
    Sleep(500);
    PrintLog("XX : 무슨 일로 온거야?");
    Sleep(500);
    PrintLog("용사 : 혹시, 여기에 사는 마녀세요?");
    Sleep(500);
    PrintLog("마녀(???) : 하.... 너희가 그렇게 멋대로 부르는거고... 용건은?");
    Sleep(500);
    PrintLog("용사 : 아, 사실 마녀가 멜론 밭에다가 독을 살포했다고 들어서 좀 물어(물리)보려고 왔어.");
    Sleep(500);
    PrintLog("마녀(???) : 그렇다면?");
    Sleep(500);
    PrintLog("용사 : 끔찍한 시간을 보내게 될 거야...");
    Sleep(500);
    PrintLog("마녀(???) : 아무것도 모르니까 그렇게 태평할 수가 있는거야.");
    Sleep(500);
    PrintLog("용사 : 들어갈게~~? ? 얼굴보고 얘기하자~");
    Sleep(500);
    PrintLog("성에 진입한다.");
    Sleep(500);
    PrintLog("용사 : 여긴 진짜 뭐 어떻게 돼먹은 곳이냐...");
    Sleep(5000);
}

void UIManager::PrintTrueEnd()
{
    clearALL();
    PrintLog("<TRUE엔딩> 알던 맛, 알게된 맛");
    Sleep(1500);
    PrintLog("전투를 끝낸 우리는 서로 숨을 고르고 탑 밖으로 나왔다.");
    PrintLog("탑 밖으로 나온 둘은 마을을 향해 걸으며 얘기를 나누게된다.");
    PrintLog("나는 마녀로부터 '멜론'이라는 진짜 의미를 듣게 되었다.");
    Sleep(1500);
    PrintLog("프로젝트 <MELON>");
    Sleep(500);
    PrintLog("Maximum 최대의");
    Sleep(500);
    PrintLog("Energy 에너지를");
    Sleep(500);
    PrintLog("Live 살리는");
    Sleep(500);
    PrintLog("ON switch 열쇠");
    Sleep(500);
    PrintLog("즉, 생물 자원에 대한 실험");
    Sleep(500);
    PrintLog("그것을 프로젝트 이름에 맞게 멜론이라는 과일을 매개체로 아쿠아에 '독'을 뿌리고 있던 것이다.");
    Sleep(500);
    PrintLog("용사 : (머리를 싸메며)이런.. 젠장 그런거였냐.. 내 인지하는 능력도 떨어졌던 이유가");
    Sleep(1000);
    PrintLog("마녀(???) : 그 멜론 때문이지. 원래 이 도시는 멜론이 유명한게 맞아.");
    PrintLog("            하지만 멜론을 들여오는 과정에서 어떤 마법사가 여기에 수작을 친거지.");
    PrintLog("            바로 멜론에 에너지 흡수 마법을 걸어 놓은거야.");
    PrintLog("            이 마법은 예로부터 금지된 금서목록 마지막에 적힌 금지 마법이였어.");
    PrintLog("            생명에 혼을 불어넣어 그게 매개체가 되어 생물을 타고타고 들어가 영혼을 흡수한다.");
    PrintLog("            이게 너희가 먹고 있던 멜론의 진실이야.");
    PrintLog("            내 힘만으로는 이 도시를 바꿀 힘이 없어.");
    PrintLog("            하지만 너 정도 실력이 되는 사람이 나타났다는 거에 다시 희망을 가지게 되었지");
    PrintLog("            (미소지으며)이제 너랑 도시의 본부를 쳐들어갈거야 준비됐어?");
    Sleep(3000);
    PrintLog("용사 : (칼을 정비하며)멜론의 원수다... 감히 멜론을 그런 매개체로 쓰다니 용서못해! 가자!");
    Sleep(1000);
    PrintLog("마을의 뒷면에 숨겨진 진실이 다시 움직이려고 한다.");
    Sleep(1500);
    PrintLog("과연 용사 일행은 모든 진실을 파헤칠 수 있을 것인가???");
    Sleep(2000);

}

//편하게 사용하기 위한 전역 포인터
UIManager* G_UI = nullptr; 


