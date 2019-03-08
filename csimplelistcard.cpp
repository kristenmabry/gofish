// ============================================================================
// File: csimplelist.cpp (Spring 2019)
// ============================================================================
// This is the implementation file for the list ADT "CSimpleListCard".  This
// particular implementation uses an array to store a list of type
// "CardListType" items.
// ============================================================================

#include    <iostream>
using namespace std;
#include    "csimplelistcard.h"
#include    "ccard.h"



// ==== CSimpleListCard::DispRetVal ===============================================
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

void    CSimpleListCard::DispRetVal(const char*  szMessage, CLStatus  value) const
{
    #ifdef  DEBUG_LIST
    cerr << szMessage << ": ";
    switch (value)
        {
        case   CL_FULL:
            cerr << "CL_FULL\n";
            break;

        case   CL_EMPTY:
            cerr << "CL_EMPTY\n";
            break;

        case   CL_ERROR:
            cerr << "CL_ERROR\n";
            break;

        case   CL_SUCCESS:
            cerr << "CL_SUCCESS\n";
            break;

        case   CL_INVALID_INDEX:
            cerr << "CL_INVALID_INDEX\n";
            break;

        default:
            cerr << "Unrecognized error code\n";
            break;
        }
    #endif  // DEBUG_LIST

}  // end of "CSimpleListCard::DispRetVal"



// ==== CSimpleListCard::GetItem ==================================================
//
// This function fetches the value of a target item from the list.
//
// Input:
//      index   -- the index location for the target item (zero-based).
//
//      item    -- a reference to a CardListType object; this argument will
//                 contain the desired item after the function completes
//                 (assuming all goes well)
//
// Output:
//      If all goes well, a value of CL_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an error code is
//      returned.
//
// ============================================================================

CLStatus  CSimpleListCard::GetItem(int  index, CardListType  &item) const
{
    // if the list is empty, return an error cocde
    if (true == IsEmpty())
        {
        DispRetVal("GetItem", CL_EMPTY);
        return CL_EMPTY;
        }

    // if the target location is not within appropriate list boundaries (i.e.,
    // 0 to m_numItems-1), return an error code
    if ((index < 0)  ||  (index > (m_numItems - 1)))
        {
        DispRetVal("GetItem", CL_INVALID_INDEX);
        return CL_INVALID_INDEX;
        }

    // initialize the reference parameter and return
    item = m_items[index];
    return CL_SUCCESS;

}  // end of "CSimpleListCard::GetItem"



// ==== CSimpleListCard::Insert ===================================================
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
//      If all goes well, a value of CL_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================

CLStatus  CSimpleListCard::Insert(int  index, const CardListType  &newItem)
{
    // if the list is already full, return an error code
    if (true == IsFull())
        {
        DispRetVal("Insert", CL_FULL);
        return CL_FULL;
        }

    // if the target location is not within appropriate list boundaries (i.e.,
    // 0 to m_numItems), return an error code
    if  ((index < 0)
    ||  (index > m_numItems)
    ||  (index > (CARD_MAX_ITEMS - 1)))
        {
        DispRetVal("Insert", CL_INVALID_INDEX);
        return CL_INVALID_INDEX;
        }

    // if the new item is to be inserted before the end of the list, any items
    // after the new item's location are "pushed" one location towards the back
    // of the list to make room for the new item
    if (index < m_numItems)
        {
        MoveItems(index, CARDMOVE_TO_BACK);
        }

    // save the new item
    m_items[index] = newItem;
    ++m_numItems;

    return CL_SUCCESS;

}  // end of "CSimpleListCard::Insert"



// ==== CSimpleListCard::MoveItems ================================================
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
//                         should contain the value CARDMOVE_TO_BACK if an item is
//                         being inserted into the list, or CARDMOVE_TO_FRONT if 
//                         the item at index is being removed from the
//                         list.
//
// Output:
//      If all goes well, a value of CL_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an errorcode is
//      returned.
//
// ============================================================================

int     CSimpleListCard::MoveItems(int  index, int  direction)
{
    int         destIndex;
    int         update;
    int         sourceIndex;
    int         numItemsMoved = 0;

    // initialize the source and destination index values
    if (CARDMOVE_TO_BACK == direction)
        {
        sourceIndex = m_numItems - 1;
        destIndex = m_numItems;
        update = -1;     // move from higher to lower addresses
        }
    else    // CARDMOVE_TO_FRONT
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

        if (CARDMOVE_TO_BACK == direction)
            {
            if ((sourceIndex < index)  ||  (destIndex < 1))
                {
                bContinueLoop = false;
                }
            }
        else    // CARDMOVE_TO_FRONT
            {
            if (sourceIndex >= m_numItems)
                {
                bContinueLoop = false;
                }
            }

        }  while (true == bContinueLoop);

    return numItemsMoved;

}  // end of "CSimpleListCard::MoveItems"



// ==== CSimpleListCard::Remove ===================================================
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
//      If all goes well, a value of CL_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================

CLStatus  CSimpleListCard::Remove(int  index)
{
    // if the list is empty, return an error cocde
    if (true == IsEmpty())
        {
        DispRetVal("Remove", CL_EMPTY);
        return CL_EMPTY;
        }

    // if the target location is not within appropriate list boundaries (i.e.,
    // 0 to m_numItems-1), return an error code
    if ((index < 0)  ||  (index > (m_numItems - 1)))
        {
        DispRetVal("Remove", CL_INVALID_INDEX);
        return CL_INVALID_INDEX;
        }

    // if the target item is before the last item in the list, we need to
    // compact the list (i.e, all trailing items are shifted one location
    // towards the front of the list to fill the newly-created gap).
    if (index < (m_numItems - 1))
        {
        MoveItems(index, CARDMOVE_TO_FRONT);
        }

    // adjust the counter
    --m_numItems;
    return CL_SUCCESS;

}  // end of "CSimpleListCard::Remove"



