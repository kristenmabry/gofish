// ============================================================================
// File: csimplelist.cpp (Spring 2019)
// ============================================================================
// This is the implementation file for the list ADT "CSimpleList".  This
// particular implementation uses an array to store a list of type
// "ListType" items.
// ============================================================================

#include    <iostream>
using namespace std;
#include    "csimplelist.h"



// ==== CSimpleList::DispRetVal ===============================================
//
// This function is used for debugging purposes.  If a value of type
// ListReturnCode needs to be displayed to stdout, you can call this function.
//
// Input:
//      szMessage   -- a null-terminated string to display to stdout (e.g., the
//                     name of the function calling this function)
//
//      value       -- the list error code to display
//
// Output:
//      nothing
//
// ============================================================================

void    CSimpleList::DispRetVal(const char*  szMessage, LStatus  value) const
{
    #ifdef  DEBUG_LIST
    cerr << szMessage << ": ";
    switch (value)
        {
        case   L_FULL:
            cerr << "L_FULL\n";
            break;

        case   L_EMPTY:
            cerr << "L_EMPTY\n";
            break;

        case   L_ERROR:
            cerr << "L_ERROR\n";
            break;

        case   L_SUCCESS:
            cerr << "L_SUCCESS\n";
            break;

        case   L_INVALID_INDEX:
            cerr << "L_INVALID_INDEX\n";
            break;

        default:
            cerr << "Unrecognized error code\n";
            break;
        }
    #endif  // DEBUG_LIST

}  // end of "CSimpleList::DispRetVal"



// ==== CSimpleList::GetItem ==================================================
//
// This function fetches the value of a target item from the list.
//
// Input:
//      index   -- the index location for the target item (zero-based).
//
//      item    -- a reference to a ListType object; this argument will
//                 contain the desired item after the function completes
//                 (assuming all goes well)
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an error code is
//      returned.
//
// ============================================================================

LStatus  CSimpleList::GetItem(int  index, ListType  &item) const
{
    // if the list is empty, return an error cocde
    if (true == IsEmpty())
        {
        DispRetVal("GetItem", L_EMPTY);
        return L_EMPTY;
        }

    // if the target location is not within appropriate list boundaries (i.e.,
    // 0 to m_numItems-1), return an error code
    if ((index < 0)  ||  (index > (m_numItems - 1)))
        {
        DispRetVal("GetItem", L_INVALID_INDEX);
        return L_INVALID_INDEX;
        }

    // initialize the reference parameter and return
    item = m_items[index];
    return L_SUCCESS;

}  // end of "CSimpleList::GetItem"



// ==== CSimpleList::Insert ===================================================
//
// This function inserts an item into the list.  If the new item is appended to
// the end of the list, the position of any other list item is unaffected.  If
// the new item is inserted before the last element, all elements after the
// target location are moved towards the back of the array one position to make
// room for the new element.
//
// Input:
//      index       -- the target index location for the new item (zero-based).
//
//      newItem     -- a const reference to the new item to insert into the list
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================

LStatus  CSimpleList::Insert(int  index, const ListType  &newItem)
{
    // if the list is already full, return an error code
    if (true == IsFull())
        {
        DispRetVal("Insert", L_FULL);
        return L_FULL;
        }

    // if the target location is not within appropriate list boundaries (i.e.,
    // 0 to m_numItems), return an error code
    if  ((index < 0)
    ||  (index > m_numItems)
    ||  (index > (MAX_ITEMS - 1)))
        {
        DispRetVal("Insert", L_INVALID_INDEX);
        return L_INVALID_INDEX;
        }

    // if the new item is to be inserted before the end of the list, any items
    // after the new item's location are "pushed" one location towards the back
    // of the list to make room for the new item
    if (index < m_numItems)
        {
        MoveItems(index, MOVE_TO_BACK);
        }

    // save the new item
    m_items[index] = newItem;
    ++m_numItems;

    return L_SUCCESS;

}  // end of "CSimpleList::Insert"



// ==== CSimpleList::MoveItems ================================================
//
// This function moves the elements of the list forward or backward one
// position.  If an item is inserted before the last element in the list, the
// "trailing" elements must be moved towards the back of the array one position
// in order to make room for the new list item.  Similarly, if a list item is
// removed from the middle of the list, the trailing elements must be moved
// towards the front of the array one position to fill in the gap left by the
// deleted item.
//
// The caller of this function only needs to indicate the target location where
// an element is being inserted or removed, and the "direction" to move the
// trailing list elements (i.e., towards the front or back of the array).
//
// NOTE: This function assumes that the caller has already verified the
// validity of the index parameter.
//
// Input:
//      index           -- the index location for the target item (zero-based).
//
//      direction       -- the direction to move the trailing (i.e., those
//                         further down the list) list elements; this parameter
//                         should contain the value MOVE_TO_BACK if an item is
//                         being inserted into the list, or MOVE_TO_FRONT if 
//                         the item at index is being removed from the
//                         list.
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an errorcode is
//      returned.
//
// ============================================================================

int     CSimpleList::MoveItems(int  index, int  direction)
{
    int         destIndex;
    int         update;
    int         sourceIndex;
    int         numItemsMoved = 0;

    // initialize the source and destination index values
    if (MOVE_TO_BACK == direction)
        {
        sourceIndex = m_numItems - 1;
        destIndex = m_numItems;
        update = -1;     // move from higher to lower addresses
        }
    else    // MOVE_TO_FRONT
        {
        sourceIndex = index + 1;
        destIndex = index;
        update = 1;      // move from lower to higher addresses
        }

    // loop and "move" elements
    bool        bContinueLoop = true;
    do  {
        m_items[destIndex] = m_items[sourceIndex];
        destIndex += update;
        sourceIndex += update;
        ++numItemsMoved;

        if (MOVE_TO_BACK == direction)
            {
            if ((sourceIndex < index)  ||  (destIndex < 1))
                {
                bContinueLoop = false;
                }
            }
        else    // MOVE_TO_FRONT
            {
            if (sourceIndex >= m_numItems)
                {
                bContinueLoop = false;
                }
            }

        }  while (true == bContinueLoop);

    return numItemsMoved;

}  // end of "CSimpleList::MoveItems"



// ==== CSimpleList::Remove ===================================================
//
// This function removes an item from the list.  If the target item is at the
// end of the list, the position of any other list item is unaffected.  If the
// target item is before the end of the list, all elements after the target
// location are moved towards the front of the array one position to fill in
// the gap left behind by the deleted item.
//
// Input:
//      index       -- the index location for the target item (zero-based).
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================

LStatus  CSimpleList::Remove(int  index)
{
    // if the list is empty, return an error cocde
    if (true == IsEmpty())
        {
        DispRetVal("Remove", L_EMPTY);
        return L_EMPTY;
        }

    // if the target location is not within appropriate list boundaries (i.e.,
    // 0 to m_numItems-1), return an error code
    if ((index < 0)  ||  (index > (m_numItems - 1)))
        {
        DispRetVal("Remove", L_INVALID_INDEX);
        return L_INVALID_INDEX;
        }

    // if the target item is before the last item in the list, we need to
    // compact the list (i.e, all trailing items are shifted one location
    // towards the front of the list to fill the newly-created gap).
    if (index < (m_numItems - 1))
        {
        MoveItems(index, MOVE_TO_FRONT);
        }

    // adjust the counter
    --m_numItems;
    return L_SUCCESS;

}  // end of "CSimpleList::Remove"



