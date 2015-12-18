#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED



#endif // CARD_H_INCLUDED


#include <iostream>


using namespace std;

class Cards{
	private:
		int cards_num;


		struct Card{ //��@�d��
			enum suit{clubs,diamonds,hearts,spades} //���
			int card_face;
			suit card_suit;
			bool exist;  //�bCards����1
			bool compare_card(const Card* const that);
            //����Ʀr�b����,this��that�j�Ǧ^1
			char card_face_TurnToChar();
			void print_card();  //�Ψӻ��U Cards::print_cards()
		}
		Card cards[cards_num];

		Cards(card_holder holder_type);
        //constructor, ��holder_type�P�_�����a�άODeck

        Card(); //��l�� player_cards �ҥΤ��L�Ѽ�constructor
		~Cards(); //destructor


	public:

        void creat_deck(); //�ȥΩ�гy����Ʋ�
        void set_player_cards(Cards* Deck); //�ȥΩ�гyplayer���  //��Deck�o�P��player
		int get_cards_num();
        void print_cards(); //�C��X5�Ӵ��@��


	friend Player;
}



void Cards::creat_deck(){ //�ȥΩ�гy����Ʋ�
    cards_num=52;

    for(int i=0;i<=12&&>=0;i++){
        cards[i].card_suit=clubs; //���wsuit
        cards[i].card_face=(i+1)-0+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        cards[i].exist=1; //�b�Ʋդ� (1)
    }
    for(int i=13;i<25&&i>=13;i++){
        cards[i].card_suit=diamons;//���wsuit
        cards[i].card_face=(i+1)-13+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        cards[i].exist=1; //�b�Ʋդ� (1)
    }
    for(int i=26;i<=38&&i>=26;i++){
        cards[i].card_suit=hearts;//���wsuit
        cards[i].card_face=(i+1)-26+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        cards[i].exist=1; //�b�Ʋդ� (1)
    }
    for(int i=39;i<=51&&i>=39;i++){
        cards[i].card_suit=spades;//���wsuit
        cards[i].card_face=(i+1)-39+1; //���w�Ʀr  (A=14, �C�Ӫ��Ĥ@�i��2, ��13�i��A)
        cards[i].exist=1; //�b�Ʋդ� (1)
    }

}

void set_player_cards(Cards* Deck){ //��Deck�o�P��player
    srand(time()); //set rand seed

    for(int i=0;i<cards_num;i++){
        bool success_flag=0;
        while(success_flag==0){
            int card_order=rand()%52;
            if(Deck.cards[card_order].exist==0){success_flag=0;}
            else if(Deck.cards[card_order].exist==1){
                cards[i].card_suit=Deck.cards[card_order].card_suit;
                cards[i].card_face=Deck.cards[card_order].card_face;
                cards[i].exist=1;
                Deck.cards[card_order].exist=0;
                success_flag=1;
            }
        }
    }
}

char Cards::Card::card_face_TurnToChar(){
    switch(card_face){
        case 14: return 'A'; break;
        case 13: return 'K'; break;
        case 12: return 'Q'; break;
        case 11: return 'J'; break;
        default: return (char)(card_face+48);
    }
}

void Cards::Card::print_card(){ //�Ψӻ��U Cards::print_cards() //����{exist
    switch(card_suit){
        case clubs:
            cout<<setw(10)<<"clubs "<<card_face_TurnToChar(card_face)<<' '; break;
        case diamonds:
            cout<<setw(10)<<"diamonds "<<card_face_TurnToChar(card_face)<<' '; break;
        case hearts:
            cout<<setw(10)<<"hearts "<<card_face_TurnToChar(card_face)<<' '; break;
        case spades:
            cout<<setw(10)<<"spades "<<card_face_TurnToChar(card_face)<<' '; break;
    }

}


void Cards::print_cards(){ //�C��X5�Ӵ��@��
    for(int i=1;i<=card_num;i++){
        cards[i].print_card();
        if(i%5==0){cout<<endl;}
    }
}

int Cards::get_cards_num(){
    return cards_num;
}

Cards::Cards(card_holder holder_type){ //constructor
    if(holder_type==Deck){  //Deck
        cards_num=52;
        creat_deck();
    }
    else if(holder_type==Player){ //Player
        cards_num=5;
        set_player_cards();
    }
}

Cards::Cards(){
    cards_num=5;
    set_player_cards();
}

Cards::~Cards(){ //destructor //�C�^�X�����ɺR�����
    cards=NULL;
    cout<<"End of the round"<<endl;
}

bool Cards::Card::compare_card(const Card* const that){ //����Ʀr�b����A this �j�� that �Ǧ^1, �Ϥ��Ǧ^0
    if(this->card_face > that->card_face){return 1;}
    else if(this->card_face==that.card_face){
        if(this->card_suit > that->card_suit){return 1;}
        else return 0;
        //���|�X�{��i�P�˼Ʀr�P��⪺�d
    }
    else return 0;
}








