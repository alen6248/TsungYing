#include <iostream>
#include "card.h"

using namespace std;

int main()
{
//Deck
    card Deck[52];
    card::creat_deck(Deck[52]);




//Player 1
    cout<<"Player 1:"<<endl;
    Player player1;
    player1.set_card();
    cout<<"Cards:"<<endl;
    player1.print_cards();
    player1.sort_cards();
    cout<<"Sorted Cards:"<<endl;
    player1.print_cards();
    player1.judge_hand_type();
    switch(player1.Handtype.Type){
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
    player1.Handtype.dominate_card.print();
    cout<<endl;

//Player 2
    cout<<"Player 2:"<<endl;
    Player player2;
    player2.set_card();
    cout<<"Cards:"<<endl;
    player2.print_cards();
    player2.sort_cards();
    cout<<"Sorted Cards:"<<endl;
    player2.print_cards();
    player2.judge_hand_type();
    switch(player2.Handtype.Type){
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
    player2.Handtype.dominate_card.print();
    cout<<endl;


//Judge the winner
    if(player1.compare(player2)){
        cout<<"Winner is player 1!"<<endl;
    }
    else{
        cout<<"Winner is player 2!"<<endl;
    }
    return 0;
}
