# Steiner-Trees
## Implementing the GUI for Steiner Trees using QT Creator

A graphical presentation of points with which we can interact to create a [Steiner Tree](http://csunplugged.org/wp-content/uploads/2014/12/unplugged-15-steiner_trees_0.pdf).  Being able to solve problems of this type are useful, for example, if you want to connect locations with roads, or connect electrical components on an electronic chip layout.  It turns out that sometimes the shortest path can be found when additional points are introduced.  All interaction with your program must be through the graphics window.

The program will have a data file with various sets of points, along with reasonable known solution lengths for each set.  It will plot the starting points on the screen as black points.  The user can:
Press a button to add Steiner points to the graph, which will show up as blue points. 
Press a button to draw lines between points (either blue or black or mixed).  The program keeps track of the sum of all the line lengths.  The user is responsible for keeping track of when all points are connected.
A message indicates whether the total length is close to the known solution or not.

For one set of data with three points the program starts as:

![1](https://github.com/hgupta20/Steiner-Trees/blob/master/images/1.png)

The first approach might be to click on the Draw Lines button and draw lines between the three points, giving:

![2](https://github.com/hgupta20/Steiner-Trees/blob/master/images/2.png)

The total length falls short of a more optimal solution.  Exiting the program and restarting allows us to try again.  We can do better if we first select the Add Points button, add the (blue) point in the middle of the other three points, and then select the Draw Lines button and connect them all together, giving:

![3](https://github.com/hgupta20/Steiner-Trees/blob/master/images/3.png)

Enclosed is a sample data file (data.txt) and Mac QtCreator project or PC QtCreator project (both including the data file) to get you started, in recognition of the fact that time is short. At left below is the contents of the data file.  The data file has 8 different configurations.  The number on the first line of the data file is the number of which puzzle (1..8) will be used. To switch to a different puzzle you will need to change that number, and save the file and re-run your program. At right below are all the corresponding configurations on the 400 x 400 pixel graphics window. The provided sample code already reads in the datafile for you. 

![4](https://github.com/hgupta20/Steiner-Trees/blob/master/images/4.png)

Starting the sample QtCreator project code (linked above) gives you the window shown at left below.  Clicking in the window displays messages both in the top of the window as well as in the console.  Clicking and dragging results in creating a line, shown at right below.

![5](https://github.com/hgupta20/Steiner-Trees/blob/master/images/5.png)
