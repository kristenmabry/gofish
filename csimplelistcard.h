// ============================================================================
// File: csimplelist.h (Spring 2019)
// ============================================================================
// Header file for the CSimpleListCard class.
// ============================================================================

#ifndef CSIMPLE_CARD_LIST_HEADER
#define CSIMPLE_CARD_LIST_HEADER

// enable this #define symbol to see debug output
#define DEBUG_LIST

#include "ccard.h"

// type definitions
typedef CCard CardListType;
enum    CLStatus  { CL_FULL
                  , CL_EMPTY
                  , CL_ERROR
                  , CL_SUCCESS
                  , CL_INVALID_INDEX
                  , CL_DUPLICATE
                  , CL_NOT_EXIST
                };

// constants
const   int     CARD_MAX_ITEMS = 52;
const   int     CARDMOVE_TO_BACK = 0;
const   int     CARDMOVE_TO_FRONT  = 1;

class   CSimpleListCard
{
public:
    // constructor and destructor
    CSimpleListCard() : m_numItems(0) {}
    ~CSimpleListCard()  { DestroyList(); }

    // member functions
    CLStatus     DestroyList()
                        { m_numItems = 0; return CL_SUCCESS; }
    void        DispRetVal(const char*  szMessage, CLStatus  value) const;
    CLStatus     GetItem(int  index, CardListType  &item) const;
    int         GetNumItems() const { return m_numItems; }
    CLStatus     Insert(int  index, const CardListType  &newItem);
    bool        IsEmpty() const { return (0 == m_numItems); }
    bool        IsFull() const { return (CARD_MAX_ITEMS == m_numItems); }
    CLStatus     Remove(int  index);

private:
    // data members
    int         m_numItems;
    CardListType    m_items[CARD_MAX_ITEMS];

    // member functions
    int         MoveItems(int  index, int  direction);
};

#endif  // CSIMPLE_CARD_LIST_HEADER
