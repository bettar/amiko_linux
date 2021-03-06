//  FullTextEntry.hpp
//  AmiKo-wx
//
//  Created by Alex Bettarini on 3 Jul 2020
//  Copyright © 2020 Ywesee GmbH. All rights reserved.

#pragma once

#include <set>
#include <map>
#include <wx/wx.h>

class FullTextEntry
{
public:
    FullTextEntry();
    virtual ~FullTextEntry() {}
    
    unsigned long getNumHits();
    wxString getRegnrs();
    wxArrayString getRegnrsAsArray();
    std::set<wxString> getChaptersForKey(wxString &regnr);
    
    // 28
    wxString hash;
    wxString keyword;
    wxString regnrs;
    
private:
    // 38
    //long numHits; // see getNumHits()
    
public:
    // .m 29
    std::map<wxString, std::set<wxString>> regChaptersDict;
};
