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
#include <algorithm>
#include <string>
#include <vector>
#include <random>

class PathNode
{
public:
    PathNode *group;
    PathNode()
    : group(this)
    {}
    PathNode* Find()
    {
        if (this == group)
            return this;
        auto newGroup = group->Find();
        group = newGroup;
        return newGroup;
    }
    bool Union(PathNode* node)
    {
        if (node->Find() == Find())
            return false;
        Find()->group = node->Find();
        return true;
    }
};

class Wall
{
public:
    PathNode* node1;
    PathNode* node2;
    bool block = true;
    void breakWall()
    {
        if (node1->Union(node2))
            block = false;
    }
};

class Maze
{
public:
    int width;
    int height;
    int pathWidth;
    int wallWidth;
    PathNode* maze;
    Wall* horizontalWalls;
    Wall* verticalWalls;
    Maze(int wid, int hei, int patw, int walw)
    : width(wid)
    , height(hei)
    , pathWidth(patw)
    , wallWidth(walw)
    {
        maze = new PathNode[width * height];
        horizontalWalls = new Wall[width * height];
        verticalWalls = new Wall[width * height];
        std::vector<Wall*> allWalls;
        for (int i = 0; i < width; ++i)
            for (int j = 0; j < height; ++j)
            {
                if (i < width - 1)
                {
                    auto wall = verticalWalls + j * width + i;
                    wall->node1 = maze + j * width + i;
                    wall->node2 = maze + j * width + i + 1;
                    allWalls.push_back(wall);
                }
                if (j < height - 1)
                {
                    auto wall = horizontalWalls + j * width + i;
                    wall->node1 = maze + j * width + i;
                    wall->node2 = maze + (j + 1) * width + i;
                    allWalls.push_back(wall);
                }
            }
        
    }
    
    ~Maze()
    {
        delete[] maze;
        delete[] horizontalWalls;
        delete[] verticalWalls;
    }
    
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
        char* array = getBitmapArray();
        
        delete[] array;
    }
    
    void fill(char* array, int x, int y)
    {
        int xbase = x * (pathWidth + wallWidth) + wallWidth;
        int ybase = y * (pathWidth + wallWidth) + wallWidth;
        
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
    char* getBitmapArray()
    {
        return new char[getBitmapSize()]();
    }
};

int main(int argc, const char * argv[]) {
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
