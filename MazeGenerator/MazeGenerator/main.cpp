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
        
    }
    
    
    
    int getBitmapRowWidth()
    {
        return (24 * width + 31) / 32 * 4;
    }
    
    int getFileSize()
    {
        return getBitmapSize() + 54;
    }
    int getBitmapSize()
    {
        return height * getBitmapRowWidth();
    }
};

int main(int argc, const char * argv[]) {
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
