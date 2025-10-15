// $Id: pmh.js,v 1.11 2007/03/22 21:36:23 krusch Exp $
// Copyright (c) 2006 IBM Corporation
// Owner: Corporate Webmaster (NUS_N_NIWWW)
document.write('<img src="//www.ibm.com/i/v14/t/print-header.gif" width="510" height="32" alt="" id="print-masthead"/>');

// Survey invitation
function ibmSurveySelect() {
	var dc = document.cookie;
	var prefix = 'ibmSurvey=';

	var begin = dc.indexOf(prefix);
	var now = new Date();
	if (begin == -1 || (begin > 0 && dc.indexOf("; " + prefix) == -1)) {
		if (window.location.href.indexOf(".ibm.com") > 0) {
			document.cookie = prefix + now.getTime().toString() + "; path=/; domain=.ibm.com";
		}
	}
}
ibmSurveySelect();

// List of patterns for inclusion and exclusion from search keyword tracking
// The first matching rule applies (true = track, false = don't track)
var ibmSearchTermRules = new Array(
	[ "/support/au/", false ],
	[ "//www.ibm.com/(.+/)?au/", true ],
        [ "/businesscenter/smb/(dk|fi|no|se)/", true ]
	);
if (typeof RegExp != 'undefined' && typeof(encodeURIComponent) != 'undefined' && typeof(document.forms['search-form']) == 'object') {
	for (var ibmSearchTermRule = 0; ibmSearchTermRule < ibmSearchTermRules.length; ibmSearchTermRule++) {

		var ibmSearchTermRegexp = new RegExp(ibmSearchTermRules[ibmSearchTermRule][0]);
        if (ibmSearchTermRegexp.test(window.location.href)) {
			if (ibmSearchTermRules[ibmSearchTermRule][1]) {
				document.forms['search-form'].onsubmit = function () {
					if (typeof sa_onclick == 'function' && typeof sa_gif == 'string')
						sa_onclick("http://www.ibm.com/search/term/" + encodeURIComponent(document.forms['search-form'].q.value) + "/?re=" + encodeURIComponent(window.location.href));
					return true;
				};
			}
			break;
        }
	}
}

// Load OpenSearch description and feeds for compatible browsers
function ibmSearchOpensearchLink() {
	if (typeof document.createElement != 'undefined') {
		var head = document.getElementsByTagName('head');
		if (head.length > 0) {
			if (typeof window.external == 'object' &&
                                window.external && 
				typeof window.external.AddSearchProvider != 'undefined' &&
				window.location.hostname.indexOf('.ibm.com') != -1) {
				var link = document.createElement('link');
				link.setAttribute('rel', 'search');
				link.setAttribute('type', 'application/opensearchdescription+xml');
				link.setAttribute('href', 'http://www.ibm.com/search/opensearch/description.xml');
				link.setAttribute('title', 'IBM Search');
				head[0].appendChild(link);
			}

			// Restrict feeds to UTF-8 encoded searches
			if (window.location.href.toLowerCase().indexOf('//www.ibm.com/search/?') != -1 &&
				window.location.href.toLowerCase().indexOf('en=utf') != -1) {
				var link = document.createElement('link');
				link.setAttribute('rel', 'alternate');
				link.setAttribute('type', 'application/rss+xml');
				link.setAttribute('href', 'http://www.ibm.com/fscripts/search/opensearch/search.fcgi' + window.location.search + '&format=rss&startIndex=1');
				link.setAttribute('title', document.title + ' (RSS)');
				head[0].appendChild(link);

				var link = document.createElement('link');
				link.setAttribute('rel', 'alternate');
				link.setAttribute('type', 'application/atom+xml');
				link.setAttribute('href', 'http://www.ibm.com/fscripts/search/opensearch/search.fcgi' + window.location.search + '&format=atom&startIndex=1');
				link.setAttribute('title', document.title + ' (ATOM)');
				head[0].appendChild(link);
			}
		}
	}
}
ibmSearchOpensearchLink();
