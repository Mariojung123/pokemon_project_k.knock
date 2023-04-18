#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>


struct monster
{
    char name[20]; //이름
    char special_name[20]; //별명
    int color; //속성
    int ad; //공격력
    int hp; //체력
};

int choice=0;
int monster_ball=0;
int good_spray=0;
int pokemon_choice(int pokemon);
int hello_user(int num);
int go_adventure(int path);
int shopping(int shop);
int monster_field(int mob);
FILE *fp; //파일 포인터 선언

int main(){
    int mob_num=0; //몬스터 개체수
    srand(time(NULL)); //시간 초기화
    struct monster id[3]={{"파이리","파이리",0,rand()%(150-101)+100,rand()%(1000-501)+500},
                            {"이상해씨","이상해씨",1,rand()%(150-101)+100,rand()%(1000-501)+500},
                            {"꼬부기","꼬부기",2,rand()%(150-101)+100,rand()%(1000-501)+500}};
    
    FILE *mobfp; //몬스터 파일 구조체 선언

    mobfp=fopen("mob_list.txt","r"); //몬스터 파일 열기

    struct monster mob[10]; //몬스터 담을 구조체 배열 선언

    fscanf(mobfp,"%d",&mob_num); //몬스터 몇마리인지 출력

    // fseek(mobfp,6L,SEEK_SET); //기준점을 바꾸어보려함

    for(int i=0; i<10; i++){ //몬스터 가져오기
        fscanf(mobfp,"%s %s %d %d %d",&mob[i].name,&mob[i].special_name,&mob[i].color,&mob[i].ad,&mob[i].hp);
    } 

    fclose(mobfp); //몬스터 파일 닫기


    
    int check=hello_user(0); //시작 화면 출력

    if(check==1){ //쓰기 모드로 시작
        fp = fopen("pokemon_directory.txt","w"); 
    }
    else{ //이어서 시작
        fp = fopen("pokemon_directory.txt","a"); 
    }


    // int ran_num=rand()%10;
    // printf("%s %s %d %d %d",mob[ran_num].name,mob[ran_num].special_name,mob[ran_num].color,mob[ran_num].ad,mob[ran_num].hp);
    // puts(""); //랜덤 출력


    int selected_pokemon=pokemon_choice(0); //포켓몬 정하기 함술

return 0;
}



int hello_user(int num){ //시작창
    printf(" ====================\n");
    printf("      포켓몬스터\n");
    printf(" press enter to start\n\n");
    printf("1. 새로하기 2. 이어하기\n");
    scanf("%d",&num);
return num;
}

int pokemon_choice(int pokemon){ //포켓몬 정하기
    printf(" ====================\n");
    printf("어느 포켓몬을 고르시겠습니까?\n");
    printf("1. 파이리, 2. 이상해씨, 3. 꼬부기\n");
    scanf("%d",&pokemon);
    printf("선택한 포켓몬: %d\n", pokemon);
    
    go_adventure(0);
return pokemon;
}

int go_adventure(int path){ //상점,여행 떠나기
    printf(" ====================\n");
    printf("여행을 떠나시겠습니까?\n");
    printf("1. 네  2. 아니요  3.상점 가기");
    scanf("%d",&path);
    printf("%d 번 선택\n",path); //(4) 갈 길 선택
    if(path==1){
        monster_field(0);
    }
    else if(path==2){
        char load;
        printf("저장하시겠습니까? (Y/N) : ");
        scanf("%s",&load);
            if(load=='Y'){
                // fp=fopen("pokemon_directory.txt","a");

                fclose(fp);
            }
            else return 0;
        return 0;
    }
    else if(path==3){
        shopping(0);
    }
return path;
}

int shopping(int shop){ //상점
    static int money=10000;
    
    char perdon=3;
    int ball_price=1000;
    int spray_price=2500;
    int num=0;
    
    int how_many;
    printf(" ====================================================\n");
    printf("\t\t현재 소유 금액: %d\n",money);
    printf("  1. 몬스터볼 1000\n  2. 회복물약 2500\n\n");
    printf("어떤 아이템을 사시겠습니까? : ");
    scanf("%d",&choice); //물건 고르기

    switch (choice)
    {
        case 1:
            printf("몇개 구매하시겠습니까? : ");
            scanf("%d",&num);
            puts("");
            printf("구매하시겠습니까? Y/N : ");
            scanf("%s",&perdon);
            puts("");
            if(perdon=='Y'){
                if(money>=num*ball_price){
                    monster_ball+=num;
                    money-=num*ball_price;
                    printf("성공적으로 몬스터볼을 구매하였다.\n");
                    printf("몬스터볼: %d 개\n",monster_ball);
                    printf("스프레이: %d 개\n",good_spray);
                    printf("다시 어떤 아이템을 사시겠습니까? Y/N ");
                    scanf("%s",&perdon);
                    if(perdon=='Y') shopping(0);
                    else if(perdon=='N') go_adventure(0);
                }
                else if(money<num*ball_price){
                    printf("돈이 부족하여 살 수 없습니다.\n");
                    shopping(0);
                }
            }
            else if(perdon=='N') shopping(0);
            break;

        case 2:
            printf("몇개 구매하시겠습니까? : ");
            scanf("%d",&num);
            puts("");
            printf("구매하시겠습니까? Y/N : ");
            scanf("%s",&perdon);
            puts("");
            if(perdon=='Y'){
                if(money>=num*spray_price){
                    good_spray+=num;
                    money-=num*spray_price;
                    printf("성공적으로 스프레이를 구매하였다.\n");
                    printf("몬스터볼: %d 개\n",monster_ball);
                    printf("스프레이: %d 개\n",good_spray);
                    printf("다시 어떤 아이템을 사시겠습니까? Y/N ");
                    scanf("%s",&perdon);
                    if(perdon=='Y') shopping(0);
                    else if(perdon=='N') go_adventure(0);
                }
                else if(money<num*spray_price){
                    printf("돈이 부족하여 살 수 없습니다.\n");
                    shopping(0);
                }
            }
            else if(perdon=='N') shopping(0);
            break;

        case 0:
            go_adventure(0);
            break;
    }


return 0;
}

int monster_field(int mob){ //몬스터 맞짱
    int select=0;

    printf(" ====================\n  길을 걷는중........\n");
    sleep(2);
    printf(" ====================\n");
    printf("야생의 포켓몬이 나타났다!\n");
    printf("1. 공격 2. 도망치기 3. 가방 열기\n>> ");
    scanf("%d",&select);

    switch (select)
    {
    case 1: //공격하기
        break;

    case 2: //도망가기
        break;

    case 3: //가방 열기
        break;

    }
return mob;
}