#include <iostream>
#include <map>
#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#define NO_CORNER -1
#define TOP_LEFT 0
#define BOTTOM_RIGHT 1
using namespace std;

/*
**    clasess
**    |
**    |
**    v
*/

int g_entity_count;
int g_turn;
bool g_defender;
bool g_sync_wind;

class Hero;
class Heroes;
class Monsters;
class Monster;
class Base;
class Isheared;

void    def_farm(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move);
void    off_farm(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move);
void    wait(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move);
void    wind_if_monster_in_base(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move);

class Isheared
{
    public:
        int x;
        int y;
        template<typename T, typename N>
        void    make_vector_of_entity_in_range(vector<T> *entity, vector<N> *vector, int dist);
};

//start point -> F end point -> T store here -> N
template<typename T, typename N>
void    Isheared::make_vector_of_entity_in_range(vector<T> *entity, vector<N> *vector, int dist)
{
    for (auto iter = entity->begin(); iter != entity->end(); iter++)
    {
        int index = distance(entity->begin(), iter);

        int x_delta = (*entity)[index].x - x;
        int y_delta = (*entity)[index].y - y;
        int hip = sqrt(pow(x_delta, 2) + pow(y_delta, 2));

        if (hip < dist)
        {
            N newN((*entity)[index]);
            vector->push_back(newN);
        }
    }
}


class Base: public Isheared
{
    public:
        Base(void)
        {
            cin >> x >> y;
            health = 3;
            cin.ignore();
            if (x == 0 && y == 0)
                corner = TOP_LEFT;
            else
                corner = BOTTOM_RIGHT;
        }
        Base(Base *base)
        {
            if (base->x == 0 && base->y == 0)
            {
                corner = BOTTOM_RIGHT;
                x = 17630;
                y = 9000;
            }
            else
            {
                corner = TOP_LEFT;
                x = 0;
                y = 0;
            }
            health = 0; //default
            mana = 0; //default
        }

        void    update(void);
        void    sort_monsters_by_dist_to_base(Monsters *monsters);
        bool    base_is_clear(void);
        bool    enemy_hero_is_close(Heroes *enemy_heroes);

        bool    corner;//top_left 0 bottom_right 1

        int     health;
        int     mana;

        vector <Monster>    monsters_by_distance;
        vector <Hero>       heroes_by_distnace;

        vector <Monster>    monsters_range_5000;
        vector <Monster>    monsters_range_8000;

        vector <Hero>       heroes_range_5000;
        vector <Hero>       heroes_range_8000;

};

class IEntity: public Isheared
{
    public:
        int id; // Unique identifier
        int type; // 0=monster, 1=your hero, 2=opponent hero
        int shield_life; // Ignore for this league; Count down until shield spell fades
        int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
        int health; // Remaining health of this monster
        int vx; // Trajectory of this monster
        int vy;
        int near_base; // 0=monster with no target yet, 1=monster targeting a base
        int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neithe

        IEntity()
        {

        };
        IEntity(IEntity const & src)
        {
            id = src.id;
            type = src.type;
            x = src.x;
            y = src.y;
            shield_life = src.shield_life; 
            is_controlled = src.is_controlled;
            health = src.health;
            vx = src.vx;
            vy = src.vy;
            near_base = src.near_base;
            threat_for = src.threat_for;
            *this = src;
        };
};

class Entity : public IEntity
{
    public:
        //reades the data for entity and get the distance to base in units
        Entity(Base *base)
        {
            cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; cin.ignore();
        };
        Entity(Entity const & src)
        {
            id = src.id;
            type = src.type;
            x = src.x;
            y = src.y;
            shield_life = src.shield_life; 
            is_controlled = src.is_controlled;
            health = src.health;
            vx = src.vx;
            vy = src.vy;
            near_base = src.near_base;
            threat_for = src.threat_for;
            *this = src;
        };
};

class Monster : public IEntity
{
    public:
        Monster()
        {
    
        };
        ~Monster()
        {
    
        };
        Monster(Entity const & src): IEntity(src)
        {
            is_target = false;          //default
            turns_to_kill = -1;         //default
            turns_till_reach_base = -1; //default
            dist_to_base = -1;          //default
            dist_to_hero = -1;          //default
        };
 
        bool    is_target;
        int     turns_to_kill;
        int     turns_till_reach_base;

        int     dist_to_base;
        int     dist_to_hero;
};

class Monsters
{
    public:
        Monsters()
        {
        };
        ~Monsters()
        {
            monster.clear();
        };

        int     get_monster_pos_in_vec_by_id(int id);
        Monster &get_monster_by_id(int id);
        void    set_is_target_by_id(int id);
        void    set_monsters_by_distane_to_base(Base *base, int distance, vector<pair<int, int>> *id_distance);
        void    set_timer();
        void    clear_controled_monsters();
        bool    is_this_monster_saved(int id);

        vector <Monster> monster;

        int counter;
        vector <Monster> monster_under_controle;
};

class Hero : public IEntity
{
    public:
        Hero()
        {
        };
    
        ~Hero()
        {
        };
        Hero(Entity const & src): IEntity(src)
        {
            has_a_target = false;
            has_a_action = false;
            is_target = false;
            is_covered = false;
        };
        void    set_monster_in_tartget_state(Monsters *monsters);
        void    attack(int x, int y);
        void    cast_wind(int x, int y);
        void    cover(Base *my_base);

        void    make_vector_of_non_shilded_monsters_in_1280(void);
        bool    in_position(int x, int y);
        void    sort_monsters_by_dist_to_hero(Monsters *monsters);

        bool    in_range_of_attack(Monster *monster);//this is optimization function can be sued for latter stuff

        bool    is_attacking(Base &enemy_base);//need to set up a way to postion a hero in a way to be inbetween base and 

        void    patrole_enemy_base(Base *enemy_base);//this is broken code need to rework

        bool    has_a_target;
        bool    has_a_action;

        bool    is_target;
        bool    is_covered;

        int     role;

        vector <Monster>    monsters_by_distance;

        vector <Monster>    monsters_range_1280;
        vector <Monster>    non_shilded_monsters_range_1280;
        vector <Monster>    monsters_range_2200;

        vector <Hero>       heroes_range_1280;
        vector <Hero>       heroes_range_2200;
};

class Heroes
{
    public:
        Heroes()
        {
        };
        ~Heroes()
        {
            hero.clear();
        };

        void    sort_distance_from_bugs(Monsters *monsters);

        Hero    &get_hero_by_id(int id);

        void    patrole(int index, Base *my_base);
        void    attack(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes, vector <Monster> *saved_monsters,  vector <Hero>  *enemy_heroes_controlabe);

        bool    all_heroes_have_target(void);


        void    def_farm(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes);
        vector <Hero> hero;
        int hero_to_move;
};

bool cmp_monster_dist(Monster &a, Monster &b)
{
    return (a.dist_to_hero < b.dist_to_hero);
}

bool cmp_monster_dist_base(Monster &a, Monster &b)
{
    return (a.dist_to_base < b.dist_to_base);
}

bool    cmp_pair(pair <Hero, Monster> &a,
    pair <Hero, Monster> &b)
{
    return (a.second.dist_to_hero < b.second.dist_to_hero);
}

void debug_parced_data(bool debug,
    Base *my_base,
    Base *enemys_base,
    Monsters *monsters,
    Heroes *my_heroes,
    Heroes *enemys_heroes)
{
    if (!debug)
        return;
     assert(my_base->x == 0 && my_base->y == 0
        || my_base->x == 17630 && my_base->y == 9000);
     assert(my_base->health >= 0 || my_base->health < 4);
     assert(enemys_base->x == 0 && enemys_base->y == 0
        || enemys_base->x == 17630 && enemys_base->y == 9000);
     assert(enemys_base->health >= 0 || enemys_base->health < 4);

    for (auto iter = monsters->monster.begin(); iter != monsters->monster.end(); iter++)
    {
        int index = distance(monsters->monster.begin(), iter);

        assert(monsters->monster[index].id >= 0);
        assert(monsters->monster[index].type == 0);

        assert(monsters->monster[index].health >= -1);
        assert(monsters->monster[index].near_base >= -1 || monsters->monster[index].near_base <= 1);
        assert(monsters->monster[index].threat_for >= -1 && monsters->monster[index].threat_for <= 2);
    }
    for (auto iter = my_heroes->hero.begin(); iter != my_heroes->hero.end(); iter++)
    {
        int index = distance(my_heroes->hero.begin(), iter);

        assert(my_heroes->hero[index].id >= 0);
        assert(my_heroes->hero[index].type == 1);

        assert(my_heroes->hero[index].health >= -1);
        assert(my_heroes->hero[index].near_base >= -1);
        assert(my_heroes->hero[index].threat_for >= -1);
    }
    for (auto iter = enemys_heroes->hero.begin(); iter != enemys_heroes->hero.end(); iter++)
    {
        int index = distance(enemys_heroes->hero.begin(), iter);

        assert(enemys_heroes->hero[index].id >= 0);
        assert(enemys_heroes->hero[index].type == 2);

        assert(enemys_heroes->hero[index].health >= -1);
        assert(enemys_heroes->hero[index].near_base >= -1);
        assert(enemys_heroes->hero[index].threat_for >= -1);
    }

    assert(my_base->mana >= 0);
    assert(enemys_base->mana >= 0);
    return ;
}
void    Base::update(void)
{
    cin >> health >> mana; cin.ignore();
}


void    wait(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move)
{
    cout << "WAIT" << " Wait " << endl;
    hero_to_move.has_a_action = true;
}

/*
**    ^
**    |
**    |
**    clasess
*/

void    Hero::sort_monsters_by_dist_to_hero(Monsters *monsters)
{
    for (auto iter = monsters->monster.begin(); iter != monsters->monster.end(); iter++)
    {
        int index = distance(monsters->monster.begin(), iter);

        int x_delta = monsters->monster[index].x - x;
        int y_delta = monsters->monster[index].y - y;
        int hip = sqrt(pow(x_delta, 2) + pow(y_delta, 2));

        Monster monster(monsters->monster[index]);
        monster.dist_to_hero = hip;
        monsters_by_distance.push_back(monster);
    }
    sort(monsters_by_distance.begin(), monsters_by_distance.end(), cmp_monster_dist);
}

void    Base::sort_monsters_by_dist_to_base(Monsters *monsters)
{
    for (auto iter = monsters->monster.begin(); iter != monsters->monster.end(); iter++)
    {
        int index = distance(monsters->monster.begin(), iter);

        int x_delta = monsters->monster[index].x - x;
        int y_delta = monsters->monster[index].y - y;
        int hip = sqrt(pow(x_delta, 2) + pow(y_delta, 2));

        Monster monster(monsters->monster[index]);
        monster.dist_to_base = hip;
        monsters_by_distance.push_back(monster);
    }
    sort(monsters_by_distance.begin(), monsters_by_distance.end(), cmp_monster_dist_base);
}

void    Monsters::set_timer()
{
    if (!this->monster_under_controle.empty() && this->counter == 0)
    {
        this->counter = 10;
        cerr << "timer set" << endl;
    }
}
void    Monsters::clear_controled_monsters()
{
    if (this->counter <= 0 && !this->monster_under_controle.empty())
    {
        this->monster_under_controle.clear();
        this->counter = 0;
        cerr << "cleared" << endl;
    }
    else if (!this->monster_under_controle.empty() && this->counter > 0)
    {
        this->counter--;
    }
}

bool    Monsters::is_this_monster_saved(int id)
{
    for (auto iter = this->monster_under_controle.begin(); iter != this->monster_under_controle.end(); iter++)
    {
        int index = distance(this->monster_under_controle.begin(), iter);

        if (id == this->monster_under_controle[index].id)
            return (true);
    }
    return (false);
}
Monster    &Monsters::get_monster_by_id(int id)
{
    int index;
    
    assert(id > 5);
    assert(!monster.empty());

    auto iter = monster.begin();
    for (iter; iter != monster.end(); iter++)
    {
        index = distance(monster.begin(), iter);

        if (id == monster[index].id)
            break ;
    }
    assert(iter != monster.end());
    return (monster[index]);
}

Hero    &Heroes::get_hero_by_id(int id)
{
    int index;

    index = 0;
    assert(id >= 0 && id <= 5);
    for (auto iter = hero.begin(); iter != hero.end(); iter++)
    {
        index = distance(hero.begin(), iter);

        if (hero[index].id == id)
            return (hero[index]);
    }
    assert(index == 0);
    return (hero[0]);
}

void    Hero::make_vector_of_non_shilded_monsters_in_1280(void)
{
    for (auto iter = monsters_range_1280.begin(); iter != monsters_range_1280.end(); iter++)
    {
        int index = distance(monsters_range_1280.begin(), iter);

        if (monsters_range_1280[index].shield_life == 0)
        {
            Monster monster(monsters_range_1280[index]);

            non_shilded_monsters_range_1280.push_back(monster);
        }
    }
}


void    init_heros_monsters(Heroes *my_heroes,
    Heroes *enemys_heroes,
    Monsters *monsters,
    Base *my_base)
{
    cin >> g_entity_count; cin.ignore();

    for (int index = 0; index < g_entity_count; index++)
    {
        Entity tmp_entity(my_base);

        if (tmp_entity.type == 1)
        {
            Hero tmp_my_hero(tmp_entity);

            my_heroes->hero.push_back(tmp_my_hero);
        }
        if (tmp_entity.type == 2)
        {
            Hero tmp_enemy_hero(tmp_entity);
            enemys_heroes->hero.push_back(tmp_enemy_hero);
        }
        if (tmp_entity.type == 0)
        {
            Monster tmp_monster(tmp_entity);
            monsters->monster.push_back(tmp_monster);
        }
    }
}

void    off_farm(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move)
{
    vector <Monster> target;
    vector <pair <Hero, Monster>> match;

    //try to get the 3 closest monsters
    for (auto iter = enemy_base->monsters_by_distance.begin(); iter != enemy_base->monsters_by_distance.end(); iter++)
    {
        int index = distance(enemy_base->monsters_by_distance.begin(), iter);

        target.push_back(enemy_base->monsters_by_distance[index]);
        if (index == 2)
            break ;
    }
    //makes one big pair with heros and mosters
    for (auto iter = my_heroes->hero.begin(); iter != my_heroes->hero.end(); iter++)
    {
        int index = distance(my_heroes->hero.begin(), iter);

        for (auto iter_2 = my_heroes->hero[index].monsters_by_distance.begin(); iter_2 != my_heroes->hero[index].monsters_by_distance.end(); iter_2++)
        {
            int index_2 = distance(my_heroes->hero[index].monsters_by_distance.begin(), iter_2);

            match.push_back(pair(my_heroes->hero[index], my_heroes->hero[index].monsters_by_distance[index_2]));
        }
    }
    sort(match.begin(), match.end(), cmp_pair);
    //so can we loop threw all the matches till every one has a
    //goes throw all the heros and monsters to see who is the best match
    //so this loop get the closest monster to hero and base if it is nit a target and matches hero_to_move id
    for (auto iter = target.begin(); iter != target.end(); iter++)
    {
        int index = distance(target.begin(), iter);

        for (auto iter_2 = match.begin(); iter_2 != match.end(); iter_2++)
        {
            int index_2 = distance(match.begin(), iter_2);

            Monster &monster = monsters->get_monster_by_id(match[index_2].second.id);
            Hero &hero = my_heroes->get_hero_by_id(match[index_2].first.id);

            if (target[index].id == match[index_2].second.id
                && monster.is_target == false
                && hero.has_a_target == false
                && hero.has_a_action == false
                && hero.id == hero_to_move.id
                && !monsters->is_this_monster_saved(monster.id)
                && !monster.is_controlled)
            {
                //cerr << " GET A MOVE match hero id: " << hero.id << " monster match id: " << monster.id << "  hero to move id: " << my_heroes->hero[0].id << endl;
                cout << "MOVE " << monster.x << " " << monster.y << " F " << monster.id << endl;
                monster.is_target = true;
                hero.has_a_target = true;
                hero.has_a_action = true;
                return ;
            }
        }
    }
}

//improve this one
void   wind_if_monster_in_base(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move)
{
    if (!my_base->monsters_range_5000.empty())
    {
       if (!hero_to_move.non_shilded_monsters_range_1280.empty() && my_base->mana >= 10) 
       {
           my_base->mana -= 10;
           cout << "SPELL WIND " << enemy_base->x << " " << enemy_base->y << " new wind " << endl;
           hero_to_move.has_a_action = true;
           g_defender = true;
       }
    }
}
void (*p[5]) (Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_mov);

void   farm(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move)
{
    if (!hero_to_move.monsters_range_2200.empty())
    {

    }
}
void   position(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move)
{
    if (my_base->corner == TOP_LEFT)
    {
        if (hero_to_move.id == 0)
            cout << "MOVE 7842 1683" << endl;
        if (hero_to_move.id == 1)
            cout << "MOVE 5555 5555" << endl;
        if (hero_to_move.id == 2)
            cout << "MOVE 3100 8000" << endl;
        hero_to_move.has_a_action = true;
    }
    else
    {
        if (hero_to_move.id == 3)
            cout << "MOVE 15500 2000" << endl;
        if (hero_to_move.id == 4)
            cout << "MOVE 10000 7300" << endl;
        if (hero_to_move.id == 5)
            cout << "MOVE 12366 4200" << endl;
        hero_to_move.has_a_action = true;
    }
}

void   get_in_to_attack_radius_of_monster_800(Base *my_base, Base *enemy_base, Monsters *monsters, Heroes *enemy_heroes,Heroes *my_heroes, Hero &hero_to_move)
{
    for (auto iter = hero_to_move.monsters_range_2200.begin(); iter != hero_to_move.monsters_range_2200.end(); iter++)
    {
        int index = distance(hero_to_move.monsters_range_2200.begin(), iter);

        // if there are no monsters positoin so that you are 5000 + 1200 from base and the monster
        // if monster comes with in 6200 attack it directly or wind it back or chang its curse
    }
}
void    enter_behaviour_tree(Base *my_base, Base *enemy_base, Monsters *Monsters, Heroes *enemy_heroes, Heroes *my_heroes)
{
    Hero    &hero_to_move = my_heroes->hero[my_heroes->hero_to_move];
    int     index = 0;

    p[0] = position;
    p[1] = get_in_to_attack_radius_of_monster_800;
    p[2] = wait;
 //   p[0] = farm;
 //   p[1] = wait;
    while (hero_to_move.has_a_action == false)
    {
        p[index](my_base, enemy_base, Monsters, enemy_heroes, my_heroes, hero_to_move);
        index++;
    }
    my_heroes->hero_to_move++;
}

int main()
{
    Base                my_base;
    Base                enemy_base(&my_base);
    
    Heroes              my_heroes;
    Heroes              enemy_heroes;
    Monsters            monsters;

    int                 heroes_per_player;

    cin >> heroes_per_player; cin.ignore();

    while (1)
    {
        g_turn++;
        my_base.update();
        enemy_base.update();
        init_heros_monsters(&my_heroes, &enemy_heroes, &monsters, &my_base);
        debug_parced_data(true, &my_base, &enemy_base, &monsters, &my_heroes, &enemy_heroes);

        monsters.set_timer();
        for (int i = 0; i < heroes_per_player; i++)
        {
            cerr << i << endl;
            my_heroes.hero[i].sort_monsters_by_dist_to_hero(&monsters);
            my_heroes.hero[i].make_vector_of_entity_in_range(&monsters.monster, &my_heroes.hero[i].monsters_range_1280, 1279);
            my_heroes.hero[i].make_vector_of_entity_in_range(&monsters.monster, &my_heroes.hero[i].monsters_range_2200, 2199);
            my_heroes.hero[i].make_vector_of_entity_in_range(&enemy_heroes.hero, &my_heroes.hero[i].heroes_range_1280, 1279);
            my_heroes.hero[i].make_vector_of_entity_in_range(&enemy_heroes.hero, &my_heroes.hero[i].heroes_range_2200, 2199);
            my_heroes.hero[i].make_vector_of_non_shilded_monsters_in_1280();

            if (enemy_heroes.hero.size() > i)
            {
                enemy_heroes.hero[i].sort_monsters_by_dist_to_hero(&monsters);
                enemy_heroes.hero[i].make_vector_of_entity_in_range(&monsters.monster, &enemy_heroes.hero[i].monsters_range_1280, 1279);
                enemy_heroes.hero[i].make_vector_of_entity_in_range(&monsters.monster, &enemy_heroes.hero[i].monsters_range_2200, 2199);
                enemy_heroes.hero[i].make_vector_of_entity_in_range(&my_heroes.hero, &enemy_heroes.hero[i].heroes_range_1280, 1279);
                enemy_heroes.hero[i].make_vector_of_entity_in_range(&my_heroes.hero, &enemy_heroes.hero[i].heroes_range_2200, 2199);
                enemy_heroes.hero[i].make_vector_of_non_shilded_monsters_in_1280();
            }
        }
        my_base.sort_monsters_by_dist_to_base(&monsters);
        my_base.make_vector_of_entity_in_range(&monsters.monster, &my_base.monsters_range_5000, 5000);
        my_base.make_vector_of_entity_in_range(&monsters.monster, &my_base.monsters_range_8000, 8000);
        my_base.make_vector_of_entity_in_range(&enemy_heroes.hero, &my_base.heroes_range_5000, 5000);
        my_base.make_vector_of_entity_in_range(&enemy_heroes.hero, &my_base.heroes_range_8000, 8000);
        enemy_base.sort_monsters_by_dist_to_base(&monsters);
        enemy_base.make_vector_of_entity_in_range(&monsters.monster, &enemy_base.monsters_range_5000, 5000);
        enemy_base.make_vector_of_entity_in_range(&monsters.monster, &enemy_base.monsters_range_8000, 8000);
        enemy_base.make_vector_of_entity_in_range(&enemy_heroes.hero, &enemy_base.heroes_range_5000, 5000);
        enemy_base.make_vector_of_entity_in_range(&enemy_heroes.hero, &enemy_base.heroes_range_8000, 8000);
        for (int i = 0; heroes_per_player > i; i++)
            enter_behaviour_tree(&my_base, &enemy_base, &monsters, &enemy_heroes, &my_heroes);

        my_base.heroes_by_distnace.clear();
        my_base.heroes_range_5000.clear();
        my_base.heroes_range_8000.clear();
        my_base.monsters_range_8000.clear();
        my_base.monsters_range_5000.clear();
        my_base.monsters_by_distance.clear();
        enemy_base.heroes_by_distnace.clear();
        enemy_base.heroes_range_5000.clear();
        enemy_base.heroes_range_8000.clear();
        enemy_base.monsters_range_8000.clear();
        enemy_base.monsters_range_5000.clear();
        enemy_base.monsters_by_distance.clear();
    
        monsters.monster.clear();
        for (int i = 0; i < 3; i++)
        {
            my_heroes.hero[i].heroes_range_1280.clear();
            my_heroes.hero[i].heroes_range_2200.clear();
            my_heroes.hero[i].monsters_range_2200.clear();
            my_heroes.hero[i].monsters_range_1280.clear();
            my_heroes.hero[i].monsters_by_distance.clear();
            my_heroes.hero[i].non_shilded_monsters_range_1280.clear();
            my_heroes.hero[i].has_a_action = false;
            my_heroes.hero[i].has_a_target = false;
            my_heroes.hero[i].is_target = false;
            my_heroes.hero[i].is_covered = false;
            if (enemy_heroes.hero.size() > i)
            {
                enemy_heroes.hero[i].heroes_range_1280.clear();
                enemy_heroes.hero[i].heroes_range_2200.clear();
                enemy_heroes.hero[i].monsters_range_2200.clear();
                enemy_heroes.hero[i].monsters_range_1280.clear();
                enemy_heroes.hero[i].monsters_by_distance.clear();
                enemy_heroes.hero[i].non_shilded_monsters_range_1280.clear();
                enemy_heroes.hero[i].has_a_action = false;
                enemy_heroes.hero[i].has_a_target = false;
                enemy_heroes.hero[i].is_target = false;
                enemy_heroes.hero[i].is_covered = false;
            }
        }
        my_heroes.hero_to_move = 0;
    }
}
