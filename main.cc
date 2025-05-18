#include "person.h"
#include "role.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <vector>
using namespace std;

Person Player("Player"), Adam("Adam"), Brent("Brent"), Cindy("Cindy"), Daphne("Daphne"), Ethan("Ethan"), Finn("Finn"),
    Gertrude("Gertrude"), Harry("Harry"), Ian("Ian"), Jessica("Jessica"), Kim("Kim"), Leon("Leon"), Mike("Mike"),
    Nate("Nate"), Ophelia("Ophelia"), Penny("Penny"), Quinn("Quinn"), Ralph("Ralph"), Sadie("Sadie"), Tanya("Tanya"),
    Uncle_Parker("Uncle Parker"), Veronica("Veronica"), Wendy("Wendy"), Xavier("Xavier"), Yorra("Yorra"), Zoe("Zoe");

vector <Person> Town = {Player, Adam, Brent, Cindy, Daphne, Ethan, Finn, Gertrude, Harry, Ian, Jessica, Kim, Leon, Mike,
    Nate, Ophelia, Penny, Quinn, Ralph, Sadie, Tanya, Uncle_Parker, Veronica, Wendy, Xavier, Yorra, Zoe};

vector <Person> detective1, detective2, dead;
Person doctor1(""), doctor2(""), mafia(""), cop1(""), cop2("");
int cop1_bullets, cop2_bullets, night_count;
size_t mafia_count;
bool alive, fool;

void set_roles();
void menu(); void eval();
void play(); void how_to(); void role_list();
void day(); void night();
void statement(Person who); void defense(Person who);

int main(){
    srand(time(0));
    menu();

    exit(0);
}

void menu(){
    string X;
    do{
        system("clear");
        cout << "   \e[36m MAFIA\e[0m\n";
        cout << "\e[32m1:\e[0m Play Game\n";
        cout << "\e[32m2:\e[0m How To Play\n";
        cout << "\e[32m3:\e[0m Role List\n";
        cout << "\e[31m4:\e[0m Exit Game\n";
        cout << "-> ";
        cin >> X;
    }while(X != "1" && X != "2" && X != "3" && X != "4");
    
    if(X == "1"){
        this_thread::sleep_for(chrono::milliseconds(500));
        play();
    }
    else if(X == "2"){
        how_to();
    }
    else if(X == "3"){
        role_list();
    }
    else if(X == "4"){
        system("clear");
        exit(0);
    }
}

void play(){
    //set up
    system("clear");
    string X;
    detective1.clear(); detective2.clear(); dead.clear();
    doctor1.set_name(""); doctor2.set_name("X"); mafia.set_name(""); cop1.set_name(""); cop2.set_name("O");
    cop1_bullets = cop2_bullets = 2; night_count = 1;
    alive = true; fool = false;
    set_roles();
    Player = Town.at(0);
    string player_role = Player.get_role().get_name();
    cout << " Welcome to the village!\n";
    cout << " You are a \e[36m" << player_role << "\e[0m" << endl;
    if(player_role == "Villager"){
        cout << " Help catch the Mafia before they kill the village\n";
    }
    else if(player_role == "Mafia"){
        cout << " Work with the other Mafia to kill the village\n";
    }
    else if(player_role == "Doctor"){
        cout << " Save a person from death each night\n";
    }
    else if(player_role == "Cop"){
        cout << " You have two bullets. Shoot carefully, and don't kill innocents!\n";
    }
    else if(player_role == "Detective"){
        cout << " Figure out a player's role each night\n";
    }
    else if(player_role == "Fool"){
        cout << " All you want is to be executed in court\n";
    }
    cout << "\n\e[33m Night falls, and the village falls asleep\e[0m\n\n";
    cout << "\e[32m [Enter 1 to proceed]\e[0m\n -> ";
    cin >> X;
    cout << endl;
    night();
}

void how_to(){
    string X;
    system("clear");
    cout << " \e[35m * How To Play *\e[0m\n\n";
    cout << "\e[36m-\e[0m At the start of the game, everyone will be assigned a random role\n";
    cout << "\e[36m-\e[0m The game is split into two phases, day and night\n";
    cout << "\e[36m-\e[0m During night, certain roles will perform special actions without being revealed\n";
    cout << "\e[36m-\e[0m During day, night events are revealed, and court takes place\n";
    cout << "\e[36m-\e[0m In court, one person is put on trial. They have a chance to defend themselves\n";
    cout << "\e[36m-\e[0m Everyone else will vote to spare or execute the person on trial\n";
    cout << "\e[36m-\e[0m After court, night starts again\n";
    cout << "\e[36m-\e[0m The game continues until a teams win condition has been met\n\n";
    cout << "\e[32m[Enter 1 to return to menu]\e[0m\n -> ";
    cin >> X;
    menu();
}

void role_list(){
    string X;
    system("clear");
    cout << " \e[35m * Role List *\e[0m\n\n";
    cout << "\e[36m-\e[0m \e[32mVillager:\e[0m Village Team\n";
    cout << "   \e[35m-\e[0m Win Condition: Eliminate all the killers\n";
    cout << "   \e[35m-\e[0m Ability: None\n";
    cout << "\e[36m-\e[0m \e[31mMafia:\e[0m Mafia Team\n";
    cout << "   \e[35m-\e[0m Win Condition: Eliminate the village\n";
    cout << "   \e[35m-\e[0m Ability: Wake up with other mafia to kill a player\n";
    cout << "\e[36m-\e[0m \e[32mCop:\e[0m Village Team\n";
    cout << "   \e[35m-\e[0m Win Condition: Eliminate all the killers\n";
    cout << "   \e[35m-\e[0m Ability: 2 bullets. May shoot a player at night\n";
    cout << "\e[36m-\e[0m \e[32mDoctor:\e[0m Village Team\n";
    cout << "   \e[35m-\e[0m Win Condition: Eliminate all the killers\n";
    cout << "   \e[35m-\e[0m Ability: Wake up to protect one player from death\n";
    cout << "\e[36m-\e[0m \e[32mDetective:\e[0m Village Team\n";
    cout << "   \e[35m-\e[0m Win Condition: Eliminate all the killers\n";
    cout << "   \e[35m-\e[0m Ability: Wake up to learn one player's role\n";
    cout << "\e[36m-\e[0m \e[33mFool:\e[0m Fool Team\n";
    cout << "   \e[35m-\e[0m Win Condition: Be executed in court\n";
    cout << "   \e[35m-\e[0m Ability: None\n\n";
    cout << "\e[36m[Enter 1 to return to menu]\e[0m\n -> ";
    cin >> X;
    menu();
}

void set_roles(){
    vector <Role> roles;
    int mafia = 0, villager = 0, cop = 0, doctor = 0, detective = 0, fool = 0;
    Role temp("");
    temp.set_lvl(1);

    //set player
    int X = rand()%5;
    if(X == 0){
        temp.set_name("Villager");
        villager++;
    }
    else{
        X = rand()%20;
        if(X < 5){
            temp.set_name("Mafia");
            mafia++;
        }
        else if(X < 9){
            temp.set_name("Doctor");
            doctor++;
        }
        else if(X < 13){
            temp.set_name("Cop");
            cop++;
        }
        else if(X < 16){
            temp.set_name("Fool");
            fool++;
        }
        else{
            temp.set_name("Detective");
            detective++;
        }
    }
    Town.at(0).set_role(temp);

    //create the other 26 roles
    //fool (1)
    if(fool == 0){
        temp.set_name("Fool");
        roles.push_back(temp);
        fool++;
    }

    //cop (1-2)
    X = rand()%2;
    if(cop == 0){
        temp.set_name("Cop");
        roles.push_back(temp);
        cop++;
    }
    if(X == 1){
        temp.set_name("Cop");
        temp.set_lvl(2);
        roles.push_back(temp);
        temp.set_lvl(1);
        cop++;
    }

    //doctor (1-2)
    X = rand()%2;
    if(doctor == 0){
        temp.set_name("Doctor");
        roles.push_back(temp);
        doctor++;
    }
    if(X == 1){
        temp.set_name("Doctor");
        temp.set_lvl(2);
        roles.push_back(temp);
        temp.set_lvl(1);
        doctor++;
    }

    //detective (1-2)
    X = rand()%2;
    if(detective == 0){
        temp.set_name("Detective");
        roles.push_back(temp);
        detective++;
    }
    if(X == 1){
        temp.set_name("Detective");
        temp.set_lvl(2);
        roles.push_back(temp);
        temp.set_lvl(1);
        detective++;
    }

    //mafia (4-6)
    X = rand()%3;
    if(mafia == 0){
        temp.set_name("Mafia");
        roles.push_back(temp);
        mafia++;
    }
    temp.set_name("Mafia");
    roles.push_back(temp);
    roles.push_back(temp);
    roles.push_back(temp);
    mafia+=3;
    mafia_count = 4;
    if(X > 0){
        roles.push_back(temp);
        mafia++;
        mafia_count++;
    }
    if(X > 1){
        roles.push_back(temp);
        mafia++;
        mafia_count++;
    }

    //villagers (14-19)
    temp.set_name("Villager");
    for(int i = 0; i < 14; i++){
        roles.push_back(temp);
        villager++;
    }
    if(cop == 1){
        roles.push_back(temp);
        villager++;
    }
    if(doctor == 1){
        roles.push_back(temp);
        villager++;
    }
    if(detective == 1){
        roles.push_back(temp);
        villager++;
    }
    if(mafia < 6){
        roles.push_back(temp);
        villager++;
    }
    if(mafia < 5){
        roles.push_back(temp);
        villager++;
    }

    //randomly add roles to players
    int count = 1;
    while(count < 27){
        X = rand()%roles.size();
        Town.at(count).set_role(roles.at(X));
        roles.erase(roles.begin() + X);
        count++;
    }
}

void night(){
    size_t X;
    cout << " \e[36m  NIGHT " << night_count << "\e[0m" << endl << endl;
    doctor1.set_name(""); doctor2.set_name("X"); mafia.set_name(""); cop1.set_name(""); cop2.set_name("O");

    if(alive){
        if(Player.get_role().get_name() == "Villager" || Player.get_role().get_name() == "Fool"){
            cout << "\e[33m The night passes, and you sleep\e[0m\n";
        }
    }
    if(!alive){
        cout << "\e[33m Your spirit watches the night pass swiftly\e[0m\n";
    }

    //DOCTOR
    //player
    if(alive && Player.get_role().get_name() == "Doctor"){
        do{
            cout << "\e[33m Select a player to protect tonight\e[0m\n";
            cout << "\e[35m 1:\e[0m Yourself\n";
            for(size_t i = 1; i < Town.size(); i++){
                cout << " \e[35m" << i+1 << ":\e[0m " << Town.at(i).get_name() << endl;
            }
            cout << " -> ";
            cin >> X;
        }while(X < 1 && X > Town.size());

        if(Player.get_role().get_lvl() == 1){
            doctor1 = Town.at(X-1);
        }
        else{
            doctor2 = Town.at(X-1);
        }
    }
    //computer
    //doc1
    for(size_t i = 0; i < Town.size(); i++){
        if(Town.at(i).get_role().get_name() == "Doctor" && Town.at(i).get_role().get_lvl() == 1 && Town.at(i).get_name() != "Player"){
            X = rand()%Town.size();
            doctor1 = Town.at(X);
        }
    }
    //doc2
    for(size_t i = 0; i < Town.size(); i++){
        if(Town.at(i).get_role().get_name() == "Doctor" && Town.at(i).get_role().get_lvl() == 2 && Town.at(i).get_name() != "Player"){
            X = rand()%Town.size();
            doctor2 = Town.at(X);
        }
    }

    //MAFIA
    //player
    if(alive && Player.get_role().get_name() == "Mafia"){
        cout << "\e[31m Other Mafia members:\e[0m\n";
        for(size_t i = 1; i < Town.size(); i++){
            if(Town.at(i).get_role().get_name() == "Mafia"){
                cout << " \e[31m- \e[0m" << Town.at(i).get_name() << endl;
            }
        }
        cout << endl;

        do{
            cout << "\e[33m Select a player to kill tonight\e[0m\n";
            for(size_t i = 1; i < Town.size(); i++){
                if(Town.at(i).get_role().get_name() != "Mafia"){
                    cout << "\e[35m " << i << ":\e[0m " << Town.at(i).get_name() << endl;
                }
            }
            cout << " -> ";
            cin >> X;
        }while(X < 1 && X > Town.size() && Town.at(X).get_role().get_name() != "Mafia");

        mafia = Town.at(X);
    }
    //computer
    else if(mafia_count != 0){
        do{
            X = rand()%Town.size();
        }while(Town.at(X).get_role().get_name() == "Mafia");
        mafia = Town.at(X);
    }

    //DETECTIVE
    //player
    if(alive && Player.get_role().get_name() == "Detective"){
        do{
            cout << "\e[33m Select a player to investigate\e[0m\n";
            for(size_t i = 1; i < Town.size(); i++){
                cout << "\e[35m " << i << ": \e[0m" << Town.at(i).get_name() << endl;
            }
            cout << " -> ";
            cin >> X;
        }while(X < 1 && X > Town.size());

        cout << endl << "\e[33m " << Town.at(X).get_name() << "\e[0m is a \e[36m" << Town.at(X).get_role().get_name() << "\e[0m" << endl;

        if(Player.get_role().get_lvl() == 1){
            detective1.push_back(Town.at(X));
        }
        else{
            detective2.push_back(Town.at(X));
        }
    }
    //computer
    //detective1
    for(size_t i = 0; i < Town.size(); i++){
        if(Town.at(i).get_role().get_name() == "Detective" && Town.at(i).get_role().get_lvl() == 1 && Town.at(i).get_name() != "Player"){
            do{
                X = rand()%Town.size();
            }while(X == i);
            detective1.push_back(Town.at(X));
        }
    }
    //detective2
    for(size_t i = 0; i < Town.size(); i++){
        if(Town.at(i).get_role().get_name() == "Detective" && Town.at(i).get_role().get_lvl() == 2 && Town.at(i).get_name() != "Player"){
            do{
                X = rand()%Town.size();
            }while(X == i);
            detective2.push_back(Town.at(X));
        }
    }

    //COP
    //player
    if(alive && Player.get_role().get_name() == "Cop"){
        do{
            cout << "\e[31m Bullet count: ";
            if(Player.get_role().get_lvl() == 1){
                cout << cop1_bullets << endl;
            }
            else{
                cout << cop2_bullets << endl;
            }
            cout << "\e[33m Do you want to shoot anyone?\n";
            cout << " *Shooting at an innocent will result in your death instead*\e[0m\n";
            cout << " \e[35m1:\e[0m Shoot someone\n";
            cout << " \e[35m2:\e[0m Wait for now\n";
            cout << " -> ";
            cin >> X;
        }while(X != 1 && X != 2);

        if(X == 2){
            cout << "\n\e[33m You hold on to your bullet for now\e[0m\n";
        }
        else{
            do{
                cout << "\e[33m Select a player to shoot\e[0m\n";
                for(size_t i = 1; i < Town.size(); i++){
                    cout << "\e[35m " << i << ": \e[0m" << Town.at(i).get_name() << endl;
                }
                cout << " -> ";
                cin >> X;
            }while(X < 1 && X > Town.size());

        cout << "\nYou shoot at \e[31m" << Town.at(X).get_name() << "\e[0m" << endl;

        if(Town.at(X).get_role().get_name() != "Mafia"){
            cout << "\e[31m You have tried to kill an innocent! You shoot yourself due to guilt\e[0m\n";
            X = 0;
        }

        if(Player.get_role().get_lvl() == 1){
            cop1 = Town.at(X);
            cop1_bullets--;
        }
        else{
            cop2 = Town.at(X);
            cop2_bullets--;
        }
        }
    }
    //computer
    //cop1
    X = rand() % (Town.size() / 3);
    if(X == 0){
        for(size_t i = 0; i < Town.size(); i++){
            if(Town.at(i).get_role().get_name() == "Cop" && Town.at(i).get_role().get_lvl() == 1 && Town.at(i).get_name() != "Player"){
                do{
                    X = rand()%Town.size();
                }while(X == i);
                if(Town.at(X).get_role().get_name() != "Mafia"){
                    X = i;
                }
                cop1 = Town.at(X);
                cop1_bullets--;
            }
        }
    }
    //cop2
    X = rand() % (Town.size() / 3);
    if(X == 0){
        for(size_t i = 0; i < Town.size(); i++){
            if(Town.at(i).get_role().get_name() == "Cop" && Town.at(i).get_role().get_lvl() == 2 && Town.at(i).get_name() != "Player"){
                do{
                    X = rand()%Town.size();
                }while(X == i);
                if(Town.at(X).get_role().get_name() != "Mafia"){
                    X = i;
                }
                cop2 = Town.at(X);
                cop2_bullets--;
            }
        }
    }
    cout << endl;

    cout << "\e[32m[Enter 1 to proceed to day]\e[0m\n -> ";
    cin >> X;
    cout << endl;
    day();
}

void day(){
    size_t X;
    int spare = 0, kill = 0;
    Person guilty("");
    cout << " \e[36m  DAY " << night_count << "\e[0m" << endl << endl;

    //night events
    if(mafia.get_name() != doctor1.get_name() && mafia.get_name() != doctor2.get_name()){
        cout << "\e[33m The Mafia killed \e[31m";
        if(mafia.get_name() == "Player"){cout << "you"; alive = false;}
        else{cout << mafia.get_name();}
        cout << "\e[33m last night\e[0m\n";
    }
    else{
        cout << "\e[33m The Mafia didn't kill anyone last night\e[0m\n";
    }

    if(cop1.get_name() != doctor1.get_name() && cop1.get_name() != doctor2.get_name() && cop1.get_name() != ""){
        if(cop1.get_name() == "Player"){cout << "\e[31m You\e[33m were"; alive = false;}
        else{cout << " \e[31m" << cop1.get_name() << "\e[33m was";}
        cout << " shot last night\e[0m\n";
    }

    if(cop2.get_name() != doctor1.get_name() && cop2.get_name() != doctor2.get_name() && cop2.get_name() != "O"){
        if(cop2.get_name() == "Player"){cout << "\e[31m You\e[33m were"; alive = false;}
        else{cout << " \e[31m" << cop2.get_name() << "\e[33m was";}
        cout << " shot last night\e[0m\n";
    }

    cout << endl;

    //remove dead players
    for(size_t i = 0; i < Town.size(); i++){
        if(Town.at(i).get_name() == mafia.get_name()){
            dead.push_back(Town.at(i));
            Town.erase(Town.begin() + i);
        }
    }
    for(size_t i = 0; i < Town.size(); i++){
        if(Town.at(i).get_name() == cop1.get_name()){
            if(cop1.get_role().get_name() == "Mafia"){mafia_count--;}
            dead.push_back(Town.at(i));
            Town.erase(Town.begin() + i);
        }
    }
    for(size_t i = 0; i < Town.size(); i++){
        if(Town.at(i).get_name() == cop2.get_name()){
            if(cop2.get_role().get_name() == "Mafia"){mafia_count--;}
            dead.push_back(Town.at(i));
            Town.erase(Town.begin() + i);
        }
    }

    //show number of mafia left
    cout << " \e[33mThere are " << mafia_count << " Mafia left\e[0m\n\n";

    //check for win
    eval();

    //player statement
    //can implement later, unneccesary for right now

    //each player's statement
    if(!alive){
        if(Town.at(0).get_role().get_name() == "Mafia" && Player.get_role().get_name() == "Mafia"){cout << "\e[31m";}
        else{cout << "\e[36m";}
        cout << Town.at(0).get_name() << ":\e[0m ";
        statement(Town.at(0));
        cout << endl;
    }
    for(size_t i = 1; i < Town.size(); i++){
        if(Town.at(i).get_role().get_name() == "Mafia" && Player.get_role().get_name() == "Mafia"){cout << "\e[31m";}
        else{cout << "\e[36m";}
        cout << Town.at(i).get_name() << ":\e[0m ";
        statement(Town.at(i));
        cout << endl;
    }
    cout << endl;

    cout << "\e[32m [Enter 1 to start court]\e[0m\n -> ";
    cin >> X;
    cout << endl;

    //court: nomination
    cout << "\e[33m Court will proceed. The guilty must be punished\e[0m\n";
    if(alive){ //player still in game
        do{
            cout << "\e[33m Nominate someone to stand trial \e[0m\n";
            for(size_t i = 1; i < Town.size(); i++){
                if(Town.at(i).get_role().get_name() == "Mafia" && Player.get_role().get_name() == "Mafia"){cout << "\e[31m";}
                else{cout << "\e[35m";}
                cout << i << ":\e[0m " << Town.at(i).get_name() << endl;
            }
            cout << " -> ";
            cin >> X;
        }while(X < 1 && X > Town.size());
        guilty = Town.at(X);

        //determine if rest of town will agree (75% chance they agree(50% if player is fool))
        if(Player.get_role().get_name() == "Fool"){ //player is fool
            X = rand()%2;
        }
        else{ //player isn't fool
            X = rand()%4;
        }
        if(X == 0){ //town disagrees
            cout << "\n \e[31mThe town disagrees with your nomination\e[0m\n";
            do{
                X = rand()%Town.size();
            }while(Town.at(X).get_name() == guilty.get_name());
            guilty = Town.at(X);
            if(Player.get_role().get_name() == "Fool"){ //increase chance of a fool win
                X = rand()%4;
                if(X == 0){
                    guilty = Town.at(0);
                }
            }
        }
        else{ //town agrees
            cout << "\n \e[32mMultiple members of the town agree with your nomination\e[0m\n";
        }
    }
    else{ //player dead
        X = rand()%5;
        if(X == 0){ //auto accuse mafia
            do{
                X = rand()%Town.size();
            }while(Town.at(X).get_role().get_name() != "Mafia");
            guilty = Town.at(X);
        }
        else{ //accuse random
            X = rand()%Town.size();
            guilty = Town.at(X);
        }
    }

    cout << "\e[33m The town has chosen \e[35m";
    if(guilty.get_name() == "Player"){cout << "you";}
    else{cout << guilty.get_name();}
    cout << "\e[33m to stand trial\e[0m\n";

    //guilty defense statement
    cout << "\n\e[33m The guilty person will now plead their case\e[0m\n";
    if(guilty.get_name() == "Player"){
        do{
            cout << " \e[33mWhat would you like to say?\e[0m\n";
            cout << "\e[35m 1:\e[0m I'm innocent\n";
            cout << "\e[35m 2:\e[0m If you vote for me, you'll regret it\n";
            cout << "\e[35m 3:\e[0m Don't kill me, you need me\n -> ";
            cin >> X;
        }while(X < 1 && X > 3);
        cout << "\n\e[36m You:\e[0m ";
        if(X == 1){cout << "I'm innocent\n";}
        else if(X == 2){cout << "If you vote for me, you'll regret it\n";}
        else{cout << "Don't kill me, you need me\n";}

    }
    else{
        cout << "\e[36m " << guilty.get_name() << "\e[0m declares: ";
        defense(guilty);
        cout << endl;
    }

    cout << "\n\e[32m [Enter 1 to begin vote]\e[0m\n -> ";
    cin >> X;
    cout << endl;

    //vote to kill
    cout << "\e[33m The town will now decide if the guilty person will live or die\e[0m\n";
    if(alive && guilty.get_name() != "Player"){ //player not on trial
        do{
            cout << "\e[33m Should \e[36m" << guilty.get_name() << "\e[33m be spared or executed?\e[0m\n";
            cout << "\e[35m 1:\e[0m Spare\n \e[35m2:\e[0m Execute\n -> ";
            cin >> X;
        }while(X != 1 && X != 2);
        cout << endl;
        if(X == 1){
            cout << "\e[36mYou\e[0m vote to \e[32mspare\e[0m\n";
            spare++;
        }
        else{
            cout << "\e[36mYou\e[0m vote to \e[31mexecute\e[0m\n";
            kill++;
        }

        for(size_t i = 1; i < Town.size(); i++){
            if(Town.at(i).get_name() != guilty.get_name()){
                cout << "\e[36m" << Town.at(i).get_name() << "\e[0m votes to ";
                if(Town.at(i).get_role().get_name() == "Mafia"){
                    if(guilty.get_role().get_name() == "Mafia"){ //won't vote against mafia
                        cout << "\e[32mspare\e[0m";
                        spare++;
                    }
                    else{
                        X = rand()%2;
                        if(X == 0){
                            cout << "\e[32mspare\e[0m";
                            spare++;
                        }
                        else{
                            cout << "\e[31mexecute\e[0m";
                            kill++;
                        }
                    }
                }
                else{
                    X = rand()%2;
                    if(X == 0){
                        cout << "\e[32mspare\e[0m";
                        spare++;
                    }
                    else{
                        cout << "\e[31mexecute\e[0m";
                        kill++;
                    }
                }
                cout << endl;
            }
        }
    }
    else{ //player dead or on trial
        for(size_t i = 0; i < Town.size(); i++){
            if(Town.at(i).get_name() != guilty.get_name()){
                cout << "\e[36m" << Town.at(i).get_name() << "\e[0m votes to ";
                if(guilty.get_name() == "Player" && guilty.get_role().get_name() == "Fool"){ //increase chance of player winning as fool
                    X = rand()%3;
                    if(X == 0){
                        cout << "\e[32mspare\e[0m";
                        spare++;
                    }
                    else{
                        cout << "\e[31mexecute\e[0m";
                            kill++;
                    }
                }
                else if(Town.at(i).get_role().get_name() == "Mafia"){
                    if(guilty.get_role().get_name() == "Mafia"){ //won't vote against mafia
                        cout << "\e[32mspare\e[0m";
                        spare++;
                    }
                    else{
                        X = rand()%2;
                        if(X == 0){
                            cout << "\e[32mspare\e[0m";
                            spare++;
                        }
                        else{
                            cout << "\e[31mexecute\e[0m";
                            kill++;
                        }
                    }
                }
                else{
                    X = rand()%2;
                    if(X == 0){
                        cout << "\e[32mspare\e[0m";
                        spare++;
                    }
                    else{
                        cout << "\e[31mexecute\e[0m";
                        kill++;
                    }
                }
                cout << endl;
            }
        }
    }

    cout << endl;
    if(spare == kill){ //tie
        cout << "\e[33m The town could not come to a consensus\n\e[32m";
        if(guilty.get_name() == "Player"){cout << "You";}
        else{cout << guilty.get_name();}
        cout << "\e[33m will not be executed\e[0m\n";
    }
    else if(spare > kill){ //spared
        cout << "\e[33m The town has come to a consensus\n\e[32m";
        if(guilty.get_name() == "Player"){cout << "You";}
        else{cout << guilty.get_name();}
        cout << "\e[33m will be spared\e[0m\n";
    }
    else{ //executed
        cout << "\e[33m The town has come to a consensus\e[31m\n";
        if(guilty.get_name() == "Player"){cout << "You"; alive = false;}
        else{cout << guilty.get_name();}
        cout << "\e[33m will be executed immediately\e[0m\n";
        for(size_t i = 0; i < Town.size(); i++){
            if(Town.at(i).get_name() == guilty.get_name()){
                dead.push_back(Town.at(i));
                Town.erase(Town.begin() + i);
                if(guilty.get_role().get_name() == "Fool"){fool = true;}
                if(guilty.get_role().get_name() == "Mafia"){mafia_count--;}
            }
        }
    }

    //check for win
    eval();

    cout << "\n\e[32m [Enter 1 to proceed to night]\e[0m\n -> ";
    cin >> X;
    cout << endl;
    night_count++;
    night();
}

void statement(Person who){
    string what = who.get_role().get_name();
    int X = rand()%5;
    if(night_count == 1){X = rand()%3;}
    //claim role (may be lying or telling truth)
    if(X == 0){
        X = rand()%50;
        if(X == 0){
            cout << "I'm in the Mafia";
            return;
        }
        if(what == "Villager"){
            X = rand()%15;
            if(X == 0){
                cout << "I'm a Doctor";
            }
            else if(X == 1){
                cout << "I'm a Cop";
            }
            else if(X == 2){
                cout << "I'm a Detective";
            }
            else{
                cout << "I'm just a Villager";
            }
        }
        if(what == "Cop"){
            X = rand()%4;
            if(X == 0){
                cout << "I'm a Cop";
            }
            else{
                cout << "I'm just a Villager";
            }
        }
        if(what == "Doctor"){
            X = rand()%4;
            if(X == 0){
                cout << "I'm a Doctor";
            }
            else{
                cout << "I'm just a Villager";
            }
        }
        if(what == "Detective"){
            X = rand()%4;
            if(X == 0){
                cout << "I'm a Detective";
            }
            else{
                cout << "I'm just a Villager";
            }
        }
        if(what == "Fool"){
            X = rand()%4;
            if(X == 0){
                cout << "I'm a Doctor";
            }
            else if(X == 1){
                cout << "I'm a Cop";
            }
            else if(X == 2){
                cout << "I'm a Detective";
            }
            else{
                cout << "I'm just a Villager";
            }
        }
        if(what == "Mafia"){
            X = rand()%7;
            if(X == 0){
                cout << "I'm a Doctor";
            }
            else if(X == 1){
                cout << "I'm a Cop";
            }
            else if(X == 2){
                cout << "I'm a Detective";
            }
            else{
                cout << "I'm just a Villager";
            }
        }
        return;
    }
    
    //detective (50% chance to declare a find (25% chance they lie))
    if(what == "Detective"){
        X = rand()%2;
        if(X == 0){ //will declare a find
            X = rand()%4;
            if(X == 0){ //false declaration
                X = rand() % Town.size();
                cout << Town.at(X).get_name() << " is a ";
                X = rand()%3;
                if(X == 0){cout << "Villager";}
                else if(X == 1){cout << "Fool";}
                else{cout << "Mafia";}
            }
            else{ //true declaration
                if(who.get_role().get_lvl() == 1){
                    X = rand() % (detective1.size());
                    cout << detective1.at(X).get_name() << " is a " << detective1.at(X).get_role().get_name();
                }
                else{
                    X = rand() % (detective2.size());
                    cout << detective2.at(X).get_name() << " is a " << detective2.at(X).get_role().get_name();
                }
            }
            return;
        }
    }
    //doctor (50% chance to say who they saved (25% chance they lie))
    if(what == "Doctor"){
        X = rand()%2;
        if(X == 0){ //will declare a save
            cout << "Last night, I saved ";
            X = rand()%4;
            if(X == 0){ //lie
                X = rand()%Town.size();
                if(who.get_name() == Town.at(X).get_name()){cout << "myself";}
                else{cout << Town.at(X).get_name();}
            }
            else{ //truth
                if(who.get_role().get_lvl() == 1){
                    if(doctor1.get_name() == who.get_name()){cout << "myself";}
                    else{cout << doctor1.get_name();}
                }
                else{
                    if(doctor2.get_name() == who.get_name()){cout << "myself";}
                    else{cout << doctor2.get_name();}
                }
            }
            return;
        }
    }
    //cop (25% chance to threaten)
    if(what == "Cop"){
        X = rand()%4;
        if(X == 0){
            if(who.get_role().get_lvl() == 1){
                if(cop1_bullets != 0){
                    cout << "I still have " << cop1_bullets << " bullets left";
                }
                else{
                    cout << "I have nothing to declare";
                }
            }
            else{
                if(cop2_bullets != 0){
                    cout << "I still have " << cop2_bullets << " bullets left";
                }
                else{
                    cout << "I have nothing to declare";
                }
            }
            return;
        }
    }
    //mafia (40% chance to pretend to be another role)
    if(what == "Mafia"){
        X = rand()%5;
        if(X < 2){ //fake a role
            X = rand()%3;
            if(X == 0){ //doctor
                cout << "Last night, I saved ";
                X = rand()%Town.size();
                if(who.get_name() == Town.at(X).get_name()){cout << "myself";}
                else{cout << Town.at(X).get_name();}
            }
            else if(X == 1){ //cop
                if(cop1_bullets != 0){
                    cout << "I still have " << cop1_bullets << " bullets left";
                }
                else if(cop2_bullets != 0){
                    cout << "I still have " << cop2_bullets << " bullets left";
                }
                else{
                    cout << "I have nothing to declare";
                }
            }
            else{ //detective
                do{
                    X = rand()%Town.size();
                }while(Town.at(X).get_name() == who.get_name());
                cout << Town.at(X).get_name() << " is a ";
                if(Town.at(X).get_role().get_name() == "Mafia"){
                    X = rand()%4;
                    if(X == 0){cout << "Villager";}
                    else if(X == 1){cout << "Cop";}
                    else if(X == 2){cout << "Doctor";}
                    else{cout << "Detective";}
                }
                else{
                    X = rand()%2;
                    if(X == 0){cout << "Villager";}
                    else{cout << "Mafia";}
                }
            }
            return;
        }
    }
    //villager (10% chance to pretend to be another role)
    if(what == "Villager"){
        X = rand()%10;
        if(X == 0){ //fake a role
            X = rand()%3;
            if(X == 0){ //doctor
                cout << "Last night, I saved ";
                X = rand()%Town.size();
                if(who.get_name() == Town.at(X).get_name()){cout << "myself";}
                else{cout << Town.at(X).get_name();}
            }
            else if(X == 1){ //cop
                if(cop1_bullets != 0){
                    cout << "I still have " << cop1_bullets << " bullets left";
                }
                else if(cop2_bullets != 0){
                    cout << "I still have " << cop2_bullets << " bullets left";
                }
                else{
                    cout << "I have nothing to declare";
                }
            }
            else{ //detective
                do{
                    X = rand()%Town.size();
                }while(Town.at(X).get_name() == who.get_name());
                cout << Town.at(X).get_name() << " is a ";
                X = rand()%5;
                if(X == 0){cout << "Villager";}
                else if(X == 1){cout << "Cop";}
                else if(X == 2){cout << "Doctor";}
                else if(X == 3){cout << "Mafia";}
                else{cout << "Detective";}
            }
            return;
        }
    }
    //fool (50% chance to pretend to be another role)
    if(what == "Fool"){
        X = rand()%2;
        if(X == 0){ //fake a role
            X = rand()%3;
            if(X == 0){ //doctor
                cout << "Last night, I saved ";
                X = rand()%Town.size();
                if(who.get_name() == Town.at(X).get_name()){cout << "myself";}
                else{cout << Town.at(X).get_name();}
            }
            else if(X == 1){ //cop
                if(cop1_bullets != 0){
                    cout << "I still have " << cop1_bullets << " bullets left";
                }
                else if(cop2_bullets != 0){
                    cout << "I still have " << cop2_bullets << " bullets left";
                }
                else{
                    cout << "I have nothing to declare";
                }
            }
            else{ //detective
                do{
                    X = rand()%Town.size();
                }while(Town.at(X).get_name() == who.get_name());
                cout << Town.at(X).get_name() << " is a ";
                X = rand()%5;
                if(X == 0){cout << "Villager";}
                else if(X == 1){cout << "Cop";}
                else if(X == 2){cout << "Doctor";}
                else if(X == 3){cout << "Mafia";}
                else{cout << "Detective";}
            }
            return;
        }
    }
    cout << "I have nothing to declare."; //base statement
    return;
}

void defense(Person who){
    string what = who.get_role().get_name();
    int X;
    if(what == "Villager"){
        cout << "I'm innocent, I swear!";
        return;
    }
    if(what == "Cop"){
        X = rand()%2;
        if(X == 0){
            cout << "I'm innocent, I swear!";
        }
        else{
            cout << "Don't do this. I'm a cop!";
        }
        return;
    }
    if(what == "Doctor"){
        X = rand()%2;
        if(X == 0){
            cout << "I'm innocent, I swear!";
        }
        else{
            cout << "I'm a doctor, you need me!";
        }
        return;
    }
    if(what == "Detective"){
        X = rand()%2;
        if(X == 0){
            cout << "I'm innocent, I swear!";
        }
        else{
            cout << "Listen, I'm a detective, don't kill me!";
        }
        return;
    }
    if(what == "Fool"){
        X = rand()%4;
        if(X == 0){
            cout << "I'm innocent, I swear!";
        }
        else if(X == 1){
            cout << "Listen, I'm a detective, don't kill me!";
        }
        else if(X == 2){
            cout << "I'm a doctor, you need me!";
        }
        else{
            cout << "Don't do this. I'm a cop!";
        }
        return;
    }
    if(what == "Mafia"){
        X = rand()%4;
        if(X == 0){
            cout << "I'm innocent, I swear!";
        }
        else if(X == 1){
            cout << "Listen, I'm a detective, don't kill me!";
        }
        else if(X == 2){
            cout << "I'm a doctor, you need me!";
        }
        else{
            cout << "Don't do this. I'm a cop!";
        }
        return;
    }
}

void eval(){
    if(fool){ //fool executed
        cout << "\e[33m  THE FOOL HAS BEEN EXECUTED\n";
        cout << "  GAME OVER\e[0m\n";
        if(Player.get_role().get_name() == "Fool"){
            cout << "\e[32m You Win! \e[0m\n";
        }
        else{
            for(size_t i = 0; i < dead.size(); i++){
                if(dead.at(i).get_role().get_name() == "Fool"){
                    cout << " \e[31m" << dead.at(i).get_name() << " Wins!\e[0m\n";
                }
            }
        }
    }
    else if(mafia_count == 0){ //mafia eliminated
        cout << "\e[33m  THE MAFIA HAVE BEEN ELIMINATED\n";
        cout << "  GAME OVER\e[0m\n";
        if(Player.get_role().get_name() != "Mafia" && Player.get_role().get_name() != "Fool"){
            cout << "\e[32m You Win!\e[0m\n";
        }
        else if(Player.get_role().get_name() == "Mafia"){
            cout << "\e[31m Your team was eliminated. The Village wins!\e[0m\n";
        }
        else{
            cout << "\e[31m You were not executed in court. The Village wins!\e[0m\n";
        }

        cout << "\n\e[33m Mafia members:\e[0m\n";
        for(size_t i = 0; i < dead.size(); i++){
            if(dead.at(i).get_role().get_name() == "Mafia"){
                cout << "\e[31m - \e[0m";
                if(dead.at(i).get_name() == "Player"){cout << "You";}
                else{cout << dead.at(i).get_name();}
                cout << endl;
            }
        }
    }
    else if(mafia_count > (Town.size() / 2)){ //mafia have eliminated enough people
        cout << "\e[33m  THE MAFIA HAVE TAKEN OVER THE VILLAGE\n";
        cout << "  GAME OVER\e[0m\n";
        if(Player.get_role().get_name() == "Mafia"){
            cout << "\e[32m You Win!\e[0m\n";
        }
        else if(Player.get_role().get_name() == "Fool"){
            cout << "\e[31m You were not executed in court. The Mafia win!\e[0m\n";
        }
        else{
            cout << "\e[31m You did not eliminate the Mafia. The Mafia win!\e[0m\n";
        }

        cout << "\n\e[33m Mafia members:\e[0m\n";
        for(size_t i = 0; i < dead.size(); i++){
            if(dead.at(i).get_role().get_name() == "Mafia"){
                cout << "\e[31m - \e[0m";
                if(dead.at(i).get_name() == "Player"){cout << "You";}
                else{cout << dead.at(i).get_name();}
                cout << endl;
            }
        }
        for(size_t i = 0; i < Town.size(); i++){
            if(Town.at(i).get_role().get_name() == "Mafia"){
                cout << "\e[31m - \e[0m";
                if(Town.at(i).get_name() == "Player"){cout << "You";}
                else{cout << Town.at(i).get_name();}
                cout << endl;
            }
        }
    }
    else{return;} //no win

    int X;
    cout << "\n\e[32m [Enter 1 to return to menu]\e[0m\n -> ";
    cin >> X;
    cout << endl;
    menu();
}
