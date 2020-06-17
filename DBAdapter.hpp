//  dbAdapter.hpp
//  AmiKo-wx
//
//  Created by Alex Bettarini on 16 Jun 2020
//  Copyright © 2020 Ywesee GmbH. All rights reserved.

#pragma once

#include <wx/wx.h>

class SQLiteDatabase;

class DBAdapter
{
public:
    DBAdapter();
    virtual ~DBAdapter() {}
    
    bool openDatabase(wxString dbName);
    
private:
     SQLiteDatabase *mySqliteDb;
};