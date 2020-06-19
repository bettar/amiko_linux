#ifndef __MainWindow__
#define __MainWindow__

/**
@file
Subclass of MainWindowBase, which is generated by wxFormBuilder.
*/

#include "MainWindowBase.h"
#include "SQLiteDatabase.hpp"

//// end generated include

class DBAdapter;
class InteractionsAdapter;
class FullTextDBAdapter;
class Medication;
class TableViewDelegate;

/** Implementing MainWindowBase */
class MainWindow : public MainWindowBase
{
	protected:
		// Handlers for MainWindowBase events.
		void OnSearchNow( wxCommandEvent& event );
		void OnButtonPressed( wxCommandEvent& event );
		void OnToolbarAction( wxCommandEvent& event );
		void OnPrintDocument( wxCommandEvent& event );
		void OnShowAboutPanel( wxCommandEvent& event );
		void OnUpdateAipsDatabase( wxCommandEvent& event );
		void OnLoadAipsDatabase( wxCommandEvent& event );
	public:
		/** Constructor */
		MainWindow( wxWindow* parent );
	//// end generated class members

private:
    void fadeInAndShow();
    void resetDataInTableView();
    void setSearchState(int searchState);
    void hideTextFinder();
    void updateSearchResults();
    void updateTableView();
    void switchTabs(int item);
    void stopProgressIndicator();
    void addTitle_andPackInfo_andMedId(char *title, char *packinfo, long medId);

    void openSQLiteDatabase();
    void openFullTextDatabase();
    void openInteractionsCsvFile();
    std::vector<Medication *> searchAnyDatabasesWith(wxString searchQuery);
    std::vector<Medication *> retrieveAllFavorites();

    // 105
    int mUsedDatabase;
    // 110
    bool mSearchInteractions;
    bool mPrescriptionMode;
    // 150
    DBAdapter *mDb;
    // 153
    FullTextDBAdapter *mFullTextDb;

    // .m 151
    InteractionsAdapter *mInteractions;

    // .m 162
    std::vector<DataObject *> doArray;

    // .m 168
    std::vector<Medication *> searchResults;
    
    // .m 183
    bool mSearchInProgress;
    
    // Delegate
    void OnHtmlLinkClicked(wxHtmlLinkEvent& event);
    //void OnHtmlCellHover(wxHtmlCellEvent &event);
    virtual void OnHtmlCellClicked(wxHtmlCellEvent &event);

private:
    
    DECLARE_EVENT_TABLE()
};

#endif // __MainWindow__
