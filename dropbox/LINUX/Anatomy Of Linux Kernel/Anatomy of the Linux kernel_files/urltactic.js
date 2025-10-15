/*
Tactic code replacement
Author : Frank Consiglio
Date: May 2006
Contacts:  Sera Lewis, Diane Hoag, Tom Coppedge 

This code rebuilds the href URL of a link on a dW page.
The logic of this code is based on a set of RULES: inbound URL vs. outbound HREF.
See one of the contacts for details.
*/

/*
THE RULES
RULE 1.
S_TACT
1st choice:  	inbound URL from referring page
2nd choice:  	zone values
LOGIC:
if Inbound URL contains S_TACT then
	use Inbound URL S_TACT and S_CMP(if present)
else 
	use Zone S_TACT and S_CMP
**********************************************	
RULE 2.
S_PKG, S_SRCID, and source
1st choice:  	what's been coded in the href
2nd choice:  	inbound URL from referring page
LOGIC:
if HREF contains S_PKG
	use HREF S_PKG
else if Inbound contains S_PKG
	use Inbound URL S_PKG
	
if HREF contains S_SRCID
	use HREF S_SRCID
else if Inbound contains S_SRCID
	use Inbound URL S_SRCID
	
if HREF contains source
	use HREF source
else if Inbound contains source
	use Inbound URL source
*********************************************
RULE 3.
Non-tactic params (ca=, lang=, etc.)
1st choice: 	what's been coded in the href
Note:  NEVER TAKE THESE FROM THE INBOUND URL FROM REFERRING PAGE 
LOGIC:
Always use HREF params not covered in the RULES 1 & 2 above.
*/

/* global variables*/
var undefined;

/* RegExp constants*/
var QUERYPATTERN = /\?/; // a literal '?'
var TACTICPATTERN = /S_TACT/; 
var PKGPATTERN = /S_PKG/;
var SRCIDPATTERN = /S_SRCID/;
var SOURCEPATTERN = /source/;
var DEFAULTHERE = 'S_TACT=105AGX01&S_CMP=LP';// fjc 11/21
var zone_tactic = DEFAULTHERE; /* this variable is set with setDefaultQuery() */	
/* Original entry point, 
legacy code and entry point could not be changed.
linkQueryAppend():
Change the href of an <a> object.
a: is the <A>, whose HREF  we are attempting to modify
*/	
function linkQueryAppend(a)
{	
	// test if already done
	if (a.doneOnce != undefined)
	{ 	
		return;// onmouseover, do only once.
	}
	else
	{
		a.doneOnce = true;// add property to <a> object so we do not reenter
	}
	
	var hrefString =  a.href; // get the href 
	var re = new RegExp("\\?.*","g");// remove everything from '?' to the end
	var cleanHref = hrefString.match(re) ? hrefString.replace(re,"") : hrefString ; // clean off any querystring and save	
	var oldArglist = QUERYPATTERN.test(hrefString) ? hrefString.substring(hrefString.indexOf('?')+1) : ""; // get inbound arg list
	var newArglist = buildArgList(oldArglist); // rebuild the arglist
	
	a.href = cleanHref + newArglist; // rebuild and replace the href
}	
	
	
/*
prcocess the URL and HREF: step throught the logic 
and return a new arglist.
FJC - 7/6/06 Changed order of building the string.
*/
function buildArgList(outArgs)
{
	var argString = "";
	var args = location.search; // get the inbound querystring
	var inArgs  = QUERYPATTERN.test(args) ? args.substring(args.indexOf('?')+1) : ""; // get inbound arg list

	var oOutArgs = new Args(outArgs);// make an Args object
	var oInArgs = new Args(inArgs);// make an Args object

	// logic 3) get the rest of the params off of the href
	var sArgs = oOutArgs.getParams(); // get all other params
	if (sArgs != "") // if there are any
	{
		argString +=  "?" + sArgs; // add them to the argstring
	}

	// logic step 2) get the PKG, SRCID & source params from href
	if (PKGPATTERN.test(outArgs))// if there is PKG on href
	{
		argString += (argString=="")? "?" + oOutArgs.getPKG() : "&" + oOutArgs.getPKG();// use PKG from the href	
	}
	else if (PKGPATTERN.test(inArgs))
	{
		argString += (argString=="")? "?" +  oInArgs.getPKG() : "&" + oInArgs.getPKG() ;//else use PKG from the URL
	}

	if (SRCIDPATTERN.test(outArgs))// if there is SRCID on href
	{
		argString += (argString=="")? "?" + oOutArgs.getSRCID() : "&" + oOutArgs.getSRCID();// use SRCID from the href	
	}
	else if (SRCIDPATTERN.test(inArgs))
	{
		argString += (argString=="")? "?" + oInArgs.getSRCID() : "&" + oInArgs.getSRCID();//else use SRCID from the URL
	}

	if (SOURCEPATTERN.test(outArgs))// if there is source on href
	{
		argString += (argString=="")? "?" + oOutArgs.getsource() : "&" + oOutArgs.getsource();// use source from the href	
	}
	else if (SOURCEPATTERN.test(inArgs))
	{
		argString += (argString=="")? "?" + oInArgs.getsource() : "&" + oInArgs.getsource();//else use source from the URL
	}
	
		// logic step 1) get tactic
	if(TACTICPATTERN.test(inArgs))// if there is a Tactic on Inbound URL
	{
		argString += (argString=="")? "?" +   oInArgs.getTactic() : "&" +  oInArgs.getTactic();// use tactic code from the inbound URL
	}
	else if (zone_tactic != "")
	{		
		argString += (argString=="")? "?" +  zone_tactic : "&" +  zone_tactic;// else add the zone tactic.
	}

	return argString; // arg string now has a tactic and possibly other params.
}


/*Args()
Return an object with property/value pairs that
are the parameter name/value pairs of a QueryString Arg List
*/
function Args(arglist){
	this.arglist = arglist==undefined ? "" : arglist;// sanity. make it "" if arglist is not definied

	var args = new Object();
	var pairs = this.arglist.split("&"); // get an array of params
	for (var i = 0; i < pairs.length; i++)
	{
		var pos = pairs[i].indexOf('='); // look for "name=value"
		if (pos == -1) continue;
		var argname = pairs[i].substring(0, pos);// get the name
		var value = pairs[i].substring(pos+1);// get the value
		args[argname] = value; // make a property and assign the value to it
	}
	

	// access method to return a tactic code
	this.getTactic = function()// returns the S_TACT=value&S_CMP=value param
										{ 
											var tact = ( eval("args.S_TACT")==undefined ? "" : "S_TACT=" + eval("args.S_TACT"));											
											if ( tact != "")// if there is a tactic add a CMP if available
												tact += ( eval("args.S_CMP")==undefined ? "" : "&S_CMP=" + eval("args.S_CMP"));
											return tact;
										};
	
	this.getSRCID = function()// returns the S_SRCID=value param
										{ 
											return( eval("args.S_SRCID")==undefined ? "" : "S_SRCID=" + eval("args.S_SRCID") );
										};

	this.getPKG = function()// returns the S_PKG=value param
										{ 
											return( eval("args.S_PKG")==undefined ?  "" : "S_PKG=" + eval("args.S_PKG") );
										};

	this.getsource = function()// returns the source=value param
										{ 
											return( eval("args.source")==undefined ? "" : "source=" + eval("args.source") );
										};
	
	this.getParams = function()// cleans up the arglist of all but the extra params
										{										  
												var re = new RegExp("S_TACT=(.*?&)|(&S_TACT=.[^&]*)|(S_TACT=.*)", "gi");// DO NOT MODIFY
												var result =  this.arglist.replace(re, "");												

												if (result != "")
												{							
													re.compile("S_CMP=(.*?&)|(&S_CMP=.[^&]*)|(S_CMP=.*)", "gi");// DO NOT MODIFY
												  result = result.replace(re, "");											
												}

												if (result != "")
												{							
													re.compile("S_PKG=(.*?&)|(&S_PKG=.[^&]*)|(S_PKG=.*)", "gi");// DO NOT MODIFY
												  result = result.replace(re, "");											
												}

												if (result != "")
												{													
													re.compile("S_SRCID=(.*?&)|(&S_SRCID[^&]*)|(S_SRCID=.*)", "gi");// DO NOT MODIFY
												  result = result.replace(re, "");															
												}

												if (result != "")
												{																	
													re.compile("source=(.*?&)|(&source=.[^&]*)|(source=.*)", "gi");// DO NOT MODIFY
												  result = result.replace(re, "");															
												}

												return result;
											
										};
}

/*
Collection of zones and corresponding tactic codes.
tactics is an object whose properties are the zone names,
and values are the tactic strings.  
TOO ADD A ZONE:  use the format:
zone_name : 'S_TACT=NNNAAANN&S_CMP=ZONE' ,
and insert it at the top of the property  list.

setDefaultQuery(): sets a global variable "zone_tactic" used by the Tactic rebuilding code.
This is a bad design, but it is legacy and could not be changed.
*/
function setDefaultQuery(zone){
	var pattern = /[\s]/; // any whitespace
	if ( zone==undefined)  return;// need to bullet proof this call	
	if (pattern.test(zone) || zone == "")   return;
	
	
	var tactics = {java : 'S_TACT=105AGX45&S_CMP=LPJAVA',
								linux : 'S_TACT=105AGX45&S_CMP=LPLINUX',
								notesdomino : 'S_TACT=105AGX13&S_CMP=LPLOTUS',
								ws : 'S_TACT=105AGX45&S_CMP=LPWS',
								xml : 'S_TACT=105AGX45&S_CMP=LPXML',
								aixlp : 'S_TACT=105AGY06&S_CMP=LP',
								aixart : 'S_TACT=105AGY06&S_CMP=ART',
								aixtut : 'S_TACT=105AGY06&S_CMP=TUT',
								systemslp : 'S_TACT=105AGX12&S_CMP=LP',
								systemsart : 'S_TACT=105AGX12&S_CMP=ART',
								systemstut : 'S_TACT=105AGX12&S_CMP=TUT',
								db2lp : 'S_TACT=105AGX11&S_CMP=LP',
								db2art : 'S_TACT=105AGX11&S_CMP=ART',
								db2tut : 'S_TACT=105AGX11&S_CMP=TUT',
								ibmlp : 'S_TACT=105AGX46&S_CMP=LP',
								ibmart : 'S_TACT=105AGX46&S_CMP=ART',
								ibmtut : 'S_TACT=105AGX46&S_CMP=TUT',
								lotuslp : 'S_TACT=105AGX13&S_CMP=LP',
								lotusart : 'S_TACT=105AGX13&S_CMP=ART',
								lotustut : 'S_TACT=105AGX13&S_CMP=TUT',
								rationallp : 'S_TACT=105AGX15&S_CMP=LP',
								rationalart : 'S_TACT=105AGX15&S_CMP=ART',
								rationaltut : 'S_TACT=105AGX15&S_CMP=TUT',
								edge : 'S_TACT=105AGX15&S_CMP=EDGE',
								tivolilp : 'S_TACT=105AGX14&S_CMP=LP',
								tivoliart : 'S_TACT=105AGX14&S_CMP=ART',
								tivolitut : 'S_TACT=105AGX14&S_CMP=TUT',
								webspherelp : 'S_TACT=105AGX10&S_CMP=LP',
								websphereart : 'S_TACT=105AGX10&S_CMP=ART',
								webspheretut : 'S_TACT=105AGX10&S_CMP=TUT',
								workplacelp : 'S_TACT=105AGX10&S_CMP=LP',
								workplaceart : 'S_TACT=105AGX10&S_CMP=ART',
								workplacetut : 'S_TACT=105AGX10&S_CMP=TUT',
								architecturelp : 'S_TACT=105AGX78&S_CMP=LP',
								architectureart : 'S_TACT=105AGX78&S_CMP=ART',
								architecturetut : 'S_TACT=105AGX78&S_CMP=TUT',
								autonomiclp : 'S_TACT=105AGX09&S_CMP=LP',
								autonomicart : 'S_TACT=105AGX09&S_CMP=ART',
								autonomictut : 'S_TACT=105AGX09&S_CMP=TUT',
								gridlp : 'S_TACT=105AGX07&S_CMP=LP',
								gridart : 'S_TACT=105AGX07&S_CMP=ART',
								gridtut : 'S_TACT=105AGX07&S_CMP=TUT',
								javalp : 'S_TACT=105AGX02&S_CMP=LP',
								javaart : 'S_TACT=105AGX02&S_CMP=ART',
								javatut : 'S_TACT=105AGX02&S_CMP=TUT',
								linuxlp : 'S_TACT=105AGX03&S_CMP=LP',
								linuxart : 'S_TACT=105AGX03&S_CMP=ART',
								linuxtut : 'S_TACT=105AGX03&S_CMP=TUT',
								opensourcelp : 'S_TACT=105AGX44&S_CMP=LP',
								opensourceart : 'S_TACT=105AGX44&S_CMP=ART',
								opensourcetut : 'S_TACT=105AGX44&S_CMP=TUT',
								powerlp : 'S_TACT=105AGX16&S_CMP=LP',
								powerart : 'S_TACT=105AGX16&S_CMP=ART',
								powertut : 'S_TACT=105AGX16&S_CMP=TUT',
								webserviceslp : 'S_TACT=105AGX04&S_CMP=LP',
								webservicesart : 'S_TACT=105AGX04&S_CMP=ART',
								webservicestut : 'S_TACT=105AGX04&S_CMP=TUT',
								weblp : 'S_TACT=105AGX08&S_CMP=LP',
								webart : 'S_TACT=105AGX08&S_CMP=ART',
								webtut : 'S_TACT=105AGX08&S_CMP=TUT',
								wirelesslp : 'S_TACT=105AGX05&S_CMP=LP',
								wirelessart : 'S_TACT=105AGX05&S_CMP=ART',
								wirelesstut : 'S_TACT=105AGX05&S_CMP=TUT',
								xmllp : 'S_TACT=105AGX06&S_CMP=LP',
								xmlart : 'S_TACT=105AGX06&S_CMP=ART',
								xmltut : 'S_TACT=105AGX06&S_CMP=TUT',
								xmlnewto : 'S_TACT=105AGX06&S_CMP=NEWTO',
								xmlstnd : 'S_TACT=105AGX06&S_CMP=STND',
								grnmoart : 'S_TACT=105AGX44&S_CMP=GRNMOART',
								grnmotut : 'S_TACT=105AGX44&S_CMP=GRNMOTUT',
								derbyart : 'S_TACT=105AGX44&S_CMP=DERBYART',
								derbytut : 'S_TACT=105AGX44&S_CMP=DERBYTUT',
								phpart : 'S_TACT=105AGX44&S_CMP=PHPART',
								phptut : 'S_TACT=105AGX44&S_CMP=PHPTUT',
								eclipseart : 'S_TACT=105AGX44&S_CMP=GRNMOART',
								eclipsetut : 'S_TACT=105AGX44&S_CMP=GRNMOTUT',
								download : 'S_TACT=105AGX45&S_CMP=LPDWNL',
								dlmain : 'S_TACT=105AGX28&S_CMP=DLMAIN',
								lpcd : 'S_TACT=105AGX45&S_CMP=LPCD',
								sekdvd : 'S_TACT=105AGX45&S_CMP=SEKDVD',
								wsdk : 'S_TACT=105AGX18&S_CMP=LPWSDK',
								tchbrf : 'S_TACT=107A727W&S_CMP=TCHBRF',
								execbrf : 'S_TACT=107A727W&S_CMP=LPEXECBRF',
								db2 : 'S_TACT=105AGX11&S_CMP=LPDB2',
								db2gsk : 'S_TACT=105AGX11&S_CMP=DB2GSK',
								dco : 'S_TACT=105AGX26&S_CMP=LPDCO',
								lnxss : 'S_TACT=105AGX17&S_CMP=LNXSS',
								lnxssp : 'S_TACT=105AGX17&S_CMP=LNXSSP',
								lnxssz : 'S_TACT=105AGX17&S_CMP=LNXSSZ',
								wsss : 'S_TACT=105AGX18&S_CMP=WSSS',
								dwt : 'S_TACT=105AGX19&S_CMP=ZHP',
								demos : 'S_TACT=105AGX19&S_CMP=DEMOS',
								ondemand : 'S_TACT=105AGX40&S_CMP=ZHP',
								rrctr : 'S_TACT=105AGX15&S_CMP=RRCTR',
								tbcode : 'S_TACT=104AHW62&S_CMP=TBCODE',
								lpemea : 'S_TACT=105AGX51&S_CMP=LPEMEA',
								db2bb : 'S_TACT=105AGX64&S_CMP=DB2LPBB',
								tvbb : 'S_TACT=105AGX64&S_CMP=TVLPBB',
								rbb : 'S_TACT=105AGX64&S_CMP=RLPBB',
								wesbb : 'S_TACT=105AGX64&S_CMP=WESLPBB',
								lsbb : 'S_TACT=105AGX64&S_CMP=LSLPBB',
								linuxbb : 'S_TACT=105AGX64&S_CMP=LINUXLPBB',
								perjasa : 'S_TACT=104AHW25&S_CMP=PERJASA',
								autonomic : 'S_TACT=105AGX09&S_CMP=DWNL',
								webcast : 'S_TACT=105AGX45&S_CMP=LPWC',
								migrate : 'S_TACT=105AGX42&S_CMP=MGST',
								sdp : 'S_TACT=105AGX43&S_CMP=SDP',
								db2cert703 : 'S_TACT=105AGX45&S_CMP=CERT703',
								db2cert512 : 'S_TACT=105AGX45&S_CMP=CERT512',
								wesdtuts : 'S_TACT=105AGX10&S_CMP=LIB',
								weswbt : 'S_TACT=105AGX10&S_CMP=WBT',
								lxjdk : 'S_TACT=105AGX03&S_CMP=LXJDK',
								rte : 'S_TACT=107A727W&S_CMP=RTE',
								RTE : 'S_TACT=107A727W&S_CMP=RTE',
								tchevt : 'S_TACT=107A727W&S_CMP=TCHEVT',
								lop : 'S_TACT=105AGX41&S_CMP=LOP',
								powerarch : 'S_TACT=105AGX16&S_CMP=DWPA',
								tutredirect : 'S_TACT=105AGX45&S_CMP=TUTRDR',
								jnewto : 'S_TACT=105AGX02&S_CMP=NEWTO',
								ppred : 'S_TACT=104AHW21&S_CMP=PPRED',
								sumpage : 'S_TACT=105AGX68&S_CMP=SP',
								htb : 'S_TACT=105AGX71&S_CMP=HTB',
								db2dl : 'S_TACT=105AGX11&S_CMP=DBDL',
								lsdl : 'S_TACT=105AGX13&S_CMP=LSDL',
								rdl : 'S_TACT=105AGX15&S_CMP=RDL',
								tvdl : 'S_TACT=105AGX14&S_CMP=TVDL',
								wesdl : 'S_TACT=105AGX10&S_CMP=WESDL',
								defaultHere : 'S_TACT=105AGX01&S_CMP=LP',
								archzn : 'S_TACT=105AGX78&S_CMP=HP',
								workplace : 'S_TACT=105AGX79&S_CMP=WP',
								wtpodcast : 'S_TACT=105AGX80&S_CMP=WTP',
								grnmolp : 'S_TACT=105AGX44&S_CMP=GRNMOLP',
								eclipselp : 'S_TACT=105AGX44&S_CMP=ECLLP',
								phplp : 'S_TACT=105AGX44&S_CMP=PHPLP',
								wasce : 'S_TACT=105AGX10&S_CMP=WASCE',
								journal : 'S_TACT=105AGX10&S_CMP=JRNL',
								derbylp : 'S_TACT=105AGX44&S_CMP=DERBYLP',
								simple : 'S_TACT=105AGY03&S_CMP=SIMPLELP',
								dwrussia : 'S_TACT=105AGX99&S_CMP=content',
								dwchina : 'S_TACT=105AGX52&S_CMP=content',
								dwjapan : 'S_TACT=105AGX90&S_CMP=content',
								dwkorea : 'S_TACT=105AGX55&S_CMP=content',
								radcert : 'S_TACT=105AGY04&S_CMP=RADCERT',
								soadvd : 'S_TACT=105AGX10&S_CMP=SOADVD',
								viper : 'S_TACT=105AGX11&S_CMP=VIPER',
								tybpf : 'S_TACT=105AGY14&S_CMP=TYBLP',
								eaklp : 'S_TACT=105AGY24&S_CMP=KITLP',
								callisto : 'S_TACT=105AGX44&S_CMP=CALLISTO',
								testkit : 'S_TACT=105AGY25&S_CMP=TESTLP',
								archlp : 'S_TACT=105AGX78&S_CMP=ARCHLP',
								online : 'S_TACT=105AGX28&S_CMP=ONLINE',
								wescert990lp : 'S_TACT=105AGX19&S_CMP=wescert990lp',
								wescert996lp : 'S_TACT=105AGX19&S_CMP=wescert996lp',
								db2certlp : 'S_TACT=105AGX19&S_CMP=db2certlp',
								radcertlp : 'S_TACT=105AGX19&S_CMP=radcert',
								ajaxlp : 'S_TACT=105AGY30&S_CMP=ajaxlp',
								defaultHereCN : 'S_TACT=105AGX52&S_CMP=EDU',
								defaultHereJP : 'S_TACT=105AGX90&S_CMP=EDU',
								defaultHereKR : 'S_TACT=105AGX55&S_CMP=EDU',
								defaultHereRU : 'S_TACT=105AGX99&S_CMP=EDU',
								hwlp : 'S_TACT=105AGX19&S_CMP=HWLP',
								probundle : 'S_TACT=105AGY32&S_CMP=PROBUNDLE',
								soalaunch : 'S_TACT=105AGX04&S_CMP=LAUNCH',
								demos : 'S_TACT=105AGY50&S_CMP=DEMOS',
								moveup : 'S_TACT=105AGY51&S_CMP=RADCELP',
								camtut : 'S_TACT=105AGX19&S_CMP=TUT',
								btmlp : 'S_TACT=105AGX44&S_CMP=BTMLP',
								spaces : 'S_TACT=105AGY56&S_CMP=LP',
								rbdews : 'S_TACT=105AGX15&S_CMP=RBDEWS',
								dtactr : 'S_TACT=105AGY55&S_CMP=DTACTR',
								eglkit : 'S_TACT=105AGY27&S_CMP=EGLLP'								
								}	;
	
	zone_tactic = (eval("tactics."+zone)==undefined ? "" : eval("tactics."+zone));							
}
