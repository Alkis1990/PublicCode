#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileInfo>
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

private:
    enum eView
    {
        first,
        second
    };

    Ui::MainWindow *ui;

    void openFile();
    void openFileHelper(QString const &filePath);
    void Exit();

    uint Iy;
    uint Ix;
    int bpp;

    QImage *Image1;
    QImage *Image2;
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;

    string datFilename;
    QFileInfo openedFileInfo;
    bool bBatchActive;

    void Inv();
    void LineSplit();
    void WordSplit();
    void HorizontalRlsa();
    void BatchProcess();


    void SetImageToView(QImage *pImg, eView view);
    bool CheckImageIsLoaded();
    void ConvertQImageToRGB888();
};

#endif // MAINWINDOW_H
