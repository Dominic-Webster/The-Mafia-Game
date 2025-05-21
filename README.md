# THE MAFIA GAME
## Version 1.1.3

## THE CLASSIC SOCIAL DEDUCTION GAME

- Get A Secret Role!
- Figure Out Who The Computer Players Are!
- Eliminate The Town As A Mafia, Or Work With The Villagers To Stop The Killers!
- Can You Trust Anyone?

---

### DESCRIPTION

Have you ever wanted to play Mafia, but don't have the players?
Now you can play on your own, with 26 unique computer-controlled players!
You get a secret role every match, and must try to complete your objective, while preventing the other teams from completing theirs.
What's the catch? No one knows what roles the other players have.
Lie, evade, and eliminate your way to victory!

---

### ROLES

- Villager: You have no abilities, but the advantage of numbers. Eliminate the killers in court to save yourself and the rest of the village.
- Doctor: Every night, you can save one person from death. Work with the village to eliminate the killers.
- Detective: Every night, you can investigate one person to learn their role. Work with the village to eliminate the killers.
- Cop: You have two bullets. Every night, you can choose to shoot a player. However, shooting at an innocent will result in your death instead, so shoot wisely. Work with the village to eliminate the killers.
- Mafia: You may be outnumbered, but you know who your allies are. Work with them to kill one player every night. Your goal: eliminate the innocents.
- Fool: Chaos is your game. You only win if you are executed in court.
- Priest: You survive death once per game. Work with the village to eliminate the killers.
- Scholar: Your votes in court are tripled. Work with the village to eliminate the killers.
- Serial Killer: Wake up to kill a player every night. You win when you're the last person standing.
- Godfather: On the first night, convert someone to the Mafia. Wake up with the other mafia. Eliminate the innocents.

---

### HOW TO DOWNLOAD

- Copy this repository's url: https://github.com/Dominic-Webster/The-Mafia-Game.git
- In your terminal, clone the repository, and open the directory.

    ```console
    git clone <repository url>
    cd <repository directory>
    ```

- Run the command "make".
- To start the game, run "./play".

---

### Update History

#### UPDATE 1.1.3
05/21/2025
- New Role: Godfather
- Fixed bug where Priest couldn't detect who killed them, so it became a 50/50 between two killed players on who actually survived

#### UPDATE 1.1.2
05/20/2025
- Fixed bug where Mafia couldn't win if Serial Killer wasn't in the game
- Tweaked Serial Killer spawn chance
- Decreased chance for player to be a Villager
- Tweaked Serial Killer court actions
- Fixed bug where cops would technically shoot the Serial Killer, but people kept getting killed
- Updated the end of match information to show all character's roles

#### UPDATE 1.1.1
05/20/2025
- New Role: Serial Killer
- Detective and Fool buffed
- Minor bug fixes (such as Priest not always letting player survive)

#### UPDATE 1.1.0
05/20/2025
- Computer characters intelligence improved
- More day options for player
- New Role: Scholar
- Minor bug fixes

#### UPDATE 1.0.1
05/18/2025
- Minor bug fixes
- New Role: Priest

#### VERSION 1.0.0
05/18/2025
- Game Launched
- 26 Computer Players
- 6 Unique Roles: Villager, Mafia, Fool, Cop, Doctor, and Detective
