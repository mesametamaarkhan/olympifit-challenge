# 🏅 OlympiFit Challenge (SFML + C++)

OlympiFit Challenge is a story-based fitness adventure game built in C++ using the SFML (Simple and Fast Multimedia Library). Take on unique side quests like trivia challenges, plane combat, and obstacle dodging to earn points. Use those points to train in the gym and boost your fitness level before entering the final Olympic challenge.

---

## 🚀 Game Highlights

- 🎯 Story-driven fitness game
- 🎮 Includes mini-games:
  - 🧠 Olympic trivia
  - ✈️ Aero Assault (plane shooter)
  - 🕹️ Obstacle Overdrive (dodge game)
- 💪 Earn points to level up in the gym
- 🏆 Participate in an Olympic finale
- 🎨 2D graphics and smooth gameplay with SFML

---

## ⚠️ Important

👉 **Please read the in-game instructions page carefully before starting.**  
It explains how to navigate quests, train, and unlock the final Olympic event.

---

## 🛠️ Installation

### Step 1: Install SFML

```bash
sudo apt update
sudo apt install libsfml-dev
g++ src/main.cpp -o olympifit -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./olympifit
