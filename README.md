# Image to Text Converter

## Description
This project is a command-line tool that converts images into text and renders them in terminals. Additionally, it includes a Python script to feed live video from a camera or a video file and convert it into text format.

## Features
- Convert images into text for terminal rendering.
- Process live video feed and convert it into text.
- Supports both live camera feed and video file input.

## Requirements
- C compiler for building the image to text converter.
- [STB library](https://github.com/nothings/stb) for image processing.
- Python 3.x for running the video feed script.
- Additional dependencies may be required, listed in the respective sections below.

## Installation
### Image to Text Converter (C)
1. Clone this repository.
2. Navigate to the `image_to_text_converter` directory.
3. Ensure you have the STB library available in your system.
4. Compile the C code using the provided Makefile or your preferred method.

### Video Feed Script (Python)
1. Ensure Python 3.x is installed on your system.
2. Install required Python packages using `pip install opencv`.

## Usage
### Image to Text Converter
- Run the compiled binary with the path to the image file as an argument.
- Example: `./image_to_text_converter path/to/image.jpg`

### Video Feed Script
- Run the Python script with optional parameters for video file input.
- Example: `./main.py path/to/video.mp4`

## Configuration
- Additional configuration options may be available in the Python script. Please refer to the script comments for details.

## Contributing
- Contributions are welcome! Fork the repository and submit a pull request with your changes.

## License
- This project is licensed under the [MIT License](LICENSE).

