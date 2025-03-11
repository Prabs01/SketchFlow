#include "Shape.h"

Shape::Shape(){
    canvas = nullptr;
}

void Shape::setCanvas(Canvas* canvas_){
    canvas = canvas_;
}

/*############################### LINE ###############################*/

Line::Line(){
    p1 = {-100,-100};
    p2 = {-100, -100};
    size = 3;
}

Line::Line(SDL_Point p1_, SDL_Point p2_, int size_, Color color_){
    p1 = p1_;
    p2 = p2_;
    size = size_;
    color= color_;
}

Line::Line(int x1, int y1, int x2, int y2, int size_, Color color_){
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    size = size_;
    color = color_;
}

void Line::drawLine(bool isBuffer, bool isClear) {
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);

    int ix = (p1.x < p2.x) ? 1 : -1;
    int iy = (p1.y < p2.y) ? 1 : -1;

    int x = p1.x;
    int y = p1.y;

    // Choose the pixel color based on whether it's drawing or clearing
    void (Canvas::*pixelFunc)(int, int, Color) = isBuffer ? &Canvas::setPixelBuffer : &Canvas::setPixel;
    
    Color colorToUse = isClear ? transparent : color;
    if(!isBuffer){
        Color colorToUse = isClear ? canvas->getBackgroundColor() : color;
    }

    if (dx >= dy) {  // Case where x changes more than y
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    (canvas->*pixelFunc)(x + xp, y + yp, colorToUse);
                }
            }
            if (p < 0) {
                p += 2 * dy;
            } else {
                y += iy;
                p += 2 * dy - 2 * dx;
            }
            x += ix;
        }
    } else {  // Case where y changes more than x
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    (canvas->*pixelFunc)(x + xp, y + yp, colorToUse);
                }
            }
            if (p < 0) {
                p += 2 * dx;
            } else {
                x += ix;
                p += 2 * dx - 2 * dy;
            }
            y += iy;
        }
    }
}

void Line::draw() {
    drawLine(false, false);  // Main canvas, drawing
}

void Line::clear() {
    drawLine(false, true);  // Main canvas, clearing
}

void Line::drawBuffer() {
    drawLine(true, false);  // Buffer, drawing
}

void Line::clearBuffer() {
    drawLine(true, true);  // Buffer, clearing
}

void Line::move(int dx, int dy){
    clear();
    p1.x += dx;
    p2.x += dx;
    p1.y += dy;
    p2.y += dy;
    draw();
}

void Line::setStartingPoint(int x1, int y1){
    p1.x = x1;
    p1.y = y1;
}

void Line::setStartingPoint(SDL_Point p){
    p1.x = p.x;
    p1.y = p.y;
}

void Line::setEndingPoint(int x2, int y2){
    p2.x = x2;
    p2.y = y2;
}

void Line::setEndingPoint(SDL_Point p){
    p2.x = p.x;
    p2.y = p.y;
}

/*############################### POLYGON ###############################*/

Polygon::Polygon(){ //def constructor
    numVertices = 3;
    p1 = {-100,-100};
    p2 = {-100, -100};
    size = 3;
}

void Polygon::generateVertices(int x, int y){
    int cx = p1.x;
    int cy = p1.y;
    
    float rad = sqrt( pow((x-cx), 2) + pow((y-cy), 2) );
    float angle = (2*M_PI)/numVertices ;
    
    vertices = (SDL_Point*)malloc(numVertices * sizeof(SDL_Point)); // Dynamically allocate memory
    if (vertices != NULL) {
        
        double rotAngle = atan2((double)(y - cy), (x - cx));  // atan2 handles vertical lines correctly

        //find coordinates w.r.t. axes
        for (int i = 0; i < numVertices; i++) {
            vertices[i].x = rad*cos(angle*i); // Copy points into the allocated array
            vertices[i].y = rad*sin(angle*i); // Copy points into the allocated array
        }

        //rotate back to its original coordinates
        for (int i = 0; i < numVertices; i++) {
             float tempx = vertices[i].x*cos(rotAngle) - vertices[i].y*sin(rotAngle);
             float tempy = vertices[i].x*sin(rotAngle) + vertices[i].y*cos(rotAngle);
             vertices[i].x = tempx;
             vertices[i].y = tempy;
        }

        //translate back to original position
        for (int i = 0; i < numVertices; i++) {
            vertices[i].x = vertices[i].x + cx;
            vertices[i].y = vertices[i].y + cy;
        }
    }
    else{
        printf("Error : Failed to initialize the points!\n");
    }

}

Polygon::Polygon(int Vertices_, int cx, int cy, int x, int y, int size_, Color color_){
    numVertices = Vertices_;
    p1.x = cx;
    p1.y = cy;
    p2.x = x;
    p2.y = y;
    size = size_;
    color = color_;

    generateVertices(x,y);

}

void Polygon::drawPolygon(bool isBuffer, bool isClear) {
    
    Color colorToUse = isClear ? transparent : color;
    if(!isBuffer){
        colorToUse = isClear ? canvas->getBackgroundColor() : color;
    }

    for (int i = 0; i < numVertices; ++i) {
        int nextIndex = (i + 1) % numVertices; // Wrap around to the first vertex
        Line line(vertices[i].x, vertices[i].y, vertices[nextIndex].x, vertices[nextIndex].y, size, colorToUse);
        line.setCanvas(canvas);

        if (isBuffer) {
            line.drawBuffer(); // Draw to buffer
        } else {
            line.draw(); // Draw to canvas
        }
    }
}

void Polygon::draw() {
    drawPolygon(false, false);  // Main canvas, drawing
}

void Polygon::clear() {
    drawPolygon(false, true);  // Main canvas, clearing
}

void Polygon::drawBuffer() {
    drawPolygon(true, false);  // Buffer, drawing
}

void Polygon::clearBuffer() {
    drawPolygon(true, true);  // Buffer, clearing
}

void Polygon::setEndingPoint(int x, int y){
    generateVertices(x,y);
}

bool Polygon::isPointInside(int px, int py){
    bool inside = false;

    for (int i = 0, j = numVertices - 1; i < numVertices; j = i++) {
        int xi = vertices[i].x, yi = vertices[i].y;
        int xj = vertices[j].x, yj = vertices[j].y;

        // Check if point is exactly on a horizontal edge
        if ((yi == py && yj == py) && (px >= std::min(xi, xj) && px <= std::max(xi, xj))) {
            return true;
        }

        // Ray-Casting Algorithm: Check if ray crosses an edge
        bool intersect = ((yi > py) != (yj > py)) &&
                         (px < (xj - xi) * (py - yi) / (yj - yi) + xi);

        if (intersect) inside = !inside;
    }

    return inside;
}

void Polygon::setNoVertices(int noVertices){
    numVertices = noVertices;
}

void Polygon::move(int dx, int dy){
    p1.x += dx;
    p1.y += dy;
    for (int i = 0; i < numVertices; i++) {
        vertices[i].x += dx;
        vertices[i].y += dy;
    }
}

/*############################### RECTANGLE ###############################*/

void Rectangle::generateVertices(int x, int y) {
    originalVertices.resize(4);
    vertices.resize(4);

    // Store unrotated diagonal point
    p2 = {x, y};

    // Compute axis-aligned rectangle
    originalVertices[0] = {p1.x, p1.y};  // First corner
    originalVertices[1] = {x, p1.y};     // Top-right
    originalVertices[2] = {x, y};        // Bottom-right
    originalVertices[3] = {p1.x, y};     // Bottom-left

    // Copy to vertices before applying rotation
    vertices = originalVertices;

    // Apply initial rotation
    rotate(0);
}

// Rotate around the center without modifying the original shape
void Rectangle::rotate(double angleChange) {
    angle += angleChange;  // Update rotation angle

    // Compute the center of the rectangle
    int cx = (originalVertices[0].x + originalVertices[2].x) / 2;
    int cy = (originalVertices[0].y + originalVertices[2].y) / 2;

    for (int i = 0; i < 4; i++) {
        // Get the original vertex relative to the center
        int relX = originalVertices[i].x - cx;
        int relY = originalVertices[i].y - cy;

        // Apply rotation matrix
        int rotatedX = static_cast<int>(relX * cos(angle) - relY * sin(angle));
        int rotatedY = static_cast<int>(relX * sin(angle) + relY * cos(angle));

        // Set rotated coordinates
        vertices[i].x = cx + rotatedX;
        vertices[i].y = cy + rotatedY;
    }
}

Rectangle::Rectangle(){ //def constructor
    p1 = {-100,-100};
    p2 = {-100, -100};
    size = 3;
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2, int size_ = 3, Color color_ = black){
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    size = size_;
    rectColor = color_;

    generateVertices(x2,y2);
}
        
void Rectangle::drawRectangle(bool isBuffer, bool isClear){

    Color colorToUse = isClear ? transparent : rectColor;
    if(!isBuffer){
        colorToUse = isClear ? canvas->getBackgroundColor() : rectColor;
    }

    for (int i = 0; i < 4; ++i) {
        int nextIndex = (i + 1) % 4; // Wrap around to the first vertex
        Line line(vertices[i].x, vertices[i].y, vertices[nextIndex].x, vertices[nextIndex].y, size, colorToUse);
        line.setCanvas(canvas);

        if (isBuffer) {
            line.drawBuffer(); // Draw to buffer
        } else {
            line.draw(); // Draw to canvas
        }
    }

}

void Rectangle::draw() {
    drawRectangle(false, false);
}
void Rectangle::clear() {
    drawRectangle(false, true);
}
void Rectangle::drawBuffer() {
    drawRectangle(true, false);
}
void Rectangle::clearBuffer() {
    drawRectangle(true, true);
}

void Rectangle::setEndingPoint(int x, int y){   //for use from Tools.cpp
    generateVertices(x,y);
}

bool Rectangle::isPointInside(int px, int py){
    bool inside = false;

    for (int i = 0, j = 4 - 1; i < 4; j = i++) {
        int xi = vertices[i].x, yi = vertices[i].y;
        int xj = vertices[j].x, yj = vertices[j].y;

        // Check if point is exactly on a horizontal edge
        if ((yi == py && yj == py) && (px >= std::min(xi, xj) && px <= std::max(xi, xj))) {
            return true;
        }

        // Ray-Casting Algorithm: Check if ray crosses an edge
        bool intersect = ((yi > py) != (yj > py)) &&
                         (px < (xj - xi) * (py - yi) / (yj - yi) + xi);

        if (intersect) inside = !inside;
    }

    return inside;
}

void Rectangle::move(int dx, int dy){
    for (int i = 0; i < 4; i++) {
        originalVertices[i].x +=dx;
        originalVertices[i].y += dy;
        vertices[i].x += dx;
        vertices[i].y += dy;
    }
}


/*############################### ELLIPSE ###############################*/


// Rotate around the center without modifying the original shape

Ellipse::Ellipse(){ //def constructor
    p1 = {-100,-100};
    p2 = {-100, -100};
    size = 3;
}

Ellipse::Ellipse(int x1, int y1, int x2, int y2, int size_ = 3, Color color_ = black){
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    size = size_;
    ellipseColor = color_;

    //generateVertices(x2,y2);
}
        
void Ellipse::drawEllipse(bool isBuffer, bool isClear) {
    Color colorToUse = isClear ? transparent : ellipseColor;
    if (!isBuffer) {
        colorToUse = isClear ? canvas->getBackgroundColor() : ellipseColor;
    }

    // Step 1: Calculate center and radii
    int cx = (p1.x + p2.x) / 2;
    int cy = (p1.y + p2.y) / 2;
    int rx = abs(p2.x - p1.x) / 2;
    int ry = abs(p2.y - p1.y) / 2;

    int x = 0, y = ry;
    long long rxSq = (long long)rx * rx;
    long long rySq = (long long)ry * ry;
    long long twoRxSq = 2 * rxSq;
    long long twoRySq = 2 * rySq;
    long long p;
    long long px = 0, py = twoRxSq * y;

    // **Region 1**
    p = round(rySq - (rxSq * ry) + (0.25 * rxSq));
    while (px < py) {
        plotEllipsePoints(cx, cy, x, y, isBuffer, colorToUse);
        x++;
        px += twoRySq;
        if (p < 0) {
            p += rySq + px;
        } else {
            y--;
            py -= twoRxSq;
            p += rySq + px - py;
        }
    }

    // **Region 2**
    p = round(rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq);
    while (y >= 0) {
        plotEllipsePoints(cx, cy, x, y, isBuffer, colorToUse);
        y--;
        py -= twoRxSq;
        if (p > 0) {
            p += rxSq - py;
        } else {
            x++;
            px += twoRySq;
            p += rxSq - py + px;
        }
    }
}


// **Helper Function to Plot Points in 4 Quadrants**
void Ellipse::plotEllipsePoints(int cx, int cy, int x, int y, bool isBuffer, Color color) {
    for(int i = x ; i< x+size ;i++){
        for(int j = y ;j<y+size;j++){
            if (isBuffer) {
                canvas->setPixelBuffer(cx +i, cy +j, color);
                canvas->setPixelBuffer(cx -i, cy +j, color);
                canvas->setPixelBuffer(cx +i, cy -j, color);
                canvas->setPixelBuffer(cx -i, cy -j, color);
            } else {
                canvas->setPixel(cx +i, cy +j, color);
                canvas->setPixel(cx -i, cy +j, color);
                canvas->setPixel(cx +i, cy -j, color);
                canvas->setPixel(cx -i, cy -j, color);
            }
        }
    }
    
}



void Ellipse::draw() {
    drawEllipse(false, false);
}
void Ellipse::clear() {
    drawEllipse(false, true);
}
void Ellipse::drawBuffer() {
    drawEllipse(true, false);
}
void Ellipse::clearBuffer() {
    drawEllipse(true, true);
}

void Ellipse::setEndingPoint(int x, int y){   //for use from Tools.cpp
    p2.x = x;
    p2.y = y;
}

bool Ellipse::isPointInside(int px, int py) {
    // Compute center of the ellipse
    int cx = (p1.x + p2.x) / 2;
    int cy = (p1.y + p2.y) / 2;

    // Compute semi-major (rx) and semi-minor (ry) axes
    int rx = abs(p2.x - p1.x) / 2;
    int ry = abs(p2.y - p1.y) / 2;

    // Avoid division by zero (in case of degenerate ellipse)
    if (rx == 0 || ry == 0) return false;

    // Apply ellipse equation
    double equation = (pow(px - cx, 2) / pow(rx, 2)) + (pow(py - cy, 2) / pow(ry, 2));

    // Check if point is inside or on the ellipse
    return equation <= 1.0;
}


void Ellipse::move(int dx, int dy){
    p1.x +=dx;
    p2.x+=dx;
    p1.y+=dy;
    p2.y+=dy;
}

void Ellipse::rotate(double angleChange){
   


    double radians = angleChange * M_PI / 180.0;

    // Compute center of the ellipse
    int cx = (p1.x + p2.x) / 2;
    int cy = (p1.y + p2.y) / 2;

    // Function to rotate a point around the center
    auto rotatePoint = [&](SDL_Point &p) {
        int xNew = cx + (p.x - cx) * cos(radians) - (p.y - cy) * sin(radians);
        int yNew = cy + (p.x - cx) * sin(radians) + (p.y - cy) * cos(radians);
        p.x = xNew;
        p.y = yNew;
    };

    // Rotate both diagonal points
    rotatePoint(p1);
    rotatePoint(p2);
}



//SPline curve

Spline::Spline(){
    startPoint = {-100,-100};
    endPoint ={-100,-100};
    controlPoint = {-100,-100};
    slope = 0;
}

Spline::Spline(SDL_Point start, SDL_Point end, SDL_Point control,float slope_, int size_=3, Color color_ = black){
    startPoint = start;
    endPoint = end;
    controlPoint = control;
    slope = slope_;
    size = size_;
    splineColor = color_;
}

void Spline::drawSpline(bool isBuffer, bool isClear){
    Color colorToUse = isClear ? transparent : splineColor;
    if (!isBuffer) {
        colorToUse = isClear ? canvas->getBackgroundColor() : splineColor;
    }

    int numSegments = 1000; // Number of segments to approximate the curve
    float t;
    SDL_Point prev = startPoint;
    
    // Compute tangent vectors
    SDL_Point tangent1 = {controlPoint.x - startPoint.x, controlPoint.y - startPoint.y};
    SDL_Point tangent2 = {static_cast<int>(slope * (endPoint.x - controlPoint.x)), endPoint.y - controlPoint.y};
    
    for (int i = 1; i <= numSegments; i++) {
        t = static_cast<float>(i) / numSegments;
        float t2 = t * t;
        float t3 = t2 * t;
        
        // Hermite basis functions
        float h1 = 2 * t3 - 3 * t2 + 1;
        float h2 = -2 * t3 + 3 * t2;
        float h3 = t3 - 2 * t2 + t;
        float h4 = t3 - t2;
        
        // Compute interpolated point
        SDL_Point cur = {
            static_cast<int>(h1 * startPoint.x + h2 * endPoint.x + h3 * tangent1.x + h4 * tangent2.x),
            static_cast<int>(h1 * startPoint.y + h2 * endPoint.y + h3 * tangent1.y + h4 * tangent2.y)
        };
        
        // Draw line segment between previous and current point
        Line segment(prev, cur,size, colorToUse);
        segment.setCanvas(canvas);
        segment.drawLine(isBuffer, isClear);
        prev = cur;
    }
}


void Spline::draw() {
    drawSpline(false, false);
}
void Spline::clear() {
    drawSpline(false, true);
}
void Spline::drawBuffer() {
    drawSpline(true, false);
}
void Spline::clearBuffer() {
    drawSpline(true, true);
}

void Spline::setControlPoint(SDL_Point control){
    controlPoint = control;
}

void Spline::setEndingPoint(SDL_Point p){
    endPoint = p;
}