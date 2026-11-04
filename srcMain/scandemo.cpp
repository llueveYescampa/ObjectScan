//-------------------------------------------------------------------------------
//
//    Scandemo --  A program demonstrating  use of the ObjectScan system
//                 Thu 21 Nov 2024 08:14:59 AM CST
//
//    questions may be addressed to :
//       Edgar F. Black -- email edgarfblack@hotmail.com
//
//
//    Program is designed to start up with 
//       standard input = keyboard and
//       standard output = screen. 
//
//    The user can then redirect
//    them to various files, back to standard input-output, etc. using
//    ObjectScan supplied functions.
//
//-----------------------------------------------------------------------------
//  Here is the alphabetic list of the ObjectScan system functions:
//  backsp()                    done
//  doscan()                    done
//  endcrd()                    done
//  endstr()                    done
//  floatn()                    done
//  getEcho()			        done
//  getstr()                    done
//  getVersion()                done
//  in_from_stdin()		        done ! former in_from_remote()
//  integr()                    done
//  isStdinKybrd()              done
//  isStdoutScreen()		    done
//  isstring()                  done
//  label()                     done
//  matchs()                    done
//  matchs_exact()              done
//  name()                      done
//  numd()                      done
//  numf()                      done
//  numi()                      done
//  out_to_stdout()             done
//  readLine()			        done ! former readsc()
//  reset()                     done
//  scan_contents()             done
//  sep()                       done
//  setInputFile(filename)	    done ! former open_input_file()
//  setInputFile()		        done ! Overloaded version of setInputFile(filename)
//  setOutputFile(filename)     done
//  setOutputFile()             done ! Overloaded version of setOutputFile(filename)
//  setEcho()			        done ! now renamed setEcho()
//  sizlst()                    done
//  skpstr()                    done
//  trlist()                    done
//  trxlist()                   done ! the arguments for this function has been changed
//  getVersion()		        done
// _____________________________________________________
//  init_scan()			not needed any more. The class constructor do the house keeping now.
//  istrue()			not needed any more
//---------------------------------------------------------------------
//   Here are some command examples and its correct answers:
//
//   > check double 12
//         check double 12
//
//   >> double not found...
//
//   > check double 12.13
//         check double 12.13
//
//   >> double found: 12.13
//
//   > check double 12e-3
//         check double 12e-3
//
//   >> double found: 0.012
//
//   > check numi 23.23
//         check numi 23.23
//
//   >> integer found:         23
//
//
//   > this is a n.a.m.e
//         this is a n.a.m.e
//
//   >> label found:  this
//
//      number of characters in label:   4
//
//
//   >> label found:    is
//
//      number of characters in label:   2
//
//
//   >> label found:     a
//
//      number of characters in label:   1
//
//
//   >> Name found: name
//
//   > list 1-8 by 2 100 to 9 by -20 type quad
//         list 1-8 by 2 9 to 100 by 20 type quad
//   > got list command
//
//   1
//   -8
//   2
//   100
//   -9
//   -20
//   lenlst:6
//   errnum:1
//   Size of the list:9
//   next: 1
//   next: 3
//   next: 5
//   next: 7
//   next: 100
//   next: 80
//   next: 60
//   next: 40
//   next: 20
//   > got type command
//
//   > got quad command after type
//
//   > got type command again after backsp(2)
//
//   > got list command after reset the scaner
//
//   > quit
//         quit
//
//   >> Normal termination. Bye!
//
//---------------------------------------------------------------------


#include <iostream>
#include <iomanip>

#include "ObjectScan.h"

// scan_demo_prog functions prototypes
void message(Scan &, const positiveInt &ierr, const char *const mensage=" ",const int &ivalue=0, const float &value=0);
void check_specified_item(Scan &);
void process_tokens_on_line(Scan &);
void output_command(Scan &);
void input_command(Scan &);
// end of scan_demo_prog functions prototypes


int main(int argc, char *argv[])
{
   
   Scan myScan;
   
   switch (argc) {
   case (2):
   case (3):
      if (!myScan.setInputFile(argv[1])) {
        cerr << "Input data file '" << argv[1] << "' not found\n";
        exit(-1);
      } // end if //  
      if (argc >= 3) {
         if (!myScan.setOutputFile(argv[2])) {    // setOutputFile() == true means file was opened
           cerr << ".... Specified file cannot be opened.... \n"
                << "....command ignored....\n";
        } // end if //
      } // end if //
      break;
   } // endswitch //


// variables used to test trlist() and trxlst()
   int errnum,iplist,next;
   int intlst[100];
   positiveInt lenlst, zero=0;
// End of variables used to test trlist() and trxlst()


   message(myScan, 1);  // Notice the defult arguments on prototype.
//
//      start infinite loop to read and process command lines
//
   while (myScan.readLine()) {
//
//               stop, quit, exit command
//
      if (myScan.matchs_exact("stop")  or myScan.matchs_exact("quit")  or myScan.matchs_exact("exit")) {
         message(myScan,2);
         exit(0);
      } // end if //
//
//               process "check" command
//
      if(myScan.matchs( "check",4 ) ) {
         check_specified_item(myScan);
//
//               check for and process integer list
//
      } else if (myScan.matchs_exact( "list")) {
         cout << "> got list command \n" << endl;
//         myScan.doScan();  // this command here is optional.
         myScan.trlist(intlst,sizeof(intlst)/sizeof(int),10,lenlst,errnum);
         for (auto i=zero; i < lenlst ;i++ ) {
            cout << intlst[i] << endl;
         }
         cout << "lenlst:" << lenlst << endl;
         cout << "errnum:" << errnum << endl;
         cout << "Size of the list:" << myScan.sizlst(intlst,lenlst) << endl;
         // Testing the sizlst function
         if (errnum == 1) {
            // not longer needed icn = 0;
            iplist = 1;
            do {
               myScan.trxlst(next,iplist,intlst,lenlst);
               cout << "next: " << next << endl;
            } while (iplist != 0 );
        
           // Testing the backsp function
//           myScan.backsp(1);                 //  not needed here
            if (myScan.matchs_exact( "type")) {
               cout << "> got type command \n" << endl;
               if (myScan.matchs_exact( "quad")) {
                  cout << "> got quad command after type\n" << endl;
               } else {
                  cout << "> miss quad command after type\n" << endl;
               }
            } else {
               cout << "> miss type command \n" << endl;
            }
            myScan.backsp(2);                
            if (myScan.matchs( "type",4)) {
               cout << "> got type command again after backsp(2)\n" << endl;
            } else {
               cout << "> miss type command again after backsp(2)\n" << endl;
            }
            // Testing the reset function
//          istrue();   not longer needed
            myScan.reset();
            if (myScan.matchs("list",4)) {
               cout << "> got list command after reset the scaner\n" << endl;
            } else {
               cout << "> miss list command. Reset was not issued\n" << endl;
            }
         } else {
            cout << "Error in list was found" << endl;
         } // end if //
//
//               turn read echo on or off
//
      } else if( myScan.matchs_exact( "echo" ) ) {
         if ( myScan.matchs_exact( "on") )  {
            myScan.setEcho( true );
         } else {
            myScan.setEcho( false );
         } // end if //
//
//              output to a different file
//
      } else if( myScan.matchs( "output",4 ) ) {
         output_command(myScan);
//
//                input from a different file
//
      } else if( myScan.matchs( "input",4 ) ) {
         input_command(myScan);
//
//                not a command. just identify each "token"
//                on the line
      } else {
         process_tokens_on_line(myScan);
      } // end if
   } // end while //
   return 0;
} // end of main() //

// **************************************************************
// *                                                            *
// * message: send message to stdout                            *
// *                                                            *
// **************************************************************

void message(Scan &scan, const positiveInt &ierr, const char *const message,const int &ivalue,
             const float &value)
{

  switch (ierr) {
  case 1:
     cout << "\n *** ObjectScan " << scan.getObjectScanVersion() << " - Demo Program  ***\n\n"  << endl;
     cout << "Type any input line at the > prompt and it will be parsed...\n\n" << endl;
     break;
  case 2:
     cout << "\n>> Normal termination. Bye!\n\n" << endl;
     break;
  case 3:
     cout << "\n>> string found: " << setw(5) <<  message << endl<< endl;
     cout << "  number of characters in string: " << setw(2) << ivalue<< endl;
     break;
  case 4:
     cout << "\n>> label found: " <<  setw(5) << message << endl << endl;
     cout << "   number of characters in label: " <<  setw(3) << ivalue << endl<< endl;
     break;
  case 5:
     cout << "\n>> integer found: " << setw(3) <<ivalue << endl<< endl;
     break;
  case 6:
     cout << "\n>> float found: "                   << value << endl<< endl;
     break;
  case 7:
     cout << "\n>> separator found: " << setw(3) <<ivalue << endl<< endl;
     break;
  case 8:
     cout << "\n>> name found: " << setw(3) << message<< endl<< endl;
     break;
  case 9:
     cout << "\n>> unrecognized item: " <<  message << endl;
     cout << "\n>> scanning of this line terminated...\n" << endl;
     break;
  default:
     cout << ">> Fatal Error: invalid menssage specified\n\n";
     cout << ">> Program Terminated....\n\n" << endl;
    exit(0);
    break;
  } // end switch //
} // end of message() //



// **************************************************************
// *                                                            *
// * check_specified_item                                       *
// *                                                            *
// **************************************************************

void check_specified_item(Scan &scan)
{
   int ivalue;
   float fvalue;
   double dvalue;

   if (scan.matchs( "double",6)) {
     if (scan.floatn( fvalue )) {
        dvalue = static_cast<double> (fvalue);
        cout << "\n >> double found: " << dvalue << endl << endl;
     } else {
        cout << "\n>> double not found...\n" << endl;
     } // end if //
     return;
   } // end if //


  if (scan.matchs( "numf", 4 )) {
    if (scan.numf( fvalue )) {
       cout << "\n>> float found: " << fvalue  << endl << endl;
    } else {
       cout << "\n>> float not found...\n"<< endl;
    } // end if //
    return;
  } // end if //


  if (scan.matchs( "numd", 4 )) {
    if (scan.numd(dvalue)) {
       cout << "\n>> double found: " << dvalue << endl << endl;
    } else {
       cout << "\n>> double not found...\n" << endl;
    } // end if //
    return;
  } // end if //
  

  if (scan.matchs( "floatn", 4 )) {
    if (scan.floatn(fvalue)) {
       cout << "\n>> float found: " << fvalue << endl << endl;
    } else {
       cout << "\n>> float not found...\n" << endl;
    } // end if //
    return;
  } // end if //
  

   if (scan.matchs( "numi", 4 )) {
     if (scan.numi( ivalue )) {
        cout << "\n>> integer found: " << setw(10) << ivalue << endl << endl;
     } else {
        cout << "\n>> integer not found...\n" << endl;
     } // end if //
     return;
   } // end if //

   if (scan.matchs( "integr", 4 )) {
     if (scan.integr( ivalue )) {
        cout << "\n>> integer found: " << setw(10) << ivalue << endl << endl;
     } else {
        cout << "\n>> integer not found...\n" << endl;
     } // end if //
     return;
   } // end if //

   cout << "\n>> unknown option for check command...\n\n";
   return;
} // end of check_specified_item() //

// **************************************************************
// *                                                            *
// * output_command                                             *
// *                                                            *
// **************************************************************

void output_command(Scan &ScanObj)
{

   ScanObj.matchs_exact( "to");
   ScanObj.matchs_exact( "file");
   if ( ScanObj.matchs("remote", 4) or ScanObj.matchs_exact("stdout") ){
       ScanObj.out_to_stdout();
   } else if ( ScanObj.isstring() or ScanObj.label() ) {
     if (!ScanObj.setOutputFile()) {    // setOutputFile() == true means file was opened
        cerr << ".... Specified file cannot be opened.... \n"
             << "....command ignored....\n";
     } // end if //
   } // end if //
} // end of output_command() //

// **************************************************************
// *                                                            *
// * input_command                                              *
// *                                                            *
// **************************************************************

void input_command(Scan &ObjScan)
{
  ObjScan.matchs_exact( "from");
  ObjScan.matchs_exact( "file" );

  if ( ObjScan.matchs("remote", 4) or ObjScan.matchs_exact("stdin")   or ObjScan.matchs("keyboard", 5)) {
    ObjScan.in_from_stdin();
  } else if ( ObjScan.isstring() or ObjScan.label() ) {
     if (!ObjScan.setInputFile()) {
        cerr << ".... Specified file cannot be opened.... \n"
             << "....command ignored....\n";
     } // end if //
  } // end if //
} // end of input_command() //

// **************************************************************
// *                                                            *
// * process_tokens_on_line                                     *
// *                                                            *
// **************************************************************

void process_tokens_on_line(Scan &scan)
{

  char text[80];
  int ivalue;
  positiveInt sep_type;
  float value;
  positiveInt nchars;

  while (true ) {
     if( scan.isstring() ) {
       scan.scan_contents( text, nchars );
       ivalue = nchars;
       message(scan, 3, text, ivalue, value );
       scan.getstr();
       while (!scan.endstr() ) {
          scan.scan_contents( text, nchars );
          ivalue = nchars;
          message(scan, 4, text, ivalue, value );
          if (scan.matchs("stop", 4)) {
             scan.skpstr();
//          } else {
//             scan.istrue();  // not needed any longer here
          } // end if
       } // end while
     } // end if //
     else
     if( scan.label() ) {
       scan.scan_contents( text, nchars);
       ivalue = nchars;
       message(scan, 4, text, ivalue, value );
     } else if(scan.name() ) {
       scan.scan_contents( text, nchars );
       ivalue = nchars;
       message(scan, 8, text, ivalue, value);
     } else if( scan.integr( ivalue )) {
         message(scan, 5, text, ivalue, value );
     } else if( scan.floatn(value) ) {
         message(scan, 6, text, ivalue, value );
     } else if( scan.sep( sep_type ) ) {
         message(scan, 7, text, sep_type, value);
     } else if( scan.endcrd() ) {
         return;
     } else {
       scan.scan_contents( text, nchars );
       message(scan, 9, text, ivalue, value );
       return;
     } // end if //
  } // end while //
} // end of process_tokens_on_line() //
