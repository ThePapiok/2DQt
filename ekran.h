#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

struct coord{
    int x;
    int y;
    int p;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
        explicit Ekran(QWidget *parent = nullptr);
        void linia(int x1,int y1,int x2,int y2,int r,int g,int b);
        void rysujWielokat();
        void drawPixel(int x,int y,int r,int g,int b);
        void setSkalax(float value);
        void setSkalay(float value);
        void setTranslajcax(int value);
        void setTranslajcay(int value);
        void setObrotalfa(int value);
        void setPochyleniea(int value);
        void setPochylenieb(int value);
        void mnozenieMacierzy(float (&pod)[3][3],float inna[3][3]);
        void mnozeniePunktow(float pod[3][3]);
        void obliczSrodek();
        void oblicz();
        void drawPunkt(int x,int y,int r,int g,int b);
        void setMacierz(float (&pod)[3][3], float inna[3][3]);
protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
private:
        QVector<coord> lista,lista2;
        QImage im;
        coord p;
        coord srodek,srodekPom;
        float macierzmc[3][3]={0};
        float macierzc[3][3]={0};
        float macierztranslacji[3][3]={0};
        float macierzskali[3][3]={0};
        float macierzobrotu[3][3]={0};
        float macierzpochyleniaa[3][3]={0};
        float macierzpochyleniab[3][3]={0};
signals:

};

#endif // EKRAN_H
