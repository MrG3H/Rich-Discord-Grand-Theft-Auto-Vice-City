# 🌴 Grand Theft Auto: Vice City - Discord Rich Presence (.asi)

![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows)
![Game](https://img.shields.io/badge/Game-GTA%20Vice%20City-purple?style=for-the-badge&logo=rockstargames)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)
![Discord](https://img.shields.io/badge/Discord-Rich%20Presence-5865F2?style=for-the-badge&logo=discord)

## 🇧🇷 Português (PT-BR)

Um plugin **.asi** moderno e otimizado que integra o **Discord Rich Presence** ao clássico **Grand Theft Auto: Vice City**. Mostre aos seus amigos exatamente o que você está fazendo em Vice City com detalhes precisos, ícones de armas e um sistema de status dinâmico.

### 📸 Funcionalidades

#### 🚗 Atividades e Cutscenes
* Detecta automaticamente se você está **"Andando a pé"** ou **"Dirigindo [Nome do Veículo]"**.
* Lista manual de veículos para garantir nomes corretos (ex: *Infernus, Cheetah, Police Car*).
* **Detecção de Cutscenes:** O status muda para "Assistindo Cutscene" automaticamente durante a história.

#### 🕵️ Missões e Localização
* **Sistema de Missão Inteligente:** Exibe "Missão: [Nome]" apenas quando você está jogando uma missão real (ignora scripts de fundo).
* **Localização Geográfica:** Utiliza um sistema de coordenadas matemáticas para identificar o bairro (ex: *Ocean Beach, Downtown*), corrigindo bugs de memória de versões modificadas do jogo.

#### 🔄 Status Rotativo (Ciclo Dinâmico)
A linha de status alterna informações a cada **3 segundos** para não poluir a tela:
1. ❤️ **Saúde:** Vida (HP) e Colete.
2. 📍 **Local:** Bairro/Zona atual.
3. ⭐ **Procurado:** Nível de estrelas (apenas se estiver sendo perseguido).
4. 🔫 **Missão:** Nome da missão atual (apenas se estiver em missão).
5. 💰 **Estado:** Dinheiro atual e Hora do jogo.

#### 🔫 Ícones de Armas
* Exibe o ícone da arma específica que o Tommy está segurando (Uzi, Python, Katana, etc.), com créditos no tooltip.

### ⚠️ Requisitos Obrigatórios

> [!IMPORTANT]
> Este mod depende de endereços de memória específicos. Para funcionar corretamente, você **DEVE** usar a versão correta do executável.

| Requisito | Detalhes |
| :--- | :--- |
| **Executável do Jogo** | **gta-vc.exe v1.0 US** (Tamanho aprox: **2.94 MB**).<br>❌ *Versões Steam/Rockstar Launcher (4-5MB) NÃO são suportadas. PODE TER FUNÇÕES QUE NÃO DETECTA, COMO ARMAS, MISSÃO ETC.* |
| **ASI Loader** | Necessário para carregar plugins .asi (Recomendado: [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader)). |
| **Bibliotecas** | Visual C++ Redistributable 2015-2022 (x86). |

### 📥 Instalação

1. Baixe a versão mais recente na aba **[Releases](../../releases)** deste repositório.
2. Extraia o arquivo `.zip`.
3. Copie os seguintes arquivos para a **pasta raiz** do seu GTA Vice City (onde fica o `gta-vc.exe`):
    * `VC_RichPresence.asi` (EM CASO DE NÃO FUNCIONAR, COLE NA PASTA `scripts`)
    * `discord-rpc.dll`
4. Abra o jogo e divirta-se! O status aparecerá automaticamente no seu perfil do Discord.

---

## 🇺🇸 English

A modern and optimized **Discord Rich Presence** plugin for **Grand Theft Auto: Vice City**. This lightweight `.asi` mod integrates seamlessly with your Discord profile, showing your friends exactly what you are doing in Vice City with precise details, active missions, custom weapon icons, and a dynamic status system.

### 📸 Features

#### 🚗 Activities & Cutscenes
* Automatically detects if you are **"On Foot"** or **"Driving [Vehicle Name]"**.
* Manual vehicle list ensures correct naming (e.g., *Infernus, Cheetah, Police Car*).
* **Cutscene Detection:** Status automatically changes to "Watching Cutscene" during story sequences.

#### 🕵️ Missions & Location
* **Smart Mission System:** Displays "Mission: [Name]" only when you are playing an actual mission (ignores background scripts).
* **Geographic Location:** Uses a coordinate-based system to identify the neighborhood (e.g., *Ocean Beach, Downtown*), fixing memory bugs present in modified game versions.

#### 🔄 Rotating Status (Dynamic Cycle)
The status line switches information every **3 seconds** to avoid screen clutter:
1. ❤️ **Health:** Health (HP) and Armor.
2. 📍 **Location:** Current Neighborhood/Zone.
3. ⭐ **Wanted:** Wanted Level (only if being chased).
4. 🔫 **Mission:** Current mission name (only if active).
5. 💰 **State:** Current Money and In-Game Time.

#### 🔫 Weapon Icons
* Displays the specific icon of the weapon Tommy is currently holding (Uzi, Python, Katana, etc.), with credits in the tooltip.

### ⚠️ Mandatory Requirements

> [!IMPORTANT]
> This mod relies on specific memory addresses. To work correctly, you **MUST** use the correct executable version.

| Requirement | Details |
| :--- | :--- |
| **Game Executable** | **gta-vc.exe v1.0 US** (Approx size: **2.94 MB**).<br>❌ *Steam/Rockstar Launcher versions (4-5MB) are NOT supported. FEATURES LIKE WEAPONS, MISSIONS, ETC. MAY NOT BE DETECTED IF YOU USE THESE VERSIONS.* |
| **ASI Loader** | Required to load .asi plugins (Recommended: [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader)). |
| **Libraries** | Visual C++ Redistributable 2015-2022 (x86). |

### 📥 Installation

1. Download the latest version from the **[Releases](../../releases)** tab of this repository.
2. Extract the `.zip` file.
3. Copy the following files to the **root folder** of your GTA Vice City (where `gta-vc.exe` is located):
    * `VC_RichPresence.asi` (IF IT DOESN'T WORK, TRY PASTING IT INTO THE `scripts` FOLDER)
    * `discord-rpc.dll`
4. Open the game and enjoy! The status will automatically appear on your Discord profile.

---

## 🤝 Credits / Créditos

* **Developed by / Desenvolvido por:** [MrGeH](https://github.com/MrG3H)
* **Based on / Baseado em:** [Plugin SDK](https://github.com/DK22Pac/plugin-sdk)
* **Technology / Tecnologia:** Discord RPC

---

> *This project is a fan-made modification and is not affiliated with Rockstar Games or Take-Two Interactive.*

---

###### 🏷️ Tags / Keywords
`Rich Discord GTA VC` • `Rich Discord Grand Theft Auto Vice City` • `Discord RPC GTA VC` • `Grand Theft Auto Vice City Discord Rich Presence` • `gta vc discord rpc` • `discord rpc grand theft auto vice city` • `GTA VC Discord Rich Presence`
