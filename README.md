# Image-Steganography-System

Overview
The Image Steganography System is a robust C++ application that enables secure encoding of text messages into images using the Least Significant Bit (LSB) technique. The project incorporates histogram analysis to validate the encoding process by comparing the original and encoded images, ensuring data security and integrity.

Features
Text Encoding: Hide secret text messages within images using the LSB steganography method.
Text Decoding: Extract embedded messages accurately from encoded images.
Histogram Analysis: Visualize and validate the differences between the original and encoded images.
Menu-Driven Interface: Intuitive command-line interface for user interactions.

Technologies Used
Programming Language: C++
Libraries: OpenCV
Development Tools: Command-line Tools, GCC Compiler
Installation
Prerequisites:
Install OpenCV (Ensure it is set up in your environment).
C++ Compiler (e.g., GCC).

Clone the Repository:

git clone https://github.com/YourUsername/ImageSteganographySystem.git
cd ImageSteganographySystem

Build the Application:
g++ -o steganography main.cpp -lopencv_core -lopencv_imgcodecs -lopencv_highgui

Run the Application:
./steganography

Usage
Encode a Message:
Select the encoding option from the menu.
Provide the input image file path and the message to be encoded.
Save the encoded image with a custom file name.
Decode a Message:
Select the decoding option from the menu.
Provide the encoded image file path to retrieve the hidden message.
Histogram Analysis:
Visualize the difference between the original and encoded images.

Project Structure
main.cpp: Core logic for encoding, decoding, and menu-driven interaction.
utils/: Utility functions for image processing and histogram generation.
images/: Example input/output images.


Applications
Covert Communication: Send hidden messages securely.
Digital Watermarking: Protect intellectual property by embedding watermarks in images.
Forensic Analysis: Identify tampering or hidden data within images.

Contact
For queries or support, feel free to reach out:
Rakshit Agarwal

Email: Rakshit.101826@stu.upes.ac.in
GitHub: Rakshit11111
License
This project is licensed under the MIT License - see the LICENSE file for details.











