#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <CImg.h>
using namespace cimg_library;
using namespace std;
void error(const char *s);
void procesoArchivo(char *archivo);

int main()
{
    CImg<unsigned int> src("test/0/n0.gif");
    int width = src.width();
    int height = src.height();
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            //unsigned int * ptr = src.data(10,10);
            std::cout <<"\t" <<*src.data(i,j);
        }
        cout<< std::endl;
    }

}
