//  main.cpp
//  AmiKo-wx
//
//  Created by Alex Bettarini on 12 Jun 2020
//  Copyright © 2020 Ywesee GmbH. All rights reserved.

#include <stdio.h>
#include <iostream>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/stdpaths.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/intl.h>
#include <wx/dir.h>
#include "wx/fs_zip.h"
#include <wx/zipstrm.h>

#include "main.hpp"
#include "MainWindow.h"
#include "DefaultsController.hpp"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;
    
    wxInitAllImageHandlers();

#if 1
    wxLanguage initialLanguage;

    if (wxString(APP_NAME) == "CoMed")
        initialLanguage = wxLANGUAGE_FRENCH_SWISS;
    else
        initialLanguage = wxLANGUAGE_GERMAN_SWISS;

    DefaultsController* defaults = DefaultsController::Instance();
    m_lang = (wxLanguage)defaults->getInt("language", initialLanguage);

    if (!m_locale.Init(m_lang, wxLOCALE_DONT_LOAD_DEFAULT) )
    {
#ifndef NDEBUG
        wxLogWarning(_("This language is not supported by the system."));
        // continue nevertheless
#endif
    }

    const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(m_lang);
    wxLocale::AddCatalogLookupPathPrefix(wxStandardPaths::Get().GetLocalizedResourcesDir(pInfo->CanonicalName, wxStandardPathsBase::ResourceCat_Messages));
    // Initialize the catalogs we'll be using
    if (m_lang != wxLANGUAGE_ENGLISH &&
        !m_locale.AddCatalog("amiko"))
    {
        wxLogError(_("Couldn't find/load the 'amiko' catalog for locale '%s'."),
                   pInfo ? pInfo->GetLocaleName() : _("unknown"));
    }

#if 0 // issue #42
    // Now try to add wxstd.mo so that loading "NOTEXIST.ING" file will produce
    // a localized error message:
    m_locale.AddCatalog("wxstd");
    // NOTE: it's not an error if we couldn't find it!
#endif

    // This catalog is installed in standard location on Linux systems and
    // shows that you may make use of the standard message catalogs as well
    //
    // if it's not installed on your system, it is just silently ignored
#ifdef __linux__
    {
        wxLogNull noLog;
        m_locale.AddCatalog("fileutils");
    }
#endif
#endif

    wxString dir = wxStandardPaths::Get().GetUserDataDir();
    if (!wxDir::Exists(dir))
        wxFileName::Mkdir(dir);
    
    wxFileSystem::AddHandler(new wxZipFSHandler);

    MainWindow* frame = new MainWindow(nullptr);
    frame->Show();
    SetTopWindow( frame );
    return true;
}

int MyApp::OnExit()
{
#if 0
    delete wxConfig::Set(nullptr);
#endif
    return EXIT_SUCCESS;
}
