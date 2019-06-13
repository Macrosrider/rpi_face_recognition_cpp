# Face Recognition on Raspberry Pi using OpenCV C++
This small research is a result of my knowledges in ML course at university.
The main idea of this project was to create little program, witch can recognize
faces of different people with Raspberry Pi. Second task was to check, how slow
cv2-wrapper for Python is and is it better to choose C++ instead of Python, when
we need maximum performance?

__The result of research and all achievements you can read on this repo's [Wiki](https://github.com/Macrosrider/rpi_face_recognition_cpp/wiki "Wiki")__.

## Requirements
To run this sample of code, the following packages should be installed on your
Raspberry Pi:

- OpenCV 3.1.0
- OpenCV-contrib 3.1.0
- RaspiCam 0.1.6

OpenCV versions could differ, but then you need to modify code, because in newer
versions of OpenCV the inheritance of FaceRecognizer class and realization of
LBPHFaceRecognizer class are different (you can just look official documentation,
provided by OpenCV).

To compile all this stuff, g++ also should be installed.

## Compile and run

This program consists of two parts - train and recognize. You can separately
compile this parts:

    make recognize
Or:

    make train

Train part of the program extracts face embeddings from photos of your dataset.
Photos should be stored in "dataset" folder. Photos of each person should be
stored in single directory. The name of this single directory is a label - it
means, that it will be displayed on bounding box during the recognition. The
file tree should be something like that:
```
project
│   README.md
│   Makefile    
│   train.cpp
|   recognizer.cpp
|
└───dataset
│   └───Mark
│   │   |   Mark_01.jpg
|   |   |   Mark_02.jpg
│   │   |   ...
|   |
│   └───Tom
│       │   Tom_01.jpg
│       │   Tom_02.jpg
│       │   ...
│   
└───cascades
|   │   lbpcascade_frontalface.xml
|
└───recognizer
    |   embeddings.xml
    |   labels.txt
```

After forming dataset simply run train to extract embeddings and after process
finish run recognizer.
