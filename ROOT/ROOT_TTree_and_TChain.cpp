///////////////////////////////////////////////////////////////////////////////
///// The Usage of TTree
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//________________________________________________________________
//**** Show an Entry with TTree::Show
//**** For example to look at the 10th entry in the staff.root tree:
 root[] TFile f("staff.root")
 root[] T->Show(10)
 ======> EVENT:10
 Category        = 361
 Flag            = 15
 Age             = 51
 Service         = 29
 Children        = 0
 Grade           = 7
 Step            = 13
 Hrweek          = 40
 Cost            = 7599
 Division        = PS
 Nation          = FR
 
 //_________________________________________________________________________
 //***** Scan a Variable the Tree with TTree::Scan
 root[] T->Scan("Cost:Age:Children")
************************************************
*    Row   *      Cost *       Age *  Children *
************************************************
*        0 *     11975 *        58 *         0 *
*        1 *     10228 *        63 *         0 *
*        2 *     10730 *        56 *         2 *
*        3 *      9311 *        61 *         0 *
*        4 *      9966 *        52 *         2 *
*        5 *      7599 *        60 *         0 *
*        6 *      9868 *        53 *         1 *
*        7 *      8012 *        60 *         1 *
...
 
