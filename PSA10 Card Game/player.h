#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED



#endif // PLAYER_H_INCLUDED


#include "card.h"

#include <iostream>

using namespace std;

enum cards_holder{Player,Deck};

class Player{
	private:
		char* player_name;
		int money_left;
		int round; //�^�X��
		struct hand_type{
            enum type{ straight_flush=9, four_of_a_kind=8, full_house=7, flush=6,
            straight=5; three_of_a_kind=4, two_pair=3; one_pair=2, high_card=1;}

            type Type;
            card dominant_card; //Player��Cards��friend,�i��card
		}
		Hand_type Handtype;
		Cards player_cards;
		Cards* use_which_deck;

		Player(char* name,int money,Cards* Deck); //constructor
		~Player(); //destructor

	public:
		//void set_player_cards(); //�o�P��player
		//�o�P��Ƨ��Cards

		void judge_hand_type();  //��l��Handtype
		void sort_cards(); //����Ʀr�b����A�ϥ�card_compare
		bool compare(const Player* const that); //thisĹthat�Ǧ^1
        void show_hand_type();
		//void print_cards();	//����Cards
		char* get_name() const;
		int get_round(); //�Ǧ^�^�X��
		int get_money_left();

}

Player::Player(char* name,int money,Cards* Deck){ //constructor
    money_left=money;
    player_name=name;
    round=0;     //�^�X�Ƥ@�}�l�]�w��0
    cout<<"Player "<<player_name<<" enter the game"<<"   money : "
    <<get_money_left()<<endl;


    use_which_deck=Deck;
    //player_cards.set_player_cards(Cards* use_which_deck)
     //�b player_cards constructor �i���l��
    judge_hand_type(); //�b�@�}�l�N�P�_Handtype

}

Player::~Player(){ //destructor
    use_which_deck=NULL;
    player_name=NULL;
    cout<<"Player "<<player_name<<" leave the game"
    <<"   total rounds : "<<get_round()<<"   money left : "<<get_money_left()<<endl;
}

void Player::show_hand_type(){
    switch(Handtype.Type){
        case straight_flush:    cout<<"Hand type : Straight flush "<<endl; break;
        case four_of_a_kind:    cout<<"Hand type : Four of a kind "<<endl; break;
        case full_house:    cout<<"Hand type : Full house "<<endl; break;
        case flush:         cout<<"Hand type : Flush "<<endl; break;
        case straight:       cout<<"Hand type : Straight "<<endl; break;
        case three_of_a_kind:    cout<<"Hand type : Three of a kind "<<endl; break;
        case two_pair:      cout<<"Hand type : Two pair "<<endl; break;
        case one_pair:      cout<<"Hand type : One pair "<<endl; break;
        case high_card:     cout<<"Hand type : High Card "<<endl; break;
    }
    cout<<"Dominant card:"<<endl;
    Handtype.dominate_card.print_card();
    cout<<endl;

}



void Player::sort_cards(){
    //��w�洫�k
    for(int i=player_cards.cards_num;i>=2;i--){
        for(int j=0;j<i-2;j++){
            if(player_cards.cards[j].compare_card(player_cards.cards[j+1])){
                card temp; //Player ��Cards��friend,�i��private�������O�w�q

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

bool Player::compare(const Player* const that){ //thisĹthat�Ǧ^1
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
    sort_cards(); //�ݸg�Lsort_cards

    int type_num[4]={0};  //tpye_num[suit name]=number

    for(int i=0;i<cards_num;i++){ //�p�� type_num
        switch(player_card.cards[i].card_suit){
            case clubs: type_num[clubs]++; break;
            case diamonds: type_num[diamonds]++; break;
            case hearts: type_num[hearts]++; break;
            case spades: type_num[spades]++; break;

        }
    }


    //�P�_Straight flush
        //A�b�̫� or �LA
    else if((type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5)&&
            player_card.cards[4].card_face==player_card.cards[3].card_face + 1&&
            player_card.cards[3].card_face==player_card.cards[2].card_face + 1&&
            player_card.cards[2].card_face==player_car.cardsd[1].card_face + 1&&
            player_card.cards[1].card_face==player_card.cards[0].card_face + 1&&){
        Handtype.Type=straight_flush;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
        //A�b�̤p
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

    //�P�_Four of a kind
    else if(type_num[0]==4||type_num[1]==4||type_num[2]==4||type_num[3]==4){
        //��4�i
        if(player_card.cards[3].card_face==player_card.cards[4].card_face){
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card.cards[4].card_face;
            Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
        }
        //�e�|�i
        else {
            Handtype.Type=four_of_a_kind;
            Handtype.dominate_card.card_face=player_card.cards[3].card_face;
            Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
        }
    }

    //�P�_ Full house
        //�e�T�i�P�Ʀr
    else if(player_card.cards[0].card_face==player_card.cards[1].card_face&&
            player_card.cards[0].card_face==player_card.cards[2].card_face&&
            player_card.cards[3].card_face==player_card.cards[4].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card.cards[2].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[2].card_suit;
    }
        //��T�i�P�Ʀr
    else if(player_card.cards[2].card_face==player_card.cards[3].card_face&&
            player_card.cards[2].card_face==player_card.cards[4].card_face&&
            player_card.cards[0].card_face==player_card.cards[1].card_face){
        Handtype.Type=full_house;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }

    //�P�_ Fulsh
    else if(type_num[0]==5||type_num[1]==5||type_num[2]==5||type_num[3]==5){
        Handtype.Type=flush;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }

    //�P�_ Stright
        //A�b�̫� or �LA
    else if(player_card.cards[4].card_face==player_card.cards[3].card_face + 1&&
            player_card.cards[3].card_face==player_card.cards[2].card_face + 1&&
            player_card.cards[2].card_face==player_card.cards[1].card_face + 1&&
            player_card.cards[1].card_face==player_card.cards[0].card_face + 1){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
        //A�b�Ĥp
    else if(player_card.cards[4].card_face==14&&
            player_card.cards[0].card_face==2&&
            player_card.cards[1].card_face==3&&
            player_card.cards[2].card_face==4&&
            player_card.cards[3].card_face==5){
        Handtype.Type=straight;
        Handtype.dominate_card.card_face=player_card.cards[3].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
    }

    //�P�_ Three of a kind
    else if(type_num[0]==3||type_num[1]==3||type_num[2]==3||type_num[3]==3){//�w�P�_�LFull house�A�ȻݧP�_�T�i�ۦP���

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

    //�P�_ Two pair
        //��12 34 �P
    else if(player_card.cards[0].card_face==player_card.cards[1].card_face&&
            player_card.cards[2].card_face==player_card.cards[3].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card.cards[3].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[3].card_suit;
    }
        //��12 45 �P
    else if(player_card.cards[0].card_face==player_card.cards[1].card_face&&
            player_card.cards[3].card_face==player_card.cards[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
        //��23 45 �P
    else if(player_card.cards[1].card_face==player_card.cards[2].card_face&&
            player_card.cards[3].card_face==player_card.cards[4].card_face){
        Handtype.Type=two_pair;
        Handtype.dominate_card.card_face=player_card.cards[4].card_face;
        Handtype.dominate_card.card_suit=player_card.cards[4].card_suit;
    }
    //�P�_ One pair  //�w�P�_�Ltwo_pair
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
