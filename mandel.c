/*
c program:
--------------------------------
 1. draws Mandelbrot set for Fc(z)=z*z +c
 using Mandelbrot algorithm ( boolean escape time )
-------------------------------
2. technique of creating ppm file is  based on the code of Claudio Rocchini
http://en.wikipedia.org/wiki/Image:Color_complex_plot.jpg
create 24 bit color graphic file ,  portable pixmap file = PPM
see http://en.wikipedia.org/wiki/Portable_pixmap
to see the file use external application ( graphic viewer)

Taken from <https://rosettacode.org/wiki/Mandelbrot_set#PPM_non_interactive>.

Files from Rosetta Code are under the [GNU Free Document License 1.3](https://www.gnu.org/licenses/fdl-1.3.en.html)
unless otherwise specified.
*/

#include <stdio.h>
#include <math.h>

#include "time.h"

static void run(int iXmax, int iYmax);

int main(void)
{
    const int width = 1280;
    const int height = 1024;
    const unsigned long pixels = (unsigned long)width * (unsigned long)height;
    my_time_t start, end;
    float kpixels_per_second;
    start = time_get();
    run(width, height);
    end = time_get();
    kpixels_per_second = time_diff(start, end, pixels);
    printf("Ran at %.3f kpixels per second\n", kpixels_per_second);
    return 0;
}

static void run(int iXmax, int iYmax)
{
    /* screen ( integer) coordinate */
    int iX, iY;
    /* world ( double) coordinate = parameter plane*/
    double Cx, Cy;
    const double CxMin = -2;
    const double CxMax = 1;
    const double CyMin = -1.5;
    const double CyMax = 1.5;
    /* */
    double PixelWidth = (CxMax - CxMin) / iXmax;
    double PixelHeight = (CyMax - CyMin) / iYmax;
    /* color component ( R or G or B) is coded from 0 to 255 */
    /* it is 24 bit color RGB file */
    const int MaxColorComponentValue = 255;
    FILE *fp;
    char *filename = "output.ppm";
    char *comment = "# "; /* comment should start with # */
    static unsigned char color[3];
    /* Z=Zx+Zy*i  ;   Z0 = 0 */
    double Zx, Zy;
    double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
    /*  */
    int Iteration;
    const int IterationMax = 255;
    /* bail-out value , radius of circle ;  */
    const double EscapeRadius = 2;
    double ER2 = EscapeRadius * EscapeRadius;
    /*create new file,give it a name and open it in binary mode  */
    fp = fopen(filename, "wb"); /* b -  binary mode */
    /*write ASCII header to the file*/
    fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", comment, iXmax, iYmax, MaxColorComponentValue);
    /* compute and write image data bytes to the file*/
    for (iY = 0; iY < iYmax; iY++)
    {
        Cy = CyMin + (iY * PixelHeight);
        if (fabs(Cy) < PixelHeight / 2)
        {
            Cy = 0.0; /* Main antenna */
        }
        for (iX = 0; iX < iXmax; iX++)
        {
            Cx = CxMin + iX * PixelWidth;
            /* initial value of orbit = critical point Z= 0 */
            Zx = 0.0;
            Zy = 0.0;
            Zx2 = Zx * Zx;
            Zy2 = Zy * Zy;
            /* */
            for (Iteration = 0; Iteration < IterationMax && ((Zx2 + Zy2) < ER2); Iteration++)
            {
                Zy = 2 * Zx * Zy + Cy;
                Zx = Zx2 - Zy2 + Cx;
                Zx2 = Zx * Zx;
                Zy2 = Zy * Zy;
            };
            /* compute  pixel color (24 bit = 3 bytes) */
            if (Iteration == IterationMax)
            { /*  interior of Mandelbrot set = black */
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }
            else
            {
                /* exterior of Mandelbrot set = white */
                color[0] = Iteration; /* Red*/
                color[1] = Iteration; /* Green */
                color[2] = Iteration; /* Blue */
            };
            /*write color to the file*/
            fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
}
