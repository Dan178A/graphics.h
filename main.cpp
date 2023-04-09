

#include <conio.h>

#include <dos.h>

#include <stdlib.h>
#include <string>
#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;
void Linea(int x1, int y1, int x2, int y2, int color = RED){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    while (x1 != x2 || y1 != y2){
        putpixel(x1, y1, color);
        int e2 = 2 * err;
        if (e2 > -dy){
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx){
            err += dx;
            y1 += sy;
        }
    }
}
void LineaDiscontinua(int x1, int y1, int x2, int y2){
    const int dashSize = 5; // longitud de la seccion discontinua
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int count = 0;
    while (true){
        if (count == dashSize){
            count = 0;
        }
        else if (count < dashSize / 2){
            putpixel(x1, y1, RED); // Dibuja un punto blanco
        }
        x1 += sx;
        err += 2 * dy;
        if (err > 0){
            y1 += sy;
            err -= 2 * dx;
        }
        if ((sx > 0 && x1 > x2) || (sx < 0 && x1 < x2)){
            break;
        }
        if ((sy > 0 && y1 > y2) || (sy < 0 && y1 < y2)){
            break;
        }
        count++;
    }
}
void Elipse(int x, int y, int stangle, int endangle, int xradius, int yradius, int color = WHITE){
    float angle, step;
    if (stangle > endangle{
        endangle += 360;
    }
    step = (float)1 / sqrt(xradius * xradius + yradius * yradius);
    for (angle = stangle; angle < endangle; angle += step)
    {
        float radian = angle * 3.1416 / 180;
        int x_point = x + cos(radian) * xradius;
        int y_point = y + sin(radian) * yradius;
        putpixel(x_point, y_point, color); // Puedes cambiar el color aqui
    }
}
void ElipseRelleno(int x, int y, int stangle, int endangle, int xradius, int yradius, int color){
    setfillstyle(SOLID_FILL, color);
    Elipse(x, y, stangle, endangle, xradius, yradius);
    fillellipse(x, y, xradius, yradius);
}
void Rectangulo(int left, int top, int right, int bottom, int color = RED){

    // Draw the lines of the Rectangulo
    Linea(left, top, right, top);       // Top line
    Linea(right, top, right, bottom);   // Right line
    Linea(right, bottom, left, bottom); // Bottom line
    Linea(left, bottom, left, top);     // Left line
                                        // Fill the Rectangulo
}
void RectanguloRelleno(int left, int top, int right, int bottom, int color = RED){
    Rectangulo(left, top, right, bottom);
    for (int y = top + 1; y < bottom; y++)
    {
        // Draw a semirrecta from left to right
        int start_x = left + 1;
        int end_x = right;
        for (int x = start_x; x < end_x; x++)
        {
            putpixel(x, y, color);
        }
    }
}
void TrianguloEquilatero(int x, int y, int lado){
    double altura = sqrt(3) / 2 * lado;

    int x1 = x - lado / 2;
    int y1 = y + altura / 3;

    int x2 = x + lado / 2;
    int y2 = y + altura / 3;

    int x3 = x;
    int y3 = y - 2 * altura / 3;

    Linea(x1, y1, x2, y2);
    Linea(x2, y2, x3, y3);
    Linea(x3, y3, x1, y1);
}
void TrianguloEquilateroRelleno(int x, int y, int lado, int color){
    double altura = sqrt(3) / 2 * lado;

    int x1 = x - lado / 2;
    int y1 = y + altura / 3;

    int x2 = x + lado / 2;
    int y2 = y + altura / 3;

    int x3 = x;
    int y3 = y - 2 * altura / 3;

    // Traza lineas entre los tres vertices del triángulo equilátero
    Linea(x1, y1, x2, y2);
    Linea(x2, y2, x3, y3);
    Linea(x3, y3, x1, y1);

    // Rellenar la forma con el color
    setfillstyle(SOLID_FILL, color);
    int poly[8] = {x1, y1, x2, y2, x3, y3, x1, y1};
    fillpoly(4, poly);
}

void TrianguloIsosceles(int x, int y, int base, int altura){
    int x1 = x - (base / 2);
    int y1 = y + (altura / 2);
    int x2 = x;
    int y2 = y - (altura / 2);
    int x3 = x + (base / 2);
    int y3 = y + (altura / 2);

    Linea(x1, y1, x2, y2);
    Linea(x2, y2, x3, y3);
    Linea(x3, y3, x1, y1);
}
void TrianguloIsoscelesRelleno(int x, int y, int base, int altura, int color){
    int x1 = x - (base / 2);
    int y1 = y + (altura / 2);
    int x2 = x;
    int y2 = y - (altura / 2);
    int x3 = x + (base / 2);
    int y3 = y + (altura / 2);
    // Escanear cada fila del triangulo
    for (int fila = y2 + 1; fila <= y1; fila++)
    {
        int dx = abs(fila - y2);
        int xi = x2 - (dx * base) / (2 * altura);
        int xf = x2 + (dx * base) / (2 * altura);
        for (int col = xi + 1; col <= xf - 1; col++)
        {
            putpixel(col, fila, color); // Pintar el pixel en (col, fila)
        }
    }
    TrianguloIsosceles(x, y, base, altura); // Dibujar la linea del triangulo despues de pintar
}

void TrianguloRectangulo(int x, int y, int base, int altura, int color = WHITE){
    int x2 = x;
    int y2 = y - altura;
    // For each row in the triangle, set the color of the pixels in the row
    for (int fila = y; fila >= y2 + 1; fila--)
    {
        // Calculate the x-coordinates of the two endpoints of the row
        int dx = abs(fila - y2);
        int xi = x2 - (dx * base) / altura;
        int xf = x2;
        // For each pixel in the row, set the color to 'color'
        for (int col = xi + 1; col <= xf - 1; col++)
        {
            putpixel(col, fila, color);
        }
    }
}
void TrianguloRectanguloRelleno(int x, int y, int base, int altura, int color){
    TrianguloRectangulo(x, y, base, altura); // Dibujar el triángulo rectángulo
    int x2 = x;
    int y2 = y - altura;
    // For each row in the triangle, set the color of the pixels in the row
    for (int fila = y; fila >= y2 + 1; fila--)
    {
        // Calculate the x-coordinates of the two endpoints of the row
        int dx = abs(fila - y2);
        int xi = x2 - (dx * base) / altura;
        int xf = x2;
        // For each pixel in the row, set the color to 'color'
        for (int col = xi + 1; col <= xf - 1; col++)
        {
            putpixel(col, fila, color);
        }
    }
}

void Hexagono(int x, int y, int r, int color){
    int i;
    int ox, oy, px, py;

    // Calcula los puntos del hexagono
    ox = x;
    oy = y;
    px = x + r;
    py = y;
    Linea(ox, oy, px, py);
    for (i = 1; i < 6; i++)
    {
        ox = px;
        oy = py;
        px = x + r * cos(i * M_PI / 3.0);
        py = y + r * sin(i * M_PI / 3.0);
        Linea(ox, oy, px, py);
    }
    Linea(px, py, x + r, y);
}
void HexagonoRelleno(int x, int y, int r, int color){
    setcolor(color);
    setfillstyle(SOLID_FILL, color); // establece el estilo para el relleno
    int i;
    int ox, oy, px, py;

    // Calcula los puntos del hexagono
    ox = x;
    oy = y;
    px = x + r;
    py = y;
    Linea(ox, oy, px, py);
    for (i = 1; i < 6; i++)
    {
        ox = px;
        oy = py;
        px = x + r * cos(i * M_PI / 3.0);
        py = y + r * sin(i * M_PI / 3.0);
        Linea(ox, oy, px, py);
    }
    Linea(px, py, x + r, y);
    floodfill(x + r / 2, y + r / 2, color); // Rellena el hexagono con el color
}

void Circulo(int x, int y, int r, int color = RED){
    int xi, yi, xf, yf;
    float theta = 0.0;
    while (theta <= 2 * M_PI){
        xi = round(r * cos(theta) + x);
        yi = round(r * sin(theta) + y);
        theta += 0.01;
        xf = round(r * cos(theta) + x);
        yf = round(r * sin(theta) + y);
        Linea(xi, yi, xf, yf, color);
    }
}
void CirculoRelleno(int x, int y, int r, int color){
    setcolor(color);
    setfillstyle(SOLID_FILL, color); // Establece el estilo para el relleno
    // Fill the circle by drawing horizontal lines from top to bottom
    for (int i = y - r; i <= y + r; i++){
        for (int j = x - r; j <= x + r; j++){
            if (pow(j - x, 2) + pow(i - y, 2) <= pow(r, 2)){
                putpixel(j, i, color);
            }
        }
    }
}

void Pentagono(int x[], int y[], int n){
    // Draw the pentagon using line()
    int i;
    for (i = 0; i < n - 1; i++){
        Linea(x[i], y[i], x[i + 1], y[i + 1]);
    }
    Linea(x[n - 1], y[n - 1], x[0], y[0]);
}
void PentagonoRelleno(int x[], int y[], int n, int color){
    // Draw and fill the pentagon
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    int vertices[n * 2];
    for (int i = 0; i < n; i++){
        vertices[i * 2] = x[i];
        vertices[i * 2 + 1] = y[i];
    }

    // Draw and fill the polygon
    fillpoly(n, vertices);
}

void Punto(int x, int y, int size, int color){
    // Set color and size of point
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    setlinestyle(0, 0, size);

    // Draw point at (x, y)
    Circulo(x, y, 0, color);
    floodfill(x, y, color);
}
void Cuadrado(int x, int y, int size){
    Rectangulo(x, y, x + size, y + size);
}
void CuadradoRelleno(int x, int y, int size, int color){

    RectanguloRelleno(x, y, x + size, y + size, BLUE);
}

void Heptagono(int x, int y, int radius){
    int n = 7; // numero de lados del heptagono
    float angle = 360.0 / n;
    float theta = -90.0;
    int x0 = 0, y0 = 0;
    int x1, y1;

    for (int i = 0; i <= n; i++){
        // Calcular los puntos final e inicial para la linea del heptagono
        x1 = round(radius * cos(theta * M_PI / 180.0));
        y1 = round(radius * sin(theta * M_PI / 180.0));
        if (i > 0){
            Linea(x + x0, y + y0, x + x1, y + y1);
        }
        x0 = x1;
        y0 = y1;
        // Calcular el siguiente angulo
        theta += angle;
    }
}
// Definir la función de rellenar el heptágono
void HeptagonoRelleno(int x, int y, int radius, int color){

    Heptagono(x, y, radius);
    // Establecer el color del relleno
    setfillstyle(SOLID_FILL, color);

    // Definir el arreglo de puntos del polígono
    int puntos[14];
    int n = 7;
    float angle = 360.0 / n;
    float theta = -90.0;
    int x0 = 0, y0 = 0;
    int x1, y1;
    for (int i = 0; i <= n; i++){
        x1 = round(radius * cos(theta * M_PI / 180.0));
        y1 = round(radius * sin(theta * M_PI / 180.0));
        puntos[i * 2] = x + x1;
        puntos[i * 2 + 1] = y + y1;
        theta += angle;
    }

    // Dibujar y rellenar el polígono
    fillpoly(n, puntos);
}

void Octagono(int x, int y, int lado){
    int n = 8; // número de lados del octagono
    float angle = 360.0 / n;
    float theta = -45.0 + angle / 2;
    int x0 = 0, y0 = 0;
    int x1, y1;

    for (int i = 0; i <= n; i++){
        // Calcular los puntos final e inicial para la linea del octágono
        x1 = round(lado / 2 * cos(theta * M_PI / 180.0));
        y1 = round(lado / 2 * sin(theta * M_PI / 180.0));
        if (i > 0){
            // Dibujar la linea del octagono
            Linea(x + x0, y + y0, x + x1, y + y1);
        }
        x0 = x1;
        y0 = y1;
        // Calcular el siguiente angulo
        theta += angle;
    }
    // Dibujar la última línea del octágono
    Linea(x + x0, y + y0, x + x1, y + y1);
}

void OctagonoRelleno(int x, int y, int lado, int color){
    Octagono(x, y, lado);

    // Establecer el color del relleno
    setfillstyle(SOLID_FILL, color);

    // Definir el arreglo de puntos del polígono
    int puntos[16];
    int n = 8;
    float angle = 360.0 / n;
    float theta = -45.0 + angle / 2;
    int x0 = 0, y0 = 0;
    int x1, y1;
    for (int i = 0; i <= n; i++){
        x1 = round(lado / 2 * cos(theta * M_PI / 180.0));
        y1 = round(lado / 2 * sin(theta * M_PI / 180.0));
        puntos[i * 2] = x + x1;
        puntos[i * 2 + 1] = y + y1;
        theta += angle;
    }

    // Dibujar y rellenar el polígono
    fillpoly(n, puntos);
}

void Rellenar(int x, int y, int colorRelleno, int colorBorde){
    /*25% abajo derecha*/
    int xR = x;
    int yR = y;
    int colorPixelActual = -1;
    for (; xR < 1200; xR = xR + 1){
        colorPixelActual = getpixel(xR, yR);
        if (colorPixelActual == colorBorde){
            xR = x;
            yR = yR + 1;
            colorPixelActual = getpixel(xR, yR);
            if (colorPixelActual == colorBorde){
                break;
            }
        }
        putpixel(xR, yR, colorRelleno);
    }
    /*25% abajo izquierda*/
    xR = x;
    yR = y;
    colorPixelActual = -1;
    for (; xR >= 0; xR = xR - 1){
        colorPixelActual = getpixel(xR, yR);
        if (colorPixelActual == colorBorde){
            xR = x;
            yR = yR + 1;
            colorPixelActual = getpixel(xR, yR);
            if (colorPixelActual == colorBorde){
                break;
            }
        }
        putpixel(xR, yR, colorRelleno);
    }
    /*25%  izquierda arriba*/
    xR = x;
    yR = y;
    colorPixelActual = -1;
    for (; xR >= 0; xR = xR - 1){
        colorPixelActual = getpixel(xR, yR);
        if (colorPixelActual == colorBorde){
            xR = x;
            yR = yR - 1;
            colorPixelActual = getpixel(xR, yR);
            if (colorPixelActual == colorBorde){
                break;
            }
        }
        putpixel(xR, yR, colorRelleno);
    }
    /* 25 derecha arriba*/
    xR = x;
    yR = y;
    colorPixelActual = -1;
    for (; xR < 1200; xR = xR + 1){
        colorPixelActual = getpixel(xR, yR);
        if (colorPixelActual == colorBorde){
            xR = x;
            yR = yR - 1;
            colorPixelActual = getpixel(xR, yR);
            if (colorPixelActual == colorBorde){
                break;
            }
        }
        putpixel(xR, yR, colorRelleno);
    }
}
/**
 * The function "LimpiarArea" clears a percentage of the screen by filling it with the background
 * color.
 *
 * @param percent The percentage of the screen area to be cleared.
 */
void LimpiarArea(int percent){
    int width = getmaxx();
    int height = getmaxy();
    int x1 = 0;
    int y1 = 0;
    int x2 = width * percent / 100;
    int y2 = height * percent / 100;
    setcolor(getbkcolor());
    setfillstyle(SOLID_FILL, getbkcolor());
    bar(x1, y1, x2, y2);
}
void LimpiarPantalla(){
    cleardevice();
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    Linea(30, 450, 600, 450);

    Linea(0, 440, 30, 450);

    Linea(650, 436, 600, 450);

    Linea(30, 430, 600, 430);

    Linea(0, 420, 30, 430);

    Linea(650, 416, 600, 430);

    Linea(30, 410, 600, 410);

    Linea(0, 400, 30, 410);

    Linea(650, 400, 600, 410);

    Linea(30, 410, 30, 450);

    Linea(600, 410, 600, 450);

    Linea(593, 410, 593, 450);

    Linea(37, 410, 37, 450);

    Rectangulo(40, 215, 590, 370);

    Rectangulo(200, 215, 410, 370);

    Linea(200, 221, 410, 221);

    Linea(200, 227, 410, 227);

    Rectangulo(210, 250, 400, 260);

    Rectangulo(213, 260, 397, 370);

    Rectangulo(235, 270, 290, 367);

    Rectangulo(310, 270, 370, 367);

    Linea(40, 260, 200, 260);

    Linea(40, 265, 200, 265);

    Linea(92, 265, 92, 370);

    Linea(148, 265, 148, 370);

    Linea(46, 297, 46, 370);

    Linea(46, 297, 66, 266);

    Linea(87, 297, 87, 370);

    Linea(87, 297, 64, 266);

    Linea(98, 297, 98, 370);

    Linea(98, 297, 118, 266);

    Linea(142, 297, 142, 370);

    Linea(142, 297, 118, 266);

    Linea(154, 297, 154, 370);

    Linea(154, 297, 174, 266);

    Linea(194, 297, 194, 370);

    Linea(194, 297, 174, 266);

    Linea(40, 224, 80, 220);

    Linea(80, 220, 156, 220);

    Linea(156, 220, 199, 224);

    Linea(40, 228, 80, 224);

    Linea(80, 224, 156, 224);

    Linea(156, 224, 199, 228);

    Elipse(60, 218, 10, 170, 9, 20);

    Elipse(100, 218, 10, 170, 9, 20);

    Elipse(140, 218, 10, 170, 9, 20);

    Elipse(178, 218, 10, 170, 9, 20);

    Linea(40, 195, 40, 220);

    Linea(80, 195, 80, 215);

    Linea(120, 195, 120, 215);

    Linea(160, 195, 160, 215);

    Linea(200, 195, 200, 215);

    Linea(40, 195, 59, 170);

    Linea(80, 195, 59, 170);

    Linea(80, 195, 97, 170);

    Linea(120, 195, 97, 170);

    Linea(120, 195, 137, 170);

    Linea(160, 195, 137, 170);

    Linea(160, 195, 177, 170);

    Linea(200, 195, 177, 170);

    Rectangulo(90, 137, 166, 168);

    Linea(90, 168, 90, 180);

    Linea(166, 168, 166, 186);

    Elipse(106, 173, 20, 143, 20, 32);

    Elipse(106, 173, 10, 170, 14, 29);

    Elipse(146, 173, 10, 160, 20, 32);

    Elipse(146, 173, 10, 170, 12, 29);

    Linea(90, 137, 80, 133);

    Linea(80, 133, 90, 127);

    Linea(166, 137, 177, 133);

    Linea(177, 133, 166, 127);

    Linea(90, 127, 166, 127);

    Elipse(128, 126, 0, 180, 33, 33);

    Elipse(128, 90, 0, 360, 7, 3);

    Linea(128, 80, 128, 87);

    Linea(410, 260, 590, 260);

    Linea(410, 265, 590, 265);

    Linea(465, 265, 465, 370);

    Linea(528, 265, 528, 370);

    Linea(415, 297, 415, 370);

    Linea(415, 297, 433, 266);

    Linea(459, 297, 459, 370);

    Linea(459, 297, 436, 266);

    Linea(470, 297, 470, 370);

    Linea(470, 297, 494, 266);

    Linea(523, 297, 523, 370);

    Linea(523, 297, 494, 266);

    Linea(533, 297, 533, 370);

    Linea(533, 297, 556, 266);

    Linea(585, 297, 585, 370);

    Linea(585, 297, 556, 266);

    Linea(410, 224, 460, 220);

    Linea(460, 220, 530, 220);

    Linea(530, 220, 590, 224);

    Linea(410, 228, 460, 224);

    Linea(460, 224, 530, 224);

    Linea(530, 224, 590, 228);

    Elipse(430, 218, 10, 170, 9, 20);

    Elipse(476, 218, 10, 170, 9, 20);

    Elipse(519, 218, 10, 170, 9, 20);

    Elipse(565, 218, 10, 170, 9, 20);

    Linea(410, 195, 410, 220);

    Linea(454, 195, 454, 215);

    Linea(498, 195, 498, 215);

    Linea(540, 195, 540, 215);

    Linea(590, 195, 590, 215);

    Linea(410, 195, 429, 170);

    Linea(454, 195, 429, 170);

    Linea(454, 195, 476, 170);

    Linea(498, 195, 476, 170);

    Linea(498, 195, 520, 170);

    Linea(540, 195, 520, 170);

    Linea(540, 195, 565, 170);

    Linea(590, 195, 565, 170);

    Rectangulo(465, 137, 545, 168);

    Linea(545, 168, 545, 189);

    Linea(465, 168, 465, 182);

    Elipse(481, 173, 20, 143, 20, 32);

    Elipse(481, 173, 10, 170, 14, 29);

    Elipse(521, 173, 10, 160, 22, 32);

    Elipse(520, 173, 10, 170, 14, 29);

    Linea(464, 137, 456, 133);

    Linea(456, 133, 464, 127);

    Linea(544, 137, 554, 133);

    Linea(554, 133, 544, 127);

    Linea(465, 127, 544, 127);

    Elipse(504, 126, 0, 180, 33, 33);

    //  setcolor(15);

    Elipse(504, 90, 0, 360, 7, 3);

    Linea(504, 80, 504, 87);

    //________center-upper__________

    //  setcolor(12);

    Linea(205, 110, 205, 214);

    Linea(215, 110, 215, 214);

    Linea(205, 110, 215, 110);

    Linea(205, 120, 215, 120);

    Linea(205, 122, 215, 122);

    Linea(205, 124, 215, 124);

    Linea(205, 199, 215, 199);

    Elipse(210, 99, 180, 360, 15, 12);

    Linea(196, 99, 203, 99);

    Linea(224, 99, 216, 99);

    Elipse(210, 99, 0, 180, 6, 8);

    Linea(200, 80, 200, 99);

    Linea(206, 80, 206, 92);

    Linea(212, 80, 212, 92);

    Linea(219, 80, 219, 99);

    Linea(199, 80, 220, 80);

    //  setcolor(15);

    Linea(199, 64, 199, 79);

    Linea(220, 64, 220, 79);

    Elipse(210, 64, 0, 180, 10, 8);

    Linea(210, 48, 210, 57);

    //  setcolor(12);

    Linea(405, 110, 405, 214);

    Linea(396, 110, 396, 214);

    Linea(405, 110, 396, 110);

    Linea(396, 120, 405, 120);

    Linea(396, 122, 405, 122);

    Linea(396, 124, 405, 124);

    Linea(396, 199, 405, 199);

    Elipse(400, 99, 180, 360, 15, 12);

    Linea(385, 99, 395, 99);

    Linea(406, 99, 416, 99);

    Elipse(400, 99, 0, 180, 6, 8);

    Linea(390, 80, 390, 99);

    Linea(396, 80, 396, 92);

    Linea(402, 80, 402, 92);

    Linea(409, 80, 409, 99);

    Linea(389, 80, 410, 80);

    //  setcolor(15);

    Linea(389, 64, 389, 79);

    Linea(410, 64, 410, 79);

    Elipse(399, 64, 0, 180, 10, 8);

    Linea(400, 48, 400, 57); ////

    //  setcolor(12);

    Elipse(230, 218, 10, 170, 9, 20);

    Elipse(266, 218, 10, 170, 9, 20);

    Elipse(303, 218, 10, 170, 9, 20);

    Elipse(343, 218, 10, 170, 9, 20);

    Elipse(380, 218, 10, 170, 9, 20);

    Linea(247, 195, 247, 215);

    Linea(285, 195, 285, 215);

    Linea(323, 195, 323, 215);

    Linea(360, 195, 360, 215);

    Linea(217, 195, 227, 170);

    Linea(247, 195, 227, 170);

    Linea(247, 195, 266, 170);

    Linea(285, 195, 266, 170);

    Linea(285, 195, 305, 170);

    Linea(323, 195, 305, 170);

    Linea(323, 195, 340, 170);

    Linea(360, 195, 340, 170);

    Linea(360, 195, 376, 170);

    Linea(395, 195, 376, 170);

    Linea(216, 170, 396, 170);

    //  setcolor(12);

    Elipse(224, 173, 10, 150, 10, 18);

    Elipse(244, 173, 10, 170, 10, 18);

    Elipse(264, 173, 10, 170, 10, 18);

    Elipse(284, 173, 10, 150, 10, 18);

    Elipse(324, 173, 10, 170, 10, 18);

    Elipse(364, 173, 10, 170, 10, 18);

    Elipse(304, 173, 10, 170, 10, 18);

    Elipse(343, 173, 10, 170, 10, 18);

    Elipse(384, 173, 10, 170, 10, 18);

    Linea(216, 150, 396, 150);

    //_________ON TOP________

    //  setcolor(15);

    Elipse(240, 142, 10, 170, 7, 11);

    Linea(234, 142, 238, 149);

    Linea(246, 140, 242, 149);

    Linea(240, 127, 240, 131);

    Elipse(260, 142, 10, 170, 7, 11);

    Linea(267, 140, 260, 150);

    Linea(252, 140, 258, 150);

    Linea(260, 127, 260, 131);

    Elipse(280, 142, 10, 170, 7, 11);

    Linea(287, 140, 280, 150);

    Linea(272, 140, 278, 150);

    Linea(280, 127, 280, 131);

    Elipse(300, 142, 10, 170, 7, 11);

    Linea(307, 140, 300, 150);

    Linea(292, 140, 298, 150);

    Linea(300, 127, 300, 131);

    Elipse(320, 142, 10, 170, 7, 11);

    Linea(327, 140, 320, 150);

    Linea(312, 140, 318, 150);

    Linea(320, 127, 320, 131);

    Elipse(340, 142, 10, 170, 7, 11);

    Linea(347, 140, 340, 150);

    Linea(332, 140, 338, 150);

    Linea(340, 127, 340, 131);

    Elipse(360, 142, 10, 170, 7, 11);

    Linea(367, 140, 360, 150);

    Linea(352, 140, 358, 150);

    Linea(360, 127, 360, 131);

    //------ FLAG

    //  setcolor(15);

    Rectangulo(289, 30, 294, 150);

    //  setcolor(12);

    Rectangulo(294, 35, 340, 45);

    //  setcolor(15);

    Rectangulo(294, 45, 340, 55);

    //  setcolor(10);

    Rectangulo(294, 55, 340, 65);

    //  setcolor(9);

    circle(316, 50, 5);

    LineaDiscontinua(312, 46, 316, 50);
    //
    LineaDiscontinua(316, 46, 316, 50);
    //
    LineaDiscontinua(319, 46, 316, 50);
    //
    LineaDiscontinua(319, 46, 316, 55);
    //
    LineaDiscontinua(312, 46, 316, 54);

    //_____TEXT

    setcolor(4);

    settextstyle(7, HORIZ_DIR, 2);

    outtextxy(240, 406, "THE RED FORT");

    setcolor(15);

    settextstyle(3, HORIZ_DIR, 2);
    outtextxy(210, 428, "Proyect by: Daniel Silva");

    //    setcolor(2);
    getch();
    LimpiarArea(50);
    getch();
    LimpiarPantalla();
    /* Aqui estan las formas rellenas*/
    setcolor(13);
    Rectangulo(1, 1, 639, 479);
    Rectangulo(15, 15, 624, 464);
    // setcolor(LIGHTBLUE);
    //    setfillstyle(6, 11);

    Linea(0, 0, 640, 480);
    Heptagono(500, 630, 50);
    Punto(50, 50, 10, RED);

    Linea(100, 100, 200, 200);

    LineaDiscontinua(300, 300, 400, 400);

    CirculoRelleno(150, 150, 30, BLUE);

    ElipseRelleno(250, 250, 0, 360, 50, 30, BLUE);

    RectanguloRelleno(50, 200, 100, 250, BLUE);

    CuadradoRelleno(200, 50, 50, BLUE);
    // //    floodfill(2, 2, 13);
    // //    settextstyle(7, 0, 3);
    // //    setcolor(12);
    TrianguloEquilateroRelleno(50, 400, 60, BLUE);

    TrianguloIsoscelesRelleno(200, 400, 60, 80, BLUE);

    TrianguloRectanguloRelleno(400, 400, 60, 80, BLUE);

    HexagonoRelleno(500, 100, 70, RED);

    HeptagonoRelleno(500, 630, 50, WHITE);
    OctagonoRelleno(400, 200, 40, GREEN);
    int px[] = {500, 550, 590, 550, 500, 460, 420, 460};
    int py[] = {200, 200, 250, 300, 300, 300, 250, 200};
    PentagonoRelleno(px, py, 8, BLUE);
    getch();      // Esperar a que el usuario presione una tecla
    closegraph(); // Cerrar la ventana grafica
    return 0;
}
