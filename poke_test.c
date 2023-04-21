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
int my_poke_num=0; //소환할 포켓몬 번호
int full_hp=0;
int money=10000;
int choice=0;
int monster_ball=0;
int good_spray=0;
int poke_num=0;
int p_num=0;
int pokemon_choice(int pokemon);
int hello_user(int num);
int go_adventure(int path);
int shopping(int shop);
int monster_field(int monster);
int damage(int my_num, int num);
struct monster mob[10]; //몬스터 담을 구조체 배열 선언
struct monster my_poke[6]; //내 포켓몬 구조체 배열 선언
FILE *fp; //파일 포인터 선언

int main(){
    int mob_num=0; //몬스터 개체수
    srand(time(NULL)); //시간 초기화


    struct monster id[3]={{"파이리","파이리",0,rand()%(150-101)+100,rand()%(1000-501)+500},
                            {"이상해씨","이상해씨",1,rand()%(150-101)+100,rand()%(1000-501)+500},
                            {"꼬부기","꼬부기",2,rand()%(150-101)+100,rand()%(1000-501)+500}};
    
    FILE *mobfp; //몬스터 파일 구조체 선언

    mobfp=fopen("mob_list.txt","r"); //몬스터 파일 열기
    if(mobfp==NULL){
        printf("파일 열기 실패");
        return 0;
    }

    fscanf(mobfp,"%d",&mob_num); //몬스터 몇마리인지 출력

    // fseek(mobfp,6L,SEEK_SET); //기준점을 바꾸어보려함

    for(int i=0; i<mob_num; i++){ //몬스터 가져오기
        fscanf(mobfp,"%s %s %d %d %d",&mob[i].name,&mob[i].special_name,&mob[i].color,&mob[i].ad,&mob[i].hp);
    }
    for(int i=0;i<mob_num; i++){
        printf("%s %s %d %d %d\n",mob[i].name,mob[i].special_name,mob[i].color,mob[i].ad,mob[i].hp);
    }

    fclose(mobfp); //몬스터 파일 닫기

    
    int check=hello_user(0); //시작 화면 출력
    //함수 들어갈 때 함수 안 함수는 메모리를 많이 잡으므로 반복문 형식으로 다시 돌아오게 만들기
    if(check==1){ //쓰기 모드로 시작 
        fp = fopen("pokemon_directory.txt","w"); 
        p_num=pokemon_choice(0)-1; //포켓몬 정하기 함술
        my_poke[0]=id[p_num];
        poke_num++;
        go_adventure(0);
    }
    else{ //이어서 시작
        fp = fopen("pokemon_directory.txt","r");
            if(fp==NULL){
                printf("파일 열기 실패");
                return 0;
            }
        fscanf(fp,"%d %d %d %d",&monster_ball,&good_spray,&poke_num,&money); //아이템 부르기
        for(int i=0; i<poke_num; i++){ //내 포켓몬 불러오기
            fscanf(fp,"%s %s %d %d %d",&my_poke[i].name,&my_poke[i].special_name,&my_poke[i].color,&my_poke[i].ad,&my_poke[i].hp);
        }
        fclose(fp);
        go_adventure(0);

    }



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
                fp=fopen("pokemon_directory.txt","w");
                fprintf(fp,"%d %d %d %d\n",monster_ball,good_spray,poke_num,money);
                for(int i=0; i<poke_num; i++){
                    fprintf(fp,"%s %s %d %d %d \n",my_poke[i].name,my_poke[i].special_name,my_poke[i].color,my_poke[i].ad,my_poke[i].hp);
                }
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

int monster_field(int monster){ //몬스터 맞짱

    int select=0;
    float hp_per=0;

    printf(" ====================\n  길을 걷는중........\n");
    sleep(2);
    printf(" ====================\n");
    printf("야생의 포켓몬이 나타났다!\n");
    
    
    int ran_num=rand()%10;
    printf("%s %s %d %d %d",mob[ran_num].name ,mob[ran_num].special_name,mob[ran_num].color,mob[ran_num].ad,mob[ran_num].hp);
    puts(""); //랜덤 출력
    full_hp = mob[ran_num].hp; // 피통 초기값

    while(select==2 || mob[ran_num].hp>0){
        if(mob[ran_num].hp>0){
            printf("1. 공격 2. 도망치기 3. 가방 열기\n>> ");
            scanf("%d",&select);
        
            switch (select){
            case 1: //공격하기
                printf("hp: %d \n",mob[ran_num].hp);
                
                if(my_poke[my_poke_num].color==0){ //내가 불속성일 떄
                    if(mob[ran_num].color==0){
                        mob[ran_num].hp-=my_poke[my_poke_num].ad;
                        printf("hp: %d \n",mob[ran_num].hp);
                        printf("효과는 의미없다.\n");
                    }
                    else if(mob[ran_num].color==1){
                        mob[ran_num].hp-=1.5*my_poke[my_poke_num].ad;
                        printf("hp: %d \n",mob[ran_num].hp);
                        printf("효과는 굉장했다.\n");
                    }
                    else if(mob[ran_num].color==2){
                        mob[ran_num].hp-=0.5*my_poke[my_poke_num].ad;
                        printf("hp: %d \n",mob[ran_num].hp);
                        printf("효과가 별로인 듯 하다.\n");
                    }
                }

                else if(my_poke[my_poke_num].color==1){ //내가 풀속성일 떄
                        if(mob[ran_num].color==0){
                            mob[ran_num].hp-=0.5*my_poke[my_poke_num].ad;
                            printf("hp: %d \n",mob[ran_num].hp);
                            printf("효과가 별로인 듯 하다.\n");
                        }
                        else if(mob[ran_num].color==1){
                            mob[ran_num].hp-=my_poke[my_poke_num].ad;
                            printf("hp: %d \n",mob[ran_num].hp);
                            printf("효과는 의미없다.\n");
                        }
                        else if(mob[ran_num].color==2){
                            mob[ran_num].hp-=1.5*my_poke[my_poke_num].ad;
                            printf("hp: %d \n",mob[ran_num].hp);
                            printf("효과는 굉장했다.\n");
                        }
                }

                else if(my_poke[my_poke_num].color==2){ //내가 물속성일 떄
                        if(mob[ran_num].color==0){
                            mob[ran_num].hp-=1.5*my_poke[my_poke_num].ad;
                            printf("hp: %d \n",mob[ran_num].hp);
                            printf("효과는 굉장했다.\n");
                        }
                        else if(mob[ran_num].color==1){
                            mob[ran_num].hp-=0.5*my_poke[my_poke_num].ad;
                            printf("hp: %d \n",mob[ran_num].hp);
                            printf("효과가 별로인 듯 하다.\n");
                        }
                        else if(mob[ran_num].color==2){
                            mob[ran_num].hp-=my_poke[my_poke_num].hp;
                            printf("hp: %d \n",mob[ran_num].hp);
                            printf("효과는 의미없다.\n");
                        }
                }
                
                damage(my_poke_num,ran_num); //상대가 나에게 공격
            
                break;
                
            case 2: //도망가기
                printf("%d\n",full_hp);
                printf("%d\n",mob[ran_num].hp);
                hp_per = (float)(mob[ran_num].hp)/full_hp; //체력 퍼센트까지 했으니 그 다음에 도망가는 부분 완성해야함

                printf("%f\n",hp_per*100);
                go_adventure(0);
                return 0;
                break;

            case 3: //가방 열기
            
                break;
            }
        }
    }

    if(mob[ran_num].hp<0){
        printf("애가 죽어버렸다...\n");
        go_adventure(0);
    }
    else if(mob[ran_num].hp==0){
        printf("앗! 포켓몬이 런쳤다...\n");
        go_adventure(0);
    }
    

return monster;
}


int damage(int my_num, int num){ //상대 공격 처리
    int dam=0;
    dam=mob[num].ad;

    if(mob[num].color==0){ //상대가 불속성일 떄
        if(my_poke[my_num].color==0){
            my_poke[my_num].hp-=mob[num].ad;
            printf("나의 hp: %d \n",my_poke[my_num].hp);
            printf("효과는 의미없다.\n");
        }
        else if(my_poke[my_num].color==1){
            my_poke[my_num].hp-=1.5*mob[num].ad;
            printf("나의 hp: %d \n",my_poke[my_num].hp);
            printf("상대는 강력하다.\n");
        }
        else if(my_poke[my_num].color==2){
            my_poke[my_num].hp-=0.5*mob[num].ad;
            printf("나의 hp: %d \n",my_poke[my_num].hp);
            printf("상대는 약하다.\n");
        }
    }

    else if(mob[num].color==1){ //상대가 풀속성일 떄
            if(my_poke[my_num].color==0){
                my_poke[my_num].hp-=0.5*mob[num].ad;
                printf("나의 hp: %d \n",my_poke[my_num].hp);
                printf("상대는 약하다.\n");
            }
            else if(my_poke[my_num].color==1){
                my_poke[my_num].hp-=mob[num].ad;
                printf("나의 hp: %d \n",my_poke[my_num].hp);
                printf("효과는 의미없다.\n");
            }
            else if(my_poke[my_num].color==2){
                my_poke[my_num].hp-=1.5*mob[num].ad;
                printf("나의 hp: %d \n",my_poke[my_num].hp);
                printf("상대는 강력하다.\n");
            }
    }

    else if(mob[num].color==2){ //상대가 물속성일 떄
            if(my_poke[my_num].color==0){
                my_poke[my_num].hp-=1.5*mob[num].ad;
                printf("나의 hp: %d \n",my_poke[my_num].hp);
                printf("상대는 강력하다.\n");
            }
            else if(my_poke[my_num].color==1){
                my_poke[my_num].hp-=0.5*mob[num].ad;
                printf("나의 hp: %d \n",my_poke[my_num].hp);
                printf("상대는 약하다.\n");
            }
            else if(my_poke[my_num].color==2){
                my_poke[my_num].hp-=mob[num].hp;
                printf("나의 hp: %d \n",my_poke[my_num].hp);
                printf("효과는 의미없다.\n");
            }
    }
    
return my_num;
}

// // int another_poke(int num){

// }