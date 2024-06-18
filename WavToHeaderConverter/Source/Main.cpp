#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "raylib.h"

std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

std::vector<std::string> getWavFiles(const std::filesystem::path& directory) {
	std::vector<std::string> wavFiles;
	for (const auto& entry : std::filesystem::directory_iterator(directory)) {
		if (entry.is_regular_file()) {
			std::string extension = entry.path().extension().string();
			if (toLower(extension) == ".wav") {
				wavFiles.push_back(entry.path().stem().string());
			}
		}
	}
	return wavFiles;
}

static void ExportWaveAsHeader(const std::string& soundName) {
	std::string inputPath = soundName + ".wav";
	std::string outputPath = soundName + ".h";
	Wave wave = LoadWave(inputPath.c_str());
	ExportWaveAsCode(wave, outputPath.c_str());
	UnloadWave(wave);
}

static void ConcatenateHeaders(const std::vector<std::string>& inputNames, const std::string& outputFile) {
	std::ofstream out(outputFile, std::ios::out | std::ios::trunc);
	if (!out.is_open()) {
		std::cerr << "Failed to open output file: " << outputFile << std::endl;
		return;
	}
	for (const std::string& inputName : inputNames) {
		std::string inputFile = inputName + ".h";
		std::ifstream in(inputFile, std::ios::in);
		if (!in.is_open()) {
			std::cerr << "Failed to open input file: " << inputFile << std::endl;
			continue;
		}
		out << in.rdbuf();
		out << "\n";
		in.close();
	}
	out.close();
	std::cout << "Files concatenated successfully into " << outputFile << std::endl;
}

int main()
{
    std::vector<std::string> wavFiles = getWavFiles(std::filesystem::current_path());
	if (wavFiles.empty()) {
		std::cout << "No .wav files found in the current directory." << std::endl;
    }else {
        for (int i = 0; i < wavFiles.size(); i++) {
            ExportWaveAsHeader(wavFiles[i]);
        }
        ConcatenateHeaders(wavFiles, "SoundFX.h");
		for (const std::string& wavFile : wavFiles) {
			std::string headerFile = wavFile + ".h";
			std::filesystem::remove(headerFile);
		}
    }
	std::cout << "Press enter to quit...";
	std::cin.get();
	return 0;
}