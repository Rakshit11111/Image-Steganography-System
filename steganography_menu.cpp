#include <iostream>
#include <cstdlib> // For system()
#include <string>
using namespace std;

// Fixed paths for files
const string inputFilePath = "/Users/rakshit/Desktop/SteganographyProject/11.png";
const string textFilePath = "/Users/rakshit/Desktop/SteganographyProject/basic_text.txt";
const string outputImagePath = "/Users/rakshit/Desktop/SteganographyProject/output_image.png";
const string decodedTextPath = "/Users/rakshit/Desktop/SteganographyProject/decoded_text.txt";

void encodeImage() {
    cout << "Using input image: " << inputFilePath << endl;
    cout << "Using text file: " << textFilePath << endl;
    cout << "Output will be saved to: " << outputImagePath << endl;

    string command = "./encode " + inputFilePath + " " + textFilePath + " " + outputImagePath;
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Encoding completed successfully. Generated image: " << outputImagePath << endl;
    } else {
        cout << "Error during encoding process.\n";
    }
}

void compileHistogramAnalysis() {
    string command = "g++ histogram_analysis.cpp -o histogram_analysis -std=c++17 `pkg-config --cflags --libs opencv4`";
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Histogram analysis program compiled successfully.\n";
    } else {
        cout << "Error compiling histogram analysis program.\n";
    }
}

void runHistogramAnalysis() {
    cout << "Using input image: " << inputFilePath << endl;
    cout << "Using encoded image: " << outputImagePath << endl;

    string command = "./histogram_analysis " + inputFilePath + " " + outputImagePath;
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Histogram analysis completed successfully.\n";
    } else {
        cout << "Error during histogram analysis.\n";
    }
}

void compileDecodeProgram() {
    string command = "g++ /Users/rakshit/Desktop/SteganographyProject/decode_text_from_image.cpp -o decode_text_from_image -std=c++17 `pkg-config --cflags --libs opencv4`";
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Decoding program compiled successfully.\n";
    } else {
        cout << "Error compiling decoding program.\n";
    }
}

void decodeImage() {
    cout << "Using encoded image: " << outputImagePath << endl;
    cout << "Decoded text will be saved to: " << decodedTextPath << endl;

    string command = "./decode_text_from_image " + outputImagePath + " " + decodedTextPath;
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Decoding completed successfully. Decoded text saved to: " << decodedTextPath << endl;
    } else {
        cout << "Error during decoding process.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Steganography Project Menu ---\n";
        cout << "1. Encode Image\n";
        cout << "2. Compile Histogram Analysis Program\n";
        cout << "3. Run Histogram Analysis\n";
        cout << "4. Compile Decoding Program\n";
        cout << "5. Decode Image\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                encodeImage();
                break;
            case 2:
                compileHistogramAnalysis();
                break;
            case 3:
                runHistogramAnalysis();
                break;
            case 4:
                compileDecodeProgram();
                break;
            case 5:
                decodeImage();
                break;
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
