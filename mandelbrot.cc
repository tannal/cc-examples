#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkImage.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPaint.h"
#include "include/core/SkColor.h"
#include "include/core/SkStream.h"
#include "include/core/SkData.h"
#include "include/encode/SkPngEncoder.h"

#include <iostream>
#include <fstream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;
constexpr int MAX_ITER = 1000;
constexpr double SCALE = 0.006;

int mandelbrot(double cr, double ci) {
    double zr = 0, zi = 0;
    int n = 0;
    while (n < MAX_ITER && zr * zr + zi * zi < 4.0) {
        double temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        n++;
    }
    return n;
}

SkColor getColor(int iterations) {
    if (iterations == MAX_ITER) {
        return SkColorSetRGB(0, 0, 0); // Black for points inside the Mandelbrot set
    } else {
        // Use a gradient or some color scheme based on the number of iterations
        int color = (255 * iterations) / MAX_ITER;
        return SkColorSetRGB(color, 0, 255 - color);
    }
}

void drawMandelbrot(SkCanvas* canvas) {
    SkPaint paint;
    paint.setAntiAlias(false);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double cr = (x - WIDTH / 2) * SCALE - 0.75;
            double ci = (y - HEIGHT / 2) * SCALE;
            int iter = mandelbrot(cr, ci);
            paint.setColor(getColor(iter));
            canvas->drawPoint(x, y, paint);
        }
    }
}

int main() {

    
    int width = WIDTH; // Replace WIDTH with the actual width value
    int height = HEIGHT; // Replace HEIGHT with the actual height value
    SkColorType type = kN32_SkColorType; // Replace kN32_SkColorType with the actual color type
    SkAlphaType alpha = kOpaque_SkAlphaType; // Replace kOpaque_SkAlphaType with the actual alpha type
    SkSurfaceProps surfaceProps; // Replace surfaceProps with the actual surface properties

    sk_sp<SkSurface> surface = SkSurfaces::Raster(SkImageInfo::Make(width, height, type, alpha));

    if (!surface) {
        std::cerr << "Could not create surface." << std::endl;
        return 1;
    }

    SkCanvas* canvas = surface->getCanvas();
    drawMandelbrot(canvas);

    SkBitmap bitmap;
    if (!bitmap.tryAllocN32Pixels(WIDTH, HEIGHT)) {
        std::cerr << "Could not allocate bitmap." << std::endl;
        return 1;
    }
    canvas->readPixels(bitmap, 0, 0);

    SkFILEWStream outStream("mandelbrot.png");
    if (!SkPngEncoder::Encode(&outStream, bitmap.pixmap(), SkPngEncoder::Options())) {
        std::cerr << "Failed to save image." << std::endl;
        return 1;
    }

    std::cout << "Mandelbrot image saved as 'mandelbrot.png'" << std::endl;
    // draw mandelbrot on a window
    // drawMandelbrot(canvas);
    // while (true) {
    //     // Draw the canvas
    //     // ...
    // }

    return 0;
}