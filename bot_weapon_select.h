//
// JK_Botti - be more human!
//
// bot_weapon_select.h
//

#define NOSKILL 0 // better than best required == N/A

#define SKILL1 1 // best
#define SKILL2 2 
#define SKILL3 3
#define SKILL4 4
#define SKILL5 5 // worst

// waypoint item flags
#define W_IFL_CROWBAR         (1<<0)
#define W_IFL_HANDGRENADE     (1<<1)
#define W_IFL_SNARK           (1<<2)
#define W_IFL_EGON            (1<<3)
#define W_IFL_GAUSS           (1<<4)
#define W_IFL_SHOTGUN         (1<<5)
#define W_IFL_PYTHON          (1<<6)
#define W_IFL_HORNETGUN       (1<<7)
#define W_IFL_MP5             (1<<8)
#define W_IFL_CROSSBOW        (1<<9)
#define W_IFL_RPG             (1<<10)
#define W_IFL_GLOCK           (1<<11)

#define W_IFL_AMMO_GAUSS      (1<<12)
#define W_IFL_AMMO_BUCKSHOT   (1<<13)
#define W_IFL_AMMO_357        (1<<14)
#define W_IFL_AMMO_9MM        (1<<15)
#define W_IFL_AMMO_ARGRENADES (1<<16)
#define W_IFL_AMMO_CROSSBOW   (1<<17)
#define W_IFL_AMMO_RPG        (1<<18)

// weapon types
#define WEAPON_FIRE  (1<<1)
#define WEAPON_MELEE (1<<2)
#define WEAPON_THROW (1<<3)
#define WEAPON_FIRE_ZOOM (WEAPON_FIRE|(1<<4))

typedef struct
{
   int iId;  // the weapon ID value
   char  weapon_name[64];  // name of the weapon when selecting it
   int type;
   
   float aim_speed; // aim speed, 0.0 worst, 1.0 best.
   
   int   primary_skill_level;   // bot skill must be less than or equal to this value
   int   secondary_skill_level; // bot skill must be less than or equal to this value
   qboolean  avoid_this_gun; // bot avoids using this weapon if possible
   qboolean  prefer_higher_skill_attack; // bot uses better of primary and secondary attacks if both avaible
      
   float primary_min_distance;   // 0 = no minimum
   float primary_max_distance;   // 9999 = no maximum
   float secondary_min_distance; // 0 = no minimum    
   float secondary_max_distance; // 9999 = no maximum
   float opt_distance; // optimal distance from target
   
   int   use_percent;   // times out of 100 to use this weapon when available
   qboolean  can_use_underwater;     // can use this weapon underwater
   int   primary_fire_percent;   // times out of 100 to use primary fire
   int   min_primary_ammo;       // minimum ammout of primary ammo needed to fire
   int   min_secondary_ammo;     // minimum ammout of seconday ammo needed to fire
   qboolean  primary_fire_hold;      // hold down primary fire button to use?
   qboolean  secondary_fire_hold;    // hold down secondary fire button to use?
   qboolean  primary_fire_charge;    // charge weapon using primary fire?
   qboolean  secondary_fire_charge;  // charge weapon using secondary fire?
   float primary_charge_delay;   // time to charge weapon
   float secondary_charge_delay; // time to charge weapon
   qboolean  secondary_use_primary_ammo; //does secondary fire use primary ammo?
   int   low_ammo_primary;
   int   low_ammo_secondary;
   
   int  waypoint_flag;
   int  ammo1_waypoint_flag;
   int  ammo2_waypoint_flag;
} bot_weapon_select_t;

typedef struct
{
   int iId;
   float primary_base_delay;
   float primary_min_delay[5];
   float primary_max_delay[5];
   float secondary_base_delay;
   float secondary_min_delay[5];
   float secondary_max_delay[5];
} bot_fire_delay_t;

typedef struct
{
   int waypoint_flag;
   char ammoName[64];
} bot_ammo_names_t;

extern bot_weapon_select_t weapon_select[13];
extern bot_fire_delay_t fire_delay[13];
extern bot_ammo_names_t ammo_names[];

enum ammo_low_t {
   AMMO_NO = 1,
   AMMO_LOW = 2,
   AMMO_OK = 3,
};

extern bot_weapon_select_t * GetWeaponSelect(int id);
extern void InitWeaponSelect(int submod_id);

extern int GetAmmoItemFlag(const char * classname);
extern int GetWeaponItemFlag(const char * classname);
extern qboolean BotCanUseWeapon(bot_t &pBot, const bot_weapon_select_t &select);
extern ammo_low_t BotPrimaryAmmoLow(bot_t &pBot, const bot_weapon_select_t &select);
extern ammo_low_t BotSecondaryAmmoLow(bot_t &pBot, const bot_weapon_select_t &select);
extern void BotSelectAttack(bot_t &pBot, const bot_weapon_select_t &select, qboolean &use_primary, qboolean &use_secondary);
extern qboolean IsValidWeaponChoose(bot_t &pBot, const bot_weapon_select_t &select);
extern qboolean IsValidPrimaryAttack(bot_t &pBot, const bot_weapon_select_t &select, const float distance, const float height, const qboolean always_in_range);
extern qboolean IsValidSecondaryAttack(bot_t &pBot, const bot_weapon_select_t &select, const float distance, const float height, const qboolean always_in_range);
extern qboolean BotGetGoodWeaponCount(bot_t &pBot, const int stop_count);
extern int BotGetLowAmmoFlags(bot_t &pBot);
extern int BotGetBetterWeaponChoice(bot_t &pBot, const bot_weapon_select_t &current, const bot_weapon_select_t *pSelect, const float distance, const float height, qboolean *use_primary, qboolean *use_secondary);
extern qboolean BotAllWeaponsRunningOutOfAmmo(bot_t &pBot);
extern qboolean IsValidToFireAtTheMoment(bot_t &pBot, const bot_weapon_select_t &select);