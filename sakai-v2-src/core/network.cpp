#include "network.h"
// Include XOR()
#include "security.h"

namespace NET
{
	std::string GetServerName()
	{
		// Create connection handle
		HINTERNET Intern = InternetOpenA(XOR("SAKAI-V2"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, INTERNET_FLAG_DONT_CACHE);
		if (Intern)
		{
			// Init our connection with server
			HINTERNET Connect = InternetConnectA(Intern, XOR(m_szDomainName), INTERNET_DEFAULT_HTTPS_PORT, "", "", INTERNET_SERVICE_HTTP, 0, NULL);
			if (Connect) 
			{
				
			}
		}
	}

	inline const char* m_szDomainName = "*YOUR DOMAIN NAME*";
}