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
        bool exist;  //�b��card��=1, ���A��card��=0
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

bool card::compare_card (const card *const that){ //����Ʀr�b����A this �j�� that �Ǧ^1, �Ϥ��Ǧ^0
    if(this->card_face > that->card_face){return 1;}
    else if(this->card_face==that.card_face){
        if(this->card_suit > that->card_suit){return 1;}
        else return 0;
        //���|�X�{��i�P�˼Ʀr�P��⪺�d
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
        deck[i].card_suit=clubs; //���wsuit
        deck[i].card_face=(i+1)-0+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        deck[i].exist=1; //�b�Ʋդ� (1)
    }
    for(int i=13;i<25&&i>=13;i++){
        deck[i].card_suit=diamons;//���wsuit
        deck[i].card_face=(i+1)-13+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        deck[i].exist=1; //�b�Ʋդ� (1)
    }
    for(int i=26;i<=38&&i>=26;i++){
        deck[i].card_suit=hearts;//���wsuit
        deck[i].card_face=(i+1)-26+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        deck[i].exist=1; //�b�Ʋդ� (1)
    }
    for(int i=39;i<=51&&i>=39;i++){
        deck[i].card_suit=spades;//���wsuit
        deck[i].card_face=(i+1)-39+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        deck[i].exist=1; //�b�Ʋդ� (1)
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

    void set_card(card player_card[5],card Deck[52]);  //�o�P (player ��� ,�Ʋ�)
    void judge_hand_type();
    void sort_cards();
    void print_cards();
    bool compare(const Player *const that);

private:
    card player_card[5];
    hand_type Handtype;
};

void Player::set_card(card player_card[5],card Deck[52]){ //�o�P
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
    //��w�洫�k
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

//�B�z Type �H�� dominant card
void Player::judge_hand_type(){ //�w�g�g�Lsort_cards
    int type_num[4]={0};  //tpye_num[type name]=number

    for(int i=0;i<5;i++){ //�p�� type_num
        switch(player_card[i].card_suit){
            case clubs: type_num[clubs]++; break;
            case diamonds: type_num[diamonds]++; break;
            case hearts: type_num[hearts]++; break;
            case spades: type_num[spades]++; break;

        }
    }


    //�P�_Straight flush
        //A�b�̫� or �LA
    else if((type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5)&&
            player_card[4].card_face==player_card[3].card_face + 1&&
            player_card[3].card_face==player_card[2].card_face + 1&&
            player_card[2].card_face==player_card[1].card_face + 1&&
            player_card[1].card_face==player_card[0].card_face + 1&&){
        Handtype.Type=straight_flush;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
        //A�b�̤p
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

    //�P�_Four of a kind
    else if(type_num[0]==4||type_num[1]==4||type_num[2]==4||type_num[3]==4){
        //��4�i
        if(player_card[3].card_face==player_card[4].card_face){
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card[4].card_face;
            Handtype.dominate_card.card_suit=player_card[4].card_suit;
        }
        //�e�|�i
        else {
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card[3].card_face;
            Handtype.dominate_card.card_suit=player_card[3].card_suit;
        }
    }

    //�P�_ Full house
        //�e�T�i�P�Ʀr
    else if(player_card[0].card_face==player_card[1].card_face&&
            player_card[0].card_face==player_card[2].card_face&&
            player_card[3].card_face==player_card[4].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card[2].card_face;
        Handtype.dominate_card.card_suit=player_card[2].card_suit;
    }
        //��T�i�P�Ʀr
    else if(player_card[2].card_face==player_card[3].card_face&&
            player_card[2].card_face==player_card[4].card_face&&
            player_card[0].card_face==player_card[1].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }

    //�P�_ Fulsh
    else if(type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5){
        Handtype.Type=flush;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }

    //�P�_ Stright
        //A�b�̫� or �LA
    else if(player_card[4].card_face==player_card[3].card_face + 1&&
            player_card[3].card_face==player_card[2].card_face + 1&&
            player_card[2].card_face==player_card[1].card_face + 1&&
            player_card[1].card_face==player_card[0].card_face + 1){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
        //A�b�Ĥp
    else if(player_card[4].card_face==14&&
            player_card[0].card_face==2&&
            player_card[1].card_face==3&&
            player_card[2].card_face==4&&
            player_card[3].card_face==5){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card[3].card_face;
        Handtype.dominate_card.card_suit=player_card[3].card_suit;
    }

    //�P�_ Three of a kind
    else if(type_num[0]==3||type_num[1]==3||type_num[2]==3||type_num[3]==3){//�w�P�_�LFull house�A�ȻݧP�_�T�i�ۦP���

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

    //�P�_ Two pair
        //��12 34 �P
    else if(player_card[0].card_face==player_card[1].card_face&&
            player_card[2].card_face==player_card[3].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card[3].card_face;
        Handtype.dominate_card.card_suit=player_card[3].card_suit;
    }
        //��12 45 �P
    else if(player_card[0].card_face==player_card[1].card_face&&
            player_card[3].card_face==player_card[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
        //��23 45 �P
    else if(player_card[1].card_face==player_card[2].card_face&&
            player_card[3].card_face==player_card[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card[4].card_face;
        Handtype.dominate_card.card_suit=player_card[4].card_suit;
    }
    //�P�_ One pair
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

bool Player::compare(const Player *const that){ //this �� that �j �Ǧ^1
    if(this->Handtype.Type > that->Handtype.Type){ return 1;}
    else if(this->Handtype.Type == that->Handtype.Type) {
        if(this->Handtype.dominant_card.compare_card(that->Handtype.dominant_card)){
            return 1;
        }
        else return 0;
        //���|�X�{��i�P�˼Ʀr�P��⪺�d
    }
    else return 0;
}










