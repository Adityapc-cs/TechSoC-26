#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

class Blender
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
    
    Blender(const string& name , const string& element , int hp , int attack , int defence , int speed , const vector<pair<string,int>>& moves)
    {
        this->name = name;
        this->element = element;
        this->hp = hp;
        initialHP = this->hp;
        this->attack = attack;
        this->defence = defence;
        this->speed = speed;
        this->moves = moves;
        cout<<"\nBlender "<<name<<" successfully created.\n";
    }
    
    static Blender userInput()
    {
        string Uname, Uelement;
        int Uhp,Uattack,Udefence,Uspeed;
        vector<pair<string,int>> Umoves(4);
        
        cout<<"Enter Blender Details: \n";
        cout<<"Name: ";
        getline(cin>>ws , Uname);
        cout<<"\nElement: ";
        getline(cin>>ws , Uelement);
        
        cout<<"\nHP: ";
        cin>>Uhp;
        cout<<"\nAttack:";
        cin>>Uattack;
        cout<<"\nDefence:";
        cin>>Udefence;
        cout<<"\nSpeed:";
        cin>>Uspeed;
        
        cout<<"\nEnter moves attributes (name,power) one by one:\n";
        for(int i = 0 ; i < 4 ; i++)
        {
            cout<<"\nMove "<<i+1<<"\n";
            cout<<"Name:";
            getline(cin>>ws , Umoves[i].first);
            cout<<"Power:";
            cin>>Umoves[i].second;
        }
        
        return Blender( Uname , Uelement , Uhp , Uattack , Udefence , Uspeed , Umoves );
        
    }
    
    void damage(Blender& defender)
    {
        int move_index;
        while(true)
        {
            cout<<"\nChoose attack move(1-4) : ";
            cin>>move_index;
            if(move_index >= 1 && move_index <= 4 )
            {
                move_index--;
                break;
            }
            cout<<"Invalid Input\n";
        }
        cout<<"\n"<<this->name<<" used "<<this->moves[move_index].first<<" !\n";
    
        int damage = round((double)(this->attack * this->moves[move_index].second) / defender.defence);
        cout<<defender.name<<" took "<<damage<<" damage !\n";
        defender.hp -= damage;
        if(defender.hp<0)
        {
            defender.hp = 0;
        }
        
    }
    
    void checkFainted()
    {
        if(this->hp>0)
        {
            cout<<"\n"<<this->name<<" fainted: False\n";
        }
        else
        {
            cout<<"\n"<<this->name<<" fainted: True\n";
        }
    }
    
    void displayStats()
    {
        cout<<"\n";
        cout<<name<<" ("<<element<<") - HP: "<<hp<<"/"<<initialHP<<", Attack: "<<attack<<", Defence: "<<defence<<", Speed: "<<speed<<"\n";
        for(int i = 0 ; i<4 ; i++ )
        {
            cout<<"Move: "<<moves[i].first<<" ("<<moves[i].second<<")  ";
        }
        cout<<"\n";
    }
    
    
};

int attackerIndex;

int selectAttacker()
{

    while(true)
    {
        cout<<"\nSelect Attacker (1 or 2) : ";
        cin>>attackerIndex;
        
        if(attackerIndex == 1 || attackerIndex == 2)
        break;
        
        cout<<"Invalid Input\n";
    }

    
    
    return attackerIndex;
}

int main()
{
    
    cout<<"\n***Create Blender 1***\n\n";
    Blender B1 = Blender::userInput();
    
    cout<<"\n***Create Blender 2***\n\n";
    Blender B2 = Blender::userInput();
    
    cout<<"***** Initial Stats ******\n\n";
    
    B1.displayStats();
    B2.displayStats();
    
    selectAttacker();
    
    Blender& Attacker = (attackerIndex == 1) ? B1 : B2 ;
    Blender& Defender = (attackerIndex == 1) ? B2 : B1 ;
    
    
    Attacker.damage(Defender);
    
    Defender.displayStats();
        
    Defender.checkFainted();
    
    return 0;
}

