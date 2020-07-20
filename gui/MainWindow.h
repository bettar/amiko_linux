#ifndef __MainWindow__
#define __MainWindow__

/**
@file
Subclass of MainWindowBase, which is generated by wxFormBuilder.
*/

#include <set>
#include "MainWindowBase.h"
//#include "SQLiteDatabase.hpp"
#include "DataStore.hpp"  // for FAVORITES_SET

//// end generated include

class DBAdapter;
class InteractionsAdapter;
class InteractionsHtmlView;
class FullTextDBAdapter;
class Medication;
class FullTextEntry;
class TableViewDelegate;
class PrescriptionsAdapter;
class PatientSheet;
class OperatorIDSheet;
class FullTextSearch;
class DataStore;

/** Implementing MainWindowBase */
class MainWindow : public MainWindowBase
{
	protected:
		// Handlers for MainWindowBase events.
		void OnSearchNow( wxCommandEvent& event );
		void OnButtonPressed( wxCommandEvent& event );
		void OnSearchFiNow( wxCommandEvent& event );
		void OnPerformFindAction( wxCommandEvent& event );
		void OnSearchPatient( wxCommandEvent& event );
		void OnNewPrescription( wxCommandEvent& event );
		void OnCheckForInteractions( wxCommandEvent& event );
		void OnSavePrescription( wxCommandEvent& event );
		void OnSendPrescription( wxCommandEvent& event );
		void OnSelectionDidChange( wxDataViewEvent& event );
		void OnToolbarAction( wxCommandEvent& event );
		void OnPrintDocument( wxCommandEvent& event );
		void OnShowAboutPanel( wxCommandEvent& event );
		void OnUpdateAipsDatabase( wxCommandEvent& event );
		void OnLoadAipsDatabase( wxCommandEvent& event );
        void OnExportWordListSearchResults( wxCommandEvent& event );
        void OnLoadPrescription( wxCommandEvent& event );
		void OnManagePatients( wxCommandEvent& event );
		void OnSetOperatorIdentity( wxCommandEvent& event );
	public:
		/** Constructor */
		MainWindow( wxWindow* parent );
	//// end generated class members

private:
    void fadeInAndShow();
    void resetDataInTableView();
    void setSearchState(int searchState, int btnId);
    void hideTextFinder();
    void updateSearchResults();
    void updateTableView();
    void switchTabs(int item);
    void stopProgressIndicator();
    void addTitle_andPackInfo_andMedId(wxString title, wxString packinfo, long medId);
    void addTitle_andAuthor_andMedId(wxString title, wxString author, long medId);
    void addTitle_andAtcCode_andAtcClass_andMedId(wxString title, wxString atccode, wxString atcclass, long medId);
    void addTitle_andRegnrs_andAuthor_andMedId(wxString title, wxString regnrs, wxString author, long medId);
    void addTitle_andApplications_andMedId(wxString title, wxString applications, long medId);

    void addKeyword_andNumHits_andHash(wxString keyword, unsigned long numHits, wxString hash);

    bool openSQLiteDatabase();
    bool openFullTextDatabase();
    bool openInteractionsCsvFile();
    void searchAnyDatabasesWith(wxString searchQuery);
    std::vector<Medication *> retrieveAllFavorites();
    void updateExpertInfoView(wxString anchor);
    void pushToMedBasket(Medication *med);
    void updateInteractionsView();
    void updatePrescriptionsView();
    void updatePrescriptionHistory();
    void updateFullTextSearchView(wxString contentStr);
    void finishedDownloading();
    void updateButtons();
    void saveFavorites();
    void loadFavorites(DataStore *favorites);
    void tappedOnStar(int row);
    Medication * getShortMediWithId(long mid);
    void setOperatorID();
    void savePrescription();
    
    // not in amiko-osx
    int m_findCount;
    wxColour fiSearchFieldBGColor;//GetBackgroundColour()
    void mySectionTitles_reloadData(); // [mySectionTitles reloadData]

    // 105
    int mUsedDatabase;
    // 110
    bool mSearchInteractions;
    bool mPrescriptionMode;
    // 150
    DBAdapter *mDb;
    // 153
    FullTextDBAdapter *mFullTextDb;
    FullTextEntry *mFullTextEntry;

    // .m 149
    Medication *mMed;

    // .m 151
    InteractionsAdapter *mInteractions;
    InteractionsHtmlView *mInteractionsView;

    // .m 155
    FullTextSearch *mFullTextSearch;

    PatientSheet *mPatientSheet;
    OperatorIDSheet *mOperatorIDSheet;
    PrescriptionsAdapter *mPrescriptionAdapter;
    [[deprecated]] std::vector<DataObject *> doArray ; // __deprecated
public:
    wxArrayString favoriteKeyData;
 
    // .m 165
    FAVORITES_SET favoriteMedsSet;     // set of RegNrs
    FAVORITES_SET favoriteFTEntrySet;  // set of hashIDs

private:
    // .m 168
    std::vector<Medication *> searchResults;
    std::vector<FullTextEntry *> searchResultsFT;

    // .m 170
    wxArrayString mListOfSectionIds;  // full paths
    wxArrayString mListOfSectionTitles;
    
    // .m 179
    wxString mAnchor;
    wxString mFullTextContentStr;
    
    // .m 183
    bool mSearchInProgress;
    float m_alpha;
    float m_delta;
    bool possibleToOverwrite;
    bool modifiedPrescription;  // if true, presenting save/overwrite option makes sense
    
    void OnLboxSelect(wxCommandEvent& event);
    void OnLboxDClick(wxCommandEvent& event);
    
    // Delegate
    void OnHtmlLinkClicked(wxHtmlLinkEvent& event);
    void OnHtmlCellHover(wxHtmlCellEvent &event);
    void OnHtmlCellClicked(wxHtmlCellEvent &event);
    void OnNavigationRequest(wxWebViewEvent& evt);
    void OnTitleChanged(wxWebViewEvent& evt);
    void OnDocumentLoaded(wxWebViewEvent& evt);

    // MLItemCellView.m:179
    void selectBasket(int cartNumber);

private:
    
    DECLARE_EVENT_TABLE()
};

#endif // __MainWindow__
