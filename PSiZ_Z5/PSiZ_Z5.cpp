/* Daniel Flis

PSiZ_Z5 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits>

using namespace std;

struct FileHeader 
{
    short Type;
    int Size;
    short Reserved1;
    short Reserved2;
    int OffBits;
} 
File;

struct ImageHeader 
{
    int headerSize;
    int width;
    int height;
    short int planes;
    short int bitPerPixel;
    int compresion;
    int imageSize;
    int xPelsPerMeter;
    int yPelsPerMeter;
    int colorUsed;
    int colorImportant;
} 
Pic;

struct coloursRGB 
{
    char R;
    char G;
    char B;
} 
Rgb;

void Details(const char* file) // Metadane
{
    FILE* test = fopen(file, "rb");

    if (test == nullptr)
    {
        cout << endl << "Blad otwarcia pliku!" << endl;
    }
    else
    {
        cout << endl << "Otwarcie pliku zakoczone pomyslnie!" << endl;

        fread(&File.Type, sizeof(File.Type), 1, test);
        fread(&File.Size, sizeof(File.Size), 1, test);
        fread(&File.Reserved1, sizeof(File.Reserved1), 1, test);
        fread(&File.Reserved2, sizeof(File.Reserved2), 1, test);
        fread(&File.OffBits, sizeof(File.OffBits), 1, test);

        fseek(test, 14, SEEK_SET);
        fread(&Pic.headerSize, sizeof(Pic.headerSize), 1, test);
        fread(&Pic.width, sizeof(Pic.width), 1, test);
        fread(&Pic.height, sizeof(Pic.height), 1, test);
        fread(&Pic.planes, sizeof(Pic.planes), 1, test);
        fread(&Pic.bitPerPixel, sizeof(Pic.bitPerPixel), 1, test);
        fread(&Pic.compresion, sizeof(Pic.compresion), 1, test);
        fread(&Pic.imageSize, sizeof(Pic.imageSize), 1, test);
        fread(&Pic.xPelsPerMeter, sizeof(Pic.xPelsPerMeter), 1, test);
        fread(&Pic.yPelsPerMeter, sizeof(Pic.yPelsPerMeter), 1, test);
        fread(&Pic.colorUsed, sizeof(Pic.colorUsed), 1, test);
        fread(&Pic.colorImportant, sizeof(Pic.colorImportant), 1, test);

        cout << endl << "INFO:" << endl << endl;

        cout << "Typ pliku: " << File.Type << endl
            << "Rozmiar pliku: " << File.Size << " bajtow" << endl
            << "Zarezerwowane 1: " << File.Reserved1 << endl
            << "Zarezerwowane 2: " << File.Reserved2 << endl
            << "Pozycja danych obrazkowych: " << File.OffBits << endl << endl;

        cout << "Wielkosc naglowka: " << Pic.headerSize << endl
            << "Szerokosc obrazu: " << Pic.width << " pikseli" << endl
            << "Wysokosc obrazu: " << Pic.height << " pikseli" << endl
            << "Liczba platow: " << Pic.planes << endl
            << "Liczba bitow na piksel: " << Pic.bitPerPixel << endl
            << "Algorytm kompresji: " << Pic.compresion << endl
            << "Rozmiar samego rysunku: " << Pic.imageSize << endl
            << "Rozdzielczosc pozioma: " << Pic.xPelsPerMeter << endl
            << "Rozdzielczosc pionowa: " << Pic.yPelsPerMeter << endl
            << "Liczba kolorow w palecie: " << Pic.colorUsed << endl
            << "Liczba waznych kolorow w palecie: " << Pic.colorImportant << endl;

        fclose(test);
    }
}

void NegativePic(const char* file) // Tworzenie negatywu
{

    FILE* test = fopen(file, "rb");
    FILE* neg = fopen("negatyw.bmp", "wb");

    if (neg == nullptr)
    {
        cout << endl << "Blad otwarcia pliku!" << endl;
    }
    else
    {
        cout << endl << "Negatyw jest wlasnie produkowany." << endl;

        fseek(neg, 0, SEEK_SET);
        fwrite(&File.Type, sizeof(File.Type), 1, neg);
        fwrite(&File.Size, sizeof(File.Size), 1, neg);
        fwrite(&File.Reserved1, sizeof(File.Reserved1), 1, neg);
        fwrite(&File.Reserved2, sizeof(File.Reserved2), 1, neg);
        fwrite(&File.OffBits, sizeof(File.OffBits), 1, neg);


        fseek(neg, 14, SEEK_SET);
        fwrite(&Pic.headerSize, sizeof(Pic.headerSize), 1, neg);
        fwrite(&Pic.width, sizeof(Pic.width), 1, neg);
        fwrite(&Pic.height, sizeof(Pic.height), 1, neg);
        fwrite(&Pic.planes, sizeof(Pic.planes), 1, neg);
        fwrite(&Pic.bitPerPixel, sizeof(Pic.bitPerPixel), 1, neg);
        fwrite(&Pic.compresion, sizeof(Pic.compresion), 1, neg);
        fwrite(&Pic.imageSize, sizeof(Pic.imageSize), 1, neg);
        fwrite(&Pic.xPelsPerMeter, sizeof(Pic.xPelsPerMeter), 1, neg);
        fwrite(&Pic.yPelsPerMeter, sizeof(Pic.yPelsPerMeter), 1, neg);
        fwrite(&Pic.colorUsed, sizeof(Pic.colorUsed), 1, neg);
        fwrite(&Pic.colorImportant, sizeof(Pic.colorImportant), 1, neg);


        fseek(neg, sizeof(File.OffBits), SEEK_SET);

        int Pic;
        for (int i = File.OffBits; i < File.Size; i++)
        {
            fseek(test, i, SEEK_SET);
            fseek(neg, i, SEEK_SET);
            fread(&Pic, 3, 1, test);
            Pic = INT_MAX - Pic;
            fwrite(&Pic, 3, 1, neg);
        }

        cout << endl;
        fclose(test);
        fclose(neg);
    }
}

