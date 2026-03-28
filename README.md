# Puzzle

![C++ Builder](https://img.shields.io/badge/C%2B%2B%20Builder-6.0-00599C?style=flat&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/platform-Windows-0078D6?style=flat&logo=windows&logoColor=white)
![VCL](https://img.shields.io/badge/framework-VCL-blueviolet?style=flat)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat)

Jigsaw puzzle game built with C++ Builder 6.0 as an engineering degree thesis project. Features multiple difficulty levels, save/load game persistence, a high score leaderboard with player profiles, MIDI audio playback, and an animated AVI intro sequence.

## Features

- **Multiple difficulty levels** -- four selectable grid sizes that control the number of puzzle pieces (easy through expert), toggled via the main menu
- **Mouse-driven gameplay** -- pick up, drag, and place puzzle pieces by clicking directly on the game canvas; pieces snap into position when placed correctly
- **Save and load system** -- persist the current game state to disk and restore it later; saved games are stored in the `Zapisane_Gry/` directory
- **High score leaderboard** -- tracks completion times per difficulty level; player names and scores are stored in the `Gracze/` directory
- **MIDI audio playback** -- background music via the Windows MCI (Media Control Interface); togglable from the Settings menu
- **Animated AVI intro** -- plays an intro video on startup using the `TMediaPlayer` component
- **Game-over animation** -- a timer-driven animation sequence plays upon puzzle completion before transitioning to the results screen
- **Multiple screens** -- dedicated forms for the intro (`mainintro`), gameplay (`main`), game loading (`laduj`), game saving (`zapisz`), high scores (`nwyniki`), and about dialog (`oprogramie`)
- **Player profiles** -- enter a player name when starting a new game; names persist across sessions for the leaderboard
- **Custom stack-based data structure** -- puzzle pieces are managed using a stack implementation for efficient piece tracking during gameplay
- **Keyboard support** -- key press events supplement mouse interaction for additional game controls

## Dependencies

| Dependency | Purpose |
|---|---|
| C++ Builder 6.0 | IDE and compiler |
| VCL (Visual Component Library) | GUI framework, canvas drawing, timers |
| Windows MCI | MIDI audio and AVI video playback |
| `TMediaPlayer` | VCL media playback component |

## Build Instructions

1. Open `PUZLE.BPR` in Borland C++ Builder 6.0.
2. Build the project (Ctrl+F9) or run directly (F9).
3. Ensure `intro.avi` and any required bitmap resources are present in the project directory.

## Project Structure

```
puzzle/
  PUZLE.BPR            # C++ Builder project file
  puzle.cpp            # WinMain entry point -- initializes all forms
  PUZLE.RES            # Compiled resource file
  wspolne.h            # Shared constants (grid size, directory paths)
  MAIN.CPP             # Gameplay form -- piece rendering, drag-and-drop, timer, menu
  MAIN.h               # Gameplay form header -- TForm1 class declaration
  MAIN.dfm             # Gameplay form layout
  mainintro.cpp        # Intro form -- AVI playback, startup animation
  mainintro.h          # Intro form header
  mainintro.dfm        # Intro form layout
  LADUJ.CPP            # Load game form -- file selection, game state deserialization
  LADUJ.h              # Load game form header
  LADUJ.dfm            # Load game form layout
  ZAPISZ.CPP           # Save game form -- file naming, game state serialization
  ZAPISZ.h             # Save game form header
  ZAPISZ.dfm           # Save game form layout
  nwyniki.cpp          # High scores form -- leaderboard display and entry
  nwyniki.h            # High scores form header
  nwyniki.dfm          # High scores form layout
  jimie.cpp            # Player name input form
  jimie.h              # Player name input form header
  jimie.dfm            # Player name input form layout
  oprogramie.cpp       # About dialog
  oprogramie.h         # About dialog header
  oprogramie.dfm       # About dialog layout
  intro.avi            # Intro animation video
  RES/                 # Bitmap and image resources
  Zapisane_Gry/        # Saved game files directory
  Gracze/              # Player profiles and high score data
```

## Presentation

[Engineering thesis presentation (Prezi)](https://prezi.com/mh6rxfmuftyk/praca-dyplomowa-inzynierska/)

## Screenshots

![image](https://user-images.githubusercontent.com/17749811/152383118-66fe0f0f-941c-4d1a-ba07-d44aee1936db.png)

![image](https://user-images.githubusercontent.com/17749811/152383080-b5f42b83-4b41-4672-9719-1de444f544ba.png)
