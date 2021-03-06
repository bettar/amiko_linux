//  Utilities.hpp
//  AmiKo-wx
//
//  Created by Alex Bettarini on 17 Jun 2020
//  Copyright © 2020 Ywesee GmbH. All rights reserved.

#pragma once

#include <wx/wx.h>

namespace UTI
{

const char * appLanguage();
wxString documentsDirectory();
bool checkFileIsAllowed(const wxString name);
wxString currentTime();
wxString prettyTime();
wxString getColorCss();
wxString sha256(const wxString str);

}
