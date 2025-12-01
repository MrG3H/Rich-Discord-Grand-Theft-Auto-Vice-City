/*
    GTA Vice City Discord RPC
    - BY:  MrGeH
    - Idioma: PT-BR.
*/

#include "plugin.h"
#include "CWorld.h"
#include "CClock.h"
#include "CText.h"
#include "CModelInfo.h"
#include "CMenuManager.h"
#include "CTheScripts.h" 
#include "discord_rpc.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

using namespace plugin;

static const char* APPLICATION_ID = "1444169612374704283";

class ViceCityRPC {
public:
    ViceCityRPC() {
        Events::gameProcessEvent += [] { UpdateDiscord(); };
        Events::shutdownRwEvent += [] { Discord_Shutdown(); };
    }

    static void InitDiscord() {
        DiscordEventHandlers handlers;
        memset(&handlers, 0, sizeof(handlers));
        Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
    }

    static void GxtCharToUTF8(const wchar_t* src, char* dest, int destSize) {
        if (!src || src[0] == L'\0') { dest[0] = '\0'; return; }
        WideCharToMultiByte(CP_UTF8, 0, src, -1, dest, destSize, NULL, NULL);
    }

    static bool IsValidPointer(void* ptr, size_t size) {
        return !IsBadReadPtr(ptr, size);
    }

    // --- MAPA GEOGRÁFICO ---
    static const char* GetZoneFromCoords(float x, float y) {
        // Ilha Oeste
        if (x < -230.0f) {
            if (y > 600.0f) {
                if (x < -680.0f && y > 1100.0f) return "Est\xC3\xA1" "dio Hyman";
                return "Centro (Downtown)";
            }
            if (y > -200.0f) {
                if (x < -920.0f && y > 200.0f) return "Ferro-Velho";
                return "Little Haiti";
            }
            if (y > -1000.0f) return "Little Havana";
            if (y > -1800.0f) {
                if (x > -600.0f) return "Porto de Vice City";
                return "Aeroporto Escobar";
            }
            return "Base A\xC3\xA9" "rea Fort Baxter";
        }
        // Ilha Leste
        else if (x > 150.0f) {
            if (y > 900.0f) return "Shopping North Point";
            if (y > -300.0f) return "Vice Point";
            if (y > -900.0f) return "Washington Beach";
            return "Ocean Beach";
        }
        // Ilhas Centrais
        else {
            if (y > 200.0f) {
                if (x > -100.0f) return "Est\xC3\xBA" "dios de Cinema";
                return "Prawn Island";
            }
            if (y > -250.0f) return "Clube de Golfe";
            if (y <= -250.0f && y > -800.0f) return "Starfish Island (Mans\xC3\xA3o)";
            return "Travessia / Ponte";
        }
        return "Mar de Vice City";
    }

    // --- LISTA DE VEÍCULOS ---
    static const char* GetCleanVehicleName(int modelID) {
        switch (modelID) {
        case 130: return "Landstalker"; case 131: return "Idaho"; case 132: return "Stinger";
        case 133: return "Linerunner"; case 134: return "Perennial"; case 135: return "Sentinel";
        case 136: return "Rio"; case 137: return "Caminh\xC3\xA3o de Bombeiro"; case 138: return "Caminh\xC3\xA3o de Lixo";
        case 139: return "Limousine"; case 140: return "Manana"; case 141: return "Infernus";
        case 142: return "Voodoo"; case 143: return "Pony"; case 144: return "Mule";
        case 145: return "Cheetah"; case 146: return "Ambul\xC3\xA2ncia"; case 147: return "FBI Washington";
        case 148: return "Moonbeam"; case 149: return "Esperanto"; case 150: return "Taxi";
        case 151: return "Washington"; case 152: return "Bobcat"; case 153: return "Caminh\xC3\xA3o de Sorvete";
        case 154: return "BF Injection"; case 155: return "Hunter (Helic\xC3\xB3ptero)"; case 156: return "Viatura Policial";
        case 157: return "Enforcer (SWAT)"; case 158: return "Carro Forte"; case 159: return "Banshee";
        case 160: return "Barco Policial"; case 161: return "\xC3\x94" "nibus"; case 162: return "Tanque Rhino";
        case 163: return "Caminh\xC3\xA3o do Ex\xC3\xA9rcito"; case 164: return "Cuban Hermes"; case 165: return "Helic\xC3\xB3ptero";
        case 166: return "Angel (Moto)"; case 167: return "\xC3\x94" "nibus de Viagem"; case 168: return "Cabbie (Taxi)";
        case 169: return "Stallion"; case 170: return "Rumpo"; case 171: return "RC Carrinho";
        case 172: return "Carro Funer\xC3\xA1rio"; case 173: return "Caminh\xC3\xA3o Cegonha"; case 174: return "Sentinel XS";
        case 175: return "Admiral"; case 176: return "Squalo (Lancha)"; case 177: return "Seasparrow";
        case 178: return "Moto de Pizza"; case 179: return "Van da Gangue"; case 180: return "Avi\xC3\xA3o";
        case 181: return "Dodo"; case 182: return "Lancha Speeder"; case 183: return "Barco de Pesca";
        case 184: return "Tropic"; case 185: return "Caminh\xC3\xA3o Flatbed"; case 186: return "Yankee";
        case 187: return "Carrinho de Golf"; case 188: return "Zebra Cab"; case 189: return "Van Top Fun";
        case 190: return "Hidroavi\xC3\xA3o"; case 191: return "PCJ 600"; case 192: return "Faggio (Scooter)";
        case 193: return "Freeway"; case 194: return "RC Avi\xC3\xA3o"; case 195: return "RC Helic\xC3\xB3ptero";
        case 196: return "Glendale"; case 197: return "Oceanic"; case 198: return "Sanchez (Moto)";
        case 199: return "Sparrow"; case 200: return "Patriot"; case 201: return "Limousine Love Fist";
        case 202: return "Guarda Costeira"; case 203: return "Bote"; case 204: return "Hermes";
        case 205: return "Sabre"; case 206: return "Sabre Turbo"; case 207: return "Phoenix";
        case 208: return "Walton"; case 209: return "Regina"; case 210: return "Comet";
        case 211: return "Deluxo"; case 212: return "Van Burrito"; case 213: return "Caminh\xC3\xA3o Spand";
        case 214: return "Marquis (Veleiro)"; case 215: return "Carrinho de Bagagem"; case 216: return "Taxi Kaufman";
        case 217: return "Maverick"; case 218: return "Maverick Jornal"; case 219: return "Rancher";
        case 220: return "FBI Rancher"; case 221: return "Virgo"; case 222: return "Greenwood";
        case 223: return "Lancha Jetmax"; case 224: return "Carro de Corrida"; case 225: return "Sandking";
        case 226: return "Blista Compact"; case 227: return "Viatura Civil";
        case 228: return "Boxville"; case 229: return "Caminh\xC3\xA3o Benson"; case 230: return "Mesa Grande";
        case 231: return "RC Goblin"; case 232: return "Carro de Corrida A"; case 233: return "Carro de Corrida B";
        case 234: return "Carro de Demoli\xC3\xA7\xC3\xA3o A"; case 235: return "Carro de Demoli\xC3\xA7\xC3\xA3o B"; case 236: return "Viatura Cheetah";
        default: return NULL;
        }
    }

    // --- LISTA DE MISSÕES ---
    static const char* GetCleanMissionName(const char* internalName) {
        if (!internalName || strlen(internalName) < 3) return NULL;
        // --- PRINCIPAL ---
        if (_strnicmp(internalName, "ken1", 4) == 0) return "A Festa";
        if (_strnicmp(internalName, "ken2", 4) == 0) return "Briga no Beco";
        if (_strnicmp(internalName, "ken3", 4) == 0) return "F\xC3\xBAria do J\xC3\xBAri";
        if (_strnicmp(internalName, "ken4", 4) == 0) return "Tumulto";
        if (_strnicmp(internalName, "avery1", 6) == 0) return "Ferro Neles";
        if (_strnicmp(internalName, "avery2", 6) == 0) return "Demoli\xC3\xA7\xC3\xA3o";
        if (_strnicmp(internalName, "avery3", 6) == 0) return "Duas Pontas";
        if (_strnicmp(internalName, "col1", 4) == 0) return "Porco Traidor";
        if (_strnicmp(internalName, "col2", 4) == 0) return "Tiroteio no Shopping";
        if (_strnicmp(internalName, "col3", 4) == 0) return "Anjos da Guarda";
        if (_strnicmp(internalName, "col4", 4) == 0) return "Senhor, Sim Senhor!";
        if (_strnicmp(internalName, "col5", 4) == 0) return "Todos a Bordo!";
        if (_strnicmp(internalName, "diaz1", 5) == 0) return "A Persegui\xC3\xA7\xC3\xA3o";
        if (_strnicmp(internalName, "diaz2", 5) == 0) return "Phnom Penh '86";
        if (_strnicmp(internalName, "diaz3", 5) == 0) return "O Barco mais R\xC3\xA1pido";
        if (_strnicmp(internalName, "diaz4", 5) == 0) return "Oferta e Demanda";
        if (_strnicmp(internalName, "diaz5", 5) == 0) return "Apagando";
        if (_strnicmp(internalName, "kent1", 5) == 0) return "Corredor da Morte";
        if (_strnicmp(internalName, "love1", 5) == 0) return "Suco do Amor";
        if (_strnicmp(internalName, "love2", 5) == 0) return "Assassino Psicopata";
        if (_strnicmp(internalName, "love3", 5) == 0) return "Tour Publicit\xC3\xA1rio";
        if (_strnicmp(internalName, "baron", 5) == 0) return "Extors\xC3\xA3o";
        if (_strnicmp(internalName, "baron2", 6) == 0) return "Briga de Bar";
        if (_strnicmp(internalName, "baron3", 6) == 0) return "Terra de Tira";
        if (_strnicmp(internalName, "cap", 3) == 0)   return "Vencendo a Parada";
        if (_strnicmp(internalName, "final", 5) == 0) return "Mantenha seus Amigos Perto";

        // Secundárias
        if (_strnicmp(internalName, "taxidr", 6) == 0) return "Taxista";
        if (_strnicmp(internalName, "pizzaboy", 8) == 0) return "Entregador de Pizza";
        if (_strnicmp(internalName, "firetru", 7) == 0) return "Bombeiro";
        if (_strnicmp(internalName, "polma", 5) == 0) return "Vigilante";
        if (_strnicmp(internalName, "ambulan", 7) == 0) return "Param\xC3\xA9""dico";
        if (_strnicmp(internalName, "bud", 3) == 0) return "Checkpoint Charlie";
        if (_strnicmp(internalName, "ice", 3) == 0) return "Distribui\xC3\xA7\xC3\xA3o";
        if (_strnicmp(internalName, "porn1", 5) == 0) return "Recrutamento";
        if (_strnicmp(internalName, "porn2", 5) == 0) return "Dildo Dodo";
        if (_strnicmp(internalName, "porn3", 5) == 0) return "Foto Policial";
        if (_strnicmp(internalName, "porn4", 5) == 0) return "Ponto G";
        if (_strnicmp(internalName, "taxi1", 5) == 0) return "V.I.P.";
        if (_strnicmp(internalName, "taxi2", 5) == 0) return "Rivalidade Amistosa";
        if (_strnicmp(internalName, "taxi3", 5) == 0) return "Cabmaggedon";
        if (_strnicmp(internalName, "bank", 4) == 0) return "O Assalto";
        if (_strnicmp(internalName, "dr", 2) == 0) return "O Motorista";
        if (_strnicmp(internalName, "shoot", 5) == 0) return "O Atirador";
        if (_strnicmp(internalName, "sun", 3) == 0) return "Sunshine Autos";
        if (_strnicmp(internalName, "cuban1", 6) == 0) return "Desafio do Barco";
        if (_strnicmp(internalName, "cuban2", 6) == 0) return "Carne de Canh\xC3\xA3o";
        if (_strnicmp(internalName, "cuban3", 6) == 0) return "Encontro Naval";
        if (_strnicmp(internalName, "cuban4", 6) == 0) return "Vodu de Tr\xC3\xB3ia";
        if (_strnicmp(internalName, "haiti1", 6) == 0) return "Juju";
        if (_strnicmp(internalName, "haiti2", 6) == 0) return "Bombas Fora!";
        if (_strnicmp(internalName, "haiti3", 6) == 0) return "Poeira Suja";
        if (_strnicmp(internalName, "phil1", 5) == 0) return "Contrabandista de Armas";
        if (_strnicmp(internalName, "phil2", 5) == 0) return "Boomshine Saigon";
        if (_strnicmp(internalName, "biker1", 6) == 0) return "Rodas de A\xC3\xA7o";
        if (_strnicmp(internalName, "biker2", 6) == 0) return "Mexendo com o Homem";
        if (_strnicmp(internalName, "biker3", 6) == 0) return "Moto Amarrada";

        return NULL;
    }
    // -- ARMAS --
    static const char* GetWeaponImageKey(int weaponID) {
        if (weaponID < 0 || weaponID > 36) return "logo_vc_large";
        const char* keys[] = {
            "weapon_fist", // ID 0 - Punho
            "weapon_brassknuckle", "weapon_screwdriver", "weapon_golfclub",
            "weapon_nightstick", "weapon_knife", "weapon_baseballbat", "weapon_hammer",
            "weapon_cleaver", "weapon_machete", "weapon_katana", "weapon_chainsaw",
            "weapon_grenade", "weapon_detonator", "weapon_teargas", "weapon_molotov",
            "weapon_rocket", "weapon_colt45", "weapon_python", "weapon_shotgun",
            "weapon_spaz", "weapon_stubby", "weapon_tec9", "weapon_uzi",
            "weapon_ingram", "weapon_mp5", "weapon_m4", "weapon_ruger",
            "weapon_sniper", "weapon_lasersniper", "weapon_rocket", "weapon_flamethrower",
            "weapon_m60", "weapon_minigun", "weapon_detonator", "logo_vc_large", "weapon_camera"
        };
        return keys[weaponID];
    }

    static void UpdateDiscord() {
        static bool isInitialized = false;
        if (!isInitialized) { InitDiscord(); isInitialized = true; }

        static DWORD lastTime = 0;
        static int currentCycle = 0;
        if (GetTickCount() - lastTime > 3000) {
            currentCycle++; if (currentCycle > 4) currentCycle = 0;
            lastTime = GetTickCount();
        }

        // --- CUTSCENE CHECK ---
        unsigned char wideScreen = *(unsigned char*)0x7E46F5;
        if (wideScreen > 0) {
            DiscordRichPresence presence;
            memset(&presence, 0, sizeof(presence));
            presence.state = "Hist\xC3\xB3ria - Assistindo Cutscene";
            presence.largeImageKey = "logo_vc_large";
            Discord_UpdatePresence(&presence);
            return;
        }

        if (FrontEndMenuManager.m_bMenuActive) {
            DiscordRichPresence p; memset(&p, 0, sizeof(p));
            p.state = "No Menu - Pausado"; p.largeImageKey = "logo_vc_large";
            Discord_UpdatePresence(&p); return;
        }

        CPlayerPed* player = FindPlayerPed();
        if (!player) return;

        DiscordRichPresence presence;
        memset(&presence, 0, sizeof(presence));
        presence.largeImageKey = "logo_vc_large";
        presence.largeImageText = "GTA: Vice City";

        // --- 1. LOCALIZAÇÃO ---
        CVector pos = player->GetPosition();
        char locationBuffer[64];
        sprintf_s(locationBuffer, "Local: %s", GetZoneFromCoords(pos.x, pos.y));

        // --- 2. MISSÃO ---
        char missionDisplayBuffer[128] = "";
        bool inMission = false;

        CRunningScript* script = CTheScripts::pActiveScripts;
        int safeLoop = 0;

        while (script && safeLoop < 200) {
            if (IsValidPointer(script, sizeof(CRunningScript))) {
                if (script->m_bIsMission) {
                    char internalName[9];
                    if (IsValidPointer(script->m_szName, 8)) {
                        strncpy_s(internalName, script->m_szName, 8);
                        internalName[8] = '\0';

                        bool isValid = true;
                        if (strlen(internalName) < 3) isValid = false;
                        for (int i = 0; i < strlen(internalName); i++) {
                            if (!isalnum((unsigned char)internalName[i]) && internalName[i] != '_') isValid = false;
                        }

                        if (isValid) {
                            const char* clean = GetCleanMissionName(internalName);
                            if (clean) {
                                sprintf_s(missionDisplayBuffer, "Miss\xC3\xA3o: %s", clean);
                                inMission = true;
                                break;
                            }
                            else {
                                sprintf_s(missionDisplayBuffer, "Miss\xC3\xA3o: %s", internalName);
                                inMission = true;
                            }
                        }
                    }
                }
                script = script->m_pNext;
            }
            else { break; }
            safeLoop++;
        }

        // --- 3. ATIVIDADE & VEÍCULO ---
        char activityBuffer[128];
        bool isInCar = false;
        if (player->m_bInVehicle && player->m_pVehicle) {
            isInCar = true;
            int model = player->m_pVehicle->m_nModelIndex;
            const char* cleanVeh = GetCleanVehicleName(model);
            if (cleanVeh) sprintf_s(activityBuffer, "Dirigindo %s", cleanVeh);
            else sprintf_s(activityBuffer, "Dirigindo Ve\xC3\xAD" "culo");
        }
        else {
            sprintf_s(activityBuffer, "Andando a p\xC3\xA9");
        }

        // --- 4. STATUS ---
        char healthBuffer[64];
        sprintf_s(healthBuffer, "Vida: %d | Colete: %d", (int)player->m_fHealth, (int)player->m_fArmour);

        // --- 5. DINHEIRO ---
        char moneyBuffer[64];
        sprintf_s(moneyBuffer, "R$%d | %02d:%02d",
            CWorld::Players[0].m_nMoney, CClock::ms_nGameClockHours, CClock::ms_nGameClockMinutes);

        // APLICAÇÃO
        presence.details = activityBuffer;

        switch (currentCycle) {
        case 0: presence.state = healthBuffer; break;
        case 1: presence.state = locationBuffer; break;
        case 2: // Procurado
            if (player->m_pWanted->m_nWantedLevel > 0) {
                char w[32]; sprintf_s(w, "N\xC3\xADvel de Procurado: %d", player->m_pWanted->m_nWantedLevel);
                presence.state = w;
            }
            else { presence.state = moneyBuffer; currentCycle++; }
            break;
        case 3: // Missão
            if (inMission) presence.state = missionDisplayBuffer;
            else { presence.state = moneyBuffer; currentCycle++; }
            break;
        case 4: presence.state = moneyBuffer; break;
        }

        // Arma
        int weaponID = 0;
        unsigned char slot = *(unsigned char*)((unsigned int)player + 0x504);
        if (slot < 13) weaponID = player->m_aWeapons[slot].m_eWeaponType;

        presence.smallImageKey = GetWeaponImageKey(weaponID);
                presence.smallImageText = "Feito por: MrGeH";

        Discord_RunCallbacks();
        Discord_UpdatePresence(&presence);
    }
} viceCityRPC;