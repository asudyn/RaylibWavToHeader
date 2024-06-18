# Wav to Header Converter tool for Raylib

# What it does?
When placed in the same directory as .wav files it uses Raylib to convert data from all .wav files into a SoundsFX.h file containing raw data for all sound effects.

# Why?
While working on a very small and minimalistic game I wanted to pack all my sound effects into my executable. 

# Usage
- [Download](https://github.com/asudyn/RaylibWavToHeader/blob/master/Builds/Release/WavToHeaderConverter.exe) the converter or build it yourself.
- Place the converter in the same directory with your .wav files.
- Run it.
- Use SoundFX.h in your project.
 
# How do I use SoundFX.h?
Here's an example of code that creates a Wave from the exported data and then creates a playable sound from it.
```
	Wave FXGameOver = {};
	FXGameOver.frameCount = FXGAMEOVER_FRAME_COUNT;
	FXGameOver.sampleRate = FXGAMEOVER_SAMPLE_RATE;
	FXGameOver.sampleSize = FXGAMEOVER_SAMPLE_SIZE;
	FXGameOver.channels = FXGAMEOVER_CHANNELS;
	FXGameOver.data = FXGAMEOVER_DATA;
	Sound gameOverSound = LoadSoundFromWave(FXGameOver);
```
