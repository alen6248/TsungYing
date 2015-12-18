#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED



#endif // CARD_H_INCLUDED


#include <iostream>


using namespace std;

class Cards{
	private:
		int cards_num;


		struct Card{ //單一卡片
			enum suit{clubs,diamonds,hearts,spades} //花色
			int card_face;
			suit card_suit;
			bool exist;  //在Cards中為1
			bool compare_card(const Card* const that);
            //先比數字在比花色,this比that大傳回1
			char card_face_TurnToChar();
			void print_card();  //用來輔助 Cards::print_cards()
		}
		Card cards[cards_num];

		Cards(card_holder holder_type);
        //constructor, 用holder_type判斷為玩家或是Deck

        Card(); //初始化 player_cards 所用之無參數constructor
		~Cards(); //destructor


	public:

        void creat_deck(); //僅用於創造整份排組
        void set_player_cards(Cards* Deck); //僅用於創造player手排  //用Deck發牌給player
		int get_cards_num();
        void print_cards(); //每輸出5個換一行


	friend Player;
}



void Cards::creat_deck(){ //僅用於創造整份排組
    cards_num=52;

    for(int i=0;i<=12&&>=0;i++){
        cards[i].card_suit=clubs; //指定suit
        cards[i].card_face=(i+1)-0+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        cards[i].exist=1; //在排組中 (1)
    }
    for(int i=13;i<25&&i>=13;i++){
        cards[i].card_suit=diamons;//指定suit
        cards[i].card_face=(i+1)-13+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        cards[i].exist=1; //在排組中 (1)
    }
    for(int i=26;i<=38&&i>=26;i++){
        cards[i].card_suit=hearts;//指定suit
        cards[i].card_face=(i+1)-26+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        cards[i].exist=1; //在排組中 (1)
    }
    for(int i=39;i<=51&&i>=39;i++){
        cards[i].card_suit=spades;//指定suit
        cards[i].card_face=(i+1)-39+1; //指定數字  (A=14, 每個花色第一張為2, 第13張為A)
        cards[i].exist=1; //在排組中 (1)
    }

}

void set_player_cards(Cards* Deck){ //用Deck發牌給player
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

void Cards::Card::print_card(){ //用來輔助 Cards::print_cards() //不表現exist
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


void Cards::print_cards(){ //每輸出5個換一行
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

Cards::~Cards(){ //destructor //每回合結束時摧毀手排
    cards=NULL;
    cout<<"End of the round"<<endl;
}

bool Cards::Card::compare_card(const Card* const that){ //先比數字在比花色， this 大於 that 傳回1, 反之傳回0
    if(this->card_face > that->card_face){return 1;}
    else if(this->card_face==that.card_face){
        if(this->card_suit > that->card_suit){return 1;}
        else return 0;
        //不會出現兩張同樣數字與花色的卡
    }
    else return 0;
}








