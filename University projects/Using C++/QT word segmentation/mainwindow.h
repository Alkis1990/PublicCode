#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <string>
#include <QtCore/qstring.h>
#include <iostream>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionHorisontal_RSLA_triggered();

private:
    Ui::MainWindow *ui;

    void openFile();
    void openFileStr(const QString& file, bool line);
    void CleanMemory();
    void Exit();

    uint Iy;
    uint Ix;
    int bpp;

    QImage *Image1;
    QGraphicsScene *scene;

    void Inv();
    void SimpleThreshold();
    void Binarization();
    void Weszka();
    void LineSplit();
    void LineSplitDetailed();
    void WordSplit();
    void WordSplitDetailed();
    void LinesBatch();
    void WordsBatch();
    void SplitLineToWordsDetailed();
    void SplitLineToWords();
    void getHistoCuts(int ymin, int ymax, vector<int> &outVector_cuts, bool horizontal);
    void Horizontal_RLSA();
   // void Vertical_RLSA();
   // void RunLengthSmoothingAlgorithm();
    int runParametric = 0;           //0: You can not run the alfgortihm parametric
    int flagAverageCharacter = 0;   //0:We did not use the average character function
    int flagFindLines = 0;          //0: Horizontal Projection's Threshold has not been given by user
    int flagFindWords = 0;          //0: Vertical Projection's Threshold has not been given by user
    int flagBin = 0;                //0: Tell us that the image has not been binarized
    int flagHorizontalRLSA = 0;     //0: Horizontal predefined limit has not been given by user
    int flagVerticalRLSA =  0;      //0: Vertical predefined limit has not been given by user
    int loadImage1 = 0;             //It means that image was loaded at the q_graphics_view
    int loadImage2 = 0;             //It means that image was loaded at the q_graphics_view_2
    int dbFlag = 0;                 //0: It means that we don't use the Images from the database
    int bySum = 1;                  //1: Initial value in order to change after the selection of the appearance method
    double averageHeight = -1.0;    //average character height by sum method
    int another_averageHeight = -1; //average character height by more apearances method


    int horizontal_C = -1;          //predefined limit C of continuous background pixel for horizontal RLSA
    int vertical_C = -1;            //predefined limit C of continuous background pixel for vertical RLSA

    unsigned char **bitmap = NULL;
    unsigned char **binary_bitmap = NULL;   //It's the bitmap of the Binary Image


    unsigned char **bitmapVerRLSA = NULL;   //It's a bitmap for the vertical RLSA  function
    unsigned char **bitmapHorRLSA = NULL;   //It's a bitmap for the horizontal RLSA  function
    string output;
};

#endif // MAINWINDOW_H
