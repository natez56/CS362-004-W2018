/********************************************************************************************************************
** Program name: UrlValidatorTest
** Authors: Khandakar Shadid - shadidk
** Chris Rico - ricoch 
** Nathan Zimmerman - zimmerna
** Date: 03/19/2018
** Description: Final Project Part B test cases for UrlValidator.java
** What the program does: Tests .isValid member of UrlValidator.
** How to run it: Compile and run. Exception should be generated, making explicit the first documented error in our 
** bug reports.  Additional errors can be discovered through the corrections outlined in our bug reports of the
** final project part B pdf document.
*********************************************************************************************************************/

import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
 //------------------Manual Testing----------------------------------------------------------------------
   
   public void testManualTest()
   {
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	int testnum=0;
	boolean test;
   /* Testing: scheme, authority,path,query */
	ResultPair testValue=new ResultPair("http://www.facebook.com",true);
	test=urlVal.isValid(testValue.item);
	System.out.println(testValue.item +" "+test+" expectedAnswer: "+testValue.valid+" Test Number: "+ ++testnum);

	ResultPair testValue2=new ResultPair("http//www.facebook.com",false);
	test=urlVal.isValid(testValue2.item);
	System.out.println(testValue2.item +" "+test+" expectedAnswer: "+testValue2.valid+" Test Number: "+ ++testnum);
	
	ResultPair testValue3=new ResultPair("www.facebook.com",false);
	test=urlVal.isValid(testValue3.item);
	System.out.println(testValue3.item +" "+test+" expectedAnswer: "+testValue3.valid+" Test Number: "+ ++testnum);
	 //ftp.xyz.com
	 ResultPair testValue4=new ResultPair("ftp.xyz.com",false);
	 test=urlVal.isValid(testValue4.item);
	 System.out.println(testValue4.item +" "+test+" expectedAnswer: "+testValue4.valid+" Test Number: "+ ++testnum);
	 
   
	 ResultPair testValue6=new ResultPair("http:/www.facebook.com/",false);
	 test=urlVal.isValid(testValue6.item);
	 System.out.println(testValue6.item +" "+test+" expectedAnswer: "+testValue6.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue7=new ResultPair("3h2://www.facebook.com/",false);
	 test=urlVal.isValid(testValue7.item);
	 System.out.println(testValue7.item +" "+test+" expectedAnswer: "+testValue7.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue8=new ResultPair("http://255.255.255.255",true);
	 test=urlVal.isValid(testValue8.item);
	 System.out.println(testValue8.item +" "+test+" expectedAnswer: "+testValue8.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue9=new ResultPair("http://www.''.com",false);
	 test=urlVal.isValid(testValue9.item);
	 System.out.println(testValue9.item +" "+test+" expectedAnswer: "+testValue9.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue10=new ResultPair("http://www.abc.com:65535",true);
	 test=urlVal.isValid(testValue10.item);
	 System.out.println(testValue10.item +" "+test+" expectedAnswer: "+testValue10.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue11=new ResultPair("http://www.abc.com:-10",false);
	 test=urlVal.isValid(testValue11.item);
	 System.out.println(testValue11.item +" "+test+" expectedAnswer: "+testValue11.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue12=new ResultPair("http://khandakarshadid@gmail.com",false);
	 test=urlVal.isValid(testValue12.item);
	 System.out.println(testValue12.item +" "+test+" expectedAnswer: "+testValue12.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue13=new ResultPair("http://www.w3.org/TR/PNG/iso_8859-1.txt",false);
	 test=urlVal.isValid(testValue13.item);
	 System.out.println(testValue13.item +" "+test+" expectedAnswer: "+testValue13.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue14=new ResultPair("http://www.google.com?action=view",false);
	 test=urlVal.isValid(testValue14.item);
	 System.out.println(testValue14.item +" "+test+" expectedAnswer: "+testValue14.valid+" Test Number: "+ ++testnum);

	 ResultPair testValue15=new ResultPair("http://mail.google.com/mail/u/0/#inbox",true);
	 test=urlVal.isValid(testValue15.item);
	 System.out.println(testValue15.item +" "+test+" expectedAnswer: "+testValue15.valid+" Test Number: "+ ++testnum);

	ResultPair testValue5=new ResultPair("h3t://www.xyz.com",true);
	test=urlVal.isValid(testValue5.item);
	System.out.println(testValue5.item +" "+test+" expectedAnswer: "+testValue5.valid+" Test Number: "+ ++testnum);		

   }
  
   
   //------------------Partition Testing----------------------------------------------------------------------   
   
   /*******************************************************************************************************************
   ** Description: testSchemePartition
   ** What it does: Complete data partitions for UrlValidator data are scheme + authority + port + path + query. 
   	  First partition is scheme. "Scheme consists of a sequence of characters beginning with a letter and followed by 
   	  any combination of letters, digits, plus (+), period (.), or hyphen (-)." This function tests valid and invalid
   	  schemes combined with remaining valid portions of a url.
   ** Describe arguments/restrictions: No arguments.
   ** What it returns: Prints tests results against expected results to screen.
   ** Sources: Quoted text information from https://en.wikipedia.org/wiki/URL
   *******************************************************************************************************************/
   public void testSchemePartition()
   {
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String validURLPart = "www.google.com";
		String schemeGood = "http://";
		String schemeBad = "1http://";

		System.out.println("Partition 1 Test Scheme.");
		
		// Test valid scheme.
		System.out.println("Test " + schemeGood + validURLPart + " Expected: true, Actual: " + urlVal.isValid(schemeGood + validURLPart));

		// Test invalid scheme.
		System.out.println("Test " + schemeBad + validURLPart + " Expected: false, Actual: " + urlVal.isValid(schemeBad + validURLPart));
		
		System.out.println();
   }
   
   /*******************************************************************************************************************
   ** Description: testAuthorityPartition
   ** What it does: Tests authority component of url. Authority consists of
      1) "An optional authentication section of a user name and password, separated by a colon, followed by an at 
      symbol (@)"
      2) "A "host", consisting of either a registered name (including but not limited to a hostname), or an IP address. 
      IPv4 addresses must be in dot-decimal notation, and IPv6 addresses must be enclosed in brackets ([ ])." This 
      function tests valid and invalid authorities combined with remaining valid portions of a url.
   ** Describe arguments/restrictions: No arguments.
   ** What it returns: Prints tests results against expected results to screen.
   ** Sources: Quoted text information from https://en.wikipedia.org/wiki/URL
   *******************************************************************************************************************/
	public void testAuthorityPartition() 
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String validURLPart = "http://";
		String authorityGood = "www.facebook.com";
		String authorityBad = "aaa.";

		System.out.println("Partition 2 Test Authority.");
		
		// Test valid authority.
		System.out.println("Test " + validURLPart + authorityGood + " Expected: true, Actual: " + urlVal.isValid(validURLPart + authorityGood));

		// Test invalid authority.
		System.out.println("Test " + validURLPart + authorityBad + " Expected: false, Actual: " + urlVal.isValid(validURLPart + authorityBad));
		
		System.out.println();
	}

	/*******************************************************************************************************************
	** Description: testPortPartition
	** What it does: Tests valid and invalid port components of a url. Port is a number separated from hostname 
	   by a colon. Valid range of numbers is 1 through 65535. Port must be positive.
	** Describe arguments/restrictions: No arguments.
	** What it returns: Prints tests results against expected results to screen.
	*******************************************************************************************************************/
	public void testPortPartition() 
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String validURLPart = "http://www.google.com";
		String portGood = ":65535";
		String portBad = ":65536";

		System.out.println("Partition 3 Test Port.");
		
		// Test valid port number.
		System.out.println("Test " + validURLPart + portGood + " Expected: true, Actual: " + urlVal.isValid(validURLPart + portGood));

		// Test invalid port number.
		System.out.println("Test " + validURLPart + portBad + " Expected: false, Actual: " + urlVal.isValid(validURLPart + portBad));
		
		System.out.println();
	}

	/*******************************************************************************************************************
	** Description: testPathPartition
	** What it does: Tests path component of url. "A path, which contains data, usually organized in hierarchical form, 
	   that appears as a sequence of segments separated by slashes." Must not begin with //.
	** Describe arguments/restrictions: No arguments.
	** What it returns: Prints tests results against expected results to screen.
	** Sources: Quoted text information from https://en.wikipedia.org/wiki/URL
	*******************************************************************************************************************/	
	public void testPathPartition() 
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String validURLPart = "http://www.google.com";
		String pathGood = "/valid";
		String pathBad = "//valid";

		System.out.println("Partition 4 Test Path.");
		
		// Test valid path.
		System.out.println("Test " + validURLPart + pathGood + " Expected: true, Actual: " + urlVal.isValid(validURLPart + pathGood));

		// Test invalid path.
		System.out.println("Test " + validURLPart + pathBad + " Expected: false, Actual: " + urlVal.isValid(validURLPart + pathBad));
		
		System.out.println();
	}

	/*******************************************************************************************************************
	** Description: testQueryPartition
	** What it does: Tests query component of url. Query is a "sequence of attribute�value pairs separated by a 
	** delimiter." No test for bad query.
	** Describe arguments/restrictions: No arguments.
	** What it returns: Prints tests results against expected results to screen.
	** Sources: Quoted text information from https://en.wikipedia.org/wiki/URL
	*******************************************************************************************************************/	
	public void testQueryPartition() 
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String validURLPart = "http://www.google.com";
		String queryGood = "?test=true";

		System.out.println("Partition 5 Test Query.");
		
		// Test valid query.
		System.out.println("Test " + validURLPart + queryGood + " Expected: true, Actual: " + urlVal.isValid(validURLPart + queryGood));
		
		System.out.println();
	}
	
	
/*------------------Program-Based Testing----------------------------------------------------------------------   
	
	Each test combines all possible permutations of URL components in the result pairs (below) to create test cases. 
	Tests will only pass if all components are valid and entire URL is also deemed valid by isValid.
	OR if any of the components are deemed invalid and the entire URL is also deemed invalid by isValid.
	
	Referenced https://en.wikipedia.org/wiki/URL for URL syntax to come up with result pairs
	
	Schema we are testing: scheme+authority+port+path+query
	<scheme>://<authority><path>?<query>
	
---------------------------------------------------------------------------------------------------------------*/
	
	
	public void testSchemeAuthority()
	{
		System.out.println("Testing Scheme-Authority Validation");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String urlToTest;
		Boolean result;

		for (ResultPair i : schemePairs)
		{
			for (ResultPair j : authorityPairs)
			{
				urlToTest = i.item + j.item;
				result = urlVal.isValid(urlToTest);
				
				//if the scheme and authority are valid and the total url is deemed valid
				///or if the scheme or authority are invalid and the total url is deemed invalid
				if((j.valid && i.valid) == result)
				{
					//print that the test passed
					System.out.println("Passed! URL is " + urlToTest + " Expected: " + (j.valid && i.valid) + ". Actual: " + result);
				}
				
				//else isValid was not able to determine a bad URL.
				else
				{
					System.out.println("Failed. URL is " + urlToTest + " Expected: " + (j.valid && i.valid) + ". Actual: " + result);
				}
			}
		}
	}
	
	public void testPort()
	{
		System.out.println("Testing Port Validation");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String goog = "http://www.google.com";
		String urlToTest;
		Boolean result;
			
		for (ResultPair j : portPairs) {
			urlToTest = goog + j.item;
			result = urlVal.isValid(urlToTest);

			// if the port is valid and the total url is deemed valid
			/// or if the port is invalid and the total url is deemed invalid
			if (j.valid == result) 
			{
				// print that the test passed
				System.out.println("Passed! URL is " + urlToTest + " Expected: " + j.valid + ". Actual: " + result);
			}

			// else isValid was not able to determine a bad URL.
			else 
			{
				System.out.println("Failed. URL is " + urlToTest + " Expected: " + j.valid + ". Actual: " + result);
			}
		}
	}

	public void testPath()
	{
		System.out.println("Testing Path Validation");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String goog = "http://www.google.com:80";
		String urlToTest;
		Boolean result;
		
		for (ResultPair j : pathPairs) {
			urlToTest = goog + j.item;
			result = urlVal.isValid(urlToTest);

			// if the path is valid and the total url is deemed valid
			/// or if the path is invalid and the total url is deemed invalid
			if (j.valid == result) 
			{
				// print that the test passed
				System.out.println("Passed! URL is " + urlToTest + " Expected: " + j.valid + ". Actual: " + result);
			}

			// else isValid was not able to determine a bad URL.
			else 
			{
				System.out.println("Failed. URL is " + urlToTest + " Expected: " + j.valid + ". Actual: " + result);
			}
		}
	}
	
	public void testQuery()
	{
		System.out.println("Testing Query Validation");
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		String goog = "http://www.google.com:80/foo";
		String urlToTest;
		Boolean result;
		
		for (ResultPair j : queryPairs) {
			urlToTest = goog + j.item;
			result = urlVal.isValid(urlToTest);

			// if the query is valid and the total url is deemed valid
			/// or if the query is invalid and the total url is deemed invalid
			if (j.valid == result) 
			{
				// print that the test passed
				System.out.println("Passed! URL is " + urlToTest + " Expected: " + j.valid + ". Actual: " + result);
			}

			// else isValid was not able to determine a bad URL.
			else 
			{
				System.out.println("Failed. URL is " + urlToTest + " Expected: " + j.valid + ". Actual: " + result);
			}
		}
	}
   
   
	ResultPair[] schemePairs = { new ResultPair("http://", true), new ResultPair("https://", true),
								  new ResultPair("ftp://", true), new ResultPair("blah://", true), new ResultPair("://", false),
								  new ResultPair("/", false), new ResultPair(":", false), new ResultPair("678", false),
								  new ResultPair("!!!", false), new ResultPair("http:", false),
								  new ResultPair("file://", true), new ResultPair("irc://", true) };

	ResultPair[] authorityPairs = { new ResultPair("www.google.com", true), new ResultPair("google.com", true),
									new ResultPair("192.168.0.0", true), new ResultPair("1000.1000.1000.1000", false), new ResultPair("1.1.1.256", false),
									new ResultPair("1000.10.10.10", false), new ResultPair("....", false), new ResultPair("abc", false),
									new ResultPair("123", false), new ResultPair(".a.b.a.", false) };

	ResultPair[] portPairs = { new ResultPair("", true), new ResultPair(":80", true), new ResultPair(":8080", true),
								new ResultPair(":80808", false), new ResultPair(":808080", false), new ResultPair(":8a", false),
								new ResultPair(":A8", false), new ResultPair(":8AA8", false), new ResultPair(":AAAAA", false),
								new ResultPair(":!@#", false), new ResultPair(":-100", false) };

	ResultPair[] pathPairs = { new ResultPair("", true), new ResultPair("/blah", true), new ResultPair("/.", true),
								new ResultPair("/..", false), new ResultPair("/...", false), new ResultPair("/?", true),
								new ResultPair("/??", true), new ResultPair("/blah/foo", true), new ResultPair("/blah/foo/bar", true) };

	ResultPair[] queryPairs = { new ResultPair("", true), new ResultPair("?key==value", true),
								new ResultPair("?key===value", true), new ResultPair("?key=?value", true),
								new ResultPair("?key=??value", true),  new ResultPair("key=value", false) }; 
   
	
	
  //------------------Main----------------------------------------------------------------------   
      public static void main(String[] argv) {

		UrlValidatorTest fct = new UrlValidatorTest("url test");
		
		System.out.println("Start Manual Tests.");
		System.out.println();
		fct.testManualTest();
		System.out.println();
		System.out.println();		

		System.out.println("Start Partition Tests.");
		System.out.println();
		fct.testSchemePartition();
		fct.testAuthorityPartition();
		fct.testPortPartition();
		fct.testPathPartition();
		fct.testQueryPartition();
		System.out.println();
		System.out.println();

		System.out.println("Start Programming-based Tests.");
		System.out.println();
		fct.testSchemeAuthority();
		fct.testPort();
		fct.testPath();
		fct.testQuery();
		System.out.println();
		System.out.println();
		
		System.out.println("End Testing.");
   }


}
