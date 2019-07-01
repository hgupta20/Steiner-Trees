# Steiner-Trees
## Implementing the GUI for Steiner Trees

A graphical presentation of points with which we can interact to create a [Steiner Tree](http://csunplugged.org/wp-content/uploads/2014/12/unplugged-15-steiner_trees_0.pdf).  Being able to solve problems of this type are useful, for example, if you want to connect locations with roads, or connect electrical components on an electronic chip layout.  It turns out that sometimes the shortest path can be found when additional points are introduced.  All interaction with your program must be through the graphics window.

The program will have a data file with various sets of points, along with reasonable known solution lengths for each set.  It will plot the starting points on the screen as black points.  The user can:
Press a button to add Steiner points to the graph, which will show up as blue points. 
Press a button to draw lines between points (either blue or black or mixed).  The program keeps track of the sum of all the line lengths.  The user is responsible for keeping track of when all points are connected.
A message indicates whether the total length is close to the known solution or not.

For one set of data with three points the program starts as:
![1](https://github.com/hgupta20/Steiner-Trees/blob/master/images/1.png)
