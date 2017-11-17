//
//  main.cpp
//  MazeGenerator
//
//  Created by 煦 柯 on 2017/11/17.
//  Copyright © 2017年 Must Studio. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>

class Maze
{
public:
    int width;
    int height;
    int pathWidth;
    int wallWidth;
    void write(std::string& fileName)
    {
        std::ofstream ofs(fileName, std::ios::binary);
        int fourb;
        short twob;
        // BMP header
        ofs.put('B');
        ofs.put('M');
        fourb = getFileSize();
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        fourb = 0;
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        fourb = 54;
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        // DIB header
        fourb = 40;
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        fourb = getBitmapWidth();
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        fourb = getBitmapHeight();
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        twob = 1;
        ofs.write(reinterpret_cast<char*>(&twob), 2);
        twob = 24;
        ofs.write(reinterpret_cast<char*>(&twob), 2);
        fourb = 0;
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        fourb = getBitmapSize();
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        fourb = 0xb12;
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        fourb = 0;
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        ofs.write(reinterpret_cast<char*>(&fourb), 4);
        // Bitmap Array
    }
    int getBitmapWidth()
    {
        return width * (pathWidth + wallWidth) + wallWidth;
    }
    
    int getBitmapHeight()
    {
        return height * (pathWidth + wallWidth) + wallWidth;
    }
    
    int getBitmapRowWidth()
    {
        return (24 * getBitmapWidth() + 31) / 32 * 4;
    }
    
    int getFileSize()
    {
        return getBitmapSize() + 54;
    }
    int getBitmapSize()
    {
        return getBitmapHeight() * getBitmapRowWidth();
    }
};

int main(int argc, const char * argv[]) {
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
