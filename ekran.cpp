#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>
#include <QImage>
#include <iostream>

using namespace std;

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{
    im=QImage(1000, 800, QImage::Format_RGB32);
    im.fill(0);
    for(int i=0;i<=2;i++)
    {
        macierzmc[i][i]=1;
        macierzc[i][i]=1;
        macierztranslacji[i][i]=1;
        macierzskali[i][i]=1;
        macierzobrotu[i][i]=1;
        macierzpochyleniaa[i][i]=1;
        macierzpochyleniab[i][i]=1;
    }
}


void Ekran::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        if(lista.size()<6)
        {
            p.x=e->pos().x();
            p.y=e->pos().y();
            drawPunkt(p.x,p.y,255,255,0);
            update();
            p.p=1;
            lista.push_back(p);
            if(lista.size()==6)
            {
                lista2=lista;
                obliczSrodek();
                srodekPom=srodek;
                macierzc[0][2]=srodek.x;
                macierzmc[0][2]=-srodek.x;
                macierzmc[1][2]=-srodek.y;
                macierzc[1][2]=srodek.y;
                rysujWielokat();
            }
        }
    }
}



void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0,0,im);
}

void Ekran::linia(int x1,int y1,int x2,int y2,int r,int g,int b)
{
    if(abs(y2-y1)<=abs(x2-x1))
        {
            float y=y1;
            float a=(float)(y2-y1)/(x2-x1);
            if(x1<x2)
            {
                for(int i=x1;i<=x2;i++)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b);
                    y+=a;
                }
            }
            else
            {
                for(int i=x1;i>=x2;i--)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b);
                    y-=a;
                }
            }

        }
        else
        {
            float x=x1;
            float a=(float)(x1-x2)/(y1-y2);
            if(y1<y2)
            {
                for(int i=y1;i<=y2;i++)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b);
                    x+=a;
                }
            }
            else
            {
                for(int i=y1;i>=y2;i--)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b);
                    x-=a;
                }
            }
    }
}

void Ekran::drawPixel(int x,int y,int r,int g,int b)
{
    if((x<im.width()&&x>=0)&&(y<im.height()&&y>=0))
    {
        uchar *pix=im.scanLine(y)+4*x;
        pix[0]=b;
        pix[1]=g;
        pix[2]=r;
    }
}

void Ekran::drawPunkt(int x,int y,int r,int g,int b)
{
    for(int i=y-2;i<=y+2;i++)
    {
        for(int j=x-2;j<=x+2;j++)
        {
            if((j<im.width()&&j>=0)&&(i<im.height()&&i>=0))
            {
                uchar *pix=im.scanLine(i)+4*j;
                pix[0]=b;
                pix[1]=g;
                pix[2]=r;
            }
        }
    }
}

void Ekran::setSkalax(float value)
{
    macierzskali[0][0]=value;
    oblicz();
}
void Ekran::setSkalay(float value)
{
    macierzskali[1][1]=value;
    oblicz();
}

void Ekran::setTranslajcax(int value)
{

    srodek.x=srodekPom.x+value;
    macierztranslacji[0][2]=value;
    macierzc[0][2]=srodek.x;
    macierzmc[0][2]=-srodek.x;
    oblicz();
}

void Ekran::setTranslajcay(int value)
{
    srodek.y=srodekPom.y+value;
    macierztranslacji[1][2]=value;
    macierzmc[1][2]=-srodek.y;
    macierzc[1][2]=srodek.y;
    oblicz();
}

void Ekran::setObrotalfa(int value)
{
    macierzobrotu[0][0]=cos(value*M_PI/180.0);
    macierzobrotu[0][1]=-sin(value*M_PI/180.0);
    macierzobrotu[1][0]=sin(value*M_PI/180.0);
    macierzobrotu[1][1]=cos(value*M_PI/180.0);
    oblicz();
}

void Ekran::setPochyleniea(int value)
{
    macierzpochyleniaa[0][1]=value;
    oblicz();
}

void Ekran::setPochylenieb(int value)
{
    macierzpochyleniab[1][0]=value;
    oblicz();
}

void Ekran::oblicz()
{
    float macierz[3][3];
    setMacierz(macierz,macierzc);
    mnozenieMacierzy(macierz,macierzskali);
    mnozenieMacierzy(macierz,macierzobrotu);
    mnozenieMacierzy(macierz,macierztranslacji);
    mnozenieMacierzy(macierz,macierzpochyleniaa);
    mnozenieMacierzy(macierz,macierzpochyleniab);
    mnozenieMacierzy(macierz,macierzmc);
    mnozeniePunktow(macierz);
    rysujWielokat();
}

void Ekran::mnozenieMacierzy(float (&pod)[3][3], float inna[3][3])
{
    float macierz[3][3]={0};
    macierz[2][2]=1;
    lista=lista2;
    for(int i=0;i<=1;i++)
    {
        for(int j=0;j<=2;j++)
        {
            for(int k=0;k<=2;k++)
            {
                macierz[i][j]+=pod[i][k]*inna[k][j];
            }
        }
    }
    setMacierz(pod,macierz);
}

void Ekran::mnozeniePunktow(float pod[3][3])
{
    coord punkt;
    for(int i=0;i<lista.size();i++)
    {
        punkt.p=1;
        punkt.x=0;
        punkt.y=0;
        punkt.x+=pod[0][0]*lista[i].x;
        punkt.x+=pod[0][1]*lista[i].y;
        punkt.x+=pod[0][2]*lista[i].p;
        punkt.y+=pod[1][0]*lista[i].x;
        punkt.y+=pod[1][1]*lista[i].y;
        punkt.y+=pod[1][2]*lista[i].p;
        lista[i]=punkt;
    }
}

void Ekran::rysujWielokat()
{
    im.fill(0);
    for(int i=1;i<lista.size();i++)
    {
        drawPunkt(lista[i].x,lista[i].y,255,255,0);
        linia(lista[i-1].x,lista[i-1].y,lista[i].x,lista[i].y,255,255,255);
    }
    drawPunkt(lista[0].x,lista[0].y,255,255,0);
    linia(lista[lista.size()-1].x,lista[lista.size()-1].y,lista[0].x,lista[0].y,255,255,255);
    update();

}

void Ekran::obliczSrodek()
{
    coord pom;
    pom.x=0;
    pom.y=0;
    for(coord a:lista)
    {
        pom.x+=a.x;
        pom.y+=a.y;
    }
    pom.x/=lista.size();
    pom.y/=lista.size();
    srodek=pom;
}


void Ekran::setMacierz(float (&pod)[3][3], float inna[3][3])
{
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {
           pod[i][j]=inna[i][j];
        }
    }
}





