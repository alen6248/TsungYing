#include <iostream>
#include "card.h"
#include "player.h"
#include "game_windows.h"

enum cards_holder{Player,Deck};

using namespace std;

int main()
{
    Cards* deck;
    deck=new Cards(52,Deck);

    Player player1("Tsung",1000,deck);
    Player player2("Ying",1000,deck);

    cout<<"Player 1 : "<<player1.get_name()<<endl;
    cout<<"Cards : "<<'\n'<<player1.player_cards.print_cards();
    cout<<"Handtype : ";  player1.show_hand_type();
    cout<<"Dominant Card : "; player1.Handtype.dominant_card.print_card();
    cout<<endl;


    cout<<"Player 2 : "<<player2.get_name()<<endl;
    cout<<"Cards : "<<'\n'<<player2.player_cards.print_cards();
    cout<<"Handtype : ";  player2.show_hand_type();
    cout<<"Dominant Card : "; player2.Handtype.dominant_card.print_card();
    cout<<endl;


    cout<<"Winner : ";

    if(player1.compare(&player2)){
        cout<<"player 1 , "<<player1.get_name()<<endl;
    }
    else{
        cout<<"player 2 , "<<player2.get_name()<<endl;
    }


    return 0;
}
