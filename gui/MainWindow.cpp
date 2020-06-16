
#include <vector>

#include <wx/wx.h>
#include <wx/stdpaths.h>
//#include <wx/dialup.h>

#include <sqlite3.h>

#include "MainWindow.h"
#include "customURLConnection.hpp"
#include "DBAdapter.hpp"

#include "../res/xpm/CoMed.xpm"

// Search states
enum {
    kTitle=0, kAuthor=1, kAtcCode=2, kRegNr=3, kTherapy=4, kWebView=5, kFullText=6
};

MainWindow::MainWindow( wxWindow* parent )
: MainWindowBase( parent )
, mCurrentSearchState(kTitle)
{
    if (APP_NAME == "CoMed") {
        m_toolAbout->SetLabel("CoMed Desitin");
        m_tbMain->SetToolNormalBitmap(wxID_ABOUT, wxBitmap( CoMed_xpm ));
    }
    
    SetTitle(APP_NAME);
    
    fadeInAndShow();

    // TODO: Register applications defaults if necessary
    // TODO: Start timer to check if database needs to be updatd (checks every hour)

    // Open sqlite database
    openSQLiteDatabase();
    
    // TODO: Open fulltext database
    // openFullTextDatabase();
//    #ifdef DEBUG
//    NSLog(@"Number of records in fulltext database = %ld", (long)[mFullTextDb getNumRecords]);
//    #endif
        
    // TODO: Open drug interactions csv file
    //openInteractionsCsvFile();
//    #ifdef DEBUG
//    NSLog(@"Number of records in interaction file = %lu", (unsigned long)[mInteractions getNumInteractions]);
//    #endif

    fiPanel->SetPage("<html><body>Fachinfo</body></html>");
    fiPanel->Fit();
}

// 483
void MainWindow::hideTextFinder()
{
    std::clog << __PRETTY_FUNCTION__  << "TODO" << std::endl;

#if 0
    // Inform NSTextFinder the text is going to change
    [myTextFinder noteClientStringWillChange];
    // Hide text finder
    [myTextFinder performAction:NSTextFinderActionHideFindInterface];
    // Discard previous data structures
    [myWebView invalidateTextRanges];
#endif
}

// 548
void MainWindow::fadeInAndShow()
{
    resetDataInTableView();
}

// 605
void MainWindow::openSQLiteDatabase()
{
    mDb = new DBAdapter;

    const char * languageCode;
    if (APP_NAME == "CoMed")
        languageCode = "fr";
    else
        languageCode = "de";

    bool ok = mDb->openDatabase(wxString::Format("amiko_db_full_idx_%s", languageCode));
}

// 847
void MainWindow::updateSearchResults()
{
    std::clog << __PRETTY_FUNCTION__ << " TODO" << std::endl;
#if 0
    if (mUsedDatabase == kAips)
        searchResults = [self searchAnyDatabasesWith:mCurrentSearchKey];
    else if (mUsedDatabase == kFavorites)
        searchResults = [self retrieveAllFavorites];
#endif
}

// 858
void MainWindow::resetDataInTableView()
{
    // Reset search state
    setSearchState(kTitle);

    //myTableView->reloadData();
}

// 1967
void MainWindow::setSearchState(int searchState)
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;

    switch (searchState)
    {
        case kTitle:
            mySearchField->SetValue("");
            mCurrentSearchState = kTitle;
            mySearchField->SetDescriptiveText(wxString::Format("%s %s", _("Search"), _("Preparation")));
             break;

        case kAuthor:
            mySearchField->SetValue("");
            mCurrentSearchState = kAuthor;
            mySearchField->SetDescriptiveText(wxString::Format("%s %s", _("Search"), _("Owner")));
            break;

        case kAtcCode:
            mySearchField->SetValue("");
            mCurrentSearchState = kAtcCode;
            mySearchField->SetDescriptiveText(wxString::Format("%s %s", _("Search"), _("ATC Code")));
            break;

        case kRegNr:
            mySearchField->SetValue("");
            mCurrentSearchState = kRegNr;
            mySearchField->SetDescriptiveText(wxString::Format("%s %s", _("Search"), _("Reg. No")));
            break;

        case kTherapy:
            mySearchField->SetValue("");
            mCurrentSearchState = kTherapy;
            mySearchField->SetDescriptiveText(wxString::Format("%s %s", _("Search"), _("Therapy")));
            break;

        case kWebView:
            // Hide textfinder
            hideTextFinder();
            // NOTE: Commented out because we're using SHCWebView now (02.03.2015)
            /*
            mySearchField->SetValue("");
            mCurrentSearchState = kWebView;
            mySearchField->SetDescriptiveText(wxString::Format("%s %s", _("Search"), _("in Fachinformation"))); // fr: @"Notice Infopro"
            */
            break;

        case kFullText:
            mySearchField->SetValue("");
            mCurrentSearchState = kFullText;
            mySearchField->SetDescriptiveText(wxString::Format("%s %s", _("Search"), _("Full Text")));
            break;
    }

    mCurrentSearchKey = "";
    mCurrentSearchState = searchState;
}

// 2286
void MainWindow::updateTableView()
{
    std::clog << __PRETTY_FUNCTION__ << " TODO" << std::endl;
}

void MainWindow::OnButtonPressed( wxCommandEvent& event )
{
    int prevState = mCurrentSearchState;

    switch (event.GetId()) {
        case wxID_BTN_PREPARATION:
            setSearchState(kTitle);
            break;
            
        case wxID_BTN_REGISTRATION_OWNER:
            setSearchState(kAuthor);
            break;
            
        case wxID_BTN_ACTIVE_SUBSTANCE:
            setSearchState(kAtcCode);
            break;
            
        case wxID_BTN_REGISTATION_NUMBER:
            setSearchState(kRegNr);
            break;
            
        case wxID_BTN_THERAPY:
            setSearchState(kTherapy);
            break;
            
        case wxID_BTN_FULL_TEXT:
            setSearchState(kFullText);
            break;
    }
    
    if (prevState == kFullText || mCurrentSearchState == kFullText)
        updateSearchResults();
    
    if (searchResults.size() > 0) {
        updateTableView();
        // myTableView->reloadData(); // TODO:
    }
}

void MainWindow::OnShowAboutPanel( wxCommandEvent& event )
{
    wxMessageBox(wxString::Format("%s\n%s\nSQLite %s",
             wxGetOsDescription(), wxVERSION_STRING, SQLITE_VERSION),
    APP_NAME, wxOK | wxICON_INFORMATION);
}

void MainWindow::OnUpdateAipsDatabase( wxCommandEvent& event )
{
    // TODO: check if there is an active internet connection
    //std::clog << wxDialupManager::IsOnline() << std::endl;

    wxBusyCursor wait;

    const char * languageCode;
    if (APP_NAME == "CoMed")
        languageCode = "fr";
    else
        languageCode = "de";

    downloadTextFileWithName(wxString::Format("amiko_report_%s.html", languageCode));
    
    downloadFileWithName(wxString::Format("drug_interactions_csv_%s.zip", languageCode));
    downloadFileWithName(wxString::Format("amiko_frequency_%s.db.zip", languageCode));
    downloadFileWithName(wxString::Format("amiko_db_full_idx_%s.zip", languageCode));
}

void MainWindow::OnLoadAipsDatabase( wxCommandEvent& event )
{
    std::clog << __PRETTY_FUNCTION__ << std::endl;
}
