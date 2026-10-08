//I have made only the AI Duel part
//During input , please enter the setup moves first as per the sequence

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
    vector<pair<string,int>>moves;
    struct StatusMove
    {
        string Name; 
        int Power;
        string Effect;
    };
    vector<StatusMove> Effects;
   
    Bender(const string& name , const string& element , int hp , int attack , int defence , int speed , const vector<pair<string,int>>& moves , vector<StatusMove>& Effects)
    {
        this->name = name;
        this->element = element;
        this->hp = hp;
        initialHP = this->hp;
        this->attack = attack;
        this->defence = defence;
        this->speed = speed;
        this->moves = moves;
        this->Effects = Effects;
        cout<<"\nBender "<<name<<" successfully created.\n";
    }
   
static Bender userInput()
    {
        string Uname, Uelement;
        int Uhp,Uattack,Udefence,Uspeed;
        
        string Nam , Eff;
        int Pow;
        vector<StatusMove>UEffects; 
        
        vector<pair<string,int>> Umoves(3);
       
        cout<<"Enter Bender Details: \n";
        cout<<"Name : ";
        getline(cin>>ws , Uname);
        
        cout<<"\n--- Element Guide ---\n";
        cout<<"Choose from: Water , Fire , Air or Earth.\n";
        cout<<"Rule: Water beats Fire, Fire beats Air, Air beats Earth and Earth beats Water.\n";
        cout<<"Strong hits do double damage! Weak hits do half.\n";
        cout<<"Element: ";
        getline(cin>>ws , Uelement);
       
        cout<<"\n--- Stats Guide ---\n";
        cout<<"For a fair game, HP should ideally be between 100 - 500.\n";
        cout<<"Keep Attack, Defence, and Speed around 75.\n";
        cout<<"Enter HP , Attack , Defence and Speed (separated by spaces): \n";
        cin>>Uhp>>Uattack>>Udefence>>Uspeed;
        
        cout<<"\n--- Status Move Guide ---\n";
        cout<<"Name can be anything of your choice , follow following instructions for effect.\n";
        cout<<"You can pick one of these 3 effects for your special move:\n";
        cout<<"1. Burn: Enemy loses 10% of their max HP every turn for 4 turns.\n";
        cout<<"2. Frozen: 50% chance the enemy's turn is skipped (lasts 3 turns).\n";
        cout<<"3. Buried: Enemy is trapped and cannot move for a few turns.\n";
        cout<<"\nStatus Move Attributes: \n";
        {
            cout<<"Enter Name , Power and Effect one by one \n";
            getline(cin>>ws , Nam);
            cin>>Pow;
            getline(cin>>ws , Eff);
            
            if (Eff.length() > 0)                   //for making things flexible enough.
            {
                char firstLetter = toupper(Eff[0]);
                
                if (firstLetter == 'F')
                {
                    Eff = "Frozen";
                }
                else if (firstLetter == 'B')
                {                                   //for seperating burn and buried from eo
                    bool isBurn = false;
                    for (char c : Eff) {
                        if (toupper(c) == 'N') {
                            isBurn = true;
                            break;
                        }            
                    }
                    if (isBurn) {
                        Eff = "Burn";
                    } else {
                        Eff = "Buried";
                    }
                }
            }
            
            UEffects.push_back({Nam , Pow , Eff});
        }
       
        cout<<"\nEnter moves attributes (name,power) one by one:\n";
        for(int i = 0 ; i < 3 ; i++)
        {
            cout<<"\nMove "<<i+1<<"\n";
            cout<<"Name and Power :\n";
            getline(cin>>ws , Umoves[i].first);
            cin>>Umoves[i].second;
        }
        
        return Bender( Uname , Uelement , Uhp , Uattack , Udefence , Uspeed , Umoves , UEffects );
    }
   
};

class AI_Duel 
{
    public:
    Bender AI;
    Bender User;

    int critical_counter = 0;
    int supereffective_counter = 0;
    int statusEffects_counter = 0;
    int resistedHits_counter = 0;
    int turns = 1;
    bool Auto;
    
    void GameMode()
    {
        while(true)
        {
            int choice;
            cout<<"\n**** FOR USER GAME MODE ****\n";
            cout<<"Enter 1 for Auto and 2 to choose attack move manually: ";
            cin>>choice;
            if(choice == 1 )
            {
                Auto = true;
                break;
            }
            else if( choice == 2 )
            {
                Auto = false;
                break;
            }
            else
            {
                cout<<"Invalid Input\n";
            }
        }    
    }
    
    AI_Duel(Bender& uAI , Bender& uUser) : AI(uAI) , User(uUser) 
    {
    }

    int StrongestMove(Bender& B)
    {
        int SMindex = 0;
        for(int i = 1 ; i < 3 ; i++ )
        {
            if(B.moves[i].second > B.moves[SMindex].second)
            {
                SMindex = i;
            }
        }
        return SMindex; 
    }
    
    void InitiateDuel()
    {
        GameMode();
        
        cout<<"\n   ===== AI DUEL BEGINS! =====    \n";
        cout<<User.name<<" ("<<User.element<<", HP: "<<User.hp<<"/"<<User.initialHP<<") VS "<<AI.name<<" ("<<AI.element<<", HP: "<<AI.hp<<"/"<<AI.initialHP<<") [ AI ]\n\n";
        
        if(AI.speed > User.speed)
        {
           
            cout<<"Turn 1: "<<AI.name<<" goes first! (Speed: "<<AI.name<<"("<<AI.speed<<")"<<" vs "<<User.name<<"("<<User.speed<<")"<<" )\n";
                StartDuel(AI , User);
           
        }
        else if(AI.speed < User.speed)
        {  
           
            cout<<"Turn 1: "<<User.name<<" goes first! (Speed: "<<AI.name<<"("<<AI.speed<<")"<<" vs "<<User.name<<"("<<User.speed<<")"<<" )\n";
                StartDuel(User , AI);
           
        }
        else
        {
            int temp = rand() % 2;
           
            cout<<"Turn 1: Speed Tie!  :  ";
            if(temp == 0)
            {
                cout<<AI.name<<" goes first! (Speed: "<<AI.name<<"("<<AI.speed<<")"<<" vs "<<User.name<<"("<<User.speed<<")"<<" )\n";
                StartDuel(AI , User);
            }
            else
            {  
                cout<<User.name<<" goes first! (Speed: "<<AI.name<<"("<<AI.speed<<")"<<" vs "<<User.name<<"("<<User.speed<<")"<<" )\n";
                StartDuel(User , AI);
            }
        }
    }
    
    void StartDuel(Bender& b1, Bender& b2)
    {
        {
        Bender* Attacker = &b1;
        Bender* Defender = &b2;
        
        bool Affected = false;
        int EffDuration = 0;
        int InitEffDuratn ;
        string Deffect;
        int healingMove = 3;

        while(b1.hp > 0 && b2.hp > 0)
        {
            if(Attacker == &(this->User))
            {
                if(!Affected)
                {
                    int move_index;
                    if(this->Auto)
                    {
                        move_index = rand() % 3;
                        cout<<"Auto Move Selected: "<< move_index + 1 <<"\n";
                    }
                    else
                    {
                        while(true)
                        {
                            cout<<"\nChoose attack move(1-3) : ";
                            cin>>move_index;
                            if(move_index >= 1 && move_index <= 3)
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
                            this->resistedHits_counter++;
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
                }
                else
                {
                    if(Deffect == "Burn" )
                    {
                        if(EffDuration!= 0)
                        {
                            cout<<"Burning!\n";
                            Attacker->hp -= (0.10)*Attacker->initialHP;
                                 
                            if(Attacker->hp > 0)
                            {
                                //normal user attk
                                int move_index;
                                if(this->Auto)
                                {
                                    move_index = rand() % 3;
                                    cout<<"Auto Move Selected: "<< move_index + 1 <<"\n";
                                }
                                else
                                {
                                    while(true)
                                    {
                                        cout<<"\nChoose attack move(1-3) : ";
                                        cin>>move_index;
                                        if(move_index >= 1 && move_index <= 3)
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
                            
                                for(int i = 0 ; i < 3 ; i++)
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
                                        this->resistedHits_counter++;
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
                            }
                            else
                            {
                                Attacker->hp = 0;

                                    cout<<"\n"<<Attacker->name<<" fainted due to bruning!\n";
                                    cout<<"🏆  "<<Defender->name<<" wins the duel!\n";
                                    cout<<"\n\n";
                                    cout<<"Duel Summary: \n";
                                    cout<<"- Winner: "<<Defender->name<<"\n";
                                    cout<<"- Turns: "<<this->turns<<"\n";
                                    cout<<"- Status Effect used: "<<this->statusEffects_counter<<"\n";
                                    cout<<"- Critical Hits: "<<this->critical_counter<<"\n";
                                    cout<<"- Super Effective Hits: "<<this->supereffective_counter<<"\n";
                                    cout<<"- Resisted Hits: "<<this->resistedHits_counter<<"\n";

                                    break;
                                    
                            }        
                        }
                        EffDuration--;
                        
                        if(EffDuration == 0)
                        {
                            Deffect ="Null";
                            Affected = false;
                        }
                        else
                        {
                            cout<<"Burn duration: "<<EffDuration<<" turns remaining\n";
                        }
                    }
                    
                    else if(Deffect == "Frozen" )
                    {
                        if(EffDuration!= 0)
                        {
                            bool skip = rand() % 2 ;
                            if(skip)
                            {
                                cout<<"Turn skipped due to frozen effect!\n";
                            }
                            else
                            {
                                cout<<"Got lucky, chance didnt got skipped due to frozen effect!\n";
                                                
                                    int move_index;
                                    if(this->Auto)
                                    {
                                        move_index = rand() % 3;
                                        cout<<"Auto Move Selected: "<< move_index + 1 <<"\n";
                                    }
                                    else
                                    {
                                        while(true)
                                        {
                                            cout<<"\nChoose attack move(1-3) : ";
                                            cin>>move_index;
                                            if(move_index >= 1 && move_index <= 3)
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
                                
                                    for(int i = 0 ; i < 3 ; i++)
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
                                            this->resistedHits_counter++;
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
                                                
                            }
                        }
                        EffDuration--;

                        if(EffDuration == 0)
                        {
                            Deffect ="Null";
                            Affected = false;
                        }  
                        else
                        {
                            cout<<"Frozen duration: "<<EffDuration<<" turns remaining\n";
                        }
                    }
                    
                    else if(Deffect == "Buried" )
                    {
                        if(EffDuration!= 0)
                        {
                            if(EffDuration == InitEffDuratn)
                            {
                                cout<<Attacker->name<<" is buried and cannot move!\n";
                            }
                            else
                            {
                                cout<<Attacker->name<<" is still buried , can not move!\n";
                            }
                        }
                        
                        EffDuration--;
                        
                        if(EffDuration == 0)
                        {
                            Deffect ="Null";
                            Affected = false;
                        } 
                        else
                        {
                            cout<<"Buried duration: "<<EffDuration<<" turns remaining\n";
                        }
                    }
                }
            }
            else
            {
                if( Attacker->hp < 0.30*(Attacker->initialHP) )
                {
                    cout<<"🤖 AI Analysis: HP critical , using a Healing Move.\n";
                    if(healingMove != 0)
                    {
                        cout<<"Healed! "<<"HP: ("<<Attacker->hp<<" -> ";
                        Attacker->hp += 0.25*(Attacker->initialHP);
                        cout<<Attacker->hp<<")\n";
                        healingMove--;
                        cout<<"Only "<<healingMove<<" remaining!\n";
                    }    
                    else
                    {
                        cout<<"No healing move available :( \n";
                    
                        if(Attacker->Effects.size() != 0 && Attacker->Effects[0].Effect != "Buried")
                        {
                            if (!Affected) 
                            {
                                cout<<"Now inflicting a status effect for revenge.\n";
                                cout<<Attacker->name<<" used "<<Attacker->Effects[0].Name<<" !\n";
                                if(Attacker->Effects[0].Effect == "Burn")
                                {
                                    EffDuration = 4 ;
                                    Deffect = "Burn";
                                    Affected = true;
                                    cout<<Defender->name<<" will BURN now! \n(10% of max HP damage each turn)  (4 turns remaining)\n";
                                }
                                else if(Attacker->Effects[0].Effect == "Frozen")
                                {
                                    EffDuration = 3;
                                    Deffect = "Frozen";
                                    Affected = true;
                                    cout<<Defender->name<<" is FROZEN now! \nNow there is 50% chance that "<<Defender->name<<"'s turn will get skipped!  (3 turns remaining)\n";
                                }
                                this->statusEffects_counter++;
                            }
                            else
                            {
                                cout<<"🤖 AI Analysis: Defender is already affected! Cannot apply status move again.\n";
                            }
                        }
                    }    
                }
                
                else if( Defender->hp > 0.70*(Defender->initialHP) && Attacker->Effects.size() != 0 && !Affected )
                {
                    int x = rand() % 3;
                    switch(x)
                    {
                        case 0 :
                        cout<<"🤖 AI Analysis: The enemy stands tall, barely scratched . Inflicting a status effect to bring them down!\n";
                        break;
                        
                        case 1:
                        cout<<"🤖 AI Analysis: Enemy look way too comfortable. Let's shake things up. Forcing a status effect!\n";
                        break;

                        case 2:
                        cout<<"🤖 AI Analysis: Full of energy, aren't they? Let's trip them up... Dropping a status effect!\n";
                        break;
                    }

                        cout<<Attacker->name<<" used "<<Attacker->Effects[0].Name<<" !\n";
                        if(Attacker->Effects[0].Effect == "Burn")
                        {
                            EffDuration = 4 ;
                            Deffect = "Burn";
                            Affected = true;
                            cout<<Defender->name<<" will BURN now! \n(10% of max HP damage each turn)  (4 turns remaining)\n";
                        }
                        else if(Attacker->Effects[0].Effect == "Frozen")
                        {
                            EffDuration = 3;
                            Deffect = "Frozen";
                            Affected = true;
                            cout<<Defender->name<<" is FROZEN now! \nNow there is 50% chance that "<<Defender->name<<"'s turn will get skipped!  (3 turns remaining)\n";
                        }
                        else if(Attacker->Effects[0].Effect == "Buried")
                        {
                            EffDuration = 2 + rand() % 3 ;
                            InitEffDuratn = EffDuration;
                            Deffect = "Buried";
                            Affected = true;
                            cout<<Defender->name<<" is now BURIED! ("<<EffDuration<<" turns remaining)\n";
                        }

                    this->statusEffects_counter++;  

                }

                else if( Defender->hp < 0.25*(Defender->initialHP) )
                {
                    int x = rand() % 3;
                    switch(x)
                    {
                        case 0 :
                        cout<<"🤖 AI Analysis: They're on their last legs. Time to finish this with everything I've got!\n";
                        break;
                        
                        case 1:
                        cout<<"🤖 AI Analysis: They're hanging by a thread. Unleashing my strongest attack!\n";
                        break;

                        case 2:
                        cout<<"🤖 AI Analysis: Almost done. Let's close this out with a massive hit!\n";
                        break;
                    }

                    int move_index = this->StrongestMove(*Attacker);

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
                            this->resistedHits_counter++;
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
                
                }

                else
                {
                    int move_index = rand() % 3;

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
                
                    for(int i = 0 ; i < 3 ; i++)
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
                            this->resistedHits_counter++;
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
                }
            }

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
                cout<<"- Status Effect used: "<<this->statusEffects_counter<<"\n";
                cout<<"- Critical Hits: "<<this->critical_counter<<"\n";
                cout<<"- Super Effective Hits: "<<this->supereffective_counter<<"\n";
                cout<<"- Resisted Hits: "<<this->resistedHits_counter<<"\n";
            }
        }
    }

    }

    
};

int main()
{
    int Choice;
    
    cout<<"Enter 1 for playing with AI and 2 for playing Tournament \n";
    cin>>Choice;
    
    if(Choice == 1)
    {
        int choice;
        cout<<"\n**** Initiating duel with AI ****\n";
        
            cout<<"\n***** Create Bender 1 *****\n";
            Bender Bender1 = Bender :: userInput();
            
            cout<<"\n***** Create Bender 2 *****\n";
            Bender Bender2 = Bender :: userInput();
    
        while(true)
        {
            cout<<"\nWhich Bender should be controlled by the AI? (1 or 2)\n";
            cin>>choice;
            
            if(choice == 1)
            {
                AI_Duel Match(Bender1 , Bender2);
                Match.InitiateDuel();
                break;
            }
            else if(choice == 2)
            {
                AI_Duel Match(Bender2 , Bender1);
                Match.InitiateDuel();
                break;
            }
            else
            {
                cout<<"Invalid Input\n";
            }
        }
    } 
}