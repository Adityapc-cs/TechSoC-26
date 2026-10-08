#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

class Bender
{
    public:
    string name;
    string element;
    int hp;
    int initialHP;
    int attack;
    int defence;
    int speed;
    vector<pair<string,int>>moves{4};
   
    Bender(const string& name , const string& element , int hp , int attack , int defence , int speed , const vector<pair<string,int>>& moves)
    {
        this->name = name;
        this->element = element;
        this->hp = hp;
        initialHP = this->hp;
        this->attack = attack;
        this->defence = defence;
        this->speed = speed;
        this->moves = moves;
        cout<<"\nBender "<<name<<" successfully created.\n";
    }
   
static Bender userInput()
    {
        string Uname, Uelement;
        int Uhp,Uattack,Udefence,Uspeed;
        vector<pair<string,int>> Umoves(4);
       
        cout<<"Enter Bender Details: \n";
        cout<<"Name: ";
        getline(cin>>ws , Uname);
        
        cout<<"\n--- Element Guide ---\n";
        cout<<"Choose from: Water, Fire, Air, or Earth.\n";
        cout<<"Rule: Water beats Fire, Fire beats Air, Air beats Earth, and Earth beats Water.\n";
        cout<<"Strong hits do double damage! Weak hits do half.\n\n";
        cout<<"Element: ";
        getline(cin>>ws , Uelement);
       
        cout<<"\n--- Stats Guide ---\n";
        cout<<"For a fair game, HP should ideally be between 100 - 200.\n";
        cout<<"Keep Attack, Defence, and Speed around 50-75.\n";
        cout<<"Enter HP , Attack , Defence and Speed (separated by spaces): \n";
        cin>>Uhp>>Uattack>>Udefence>>Uspeed;
       
        cout<<"\nEnter moves attributes (name,power) one by one:\n";
        for(int i = 0 ; i < 4 ; i++)
        {
            cout<<"\nMove "<<i+1<<"\n";
            cout<<"Name and Power :\n";
            getline(cin>>ws , Umoves[i].first);
            cin>>Umoves[i].second;
        }
       
        return Bender( Uname , Uelement , Uhp , Uattack , Udefence , Uspeed , Umoves );
       
    }
    void displayStats()
    {
        cout<<"\n";
        cout<<name<<" ("<<element<<") - HP: "<<hp<<"/"<<initialHP<<", Attack: "<<attack<<", Defence: "<<defence<<", Speed: "<<speed<<"\n";
        for(int i = 0 ; i<4 ; i++ )
        {
            cout<<"Moves: "<<moves[i].first<<" ("<<moves[i].second<<")  ";
        }
        cout<<"\n";
    }
   
   
};

class duel
{
    public:
   
    Bender b1;
    Bender b2;

    int critical_counter = 0;
    int supereffective_counter = 0;
    int turns = 1;
    bool Auto;
   
    duel(Bender B1, Bender B2) : b1(B1), b2(B2)
    {
    }

    void GameMode()
    {
       int choice;
            cout<<"Enter 1 for Auto and 2 to choose attack move manually: ";
            cin>>choice;
            if(choice == 1 )
            {
                Auto = true;
            }
            else if( choice == 2 )
            {
                Auto = false;
            }
            else
            {
                cout<<"Invalid input :\n";
                GameMode();
            }
    }
   
    void InitiateDuel()
    {
        this->GameMode();
       
        cout<<"\n===== DUEL BEGINS =====\n";
        cout<<b1.name<<" ("<<b1.element<<", HP: "<<b1.hp<<"/"<<b1.initialHP<<") VS "<<b2.name<<" ("<<b2.element<<", HP: "<<b2.hp<<"/"<<b2.initialHP<<")\n\n";
   
        if(b1.speed > b2.speed)
        {
           
            cout<<"Turn 1: "<<b1.name<<" goes first! (Speed: "<<b1.name<<"("<<b1.speed<<")"<<" vs "<<b2.name<<"("<<b2.speed<<")"<<" )\n";
                StartDuel(b1 , b2);
           
        }
        else if(b1.speed < b2.speed)
        {  
           
            cout<<"Turn 1: "<<b2.name<<" goes first! (Speed: "<<b1.name<<"("<<b1.speed<<")"<<" vs "<<b2.name<<"("<<b2.speed<<")"<<" )\n";
                StartDuel(b2 , b1);
           
        }
        else
        {
            int temp = rand() % 2;
           
            cout<<"Turn 1: Speed Tie!  :  ";
            if(temp == 0)
            {
                cout<<b1.name<<" goes first! (Speed: "<<b1.name<<"("<<b1.speed<<")"<<" vs "<<b2.name<<"("<<b2.speed<<")"<<" )\n";
                StartDuel(b1 , b2);
            }
            else
            {  
                cout<<b2.name<<" goes first! (Speed: "<<b1.name<<"("<<b1.speed<<")"<<" vs "<<b2.name<<"("<<b2.speed<<")"<<" )\n";
                StartDuel(b2 , b1);
            }
        }
    }
   
    void StartDuel(Bender& b1, Bender& b2)
    {
        Bender* Attacker = &b1;
        Bender* Defender = &b2;
        
        while(b1.hp > 0 && b2.hp > 0)
        {
            int move_index;
            
            if(this->Auto)
            {
                move_index = rand() % 4;
                cout<<"Auto Move Selected: "<< move_index + 1 <<"\n";
            }
            else
            {
                while(true)
                {
                    cout<<"\nChoose attack move(1-4) : ";
                    cin>>move_index;
                    if(move_index >= 1 && move_index <= 4)
                    {
                        move_index--;
                        break;
                    }
                    cout<<"Invalid Input\n";
                }    
            }
            cout<<Attacker->name<<" used "<<Attacker->moves[move_index].first<<"!\n";
    
            double base_damage = (double)(Attacker->attack * Attacker->moves[move_index].second) / Defender->defence;
               
            double elemental_multiplier = 1.0;
    
            static string MatchUp[4][2] =
            {
                { "Water" , "Fire"  } ,
                { "Fire"  , "Air"   } ,
                { "Air"   , "Earth" } ,
                { "Earth" , "Water" }
            };
           
            for(int i = 0 ; i < 4 ; i++)
            {
                if(Attacker->element == MatchUp[i][0] && Defender->element == MatchUp[i][1])
                {
                    elemental_multiplier = 2.0;
                    this->supereffective_counter++;
                    cout<<"Super Effective! ("<<Attacker->element<<" is strong against "<<Defender->element<<")\n";
                    break;
                }
                else if(Attacker->element == MatchUp[i][1] && Defender->element == MatchUp[i][0])
                {
                    elemental_multiplier = 0.5;
                    cout<<"Not very effective... ("<<Attacker->element<<" is weak against "<<Defender->element<<")\n";
                    break;
                }
            }
           
            float critical_chance = 0.10;
            float critical_multiplier = 1.0;
    
            bool is_critical = rand() % 100 < critical_chance * 100 ;
           
            if(is_critical)
            {
                critical_multiplier = 2.0;
                this->critical_counter++;
                cout<<"Critical Hit!\n";
            }
           
            int final_damage = max( 1 , (int)round(base_damage * elemental_multiplier * critical_multiplier) );
           
            cout<<Defender->name<<" took "<<final_damage<<" damage !\n";
            Defender->hp -= final_damage;
            if(Defender->hp < 0)
            {
                Defender->hp = 0;
            }
            cout<<Defender->name<<" HP: "<<Defender->hp<<"/"<<Defender->initialHP<<"\n";
    
            if(Defender->hp > 0)
            {
                this->turns++;
                cout<<"\nTurn "<<turns<<": "<<Defender->name<<" strikes back!\n";
                Bender* temp = Attacker;
                Attacker = Defender;
                Defender = temp;
            }
            else
            {
                cout<<"\n"<<Defender->name<<" fainted!\n";
                cout<<"🏆  "<<Attacker->name<<" wins the duel!\n";
                cout<<"\n\n";
                cout<<"Duel Summary: \n";
                cout<<"- Winner: "<<Attacker->name<<"\n";
                cout<<"- Turns: "<<this->turns<<"\n";
                cout<<"- Critical Hits: "<<this->critical_counter<<"\n";
                cout<<"- Super Effective Hits: "<<this->supereffective_counter<<"\n";
            }
        }
    }

};


int main()
{
    srand(time(NULL));
   
    cout<<"\n***** Create Bender 1 *****\n";
    Bender B1 = Bender::userInput();
   
    cout<<"\n***** Create Bender 2 *****\n";
    Bender B2 = Bender::userInput();

    duel Duel(B1, B2);
    Duel.InitiateDuel();
}
