#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Function to set the least significant bit of a pixel channel
void setLSB(uchar &pixel, bool bit) {
    if (bit)
        pixel |= 1;  // Set LSB to 1
    else
        pixel &= ~1; // Set LSB to 0
}

int main(int argc, char** argv) {
    // Check for valid input arguments
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <image> <textfile> <output_image>" << endl;
        return -1;
    }

    // Read input image
    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Open the text file to hide
    ifstream file(argv[2], ios::binary);
    if (!file.is_open()) {
        cout << "Could not open the text file." << endl;
        return -1;
    }

    // Check output file format
    string filePath = argv[3];
    string fileExtension = filePath.substr(filePath.find_last_of(".") + 1);
    if (fileExtension == "jpg" || fileExtension == "jpeg") {
        cout << "Warning: JPEG is a lossy format and may alter the encoded data. Use PNG or BMP for best results." << endl;
    }

    // Variables to keep track of text encoding
    char ch;
    int bitPos = 0;
    
    // Read first character from the text file
    file.get(ch);
    
    bool messageEnded = false;
    for (int row = 0; row < image.rows && !messageEnded; row++) {
        for (int col = 0; col < image.cols && !messageEnded; col++) {
            // Access each pixel in the image (3 channels: B, G, R)
            Vec3b &pixel = image.at<Vec3b>(row, col);

            // Encode 3 bits of the character across B, G, and R channels
            setLSB(pixel[0], (ch >> (7 - bitPos)) & 1); // Blue channel
            bitPos++;
            if (bitPos < 8) {
                setLSB(pixel[1], (ch >> (7 - bitPos)) & 1); // Green channel
                bitPos++;
            }
            if (bitPos < 8) {
                setLSB(pixel[2], (ch >> (7 - bitPos)) & 1); // Red channel
                bitPos++;
            }

            // Move to the next character when 8 bits are encoded
            if (bitPos == 8) {
                bitPos = 0;
                file.get(ch);  // Move to the next character
                if (file.eof()) {
                    messageEnded = true;
                }
            }
        }
    }

    // Save the modified image with encoded text
    imwrite(argv[3], image);

    cout << "Text successfully encoded into image." << endl;

    return 0;
}
