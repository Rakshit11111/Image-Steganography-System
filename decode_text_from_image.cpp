#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Function to get the least significant bit of a pixel
bool getLSB(uchar pixel) {
    return pixel & 1;  // Returns 1 if the LSB is 1, 0 if LSB is 0
}

int main(int argc, char** argv) {
    // Check for valid input arguments
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <encoded_image> <output_textfile>" << endl;
        return -1;
    }

    // Read the encoded image
    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Open the output file to save the decoded text
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        cout << "Could not open the output file." << endl;
        return -1;
    }

    // Variables to keep track of decoding process
    char ch = 0;
    int bitPos = 0;
    
    // Loop over each pixel in the image
    bool messageEnded = false;
    for (int row = 0; row < image.rows && !messageEnded; row++) {
        for (int col = 0; col < image.cols && !messageEnded; col++) {
            // Access each pixel in the image (3 channels: B, G, R)
            Vec3b pixel = image.at<Vec3b>(row, col);

            // Retrieve the bit from the LSB of the Blue channel and set it in the current character
            ch |= getLSB(pixel[0]) << (7 - bitPos);

            // Move to the next bit
            bitPos++;
            if (bitPos == 8) {
                // Write the character to the output file
                outputFile.put(ch);

                // Check for the end of the message (null terminator)
                if (ch == '\0') {
                    messageEnded = true;
                }

                // Reset bit position and character for next byte
                ch = 0;
                bitPos = 0;
            }
        }
    }

    outputFile.close();
    cout << "Text successfully decoded from image." << endl;

    return 0;
}
