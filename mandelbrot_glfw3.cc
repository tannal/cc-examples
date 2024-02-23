#include "GLFW/glfw3.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLAssembleInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkColor.h"

#include <iostream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;
constexpr int MAX_ITER = 1000;
constexpr double SCALE = 0.006;

int mandelbrot(double cr, double ci) {
    double zr = 0.0, zi = 0.0;
    int n = 0;
    while ((zr*zr + zi*zi < 4.0) && (n < MAX_ITER)) {
        double temp = zr*zr - zi*zi + cr;
        zi = 2.0*zr*zi + ci;
        zr = temp;
        ++n;
    }
    return n;
}

SkColor getColor(int iterations) {
    if (iterations == MAX_ITER) {
        return SkColorSetARGB(255, 0, 0, 0); // black
    } else {
        // Create a color based on the number of iterations.
        int r = (iterations % 256);
        int g = ((iterations * 7) % 256);
        int b = ((iterations * 13) % 256);
        return SkColorSetARGB(255, r, g, b);
    }
}

void drawMandelbrot(SkCanvas* canvas) {
    SkPaint paint;
    paint.setAntiAlias(false);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double cr = (x - WIDTH / 2) * SCALE - 0.75;
            double ci = (y - HEIGHT / 2) * SCALE;
            int n = mandelbrot(cr, ci);
            SkColor color = getColor(n);
            paint.setColor(color);
            canvas->drawPoint(x, y, paint);
        }
    }
}

int main() {
    return 0;
}
