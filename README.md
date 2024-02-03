# Image to Text Converter

## Description
This project is a command-line tool that converts images into text and renders them in terminals. Additionally, it includes a Python script to feed live video from a camera or a video file and convert it into text format.

## Features
- Convert images into text for terminal rendering.
- Process live video feed and convert it into text.
- Supports both live camera feed and video file input.

## Requirements
- Gcc compiler for building the image to text converter.
- Make
- Python 3.x for running the video feed script.

## Installation
### Image to Text Converter (C)
1. Clone this repository.
2. Compile the C code using the provided Makefile or your preferred method.

### Video Feed Script (Python)
1. Ensure Python 3.x is installed on your system.
2. Install required Python packages using `pip install opencv`.

## Usage
### Image to Text Converter
- Run the compiled binary with the path to the image file as an argument.
- Example: `./img_to_ascii path/to/image.jpg`

### Video Feed Script
- Run the Python script with optional parameters for video file input.
- Example: `python main.py [path/to/video.mp4]`

## Contributing
- Contributions are welcome! Fork the repository and submit a pull request with your changes.

## License
- I dont really understand licensing yet so you can go and do whatever you want with this.

## Acknowledgements
- Huge thanks to the stbi library which helped parse the images in easily.
