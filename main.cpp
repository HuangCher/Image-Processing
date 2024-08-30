
#include "header.h"
#include "Pixel.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

// reader, writer, and test
Header reader(string path, vector<Pixel> &image) {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    ifstream file;
    file.open(path, ios::binary);

    file.read(&idLength, 1);
    file.read(&colorMapType, 1);
    file.read(&dataTypeCode, 1);
    file.read(reinterpret_cast<char*>(&colorMapOrigin), 2);
    file.read(reinterpret_cast<char*>(&colorMapLength), 2);
    file.read(&colorMapDepth, 1);
    file.read(reinterpret_cast<char*>(&xOrigin), 2);
    file.read(reinterpret_cast<char*>(&yOrigin), 2);
    file.read(reinterpret_cast<char*>(&width), 2);
    file.read(reinterpret_cast<char*>(&height), 2);
    file.read(&bitsPerPixel, 1);
    file.read(&imageDescriptor, 1);

    for(int i = 0; i < width*height; i++) {
        char b;
        char g;
        char r;
        file.read(&b, 1);
        file.read(&g, 1);
        file.read(&r, 1);

        image.push_back(Pixel(b, g, r));
    }
    file.close();
    return Header(idLength, colorMapType, dataTypeCode, colorMapOrigin, colorMapLength, colorMapDepth, xOrigin, yOrigin, width, height, bitsPerPixel, imageDescriptor);
}

void writer(Header info, vector<Pixel> &image, string part) {
    ofstream newfile;
    newfile.open(part, ios::binary);

    newfile.write(&info.idLength, 1);
    newfile.write(&info.colorMapType, 1);
    newfile.write(&info.dataTypeCode, 1);
    newfile.write(reinterpret_cast<const char*>(&info.colorMapOrigin), 2);
    newfile.write(reinterpret_cast<const char*>(&info.colorMapLength), 2);
    newfile.write(&info.colorMapDepth, 1);
    newfile.write(reinterpret_cast<const char*>(&info.xOrigin), 2);
    newfile.write(reinterpret_cast<const char*>(&info.yOrigin), 2);
    newfile.write(reinterpret_cast<const char*>(&info.width), 2);
    newfile.write(reinterpret_cast<const char*>(&info.height), 2);
    newfile.write(&info.bitsPerPixel, 1);
    newfile.write(&info.imageDescriptor, 1);

    for(int i = 0; i < image.size(); i++) {
        char b = image[i].b;
        char g = image[i].g;
        char r = image[i].r;
        newfile.write(&b, 1);
        newfile.write(&g, 1);
        newfile.write(&r, 1);
    }

    newfile.close();
}

void compare(const vector<Pixel> &input, const string &exoutput) {
    vector<Pixel> output;
    reader(exoutput, output);

    for(int i = 0; i < input.size(); i++) {
        if(input[i].b != output[i].b || input[i].g != output[i].g || input[i].r != output[i].r) {
            cout << "Pixel is incorrect at index: " << i << endl;
            cout << "Incorret BGR value: " << endl;
            cout << "Your pixel values: " << (int) (unsigned char) output[i].b << ", " << (int) (unsigned char) output[i].g << ", " << (int) (unsigned char) output[i].r << endl;
            cout << "Expected pixel values: " << (int) (unsigned char) input[i].b << ", " << (int) (unsigned char) input[i].g << ", " << (int) (unsigned char) input[i].r << endl;
            return;
        }
    }
    cout << "All pixels checked." << endl;
}



// //TASKS:
// void taskOne(string top, string bottom) {
//     vector<Pixel> topImage;
//     vector<Pixel> bottomImage;
//     vector<Pixel> imageFinal;
//     reader(top, topImage);
//     reader(bottom, bottomImage);
//     Header final = reader(top, imageFinal);

//     //multiply top and bottom
//     for(int i = 0; i < imageFinal.size(); i++) {
//         imageFinal[i].b = (topImage[i].npb * bottomImage[i].npb * 255) + 0.5;
//         imageFinal[i].g = (topImage[i].npg * bottomImage[i].npg * 255) + 0.5;
//         imageFinal[i].r = (topImage[i].npr * bottomImage[i].npr * 255) + 0.5;
//     }

//     writer(final, imageFinal, "part1.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part1.tga");
// }

// void taskTwo(string top, string bottom) {
//     vector<Pixel> topImage;
//     vector<Pixel> bottomImage;
//     vector<Pixel> imageFinal;
//     reader(top, topImage);
//     reader(bottom, bottomImage);
//     Header final = reader(top, imageFinal);

//     //subtract top and bottom
//     for(int i = 0; i < imageFinal.size(); i++) {
//         if((int) (unsigned char) topImage[i].b - (int) (unsigned char) bottomImage[i].b < 0) {
//             imageFinal[i].b = 0;
//         } else {
//             imageFinal[i].b = topImage[i].b - bottomImage[i].b;
//         }

//         if((int) (unsigned char) topImage[i].g - (int) (unsigned char) bottomImage[i].g < 0) {
//             imageFinal[i].g = 0;
//         } else {
//             imageFinal[i].g = topImage[i].g - bottomImage[i].g;
//         }

//         if((int) (unsigned char) topImage[i].r - (int) (unsigned char) bottomImage[i].r < 0) {
//             imageFinal[i].r = 0;
//         } else {
//             imageFinal[i].r = topImage[i].r - bottomImage[i].r;
//         }
//     }
//     writer(final, imageFinal, "part2.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part2.tga");
// }

// void taskThree(string top1, string top2, string bottom) {
//     vector<Pixel> imageFinal;
//     vector<Pixel> topImage;

//     //multiplies top1 and top2
//     vector<Pixel> topOne;
//     vector<Pixel> topTwo;
//     reader(top1, topImage);
//     reader(top1, topOne);
//     reader(top2, topTwo);
//     for(int i = 0; i < topImage.size(); i++) {
//         topImage[i].b = (topOne[i].npb * topTwo[i].npb * 255) + 0.5;
//         topImage[i].npb = (float)(unsigned char)topImage[i].b / 255;
//         topImage[i].g = (topOne[i].npg * topTwo[i].npg * 255) + 0.5;
//         topImage[i].npg = (float)(unsigned char)topImage[i].g / 255;
//         topImage[i].r = (topOne[i].npr * topTwo[i].npr * 255) + 0.5;
//         topImage[i].npr = (float)(unsigned char)topImage[i].r / 255;
//     }

//     vector<Pixel> bottomImage;
//     reader(bottom, bottomImage);
//     Header final = reader(bottom, imageFinal);

//     //screen top and bottom
//     for(int i = 0; i < imageFinal.size(); i++) {
//         imageFinal[i].b = (1 - ((1 - topImage[i].npb) * (1 - bottomImage[i].npb))) * 255 + 0.5;
//         imageFinal[i].g = (1 - ((1 - topImage[i].npg) * (1 - bottomImage[i].npg))) * 255 + 0.5;
//         imageFinal[i].r = (1 - ((1 - topImage[i].npr) * (1 - bottomImage[i].npr))) * 255 + 0.5;
//     }

//     writer(final, imageFinal, "part3.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part3.tga");
// }

// void taskFour(string top1, string top2, string bottom) {
//     vector<Pixel> imageFinal;
//     vector<Pixel> topImage;

//     //multiplies top1 and top2
//     vector<Pixel> topOne;
//     vector<Pixel> topTwo;
//     reader(top1, topImage);
//     reader(top1, topOne);
//     reader(top2, topTwo);
//     for(int i = 0; i < topImage.size(); i++) {
//         topImage[i].b = (topOne[i].npb * topTwo[i].npb * 255) + 0.5;
//         topImage[i].g = (topOne[i].npg * topTwo[i].npg * 255) + 0.5;
//         topImage[i].r = (topOne[i].npr * topTwo[i].npr * 255) + 0.5;
//     }

//     vector<Pixel> bottomImage;
//     reader(bottom, bottomImage);
//     Header final = reader(bottom, imageFinal);

//     //subtracts top and bottom
//     for(int i = 0; i < imageFinal.size(); i++) {
//         if((int) (unsigned char) topImage[i].b - (int) (unsigned char) bottomImage[i].b < 0) {
//             imageFinal[i].b = 0;
//         } else {
//             imageFinal[i].b = topImage[i].b - bottomImage[i].b;
//         }

//         if((int) (unsigned char) topImage[i].g - (int) (unsigned char) bottomImage[i].g < 0) {
//             imageFinal[i].g = 0;
//         } else {
//             imageFinal[i].g = topImage[i].g - bottomImage[i].g;
//         }

//         if((int) (unsigned char) topImage[i].r - (int) (unsigned char) bottomImage[i].r < 0) {
//             imageFinal[i].r = 0;
//         } else {
//             imageFinal[i].r = topImage[i].r - bottomImage[i].r;
//         }
//     }

//     writer(final, imageFinal, "part4.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part4.tga");
// }

// void taskFive(string top, string bottom) {
//     vector<Pixel> topImage;
//     vector<Pixel> bottomImage;
//     vector<Pixel> imageFinal;
//     reader(top, topImage);
//     reader(bottom, bottomImage);
//     Header final = reader(top, imageFinal);

//     //overlay top and bottom
//     for(int i = 0; i < imageFinal.size(); i++) {
//         if(bottomImage[i].npb <= 0.5) {
//             imageFinal[i].b = (2 * bottomImage[i].npb * topImage[i].npb) * 255 + 0.5;
//         } else if(bottomImage[i].npb > 0.5) {
//             imageFinal[i].b = (1 - (2 * (1 - bottomImage[i].npb) * (1 - topImage[i].npb))) * 255 + 0.5;
//         }

//         if(bottomImage[i].npg <= 0.5) {
//             imageFinal[i].g = (2 * bottomImage[i].npg * topImage[i].npg) * 255 + 0.5;
//         } else if(bottomImage[i].npg > 0.5) {
//             imageFinal[i].g = (1 - (2 * (1 - bottomImage[i].npg) * (1 - topImage[i].npg))) * 255 + 0.5;
//         }

//         if(bottomImage[i].npr <= 0.5) {
//             imageFinal[i].r = (2 * bottomImage[i].npr * topImage[i].npr) * 255 + 0.5;
//         } else if(bottomImage[i].npr > 0.5) {
//             imageFinal[i].r = (1 - (2 * (1 - bottomImage[i].npr) * (1 - topImage[i].npr))) * 255 + 0.5;
//         }
//     }

//     writer(final, imageFinal, "part5.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part5.tga");
// }

// void taskSix(string top) {
//     vector<Pixel> topImage;
//     vector<Pixel> imageFinal;
//     reader(top, topImage);
//     Header final = reader(top, imageFinal);

//     // adds 200 to green
//     for(int i = 0; i < imageFinal.size(); i++) {
//         if((int) (unsigned char) topImage[i].g + 200 > 255) {
//             imageFinal[i].g = 255;
//         } else {
//             imageFinal[i].g = topImage[i].g + 200;
//         }
//     }

//     writer(final, imageFinal, "part6.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part6.tga");
// }

// void taskSeven(string top) {
//     vector<Pixel> topImage;
//     vector<Pixel> imageFinal;
//     reader(top, topImage);
//     Header final = reader(top, imageFinal);

//     // scale red by 4 and blue by 0
//     for(int i = 0; i < imageFinal.size(); i++) {
//         if((int) (unsigned char) topImage[i].r * 4 > 255) {
//             imageFinal[i].r = 255;
//         } else {
//             imageFinal[i].r = topImage[i].r * 4;
//         }
//         imageFinal[i].b = topImage[i].b * 0;
//     }

//     writer(final, imageFinal, "part7.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part7.tga");
// }

// void taskEight(string top) {
//     vector<Pixel> topImage;
//     vector<Pixel> imageFinalB;
//     vector<Pixel> imageFinalG;
//     vector<Pixel> imageFinalR;
//     reader(top, topImage);
//     Header finalB = reader(top, imageFinalB);
//     Header finalG = reader(top, imageFinalG);
//     Header finalR = reader(top, imageFinalR);

//     // blue
//     for(int i = 0; i < imageFinalB.size(); i++) {
//         imageFinalB[i].g = imageFinalB[i].b;
//         imageFinalB[i].r = imageFinalB[i].b;
//     }

//     // green
//     for(int i = 0; i < imageFinalG.size(); i++) {
//         imageFinalG[i].b = imageFinalG[i].g;
//         imageFinalG[i].r = imageFinalG[i].g;
//     }

//     // red
//     for(int i = 0; i < imageFinalR.size(); i++) {
//         imageFinalR[i].b = imageFinalR[i].r;
//         imageFinalR[i].g = imageFinalR[i].r;
//     }

//     writer(finalB, imageFinalB, "part8_b.tga");
//     writer(finalG, imageFinalG, "part8_g.tga");
//     writer(finalR, imageFinalR, "part8_r.tga");

//     // compare(imageFinalB, "examples/EXAMPLE_part8_b.tga");
//     // compare(imageFinalG, "examples/EXAMPLE_part8_g.tga");
//     // compare(imageFinalR, "examples/EXAMPLE_part8_r.tga");

// }

// void taskNine(string lB, string lG, string lR) {
//     vector<Pixel> imageB;
//     vector<Pixel> imageG;
//     vector<Pixel> imageR;
//     vector<Pixel> imageFinal;
//     reader(lB, imageB);
//     reader(lG, imageG);
//     reader(lR, imageR);
//     Header final = reader(lB, imageFinal);

//     //combines BGR to one file
//     for(int i = 0; i < imageFinal.size(); i++) {
//         imageFinal[i].b = imageB[i].b;
//         imageFinal[i].g = imageG[i].g;
//         imageFinal[i].r = imageR[i].r;
//     }

//     writer(final, imageFinal, "part9.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part9.tga");

// }

// void taskTen(string top) {
//     vector<Pixel> topImage;
//     vector<Pixel> imageFinal;
//     reader(top, topImage);
//     Header final = reader(top, imageFinal);
//     int count = 0;

//     // rotate 180 degrees
//     for(int i = imageFinal.size() - 1; i >= 0; i--) {
//         imageFinal[i] = topImage[0 + count];
//         count++;
//     }
//     writer(final, imageFinal, "part10.tga");
//     // compare(imageFinal, "examples/EXAMPLE_part10.tga");

// }



// METHODS
vector<Pixel> multiply(vector<Pixel> &trackingImage, string bottom) {
    vector<Pixel> bottomImage;
    reader(bottom, bottomImage);

    //multiply top and bottom
    for(int i = 0; i < trackingImage.size(); i++) {
        trackingImage[i].b = (trackingImage[i].npb * bottomImage[i].npb * 255) + 0.5;
        trackingImage[i].g = (trackingImage[i].npg * bottomImage[i].npg * 255) + 0.5;
        trackingImage[i].r = (trackingImage[i].npr * bottomImage[i].npr * 255) + 0.5;
    }
    return trackingImage;
}

vector<Pixel> subtract(vector<Pixel> &trackingImage, string bottom) {
    vector<Pixel> bottomImage;
    reader(bottom, bottomImage);

    //subtract top and bottom
    for(int i = 0; i < trackingImage.size(); i++) {
        if((int) (unsigned char) trackingImage[i].b - (int) (unsigned char) bottomImage[i].b < 0) {
            trackingImage[i].b = 0;
            trackingImage[i].npb = 0;
        } else {
            trackingImage[i].b = trackingImage[i].b - bottomImage[i].b;
            trackingImage[i].npb = (float) (unsigned char) trackingImage[i].b/255;
        }

        if((int) (unsigned char) trackingImage[i].g - (int) (unsigned char) bottomImage[i].g < 0) {
            trackingImage[i].g = 0;
            trackingImage[i].npg = 0;
            
        } else {
            trackingImage[i].g = trackingImage[i].g - bottomImage[i].g;
            trackingImage[i].npg = (float) (unsigned char) trackingImage[i].g/255;
            
        }

        if((int) (unsigned char) trackingImage[i].r - (int) (unsigned char) bottomImage[i].r < 0) {
            trackingImage[i].r = 0;
            trackingImage[i].npr = 0;
        } else {
            trackingImage[i].r = trackingImage[i].r - bottomImage[i].r;
            trackingImage[i].npr = (float) (unsigned char) trackingImage[i].r/255;
           
        }
    }
    return trackingImage;
}

vector<Pixel> overlay(vector<Pixel> &trackingImage, string bottom) {
    vector<Pixel> bottomImage;
    reader(bottom, bottomImage);

    //overlay top and bottom
    for(int i = 0; i < trackingImage.size(); i++) {
        if(bottomImage[i].npb <= 0.5) {
            trackingImage[i].b = (2 * bottomImage[i].npb * trackingImage[i].npb) * 255 + 0.5;
        } else if(bottomImage[i].npb > 0.5) {
            trackingImage[i].b = (1 - (2 * (1 - bottomImage[i].npb) * (1 - trackingImage[i].npb))) * 255 + 0.5;
        }

        if(bottomImage[i].npg <= 0.5) {
            trackingImage[i].g = (2 * bottomImage[i].npg * trackingImage[i].npg) * 255 + 0.5;
        } else if(bottomImage[i].npg > 0.5) {
            trackingImage[i].g = (1 - (2 * (1 - bottomImage[i].npg) * (1 - trackingImage[i].npg))) * 255 + 0.5;
        }

        if(bottomImage[i].npr <= 0.5) {
            trackingImage[i].r = (2 * bottomImage[i].npr * trackingImage[i].npr) * 255 + 0.5;
        } else if(bottomImage[i].npr > 0.5) {
            trackingImage[i].r = (1 - (2 * (1 - bottomImage[i].npr) * (1 - trackingImage[i].npr))) * 255 + 0.5;
        }
    }
    return trackingImage;
}

vector<Pixel> screen(vector<Pixel> &trackingImage, string top) {
    vector<Pixel> topImage;
    reader(top, topImage);

    //screen top and bottom
    for(int i = 0; i < trackingImage.size(); i++) {
        trackingImage[i].b = (1 - ((1 - topImage[i].npb) * (1 - trackingImage[i].npb))) * 255 + 0.5;
        trackingImage[i].g = (1 - ((1 - topImage[i].npg) * (1 - trackingImage[i].npg))) * 255 + 0.5;
        trackingImage[i].r = (1 - ((1 - topImage[i].npr) * (1 - trackingImage[i].npr))) * 255 + 0.5;
    }
    return trackingImage;
}

vector<Pixel> combine(vector<Pixel> &trackingImage, string lG, string lB) {
    vector<Pixel> imageB;
    vector<Pixel> imageG;
    reader(lB, imageB);
    reader(lG, imageG);

    //combines BGR to one file
    for(int i = 0; i < trackingImage.size(); i++) {
        trackingImage[i].b = imageB[i].b;
        trackingImage[i].g = imageG[i].g;
        trackingImage[i].r = trackingImage[i].r;
    }
    return trackingImage;
}

vector<Pixel> flip(vector<Pixel> &trackingImage) {
    vector<Pixel> temp;
    for(int i = 0; i < trackingImage.size(); i++) {
        temp.push_back(trackingImage[i]);
    }

    int count = 0;

    // rotate 180 degrees
    for(int i = trackingImage.size() - 1; i >= 0; i--) {
        trackingImage[i] = temp[0 + count];
        count++;
    }
    return trackingImage;
}

vector<Pixel> onlyred(vector<Pixel> &trackingImage) {
    for(int i = 0; i < trackingImage.size(); i++) {
        trackingImage[i].b = trackingImage[i].r;
        trackingImage[i].g = trackingImage[i].r;
    }
    return trackingImage;
}

vector<Pixel> onlygreen(vector<Pixel> &trackingImage) {
    for(int i = 0; i < trackingImage.size(); i++) {
        trackingImage[i].b = trackingImage[i].g;
        trackingImage[i].r = trackingImage[i].g;
    }
    return trackingImage;
}

vector<Pixel> onlyblue(vector<Pixel> &trackingImage) {
    for(int i = 0; i < trackingImage.size(); i++) {
        trackingImage[i].g = trackingImage[i].b;
        trackingImage[i].r = trackingImage[i].b;
    }
    return trackingImage;
}

vector<Pixel> addred(vector<Pixel> &trackingImage, int num) {
    for(int i = 0; i < trackingImage.size(); i++) {
        if((int) (unsigned char) trackingImage[i].r + num > 255) {
            trackingImage[i].r = 255;
        } else if((int) (unsigned char) trackingImage[i].r + num < 0) {
            trackingImage[i].r = 0;
        } else {
            trackingImage[i].r = trackingImage[i].r + num;
        }
    }
    return trackingImage;
}

vector<Pixel> addgreen(vector<Pixel> &trackingImage, int num) {
    for(int i = 0; i < trackingImage.size(); i++) {
        if((int) (unsigned char) trackingImage[i].g + num > 255) {
            trackingImage[i].g = 255;
        } else if((int) (unsigned char) trackingImage[i].g + num < 0) {
            trackingImage[i].g = 0;            
        } else {
            trackingImage[i].g = trackingImage[i].g + num;
        }
    }
    return trackingImage;
}

vector<Pixel> addblue(vector<Pixel> &trackingImage, int num) {
    for(int i = 0; i < trackingImage.size(); i++) {
        if((int) (unsigned char) trackingImage[i].b + num > 255) {
            trackingImage[i].b = 255;
        } else if((int) (unsigned char) trackingImage[i].b + num < 0) {
            trackingImage[i].b = 0;
        } else {
            trackingImage[i].b = trackingImage[i].b + num;
        }
    }
    return trackingImage;
}

vector<Pixel> scalered(vector<Pixel> &trackingImage, int num) {
    for(int i = 0; i < trackingImage.size(); i++) {
        if((int) (unsigned char) trackingImage[i].r * num > 255) {
            trackingImage[i].r = 255;
        } else {
            trackingImage[i].r = trackingImage[i].r * num;
        }
    }
    return trackingImage;
}

vector<Pixel> scalegreen(vector<Pixel> &trackingImage, int num) {
    for(int i = 0; i < trackingImage.size(); i++) {
        if((int) (unsigned char) trackingImage[i].g * num > 255) {
            trackingImage[i].g = 255;
        } else {
            trackingImage[i].g = trackingImage[i].g * num;
        }
    }
    return trackingImage;
}

vector<Pixel> scaleblue(vector<Pixel> &trackingImage, int num) {
    for(int i = 0; i < trackingImage.size(); i++) {
        if((int) (unsigned char) trackingImage[i].b * num > 255) {
            trackingImage[i].b = 255;
        } else {
            trackingImage[i].b = trackingImage[i].b * num;
        }
    }
    return trackingImage;
}

int main(int argc, char *argv[]) {
    // taskOne("input/layer1.tga", "input/pattern1.tga");
    // taskTwo("input/car.tga", "input/layer2.tga");
    // taskThree("input/layer1.tga", "input/pattern2.tga", "input/text.tga");
    // taskFour("input/layer2.tga", "input/circles.tga", "input/pattern2.tga");
    // taskFive("input/layer1.tga", "input/pattern1.tga");
    // taskSix("input/car.tga");
    // taskSeven("input/car.tga");
    // taskEight("input/car.tga");
    // taskNine("input/layer_blue.tga", "input/layer_green.tga", "input/layer_red.tga");
    // taskTen("input/text2.tga");

    vector<Pixel> trackingImage;
    int i = 3;
    // help command
    if ((argc == 2 && strcmp(argv[1], "--help") == 0) || argc == 1) {
        cout << "Project 2: Image Processing, Summer 2024" << endl << endl;
        cout << "Usage:" << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]";
        return 0;
    }

    // checks output files
    string outputfile(argv[1]);
    if ((outputfile.find(".tga") == string::npos) || 3 > argc) {
        cout << "Invalid file name." << endl;
        return 1;
    }

    if (outputfile.find("output/") == string::npos) {
        outputfile = "output/" + outputfile;
    }

    // checks the input/tracking image
    string sourcefile(argv[2]);
    if (sourcefile.find(".tga") == string::npos) {
        cout << "Invalid file name." << endl;
        return 1;
    }

    ifstream tracking;
    tracking.open(sourcefile, ios::binary);
    if (!tracking.is_open()) {
        cout << "File does not exist." << endl;
        return 1;
    }
    tracking.close();

    if (sourcefile.find("input/") == string::npos) {
        sourcefile = "input/" + sourcefile;
    }
    Header final = reader(sourcefile, trackingImage);


    while (i < argc) {
        // multiply command
        if(strcmp(argv[i], "multiply") == 0) {
            i++;
            //checks multiply argument
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            string filename(argv[i]);
            if (filename.find(".tga") == string::npos) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream file;
            file.open(filename, ios::binary);
            if (!file.is_open()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            file.close();
            multiply(trackingImage, argv[i]);
        }

        // subtract command
        else if (strcmp(argv[i], "subtract") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            string filename(argv[i]);
            if (filename.find(".tga") == string::npos) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream file;
            file.open(filename, ios::binary);
            if (!file.is_open()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            file.close();
            subtract(trackingImage, argv[i]);
        }

        // overlay command
        else if (strcmp(argv[i], "overlay") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            string filename(argv[i]);
            if (filename.find(".tga") == string::npos) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream file;
            file.open(filename, ios::binary);
            if (!file.is_open()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            file.close();
            overlay(trackingImage, argv[i]);
        }

        // screen command
        else if (strcmp(argv[i], "screen") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            string filename(argv[i]);
            if (filename.find(".tga") == string::npos) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream file;
            file.open(filename, ios::binary);
            if (!file.is_open()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            file.close();
            screen(trackingImage, argv[i]);
        }

        //combine command
        else if (strcmp(argv[i], "combine") == 0) {
            //checks the first addition file
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            string filename1(argv[i]);
            if (filename1.find(".tga") == string::npos) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream file1;
            file1.open(filename1, ios::binary);
            if (!file1.is_open()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            file1.close();
            char *arg1 = argv[i];

            //checks the second addition file
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            string filename2(argv[i]);
            if (filename2.find(".tga") == string::npos) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            ifstream file2;
            file2.open(filename2, ios::binary);
            if (!file2.is_open()) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            file2.close();
            combine(trackingImage, arg1, argv[i]);
        }

        // flip command
        else if (strcmp(argv[i], "flip") == 0) {
            flip(trackingImage);
        }

        // onlyred command
        else if (strcmp(argv[i], "onlyred") == 0) {
            onlyred(trackingImage);
        }

        // onlygreen command
        else if (strcmp(argv[i], "onlygreen") == 0) {
            onlygreen(trackingImage);
        }

        // onlyblue command
        else if (strcmp(argv[i], "onlyblue") == 0) {
            onlyblue(trackingImage);
        }

        // addred command
        else if (strcmp(argv[i], "addred") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            try {
                int num = stoi(argv[i]);
                addred(trackingImage, num);

            } catch (invalid_argument &e){
                cerr << "Invalid argument, expected number." << endl;
                return 1;
            }
        }

        // addgreen command
        else if (strcmp(argv[i], "addgreen") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            try {
                int num = stoi(argv[i]);
                addgreen(trackingImage, num);

            } catch (invalid_argument &e){
                cerr << "Invalid argument, expected number." << endl;
                return 1;
            }
        }

        // addblue command
        else if (strcmp(argv[i], "addblue") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            try {
                int num = stoi(argv[i]);
                addblue(trackingImage, num);

            } catch (invalid_argument &e){
                cerr << "Invalid argument, expected number." << endl;
                return 1;
            }
        }
        
        // scalered command
        else if (strcmp(argv[i], "scalered") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            try {
                int num = stoi(argv[i]);
                scalered(trackingImage, num);

            } catch (invalid_argument &e){
                cerr << "Invalid argument, expected number." << endl;
                return 1;
            }
        }

        // scalegreen command
        else if (strcmp(argv[i], "scalegreen") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            try {
                int num = stoi(argv[i]);
                scalegreen(trackingImage, num);

            } catch (invalid_argument &e){
                cerr << "Invalid argument, expected number." << endl;
                return 1;
            }
        }

        // scaleblue command
        else if (strcmp(argv[i], "scaleblue") == 0) {
            i++;
            if(i >= argc) {
                cout << "Missing argument." << endl;
                return 1;
            }
            try {
                int num = stoi(argv[i]);
                scaleblue(trackingImage, num);

            } catch (invalid_argument &e){
                cerr << "Invalid argument, expected number." << endl;
                return 1;
            }
        }

        else {
            cout << "Invalid method name." << endl;
            return 1;
        }
        i++;
    }

    writer(final, trackingImage, outputfile);
    return 0;
}
