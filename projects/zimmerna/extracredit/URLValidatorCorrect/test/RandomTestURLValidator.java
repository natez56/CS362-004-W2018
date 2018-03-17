/******************************************************************************
** Program name: RandomTestURLValidator.java
** Author: Nathan Zimmerman
** Date: 03/16/2018
** Description: Bonus assignment project for CS362 400 W2018. Implementation
of a random tester for URL Validator valid() method. Generates random values
for URLs based on the format scheme:[//[user[:password]@]host[:port]][/path][?query]
** How to run it: Compile into .class file and run. Run with the files that come
with the URLValidatorCorrect folder.
******************************************************************************/

import junit.framework.TestCase;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.concurrent.ThreadLocalRandom;

public class RandomTestURLValidator extends TestCase {

	public RandomTestURLValidator(String testName) {
		super(testName);
	}

	/****************************************************************************
	** Description: generateRandScheme
	** What it does: Generates a random scheme based on the format 
	scheme:[//.
	** Describe arguments/restrictions: None. 
	** What it returns: ResultPair object with the scheme string and a Boolean
	representing whether the scheme is correct or not.
	****************************************************************************/
	public ResultPair generateRandScheme() 
	{
		Boolean schemeIsValid = true;

		// Chars besides a-z that are valid scheme chars.
		char[] otherValidChars = {'+', '.', '-'};
		
		// Get random scheme length.
		int schemeLength = ThreadLocalRandom.current().nextInt(0, 10 + 1);
		char[] schemeChars = new char[schemeLength + 3];

		if (schemeLength < 1) {
			schemeIsValid = false;
		}

		// Populate scheme with random letters a-z, numbers 0-9, or other valid characters.
		for (int i = 0; i < schemeLength; i++) {
			// Random choice of letter, number, or other.
			int choice = ThreadLocalRandom.current().nextInt(0, 38 + 1);

			// Generate random values for scheme based on choice.
			if (choice < 26) {
				schemeChars[i] = (char)ThreadLocalRandom.current().nextInt(97, 122 + 1);
			} else if (choice < 36) {
				schemeChars[i] = (char)ThreadLocalRandom.current().nextInt(48, 57 + 1);
			} else {
				schemeChars[i] = otherValidChars[ThreadLocalRandom.current().nextInt(0, 2 + 1)];
			}

			// Scheme must begin with a letter to be valid.
			if (i == 0 && choice >= 26) {
				schemeIsValid = false;
			}
		}

		// Chance to generate :// or not. If any of the :// characters are not
		// generated the the scheme is bad.  Aprox 99% chance to generate each char.
		if (ThreadLocalRandom.current().nextInt(0, 100 + 1) < 99) {
			schemeChars[schemeLength] = ':';
		} else {
			schemeIsValid = false;
		}

		if (ThreadLocalRandom.current().nextInt(0, 100 + 1) < 99) {
			schemeChars[schemeLength + 1] = '/';
		} else {
			schemeIsValid = false;
		}

		if (ThreadLocalRandom.current().nextInt(0, 100 + 1) < 99) {
			schemeChars[schemeLength + 2] = '/';
		} else {
			schemeIsValid = false;
		}

		// Convert character array into string.
		String schemeString = new String(schemeChars);

		ResultPair scheme = new ResultPair(schemeString, schemeIsValid);

		return scheme;
	}

	/****************************************************************************
	** Description: generateRandAuthority
	** What it does: Generates a random authority string and tracks if it is valid.
	Authority will be generated as a host or an ip address. Authority can also have
	a username, password, and @ component. Basic format is [user[:password]@]host
	** Describe arguments/restrictions: None
	** What it returns: ResultPair consisting of the authority string and whether
	it is valid or not.
	****************************************************************************/
	public ResultPair generateRandAuthority() 
	{
		Boolean authorityIsValid = true;
		int userNameLength = 0;
		int userPasswordLength = 0;
		int hostLength = 0;
		int totalAuthorityLength = 0;
		int userIPLength = 0;
		char[] userName;
		char[] userPassword;
		char[] host;
		char[] userIP;

		// Low chance to generate a username and password + @ component.
		if (ThreadLocalRandom.current().nextInt(0, 100 + 1) > 99) {
			userNameLength = ThreadLocalRandom.current().nextInt(0, 10 + 1);
			userPasswordLength = ThreadLocalRandom.current().nextInt(0, 10 + 1);
			totalAuthorityLength += userNameLength + userPasswordLength;
		}
		
		userName = new char[userNameLength];

		// Fill username with random characters or numbers.
		for (int i = 0; i < userNameLength; i++) {
			if (ThreadLocalRandom.current().nextInt(0, 1 + 1) == 1) {
				userName[i] = (char)ThreadLocalRandom.current().nextInt(97, 122 + 1);
			} else {
				userName[i] = (char)ThreadLocalRandom.current().nextInt(48, 57 + 1);
			}
		}

		userPassword = new char[userPasswordLength];

		// Fill password with random characters or numbers.
		for (int i = 0; i < userPasswordLength; i++) {
			if (ThreadLocalRandom.current().nextInt(0, 1 + 1) == 1) {
				userPassword[i] = (char)ThreadLocalRandom.current().nextInt(97, 122 + 1);
			} else {
				userPassword[i] = (char)ThreadLocalRandom.current().nextInt(48, 57 + 1);
			}
		}	

		// 50% to generate host, otherwise generates an ip address.
		if (ThreadLocalRandom.current().nextInt(0, 1 + 1) == 1) {
			hostLength = ThreadLocalRandom.current().nextInt(0, 256 + 1);
		}

		// Max host length is 255.
		if (hostLength > 255) {
			authorityIsValid = false;
		}

		host = new char[hostLength];
		char[] otherHostChars = {'-', '.'};

		// Max number of characters between '.' in host is 63. This tracks that number.
		int labelLength = 0;

		// Min labelLength is 1. Two periods cannot follow each other.
		char prev = 'x';

		// Generate random host name using characters a-z, numbers 0-9, and otherHostChars.
		for (int i = 0; i < hostLength; i++) {
			// Add '.' for tld in host nome. For example this adds the . before com.
			if (i == hostLength - 4) {
				if (ThreadLocalRandom.current().nextInt(1, 100 + 1) < 99) {
					host[i] = '.';
				} else {
					host[i] = (char)ThreadLocalRandom.current().nextInt(97, 122 + 1);
				}
			} else {
				int choice = ThreadLocalRandom.current().nextInt(0, 2 + 1);

				if (choice == 0) {
					host[i] = (char)ThreadLocalRandom.current().nextInt(97, 122 + 1);
				} else if (choice == 1) {
					host[i] = (char)ThreadLocalRandom.current().nextInt(48, 57 + 1);
				} else {
					host[i] = otherHostChars[ThreadLocalRandom.current().nextInt(0, 1 + 1)];
				}
			}

			// Check for repeat and invalid characters in host name.
			if (host[i] == '.' && prev == '.') {
				authorityIsValid = false;
			} else if (host[i] == '.' && prev == '-') {
				authorityIsValid = false;
			} else if (host[i] == '-' && prev == '.') {
				authorityIsValid = false;
			} else if (i == 0 && host[i] == '.') {
				authorityIsValid = false;
			} else if (host[i] == '.') {
				labelLength = 0;
			} else if (host[i] == '-' && i > hostLength - 4) {
				authorityIsValid = false;
			}

			// Name cannot begin with '.' or '-'.
			if (i == 0) {
				if(host[i] == '.' || host[i] == '-') {
					authorityIsValid = false;
				}
			} 

			// Labels must be less than 64 characters in length.
			labelLength++;
			if (labelLength > 63) {
				authorityIsValid = false;
			}

			prev = host[i];
		}

		// Check tld value to make sure that it exists.
		if (hostLength > 0) {
			int lastDot = -1;

			// Parse tld by looking for the last dot in the authority.
			for (int i = 0; i < host.length; i++) {
				if (host[i] == '.' && i != host.length - 1) {
					lastDot = i;
				}
			}
			
			// Run tld through domainValidator.
			if (lastDot < 0) {
				authorityIsValid = false;
			} else {
				String tldIn = new String(host);

				// Ignore trailing '.'
				if (host[host.length - 1] == '.') {
					tldIn = tldIn.substring(lastDot, host.length - 1);
				} else {
					tldIn = tldIn.substring(lastDot);
				}
				
				DomainValidator domainValidator = DomainValidator.getInstance(true);
				if (domainValidator.isValidTld(tldIn) == false) {
					authorityIsValid = false;
				}
			}
		}
		
		// Host length must be at least 3 chars.
		if (host.length > 0 && host.length < 3) {
			authorityIsValid = false;
		}

		// Track the total length of the authority.
		totalAuthorityLength += hostLength;
		
		// Generate IPV6 IP address. Only used if host length is < 1. Also converts
		// The component numbers into a char array to add to the final authority string.
		int firstNum = ThreadLocalRandom.current().nextInt(0, 256 + 1);
		char[] firstNumChars = ("" + firstNum).toCharArray();

		int secondNum = ThreadLocalRandom.current().nextInt(0, 256 + 1);
		char[] secondNumChars = ("" + secondNum).toCharArray();

		int thirdNum = ThreadLocalRandom.current().nextInt(0, 256 + 1);
		char[] thirdNumChars = ("" + thirdNum).toCharArray();

		int fourthNum = ThreadLocalRandom.current().nextInt(0, 256 + 1);
		char[] fourthNumChars = ("" + fourthNum).toCharArray();
		
		userIPLength = firstNumChars.length + secondNumChars.length + thirdNumChars.length + fourthNumChars.length + 3;

		userIP = new char[userIPLength];		

		if (hostLength > 0){
			userIPLength = 0;
		} else {
			int j = 0;

			// Add all the separate components together into one char array
			for (int i = 0; i < firstNumChars.length; i++) {
				userIP[j] = firstNumChars[i];
				j++;
			}

			userIP[j] = '.';
			j++;

			for (int i = 0; i < secondNumChars.length; i++) {
				userIP[j] = secondNumChars[i];
				j++;
			}

			userIP[j] = '.';
			j++;

			for (int i = 0; i < thirdNumChars.length; i++) {
				userIP[j] = thirdNumChars[i];
				j++;
			}

			userIP[j] = '.';
			j++;

			for (int i = 0; i < fourthNumChars.length; i++) {
				userIP[j] = fourthNumChars[i];
				j++;
			}
		}

		// IP addres numbers can have a max value of 255.
		if (firstNum > 255 || secondNum > 255 || thirdNum > 255 || fourthNum > 255) {
			authorityIsValid = false;
		}
		
		totalAuthorityLength += userIPLength;

		// Track the @ symbol by adding 1 to total length.
		if (userNameLength + userPasswordLength > 0) {
			totalAuthorityLength += 1;
		}	
		
		// Create a character array to track all of the separate authority components.
		char[] authorityChars = new char[totalAuthorityLength];

		int i = 0;

		// Add each component of authority to the final character array.
		for (int j = 0; j < userNameLength; j++) {
			authorityChars[i] = userName[j];
			i++;
		}

		for (int j = 0; j < userPasswordLength; j++) {
			authorityChars[i] = userPassword[j];
			i++;
		}

		if (userNameLength + userPasswordLength > 0) {
			authorityChars[i] = '@';
			i++;
		}

		for (int j = 0; j < hostLength; j++) {
			authorityChars[i] = host[j];
			i++;
		}

		for (int j = 0; j < userIPLength; j++) {
			authorityChars[i] = userIP[j];
			i++;
		}
		
		// Convert character array into string format.
		String authorityString = new String(authorityChars);
		
		ResultPair authority = new ResultPair(authorityString, authorityIsValid);

		return authority;
	}

	/****************************************************************************
	** Description: generateRandPort
	** What it does: Chance to generate a random port number. Found in URL.
	Preceded by ':' marking this number as a port number.
	** Describe arguments/restrictions: None
	** What it returns: ResultPair with port number in string format and a Boolean
	representing whether the number is valid or not.
	****************************************************************************/
	public ResultPair generateRandPort() 
	{
		Boolean portIsValid = true;
		int portNum = 0;
		String portString;

		// Chance to generate a port number -1 to 70000.
		if (ThreadLocalRandom.current().nextInt(1, 10 + 1) < 5) {
			portNum = ThreadLocalRandom.current().nextInt(-1, 70000 + 1);

			// Check if port number is within valid range.
			if (portNum < 0 || portNum > 65535) {
				portIsValid = false;
			}

			// Convert int to char array and add ':' character at beginning.
			char[] portChars = (":" + portNum).toCharArray();
			
			// Convert character array to string.
			portString = new String(portChars);
		} else {
			portString = "";
		}
		
		ResultPair port = new ResultPair(portString, portIsValid);

		return port;
	}

	/****************************************************************************
	** Description: generateRanPath
	** What it does: Generates a random path for a URL.
	** Describe arguments/restrictions: None.
	** What it returns: ResultPair containing a path string and a Boolean representing
	if the path is valid or not.
	****************************************************************************/
	public ResultPair generateRandPath() 
	{
		Boolean pathIsValid = true;

		// Generate random path length.
		int pathLength = ThreadLocalRandom.current().nextInt(0, 100 + 1);

		// Other valid path characters.
		char[] pathOtherChars = {'@', '&', '=', '+', ',', '.', '!', '/', '~', '*', '\'', '%', '$', '_', ';'};
		char[] pathChars = new char[pathLength];

		// Used to track if // is present in path. // is not valid.
		char prev = 'x';

		for (int i = 0; i < pathLength; i++) {
			// Initial path value is /
			if (i == 0) {
				pathChars[i] = '/';
			} else {
				int choice = ThreadLocalRandom.current().nextInt(0, 2 + 1);

				// Generate either a character a-z, number 0-9, or other character.
				if (choice == 0) {
					pathChars[i] = (char)ThreadLocalRandom.current().nextInt(97, 122 + 1);
				} else if (choice == 1) {
					pathChars[i] = (char)ThreadLocalRandom.current().nextInt(48, 57 + 1);
				} else {
					pathChars[i] = pathOtherChars[ThreadLocalRandom.current().nextInt(0, pathOtherChars.length)];
				}
			}

			// The path // is not valid.
			if (pathChars[i] == '/' && prev == '/') {
				pathIsValid = false;
			}

			prev = pathChars[i];
		}
		
		// Convert path character array to string.
		String pathString = new String(pathChars);
		
		// Check path for the presence of /../ or /.. if either are present then the
		// path is not valid.
		try {
			URI uri = new URI(null,null,pathString,null);
			String norm = uri.normalize().getPath();

      if (norm.startsWith("/../") || norm.equals("/..")) {   // Trying to go to the parent dir
        pathIsValid = false;
      }
    } catch (URISyntaxException e) {
      pathIsValid = false;
    }

    ResultPair path = new ResultPair(pathString, pathIsValid);

    return path;
	}

	/****************************************************************************
	** Description: generateRandQuery
	** What it does: Generates a random query string.
	** Describe arguments/restrictions: None.
	** What it returns: ResultPair containing a query string and a Boolean representing
	if the query string is valid or not.
	****************************************************************************/
	public ResultPair generateRandQuery() 
	{
		Boolean queryIsValid = true;

		// Generate a random query string length.
		int queryLength = ThreadLocalRandom.current().nextInt(0, 100 + 1);

		// Other characters besides letters and numbers that are valid.
		char[] queryOtherChars = {'@', '&', '=', '+', ',', '.', '!', '/', '~', '*', '\'', '%', '$', '_', ';', '?'};
		char[] queryChars = new char[queryLength];

		for (int i = 0; i < queryLength; i++) {
			// Initial query char is '?'
			if (i == 0) {
				queryChars[i] = '?';
			} else {
				int choice = ThreadLocalRandom.current().nextInt(0, 2 + 1);
				if (choice == 0) {
					queryChars[i] = (char)ThreadLocalRandom.current().nextInt(97, 122 + 1);
				} else if (choice == 1) {
					queryChars[i] = (char)ThreadLocalRandom.current().nextInt(48, 57 + 1);
				} else {
					queryChars[i] = queryOtherChars[ThreadLocalRandom.current().nextInt(0, queryOtherChars.length)];
				}
			}
		}
		
		// Convert query char array to string.
		String queryString = new String(queryChars);
	
		ResultPair query = new ResultPair(queryString, queryIsValid);

		return query;
	}       

	/****************************************************************************
	** Description: randomTest
	** What it does: Generates a random url to test. Calls a test oracle function
	that compares the result of a call to the UrlValidator function isValid with
	the correctly simulated results generated by the various random generate functions.
	** Describe arguments/restrictions: None
	** What it returns: Boolean, true if results between the isValid function call
	and the simulated results do not match. False otherwise.
	****************************************************************************/
	public Boolean randomTest() 
	{
		Boolean isFailure;

		// Generate each component of the URL.
		ResultPair scheme = generateRandScheme();
		ResultPair authority = generateRandAuthority();
		ResultPair port = generateRandPort();
		ResultPair path = generateRandPath();
		ResultPair query = generateRandQuery();

		// Add each component to create the url string to test.
		String url = scheme.item + authority.item + port.item + path.item + query.item;

		isFailure = testOracle(url, scheme.valid, authority.valid, port.valid, 
		                       path.valid, query.valid);

		return isFailure;
	}

	/****************************************************************************
	** Description: testOracle
	** What it does: Compares the simulated results of the generate functions with
	that of the isValid function call.
	** Describe arguments/restrictions: Takes a url string and the boolean results
	of each of the generate functions that have tracked whether each component of 
	the Url is valid or not. 
	** What it returns: Returns true if the function isValid matches the result
	of the booleans given by the generate functions. Otherwise returns false.
	****************************************************************************/
	public Boolean testOracle(String testURL, Boolean isSchemeValid, 
	                          Boolean isAuthorityValid, Boolean isPortValid, 
	                          Boolean isPathValid, Boolean isQueryValid) 
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		Boolean isFailure = false;

		// Function under test.
		Boolean result = urlVal.isValid(testURL);

		// Simulated result.
		Boolean expected = isSchemeValid && isAuthorityValid && isPortValid && isPathValid && isQueryValid;
		
		// Fails if results do not match expectations. A fail indicates a problem with the isValid function.
		if (result != expected) {
			System.out.println("FAILURE URL: " + testURL + " Expected: " + expected + " Actual: " + result);
			isFailure = true;
		} else {
			System.out.println("PASS URL: " + testURL + " Expected: " + expected + " Actual: " + result);
		}

		return isFailure;
	}
	
  /****************************************************************************
	** Description: Main
	** What it does: Driver function to run the random tester for the UrlValidator
	isValid function.
	** What it returns: Prints total passed tests to the screen. Also prints the
	URL being tested along with expected and actual results.
	****************************************************************************/  
	public static void main(String[] argv) 
	{
		RandomTestURLValidator fct = new RandomTestURLValidator("url test");
		Boolean isFailure;
		int numFailures = 0;
		int numTests = 5000;

		for (int i = 0; i < numTests; i++) {
			isFailure = fct.randomTest();

			if (isFailure) {
				numFailures++;
			}
		}

		System.out.println("Total passed tests = " + (numTests - numFailures) + "/" + numTests);
	}
}
