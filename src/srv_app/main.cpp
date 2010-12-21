/******************************************************************************
 * Project:  wxGIS (GIS Server)
 * Purpose:  Main application class.
 * Author:   Bishop (aka Barishnikov Dmitriy), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2010  Bishop
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#include "wxgissrv/srv_app/main.h"
#include "wxgissrv/srv_framework/server.h"

//---------------------------------------------
// main
//---------------------------------------------


int main(int argc, char **argv)
{
    wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

    wxInitializer initializer;
    if ( !initializer )
    {
        wxFprintf(stderr, _("Failed to initialize the wxWidgets library, aborting."));//fprintf(
        return -1;
    }

	bool success( false );

    // Parse command line arguments
    success = parse_commandline_parameters( argc, argv );

    return success;
}


bool parse_commandline_parameters( int argc, char** argv )
{
    // Create the commandline parser
    static const wxCmdLineEntryDesc my_cmdline_desc[] =
    {
        { wxCMD_LINE_SWITCH, wxT( "h" ), wxT( "help" ), _( "Show this help message" ),
            wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
        { wxCMD_LINE_SWITCH, wxT( "v" ), wxT( "version" ), _( "The version of this program" ) },
		{ wxCMD_LINE_SWITCH, wxT( "r" ), wxT("run"), _( "Run the monitoring server in standalone mode. Press 'q' to quit." ) },
		//{ wxCMD_LINE_OPTION, wxT( "i" ), wxT("index"), _( "Index the locations set in DB with max count of nodes" ), wxCMD_LINE_VAL_NUMBER },
		//{ wxCMD_LINE_SWITCH, wxT( "u" ), wxT("update"), _( "Update the locations set in config file (add/remove paths & etc.)" ) },
  //      { wxCMD_LINE_SWITCH, wxT( "l" ), wxT("list"), _( "list path's" ) },
  //      { wxCMD_LINE_SWITCH, wxT( "L" ), wxT("listall"), _( "list all path's" ) },
  //      { wxCMD_LINE_OPTION, wxT( "d" ), wxT("detail"), _("show node details"), wxCMD_LINE_VAL_NUMBER },
		{ wxCMD_LINE_NONE }
    };

    wxCmdLineParser my_parser( my_cmdline_desc, argc, argv );
    my_parser.SetLogo(wxString::Format(_("The wxMonitoring server utility (%s)\nAuthor: Bishop (aka Barishnikov Dmitriy), polimax@mail.ru\nCopyright (c) 2010"), APP_VER));

    // Parse the parameters
    int my_parse_success = my_parser.Parse( );
    // Print help if the specify /? or if a syntax error occured.
    if( my_parse_success != 0 )
    {
        return false;
    }

	if( my_parser.Found( wxT( "v" ) ) )
	{
	    wxString out = wxString::Format(_("The wxMonitoring server utility (%s)\nAuthor: Bishop (aka Barishnikov Dmitriy), polimax@mail.ru\nCopyright (c) 2010\n"), APP_VER);
	    wxFprintf(stdout, out);
		return true;
	}

	if( my_parser.Found( wxT( "r" ) ) )
	{
        wxGISServer Server;
		if(!Server.Start())
		{
            Server.Stop();
			return false;
		}

        wxFprintf(stdout, wxString(_("Press 'q' to quit.\n")));
		while (getchar() != 'q');

		Server.Stop();
		return true;
	}
    
//	//
//	//1 get config
//	wxXmlDocument config_doc;
//	if (!config_doc.Load(sConfigPath))
//	{
//		wxLogError(_("Config load error! Path: %s"), sConfigPath.c_str());
//		return false;
//	}
//	// start processing the XML file
//	if (config_doc.GetRoot()->GetName() != wxT("wxSphinxIndexer"))
//	{
//		wxLogError(_("Config format not supported! Config file: %s"), sConfigPath.c_str());
//		return false;
//	}
//
//	wxString sDBPath, sLogPath, sLoc;
//	wxXmlNode *pIndexPaths(0);
//	wxXmlNode *child = config_doc.GetRoot()->GetChildren();
//	wxXmlNode *pLib(0);
//	wxXmlNode *pIndexerConf(0);
//	wxXmlNode *pFactoriesConf(0);
//	while (child)
//	{
//	//2 get DB path from config
//		if (child->GetName() == wxT("db"))
//			sDBPath = child->GetPropVal(wxT("path"), wxT(""));
//		if (child->GetName() == wxT("log"))
//			sLogPath = child->GetPropVal(wxT("path"), wxT(""));
//        if (child->GetName() == wxT("loc"))
//            sLoc = child->GetPropVal(wxT("locale"), wxT("en"));
//	//3 get index path from config
//		if (child->GetName() == wxT("updater"))
//			pIndexPaths = child;
//	//4 get libs
//		if (child->GetName() == wxT("lib"))
//			pLib = child;
//	//5 get libs
//		if (child->GetName() == wxT("indexer"))
//			pIndexerConf = child;
//	//6 get factories
//		if (child->GetName() == wxT("factories"))
//			pFactoriesConf = child;
//
//		child = child->GetNext();
//	}
//
////	setlocale (LC_ALL, "");
////    bindtextdomain (PACKAGE, LOCALEDIR);
////    textdomain (PACKAGE);
//	// locale we'll be using
//	wxLocale locale;
//	//wxString sLocale(wxT("ru"));
//	//init locale
//	int iLocale(0);
//	const wxLanguageInfo* loc_info = wxLocale::FindLanguageInfo(sLoc);
//	if(loc_info != NULL)
//		iLocale = loc_info->Language;
//
//    // don't use wxLOCALE_LOAD_DEFAULT flag so that Init() doesn't return
//	// false just because it failed to load wxstd catalog
//    if ( !locale.Init(iLocale, wxLOCALE_CONV_ENCODING) )
//    {
//        wxLogError(_T("This language is not supported by the system."));
//		return false;
//    }
//	//locale.Init(wxLANGUAGE_DEFAULT);
//    #ifdef __LINUX__
//	{
//		locale.AddCatalog(_T("fileutils"));
//	}
//	#endif
//
//	//3. wxLog setup
//	wxFFile LogFile;
//	if(!sLogPath.IsEmpty())
//	{
//		wxDir dir(sLogPath);
//		if (dir.IsOpened())
//		{
//			wxDateTime dt(wxDateTime::Now());
//			wxString logfilename = sLogPath + wxFileName::GetPathSeparator() +
//				wxString::Format(wxT("wxSphinxLog_%.4d%.2d%.2d.log"),dt.GetYear(), dt.GetMonth() + 1, dt.GetDay());
//
//			if(!bQuiet)
//				wxLogMessage(_("Log file: %s"), logfilename.c_str());
//
//			if(!LogFile.Open(logfilename.GetData(), wxT("a+")))
//				wxLogError(_("Filed to open log file"));
//
//			delete wxLog::SetActiveTarget(new wxLogStderr(LogFile.fp()));
//		}
//	}
//
//	wxLogMessage(_("The language set to %s"), loc_info->Description.c_str());
//
//	//4 open/create DB
//	wxSQLite3Database db;
//	db.Open(sDBPath + wxFileName::GetPathSeparator() + INDEXDB);
//	if(!db.IsOpen())
//	{
//        wxLogError(_("Filed to open DB"));
//		return false;
//	}
//
//	//5 load libs
//	wxSphinxPluginManager mngr(pLib);
//    wxSphinxFactories Factories(pFactoriesConf);
//
//	if( my_parser.Found( wxT( "l" ) ) )
//	{
//		wxSphinxUpdater updater(bQuiet, pIndexPaths, &db, &Factories);
//		updater.List(false);
//		return true;
//	}
//
//	if( my_parser.Found( wxT( "L" ) ) )
//	{
//		wxSphinxUpdater updater(bQuiet, pIndexPaths, &db, &Factories);
//		updater.List(true);
//		return true;
//	}
//
//    long nMaxCount;
//	if( my_parser.Found( wxT( "i" ), &nMaxCount ) )
//	{
//		//do work
//		wxSphinxIndexer indexer(bQuiet, pIndexerConf, &db, &Factories);
//		return indexer.Start(nMaxCount);
//	}
//
//	if( my_parser.Found( wxT( "u" ) ) )
//	{
//		//do work
//		wxSphinxUpdater updater(bQuiet, pIndexPaths, &db, &Factories);
//		return updater.Start();
//	}
//	long nIndex;
//	if( my_parser.Found( wxT( "d" ), &nIndex ))
//	{
//		//do work
//		wxSphinxIndexer indexer(bQuiet, pIndexerConf, &db, &Factories);
//		return indexer.ShowDetails(nIndex);
//    }
	my_parser.Usage();

    // Either we are using the defaults or the provided parameters were valid.

    return true;

} 



// end parse_commandline_parameters

    //static const wxCmdLineEntryDesc cmdLineDesc[] =
    //{
    //    { wxCMD_LINE_SWITCH, _T("h"), _T("help"), _T("show this help message"),
    //        wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
    //    { wxCMD_LINE_SWITCH, _T("q"), _T("quiet"), _T("be quiet (don't log fcp)") },
    //    { wxCMD_LINE_OPTION, _T("o"), _T("fcphost"), _T("use given fcp host"),
    //        wxCMD_LINE_VAL_STRING },
    //    { wxCMD_LINE_OPTION, _T("p"), _T("fcpport"), _T("use given fcp port"),
    //        wxCMD_LINE_VAL_NUMBER },
    //    { wxCMD_LINE_OPTION, _T("t"), _T("fcptimeout"), _T("set connection timeout for fcp"),
    //        wxCMD_LINE_VAL_NUMBER },
    //    { wxCMD_LINE_NONE }
    //};

	//wxCmdLineParser parser(cmdLineDesc, argc, wxArgv);
 //   switch ( parser.Parse(true) )
 //       {
 //       case -1:
 //           return 0;  // Help was shown, go away.
 //           break;

 //       case 0:
 //           // everything is ok; proceed
 //           break;

 //       default:
 //           wxLogFatalError(_T("Syntax error detected, aborting."));
 //           break;
 //   }

 //   wxString host;
 //   if ( !parser.Found(_T("o"), &host) )
 //   {
 //       if ( !wxGetEnv(_T(FCP_HOST_ENV_NAME), &host) )
 //       {
 //           host = _T(DEFAULT_FCP_HOST);
 //       }
 //   }
//
//    long port;
//    if ( !parser.Found(_T("p"), &port) )
//    {
//        wxString sport;
//        if ( wxGetEnv(_T(FCP_PORT_ENV_NAME), &sport) )
//        {
//            if ( !sport.ToLong(&port) )
//            {
//                wxLogFatalError(_T("not a valid number"));
//            }
//        }
//        else
//        {
//            port = DEFAULT_FCP_PORT;
//        }
//    }
//
//    long timeout;
//    if ( !parser.Found(_T("t"), &timeout) )
//    {
//        wxString stimeout;
//        if ( wxGetEnv(_T(FCP_TIMEOUT_ENV_NAME), &stimeout) )
//        {
//            if ( !stimeout.ToLong(&timeout) )
//            {
//                wxLogFatalError(_T("not a valid number"));
//            }
//        }
//        else
//        {
//            timeout = DEFAULT_FCP_TIMEOUT;
//        }
//    }
//

