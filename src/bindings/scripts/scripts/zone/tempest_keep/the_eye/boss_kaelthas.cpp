/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: boss_Kaelthas
SD%Complete: 60
SDComment: Mind Control, Reset Event if Weapons despawn/reset
SDCategory: Tempest Keep, The Eye
EndScriptData */

#include "precompiled.h"
#include "def_the_eye.h"
#include "WorldPacket.h"

//kael'thas Speech
#define SAY_INTRO                         -1550016
#define SAY_INTRO_CAPERNIAN               -1550017
#define SAY_INTRO_TELONICUS               -1550018
#define SAY_INTRO_THALADRED               -1550019
#define SAY_INTRO_SANGUINAR               -1550020
#define SAY_PHASE2_WEAPON                 -1550021
#define SAY_PHASE3_ADVANCE                -1550022
#define SAY_PHASE4_INTRO2                 -1550023
#define SAY_PHASE5_NUTS                   -1550024
#define SAY_SLAY1                         -1550025
#define SAY_SLAY2                         -1550026
#define SAY_SLAY3                         -1550027
#define SAY_MINDCONTROL1                  -1550028
#define SAY_MINDCONTROL2                  -1550029
#define SAY_GRAVITYLAPSE1                 -1550030
#define SAY_GRAVITYLAPSE2                 -1550031
#define SAY_SUMMON_PHOENIX1               -1550032
#define SAY_SUMMON_PHOENIX2               -1550033
#define SAY_DEATH                         -1550034

//Thaladred the Darkener speech
#define SAY_THALADRED_AGGRO               -1550035
#define SAY_THALADRED_DEATH               -1550036
#define EMOTE_THALADRED_GAZE              -1550037

//Lord Sanguinar speech
#define SAY_SANGUINAR_AGGRO               -1550038
#define SAY_SANGUINAR_DEATH               -1550039

//Grand Astromancer Capernian speech
#define SAY_CAPERNIAN_AGGRO               -1550040
#define SAY_CAPERNIAN_DEATH               -1550041

//Master Engineer Telonicus speech
#define SAY_TELONICUS_AGGRO               -1550042
#define SAY_TELONICUS_DEATH               -1550043

//Phase 2 spells (Not used)
#define SPELL_SUMMON_WEAPONS              36976
#define SPELL_SUMMON_WEAPONA              36958
#define SPELL_SUMMON_WEAPONB              36959
#define SPELL_SUMMON_WEAPONC              36960
#define SPELL_SUMMON_WEAPOND              36961
#define SPELL_SUMMON_WEAPONE              36962
#define SPELL_SUMMON_WEAPONF              36963
#define SPELL_SUMMON_WEAPONG              36964
#define SPELL_RES_VISUAL                  24171
#define SPELL_WEAPON_SPAWN                41236

//Phase 4 spells
#define SPELL_FIREBALL                    36805
#define SPELL_PYROBLAST                   36819
#define SPELL_FLAME_STRIKE                36735
#define SPELL_FLAME_STRIKE_VIS            36730
#define	SPELL_BANISH					  35182
#define SPELL_FLAME_STRIKE_DMG            36731
#define SPELL_ARCANE_DISRUPTION           36834
#define SPELL_SHOCK_BARRIER               36815
#define SPELL_SUMMON_PHOENIX              36723
#define SPELL_MIND_CONTROL                32830

//Phase 5 spells
#define SPELL_NETHERBEAM_EXPLODE          36089
#define SPELL_NETHERBEAM                  36090
#define SPELL_NETHERBEAM_GLOW1            36364
#define SPELL_NETHERBEAM_GLOW2            36370
#define SPELL_NETHERBEAM_GLOW3            36371
#define SPELL_GAINING_POWER               36091
#define SPELL_EXPLODE                     36092
#define SPELL_FULLPOWER                   36187
#define SPELL_KNOCKBACK                   11027
#define SPELL_GRAVITY_LAPSE               34480
#define SPELL_GRAVITY_LAPSE_AURA          39432
#define SPELL_NETHER_BEAM                 35873
#define SPELL_EXPLODE_SHAKE1              36373
#define SPELL_EXPLODE_SHAKE2              36375
#define SPELL_EXPLODE_SHAKE3              36354
#define SPELL_EXPLODE_SHAKE4              36376

//Thaladred the Darkener spells
#define SPELL_PSYCHIC_BLOW                10689
#define SPELL_SILENCE                     30225
#define SPELL_REND                        36965

//Lord Sanguinar spells
#define SPELL_BELLOWING_ROAR              40636

//Grand Astromancer Capernian spells
#define CAPERNIAN_DISTANCE                20                //she casts away from the target
#define SPELL_CAPERNIAN_FIREBALL          36971
#define SPELL_CONFLAGRATION               37018
#define SPELL_ARCANE_EXPLOSION            36970

//Master Engineer Telonicus spells
#define SPELL_BOMB                        37036
#define SPELL_REMOTE_TOY                  37027

//Nether Vapor spell
#define SPELL_NETHER_VAPOR                35858  //trigger for 35859
#define SPELL_SUMMON_NETHER_VAPOR         35865

//Phoenix spell
#define SPELL_BURN                        36720
#define SPELL_EMBER_BLAST                 34341
#define SPELL_REBIRTH                     41587

//Creature IDs
#define NETHER_VAPOR_CLOUD                21002
#define PHOENIX                           21362
#define PHOENIX_EGG                       21364

//Phoenix egg and phoenix model
#define PHOENIX_MODEL                     19682
#define PHOENIX_EGG_MODEL                 20245

//weapon id + position
float KaelthasWeapons[7][5] =
{
    {21270, 794.38, 15, 48.72, 2.9},                        //[Cosmic Infuser]
    {21269, 785.47, 12.12, 48.72, 3.14},                    //[Devastation]
    {21271, 781.25, 4.39, 48.72, 3.14},                     //[Infinity Blade]
    {21273, 777.38, -0.81, 48.72, 3.06},                    //[Phaseshift Bulwark]
    {21274, 781.48, -6.08, 48.72, 3.9},                     //[Staff of Disintegration]
    {21272, 785.42, -13.59, 48.72, 3.4},                    //[Warp Slicer]
    {21268, 793.06, -16.61, 48.72, 3.10}                    //[Netherstrand Longbow]
};

#define GRAVITY_X 795.0f
#define GRAVITY_Y 0.0f
#define GRAVITY_Z 70.0f

#define TIME_PHASE_2_3			125000 // Phase 2 ends approximately 2 minutes and 5 seconds after it begins
#define TIME_PHASE_3_4			180000 // Phase 3 ends approximately 3 minutes after it begins

#define KAEL_VISIBLE_RANGE  50.0f
#define ROOM_BASE_Z 49.0f

// Netherstrand Longbow spells
#define SPELL_BOW_MULTISHOOT    36979  // multi-shot
#define SPELL_BOW_SHOOT         36980  // normal range shot
#define SPELL_BOW_BLINK         36994  // blink 

// Devastation
#define SPELL_DEVASTATION_WW    36981  // Whirlwind

// Warp Slicer                
#define SPELL_WARP_REND         36991  // rend

// Cosmic Infuser
#define SPELL_INFUSER_HEAL      36983  // heal spell
#define SPELL_INFUSER_HNOVA     36985  // holy nova

// Infinity Blade
#define SPELL_BLADE_TRASH       3391  // 2 extra attacks

// Phaseshift Bulwark
#define SPELL_BULWARK_SBASH     36988 // shield bash
#define SPELL_BULWARK_SSPIKE    37016 // shield spike

// Staff of Disintegration
#define SPELL_STAFF_FNOVA       36989 // frost nova
#define SPELL_STAFF_WBOLT       36990 // frostbolt

// Advisors hp
#define HP_THALADRED    279999
#define HP_SANGUINAR    289999
#define HP_CAPERNIAN    199999
#define HP_TELONICUS    274999

//Base AI for Advisors
struct TRINITY_DLL_DECL advisorbase_ai : public ScriptedAI
{
    advisorbase_ai(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
    }

    ScriptedInstance* pInstance;
    bool SetHP;

    void Reset()
    {
        m_creature->setActive(true);
        m_creature->SetNoCallAssistance(true);

        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        m_creature->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
        m_creature->ApplySpellImmune(1, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, true);

        //reset encounter
        if(pInstance && (pInstance->GetData(DATA_KAELTHASEVENT) == 1 || pInstance->GetData(DATA_KAELTHASEVENT) == 3))
        {
            if(Creature *Kaelthas = (Creature*)Unit::GetUnit((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
                Kaelthas->AI()->EnterEvadeMode();
        }

        UpdateMaxHealth(false);
    }

    void MoveInLineOfSight(Unit *who)
    {
        if(!who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        ScriptedAI::MoveInLineOfSight(who);
    }

    void AttackStart(Unit* who)
    {
        if (!who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        ScriptedAI::AttackStart(who);
    }

    void Revive()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetHealth(m_creature->GetMaxHealth());
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, PLAYER_STATE_NONE);
        m_creature->setDeathState(ALIVE);
        DoCast(m_creature, SPELL_RES_VISUAL, false);

        DoZoneInCombat(); // So we have now new shiny target list ;]

        if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0, 200, true))
        {
            m_creature->GetMotionMaster()->MoveChase(target);
            m_creature->AI()->AttackStart(target);
        }
        else
            m_creature->GetMotionMaster()->Initialize();
    }

    void UpdateMaxHealth(bool twice)
    {
        if(m_creature->GetGUID() == pInstance->GetData64(DATA_LORDSANGUINAR))
            m_creature->SetMaxHealth(twice ? HP_SANGUINAR*2 : HP_SANGUINAR);

        if(m_creature->GetGUID() == pInstance->GetData64(DATA_GRANDASTROMANCERCAPERNIAN))
            m_creature->SetMaxHealth(twice ? HP_CAPERNIAN*2 : HP_CAPERNIAN);

        if(m_creature->GetGUID() == pInstance->GetData64(DATA_MASTERENGINEERTELONICUS))
            m_creature->SetMaxHealth(twice ? HP_TELONICUS*2 : HP_TELONICUS);

        if (m_creature->GetGUID() == pInstance->GetData64(DATA_THALADREDTHEDARKENER))
            m_creature->SetMaxHealth(twice ? HP_THALADRED*2 : HP_THALADRED);
    }

    void DamageTaken(Unit* pKiller, uint32 &damage)
    {
        if(damage >= m_creature->GetHealth())
        {
            //Don't really die in phase 1 & 3, only die after that
            if(pInstance && pInstance->GetData(DATA_KAELTHASEVENT) != 0)
            {
                damage = 0;

                m_creature->InterruptNonMeleeSpells(true);
                m_creature->RemoveAllAuras();
                m_creature->SetHealth(0);
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MoveIdle();
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1,PLAYER_STATE_DEAD);
            
                UpdateMaxHealth(true);

                /*if(pInstance->GetData(DATA_KAELTHASEVENT) == 4)		// phase 3 = phase 4, to discriminate phase 3 state from DONE
                    JustDied(pKiller);*/
            }
        }
    }
};

//Kael'thas AI
struct TRINITY_DLL_DECL boss_kaelthasAI : public ScriptedAI
{
    boss_kaelthasAI(Creature *c) : ScriptedAI(c), summons(m_creature)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        m_creature->GetPosition(wLoc);

        for(int i = 0; i < 4; i++)
            AdvisorGuid[i] = 0;

        // check if not source of Kael bugging from time to time
        /*SpellEntry *TempSpell = (SpellEntry*)GetSpellStore()->LookupEntry(SPELL_PYROBLAST);
        if(TempSpell)
        {
            TempSpell->EffectImplicitTargetA[0] = TARGET_UNIT_TARGET_ENEMY;
            TempSpell->EffectImplicitTargetB[0] = 0;
        }*/
    }

    ScriptedInstance* pInstance;

    uint32 Fireball_Timer;
    uint32 Visual_Timer;
    uint32 Arcane_Timer1;
    uint32 Arcane_Timer2;
    uint32 ShockPyroChain_Timer;
    uint32 ShockBarrier_Timer;
    uint32 Pyro_Timer;
    uint32 GravityLapse_Timer;
    uint32 GravityLapse_Phase;
    uint32 NetherBeam_Timer;
    uint32 Kick_Timer;
    uint32 FlameStrike_Timer;
    uint32 MindControl_Timer;
    uint32 Phoenix_Timer;
    uint32 Check_Timer;
    uint32 Phase;
    uint32 PhaseSubphase;                                   //generic
    uint32 Phase_Timer;                                     //generic timer
    uint32 PyrosCasted;
    uint32 Check_Timer2;
    uint32 Anim_Timer;
    uint32 Step;

    WorldLocation wLoc;

    bool Arcane1;
    bool Arcane2;
    bool MC_Done;
    bool InGravityLapse;
    bool IsCastingFireball;
    bool ChainPyros;
    bool reset;

    uint64 AdvisorGuid[4];
    uint64 WeaponGuid[7];
    SummonList summons;

    void DeleteLegs()
    {
        InstanceMap::PlayerList const &playerliste = ((InstanceMap*)m_creature->GetMap())->GetPlayers();
        InstanceMap::PlayerList::const_iterator it;

        Map::PlayerList const &PlayerList = ((InstanceMap*)m_creature->GetMap())->GetPlayers();
        for(Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
        {
            Player* i_pl = i->getSource();
            i_pl->DestroyItemCount(30312, 1, true);
            i_pl->DestroyItemCount(30311, 1, true);
            i_pl->DestroyItemCount(30317, 1, true);
            i_pl->DestroyItemCount(30316, 1, true);
            i_pl->DestroyItemCount(30313, 1, true);
            i_pl->DestroyItemCount(30314, 1, true);
            i_pl->DestroyItemCount(30318, 1, true);
            i_pl->DestroyItemCount(30319, 1, true);
            i_pl->DestroyItemCount(30320, 1, true);
        }
    }

    void Reset()
    {
        m_creature->SetNoCallAssistance(true);
        Fireball_Timer = 5000+rand()%10000;
        Arcane_Timer1 = 20000;
        Arcane_Timer2 = 40000;
        MindControl_Timer = 10000;
        Phoenix_Timer =50000;
        ShockPyroChain_Timer = 60000;
        PyrosCasted = 0;
        Pyro_Timer = 0;
        ShockBarrier_Timer = 60000;
        FlameStrike_Timer = 29000;
        GravityLapse_Timer = 20000;
        GravityLapse_Phase = 0;
        NetherBeam_Timer = 8000;
        Kick_Timer = 3000;
        Check_Timer = 4000;
        Check_Timer2 = 3000;
        PyrosCasted = 0;
        Phase = 0;
        Anim_Timer = 0;
        Step = 0;
        Arcane1 = false;
        Arcane2 = false;
        MC_Done = false;
        InGravityLapse = false;
        IsCastingFireball = false;
        ChainPyros = false;
        reset = true;

        DeleteLegs();
        summons.DespawnAll();

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
        m_creature->Relocate(GRAVITY_X, GRAVITY_Y, ROOM_BASE_Z, 3.14f);

        m_creature->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
        m_creature->ApplySpellImmune(1, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, true);
        m_creature->ApplySpellImmune(2, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);

        if(pInstance)
            pInstance->SetData(DATA_KAELTHASEVENT, NOT_STARTED);
            pInstance->SetData(DATA_EXPLODE, false);
    }

    void PrepareAdvisors()
    {
        for(uint8 i = 0; i < 4; ++i)
        {
            if(Creature *pCreature = (Creature*)Unit::GetUnit((*m_creature), AdvisorGuid[i]))
            {
                pCreature->Respawn();
                pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                pCreature->setFaction(m_creature->getFaction());
                pCreature->AI()->EnterEvadeMode();
            }
        }
    }

    void StartEvent()
    {
        if(!pInstance)
            return;

        AdvisorGuid[0] = pInstance->GetData64(DATA_THALADREDTHEDARKENER);
        AdvisorGuid[1] = pInstance->GetData64(DATA_LORDSANGUINAR);
        AdvisorGuid[2] = pInstance->GetData64(DATA_GRANDASTROMANCERCAPERNIAN);
        AdvisorGuid[3] = pInstance->GetData64(DATA_MASTERENGINEERTELONICUS);

        if(!AdvisorGuid[0] || !AdvisorGuid[1] || !AdvisorGuid[2] || !AdvisorGuid[3])
        {
            error_log("TSCR: Kael'Thas One or more advisors missing, Skipping Phases 1-3");
            DoYell("TSCR: Kael'Thas One or more advisors missing, Skipping Phases 1-3", LANG_UNIVERSAL, NULL);

            DoScriptText(SAY_PHASE4_INTRO2, m_creature);
            Phase = 4;

            pInstance->SetData(DATA_KAELTHASEVENT, 4);

            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if(Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                AttackStart(target);
            }
        else
        {
            PrepareAdvisors();
            DeleteLegs();

            DoScriptText(SAY_INTRO, m_creature);

            pInstance->SetData(DATA_KAELTHASEVENT, IN_PROGRESS);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            PhaseSubphase = 0;
            Phase_Timer = 23000;
            Phase = 1;
        }
    }
    void MoveInLineOfSight(Unit *who)
    {
        if (!m_creature->hasUnitState(UNIT_STAT_STUNNED) && who->isTargetableForAttack() &&
            m_creature->IsHostileTo(who))
        {
            if (!m_creature->canFly() && m_creature->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                return;

            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->IsWithinLOSInMap(who))
            {
                if (!m_creature->getVictim() && Phase >= 4)
                {
                    who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
                    AttackStart(who);
                }
                else if (m_creature->GetMap()->IsDungeon())
                {
                    if (pInstance && !pInstance->GetData(DATA_KAELTHASEVENT) && !Phase)
                        StartEvent();

                    who->SetInCombatWith(m_creature);
                    m_creature->AddThreat(who, 0.0f);
                }
            }
        }
    }

    void Aggro(Unit *who)
    {
        if (pInstance && !pInstance->GetData(DATA_KAELTHASEVENT) && !Phase)
            StartEvent();
    }

    void KilledUnit()
    {
        switch(rand()%3)
        {
        case 0: DoScriptText(SAY_SLAY1, m_creature); break;
        case 1: DoScriptText(SAY_SLAY2, m_creature); break;
        case 2: DoScriptText(SAY_SLAY3, m_creature); break;
        }
    }

    void JustSummoned(Creature* summoned)
    {
        if(summoned->GetEntry() == PHOENIX)
        {
            summoned->setFaction(m_creature->getFaction());
            Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0);
            if(target)
            {
                summoned->setActive(true);
                summoned->AI()->AttackStart(target);
            }
        }
        summons.Summon(summoned);
    }

    void SummonedCreatureDespawn(Creature *summon) {summons.Despawn(summon);}
    void JustDied(Unit* Killer)
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X,1.0f);

        DoScriptText(SAY_DEATH, m_creature);

        DeleteLegs();
        summons.DespawnAll();

        if(pInstance)
            pInstance->SetData(DATA_KAELTHASEVENT, DONE);

        Creature *pCreature;
        for(uint8 i = 0; i < 4; ++i)
        {
            pCreature = (Unit::GetCreature((*m_creature), AdvisorGuid[i]));
            if(pCreature)
            {
                pCreature->setDeathState(JUST_DIED);
            }
        }
    }

    uint32 Intro_next(uint32 Step)  //animation sequence when starting phase 5
    {	/*TODO list:
        - find a proper way to implement netherbeams (36089, 36090)
        - find right spells and animations for an arcane storm (some spells known: 36196, 36197, 36198)
        - find a way of using spells: 36201, 36290, 36291
        - setup proper timers
        - others
        */
        switch(Step)
        {
        case 0:
            return 0;
        case 1: 
            pInstance->SetData(DATA_KAELTHASEVENT, 4);
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveIdle();
            DoTeleportTo(GRAVITY_X, GRAVITY_Y, ROOM_BASE_Z);
            m_creature->Relocate(GRAVITY_X, GRAVITY_Y, ROOM_BASE_Z, 0);
            m_creature->InterruptNonMeleeSpells(false);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            DoResetThreat();
            return 1000;
        case 2:
            DoCast(m_creature, SPELL_GAINING_POWER);
            return 1000;
        case 3:
            //Netherbeam spells needed here
            return 0;
        case 4: 
            DoScriptText(SAY_PHASE5_NUTS, m_creature);
            return 1000;
        case 5:
            m_creature->AddUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT + MOVEMENTFLAG_LEVITATING);
            m_creature->SendMonsterMove(GRAVITY_X-0.5f, GRAVITY_Y, ROOM_BASE_Z+25.0f, 12000);
            DoCast(m_creature, SPELL_EXPLODE_SHAKE1, true);
            return 4000;
        case 6:
            DoCast(m_creature, SPELL_NETHERBEAM_GLOW1, true);
            return 4000;
        case 7:
            DoCast(m_creature, SPELL_EXPLODE_SHAKE2, true);
            DoCast(m_creature, SPELL_NETHERBEAM_GLOW2, true);
            return 4000;
        case 8:
            m_creature->Relocate(GRAVITY_X-0.5f, GRAVITY_Y, ROOM_BASE_Z+25.0f);
            DoCast(m_creature, SPELL_NETHERBEAM_GLOW3, true);
            return 4000;
        case 9:
            DoCast(m_creature, SPELL_EXPLODE_SHAKE3, true);
            return 2000;
        case 10:
            m_creature->RemoveAllAuras();
            if(pInstance)
            pInstance->SetData(DATA_EXPLODE, true);
            return 1000;
        case 11:
            DoCast(m_creature, SPELL_EXPLODE);
            return 2000;
        case 12:
            DoCast(m_creature, SPELL_EXPLODE_SHAKE4, true);
            return 1000;
        case 13:
            DoCast(m_creature, SPELL_FULLPOWER);
            m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 2.0f);
            return 1000;
        case 14:
            return 2000;
        case 15:
            m_creature->SendMonsterMove(GRAVITY_X-1.0f, GRAVITY_Y, ROOM_BASE_Z, 13000);
            m_creature->Relocate(GRAVITY_X-1.0f, GRAVITY_Y, ROOM_BASE_Z);
            return 13000;			
        case 16:
            m_creature->Relocate(GRAVITY_X-1.0f, GRAVITY_Y, ROOM_BASE_Z);
            m_creature->InterruptNonMeleeSpells(false);
            m_creature->RemoveAurasDueToSpell(SPELL_FULLPOWER);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT + MOVEMENTFLAG_LEVITATING);
            Phase = 6;
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0)) //reset threat when starting phase 5
            {
                DoResetThreat();
                DoZoneInCombat();
                DoStartMovement(target);
                AttackStart(target);
            }
            Phase_Timer = 8000;
            return 500;
        default: return 0;
        }
        return 0;
    }


    void UpdateAI(const uint32 diff)
    {
        if (reset)
        {
            PrepareAdvisors();
            reset = false;
            return;
        }

        if(pInstance && Phase)
        {
            if(pInstance->GetData(DATA_KAELTHASEVENT) == IN_PROGRESS && m_creature->getThreatManager().getThreatList().empty())
            {
                EnterEvadeMode();
                return;
            }
        }
        //Phase 1
        switch (Phase)
        {
            case 1:
            {
                Unit *target;
                Creature* Advisor;

                //Subphase switch
                switch(PhaseSubphase)
                {
                    //Subphase 1 - Start
                    case 0:
                        if(Phase_Timer < diff)
                        {
                            DoScriptText(SAY_INTRO_THALADRED, m_creature);

                            //start advisor within 7 seconds
                            Phase_Timer = 7000;

                            ++PhaseSubphase;
                        }else Phase_Timer -= diff;
                        break;

                        //Subphase 1 - Unlock advisor
                    case 1:
                        if(Phase_Timer < diff)
                        {
                            Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[0]));

                            if(Advisor)
                            {
                                Advisor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                Advisor->setFaction(m_creature->getFaction());

                                target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                                if(target)
                                    Advisor->AI()->AttackStart(target);
                            }

                            ++PhaseSubphase;
                        }else Phase_Timer -= diff;
                        break;

                        //Subphase 2 - Start
                    case 2:
                        Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[0]));
                        if(Advisor && (Advisor->GetUInt32Value(UNIT_FIELD_BYTES_1) == PLAYER_STATE_DEAD))
                        {
                            DoScriptText(SAY_INTRO_SANGUINAR, m_creature);

                            //start advisor within 12.5 seconds
                            Phase_Timer = 12500;

                            ++PhaseSubphase;
                        }
                        break;

                        //Subphase 2 - Unlock advisor
                    case 3:
                        if(Phase_Timer < diff)
                        {
                            Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[1]));

                            if(Advisor)
                            {
                                Advisor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                Advisor->setFaction(m_creature->getFaction());

                                target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                                if(target)
                                    Advisor->AI()->AttackStart(target);
                            }

                            ++PhaseSubphase;
                        }else Phase_Timer -= diff;
                        break;

                        //Subphase 3 - Start
                    case 4:
                        Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[1]));
                        if(Advisor && (Advisor->GetUInt32Value(UNIT_FIELD_BYTES_1) == PLAYER_STATE_DEAD))
                        {
                            DoScriptText(SAY_INTRO_CAPERNIAN, m_creature);

                            //start advisor within 7 seconds
                            Phase_Timer = 7000;

                            ++PhaseSubphase;
                        }
                        break;

                        //Subphase 3 - Unlock advisor
                    case 5:
                        if(Phase_Timer < diff)
                        {
                            Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[2]));

                            if(Advisor)
                            {
                                Advisor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                Advisor->setFaction(m_creature->getFaction());

                                target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                                if(target)
                                    Advisor->AI()->AttackStart(target);
                            }

                            ++PhaseSubphase;
                        }else Phase_Timer -= diff;
                        break;

                        //Subphase 4 - Start
                    case 6:
                        Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[2]));
                        if(Advisor && (Advisor->GetUInt32Value(UNIT_FIELD_BYTES_1) == PLAYER_STATE_DEAD))
                        {
                            DoScriptText(SAY_INTRO_TELONICUS, m_creature);

                            //start advisor within 8.4 seconds
                            Phase_Timer = 8400;

                            ++PhaseSubphase;
                        }
                        break;

                        //Subphase 4 - Unlock advisor
                    case 7:
                        if(Phase_Timer < diff)
                        {
                            Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[3]));

                            if(Advisor)
                            {
                                Advisor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                Advisor->setFaction(m_creature->getFaction());

                                target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                                if(target)
                                    Advisor->AI()->AttackStart(target);
                            }

                            Phase_Timer = 3000;

                            ++PhaseSubphase;
                        }else Phase_Timer -= diff;
                        break;

                        //End of phase 1
                    case 8:
                        Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[3]));
                        if(Advisor && (Advisor->GetUInt32Value(UNIT_FIELD_BYTES_1) == PLAYER_STATE_DEAD))
                        {
                            Phase = 2;
                            pInstance->SetData(DATA_KAELTHASEVENT, 2);

                            DoScriptText(SAY_PHASE2_WEAPON, m_creature);
                            PhaseSubphase = 0;
                            Phase_Timer = 3500;
                            DoCast(m_creature, SPELL_SUMMON_WEAPONS);
                        }
                        break;
                }
            }break;

            case 2:
            {
                if (PhaseSubphase == 0)
                {
                    if (Phase_Timer < diff)
                    {
                        PhaseSubphase = 1;
                    }else Phase_Timer -= diff;
                }

                //Spawn weapons
                if (PhaseSubphase == 1)
                {
                    Creature* Weapon;
                    for (uint32 i = 0; i < 7; ++i)
                    {
                        Unit* Target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                        Weapon = m_creature->SummonCreature(((uint32)KaelthasWeapons[i][0]),KaelthasWeapons[i][1],KaelthasWeapons[i][2],KaelthasWeapons[i][3],0,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);

                        if (!Weapon)
                            error_log("STSCR: Kael'thas weapon %i could not be spawned", i);
                        else
                        {
                            Weapon->setFaction(m_creature->getFaction());
                            Weapon->AI()->AttackStart(Target);
                            Weapon->CastSpell(Weapon, SPELL_WEAPON_SPAWN, false);
                            WeaponGuid[i] = Weapon->GetGUID();
                        }
                    }

                    PhaseSubphase = 2;
                    Phase_Timer = TIME_PHASE_2_3;
                }

                if (PhaseSubphase == 2)
                    if (Phase_Timer < diff)
                {
                    DoScriptText(SAY_PHASE3_ADVANCE, m_creature);
                    pInstance->SetData(DATA_KAELTHASEVENT, 4);		// phase 3 = phase 4, to discriminate phase 3 state from DONE
                    Phase = 3;
                    PhaseSubphase = 0;
                }else Phase_Timer -= diff;
                 //missing Resetcheck
            }break;

            case 3:
            {
                if (PhaseSubphase == 0)
                {
                    Creature* Advisor;
                    for (uint32 i = 0; i < 4; ++i)
                    {
                        Advisor = (Creature*)(Unit::GetUnit((*m_creature), AdvisorGuid[i]));
                        if (!Advisor)
                            error_log("TSCR: Kael'Thas Advisor %u does not exist. Possibly despawned? Incorrectly Killed?", i);
                        else
                            ((advisorbase_ai*)Advisor->AI())->Revive();
                    }

                    m_creature->StopMoving();
                    PhaseSubphase = 1;
                    Phase_Timer = TIME_PHASE_3_4;
                }

                if(Phase_Timer < diff)
                {
                    DoScriptText(SAY_PHASE4_INTRO2, m_creature);
                    Phase = 4;

                    pInstance->SetData(DATA_KAELTHASEVENT, 4);

                    DoResetThreat();
                    DoZoneInCombat();
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                    if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    {
                        DoResetThreat();//only healers will be at top threat, so reset(not delete) all players's threat when Kael comes to fight
                        AttackStart(target);
                    }
                    Phase_Timer = 30000;
                }else Phase_Timer -= diff;
            }
            break;

            case 4:
            case 5:
            case 6:
            {
                //Return since we have no target
                if (!UpdateVictim() )
                    return;

                //Check_Timer
                if(Check_Timer < diff)
                {
                    if(m_creature->GetDistance(wLoc.x,wLoc.y,wLoc.z) > 135.0f)
                        EnterEvadeMode();
                    else
                        DoZoneInCombat();
            
                    Check_Timer = 3000;
                }else Check_Timer -= diff;

                
                if(!ChainPyros && Phase != 5)
                {
                    //Fireball_Timer
                    if(Fireball_Timer < diff)
                    {
                        if(!IsCastingFireball  && !InGravityLapse)
                        {
                            if(!m_creature->IsNonMeleeSpellCasted(false))
                            {
                                //interruptable
                                m_creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                                m_creature->CastSpell(m_creature->getVictim(), SPELL_FIREBALL, false);
                                IsCastingFireball = true;
                                Fireball_Timer = 2500;
                            }
                        }
                        else
                        {
                            //apply resistance
                            m_creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                            IsCastingFireball = false;
                            Fireball_Timer = 5000+rand()%10000;
                        }
                    }else Fireball_Timer -= diff;

                    //Phoenix_Timer
                    if(Phoenix_Timer < diff && !IsCastingFireball && !InGravityLapse)
                    {
                         DoCast(m_creature, SPELL_SUMMON_PHOENIX, true);
                         switch(rand()%2)
                          {
                            case 0: DoScriptText(SAY_SUMMON_PHOENIX1, m_creature); break;
                            case 1: DoScriptText(SAY_SUMMON_PHOENIX2, m_creature); break;
                          }
                         Phoenix_Timer = 30000 +rand()%10000;
                    }
                    else
                        Phoenix_Timer -=diff;

                    // FlameStrike_Timer
                    if(FlameStrike_Timer < diff && !InGravityLapse)
                    {
                        if(m_creature->IsNonMeleeSpellCasted(true))
                        {
                            m_creature->InterruptNonMeleeSpells(true);
                        }
                        if (Unit* pUnit = SelectUnit(SELECT_TARGET_RANDOM, 0, 70, true))
                            DoCast(pUnit, SPELL_FLAME_STRIKE);

                        FlameStrike_Timer = 30000;
                    }
                    else
                        FlameStrike_Timer -= diff;
                }
                    
                if(Phase != 5)
                    {
                        if(Arcane_Timer1 < diff && !Arcane1)
                        {
                            //Arcane Disruption after 20 sec from Pyros chain (4 Phase) or Shock (5 Phase)
                            DoCast(m_creature, SPELL_ARCANE_DISRUPTION, true);
                            Arcane1 = true;

                            // MC after 20 sec from Pyros chain (4 Phase)
                            if(Phase == 4)
                            {
                              if(m_creature->getThreatManager().getThreatList().size() >= 2)
                              for (uint32 i = 0; i < 3; i++)
                              {

                                  Unit* target =SelectUnit(SELECT_TARGET_RANDOM, 1, 70, true);
                                  if(!target)
                                      target = m_creature->getVictim();

                                  if(target)
                                      DoCast(target, SPELL_MIND_CONTROL);
                                      switch(rand()%2)
                                      {
                                       case 0: DoScriptText(SAY_MINDCONTROL1, m_creature); break;
                                       case 1: DoScriptText(SAY_MINDCONTROL2, m_creature); break;
                                      }
                              }
                              MindControl_Timer = 10000;
                              MC_Done = false;				// for second MC to have a good timer
                            }
                        }
                        else
                            Arcane_Timer1 -= diff;

                        if(Arcane_Timer2 < diff)
                        {
                            // MC after 50 sec from Pyros chain (4 Phase)
                            if(MindControl_Timer < diff && Phase == 4 && !MC_Done)
                            {
                                if(m_creature->getThreatManager().getThreatList().size() >= 2)
                                for (uint32 i = 0; i < 3; i++)
                                {

                                    Unit* target =SelectUnit(SELECT_TARGET_RANDOM, 1, 70, true);
                                    if(!target)
                                        target = m_creature->getVictim();

                                    if(target)
                                        DoCast(target, SPELL_MIND_CONTROL);
                                        switch(rand()%2)
                                          {
                                           case 0: DoScriptText(SAY_MINDCONTROL1, m_creature); break;
                                           case 1: DoScriptText(SAY_MINDCONTROL2, m_creature); break;
                                          }
                                }
                                MC_Done = true;
                            }else
                                MindControl_Timer -= diff;

                            //Arcane Disruption after 40 sec from Pyros chain (4 Phase) or Shock (5 Phase)
                            if(!Arcane2)
                            {
                            DoCast(m_creature, SPELL_ARCANE_DISRUPTION, true);
                            Arcane2 = true;
                            }
                        }
                        else
                            Arcane_Timer2 -= diff;									
                    }

                //Phase 4 specific spells
                if(Phase == 4)
                {
                    if (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 50)
                    {
                        Phase = 5;
                    }

                    // arcane disruption, shock, pyroblasts chain
                    if(ShockPyroChain_Timer < diff)
                    {
                        if(PyrosCasted == 0)
                        {
                            if(m_creature->IsNonMeleeSpellCasted(true))
                            {
                                m_creature->InterruptNonMeleeSpells(true);
                            }
                            DoCast(m_creature, SPELL_SHOCK_BARRIER);
                            DoCast(m_creature, SPELL_ARCANE_DISRUPTION, true);
                            Fireball_Timer = 2500;
                            Arcane_Timer1 = 20000;
                            Arcane1 = false;
                            Arcane_Timer2 = 40000;
                            Arcane2 = false;
                            ChainPyros = true;
                        }

                        if(PyrosCasted < 3 && Pyro_Timer < diff)
                        {
                            m_creature->StopMoving();
                            m_creature->CastSpell(m_creature->getVictim(), SPELL_PYROBLAST, false);
                            ++PyrosCasted;
                            Pyro_Timer = 4000 + diff;
                        }
                        else
                            Pyro_Timer -= diff;

                        if(PyrosCasted >= 3 && Pyro_Timer < diff)
                        {
                            ChainPyros = false;
                            PyrosCasted = 0;
                            ShockPyroChain_Timer = 48000;
                            Pyro_Timer = 0;
                        }
                    }
                    else
                        ShockPyroChain_Timer -= diff;
                }
                else
                    Check_Timer -= 4100;

                if(Phase == 5)
                {
                    if(Anim_Timer < diff)
                    {
                        Anim_Timer = Intro_next(Step++);
                    }
                    else
                        Anim_Timer -= diff;
                }

                //Phase 5
                if(Phase == 6)
                {
                    //GravityLapse_Timer
                    if(GravityLapse_Timer < diff)
                    {
                        std::list<HostilReference*>::iterator i = m_creature->getThreatManager().getThreatList().begin();
                        switch(GravityLapse_Phase)
                        {
                            case 0:
                                m_creature->GetMotionMaster()->Clear();
                                m_creature->GetMotionMaster()->MoveIdle();
                                DoTeleportTo(GRAVITY_X, GRAVITY_Y, ROOM_BASE_Z);
                                // 1) Kael'thas will portal the whole raid right into his body
                                for (i = m_creature->getThreatManager().getThreatList().begin(); i!= m_creature->getThreatManager().getThreatList().end();)
                                {
                                    Unit* pUnit = Unit::GetUnit((*m_creature), (*i)->getUnitGuid());
                                    ++i;
                                    if(pUnit && (pUnit->GetTypeId() == TYPEID_PLAYER))
                                    {
                                        //Use work around packet to prevent player from being dropped from combat
                                        DoTeleportPlayer(pUnit, GRAVITY_X, GRAVITY_Y, ROOM_BASE_Z, pUnit->GetOrientation());
                                    }
                                }
                                summons.AuraOnEntry(PHOENIX,SPELL_BANISH,true);
                                if(pInstance)
                                    pInstance->SetData(DATA_KAELTHASEVENT, 5);	// set KaelthasEventPhase = 5 for Gravity Lapse phase
                                GravityLapse_Timer = 500;
                                ++GravityLapse_Phase;
                                InGravityLapse = true;
                                Arcane_Timer1 = 20000;
                                Arcane1 = false;
                                Arcane_Timer2 = 40000;
                                Arcane2 = false;
                                Phoenix_Timer = 33000;
                                FlameStrike_Timer = 32000;
                                ShockBarrier_Timer = 0;
                                NetherBeam_Timer = 5000;
                                Kick_Timer = 3000;
                                break;

                            case 1:
                                switch(rand()%2)
                                {
                                case 0: DoScriptText(SAY_GRAVITYLAPSE1, m_creature); break;
                                case 1: DoScriptText(SAY_GRAVITYLAPSE2, m_creature); break;
                                }

                                // 2) At that point he will put a Gravity Lapse debuff on everyone
                                for (i = m_creature->getThreatManager().getThreatList().begin(); i!= m_creature->getThreatManager().getThreatList().end();)
                                {
                                    Unit* pUnit = Unit::GetUnit((*m_creature), (*i)->getUnitGuid());
                                    ++i;
                                    if(pUnit && pUnit->GetTypeId() == TYPEID_PLAYER)
                                    {
                                        m_creature->CastSpell(pUnit, SPELL_KNOCKBACK, true);
                                        //Gravity lapse - needs an exception in Spell system to work

                                        pUnit->CastSpell(pUnit, SPELL_GRAVITY_LAPSE, true, 0, 0, m_creature->GetGUID());
                                        pUnit->CastSpell(pUnit, SPELL_GRAVITY_LAPSE_AURA, true, 0, 0, m_creature->GetGUID());

                                        //Using packet workaround
                                        WorldPacket data(12);
                                        data.SetOpcode(SMSG_MOVE_SET_CAN_FLY);
                                        data.append(pUnit->GetPackGUID());
                                        data << uint32(0);
                                        pUnit->SendMessageToSet(&data, true);
                                    }
                                }
                                GravityLapse_Timer = 3000;
                                DoCast(m_creature, SPELL_SUMMON_NETHER_VAPOR);
                                ++GravityLapse_Phase;
                                break;

                            case 2:
                                //Summon Nether Vapor clouds NPC's and cast Nether Vapor aura on self
                                DoCast(m_creature, SPELL_NETHER_VAPOR, true);
                                for(uint8 i = 0; i <= 16; i += 16)
                                {
                                for(uint8 j = 0; j <= 16; j += 16)
                                {
                                for(uint8 k = 0; k <=4; k +=4)
                                {
                                    m_creature->SummonCreature(NETHER_VAPOR_CLOUD, GRAVITY_X-8.0f+i, GRAVITY_Y-8.0f+j, ROOM_BASE_Z+4.0f+k, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 0); 
                                }
                                }
                                }
                                GravityLapse_Timer = 27000;
                                ++GravityLapse_Phase;
                                break;

                            case 3:
                                //Remove flight
                                Map *map = m_creature->GetMap();
                                Map::PlayerList const &PlayerList = map->GetPlayers();
                                if (PlayerList.isEmpty())
                                    return;

                                Map::PlayerList::const_iterator i;
                                for (i = PlayerList.begin(); i!= PlayerList.end();)
                                {
                                    Player* i_pl = i->getSource();
                                    Unit* pUnit = Unit::GetUnit((*m_creature), i_pl->GetGUID());
                                    ++i;
                                    if(pUnit && pUnit->GetTypeId() == TYPEID_PLAYER)
                                    {
                                        //Using packet workaround
                                        WorldPacket data(12);
                                        data.SetOpcode(SMSG_MOVE_UNSET_CAN_FLY);
                                        data.append(pUnit->GetPackGUID());
                                        data << uint32(0);
                                        pUnit->SendMessageToSet(&data, true);
                                    }
                                }
                                m_creature->RemoveAurasDueToSpell(SPELL_NETHER_VAPOR);
                                InGravityLapse = false;
                                summons.AuraOnEntry(PHOENIX,SPELL_BANISH,false);
                                if(pInstance)
                                    pInstance->SetData(DATA_KAELTHASEVENT, 4);	// after Gravity Lapse set back state 4 of KaelthasPhaseEvent
                                GravityLapse_Timer = 60000;
                                GravityLapse_Phase = 0;
                                DoStartMovement(m_creature->getVictim());
                                AttackStart(m_creature->getVictim());
                                break;
                        }
                    }else GravityLapse_Timer -= diff;

                    if(InGravityLapse)
                    {
                        //ShockBarrier_Timer in 5th phase only
                        if(ShockBarrier_Timer < diff)
                        {
                            DoCast(m_creature, SPELL_SHOCK_BARRIER);
                            ShockBarrier_Timer = 8000;
                        }else ShockBarrier_Timer -= diff;

                        //NetherBeam_Timer
                        if(NetherBeam_Timer < diff)
                        {
                            if (Unit* pUnit = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                DoCast(pUnit, SPELL_NETHER_BEAM);

                            NetherBeam_Timer = 4000;
                        }else NetherBeam_Timer -= diff;

                        if(Kick_Timer < diff)
                        {
                            Map *map = m_creature->GetMap();
                            Map::PlayerList const &PlayerList = map->GetPlayers();
                            Map::PlayerList::const_iterator i;
                            for (i = PlayerList.begin(); i!= PlayerList.end();)
                            {
                                Player * iPl = i->getSource();
                                Unit* pUnit = Unit::GetUnit((*m_creature), iPl->GetGUID());
                                ++i;
                                float tempZ = iPl->GetPositionZ();
                                if (tempZ < ROOM_BASE_Z + 7)
                                    m_creature->CastSpell(iPl, SPELL_KNOCKBACK, true);
                                WorldPacket data(12);
                                data.SetOpcode(SMSG_MOVE_SET_CAN_FLY);
                                data.append(pUnit->GetPackGUID());
                                data << uint32(0);
                                pUnit->SendMessageToSet(&data, true);
                            }
                            Kick_Timer = 1000;
                        }
                        else
                            Kick_Timer -= diff;
                    }
                }

                if (!InGravityLapse)
                    DoMeleeAttackIfReady();
            }
        }
    }
};

//Thaladred the Darkener AI
struct TRINITY_DLL_DECL boss_thaladred_the_darkenerAI : public advisorbase_ai
{
    boss_thaladred_the_darkenerAI(Creature *c) : advisorbase_ai(c) {}

    uint32 Gaze_Timer;
    uint32 Rend_Timer;
    uint32 Silence_Timer;
    uint32 PsychicBlow_Timer;
    uint32 Check_Timer;
    uint32 Check_Timer2;

    void Reset()
    {
        Gaze_Timer = 100;
        Rend_Timer = 1000;
        Silence_Timer = 20000;
        PsychicBlow_Timer = 10000;
        Check_Timer = 1000;
        Check_Timer2 = 3000;

        advisorbase_ai::Reset();
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_THALADRED_DEATH, m_creature);
    }

    void Aggro(Unit *who)
    {
        if(!who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        DoScriptText(SAY_THALADRED_AGGRO, m_creature);
        m_creature->AddThreat(who, 5000000.0f);
        m_creature->SetUnitMovementFlags(MOVEMENTFLAG_WALK_MODE);
        m_creature->SetSpeed(MOVE_WALK, 1.2f, true);
    }

    void UpdateAI(const uint32 diff)
    {
        //Faking death, don't do anything
        if(m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        //Return since we have no target
        if (!UpdateVictim() )
            return;

        if(Creature* kael = Creature::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
        {
            //Check_Timer
            if(Check_Timer2 < diff)
            {
                WorldLocation wLoc = ((boss_kaelthasAI*)kael->AI())->wLoc;
                if(m_creature->GetDistance(wLoc.x,wLoc.y,wLoc.z) > 200.0f)
                    EnterEvadeMode();
                else
                    DoZoneInCombat();
            
                 Check_Timer2 = 3000;
            }
            else
                Check_Timer2 -= diff;
        }

        if(Unit *t = m_creature->getVictim())
        {
            if(t->IsImmunedToDamage(SPELL_SCHOOL_MASK_NORMAL,false))
            {
                if(Unit* target = SelectUnit(SELECT_TARGET_TOPAGGRO, 1))
                {
                    m_creature->AddThreat(target, 5000001.0f);
                    AttackStart(target);
                }
            }
        }

        if(Check_Timer < diff)
        {
           if(m_creature->getThreatManager().getThreat(m_creature->getVictim(),false) < 5000000.0f)
               m_creature->AddThreat(m_creature->getVictim(), 5000001.0f);
        
            Check_Timer = 1000;
        }
        else
            Check_Timer -= diff;

        //Gaze_Timer
        if(Gaze_Timer < diff)
        {
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0, 100, true))
            {
                if(target)
                {
                    DoResetThreat();
                    m_creature->AddThreat(target, 5000001.0f);
                    DoScriptText(EMOTE_THALADRED_GAZE, m_creature, target);
                    m_creature->SetUnitMovementFlags(MOVEMENTFLAG_WALK_MODE);
                    m_creature->SetSpeed(MOVE_WALK, 1.2f, true);
                    AttackStart(target);
                }
                Gaze_Timer = 8500;
            }
        }
        else
            Gaze_Timer -= diff;

        //Silence_Timer
        if(Silence_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_SILENCE, true);
            Silence_Timer = 20000;
        }
        else
            Silence_Timer -= diff;

        if(Rend_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_REND, true);
            Rend_Timer = 10000;
        }
        else
            Rend_Timer -= diff;

        //PsychicBlow_Timer
        if(PsychicBlow_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_PSYCHIC_BLOW, true);
            PsychicBlow_Timer = 20000+rand()%5000;
        }
        else
            PsychicBlow_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

//Lord Sanguinar AI
struct TRINITY_DLL_DECL boss_lord_sanguinarAI : public advisorbase_ai
{
    boss_lord_sanguinarAI(Creature *c) : advisorbase_ai(c){}

    uint32 Fear_Timer;
    uint32 Check_Timer;

    void Reset()
    {
        Fear_Timer = 20000;
        Check_Timer = 3000;

        m_creature->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);
        m_creature->ApplySpellImmune(1, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);

        advisorbase_ai::Reset();
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(SAY_SANGUINAR_DEATH, m_creature);
    }

    void Aggro(Unit *who)
    {
        if (!who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        DoScriptText(SAY_SANGUINAR_AGGRO, m_creature);
    }
    
    void UpdateAI(const uint32 diff)
    {
        //Faking death, don't do anything
        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        //Return since we have no target
        if (!UpdateVictim() )
            return;

        if(Creature* kael = Creature::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
        {
            //Check_Timer
            if(Check_Timer < diff)
            {
                WorldLocation wLoc = ((boss_kaelthasAI*)kael->AI())->wLoc;
                if(m_creature->GetDistance(wLoc.x,wLoc.y,wLoc.z) > 200.0f)
                    EnterEvadeMode();
                else
                    DoZoneInCombat();
            
                 Check_Timer = 3000;
             }else Check_Timer -= diff;
        }

        //Fear_Timer
        if(Fear_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_BELLOWING_ROAR);
            Fear_Timer = 25000+rand()%10000;                //approximately every 30 seconds
        }else Fear_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

//Grand Astromancer Capernian AI
struct TRINITY_DLL_DECL boss_grand_astromancer_capernianAI : public advisorbase_ai
{
    boss_grand_astromancer_capernianAI(Creature *c) : advisorbase_ai(c){}

    uint32 Fireball_Timer;
    uint32 Conflagration_Timer;
    uint32 ArcaneExplosion_Timer;
    uint32 Yell_Timer;
    bool Yell;
    uint32 Check_Timer;

    void Reset()
    {
        Fireball_Timer = 2000;
        Conflagration_Timer = 20000;
        ArcaneExplosion_Timer = 5000;
        Yell_Timer = 2000;
        Yell = false;
        Check_Timer = 3000;

        advisorbase_ai::Reset();
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_CAPERNIAN_DEATH, m_creature);
    }

    void AttackStart(Unit* who)
    {
        if (!who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        if (m_creature->Attack(who, true))
        {
            m_creature->AddThreat(who, 0.0f);

            if (!InCombat)
            {
                InCombat = true;
                Aggro(who);
            }

            DoStartMovement(who, CAPERNIAN_DISTANCE, M_PI/2);
        }
    }

    void Aggro(Unit *who)
    {
        if (who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;
    }

    void UpdateAI(const uint32 diff)
    {
        //Faking Death, don't do anything
        if ( m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) )
            return;

        //Return since we have no target
        if (!UpdateVictim() )
            return;

        if(Creature* kael = Creature::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
        {
            //Check_Timer
            if(Check_Timer < diff)
            {
                WorldLocation wLoc = ((boss_kaelthasAI*)kael->AI())->wLoc;
                if(m_creature->GetDistance(wLoc.x,wLoc.y,wLoc.z) > 200.0f)
                    EnterEvadeMode();
                else
                    DoZoneInCombat();
            
                 Check_Timer = 3000;
             }else Check_Timer -= diff;
        }

        //Yell_Timer
        if(!Yell)
        {
            if(Yell_Timer < diff)
            {
                DoScriptText(SAY_CAPERNIAN_AGGRO, m_creature);

                Yell = true;
            }else Yell_Timer -= diff;
        }

        //Fireball_Timer
        if(Fireball_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_CAPERNIAN_FIREBALL);
            Fireball_Timer = 4000;
        }else Fireball_Timer -= diff;

        //Conflagration_Timer
        if(Conflagration_Timer < diff)
        {
            Unit *target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM, 0, 30, true);

            if(target)
                DoCast(target, SPELL_CONFLAGRATION);
            else
                DoCast(m_creature->getVictim(), SPELL_CONFLAGRATION);

            Conflagration_Timer = 10000+rand()%5000;
        }else Conflagration_Timer -= diff;

        //ArcaneExplosion_Timer
        if(ArcaneExplosion_Timer < diff)
        {
            bool InMeleeRange = false;
            Unit *target = NULL;
            std::list<HostilReference*>& m_threatlist = m_creature->getThreatManager().getThreatList();
            for (std::list<HostilReference*>::iterator i = m_threatlist.begin(); i!= m_threatlist.end();++i)
            {
                Unit* pUnit = Unit::GetUnit((*m_creature), (*i)->getUnitGuid());
                                                            //if in melee range
                if(pUnit && pUnit->IsWithinDistInMap(m_creature, 5))
                {
                    InMeleeRange = true;
                    target = pUnit;
                    break;
                }
            }

            if(InMeleeRange)
                DoCast(target, SPELL_ARCANE_EXPLOSION);

            ArcaneExplosion_Timer = 4000+rand()%2000;
        }else ArcaneExplosion_Timer -= diff;

        //Do NOT deal any melee damage.
    }
};

//Master Engineer Telonicus AI
struct TRINITY_DLL_DECL boss_master_engineer_telonicusAI : public advisorbase_ai
{
    boss_master_engineer_telonicusAI(Creature *c) : advisorbase_ai(c)
    {
        SpellEntry *TempSpell = (SpellEntry*)GetSpellStore()->LookupEntry(SPELL_BOMB);
        if(TempSpell)
            TempSpell->Effect[0] = 2;
    }

    uint32 Bomb_Timer;
    uint32 RemoteToy_Timer;
    uint32 Check_Timer;

    void Reset()
    {
        Bomb_Timer = 10000;
        RemoteToy_Timer = 5000;
        Check_Timer = 3000;

        advisorbase_ai::Reset();
    }

    void JustDied(Unit* pKiller)
    {
         DoScriptText(SAY_TELONICUS_DEATH, m_creature);
    }

    void AttackStart(Unit *who)
    {
        if (!who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;
        
        if(who->getClass() == CLASS_HUNTER)
        {
            ScriptedAI::AttackStart(who,true);
            DoStartMovement(who, 28.0f, 2*M_PI);
        }        
        else
            ScriptedAI::AttackStart(who,true);
    }

    void Aggro(Unit *who)
    {
        if (!who || m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        DoScriptText(SAY_TELONICUS_AGGRO, m_creature);
    }

    void UpdateAI(const uint32 diff)
    {
        //Faking Death, do nothing
        if(m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        //Return since we have no target
        if (!UpdateVictim() )
            return;

        if( Unit *hunter = m_creature->getVictim() )
        {
            if( hunter->getClass() == CLASS_HUNTER )
            {
                if( m_creature->GetDistance2d(hunter) > 30.0f )
                {
                    DoStartMovement(hunter, 28.0f, 2*M_PI);
                }
                else if( m_creature->hasUnitState(UNIT_STAT_CHASE) )
                    m_creature->StopMoving();
            }
            else
                if( !m_creature->hasUnitState(UNIT_STAT_CHASE) )
                    ScriptedAI::AttackStart(hunter, true);
        }

        if(Creature* kael = Creature::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
        {
            //Check_Timer
            if(Check_Timer < diff)
            {
                WorldLocation wLoc = ((boss_kaelthasAI*)kael->AI())->wLoc;
                if(m_creature->GetDistance(wLoc.x,wLoc.y,wLoc.z) > 200.0f)
                    EnterEvadeMode();
                else
                    DoZoneInCombat();
            
                 Check_Timer = 3000;
             }else Check_Timer -= diff;
        }

        //RemoteToy_Timer
        if(RemoteToy_Timer < diff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(target, SPELL_REMOTE_TOY);

            RemoteToy_Timer = 10000+rand()%5000;
        }else RemoteToy_Timer -= diff;

        //Bomb_Timer
        if(Bomb_Timer < diff)
        {
            m_creature->CastSpell(m_creature->getVictim(), SPELL_BOMB, false);
            Bomb_Timer = 2000+rand()%6000;
            return;
        }else Bomb_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

//Flame Strike AI
struct TRINITY_DLL_DECL mob_kael_flamestrikeAI : public Scripted_NoMovementAI
{
    mob_kael_flamestrikeAI(Creature *c) : Scripted_NoMovementAI(c) {}

    uint32 Timer;
    bool Casting;
    bool KillSelf;

    void Reset()
    {
        Timer = 5000;
        Casting = false;
        KillSelf = false;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->setFaction(14);
    }

    void Aggro(Unit *who)
    {
    }

    void MoveInLineOfSight(Unit *who)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!Casting)
        {
            DoCast(m_creature, SPELL_FLAME_STRIKE_VIS);
            Casting = true;
        }

        //Timer
        if(Timer < diff)
        {
            if (!KillSelf)
            {
                m_creature->InterruptNonMeleeSpells(false);
                DoCast(m_creature, SPELL_FLAME_STRIKE_DMG);
            }else m_creature->DealDamage(m_creature, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);

            KillSelf = true;
            Timer = 1000;
        }else Timer -= diff;
    }
};

//Phoenix AI
struct TRINITY_DLL_DECL mob_phoenix_tkAI : public ScriptedAI
{
    mob_phoenix_tkAI(Creature *c) : ScriptedAI(c)
    {
       pInstance = ((ScriptedInstance*)c->GetInstanceData());
    }

    ScriptedInstance* pInstance;
    uint32 Cycle_Timer;
    bool Egg;

    void Reset()
    {
        m_creature->AddUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT + MOVEMENTFLAG_LEVITATING);//birds can fly! :)
        Cycle_Timer = 2000;
        Egg = true;
        m_creature->CastSpell(m_creature,SPELL_BURN,true);
    }

    void Aggro(Unit *who) { }

    void JustDied(Unit* Killer)
    {
        float x,y,z;

        m_creature->GetPosition(x,y,z);
        Creature * phoenixEgg = Egg ? m_creature->SummonCreature(PHOENIX_EGG,x,y,z,0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,60000) : NULL;
        m_creature->CastSpell(m_creature, SPELL_EMBER_BLAST, true);
        if(phoenixEgg)
          {
            phoenixEgg->setFaction(m_creature->getFaction());
            phoenixEgg = NULL;
          }
        m_creature->RemoveCorpse();
    }

    void SpellHit(Unit *caster, SpellEntry* spell)
    {
        for(int i = 0; i < 3; i++)
        {
            if(spell->EffectMechanic[i] == MECHANIC_BANISH && spell->Id != SPELL_BANISH)
                m_creature->RemoveAurasDueToSpell(spell->Id);
        }

    }

    void UpdateAI(const uint32 diff)
    {
        if (Cycle_Timer < diff)
        {
            if(pInstance)//check for boss reset
            {
                Creature* Kael = Unit::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS));
                if (Kael && Kael->getThreatManager().getThreatList().empty())
                {
                    Egg = false;
                    m_creature->Kill(m_creature, false);
                    Cycle_Timer = 2000;
                    return;
                }
            }
              //spell Burn should possible do this, but it doesn't, so do this for now.
             uint32 dmg = 0.05*(m_creature->GetMaxHealth());	// burn 5% of phoenix HP each tick

             if (m_creature->GetHealth() > dmg)
             {
                 m_creature->SetHealth(uint32(m_creature->GetHealth()-dmg));
             }			 
              else m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);	//kill it
          Cycle_Timer = 2000;
        }else Cycle_Timer -= diff;

        if (!UpdateVictim())
            return;
        DoMeleeAttackIfReady();
    }
};

struct TRINITY_DLL_DECL mob_phoenix_egg_tkAI : public ScriptedAI
{
    mob_phoenix_egg_tkAI(Creature *c) : ScriptedAI(c) 
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
    }

    uint32 Rebirth_Timer;
    bool summoned;
    ScriptedInstance* pInstance;

    void Reset()
    {
        Rebirth_Timer = 15000;
        summoned = false;
    }

    //ignore any
    void MoveInLineOfSight(Unit* who) { return; }

    void AttackStart(Unit* who)
    {
        if (m_creature->Attack(who, false))
        {
            if (!InCombat)
            {
                InCombat = true;
                Aggro(who);
            }
            DoStartNoMovement(who);
        }
    }

    void Aggro(Unit *who) { }

    void JustSummoned(Creature* summoned)
    {
        summoned->CastSpell(summoned,SPELL_REBIRTH,false);

        if(summoned->GetEntry() == PHOENIX)
        {
            summoned->setFaction(m_creature->getFaction());
            DoZoneInCombat();
            Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0);
            if(target)
            {
                summoned->setActive(true);
                summoned->AI()->AttackStart(target);
            }
        }

        if(pInstance)//check for boss reset
        {
            if(Creature* Kael = Unit::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
                ((boss_kaelthasAI*)Kael->AI())->summons.Summon(summoned);
        }
    }

    void UpdateAI(const uint32 diff)
    {
      if(pInstance->GetData(DATA_KAELTHASEVENT) == 4)
      {
        if (Rebirth_Timer < diff)
        {
            if(!summoned)
            {
                Creature* Phoenix = m_creature->SummonCreature(PHOENIX,m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),m_creature->GetOrientation(),TEMPSUMMON_CORPSE_DESPAWN,5000);
                summoned = true;
            }
            m_creature->Kill(m_creature, false);
        }
        else
            Rebirth_Timer -= diff;
      }
    }
};

struct TRINITY_DLL_DECL mob_nether_vaporAI : public ScriptedAI
{
    mob_nether_vaporAI(Creature *c) : ScriptedAI(c) 
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
    }

    ScriptedInstance* pInstance;

    uint32 Vapor_Timer;
    uint32 Cast_Timer;

    void Reset()
    {
        Vapor_Timer = 27000;
        Cast_Timer = 8000;

        m_creature->setFaction(16);
        m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, m_creature->GetFloatValue(OBJECT_FIELD_SCALE_X)*4.0f);
        m_creature->AddUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT + MOVEMENTFLAG_LEVITATING);
        m_creature->StopMoving();
    }

    //ignore
    void MoveInLineOfSight(Unit* who) { return; }

    void Aggro(Unit *who) { return; }

    void UpdateAI(const uint32 diff)
    {

        if(Cast_Timer < diff)
        {
            m_creature->Relocate(m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ());
            m_creature->CastSpell(m_creature, SPELL_NETHER_VAPOR, false);
            m_creature->GetMotionMaster()->MoveRandom(20.0);
            Cast_Timer = 8000;
        }
        else
            Cast_Timer -= diff;

        if(Vapor_Timer < diff)
        {
            m_creature->Kill(m_creature, false);
        }
        else
            Vapor_Timer -= diff;
    }
};


enum WEAPON_ADVISOR
{
    NETHERSTRAND_LONGBOW    = 21268,
    DEVASTATION             = 21269,
    COSMIC_INFUSER          = 21270,
    INFINITY_BLADES         = 21271,
    WARP_SLICER             = 21272,     
    PHASESHIFT_BULWARK      = 21273,
    STAFF_OF_DISINTEGRATION = 21274,
};

struct TRINITY_DLL_DECL weapon_advisorAI : public ScriptedAI
{
    weapon_advisorAI(Creature *c) : ScriptedAI(c)
    {
       pInstance = ((ScriptedInstance*)c->GetInstanceData());
    }

    ScriptedInstance* pInstance;

    uint32 MultiShoot_Timer;
    uint32 Shoot_Timer;
    uint32 Whirlwind_Timer;
    uint32 Thrash_Timer;
    uint32 SBash_Timer;
    uint32 FNova_Timer;
    uint32 WBolt_Timer;
    uint32 Heal_Timer;
    uint32 HNova_Timer;
    uint8  WBolt_count;
    uint32 Rend_Timer;
    uint32 Check_Timer;
    
    void Reset()
    {
        switch(m_creature->GetEntry())
        {
            case NETHERSTRAND_LONGBOW:
                Shoot_Timer      = 2000;
                MultiShoot_Timer = 16000;
            break;
            case DEVASTATION:
                Whirlwind_Timer  = 30000;              // Every 30 s
            break;                
            case COSMIC_INFUSER:
                Heal_Timer      = 1000;               // To remove stress from core
                HNova_Timer     = 10000+rand()%10000; // 10-20 s
            break;
            case INFINITY_BLADES:
                Thrash_Timer    = 10000;              // Poprawne czasy znalezc !
            break;
            case PHASESHIFT_BULWARK:
                SBash_Timer     = 12000;
                m_creature->CastSpell(m_creature,SPELL_BULWARK_SSPIKE,true);
            break;
            case STAFF_OF_DISINTEGRATION:
                WBolt_Timer     = 3000;               // Poprawne czasy znalezc !
                WBolt_count     = 0;
                FNova_Timer     = 12000;
            break;            
        }
        Check_Timer = 3000;
        Rend_Timer = 2000;
    }
    
    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (m_creature->Attack(who, false))
        {
            m_creature->AddThreat(who, 0.0f);
            m_creature->SetInCombatWith(who);
            who->SetInCombatWith(m_creature);

            if(m_creature->GetEntry() == NETHERSTRAND_LONGBOW)
                m_creature->GetMotionMaster()->MoveChase(who,15.0f);
            else
                DoStartMovement(who);
        }
    }

    void Aggro(Unit *who) { }
    
    void DoRangedAttackIfReady(const uint32 diff)
    {
        if(Shoot_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_BOW_SHOOT,false);
            Shoot_Timer = 2000;
        }else Shoot_Timer -= diff;
    }
    
    void DamageTaken(Unit* done_by, uint32 &damage)
    {
        if(m_creature->IsWithinDistInMap(done_by, 5.0f, false))
        {
            if(m_creature->GetEntry() == NETHERSTRAND_LONGBOW)
                DoResetThreat();
         }
    }
    
    Unit *CheckIfAdvisorNeedHeal()
    {
        if(!pInstance)
            return NULL;

        if(Creature* kael = Creature::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
        {
            for(uint8 i = 0; i < 7; ++i)
            {
                if(Unit* adv = Unit::GetUnit((*m_creature), ((boss_kaelthasAI*)kael->AI())->WeaponGuid[i]))
                    if (adv->isAlive() && adv->GetHealth() / adv->GetMaxHealth() < .2)
                        return adv; 
            } 
        }
        return NULL;        
    }
    
    void UpdateAI(const uint32 diff)
    {
      
        if(!UpdateVictim())
            return;

        if(Creature* kael = Creature::GetCreature((*m_creature), pInstance->GetData64(DATA_KAELTHAS)))
        {
            //Check_Timer
            if(Check_Timer < diff)
            {
                WorldLocation wLoc = ((boss_kaelthasAI*)kael->AI())->wLoc;
                if(m_creature->GetDistance(wLoc.x,wLoc.y,wLoc.z) > 200.0f)
                    EnterEvadeMode();
                else
                    DoZoneInCombat();
            
                 Check_Timer = 3000;
             }else Check_Timer -= diff;
        }


        switch(m_creature->GetEntry())
        {
            case NETHERSTRAND_LONGBOW:

                if(MultiShoot_Timer < diff)
                {
                    // DoCast(m_creature,SPELL_BOW_BLINK); ! Need to manualy relocate it xF
                    DoCast(m_creature->getVictim(),SPELL_BOW_MULTISHOOT,false);
                    MultiShoot_Timer = 15000;
                }else MultiShoot_Timer -= diff;
                
                DoRangedAttackIfReady(diff);
            break;
            case DEVASTATION:

                if(Whirlwind_Timer < diff)
                {
                    DoCast(m_creature,SPELL_DEVASTATION_WW,false);
                    Whirlwind_Timer = 30000;
                }else Whirlwind_Timer -= diff; 
                
                DoMeleeAttackIfReady();
            break;                
            case COSMIC_INFUSER:
                
                if(Heal_Timer < diff)
                {
                    if(Unit* adv = CheckIfAdvisorNeedHeal())
                    {
                        DoCast(adv,SPELL_INFUSER_HEAL,false);
                        Heal_Timer = 10000;
                    }else Heal_Timer = 5000;                     
                }else Heal_Timer -= diff;
                
                if(HNova_Timer < diff)
                {
                    DoCast(m_creature,SPELL_INFUSER_HNOVA,false);
                    HNova_Timer = 10000+rand()%10000; 
                }else HNova_Timer -= diff;
                
                DoMeleeAttackIfReady();
            break;
            case INFINITY_BLADES:
                
                if(Thrash_Timer < diff)
                {
                    m_creature->CastSpell(m_creature,SPELL_BLADE_TRASH,false);
                    Thrash_Timer = 10000;
                }else Thrash_Timer -= diff;
                
                DoMeleeAttackIfReady();
            break;
            case PHASESHIFT_BULWARK:
                
                if(SBash_Timer < diff)
                {
                    if(Unit* random = SelectUnit(SELECT_TARGET_RANDOM,0,7,true))
                        m_creature->CastSpell(random,SPELL_BULWARK_SBASH,false);

                    SBash_Timer = 12000;
                }else SBash_Timer -= diff;

                DoMeleeAttackIfReady();
            break;
            case STAFF_OF_DISINTEGRATION:

                if(WBolt_Timer < diff)
                {
                    DoCast(m_creature->getVictim(),SPELL_STAFF_WBOLT,false);
                    WBolt_count++;
                    WBolt_Timer = (WBolt_count < 4) ? 3000 : 10000;
                    
                    if(WBolt_count > 3) 
                        WBolt_count = 0;
                
                }else WBolt_Timer -= diff;

                if(FNova_Timer < diff)
                {
                    DoCast(m_creature,SPELL_STAFF_FNOVA,false);
                    FNova_Timer = 18000;
                }else FNova_Timer -= diff;
                 
                DoMeleeAttackIfReady();
            break;
            case WARP_SLICER:
                
                if(Rend_Timer <= diff)
                {
                    if(Aura * aur = m_creature->GetAura(SPELL_WARP_REND,0))
                        if(aur && aur->GetStackAmount() < 10)
                            m_creature->CastSpell(m_creature->getVictim(),SPELL_WARP_REND,true);
                    Rend_Timer = 2000;
                }else Rend_Timer -= diff;
                
                DoMeleeAttackIfReady();
            break;
            default:
                DoMeleeAttackIfReady();
            break;

        } 
    }
};

CreatureAI* GetAI_boss_kaelthas(Creature *_Creature)
{
    return new boss_kaelthasAI (_Creature);
}

CreatureAI* GetAI_boss_thaladred_the_darkener(Creature *_Creature)
{
    return new boss_thaladred_the_darkenerAI (_Creature);
}

CreatureAI* GetAI_boss_lord_sanguinar(Creature *_Creature)
{
    return new boss_lord_sanguinarAI (_Creature);
}

CreatureAI* GetAI_boss_grand_astromancer_capernian(Creature *_Creature)
{
    return new boss_grand_astromancer_capernianAI (_Creature);
}

CreatureAI* GetAI_boss_master_engineer_telonicus(Creature *_Creature)
{
    return new boss_master_engineer_telonicusAI (_Creature);
}

CreatureAI* GetAI_mob_kael_flamestrike(Creature *_Creature)
{
    return new mob_kael_flamestrikeAI (_Creature);
}

CreatureAI* GetAI_mob_phoenix_tk(Creature *_Creature)
{
    return new mob_phoenix_tkAI (_Creature);
}

CreatureAI* GetAI_mob_phoenix_egg_tk(Creature *_Creature)
{
    return new mob_phoenix_egg_tkAI (_Creature);
}
CreatureAI* GetAI_mob_nether_vapor(Creature *_Creature)
{
    return new mob_nether_vaporAI (_Creature);
}
CreatureAI* GetAI_weapon_advisor(Creature *_Creature)
{
    return new weapon_advisorAI (_Creature);
}
void AddSC_boss_kaelthas()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_kaelthas";
    newscript->GetAI = &GetAI_boss_kaelthas;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="boss_thaladred_the_darkener";
    newscript->GetAI = &GetAI_boss_thaladred_the_darkener;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="boss_lord_sanguinar";
    newscript->GetAI = &GetAI_boss_lord_sanguinar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="boss_grand_astromancer_capernian";
    newscript->GetAI = &GetAI_boss_grand_astromancer_capernian;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="boss_master_engineer_telonicus";
    newscript->GetAI = &GetAI_boss_master_engineer_telonicus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name= "mob_kael_flamestrike";
    newscript->GetAI = &GetAI_mob_kael_flamestrike;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_phoenix_tk";
    newscript->GetAI = &GetAI_mob_phoenix_tk;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_phoenix_egg_tk";
    newscript->GetAI = &GetAI_mob_phoenix_egg_tk;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_nether_vapor";
    newscript->GetAI = &GetAI_mob_nether_vapor;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "weapon_advisor";
    newscript->GetAI = &GetAI_weapon_advisor;
    newscript->RegisterSelf();
}

