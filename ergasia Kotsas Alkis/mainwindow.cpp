#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QtCore/qstring.h>


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Iy=0;
    Ix=0;
    bpp=0;

    // sender, signal, receiver, slot
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::Exit);
    connect(ui->actionInv, &QAction::triggered, this, &MainWindow::Inv);
    connect(ui->actionLine_Split, &QAction::triggered, this, &MainWindow::LineSplit);
    connect(ui->actionLine_Split_Detailed, &QAction::triggered, this, &MainWindow::LineSplitDetailed);
    connect(ui->actionWord_Split, &QAction::triggered, this, &MainWindow::SplitLineToWords);
    connect(ui->actionWord_Split_Detailed, &QAction::triggered, this, &MainWindow::WordSplitDetailed);
    connect(ui->actionLines_Batch, &QAction::triggered, this, &MainWindow::LinesBatch);
    connect(ui->actionWords_Batch, &QAction::triggered, this, &MainWindow::WordsBatch);
    connect(ui->actionHorisontal_RSLA, &QAction::triggered, this, &MainWindow::Horizontal_RLSA);
    //connect(ui->actionVertical_RLSA, &QAction::triggered, this, &MainWindow::Vertical_RLSA);
    //connect(ui->actionRLSA_2, &QAction::triggered, this, &MainWindow::RunLengthSmoothingAlgorithm);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
  //QMessageBox msg; msg.setText("OK"); msg.exec();

    QFile *f = new (std::nothrow) QFile(QFileDialog::getOpenFileName(this, tr("Open File"),QCoreApplication::applicationDirPath(),tr("Images (*.png *.tif *.jpg *.bmp)")));

    if(f->exists())
    {
       // QMessageBox msg; msg.setText(f->fileName()); msg.exec();
        Image1 =  new (std::nothrow) QImage(f->fileName());
        output = f->fileName().toStdString() + ".dat";


        scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*Image1));
        ui->graphicsView->setScene(scene);

        //ui->label->setPixmap(QPixmap::fromImage(*Image1,Qt::AutoColor));

        Ix = Image1->width();
        Iy = Image1->height();
        bpp = Image1->depth();

        QString information = "BPP: "+QString::number(bpp)+"\nWidth: "+QString::number(Ix)+"\nHeight: "+QString::number(Iy);

        ui->label->setText(information);


    }
}
void MainWindow::openFileStr(const QString& file, bool line)
{
  //QMessageBox msg; msg.setText("OK"); msg.exec();

    QFile *f = new (std::nothrow) QFile(file);

    if(f->exists())
    {
       // QMessageBox msg; msg.setText(f->fileName()); msg.exec();
        Image1 =  new (std::nothrow) QImage(f->fileName());
        string tmpStr = f->fileName().toStdString();
        auto pos = tmpStr.find_last_of("/\\");

        if (line) {
            output =  tmpStr.substr(0,pos+1) + "Line\\" + tmpStr.substr(pos+1) + ".dat";
        } else {
            output =  tmpStr.substr(0,pos+1) + "Word\\" + tmpStr.substr(pos+1) + ".dat";
        }

        scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*Image1));
        ui->graphicsView->setScene(scene);

        //ui->label->setPixmap(QPixmap::fromImage(*Image1,Qt::AutoColor));

        Ix = Image1->width();
        Iy = Image1->height();
        bpp = Image1->depth();

        QString information = "BPP: "+QString::number(bpp)+"\nWidth: "+QString::number(Ix)+"\nHeight: "+QString::number(Iy);

        ui->label->setText(information);


    }
}

void MainWindow::Inv()
{
    for(uint y=0;y<Iy;y++)
    {
        for(uint x=0;x<Ix;x++)
        {
            QRgb value;
            unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
            value = qRgb(255-u,255-u,255-u);
            Image1->setPixel(x,y,value);
        }
    }

    scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*Image1));
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::SimpleThreshold()
{
    int thr = 200;
    for(uint y=0;y<Iy;y++)
    {
        for(uint x=0;x<Ix;x++)
        {
            QRgb value;
            unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));

            if(u>thr)
            {
                value = qRgb(255,255,255);
                Image1->setPixel(x,y,value);
            }else
            {
                value = qRgb(0,0,0);
                Image1->setPixel(x,y,value);
            }

        }
    }

    scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*Image1));
    ui->graphicsView_2->setScene(scene);
}


void MainWindow::LineSplit() {
    cout << Ix << endl;
    cout << Iy << endl;
    /** Initialize all starting values to 0 **/
        int *values = new int[Ix*Iy];
        for(uint i = 0; i < Ix*Iy; i++) {
            values[i] = 0;
        }

        int *horizontal_histogram;
        float y_valley_threshold = 0.6;

        if ((horizontal_histogram = new int[Iy]) == NULL ) {
            cerr << "Error in y histogram allocation" << endl;
            exit(-1);
        }

        for(uint y = 0; y < Iy; y++) {
            horizontal_histogram[y] = 0;

            for(uint x = 0; x < Ix; x++) {
                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {//black
                    horizontal_histogram[y] += 1;
                }
            }
        }

        float line_width_threshold = 8.0;
        for(uint y = 0; y < Iy; y++) {
            float line_pixel_threshold = (float)((line_width_threshold*Ix)/100.0);
            horizontal_histogram[y] = horizontal_histogram[y] >= line_pixel_threshold;
        }

        vector<uint> horizontal_cuts;

        uint y = 0;
        while (y < Iy) {
            while (y < Iy && horizontal_histogram[y] != 0) {
                y++;
            }
            uint black_valley = y;

            while (y < Iy && horizontal_histogram[y] == 0) {
                y++;
            }
            int white_valley = y;

            uint midean = black_valley + (white_valley - black_valley)/2;
            if (white_valley - black_valley >= (float)y_valley_threshold*Ix/100.0) {
                horizontal_cuts.push_back(midean);
            }
        }

        delete[] horizontal_histogram;
        if(horizontal_cuts.size() < 2) {
            cerr << "Not enough horizontal cuts" << endl;
            return;
        }
        else {
            cout << "Horizontal cuts size: " << horizontal_cuts.size() << endl;
        }

        QImage *Image2 = new QImage(Ix,Iy,QImage::Format_RGB32);
        for (uint x = 0; x < Ix; x++) {
            for (uint y = 0; y < Iy; y++) {
                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {
                    QRgb value = qRgb(0, 0, 0);
                    Image2->setPixelColor(x,y,value);
                }
                else {
                    QRgb value = qRgb(255,255,255);
                    Image2->setPixelColor(x,y,value);
                }
            }
        }

        int value = 0;
        QRgb red = qRgb(255,0,0);
        QRgb green = qRgb(0,255,0);
        QRgb blue = qRgb(0,0,255);
        QRgb yellow = qRgb(255, 255, 0);
        QRgb cyan = qRgb(0, 255, 255);
        QRgb purple = qRgb(255, 0, 255);

        QRgb colours[] = {red, blue, green, yellow, cyan, purple};

        for(uint i = 0; i < horizontal_cuts.size() - 1; i++) {
            for(uint y = horizontal_cuts[i]; y < horizontal_cuts[i+1]; y++) {
                for(uint x = 0; x < Ix; x++) {
                    unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                    if(u == 0) {
                        values[y*Ix+x] = value;
                        int index = value % 6;
                        Image2->setPixelColor(x,y,colours[index]);
                    }
                }
            }
            value++;
        }

        FILE *fp = fopen(output.c_str(), "wb+");
        for(uint y = 0; y < Iy; y++) {
            for(uint x = 0; x < Ix; x++) {
                fwrite(&values[y*Ix+x], 1, sizeof(int), fp);
            }
        }
        fclose(fp);
        delete[] values;
        scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*Image2));
        ui->graphicsView_2->setScene(scene);
}


void MainWindow::LineSplitDetailed() {
    cout << Ix << endl;
    cout << Iy << endl;
    /** Initialize all starting values to 0 **/
    int *values = new int[Ix*Iy];
    for(uint i = 0; i < Ix*Iy; i++) {
        values[i] = 0;
    }

    int *horizontal_histogram;
    float y_valley_threshold = 0.9;

        if ((horizontal_histogram = new int[Iy]) == NULL ) {
            cerr << "Error in y histogram allocation" << endl;
            exit(-1);
        }


        for(uint y = 0; y < Iy; y++) {
            horizontal_histogram[y] = 0;

            for(uint x = 0; x < Ix; x++) {
                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {
                    horizontal_histogram[y] += 1;
                }
            }
            cout << "horizontal_histogram[" << y << "]" << horizontal_histogram[y] << endl;
        }

        float line_width_threshold = 8.0;
        for(uint y = 0; y < Iy; y++) {
            float line_pixel_threshold = (float)((line_width_threshold*Ix)/100.0);
            horizontal_histogram[y] = (horizontal_histogram[y] >= line_pixel_threshold)*horizontal_histogram[y];
        }


        QImage *Image2 = new QImage(Ix,Iy,QImage::Format_RGB32);

        QRgb red = qRgb(255,0,0);
        QRgb green = qRgb(0,255,0);
        QRgb blue = qRgb(0,0,255);
        QRgb brown = qRgb(255, 255, 0);
        QRgb greenblue = qRgb(0, 255, 255);
        QRgb purple = qRgb(255, 0, 255);
        QRgb colours[] = {red, blue, green, brown, greenblue, purple};

        for (uint x = 0; x < Ix; x++) {
            for (uint y = 0; y < Iy; y++) {
                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {
                    QRgb value = qRgb(0, 0, 0);
                    Image2->setPixelColor(x,y,value);
                }
                else {
                    QRgb value = qRgb(255,255,255);
                    Image2->setPixelColor(x,y,value);
                }
            }
        }



        for(uint i = 0; i < Iy; i++) {
            if(horizontal_histogram[i] > 0)
                for(int j = 0; j < horizontal_histogram[i]; j++)
                    Image2->setPixelColor(j,i,blue);
        }

        vector<uint> horizontal_cuts;

        uint y = 0;
        while (y < Iy) {
            while (y < Iy && horizontal_histogram[y] != 0) {
                y++;
            }
            uint black_valley = y;
            while (y < Iy && horizontal_histogram[y] == 0) {
                y++;
            }
            uint white_valley = y;
            uint midean = black_valley + (white_valley - black_valley)/2;
            if (white_valley - black_valley >= (float)y_valley_threshold*Ix/100.0) {
                horizontal_cuts.push_back(midean);
            }
        }

        delete[] horizontal_histogram;
        if(horizontal_cuts.size() < 2) {
            cerr << "Not enough horizontal cuts" << endl;
            return;
        }
        else {
            cout << "Horizontal cuts size: " << horizontal_cuts.size() << endl;
        }

        int value = 0;

        for(uint i = 0; i < horizontal_cuts.size() - 1; i++) {
            for(uint y = horizontal_cuts[i]; y < horizontal_cuts[i+1]; y++) {
                for(uint x = 0; x < Ix; x++) {
                    unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                    if(u == 0) {
                        values[y*Ix+x] = value;
                        int index = value % 6;
                        Image2->setPixelColor(x,y,colours[index]);
                    }
                }
            }
            value++;
        }

        FILE *fp = fopen(output.c_str(), "wb+");
        for(uint y = 0; y < Iy; y++) {
            for(uint x = 0; x < Ix; x++) {
                fwrite(&values[y*Ix+x], 1, sizeof(int), fp);
            }
        }
        fclose(fp);
        delete[] values;
        scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*Image2));
        ui->graphicsView_2->setScene(scene);
}

void MainWindow::WordSplit() {

}

void MainWindow::WordSplitDetailed() {
    /** Initialize all starting values to 0 **/
        int *values = new int[Ix*Iy];
        for(unsigned int i = 0; i < Ix*Iy; i++) {
            values[i] = 0;
        }

        int *horizontal_histogram;
        int y_valley_threshold = 0.9;
        if ((horizontal_histogram = new int[Iy]) == NULL ) {
            cerr << "Error in y histogram allocation" << endl;
            exit(-1);
        }

        for(unsigned int y = 0; y < Iy; y++) {
            horizontal_histogram[y] = 0;

            for(int x = 0; x < Ix; x++) {

                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {
                    horizontal_histogram[y] += 1;
                }
            }
        }
        int line_width_threshold = 8.0;
        for(int y = 0; y < Iy; y++) {
            float line_pixel_threshold = (float)((line_width_threshold*Ix)/100.0);
            horizontal_histogram[y] = (horizontal_histogram[y] >= line_pixel_threshold);
        }

        QImage *Image2 = new QImage(Ix,Iy,QImage::Format_RGB32);

        QRgb red = qRgb(255,0,0);
        QRgb green = qRgb(0,255,0);
        QRgb blue = qRgb(0,0,255);
        QRgb brown = qRgb(255, 255, 0);
        QRgb greenblue = qRgb(0, 255, 255);
        QRgb purple = qRgb(255, 0, 255);

        QRgb colours[] = {red, blue, green, brown, greenblue, purple};

        for (uint x = 0; x < Ix; x++) {
            for (uint y = 0; y < Iy; y++) {
                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {
                    QRgb value = qRgb(0, 0, 0);
                    Image2->setPixelColor(x,y,value);
                }
                else {
                    QRgb value = qRgb(255,255,255);
                    Image2->setPixelColor(x,y,value);
                }
            }
        }

        for(uint i = 0; i < Iy; i++) {
            if(horizontal_histogram[i] > 0)
                for(int j = 0; j < 50; j++)
                    Image2->setPixelColor(j,i,blue);
        }

        vector<int> horizontal_cuts;

        int y = 0;
        while (y < Iy) {
            while (y < Iy && horizontal_histogram[y] != 0) {
                y++;
            }
            int black_valley = y;

            while (y < Iy && horizontal_histogram[y] == 0) {
                y++;
            }
            int white_valley = y;

            int midean = black_valley + (white_valley - black_valley)/2;
            if (white_valley - black_valley >= (float)y_valley_threshold*Iy/100.0) {
                horizontal_cuts.push_back(midean);
            }
        }

        delete[] horizontal_histogram;
        if(horizontal_cuts.size() < 2) {
            return;
        }

        int * vertical_histogram = new int[Ix] {};
        for(uint i = 0; i < horizontal_cuts.size() - 1; i++) {
            uint lineY = horizontal_cuts[i];
            for(uint y = horizontal_cuts[i]; y < horizontal_cuts[i+1]; y++) {
                for(uint x = 0; x < Ix; x++) {
                    unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));

                    if(u == 0) {
                        vertical_histogram[x] = 1;
                    }
                }
            }
            for(uint i = 0; i < Ix; i++) {
                if(vertical_histogram[i] > 0)
                    for(int j = 0; j < 8; j++){
                        Image2->setPixelColor(i,lineY+j,blue);
                        vertical_histogram[i] = 0;
                    }
                vertical_histogram[i] == 0;
            }
        }



        delete [] vertical_histogram;

        FILE *fp = fopen(output.c_str(), "wb+");
        for(uint y = 0; y < Iy; y++) {
            for(uint x = 0; x < Ix; x++) {
                fwrite(&values[y*Ix+x], 1, sizeof(int), fp);
            }
        }
        fclose(fp);
        delete[] values;
        scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*Image2));
        ui->graphicsView_2->setScene(scene);
}


void MainWindow::SplitLineToWords()
{
    cout << Ix << endl;
    cout << Iy << endl;
    /** Initialize all starting values to 0 **/
        int *values = new int[Ix*Iy];
        for(uint i = 0; i < Ix*Iy; i++) {
            values[i] = 0;
        }

        int *horizontal_histogram;
        float y_valley_threshold = 0.9;

        if ((horizontal_histogram = new int[Iy]) == NULL ) {
            cerr << "Error in y histogram allocation" << endl;
            exit(-1);
        }

        for(uint y = 0; y < Iy; y++) {
            horizontal_histogram[y] = 0;

            for(uint x = 0; x < Ix; x++) {
                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {
                    horizontal_histogram[y] += 1;
                }
            }
        }

        float line_width_threshold = 8.0;
        for(uint y = 0; y < Iy; y++) {
            float line_pixel_threshold = (float)((line_width_threshold*Ix)/100.0);
            horizontal_histogram[y] = horizontal_histogram[y] >= line_pixel_threshold;
        }

        vector<uint> horizontal_cuts;

        uint y = 0;
        while (y < Iy) {
            while (y < Iy && horizontal_histogram[y] != 0) {
                y++;
            }
            uint black_valley = y;

            while (y < Iy && horizontal_histogram[y] == 0) {
                y++;
            }
            int white_valley = y;

            uint midean = black_valley + (white_valley - black_valley)/2;
            if (white_valley - black_valley >= (float)y_valley_threshold*Ix/100.0) {
                horizontal_cuts.push_back(midean);
            }
        }

        delete[] horizontal_histogram;
        if(horizontal_cuts.size() < 2) {
            cerr << "Not enough horizontal cuts" << endl;
            return;
        }
        else {
            cout << "Horizontal cuts size: " << horizontal_cuts.size() << endl;
        }

        QImage *Image2 = new QImage(Ix,Iy,QImage::Format_RGB32);
        for (uint x = 0; x < Ix; x++) {
            for (uint y = 0; y < Iy; y++) {
                unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));
                if(u == 0) {
                    QRgb value = qRgb(0, 0, 0);
                    Image2->setPixelColor(x,y,value);
                }
                else {
                    QRgb value = qRgb(255,255,255);
                    Image2->setPixelColor(x,y,value);
                }
            }
        }

        int value = 0;
        QRgb red = qRgb(255,0,0);
        QRgb green = qRgb(0,255,0);
        QRgb blue = qRgb(0,0,255);
        QRgb yellow = qRgb(255, 255, 0);
        QRgb cyan = qRgb(0, 255, 255);
        QRgb purple = qRgb(255, 0, 255);

        QRgb colours[] = {red, blue, green, yellow, cyan, purple};
        int* wordColor = new int[Ix];

        for(uint i = 0; i < horizontal_cuts.size() - 1; i++) {
            unsigned int pos1 = horizontal_cuts[i] + (horizontal_cuts[i+1] - horizontal_cuts[i])*0.4;
            unsigned int pos2 = horizontal_cuts[i] + (horizontal_cuts[i+1] - horizontal_cuts[i])*0.7;
            unsigned int whiteSpace = 0;
            int index = 0;

            for(uint x = 0; x < Ix; x++) {
                unsigned char p1 = (unsigned char) qGray(Image1->pixel(x,pos1));
                unsigned char p2 = (unsigned char) qGray(Image1->pixel(x,pos2));

                if (p1 != 0 && p2 != 0) {
                    whiteSpace++;
                } else {
                    whiteSpace = 0;
                }

                if (whiteSpace > 40) {
                    index++;
                    whiteSpace = 0;
                }

                wordColor[x] = index%6;
            }
            for(uint y = horizontal_cuts[i]; y < horizontal_cuts[i+1]; y++) {
                for(uint x = 0; x < Ix; x++) {
                    unsigned char u = (unsigned char) qGray(Image1->pixel(x,y));

                    if(u == 0) {
                        values[y*Ix+x] = value;
                        //int index = value % 6;
                        Image2->setPixelColor(x,y,colours[wordColor[x]]);
                    }
                }
            }
           // value++;
        }
        delete [] wordColor;
        FILE *fp = fopen(output.c_str(), "wb+");
        for(uint y = 0; y < Iy; y++) {
            for(uint x = 0; x < Ix; x++) {
                fwrite(&values[y*Ix+x], 1, sizeof(int), fp);
            }
        }
        fclose(fp);
        delete[] values;
        scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*Image2));
        ui->graphicsView_2->setScene(scene);


}


void MainWindow::WordsBatch() {
    for (int i=101; i<301; i++)
    {
        string tmpString = "C:\\Users\\alkiviadis\\Desktop\\ergasia Kotsas Alkis\\images_test\\";
        tmpString = tmpString + to_string(i) + ".tif";
        QString file_tif = QString(tmpString.c_str());
        openFileStr(file_tif, false);
        SplitLineToWords();
    }
}

void MainWindow::LinesBatch() {

    for (int i=101; i<301; i++)
    {
        string tmpString = "C:\\Users\\alkiviadis\\Desktop\\ergasia Kotsas Alkis\\images_test\\";
        tmpString = tmpString + to_string(i) + ".tif";
        QString file_tif = QString(tmpString.c_str());
        openFileStr(file_tif, true);
        LineSplit();
    }

}

void MainWindow::Weszka()
{

}

void MainWindow::CleanMemory()
{

}

void MainWindow::Exit()
{
    CleanMemory();
    QCoreApplication::exit(0);
}

void MainWindow::on_pushButton_clicked()
{
    ui->graphicsView->scale(0.9,0.9);
    ui->graphicsView_2->scale(0.9,0.9);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->graphicsView->scale(1.1,1.1);
    ui->graphicsView_2->scale(1.1,1.1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->graphicsView->resetMatrix();
    ui->graphicsView_2->resetMatrix();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    ui->graphicsView_2->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::on_actionHorisontal_RSLA_triggered()
{

}


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Horizontal_RLSA
void MainWindow::Horizontal_RLSA(){

     /*   if( loadImage1 == 0 ){      //You have to read an image first
            int result3 = QMessageBox::information(this, "Error", "You must Load an Image First.", QMessageBox::Ok);
            if( result3 == QMessageBox::Ok ){ return; }
        }

        if( flagBin == 0 ){         //It means that the image has not been binarized
            int result1 = QMessageBox::information(this,"Error", "First of all Binarization.", QMessageBox::Ok);
            if( result1 == QMessageBox::Ok ){ return; }
        }

        if( runParametric != 1 ){   //It means that we do not want parametric run

            if(  flagHorizontalRLSA == 0 ){   //It means that the user did not give the Horizontal_C
                int result3 = QMessageBox::information(this, "Error", "You must provide Horizontal_C.", QMessageBox::Ok);
                if( result3 == QMessageBox::Ok ){ return; }
            }
        }
        */

        //CREATION OF THE IMAGE AFTER HORIZONTAL RLSA
    cout << "checkpoint1"<< endl;
        QImage *Himage = new QImage(Ix, Iy, QImage::Format_RGB32);
        QRgb whitePxl, blackPxl, lightskybluePxl;
        whitePxl = qRgb(255,255,255);
        blackPxl = qRgb(0,0,0);
        lightskybluePxl = qRgb(135,206,250);


        //This bitmap is useful for the logic and operation of the RLSA
        bitmapHorRLSA = new (std::nothrow)  unsigned char* [Iy];   //It's a bitmap for the horizontal RLSA  function
         cout << "checkpoint2"<< endl;
        for (int y=0; y<Iy; y++) bitmapHorRLSA[y] = new(std::nothrow)  unsigned char[Ix];

        for(int y=0; y<Iy; ++y)         //For every line of the image
            for(int x=0; x<Ix; ++x){    //For every column of the image

                unsigned char u = (unsigned char)qGray(Himage->pixel(x,y));

                if( u == 0 ){  //We find a white pixel

                    Himage->setPixel(x,y,blackPxl);
                    bitmapHorRLSA[y][x] = 0;        //foreground-black
                }
                else{   //We find a black pixel

                    Himage->setPixel(x,y,whitePxl);
                    bitmapHorRLSA[y][x] = 1;         //background-white
                }
            }


        //This bitmap is useful for the creation of the .dat files
        unsigned char **bitmapOfTag = NULL;
        bitmapOfTag = new (std::nothrow) unsigned char* [Iy];

        for (int y=0; y<Iy; y++){

            bitmapOfTag[y] = new(std::nothrow)  unsigned char[Ix];

            for(int x=0; x<Ix; x++){

                unsigned char u = (unsigned char)qGray(Himage->pixel(x,y));

                if( u == 255 ) bitmapOfTag[y][x] = 0;  //background-white
                else bitmapOfTag[y][x] = 1;            //foreground-black
            }
        }

        for(int y=0; y<Iy; ++y){        //For every line

            int count = 0;          //Counter for white pixel
            int flag = 0;           //0: It means that we find black pixel

            for(int x=0; x<Ix; ++x){    //For every column

                unsigned char u = (unsigned char)qGray(Himage->pixel(x,y));
                if( u == 255 ){   //We find a white pixel
                    flag = 255;
                    count++;
                }
                else{               //We find a black pixel

                    if ( flag == 255 && count <= 5 ){

                        for(int k=(x-count); k<x; ++k ){     //Converting count pixels from white to black

                            Himage->setPixel(k,y,lightskybluePxl);

                            bitmapOfTag[y][k] = 1;      //Foreground-black
                            bitmapHorRLSA[y][k] = 1;    //Foreground-black
                        }
                    }

                    flag = 0;   //Reseting the flag
                    count = 0;  //Reseting the counter
                }
            }
        }

 /*       if( dbFlag == 1 ){  //We'll create .dat files
            Create_dot_Dat_Files_v_2_0( bitmapOfTag, "RLSA_DB/lines/");
        }
        else{               //We'll create .tif files
            Himage->save("RLSA/HorizontalRLSA.tif");
        }
*/
        //Hor_Image =  new (std::nothrow) QImage(*Himage);    //In order to be used by the RLSE_H_V

        for(int y=0;y<Iy;y++){ delete[] bitmapOfTag[y]; }
        delete bitmapOfTag;

        //scene2 = new (std::nothrow) QGraphicsScene;
        //scene2->addPixmap(QPixmap::fromImage(*Himage));
        //ui->graphicsView_2->setScene(scene2);

        loadImage2 = 1;     //Image has been put at the graphicsView_2

        if(runParametric == 1){

            if( !bySum ) printf("Average Character Height is: %d.\n", another_averageHeight);

            printf("Horizontal_c = %d is two times the Average Height.\n", horizontal_C);
        }
        else printf("Horizontal_c = %d.\n", horizontal_C);

        scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*Himage));
        ui->graphicsView_2->setScene(scene);
}

