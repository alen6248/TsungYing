#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED



#endif // CARD_H_INCLUDED

#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

// card
class card{
    friend Player;

    public:
        char TernToChar_card_face(int card_face);
        void print();
        bool compare_card(const card *const that);
        void creat_deck(card deck[52]);
        enum suit{clubs,diamonds,hearts,spades};

    private:
        suit card_suit;
        int card_face;
        bool exist;  //在該card中=1, 不再該card中=0
};

char card::TernToChar_card_face(int card_face){
    switch(card_face){
        case 14: return 'A'; break;
        case 13: return 'K'; break;
        case 12: return 'Q'; break;
        case 11: return 'J'; break;
        default: return (char)(card_face+48);
    }
}

bool card::compare_card (const card *const that){ //先比數字在比花色， this 大於 that 傳回1, 反之傳回0
    if(this->card_face > that->card_face){return 1;}
    else if(this->card_face==that.card_face){
        if(this->card_suit > that->card_suit){return 1;}
        else return 0;
        //不會出現兩張同樣數字與花色的卡
    }
    else return 0;
}

void card::print(){
    switch(card_suit){
        case clubs:
            cout<<setw(10)<<"clubs "<<TernToChar_card_face(card_face)<<' '; break;
        case diamonds:
            cout<<setw(10)<<"diamonds "<<TernToChar_card_face(card_face)<<' '; break;
        case hearts:
            cout<<setw(10)<<"hearts "<<TernToChar_card_face(card_face)<<' '; break;
        case spades:
            cout<<setw(10)<<"spades "<<TernToChar_card_face(card_face)<<' '; break;
    }
}

void card::creat_deck(card deck[52]){
    for(int i=0;i<=12&&>=0;i++){
        deck[i].card_suit=clubs; //指定suit
        deck[i].card_face=(i+1)-0+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        deck[i].exist=1; //在排組中 (1)
    }
    for(int i=13;i<25&&i>=13;i++){
        deck[i].card_suit=diamons;//指定suit
        deck[i].card_face=(i+1)-13+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        deck[i].exist=1; //在排組中 (1)
    }
    for(int i=26;i<=38&&i>=26;i++){
        deck[i].card_suit=hearts;//指定suit
        deck[i].card_face=(i+1)-26+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        deck[i].exist=1; //在排組中 (1)
    }
    for(int i=39;i<=51&&i>=39;i++){
        deck[i].card_suit=spades;//指定suit
        deck[i].card_face=(i+1)-39+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        deck[i].exist=1; //在排組中 (1)
    }

}













//player
class Player{

public:
    struct hand_type{
        enum type{
            straight_flush=9, four_of_a_kind=8, full_house=7, flush=6, straight=5; three_of_a_kind=4, two_pair=3; one_pair=2, high_card=1;
        }Type;
        card dominate_card;
    };

    void set_card(card player_card[5],card Deck[52]);  //發牌 (player 手排 ,排組)
    void judge_hand_type();
    void sort_cards();
    void print_cards();
    bool compare(const Player *const that);

private:
    card player_card[5];
    hand_type Handtype;
};

void Player::set_card(card player_card[5],card Deck[52]){ //發牌
    srand(time()); //set rand seed

    for(int i=0;i<5;i++){
        bool success_flag=0;
        while(success_flag==0){
            int card_order=rand()%52;
            if(Deck[card_order].exist==0){success_flag=0;}
            else if(Deck[card_order].exist==1){
                player_card[i].card_suit=Deck[card_order].card_suit;
                player_card[i].card_face=Deck[card_order].card_face;
                player_card[i].exist=1;
                Deck[card_order].exist=0;
                success_flag=1;
            }
        }
    }
}


void Player::sort_cards(){
    //氣泡交換法
    for(int i=5;i>=2;i--){
        for(int j=0;j<i-2;j++){
            if(player_card[j].compare_card(player_card[j+1])){
                card temp;
                temp.card_suit=player_card[j+1].card_suit;
                tmep.card_face=player_card[j+1].card_face;

                player_card[j+1].card_suit=player_card[j].card_suit;
                player_card[j+1].card_face=player_card[j].card_face;

                player_card[j].card_suit=temp.card_suit;
                player_card[j].card_face=temp.card_face;
            }
        }
    }
}

//處理 Type 以及 dominant card
void Player::judge_hand_type(){ //已經經過sort_cards
    int type_num[4]={0};  //tpye_num[type name]=number

    for(int i=0;i<5;i++){ //計算 type_num
        switch(player_card[i].card_suit){
            case clubs: type_num[clubs]++; break;
            case diamonds: type_num[diamonds]++; break;
            case hearts: type_num[hearts]++; break;
            case spades: type_num[spades]++; break;

        }
    }


    //判斷Straight flush
        //A在最後 or 無A
    else if((type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5)&&
            player_card[4].card_face==player_card[3].card_face + 1&&
            player_card[3].card_face==player_card[2].card_face + 1&&
            player_card[2].card_face==player_card[1].card_face + 1&&
            player_card[1].card_face==player_card[0].card_face + 1&&){
        Handtype.Type=straight_flush;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
        //A在最小
    else if((type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5)&&
            player_card[4].card_face==14&&
            player_card[0].card_face==2&&
            player_card[1].card_face==3&&
            player_card[2].card_face==4&&
            player_card[3].card_face==5){
        Handtype.Type=straight_flush;
        Handtype.dominate_card.card_face=player_card[3].card_face;
        Handtype.dominate_card.card_suit=player_card[3].card_suit;
    }

    //判斷Four of a kind
    else if(type_num[0]==4||type_num[1]==4||type_num[2]==4||type_num[3]==4){
        //後4張
        if(player_card[3].card_face==player_card[4].card_face){
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card[4].card_face;
            Handtype.dominate_card.card_suit=player_card[4].card_suit;
        }
        //前四張
        else {
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card[3].card_face;
            Handtype.dominate_card.card_suit=player_card[3].card_suit;
        }
    }

    //判斷 Full house
        //前三張同數字
    else if(player_card[0].card_face==player_card[1].card_face&&
            player_card[0].card_face==player_card[2].card_face&&
            player_card[3].card_face==player_card[4].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card[2].card_face;
        Handtype.dominate_card.card_suit=player_card[2].card_suit;
    }
        //後三張同數字
    else if(player_card[2].card_face==player_card[3].card_face&&
            player_card[2].card_face==player_card[4].card_face&&
            player_card[0].card_face==player_card[1].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }

    //判斷 Fulsh
    else if(type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5){
        Handtype.Type=flush;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }

    //判斷 Stright
        //A在最後 or 無A
    else if(player_card[4].card_face==player_card[3].card_face + 1&&
            player_card[3].card_face==player_card[2].card_face + 1&&
            player_card[2].card_face==player_card[1].card_face + 1&&
            player_card[1].card_face==player_card[0].card_face + 1){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
        //A在第小
    else if(player_card[4].card_face==14&&
            player_card[0].card_face==2&&
            player_card[1].card_face==3&&
            player_card[2].card_face==4&&
            player_card[3].card_face==5){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card[3].card_face;
        Handtype.dominate_card.card_suit=player_card[3].card_suit;
    }

    //判斷 Three of a kind
    else if(type_num[0]==3||type_num[1]==3||type_num[2]==3||type_num[3]==3){//已判斷過Full house，僅需判斷三張相同花色

        if(player_card[0].card_face==player_card[2].card_face){ //123
            Handtype.Type=three_of_a_kind;
            Handtype.dominate_card.card_face=player_card[2].card_face;
            Handtype.dominate_card.card_suit=player_card[2].card_suit;
        }
        else if(player_card[1].card_face==player_card[3].card_face){ //234
            Handtype.Type=three_of_a_kind;
            Handtype.dominate_card.card_face=player_card[3].card_face;
            Handtype.dominate_card.card_suit=player_card[3].card_suit;
        }
        else if(player_card[2].card_face==player_card[4].card_face){ //345
            Handtype.Type=three_of_a_kind;
            Handtype.dominate_card.card_face=player_card[4].card_face;
            Handtype.dominate_card.card_suit=player_card[4].card_suit;
        }
    }

    //判斷 Two pair
        //第12 34 同
    else if(player_card[0].card_face==player_card[1].card_face&&
            player_card[2].card_face==player_card[3].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card[3].card_face;
        Handtype.dominate_card.card_suit=player_card[3].card_suit;
    }
        //第12 45 同
    else if(player_card[0].card_face==player_card[1].card_face&&
            player_card[3].card_face==player_card[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
        //第23 45 同
    else if(player_card[1].card_face==player_card[2].card_face&&
            player_card[3].card_face==player_card[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
    //判斷 One pair
        //12
    else if(player_card[0].card_face==player_card[1].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card[1].card_face;
        Handtype.dominate_card.card_suit=player_card[1].card_suit;
    }
        //23
    else if(player_card[1].card_face==player_card[2].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card[2].card_face;
        Handtype.dominate_card.card_suit=player_card[2].card_suit;
    }
        //34
    else if(player_card[2].card_face==player_card[3].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card[3].card_face;
        Handtype.dominate_card.card_suit=player_card[3].card_suit;
    }
        //45
    else if(player_card[3].card_face==player_card[4].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
    // High card
    else{
        Handtype.Type=high_card;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
}

void Player::print_cards(){
    for(int i=0;i<5;i++){
        player_card[i].print();
    }
}

bool Player::compare(const Player *const that){ //this 比 that 大 傳回1
    if(this->Handtype.Type > that->Handtype.Type){ return 1;}
    else if(this->Handtype.Type == that->Handtype.Type) {
        if(this->Handtype.dominant_card.compare_card(that->Handtype.dominant_card)){
            return 1;
        }
        else return 0;
        //不會出現兩張同樣數字與花色的卡
    }
    else return 0;
}










