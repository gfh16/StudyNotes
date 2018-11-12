///////////////////////////////////////////////////////////////////////////////
///// The Usage of TTree
//////////////////////////////////////////////////////////////////////////////

**** What is TTree ?  Why we use tree ?
1. Each object is not written individually, will produce a much smaller file than if the objects were written individually.
2. Reduces the header of each object
3. To optimize the data access

**** Compare with without tree *****
//  If we had saved the million events without a TTree we would have to:
    read each event in its entirety into memory
    extract the Px and Py from the event
    compute the sum of the squares
    fill a histogram
    
// really do not need to read the entire event, every time.We just need Px, and Py    
   Use a tree with one branch containing Px, another containing Py

