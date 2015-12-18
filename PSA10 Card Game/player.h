#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED



#endif // PLAYER_H_INCLUDED


#include "card.h"

#include <iostream>

using namespace std;


class Player{
	private:
		char* player_name;
		int money_left;
		int round; //回合數
		struct hand_type{
            enum type{ straight_flush=9, four_of_a_kind=8, full_house=7, flush=6,
            straight=5; three_of_a_kind=4, two_pair=3; one_pair=2, high_card=1;}

            type Type;
            card dominant_card; //Player為Cards的friend,可用card
		}
		Hand_type Handtype;
		Cards player_cards;
		Cards* use_which_deck;

		Player(char* name,int money,Cards* Deck); //constructor
		~Player(); //destructor

	public:
		//void set_player_cards(); //發牌給player
		//發牌函數改到Cards

		void judge_hand_type();  //初始化Handtype
		void sort_cards(); //先比數字在比花色，使用card_compare
		bool compare(const Player* const that); //this贏that傳回1

		//void print_cards();	//移到Cards
		char* get_name() const;
		int get_round(); //傳回回合數
		int get_money_left();

}

Player::Player(char* name,int money,Cards* Deck){ //constructor
    use_which_deck=Deck;
    player_name=name;
    player_cards.set_player_cards(Cards* use_which_deck)
    money_left=money;
    round=0; //回合數一開始設定為0
    judge_hand_type(); //在一開始就判斷Handtype
    cout<<"Player "<<player_name<<" enter the game"<<"   money : "
    <<get_money_left()<<endl;
}

Player::~Player(){ //destructor
    use_which_deck=NULL;
    player_name=NULL;
    cout<<"Player "<<player_name<<" leave the game"
    <<"   total rounds : "<<get_round()<<"   money left : "<<get_money_left()<<endl;
}

void Player::sort_cards(){
    //氣泡交換法
    for(int i=player_cards.cards_num;i>=2;i--){
        for(int j=0;j<i-2;j++){
            if(player_cards.cards[j].compare_card(player_cards.cards[j+1])){
                card temp; //Player 為Cards的friend,可用private成員型別定義

                temp.card_suit=player_cards.cards[j+1].card_suit;
                tmep.card_face=player_cards.cards[j+1].card_face;

                player_cards.cards[j+1].card_suit=player_cards.cards[j].card_suit;
                player_cards.cards[j+1].card_face=player_cards.cards[j].card_face;

                player_cards.cards[j].card_suit=temp.card_suit;
                player_cards.cards[j].card_face=temp.card_face;
            }
        }
    }
}

bool Player::compare(const Player* const that){ //this贏that傳回1
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


int Player::get_round(){
    return round;
}

char* Player::get_name() const {
    return *player_name;
}

int Player::get_money_left(){
    return money_left;
}

void Player::judge_hand_type(){
    sort_cards(); //需經過sort_cards

    int type_num[4]={0};  //tpye_num[suit name]=number

    for(int i=0;i<cards_num;i++){ //計算 type_num
        switch(player_card.cards[i].card_suit){
            case clubs: type_num[clubs]++; break;
            case diamonds: type_num[diamonds]++; break;
            case hearts: type_num[hearts]++; break;
            case spades: type_num[spades]++; break;

        }
    }


    //判斷Straight flush
        //A在最後 or 無A
    else if((type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5)&&
            player_card.cards[4].card_face==player_card.cards[3].card_face + 1&&
            player_card.cards[3].card_face==player_card.cards[2].card_face + 1&&
            player_card.cards[2].card_face==player_car.cardsd[1].card_face + 1&&
            player_card.cards[1].card_face==player_card.cards[0].card_face + 1&&){
        Handtype.Type=straight_flush;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
        //A在最小
    else if((type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5)&&
            player_card.cards[4].card_face==14&&
            player_card.cards[0].card_face==2&&
            player_card.cards[1].card_face==3&&
            player_card.cards[2].card_face==4&&
            player_card.cards[3].card_face==5){
        Handtype.Type=straight_flush;
        Handtype.dominate_card.card_face=player_card.cards[3].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
    }

    //判斷Four of a kind
    else if(type_num[0]==4||type_num[1]==4||type_num[2]==4||type_num[3]==4){
        //後4張
        if(player_card.cards[3].card_face==player_card.cards[4].card_face){
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card.cards[4].card_face;
            Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
        }
        //前四張
        else {
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card.cards[3].card_face;
            Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
        }
    }

    //判斷 Full house
        //前三張同數字
    else if(player_card.cards[0].card_face==player_card.cards[1].card_face&&
            player_card.cards[0].card_face==player_card.cards[2].card_face&&
            player_card.cards[3].card_face==player_card.cards[4].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card.cards[2].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[2].card_suit;
    }
        //後三張同數字
    else if(player_card.cards[2].card_face==player_card.cards[3].card_face&&
            player_card.cards[2].card_face==player_card.cards[4].card_face&&
            player_card.cards[0].card_face==player_card.cards[1].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }

    //判斷 Fulsh
    else if(type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5){
        Handtype.Type=flush;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }

    //判斷 Stright
        //A在最後 or 無A
    else if(player_card.cards[4].card_face==player_card.cards[3].card_face + 1&&
            player_card.cards[3].card_face==player_card.cards[2].card_face + 1&&
            player_card.cards[2].card_face==player_card.cards[1].card_face + 1&&
            player_card.cards[1].card_face==player_card.cards[0].card_face + 1){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
        //A在第小
    else if(player_card.cards[4].card_face==14&&
            player_card.cards[0].card_face==2&&
            player_card.cards[1].card_face==3&&
            player_card.cards[2].card_face==4&&
            player_card.cards[3].card_face==5){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card.cards[3].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
    }

    //判斷 Three of a kind
    else if(type_num[0]==3||type_num[1]==3||type_num[2]==3||type_num[3]==3){//已判斷過Full house，僅需判斷三張相同花色

        if(player_card.cards[0].card_face==player_card.cards[2].card_face){ //123
            Handtype.Type=three_of_a_kind;
            Handtype.dominate_card.card_face=player_card.cards[2].card_face;
            Handtype.dominate_card.card_suit=player_card.cards[2].card_suit;
        }
        else if(player_card.cards[1].card_face==player_card.cards[3].card_face){ //234
            Handtype.Type=three_of_a_kind;
            Handtype.dominate_card.card_face=player_card.cards[3].card_face;
            Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
        }
        else if(player_card.cards[2].card_face==player_card.cards[4].card_face){ //345
            Handtype.Type=three_of_a_kind;
            Handtype.dominate_card.card_face=player_card.cards[4].card_face;
            Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
        }
    }

    //判斷 Two pair
        //第12 34 同
    else if(player_card.cards[0].card_face==player_card.cards[1].card_face&&
            player_card.cards[2].card_face==player_card.cards[3].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card.cards[3].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
    }
        //第12 45 同
    else if(player_card.cards[0].card_face==player_card.cards[1].card_face&&
            player_card.cards[3].card_face==player_card.cards[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
        //第23 45 同
    else if(player_card.cards[1].card_face==player_card.cards[2].card_face&&
            player_card.cards[3].card_face==player_card.cards[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
    //判斷 One pair  //已判斷過two_pair
        //12
    else if(player_card.cards[0].card_face==player_card.cards[1].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card.cards[1].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[1].card_suit;
    }
        //23
    else if(player_card.cards[1].card_face==player_card.cards[2].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card.cards[2].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[2].card_suit;
    }
        //34
    else if(player_card.cards[2].card_face==player_card.cards[3].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card.cards[3].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
    }
        //45
    else if(player_card.cards[3].card_face==player_card.cards[4].card_face){
        Handtype.Type=one_pair;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
    // High card
    else{
        Handtype.Type=high_card;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }

}
