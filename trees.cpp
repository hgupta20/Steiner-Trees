/*
 *  System: Windows 10,Dev-C++
 *  Author: Harsh Devprakash Gupta
 *
 */

#include <iostream>
#include "gobjects.h"     // for all graphics objects
#include "gevents.h"      // for mouse events
#include <fstream>        // For file input
#include <cmath>          // For math functions
#include <ctime>          // For Time functions
using namespace std;

// Global constants
const int PointRadius = 7;   // Constant Radius for points.

// Create a graphics window, which will be used to draw graphical shapes.
// This can be a global variable, but you may not have any other global variables.
GWindow graphicsWindow;

// Display name and program information
void displayIdentifyingInformation()
{
    
    cout << "Author: Harsh Devprakash Gupta" << endl;
    cout << "System: C++ in Dev C++" << endl;
    cout<< endl;
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------------------------------------------------------------------
class MyButton
{
    public:
        // Constructor
        MyButton(){}; // Default Constructor.
        MyButton(string color, int x, int y, int width, int height, string label )
        {
            this->color = color;this->label = label;
            this->x= x; this->y = y; this->width = width; this->height = height;

            theRectangle = new GRect(x, y, width, height);
            theRectangle->setColor( color);
            theRectangle->setFilled( true);
            graphicsWindow.add( theRectangle);

            theLabel = new GLabel();
            theLabel->setText(label);
            // Find size of text, to determine placement relative to enclosing rectangle
            int xOffset = (width  - theLabel->getBounds().getWidth()) / 2;
            int yOffset = (height - theLabel->getBounds().getHeight()) + 5;
            theLabel->setLocation( x + xOffset, y + yOffset);
            graphicsWindow.add( theLabel);
        }
        // Accessor (get) member functions
        string getColor() { return color; }
        string getLabel() { return label; }
        int getX() { return x; }
        int getY() { return y; }
        int getWidth() { return width; }
        int getHeight() { return height; }

        // Mutator (set) member functions
        void setX( int theRow) { x = theRow; }
        void setY( int theCol) { y = theCol; }
        void setWidth( int theWidth) { width = theWidth; }
        void setHeight( int theHeight) { height = theHeight; }
        void setColor( string theColor) { color = theColor; }
        void setLabel( string theLabel) { label = theLabel; }

        // Functions for Buttons in the range of MouseX and MouseY
        bool buttonClicked(int mouseX, int mouseY){
            return theRectangle->contains( mouseX, mouseY);

        }




    private:
        string color;
        string label;
        int x,y,width,height;
        GRect *theRectangle;
        GLabel *theLabel;


}; // end class MyButton

//-------------------------------------------------------------------------------------
class MyPoint
{
    public:
        // Constructor
    MyPoint(){};
        MyPoint(string color, int x, int y, int radiusW, int radiusH, bool visibility= true)
        {
            this->color = color;
            this->x= x; this->y = y; this->radiusW = radiusW; this->radiusH = radiusH;


            theCircle = new GOval(x, y, radiusW, radiusH);
            theCircle->setColor( color);
            theCircle->setFilled( true);
            if (visibility){
                graphicsWindow.add( theCircle);
            }

        }
        // Accessor (get) member functions
        string getColor() { return color; }
        int getRadiusH() { return radiusH; }
        int getX() { return x; }
        int getY() { return y; }
        int getRadiusW() { return radiusW; }



        // Mutator (set) member functions
        void setX( int theX)
        {
            x = theX;
            theCircle->setBounds(x, this->y, this->radiusW, this->radiusH);
        }
        void setY( int theY)
        {
            y = theY;
            theCircle->setBounds(this->x, y, this->radiusW, this->radiusH);
        }
        void setRadiusH( int theRadiusH) { radiusH = theRadiusH; }
        void setRadiusW( int theRadiusW) { radiusW = theRadiusW; }
        void setColor( string theColor) { color = theColor; }

        // Functions for diffrent operations
        bool pointClicked(int mouseX, int mouseY){
            return theCircle->contains( mouseX, mouseY);

        }
        void makeitVisible(){
            visibility=true;
            graphicsWindow.add( theCircle);
        }

    private:
        string color;
        int x,y,radiusW,radiusH;
        GOval *theCircle;
        bool visibility;


}; // end class MyPoint
//-------------------------------------------------------------------------------------------------------
// Read in the sets of points information from the data file
// We make the pointsArray Vector a reference parameter so that read-in values are
// reflected back to the caller.
void readInputFile( Vector<MyPoint*> &pointsArray, int &idealScore)
{

    ifstream inputFileStream;  // declare the input file stream

    // Open input file and verify.
    inputFileStream.open("data.txt");
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file data.txt.  Exiting..." << endl;
        exit( -1);
    }

    // Read sets of data from input file.  Each read operation reads the next set of data.
    // The first line in the input file indicates which set to use.
    int whichSetToUse;
    inputFileStream >> whichSetToUse;

    int howManyPoints;    // How many points are in the set of points

    int x, y;             // Store individual point x,y values from input file
    // Reserve some reasonable number of total points for the vector, so that
    //pointsArray.ensureCapacity( 30);

    // Read in and discard some number of sets of points before we get the real set we will be using
    for( int i = 0; i < whichSetToUse-1; i++) {
        inputFileStream >> howManyPoints >> idealScore;

        for( int j = 0; j < howManyPoints; j++) {
            inputFileStream >> x >> y;    // Read in the points
        }
    }

    inputFileStream >> howManyPoints >> idealScore;


    // Read in and store the points information
    for( int i = 0; i < howManyPoints; i++) {
        inputFileStream >> x >> y;    // Read in the points

        cout << "Point " << i << " is at " << x << "," << y << endl;
        pointsArray.push_back(new MyPoint( "black", x,y, PointRadius*2, PointRadius*2));
     }
}//end readInputFile()


//------------------------------------------------------------------------------------------

int closestX(int mouseXPosition, int mouseYPosition, int numberOfPoints, Vector<MyPoint*> &pointsArray){

    int difference1= abs(mouseXPosition-pointsArray[0]->getX());
    int difference2= abs(mouseYPosition-pointsArray[0]->getY());
    int length= sqrt((difference1*difference1) + (difference2*difference2));
    int xPosition=0;

    for( int i = 0; i < numberOfPoints; i++) {
       int tempdifference1= abs(mouseXPosition-pointsArray[i]->getX());
       int tempdifference2= abs(mouseYPosition-pointsArray[i]->getY());
       int templength= sqrt((tempdifference1*tempdifference1) + (tempdifference2*tempdifference2));
       if (length>=templength){
           length=templength;
           xPosition=pointsArray[i]->getX() + 7;
       }

    }
    return xPosition;

}
//--------------------------------------------------------------------------------------------------------
int closestY(int mouseXPosition, int mouseYPosition, int numberOfPoints, Vector<MyPoint*> &pointsArray){

    int difference1= abs(mouseXPosition-pointsArray[0]->getX());
    int difference2= abs(mouseYPosition-pointsArray[0]->getY());
    int length= sqrt((difference1*difference1) + (difference2*difference2));
    int yPosition=0;

    for( int i = 0; i < numberOfPoints; i++) {
       int tempdifference1= abs(mouseXPosition-pointsArray[i]->getX());
       int tempdifference2= abs(mouseYPosition-pointsArray[i]->getY());
       int templength= sqrt((tempdifference1*tempdifference1) + (tempdifference2*tempdifference2));
       if (length>=templength){
           length=templength;
           yPosition=pointsArray[i]->getY()+7;
       }

    }
    return yPosition;

}
//--------------------------------------------------------------------------------------------------------
void calculatetheLength(Vector <GLine*>lineVector, int &totalLength){

    totalLength =0;
    GPoint startpoint, endpoint;
    for( int i = 0; i < lineVector.size()-1; i++) {
        startpoint = lineVector[i]->getStartPoint();

        int x1 = startpoint.getX();
        int y1 = startpoint.getY();

        endpoint = lineVector[i]->getEndPoint();
        int x2 = endpoint.getX();
        int y2 = endpoint.getY();

        totalLength= totalLength + (sqrt(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)))) ;

    }

}
//--------------------------------------------------------------------------------------------------------

int main()
{
    graphicsWindow.setCanvasSize( 400, 400);   // Set the size-
    graphicsWindow.setWindowTitle("  hgupta20  QtCreator Program 6");

    Vector<MyPoint*> pointsArray(0);    // Store all points that are created.
    Vector<GLine*> linesVector(0);      // Store all lines that are created.

    int idealScore = 0;                 // Precomputed ideal score for each puzzle
    int numOfPoints = 0;                // Index of Points Array
    int closestXPosition =0;            // To store the closest point from mouse x position
    int closestYPosition =0;            // To store the closest point from mouse y position
    int totalLength=0;                  // // To store the total Length



    // Get the set of data to use from the input file
    readInputFile( pointsArray, idealScore);


    // Create the Control and message components.

    GLabel *messagesLabel = new GLabel();
    messagesLabel->setText("Find the minimal spanning tree, using additional points.");
    messagesLabel->setLocation( 30,20);
    graphicsWindow.add( messagesLabel);


    MyButton *addPointsButton= new MyButton("green",10,350, 70,30,"Add Points");
    MyButton *drawLinesButton= new MyButton("lightgray",90,350, 70,30,"Draw Lines");
    MyButton *exitButton= new MyButton("red",250,350, 50,30,"Exit");

    GLabel *LengthLabel = new GLabel();
    LengthLabel->setText("Length: ");
    LengthLabel->setLocation( 320,360);
    graphicsWindow.add( LengthLabel);

    GLabel *LengthNumber = new GLabel();
    LengthNumber->setText(to_string(totalLength));
    LengthNumber->setLocation( 320,380);
    graphicsWindow.add( LengthNumber);

    // Make the graphics window have focus, since all interaction will be through the window
    graphicsWindow.requestFocus();

    // Set values to use for keeping track of program modes
    const int Default = 0;
    const int DrawPoints = 1;
    const int DrawLines = 2;
    int programMode = Default;        // Modes are Default, DrawPoints, DrawLines. Start in Default mode
                                      // Change to the other modes when those buttons are pressed.
    bool buttonWasPressed = false;    // Set to false when a button is pressed.  Used to avoid drawing on buttons
                                      // immediately when they are pressed.

    int mouseX = -1;                    // Will store mouse position
    int mouseY = -1;

    char message[ 81];                  // For the Messages on the window
    bool mouseWithinButtons=false;      // For checking the values
    bool mouseNotWithinButtons=false;


    linesVector.push_back( new GLine(0,0,0,0));  // Line to be drawn on the screen.  It starts out as a single unseen point.
    int index = linesVector.size()-1;
    linesVector[index]->setLineWidth(2);
    graphicsWindow.add(linesVector[index]);

    pointsArray.push_back(new MyPoint("blue",0,0, PointRadius*2, PointRadius*2, false));
    numOfPoints= pointsArray.size()-1;


    GMouseEvent e;

    // Stores the mouse event each time through the event loop
    int counter = 0;    // Used to display debugging information, to help understand how the event loop works.

    // Main event loop, to handle the different mouse events.
    while (true) {
        calculatetheLength(linesVector,totalLength);
        LengthNumber->setText(to_string(totalLength));

        // Wait for a mouse event, then get the x,y coordinates
        e = waitForEvent(MOUSE_EVENT);
        // Get the current mouse x,y location
        mouseX = e.getX();
        mouseY = e.getY();
        counter++;    // Iterations counter

        index= linesVector.size()-1;
        numOfPoints= pointsArray.size()-1;

        if (exitButton->buttonClicked( mouseX, mouseY) || addPointsButton->buttonClicked( mouseX, mouseY) ||drawLinesButton->buttonClicked( mouseX, mouseY) ){
                    mouseWithinButtons= true;
                    mouseNotWithinButtons= !mouseWithinButtons;
                }
        else if (!exitButton->buttonClicked( mouseX, mouseY) && !addPointsButton->buttonClicked( mouseX, mouseY) && !drawLinesButton->buttonClicked( mouseX, mouseY)){
                    mouseNotWithinButtons= true;
                    mouseWithinButtons= !mouseNotWithinButtons;
        }

        if (e.getEventType() == MOUSE_PRESSED) {

                    sprintf( message,"Mouse pressed at %d,%d", mouseX, mouseY);  // print into a string
                    messagesLabel->setLabel(message);

                    // See if Exit button was clicked by seeing if mouse press location is inside the rectangle
                    if( exitButton->buttonClicked( mouseX, mouseY)) {
                        messagesLabel->setLabel("Exiting...");
                        break;
                    }
                    else if( addPointsButton->buttonClicked( mouseX, mouseY)) {
                        programMode=DrawPoints;
                        buttonWasPressed=true;
                        messagesLabel->setLabel("Click to add points.");


                    }
                    else if( drawLinesButton->buttonClicked( mouseX, mouseY)) {
                        buttonWasPressed=true;
                        programMode=DrawLines;
                        messagesLabel->setLabel("Click and Drag between two points to add lines. ");

                    }
                    else if (programMode==DrawLines){

                        linesVector[index]->setStartPoint( mouseX, mouseY);
                        linesVector[index]->setEndPoint( mouseX, mouseY);
                        closestXPosition=closestX(mouseX, mouseY, numOfPoints, pointsArray);  // Using the closest point
                        closestYPosition= closestY(mouseX, mouseY, numOfPoints, pointsArray); // Using the closest point
                        linesVector[index]->setStartPoint( closestXPosition, closestYPosition);
                        sprintf( message,"Setting line starting point %d, %d", mouseX, mouseY);
                        messagesLabel->setLabel(message);

                     }
                    else if (programMode==DrawPoints ){

                        pointsArray[numOfPoints]->setX(mouseX-7);
                        pointsArray[numOfPoints]->setY(mouseY-7);
                        pointsArray[numOfPoints]->makeitVisible();
                        sprintf( message,"Creating the point at  %d, %d", mouseX-7, mouseY-7);
                        messagesLabel->setLabel(message);
                    }
        }
        else if( e.getEventType() == MOUSE_RELEASED) {

                    if (mouseNotWithinButtons){
                        sprintf( message,"Mouse released at %d,%d", mouseX, mouseY);  // print into a string
                        messagesLabel->setLabel(message);
                        cout << "Mouse was released at : " << mouseX << "," << mouseY << endl;

                        if (programMode==DrawLines ){

                            if (mouseNotWithinButtons){

                                closestXPosition=closestX(mouseX, mouseY, numOfPoints, pointsArray);
                                closestYPosition= closestY(mouseX, mouseY, numOfPoints, pointsArray);

                                linesVector[index]->setEndPoint( closestXPosition, closestYPosition);
                                linesVector.push_back(new GLine(0,0,0,0));
                                ++index;
                                linesVector[index]->setLineWidth(2);
                                graphicsWindow.add(linesVector[index]);

                                calculatetheLength(linesVector,totalLength);


                                if (totalLength<= idealScore*1.05){
                                    sprintf( message,"Great %d is less than or close to %d", totalLength, idealScore);
                                    messagesLabel->setLabel(message);

                                }
                                else{
                                    sprintf( message,"Sorry %d is larger than %d, Please try Again", totalLength, idealScore);
                                    messagesLabel->setLabel(message);
                                }
                            }


                        }
                        else if (programMode == DrawPoints){
                            if (!mouseWithinButtons){
                                pointsArray[numOfPoints]->setX(mouseX-7); // Subtracting 7 to make point on the cursor.
                                pointsArray[numOfPoints]->setY(mouseY-7);
                                pointsArray.push_back(new MyPoint("blue",0,0, PointRadius*2, PointRadius*2, false));
                                ++numOfPoints;
                            }
                        }
                    }
        }
        else if(e.getEventType() == MOUSE_DRAGGED) { // Mouse Dragged Event.

                    if  (mouseNotWithinButtons){ // Switching the bool values
                        cout << "Mouse dragged to " << mouseX << "," << mouseY << endl;

                        if (programMode==DrawLines){
                            if (!mouseWithinButtons){
                                linesVector[index]->setEndPoint(mouseX, mouseY);
                            }

                        }
                        else if (programMode== DrawPoints){
                            if (!mouseWithinButtons){
                                pointsArray[numOfPoints]->setX(mouseX-7);
                                pointsArray[numOfPoints]->setY(mouseY-7);
                            }
                        }
                    }
            }



    }//end while( true)

    // Close the windows, first the graphics window
    graphicsWindow.requestFocus();
    graphicsWindow.close();
    exitGraphics();

    return 0;
}
