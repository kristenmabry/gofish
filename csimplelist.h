// ============================================================================
// File: csimplelist.h (Spring 2019)
// ============================================================================
// Header file for the CSimpleList class.
// ============================================================================

#ifndef CSIMPLE_LIST_HEADER
#define CSIMPLE_LIST_HEADER

// enable this #define symbol to see debug output
#define DEBUG_LIST

// type definitions
typedef int     ListType;
enum    LStatus  { L_FULL
                  , L_EMPTY
                  , L_ERROR
                  , L_SUCCESS
                  , L_INVALID_INDEX
                  , L_DUPLICATE
                  , L_NOT_EXIST
                };

// constants
const   int     MAX_ITEMS = 14;
const   int     MOVE_TO_BACK = 0;
const   int     MOVE_TO_FRONT  = 1;

class   CSimpleList
{
public:
    // constructor and destructor
    CSimpleList() : m_numItems(0) {}
    ~CSimpleList()  { DestroyList(); }

    // member functions
    LStatus     DestroyList()
                        { m_numItems = 0; return L_SUCCESS; }
    void        DispRetVal(const char*  szMessage, LStatus  value) const;
    LStatus     GetItem(int  index, ListType  &item) const;
    int         GetNumItems() const { return m_numItems; }
    LStatus     Insert(int  index, const ListType  &newItem);
    bool        IsEmpty() const { return (0 == m_numItems); }
    bool        IsFull() const { return (MAX_ITEMS == m_numItems); }
    LStatus     Remove(int  index);

private:
    // data members
    int         m_numItems;
    ListType    m_items[MAX_ITEMS];

    // member functions
    int         MoveItems(int  index, int  direction);
};

#endif  // CSIMPLE_LIST_HEADER
